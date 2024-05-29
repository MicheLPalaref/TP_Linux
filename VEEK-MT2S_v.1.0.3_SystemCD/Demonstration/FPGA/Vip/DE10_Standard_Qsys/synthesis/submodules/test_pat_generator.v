module test_pat_generator(
 clock,
 reset,

 dout_ready,
 dout_valid,
 dout_data,
 dout_sop,
 dout_eop,
 dout_empty,

 control_av_chipselect,
 control_av_write,
 control_av_address,
 control_av_writedata,
 control_av_readdata
// ,control_av_waitrequest

)/* synthesis multstyle = "dsp" */;

input clock;
input reset;

input dout_ready;
output dout_valid;
output [23:0] dout_data;
output dout_sop;
output dout_eop;
output [1:0] dout_empty;

input control_av_chipselect;
input control_av_write;
input [0:0] control_av_address;
input [31:0] control_av_writedata;
output [31:0] control_av_readdata;

assign dout_empty = 0;

parameter WIDTH=16'd1024;
parameter HEIGHT=16'd768;
parameter CTRL_PKT_NUM=3;
parameter CTRL_PKT_HEADER=24'd15;
parameter DATA_PKT_HEADER=24'd0;

///////////////////////
// Avalon-MM slave regs
reg [31:0] cpu_reg0;
//reg [31:0] cpu_reg1;

always @(posedge clock or posedge reset) begin
  if (reset) begin
    cpu_reg0 <= 32'b0;
//    cpu_reg1 <= 32'b0;
  end
  else begin
    if ( ( control_av_address == 0 ) & control_av_write & control_av_chipselect) 
      cpu_reg0 <= control_av_writedata;
//    else if ( ( control_av_address == 1 ) & control_av_write & control_av_chipselect) 
//      cpu_reg1 <= control_av_writedata;
  end
end

assign control_av_readdata = cpu_reg0 ;
//assign control_av_readdata = ( control_av_address == 0 ) ? cpu_reg0 : cpu_reg1;
///////////////////////

reg [11:0] dot_cnt;
reg [11:0] line_cnt;


///////////////////////
// Catch ready signal
reg dout_ready_reg;
always @(posedge clock or posedge reset) begin
  if (reset) 
    dout_ready_reg <= 0;
  else
    dout_ready_reg <= dout_ready;
end

///////////////////////
// valid is always 1 but masked by dout_ready_reg
assign dout_valid = dout_ready_reg;


///////////////////////
// State Machine


//reg     out;
reg  [1:0]   pkt_state;
        
parameter STATE_CTRL_PKT_SOP = 0;
parameter STATE_CTRL_PKT_DAT = 1;
parameter STATE_DATA_PKT_SOP = 2;
parameter STATE_DATA_PKT_DAT = 3;



wire ctrl_pkt_sop = (pkt_state == STATE_CTRL_PKT_SOP ) ? 1 : 0 ;
wire ctrl_pkt_eop = ((pkt_state == STATE_CTRL_PKT_DAT) & (dot_cnt==(CTRL_PKT_NUM-1))  ) ? 1 : 0 ; 


wire data_pkt_sop = (pkt_state == STATE_DATA_PKT_SOP ) ? 1 : 0 ;
wire data_pkt_eop = ((pkt_state == STATE_DATA_PKT_DAT) & (dot_cnt==(WIDTH-1)) & (line_cnt==(HEIGHT-1))  ) ? 1 : 0 ;


always @ (posedge clock or posedge reset) begin
  if (reset) pkt_state <= STATE_CTRL_PKT_SOP; 
  else 
    case (pkt_state) // state transitions
        STATE_CTRL_PKT_SOP: if (dout_ready_reg) pkt_state <= STATE_CTRL_PKT_DAT;
        STATE_CTRL_PKT_DAT: if (dout_ready_reg & ctrl_pkt_eop) pkt_state <= STATE_DATA_PKT_SOP;
        STATE_DATA_PKT_SOP: if (dout_ready_reg) pkt_state <= STATE_DATA_PKT_DAT;
        STATE_DATA_PKT_DAT: if (dout_ready_reg & data_pkt_eop) pkt_state <= STATE_CTRL_PKT_SOP;
        default : pkt_state = STATE_CTRL_PKT_DAT;
    endcase
end

///////////////////////


/////////////////////////
// sop and eop signals
assign dout_sop = (ctrl_pkt_sop | data_pkt_sop) & dout_ready_reg;
assign dout_eop = (ctrl_pkt_eop | data_pkt_eop) & dout_ready_reg;


/////////////////////////
// dot and line counter





always @(posedge clock or posedge reset) begin
  if (reset) begin
    dot_cnt <= 0;
  end
  else begin
    if (dout_ready_reg)
      if ((pkt_state == STATE_DATA_PKT_DAT) ) begin
        if ( dot_cnt < (WIDTH-1) )
          dot_cnt <= dot_cnt + 11'd1;
        else
         dot_cnt <= 0;
      end
      else if ((pkt_state == STATE_CTRL_PKT_DAT) )begin // control packet
        if ( dot_cnt < (CTRL_PKT_NUM-1) )
          dot_cnt <= dot_cnt + 11'd1;
        else
          dot_cnt <= 0;
      end
  end
end

always @(posedge clock or posedge reset) begin
  if (reset) begin
    line_cnt <= 0;
  end
  else begin
    if (dout_ready_reg ) begin
      if (pkt_state == STATE_DATA_PKT_DAT) begin
        if ( dot_cnt == (WIDTH-1) )  begin
          if ( line_cnt < (HEIGHT-1) )
            line_cnt <= line_cnt + 11'd1;
          else
            line_cnt <= 0;
        end
      end
      else
          line_cnt <= 0;
    end
  end
end

///////////////////////
/*
reg [31:0] synched_cpu0_reg;
always @(posedge clock or posedge reset) begin
  if (reset) begin
    synched_cpu0_reg <= 0;
  end
  else if (ctrl_pkt_sop)
    synched_cpu0_reg <= cpu_reg0;
end
*/
wire [31:0] synched_cpu0_reg = cpu_reg0;

reg [23:0] ctrl_data;
wire [7:0] r_data;
wire [7:0] g_data;
wire [7:0] b_data;

reg [7:0] stripe;
always @( synched_cpu0_reg[31:28] or dot_cnt ) begin
  case (synched_cpu0_reg[31:28])
    4'd1: stripe = { {dot_cnt[0] ^ {1{dot_cnt[1]}}},   7'b1000000};
    4'd2: stripe = { {dot_cnt[1:0] ^ {2{dot_cnt[2]}}}, 6'b100000};
    4'd3: stripe = { {dot_cnt[2:0] ^ {3{dot_cnt[3]}}}, 5'b10000};
    4'd4: stripe = { {dot_cnt[3:0] ^ {4{dot_cnt[4]}}}, 4'b1000};
    4'd5: stripe = { {dot_cnt[4:0] ^ {5{dot_cnt[5]}}}, 3'b100};
    4'd6: stripe = { {dot_cnt[5:0] ^ {6{dot_cnt[6]}}}, 2'b10};
    4'd7: stripe = { {dot_cnt[6:0] ^ {7{dot_cnt[7]}}}, 1'b0};
    default: stripe = 8'd255;
  endcase
end

reg [15:0] frame_r;
reg [15:0] frame_g;
reg [15:0] frame_b;
always @(posedge clock) begin
  frame_r <= stripe * {synched_cpu0_reg[23:20], synched_cpu0_reg[20], 3'b0 };
  frame_g <= stripe * {synched_cpu0_reg[19:16], synched_cpu0_reg[16], 3'b0 };
  frame_b <= stripe * {synched_cpu0_reg[15:12], synched_cpu0_reg[12], 3'b0 };
end
  
//wire [7:0] gry = { 1'b0, {dot_cnt[3:0] ^ {4{dot_cnt[4]}}}, 3'b0};

wire is_frame = ((line_cnt<60) | ( line_cnt>=540)) ? 1 : 0;  // outside of center 480 lines out of 600 line

//wire [7:0] frame_r =  (dot_cnt[1:0]== synched_cpu0_reg[21:20] ) ? { {synched_cpu0_reg[19:16]},4'b0} : 8'b0;
//wire [7:0] frame_g =  (dot_cnt[1:0]== synched_cpu0_reg[13:12] ) ? { {synched_cpu0_reg[11: 8]},4'b0} : 8'b0;
//wire [7:0] frame_b =  (dot_cnt[1:0]== synched_cpu0_reg[ 5: 4] ) ? { {synched_cpu0_reg[ 3: 0]},4'b0} : 8'b0;

wire [23:0] frame_color = { frame_r[15:8], frame_g[15:8], frame_b[15:8] };
//wire [23:0] frame_color = (synched_cpu0_reg[29]) ? ( { 3{gry} } ) :  { frame_r, frame_g, frame_b };

/*
wire [23:0] frame_color = (synched_cpu0_reg[29]) ? ( { 3{gry} } ) : 
( (dot_cnt[1:0]==0) ? { 3{{synched_cpu0_reg[15:12]},4'b0}} :
                          (dot_cnt[1:0]==1) ? { 3{{synched_cpu0_reg[11:8]},4'b0}} :
                          (dot_cnt[1:0]==2) ? { 3{{synched_cpu0_reg[7:4]},4'b0}} :  
                                              { 3{{synched_cpu0_reg[3:0]},4'b0}} ) ;  
*/


///////////////////////
// Making Image Data

//assign b_data = (synched_cpu0_reg[25:24] == 2'd0) ? synched_cpu0_reg[ 7: 0] : (synched_cpu0_reg[25:24] == 2'd1) ? dot_cnt[7:0] : dot_cnt[9:2];
//assign g_data = (synched_cpu0_reg[25:24] == 2'd0) ? synched_cpu0_reg[15: 8] : (synched_cpu0_reg[25:24] == 2'd1) ? dot_cnt[8:1] : line_cnt[7:0];
//assign r_data = (synched_cpu0_reg[25:24] == 2'd0) ? synched_cpu0_reg[23:16] : (synched_cpu0_reg[25:24] == 2'd1) ? line_cnt[7:0] : line_cnt[8:1] ;

// RGB 4bit 
assign b_data = (synched_cpu0_reg[25:24] == 2'd0) ? {synched_cpu0_reg[ 3:0],4'b0} : (synched_cpu0_reg[25:24] == 2'd1) ? dot_cnt[7:0] : dot_cnt[9:2];
assign g_data = (synched_cpu0_reg[25:24] == 2'd0) ? {synched_cpu0_reg[ 7:4],4'b0} : (synched_cpu0_reg[25:24] == 2'd1) ? dot_cnt[8:1] : line_cnt[7:0];
assign r_data = (synched_cpu0_reg[25:24] == 2'd0) ? {synched_cpu0_reg[11:8],4'b0} : (synched_cpu0_reg[25:24] == 2'd1) ? line_cnt[7:0] : line_cnt[8:1] ;

wire [23:0] image_data= (synched_cpu0_reg[26] & is_frame) ? frame_color : {r_data, g_data, b_data};

///////////////////////
// Making Final Output Data
reg [23:0] dout_data;
always @(pkt_state or ctrl_data or image_data ) begin
  case (pkt_state) 
     STATE_CTRL_PKT_SOP: dout_data = CTRL_PKT_HEADER;
     STATE_CTRL_PKT_DAT: dout_data = ctrl_data;
     STATE_DATA_PKT_SOP: dout_data = DATA_PKT_HEADER;
     default:            dout_data = image_data; 
  endcase
end

wire [15:0] w_width = WIDTH;
wire [15:0] w_height = HEIGHT;
always @(dot_cnt[3:0] or w_width or w_height) begin
  case (dot_cnt[3:0])
    0 : ctrl_data = { 4'b0,  w_width[ 7: 4], 4'b0,  w_width[11: 8], 4'b0,  w_width[15:12] };
    1 : ctrl_data = { 4'b0, w_height[11: 8], 4'b0, w_height[15:12], 4'b0,  w_width[ 3: 0] };
    2 : ctrl_data = { 4'b0,            4'b0, 4'b0, w_height[ 3: 0], 4'b0, w_height[ 7: 4] };
    default : ctrl_data = 24'bx;
  endcase
end


endmodule

