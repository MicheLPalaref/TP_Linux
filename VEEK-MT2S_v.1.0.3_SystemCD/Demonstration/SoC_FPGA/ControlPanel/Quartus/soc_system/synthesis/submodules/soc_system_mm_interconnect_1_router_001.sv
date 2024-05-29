// (C) 2001-2017 Intel Corporation. All rights reserved.
// Your use of Intel Corporation's design tools, logic functions and other 
// software and tools, and its AMPP partner logic functions, and any output 
// files any of the foregoing (including device programming or simulation 
// files), and any associated documentation or information are expressly subject 
// to the terms and conditions of the Intel Program License Subscription 
// Agreement, Intel MegaCore Function License Agreement, or other applicable 
// license agreement, including, without limitation, that your use is for the 
// sole purpose of programming logic devices manufactured by Intel and sold by 
// Intel or its authorized distributors.  Please refer to the applicable 
// agreement for further details.



// Your use of Altera Corporation's design tools, logic functions and other 
// software and tools, and its AMPP partner logic functions, and any output 
// files any of the foregoing (including device programming or simulation 
// files), and any associated documentation or information are expressly subject 
// to the terms and conditions of the Altera Program License Subscription 
// Agreement, Altera MegaCore Function License Agreement, or other applicable 
// license agreement, including, without limitation, that your use is for the 
// sole purpose of programming logic devices manufactured by Altera and sold by 
// Altera or its authorized distributors.  Please refer to the applicable 
// agreement for further details.


// $Id: //acds/rel/16.1/ip/merlin/altera_merlin_router/altera_merlin_router.sv.terp#1 $
// $Revision: #1 $
// $Date: 2016/08/07 $
// $Author: swbranch $

// -------------------------------------------------------
// Merlin Router
//
// Asserts the appropriate one-hot encoded channel based on 
// either (a) the address or (b) the dest id. The DECODER_TYPE
// parameter controls this behaviour. 0 means address decoder,
// 1 means dest id decoder.
//
// In the case of (a), it also sets the destination id.
// -------------------------------------------------------

`timescale 1 ns / 1 ns

module soc_system_mm_interconnect_1_router_001_default_decode
  #(
     parameter DEFAULT_CHANNEL = 7,
               DEFAULT_WR_CHANNEL = -1,
               DEFAULT_RD_CHANNEL = -1,
               DEFAULT_DESTID = 2 
   )
  (output [86 - 82 : 0] default_destination_id,
   output [30-1 : 0] default_wr_channel,
   output [30-1 : 0] default_rd_channel,
   output [30-1 : 0] default_src_channel
  );

  assign default_destination_id = 
    DEFAULT_DESTID[86 - 82 : 0];

  generate
    if (DEFAULT_CHANNEL == -1) begin : no_default_channel_assignment
      assign default_src_channel = '0;
    end
    else begin : default_channel_assignment
      assign default_src_channel = 30'b1 << DEFAULT_CHANNEL;
    end
  endgenerate

  generate
    if (DEFAULT_RD_CHANNEL == -1) begin : no_default_rw_channel_assignment
      assign default_wr_channel = '0;
      assign default_rd_channel = '0;
    end
    else begin : default_rw_channel_assignment
      assign default_wr_channel = 30'b1 << DEFAULT_WR_CHANNEL;
      assign default_rd_channel = 30'b1 << DEFAULT_RD_CHANNEL;
    end
  endgenerate

endmodule


module soc_system_mm_interconnect_1_router_001
(
    // -------------------
    // Clock & Reset
    // -------------------
    input clk,
    input reset,

    // -------------------
    // Command Sink (Input)
    // -------------------
    input                       sink_valid,
    input  [100-1 : 0]    sink_data,
    input                       sink_startofpacket,
    input                       sink_endofpacket,
    output                      sink_ready,

    // -------------------
    // Command Source (Output)
    // -------------------
    output                          src_valid,
    output reg [100-1    : 0] src_data,
    output reg [30-1 : 0] src_channel,
    output                          src_startofpacket,
    output                          src_endofpacket,
    input                           src_ready
);

    // -------------------------------------------------------
    // Local parameters and variables
    // -------------------------------------------------------
    localparam PKT_ADDR_H = 54;
    localparam PKT_ADDR_L = 36;
    localparam PKT_DEST_ID_H = 86;
    localparam PKT_DEST_ID_L = 82;
    localparam PKT_PROTECTION_H = 90;
    localparam PKT_PROTECTION_L = 88;
    localparam ST_DATA_W = 100;
    localparam ST_CHANNEL_W = 30;
    localparam DECODER_TYPE = 0;

    localparam PKT_TRANS_WRITE = 57;
    localparam PKT_TRANS_READ  = 58;

    localparam PKT_ADDR_W = PKT_ADDR_H-PKT_ADDR_L + 1;
    localparam PKT_DEST_ID_W = PKT_DEST_ID_H-PKT_DEST_ID_L + 1;



    // -------------------------------------------------------
    // Figure out the number of bits to mask off for each slave span
    // during address decoding
    // -------------------------------------------------------
    localparam PAD0 = log2ceil(64'h20 - 64'h0); 
    localparam PAD1 = log2ceil(64'h40 - 64'h20); 
    localparam PAD2 = log2ceil(64'h1008 - 64'h1000); 
    localparam PAD3 = log2ceil(64'h2008 - 64'h2000); 
    localparam PAD4 = log2ceil(64'h3010 - 64'h3000); 
    localparam PAD5 = log2ceil(64'h4010 - 64'h4000); 
    localparam PAD6 = log2ceil(64'h5010 - 64'h5000); 
    localparam PAD7 = log2ceil(64'h31080 - 64'h31000); 
    localparam PAD8 = log2ceil(64'h32200 - 64'h32000); 
    localparam PAD9 = log2ceil(64'h33020 - 64'h33000); 
    localparam PAD10 = log2ceil(64'h34008 - 64'h34000); 
    localparam PAD11 = log2ceil(64'h35020 - 64'h35000); 
    localparam PAD12 = log2ceil(64'h36080 - 64'h36000); 
    localparam PAD13 = log2ceil(64'h37200 - 64'h37000); 
    localparam PAD14 = log2ceil(64'h39200 - 64'h39000); 
    localparam PAD15 = log2ceil(64'h3a080 - 64'h3a000); 
    localparam PAD16 = log2ceil(64'h3b020 - 64'h3b000); 
    localparam PAD17 = log2ceil(64'h50020 - 64'h50000); 
    localparam PAD18 = log2ceil(64'h51010 - 64'h51000); 
    localparam PAD19 = log2ceil(64'h52020 - 64'h52000); 
    localparam PAD20 = log2ceil(64'h53010 - 64'h53000); 
    localparam PAD21 = log2ceil(64'h54020 - 64'h54000); 
    localparam PAD22 = log2ceil(64'h55010 - 64'h55000); 
    localparam PAD23 = log2ceil(64'h56020 - 64'h56000); 
    localparam PAD24 = log2ceil(64'h57010 - 64'h57000); 
    localparam PAD25 = log2ceil(64'h58020 - 64'h58000); 
    localparam PAD26 = log2ceil(64'h59010 - 64'h59000); 
    // -------------------------------------------------------
    // Work out which address bits are significant based on the
    // address range of the slaves. If the required width is too
    // large or too small, we use the address field width instead.
    // -------------------------------------------------------
    localparam ADDR_RANGE = 64'h59010;
    localparam RANGE_ADDR_WIDTH = log2ceil(ADDR_RANGE);
    localparam OPTIMIZED_ADDR_H = (RANGE_ADDR_WIDTH > PKT_ADDR_W) ||
                                  (RANGE_ADDR_WIDTH == 0) ?
                                        PKT_ADDR_H :
                                        PKT_ADDR_L + RANGE_ADDR_WIDTH - 1;

    localparam RG = RANGE_ADDR_WIDTH-1;
    localparam REAL_ADDRESS_RANGE = OPTIMIZED_ADDR_H - PKT_ADDR_L;

      reg [PKT_ADDR_W-1 : 0] address;
      always @* begin
        address = {PKT_ADDR_W{1'b0}};
        address [REAL_ADDRESS_RANGE:0] = sink_data[OPTIMIZED_ADDR_H : PKT_ADDR_L];
      end   

    // -------------------------------------------------------
    // Pass almost everything through, untouched
    // -------------------------------------------------------
    assign sink_ready        = src_ready;
    assign src_valid         = sink_valid;
    assign src_startofpacket = sink_startofpacket;
    assign src_endofpacket   = sink_endofpacket;
    wire [PKT_DEST_ID_W-1:0] default_destid;
    wire [30-1 : 0] default_src_channel;




    // -------------------------------------------------------
    // Write and read transaction signals
    // -------------------------------------------------------
    wire read_transaction;
    assign read_transaction  = sink_data[PKT_TRANS_READ];


    soc_system_mm_interconnect_1_router_001_default_decode the_default_decode(
      .default_destination_id (default_destid),
      .default_wr_channel   (),
      .default_rd_channel   (),
      .default_src_channel  (default_src_channel)
    );

    always @* begin
        src_data    = sink_data;
        src_channel = default_src_channel;
        src_data[PKT_DEST_ID_H:PKT_DEST_ID_L] = default_destid;

        // --------------------------------------------------
        // Address Decoder
        // Sets the channel and destination ID based on the address
        // --------------------------------------------------

    // ( 0x0 .. 0x20 )
    if ( {address[RG:PAD0],{PAD0{1'b0}}} == 19'h0   ) begin
            src_channel = 30'b000000000000010000000000000;
            src_data[PKT_DEST_ID_H:PKT_DEST_ID_L] = 1;
    end

    // ( 0x20 .. 0x40 )
    if ( {address[RG:PAD1],{PAD1{1'b0}}} == 19'h20   ) begin
            src_channel = 30'b000000000000001000000000000;
            src_data[PKT_DEST_ID_H:PKT_DEST_ID_L] = 0;
    end

    // ( 0x1000 .. 0x1008 )
    if ( {address[RG:PAD2],{PAD2{1'b0}}} == 19'h1000  && read_transaction  ) begin
            src_channel = 30'b000000000000000000100000000;
            src_data[PKT_DEST_ID_H:PKT_DEST_ID_L] = 21;
    end

    // ( 0x2000 .. 0x2008 )
    if ( {address[RG:PAD3],{PAD3{1'b0}}} == 19'h2000   ) begin
            src_channel = 30'b000000000000000000000010000;
            src_data[PKT_DEST_ID_H:PKT_DEST_ID_L] = 9;
    end

    // ( 0x3000 .. 0x3010 )
    if ( {address[RG:PAD4],{PAD4{1'b0}}} == 19'h3000   ) begin
            src_channel = 30'b000000000000000001000000000;
            src_data[PKT_DEST_ID_H:PKT_DEST_ID_L] = 11;
    end

    // ( 0x4000 .. 0x4010 )
    if ( {address[RG:PAD5],{PAD5{1'b0}}} == 19'h4000   ) begin
            src_channel = 30'b000000010000000000000000000;
            src_data[PKT_DEST_ID_H:PKT_DEST_ID_L] = 20;
    end

    // ( 0x5000 .. 0x5010 )
    if ( {address[RG:PAD6],{PAD6{1'b0}}} == 19'h5000   ) begin
            src_channel = 30'b000000001000000000000000000;
            src_data[PKT_DEST_ID_H:PKT_DEST_ID_L] = 10;
    end

    // ( 0x31000 .. 0x31080 )
    if ( {address[RG:PAD7],{PAD7{1'b0}}} == 19'h31000   ) begin
            src_channel = 30'b000000000000100000000000000;
            src_data[PKT_DEST_ID_H:PKT_DEST_ID_L] = 3;
    end

    // ( 0x32000 .. 0x32200 )
    if ( {address[RG:PAD8],{PAD8{1'b0}}} == 19'h32000   ) begin
            src_channel = 30'b000000000000000000010000000;
            src_data[PKT_DEST_ID_H:PKT_DEST_ID_L] = 2;
    end

    // ( 0x33000 .. 0x33020 )
    if ( {address[RG:PAD9],{PAD9{1'b0}}} == 19'h33000   ) begin
            src_channel = 30'b000100000000000000000000000;
            src_data[PKT_DEST_ID_H:PKT_DEST_ID_L] = 17;
    end

    // ( 0x34000 .. 0x34008 )
    if ( {address[RG:PAD10],{PAD10{1'b0}}} == 19'h34000   ) begin
            src_channel = 30'b000000000001000000000000000;
            src_data[PKT_DEST_ID_H:PKT_DEST_ID_L] = 8;
    end

    // ( 0x35000 .. 0x35020 )
    if ( {address[RG:PAD11],{PAD11{1'b0}}} == 19'h35000   ) begin
            src_channel = 30'b001000000000000000000000000;
            src_data[PKT_DEST_ID_H:PKT_DEST_ID_L] = 19;
    end

    // ( 0x36000 .. 0x36080 )
    if ( {address[RG:PAD12],{PAD12{1'b0}}} == 19'h36000   ) begin
            src_channel = 30'b000000000000000000000000001;
            src_data[PKT_DEST_ID_H:PKT_DEST_ID_L] = 25;
    end

    // ( 0x37000 .. 0x37200 )
    if ( {address[RG:PAD13],{PAD13{1'b0}}} == 19'h37000   ) begin
            src_channel = 30'b000000000000000000000000100;
            src_data[PKT_DEST_ID_H:PKT_DEST_ID_L] = 27;
    end

    // ( 0x39000 .. 0x39200 )
    if ( {address[RG:PAD14],{PAD14{1'b0}}} == 19'h39000   ) begin
            src_channel = 30'b000000000000000000000000010;
            src_data[PKT_DEST_ID_H:PKT_DEST_ID_L] = 26;
    end

    // ( 0x3a000 .. 0x3a080 )
    if ( {address[RG:PAD15],{PAD15{1'b0}}} == 19'h3a000   ) begin
            src_channel = 30'b000000000000000000000001000;
            src_data[PKT_DEST_ID_H:PKT_DEST_ID_L] = 28;
    end

    // ( 0x3b000 .. 0x3b020 )
    if ( {address[RG:PAD16],{PAD16{1'b0}}} == 19'h3b000   ) begin
            src_channel = 30'b100000000000000000000000000;
            src_data[PKT_DEST_ID_H:PKT_DEST_ID_L] = 29;
    end

    // ( 0x50000 .. 0x50020 )
    if ( {address[RG:PAD17],{PAD17{1'b0}}} == 19'h50000   ) begin
            src_channel = 30'b000000000010000000000000000;
            src_data[PKT_DEST_ID_H:PKT_DEST_ID_L] = 23;
    end

    // ( 0x51000 .. 0x51010 )
    if ( {address[RG:PAD18],{PAD18{1'b0}}} == 19'h51000   ) begin
            src_channel = 30'b000000100000000000000000000;
            src_data[PKT_DEST_ID_H:PKT_DEST_ID_L] = 24;
    end

    // ( 0x52000 .. 0x52020 )
    if ( {address[RG:PAD19],{PAD19{1'b0}}} == 19'h52000   ) begin
            src_channel = 30'b000000000000000000001000000;
            src_data[PKT_DEST_ID_H:PKT_DEST_ID_L] = 5;
    end

    // ( 0x53000 .. 0x53010 )
    if ( {address[RG:PAD20],{PAD20{1'b0}}} == 19'h53000   ) begin
            src_channel = 30'b000000000000000010000000000;
            src_data[PKT_DEST_ID_H:PKT_DEST_ID_L] = 4;
    end

    // ( 0x54000 .. 0x54020 )
    if ( {address[RG:PAD21],{PAD21{1'b0}}} == 19'h54000   ) begin
            src_channel = 30'b000000000000000000000100000;
            src_data[PKT_DEST_ID_H:PKT_DEST_ID_L] = 7;
    end

    // ( 0x55000 .. 0x55010 )
    if ( {address[RG:PAD22],{PAD22{1'b0}}} == 19'h55000   ) begin
            src_channel = 30'b000000000000000100000000000;
            src_data[PKT_DEST_ID_H:PKT_DEST_ID_L] = 13;
    end

    // ( 0x56000 .. 0x56020 )
    if ( {address[RG:PAD23],{PAD23{1'b0}}} == 19'h56000   ) begin
            src_channel = 30'b010000000000000000000000000;
            src_data[PKT_DEST_ID_H:PKT_DEST_ID_L] = 18;
    end

    // ( 0x57000 .. 0x57010 )
    if ( {address[RG:PAD24],{PAD24{1'b0}}} == 19'h57000   ) begin
            src_channel = 30'b000001000000000000000000000;
            src_data[PKT_DEST_ID_H:PKT_DEST_ID_L] = 14;
    end

    // ( 0x58000 .. 0x58020 )
    if ( {address[RG:PAD25],{PAD25{1'b0}}} == 19'h58000   ) begin
            src_channel = 30'b000000000100000000000000000;
            src_data[PKT_DEST_ID_H:PKT_DEST_ID_L] = 6;
    end

    // ( 0x59000 .. 0x59010 )
    if ( {address[RG:PAD26],{PAD26{1'b0}}} == 19'h59000   ) begin
            src_channel = 30'b000010000000000000000000000;
            src_data[PKT_DEST_ID_H:PKT_DEST_ID_L] = 12;
    end

end


    // --------------------------------------------------
    // Ceil(log2()) function
    // --------------------------------------------------
    function integer log2ceil;
        input reg[65:0] val;
        reg [65:0] i;

        begin
            i = 1;
            log2ceil = 0;

            while (i < val) begin
                log2ceil = log2ceil + 1;
                i = i << 1;
            end
        end
    endfunction

endmodule


