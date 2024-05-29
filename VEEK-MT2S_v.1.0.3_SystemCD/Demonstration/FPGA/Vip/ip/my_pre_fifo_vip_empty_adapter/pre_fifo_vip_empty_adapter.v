// This component is to remove empty signal contradiction error, 
// for connection with VIP and standard FIFO component.
// source has 2bit empty signal but sink does not. 

// SPR 295342 is tracking this issue.
module pre_fifo_vip_empty_adapter(
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
 dout_empty

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


  assign din_ready = dout_ready;

  assign dout_data = din_data;
  assign dout_valid = din_valid;
  assign dout_sop = din_sop;
  assign dout_eop = din_eop;
  assign dout_empty = 2'b0;

endmodule



