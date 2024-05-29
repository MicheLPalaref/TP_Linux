// ============================================================================
// Copyright (c) 2017 by Terasic Technologies Inc.
// ============================================================================
//
// Permission:
//
//   Terasic grants permission to use and modify this code for use
//   in synthesis for all Terasic Development Boards and Altera Development 
//   Kits made by Terasic.  Other use of this code, including the selling 
//   ,duplication, or modification of any portion is strictly prohibited.
//
// Disclaimer:
//
//   This VHDL/Verilog or C/C++ source code is intended as a design reference
//   which illustrates how these types of functions can be implemented.
//   It is the user's responsibility to verify their design for
//   consistency and functionality through the use of formal
//   verification methods.  Terasic provides no warranty regarding the use 
//   or functionality of this code.
//
// ============================================================================
//           
//  Terasic Technologies Inc
//  9F., No.176, Sec.2, Gongdao 5th Rd, East Dist, Hsinchu City, 30070. Taiwan
//  
//  
//                     web: http://www.terasic.com/  
//                     email: support@terasic.com
//
// ============================================================================
//Date:  Jan  7 2017
// ============================================================================

`default_nettype none
//`define ENABLE_HPS

module DE10_Standard(

      ///////// CLOCK /////////
      input              CLOCK2_50,
      input              CLOCK3_50,
      input              CLOCK4_50,
      input              CLOCK_50,

      ///////// KEY /////////
      input    [ 3: 0]   KEY,

      ///////// SW /////////
      input    [ 9: 0]   SW,

      ///////// LED /////////
      output   [ 9: 0]   LEDR,

      ///////// Seg7 /////////
      output   [ 6: 0]   HEX0,
      output   [ 6: 0]   HEX1,
      output   [ 6: 0]   HEX2,
      output   [ 6: 0]   HEX3,
      output   [ 6: 0]   HEX4,
      output   [ 6: 0]   HEX5,

      ///////// SDRAM /////////
      output             DRAM_CLK,
      output             DRAM_CKE,
      output   [12: 0]   DRAM_ADDR,
      output   [ 1: 0]   DRAM_BA,
      inout    [15: 0]   DRAM_DQ,
      output             DRAM_LDQM,
      output             DRAM_UDQM,
      output             DRAM_CS_N,
      output             DRAM_WE_N,
      output             DRAM_CAS_N,
      output             DRAM_RAS_N,

      ///////// Video-In /////////
      input              TD_CLK27,
      input              TD_HS,
      input              TD_VS,
      input    [ 7: 0]   TD_DATA,
      output             TD_RESET_N,

      ///////// VGA /////////
      output             VGA_CLK,
      output             VGA_HS,
      output             VGA_VS,
      output   [ 7: 0]   VGA_R,
      output   [ 7: 0]   VGA_G,
      output   [ 7: 0]   VGA_B,
      output             VGA_BLANK_N,
      output             VGA_SYNC_N,

      ///////// Audio /////////
      inout              AUD_BCLK,
      output             AUD_XCK,
      inout              AUD_ADCLRCK,
      input              AUD_ADCDAT,
      inout              AUD_DACLRCK,
      output             AUD_DACDAT,

      ///////// PS2 /////////
      inout              PS2_CLK,
      inout              PS2_CLK2,
      inout              PS2_DAT,
      inout              PS2_DAT2,

      ///////// ADC /////////
      output             ADC_SCLK,
      input              ADC_DOUT,
      output             ADC_DIN,
      output             ADC_CONVST,

      ///////// I2C for Audio and Video-In /////////
      output             FPGA_I2C_SCLK,
      inout              FPGA_I2C_SDAT,

      ///////// GPIO /////////
      inout    [35: 0]   GPIO,

	//////////// HSMC, HSMC connect to MTLC2 -Multi-Touch/LCD/Camera //////////
      inout 	      		CAMERA_I2C_SCL,
      inout 	      		CAMERA_I2C_SDA,
      output	      		CAMERA_PWDN_n,
      output	 [7:0]		LCD_B,
      output	      		LCD_DCLK,
      output	      		LCD_DE,
      output	      		LCD_DIM,
      output	      		LCD_DITH,
      output	 [7:0]		LCD_G,
      output	      		LCD_HSD,
      output	      		LCD_MODE,
      output	      		LCD_POWER_CTL,
      output	      		LCD_RSTB,
      output	 [7:0]		LCD_R,
      output	      		LCD_SHLR,
      output	      		LCD_UPDN,
      output	      		LCD_VSD,
      output	      		LSENSOR_ADDR_SEL,
      input 	      		LSENSOR_INT,
      inout 	      		LSENSOR_SCL,
      inout 	      		LSENSOR_SDA,
      output	      		MIPI_CS_n,
      inout 	      		MIPI_I2C_SCL,
      inout 	      		MIPI_I2C_SDA,
      output	      		MIPI_MCLK,
      input 	      		MIPI_PIXEL_CLK,
      input 	[13:0]		MIPI_PIXEL_D,
      input 	      		MIPI_PIXEL_HS,
      input 	      		MIPI_PIXEL_VS,
      output	      		MIPI_REFCLK,
      output	      		MIPI_RESET_n,
      output	      		MPU_AD0_SDO,
      output	      		MPU_CS_n,
      output	      		MPU_FSYNC,
      input 	      		MPU_INT,
      inout 	      		MPU_SCL_SCLK,
      inout 	      		MPU_SDA_SDI,
      inout 	      		TOUCH_I2C_SCL,
      inout 	      		TOUCH_I2C_SDA,
      input 	      		TOUCH_INT_n,


`ifdef ENABLE_HPS
      ///////// HPS /////////
      inout              HPS_CONV_USB_N,
      output   [14: 0]   HPS_DDR3_ADDR,
      output   [ 2: 0]   HPS_DDR3_BA,
      output             HPS_DDR3_CAS_N,
      output             HPS_DDR3_CKE,
      output             HPS_DDR3_CK_N,
      output             HPS_DDR3_CK_P,
      output             HPS_DDR3_CS_N,
      output   [ 3: 0]   HPS_DDR3_DM,
      inout    [31: 0]   HPS_DDR3_DQ,
      inout    [ 3: 0]   HPS_DDR3_DQS_N,
      inout    [ 3: 0]   HPS_DDR3_DQS_P,
      output             HPS_DDR3_ODT,
      output             HPS_DDR3_RAS_N,
      output             HPS_DDR3_RESET_N,
      input              HPS_DDR3_RZQ,
      output             HPS_DDR3_WE_N,
      output             HPS_ENET_GTX_CLK,
      inout              HPS_ENET_INT_N,
      output             HPS_ENET_MDC,
      inout              HPS_ENET_MDIO,
      input              HPS_ENET_RX_CLK,
      input    [ 3: 0]   HPS_ENET_RX_DATA,
      input              HPS_ENET_RX_DV,
      output   [ 3: 0]   HPS_ENET_TX_DATA,
      output             HPS_ENET_TX_EN,
      inout    [ 3: 0]   HPS_FLASH_DATA,
      output             HPS_FLASH_DCLK,
      output             HPS_FLASH_NCSO,
      inout              HPS_GSENSOR_INT,
      inout              HPS_I2C1_SCLK,
      inout              HPS_I2C1_SDAT,
      inout              HPS_I2C2_SCLK,
      inout              HPS_I2C2_SDAT,
      inout              HPS_I2C_CONTROL,
      inout              HPS_KEY,
      inout              HPS_LCM_BK,
      inout              HPS_LCM_D_C,
      inout              HPS_LCM_RST_N,
      input              HPS_LCM_SPIM_CLK,
      output             HPS_LCM_SPIM_MOSI,
	  input 			 HPS_LCM_SPIM_MISO,
      output             HPS_LCM_SPIM_SS,
      inout              HPS_LED,
      inout              HPS_LTC_GPIO,
      inout              HPS_RESET_N,
      output             HPS_SD_CLK,
      inout              HPS_SD_CMD,
      inout    [ 3: 0]   HPS_SD_DATA,
      output             HPS_SPIM_CLK,
      input              HPS_SPIM_MISO,
      output             HPS_SPIM_MOSI,
      output             HPS_SPIM_SS,
      input              HPS_UART_RX,
      output             HPS_UART_TX,
      input              HPS_USB_CLKOUT,
      inout    [ 7: 0]   HPS_USB_DATA,
      input              HPS_USB_DIR,
      input              HPS_USB_NXT,
      output             HPS_USB_STP,
`endif /*ENABLE_HPS*/


      ///////// IR /////////
      output             IRDA_TXD,
      input              IRDA_RXD
);


//=======================================================
//  REG/WIRE declarations
//=======================================================


wire reset_n;
wire video_hs;
wire video_vs;
wire video_clk;
wire video_de;
wire [7:0] video_r;
wire [7:0] video_g;
wire [7:0] video_b;

wire [9:0] nios_led;

//=======================================================
//  Structural coding
//=======================================================


	
assign reset_n = KEY[0];
	


    camera_qsys u0 (
        .reset_reset_n                            (reset_n),                                  //               clk_50_clk_in_reset.reset_n
        .clk_50_clk                               (CLOCK_50),                                   //                     clk_50_clk_in.clk
        .clk_vga_clk                              (video_clk),                               //                          clk_vga.clk

        .led_external_connection_export           (nios_led),                    //           led_external_connection.export
        .sw_external_connection_export            (SW),                        //            sw_external_connection.export
        .key_external_connection_export           (KEY),                       //           key_external_connection.export
		  
			// sdram 
        .clk_sdram_clk                     (DRAM_CLK),                             //                         pll_sdram.clk
        .sdram_wire_addr                   (DRAM_ADDR),                   //                        sdram_wire.addr
        .sdram_wire_ba                     (DRAM_BA),                     //                                  .ba
        .sdram_wire_cas_n                  (DRAM_CAS_N),                  //                                  .cas_n
        .sdram_wire_cke                    (DRAM_CKE),                    //                                  .cke
        .sdram_wire_cs_n                   (DRAM_CS_N),                   //                                  .cs_n
        .sdram_wire_dq              		 (DRAM_DQ),              //                                  .dq
        .sdram_wire_dqm                    ({DRAM_UDQM,DRAM_LDQM}),                    //                                  .dqm
        .sdram_wire_ras_n                  (DRAM_RAS_N),                  //                                  .ras_n
        .sdram_wire_we_n                   (DRAM_WE_N),                   //                                  .we_n
		  
		  
		  
		  // display
        .alt_vip_cl_cvo_0_clocked_video_vid_clk             (video_clk),             //       alt_vip_itc_0_clocked_video.vid_clk
        .alt_vip_cl_cvo_0_clocked_video_vid_data          ({video_r, video_g, video_b}),          //                                  .vid_data
        .alt_vip_cl_cvo_0_clocked_video_underflow         (),         //                                  .underflow
        .alt_vip_cl_cvo_0_clocked_video_vid_datavalid     (video_de),     //                                  .vid_datavalid
        .alt_vip_cl_cvo_0_clocked_video_vid_v_sync        (video_vs),        //                                  .vid_v_sync
        .alt_vip_cl_cvo_0_clocked_video_vid_h_sync        (video_hs),        //                                  .vid_h_sync
        .alt_vip_cl_cvo_0_clocked_video_vid_f             (),             //                                  .vid_f
        .alt_vip_cl_cvo_0_clocked_video_vid_h             (),             //                                  .vid_h
        .alt_vip_cl_cvo_0_clocked_video_vid_v             (),             //                                  .vid_v
		  
		  // touch
        .i2c_opencores_touch_export_scl_pad_io        (TOUCH_I2C_SCL),        //            i2c_opencores_0_export.scl_pad_io
        .i2c_opencores_touch_export_sda_pad_io        (TOUCH_I2C_SDA),        //                                  .sda_pad_io
        .touch_int_n_external_connection_export       (TOUCH_INT_n), // lcd_touch_int_external_connection.export
		  
		  // camera
        .d8m_xclkin_clk                            (MIPI_REFCLK),                            //                       d8m_xclkin.clk
		//.mipi_ref_clk                                  ( ),                             //                            mipi_ref.clk
	   .terasic_camera_conduit_end_camera_d         ({MIPI_PIXEL_D[9:0],2'b00}),               //     terasic_camera_0_conduit_end.D
		.terasic_camera_conduit_end_camera_fval      (MIPI_PIXEL_VS),            //                                 .FVAL
		.terasic_camera_conduit_end_camera_lval      (MIPI_PIXEL_HS),            //                                 .LVAL
		.terasic_camera_conduit_end_camera_pixclk    (~MIPI_PIXEL_CLK),          //                                 .PIXCLK
		  
		.i2c_opencores_camera_export_scl_pad_io        (CAMERA_I2C_SCL),       //      i2c_opencores_camera_export.scl_pad_io
		.i2c_opencores_camera_export_sda_pad_io        (CAMERA_I2C_SDA),       //                                 .sda_pad_io
		.camera_pwdn_n_external_connection_export        (CAMERA_PWDN_n),       //  mipi_pwdn_n_external_connection.export
		  
		.i2c_opencores_mipi_export_scl_pad_io          (MIPI_I2C_SCL),         //        i2c_opencores_mipi_export.scl_pad_io
		.i2c_opencores_mipi_export_sda_pad_io          (MIPI_I2C_SDA),         //                                 .sda_pad_io
		.mipi_reset_n_external_connection_export       (MIPI_RESET_n),      // mipi_reset_n_external_connection.export
		  
		.terasic_auto_focus_0_conduit_vcm_i2c_scl      (CAMERA_I2C_SCL),     //     terasic_auto_focus_0_conduit.vcm_i2c_scl
		.terasic_auto_focus_0_conduit_vcm_i2c_sda      (CAMERA_I2C_SDA),     //                                 .vcm_i2c_sda
		.terasic_auto_focus_0_conduit_clk50            (CLOCK3_50),            //                                 .clk50  		  
		  
    );

		
		
// vga on baord
assign {VGA_R, VGA_G, VGA_B} = {video_r, video_g, video_b};
assign VGA_BLANK_N = 1'b1;
assign VGA_SYNC_N = 1'b0;
assign VGA_HS = video_hs;
assign VGA_VS = video_vs;
assign VGA_CLK = ~video_clk;


// MTL - display
assign {LCD_R,LCD_G,LCD_B} = {video_r, video_g, video_b};
assign LCD_DCLK = video_clk;
assign LCD_HSD = ~video_hs;
assign LCD_VSD = ~video_vs;
//assign LCD_DE = video_de;

// lcd config
////assign LCD_BLON = 1'b1;
////assign LCD_ON = 1'b1;
assign LCD_MODE = 1'b0;  //HSD/VSD mode
assign LCD_RSTB = 1'b1; //NO RESET
assign LCD_DIM  = 1'b1;
assign LCD_POWER_CTL = 1'b1;
assign LCD_SHLR   = 1'b1;
assign LCD_UPDN   = 1'b0;
assign LCD_DITH 	= 1'b0;

// mipi camera config
////assign MIPI_WP      = 1'b0;
assign MIPI_CS_n    = 1'b0;

		
		
//heart_beat heart_beat_clk(
//.clk(MIPI_REFCLK),
//.led(LEDR[0])
//);	
//
//heart_beat heart_beat_clk2(
//.clk(MIPI_PIXEL_CLK),
//.led(LEDR[1])
//);		
		
////////////////////////////////
// LED & 7-Segment	free run
reg  [31:0]	Cont;
always@(posedge CLOCK_50 or negedge KEY[0])
    begin
        if(!KEY[0])
			 Cont	<=	0;
        else
			 Cont	<=	Cont+1;
    end
	 

wire [23:0]	mSEG7_DIG;
//7 segment LUT

SEG7_LUT_6 			SEG7_Inst	(	.oSEG0(HEX0),
							   .oSEG1(HEX1),
							   .oSEG2(HEX2),
							   .oSEG3(HEX3),
								.oSEG4(HEX4),
								.oSEG5(HEX5),
							   .iDIG(mSEG7_DIG) );
		

assign	LEDR      	=	KEY[0]? {	Cont[25:24],Cont[25:24],Cont[25:24],Cont[25:24],Cont[25:24]	} & nios_led:10'h3ff;
assign	mSEG7_DIG	=	KEY[0]? {	Cont[27:24],Cont[27:24],Cont[27:24],Cont[27:24],Cont[27:24],Cont[27:24] } :{6{4'b1000}};	
		
		
endmodule
