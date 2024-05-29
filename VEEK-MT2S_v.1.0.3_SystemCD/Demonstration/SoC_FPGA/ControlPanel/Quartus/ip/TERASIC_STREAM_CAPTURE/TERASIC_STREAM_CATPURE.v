module TERASIC_STREAM_CAPTURE(
	input	clk,
	input	reset_n,
	
	// avalon slave port
	input					slave_chip_select_n,
	input		[2:0]		slave_addr,
	input					slave_read,
	output	reg	[31:0]	slave_readdata,
	input					slave_write,
	input		[31:0]	slave_writedata,
		
	// avalon master port
	output				master_chip_select_n,
	output	[31:0]	master_addr, // byte addresss
	output				master_write,
	output	[31:0]	master_writedata, // RGB 24bits
	input 				master_waitrequest_n,
	
	// streaming sink
	input	[23:0]            	sink_data,
	input								sink_valid,
	output							sink_ready,
	input								sink_sop,
	input								sink_eop,

	// streaming source
	output	[23:0]			  	   source_data,
	output								source_valid,
	input									source_ready,
	output								source_sop,
	output								source_eop
);

parameter FRAME_WIDTH	=1024;
parameter FRAME_HEIGHT	=768;
parameter ENABLE_SOURCE =0;

//////////////////////////////////////
// by pass stream
assign source_data = sink_data;
assign source_valid = sink_valid;
assign source_sop = sink_sop;
assign source_eop = sink_eop;
assign sink_ready = ((ENABLE_SOURCE==0)?1'b1:source_ready);


//////////////////////////////////////
// capture video frame (skip control frame)

//wire [3:0] package_id/* synthesis keep */; 
//wire is_control_id/* synthesis keep */;
//reg is_control_package/*synthesis noprune*/;
//
//
//assign is_control_id = (sink_data[3:0] == 4'hf)?1'b1:1'b0;
//
//always @(posedge clk or negedge reset_n)
//begin
//	if (~reset_n)
//		is_control_package <= 1'b0;
//	else if (sink_sop & sink_valid)
//		is_control_package <= is_control_id;
//end
//
//wire is_video_data;
//assign is_video_data = ((sink_sop & is_control_id) | (~sink_sop & is_control_package))?1'b0:1'b1;

wire is_video_id/* synthesis keep */;
wire is_control_id/* synthesis keep */;
wire is_data_valid_ack/* synthesis keep */;
wire is_video_sop/* synthesis keep */;
wire is_control_sop/* synthesis keep */;


assign is_video_id =  (sink_data[7:0] == 8'h00)?1'b1:1'b0;
assign is_control_id =  (sink_data[7:0] == 8'h0f)?1'b1:1'b0;


assign is_data_valid_ack = sink_valid & ((ENABLE_SOURCE==0)?1'b1:source_ready);
assign is_video_sop =  (is_video_id & sink_sop & is_data_valid_ack)?1'b1:1'b0;
assign is_control_sop =  (is_control_id & sink_sop & is_data_valid_ack)?1'b1:1'b0;
//assign is_eop = sink_eop & is_data_valid_ack;



//////////////////////////////////////
// avalon slave

reg 			flag_done/*synthesis noprune*/;
reg 			flag_capture/*synthesis noprune*/;
reg [31:0]	flag_capture_addr/*synthesis noprune*/;
reg 			flag_dummy_data/*synthesis noprune*/;
reg 			flag_auto_frame_dim/*synthesis noprune*/;
reg [15:0]	user_frame_width/*synthesis noprune*/;
reg [15:0]	user_frame_height/*synthesis noprune*/;

`define REG_CONTROL						3'd0 // control & status. W0: start bit, R0: done bit
`define REG_STATUS						3'd1 // memory start addresss
`define REG_MEM_ADDR						3'd2 //
`define REG_FRAME_DIM					3'd3 // high(bit31~bit16) + low(bit15~bit0)
`define REG_DETECTED_FRAME_DIM		3'd4 // high(bit31~bit16) + low(bit15~bit0)



always @(posedge clk or negedge reset_n)
begin
	if (~reset_n)
	begin
		flag_capture <= 1'b0;
		flag_capture_addr <= 0;
		user_frame_width <= FRAME_WIDTH;
		user_frame_height <= FRAME_HEIGHT;
	end
	else if (~slave_chip_select_n & slave_read)
	begin
		if (slave_addr == `REG_STATUS)
			slave_readdata <= {29'b0, flag_invalid_frame, flag_fifo_overflow, flag_done};
		else if (slave_addr == `REG_DETECTED_FRAME_DIM)
			slave_readdata <= {cur_frame_width, cur_frame_height};
	end
	else if (~slave_chip_select_n & slave_write)
	begin
		if (slave_addr == `REG_CONTROL)
			{flag_auto_frame_dim, flag_dummy_data, flag_capture} <= slave_writedata[2:0];
		else if (slave_addr == `REG_MEM_ADDR)
			flag_capture_addr <= slave_writedata[31:0];
		else if (slave_addr == `REG_FRAME_DIM)
			{user_frame_height, user_frame_width} <= slave_writedata[31:0];
	end
end

//////////////////////////////////////
// gen start capture signal
wire start_capture/* synthesis keep */;
reg pre_flag_capture/*synthesis noprune */;

assign start_capture = ~pre_flag_capture & flag_capture;

always @(posedge clk or negedge reset_n)
begin
	if (~reset_n)
		pre_flag_capture <= 1'b0;
	else
		pre_flag_capture <= flag_capture;
end


////////////////
// state
`define STATE_STANDYBY	3'd0
`define STATE_INIT		3'd1
`define STATE_FIND_DIM	3'd2  // find frame dimension
`define STATE_WAIT_SOP	3'd3  // wait start package of video package
`define STATE_CAPTURE	3'd4
`define STATE_DONE		3'd5


wire 			state_capturing;
reg [2:0] 	state /*synthesis noprune*/;

assign state_capturing = (state == `STATE_CAPTURE)?1'b1:1'b0;

//wire reading_adc;
wire read_more;
wire read_last_sample;
wire write_more;
wire write_last_sample;

reg 		 	flag_fifo_overflow/*synthesis noprune*/;
reg 		 	flag_invalid_frame/*synthesis noprune*/;
reg [23:0] 	read_cnt/*synthesis noprune*/;
reg [23:0] 	write_cnt/*synthesis noprune*/;
//reg			wait_last_write_done;
reg [15:0]	cur_frame_width/*synthesis noprune*/;
reg [15:0]	cur_frame_height/*synthesis noprune*/;
reg [3:0]	index/*synthesis noprune*/;
reg [23:0]  data[2:0];


assign read_more = (read_cnt < cur_frame_width*cur_frame_height)?1'b1:1'b0;
assign read_last_sample = ((read_cnt+1) == cur_frame_width*cur_frame_height)?1'b1:1'b0;

assign write_last_sample = ((write_cnt+1) == cur_frame_width*cur_frame_height)?1'b1:1'b0;
assign write_more = (write_cnt < read_cnt)?1'b1:1'b0;

always @(posedge clk or negedge reset_n)
begin
	if (~reset_n)
	begin
		state <= `STATE_STANDYBY;
		//flag_fifo_overflow <= 1'b0;
		//flag_invalid_frame <= 1'b0;
		//flag_done <= 1'b0;
		//fifo_aclr <= 1'b0;
	end
	else if (start_capture)
	begin
		state <= `STATE_INIT;
		read_cnt <= 0;
		write_cnt <= 0;
		flag_fifo_overflow <= 1'b0;
		flag_invalid_frame <= 1'b0;
	//	wait_last_write_done <= 1'b0;
		flag_done <= 1'b0;
		fifo_aclr <= 1'b1; // active fifo clear
	end
	else
	begin
		case(state)
			`STATE_STANDYBY: 
				begin
				state <= `STATE_STANDYBY;
				end
				
			`STATE_INIT:
				begin
					fifo_aclr <= 1'b0; // unactive fifo clear
					index <= 0;
					if (~fifo_wrfull & fifo_rdempty) // clear done
						state <= `STATE_FIND_DIM;				
				end
				
			`STATE_FIND_DIM:
				begin
					if (flag_auto_frame_dim)
					begin
						if (index == 0) // find sop
						begin
							if (is_control_sop)
								index <= 1;
						end
						else if (is_data_valid_ack)
						begin
							if (index == 1)
							begin
								cur_frame_width[15:12] <= sink_data[7:0];
								cur_frame_width[11:8] <= sink_data[15:8];
								cur_frame_width[7:4] <= sink_data[23:16];
							end
							else if (index == 2)
							begin
								cur_frame_width[3:0] <= sink_data[7:0];
								cur_frame_height[15:12] <= sink_data[15:8];
								cur_frame_height[11:8] <= sink_data[23:16];
							end
							else if (index == 3)
							begin
								cur_frame_height[7:4] <= sink_data[7:0];
								cur_frame_height[3:0] <= sink_data[15:8];
								state <= `STATE_WAIT_SOP;	// go to next step
								//<= sink_data[23:16];
							end
							index <= index + 1;
							
						end
					end
					else
					begin
						cur_frame_width <= user_frame_width;
						cur_frame_height <= user_frame_height;
						state <= `STATE_WAIT_SOP;	
						
					end
				end				
				
			`STATE_WAIT_SOP:
				begin
					if (is_video_sop)
						state <= `STATE_CAPTURE;	 // go to next step
					else
						state <= `STATE_WAIT_SOP; // continued to wait
				end				
				
			`STATE_CAPTURE:
				begin
						// reading (camera --> fifo)
						if (read_more & is_data_valid_ack)
						begin
							if (sink_sop | (sink_eop & ~read_last_sample) | (~sink_eop & read_last_sample))
							begin
								flag_invalid_frame <= 1'b1;
								state <= `STATE_DONE; // invalid frame, abort
							end
							else
							begin
								read_cnt <= read_cnt + 1; // continued read
								if (fifo_wrfull)
								begin
									flag_fifo_overflow <= 1'b1; // flag fifo overvoew
									state <= `STATE_DONE;  //abort
								end
									
							end
						end
						
						// writing (fifo --> memory)
						if (write_more & fifo_rdreq) //write_more & master_write)
						begin
							write_cnt <= write_cnt + 1;
							if (write_last_sample)
								state <= `STATE_DONE;
						end								
						
//						// writing (fifo --> memory)
//						if (wait_last_write_done) 
//						begin
//							if (master_waitrequest_n)
//								state <= `STATE_DONE;
//						end		
//						else if (write_more & fifo_rdreq) //write_more & master_write)
//						begin
//							write_cnt <= write_cnt + 1;
//							if (write_last_sample)
//								wait_last_write_done <= 1'b1;
//						end
				
				end
			
			`STATE_DONE: 
				begin
					flag_done <= 1'b1;
					state <= `STATE_STANDYBY;
				end
				
		endcase
	end

end


//////////////////////////////////////
// write ADC data to fifo
// ADC --> FIFO
reg  fifo_aclr;
wire fifo_wrreq;
wire fifo_rdreq;
wire fifo_rdempty;
wire fifo_wrfull;
wire [23:0]	fifo_q; // RGB 24 bits

//assign fifo_aclr = (state == `STATE_INIT)?1'b1:1'b0;
assign fifo_wrreq = state_capturing & read_more & is_data_valid_ack;

FRAME_FIFO fifo(
	.aclr(fifo_aclr),
	.data(flag_dummy_data?read_cnt:sink_data),
	.rdclk(clk),
	.rdreq(fifo_rdreq),
	.wrclk(clk),
	.wrreq(fifo_wrreq),
	.q(fifo_q),
	.rdempty(fifo_rdempty),
	.wrfull(fifo_wrfull)
	);


//////////////////////////
// write FIFO data to Memory (MM Master Port)
// FIFO ---> Memory (MM Master Port)

assign master_chip_select_n = fifo_rdempty & state_capturing;
assign master_write = ~fifo_rdempty & state_capturing;
assign master_writedata = fifo_q;
assign fifo_rdreq = master_write & master_waitrequest_n;
assign master_addr = flag_capture_addr + write_cnt * 4 ; // one word = 3/4 bytes



endmodule
