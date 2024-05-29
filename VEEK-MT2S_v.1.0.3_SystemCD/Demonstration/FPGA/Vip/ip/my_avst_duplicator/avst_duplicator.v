module avst_duplicator(
 clock,
 reset,

 din_ready,
 din_valid,
 din_data,
 din_sop,
 din_eop,
// din_empty,

 dout_ready,
 dout_valid,
 dout_data,
 dout_sop,
 dout_eop,
 dout_empty,


 dout_sub_ready,
 dout_sub_valid,
 dout_sub_data,
 dout_sub_sop,
 dout_sub_eop,
 dout_sub_empty


// control_av_chipselect,
// control_av_write,
// control_av_address,
// control_av_writedata,
// control_av_readdata
//// ,control_av_waitrequest

);

input clock;
input reset;

output din_ready;
input din_valid;
input [23:0] din_data;
input din_sop;
input din_eop;
//input [1:0] din_empty;

input dout_ready;
output dout_valid;
output [23:0] dout_data;
output dout_sop;
output dout_eop;
output [1:0] dout_empty;

input dout_sub_ready;
output dout_sub_valid;
output [23:0] dout_sub_data;
output dout_sub_sop;
output dout_sub_eop;
output [1:0]  dout_sub_empty;


//input control_av_chipselect;
//input control_av_write;
//input [0:0] control_av_address;
//input [31:0] control_av_writedata;
//output [31:0] control_av_readdata;

//assign dout_empty = 0;



///////////////////////
// Avalon-MM slave regs
/*
reg [31:0] cpu_reg0;
reg [31:0] cpu_reg1;
reg write_reg;

always @(posedge clock or posedge reset) begin
  if (reset) begin
    cpu_reg0 <= 32'b0;
    cpu_reg1 <= 32'b0;
  end
  else begin
    if ( ( control_av_address == 0 ) & control_av_write & control_av_chipselect) 
      cpu_reg0 <= control_av_writedata;
    else if ( ( control_av_address == 1 ) & control_av_write & control_av_chipselect) 
      cpu_reg1 <= control_av_writedata;
  end
end

wire write_adr1_en =  ( control_av_address == 1 ) & control_av_write & control_av_chipselect;
always @(posedge clock or posedge reset) begin
  if (reset) 
    write_reg <= 1'b0;
  else
    write_reg <= write_adr1_en;
end

wire write_neg_edge =  write_reg & ~write_adr1_en;

assign control_av_readdata = ( control_av_address == 0 ) ? cpu_reg0 : cpu_reg1;
*/
///////////////////////

//assign din_ready = dout_ready;
assign din_ready = dout_ready & dout_sub_ready;


// detect control packet
/*
  reg is_ctrl_packet;
  reg endofpacket_reg;

  always @(posedge clock or posedge reset ) begin
    if (reset) begin
      is_ctrl_packet <= 1'b0;
    end
    else if (din_valid) begin
      if (din_sop) begin
        if (din_data[3:0]==4'hf) begin
          is_ctrl_packet <= 1'b1;
        end
      end
      else if (din_eop) begin
        is_ctrl_packet <= 1'b0;
      end
    end
  end
  always @(posedge clock) begin
    endofpacket_reg <= din_eop;
  end

  wire ctrl_packet_mask = (din_sop & (din_data[3:0]==4'hf)) | (is_ctrl_packet & !endofpacket_reg);
*/
/*
  reg dout_sub_ready_reg;
  always @(posedge clock or posedge reset ) begin
    if (reset) 
      dout_sub_ready_reg <= 1'b0;
    else
      dout_sub_ready_reg <= dout_sub_ready;
  end
*/

  assign dout_data = din_data;
  assign dout_valid = din_valid;
  assign dout_sop = din_sop;
  assign dout_eop = din_eop;
  assign dout_empty = 2'b0;


  assign dout_sub_data = din_data;
  assign dout_sub_valid = din_valid; 
  assign dout_sub_sop = din_sop;
  assign dout_sub_eop = din_eop ;
  assign dout_sub_empty = 2'b0;

//  wire [7:0] data_low_zero = (din_data[7:0]<=cpu_reg0[7:0]) ? cpu_reg0[23:16] : cpu_reg0[15:8];
//  wire [7:0] data_mid_zero = (din_data[15:8]<=cpu_reg0[7:0]) ? cpu_reg0[23:16] : cpu_reg0[15:8];
//  wire [7:0] data_hig_zero = (din_data[23:16]<=cpu_reg0[7:0]) ? cpu_reg0[23:16] : cpu_reg0[15:8];

//  wire [7:0] data_all_zero = ( (din_data[23:16]<=cpu_reg0[7:0]) & (din_data[15:8]<=cpu_reg0[7:0]) & (din_data[7:0]<=cpu_reg0[7:0]) ) ? cpu_reg0[23:16] : cpu_reg0[15:8];

/*
  reg [7:0] alpha_data;
  always @(cpu_reg0 or data_low_zero or data_mid_zero or data_hig_zero or data_all_zero) begin
    case (cpu_reg0[31:24])
      8'h00: alpha_data = cpu_reg0[7:0];
      8'h01: alpha_data = data_hig_zero;
      8'h02: alpha_data = data_mid_zero;
      8'h03: alpha_data = data_low_zero;
      8'h04: alpha_data = data_all_zero;
      default: alpha_data = 8'h00;
    endcase
  end
*/

//  assign dout_alpha_data = ((din_sop) ? 8'b0: alpha_data);



endmodule



