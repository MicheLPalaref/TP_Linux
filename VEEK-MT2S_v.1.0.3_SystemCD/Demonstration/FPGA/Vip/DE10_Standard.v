// ============================================================================
// Copyright (c) 2016 by Terasic Technologies Inc.
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
//Date:  Thu Nov  3 15:01:20 2016
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
	   input 			    HPS_LCM_SPIM_MISO,
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

wire   locked;

// mtlc2
wire       mtlc2_clk;
wire       mtlc2_hs;
wire       mtlc2_vs;
wire       mtlc2_de;
wire [7:0] mtlc2_r;
wire [7:0] mtlc2_g;
wire [7:0] mtlc2_b;

//=======================================================
//  Structural coding
//=======================================================


DE10_Standard_Qsys u0(

		/*input  wire        */    .clk_clk(CLOCK_50),     
		/*input  wire        */    .reset_reset_n(1'b1),                                

		
		/*output wire        */    .clk_mtlc_clk(mtlc2_clk),                                 
		/*output wire        */    .clk_sdram_clk(DRAM_CLK),                                
		/*output wire        */    .clk_sys_clk(),                                  
		/*output wire        */    .pll_0_locked_export(locked),   

		/*output wire [3:0]  */    .led_pio_external_connection_export(LEDR[3:0]),           
		/*input  wire [3:0]  */    .button_pio_external_connection_export(KEY),  
      
	// sdram
		/*output wire [12:0] */    .sdram_wire_addr(DRAM_ADDR),                                 
		/*output wire [1:0]  */    .sdram_wire_ba(DRAM_BA),                                   
		/*output wire        */    .sdram_wire_cas_n(DRAM_CAS_N),                                
		/*output wire        */    .sdram_wire_cke(DRAM_CKE),                                  
		/*output wire        */    .sdram_wire_cs_n(DRAM_CS_N),                                 
		/*inout  wire [15:0] */    .sdram_wire_dq(DRAM_DQ),                                   
		/*output wire [1:0]  */    .sdram_wire_dqm({DRAM_UDQM,DRAM_LDQM}),                                  
		/*output wire        */    .sdram_wire_ras_n(DRAM_RAS_N),                                
		/*output wire        */    .sdram_wire_we_n(DRAM_WE_N),    

	// the_multi_touch
		/*inout  wire        */    .touch_i2c_opencores_export_scl_pad_io(TOUCH_I2C_SCL),        
		/*inout  wire        */    .touch_i2c_opencores_export_sda_pad_io(TOUCH_I2C_SDA),        
		/*input  wire        */    .touch_int_n_external_connection_export(TOUCH_INT_n),      
   
	//TV and audio i2c
		/*output wire        */    .av_i2c_clk_pio_external_connection_export(FPGA_I2C_SCLK),    
		/*inout  wire        */    .av_i2c_data_pio_external_connection_export(FPGA_I2C_SDAT),   

	//TV
		/*output wire        */    .td_reset_pio_external_connection_export(TD_RESET_N),  
	// cvi ii
      /*input  wire        */    .alt_vip_cl_cvi_0_clocked_video_vid_clk(TD_CLK27),            
		/*input  wire [7:0]  */    .alt_vip_cl_cvi_0_clocked_video_vid_data(TD_DATA),           
		/*input  wire        */    .alt_vip_cl_cvi_0_clocked_video_vid_de(1'b1),             
		/*input  wire        */    .alt_vip_cl_cvi_0_clocked_video_vid_datavalid(1'b1),      
		/*input  wire        */    .alt_vip_cl_cvi_0_clocked_video_vid_locked(1'b1),         
		/*input  wire        */    .alt_vip_cl_cvi_0_clocked_video_vid_f(),              
		/*input  wire        */    .alt_vip_cl_cvi_0_clocked_video_vid_v_sync(),         
		/*input  wire        */    .alt_vip_cl_cvi_0_clocked_video_vid_h_sync(),         
		/*input  wire [7:0]  */    .alt_vip_cl_cvi_0_clocked_video_vid_color_encoding(), 
		/*input  wire [7:0]  */    .alt_vip_cl_cvi_0_clocked_video_vid_bit_width(),      
		/*output wire        */    .alt_vip_cl_cvi_0_clocked_video_sof(),                
		/*output wire        */    .alt_vip_cl_cvi_0_clocked_video_sof_locked(),         
		/*output wire        */    .alt_vip_cl_cvi_0_clocked_video_refclk_div(),         
		/*output wire        */    .alt_vip_cl_cvi_0_clocked_video_clipping(),           
		/*output wire        */    .alt_vip_cl_cvi_0_clocked_video_padding(),            
		/*output wire        */    .alt_vip_cl_cvi_0_clocked_video_overflow(),        
	
	
	//mtlc2 
		/*input  wire        */    .alt_vip_itc_mtlc_clocked_video_vid_clk(mtlc2_clk),       
		/*output wire [23:0] */    .alt_vip_itc_mtlc_clocked_video_vid_data({mtlc2_r,mtlc2_g,mtlc2_b}),      
		/*output wire        */    .alt_vip_itc_mtlc_clocked_video_underflow(),     
		/*output wire        */    .alt_vip_itc_mtlc_clocked_video_vid_datavalid(mtlc2_de), 
		/*output wire        */    .alt_vip_itc_mtlc_clocked_video_vid_v_sync(mtlc2_vs),    
		/*output wire        */    .alt_vip_itc_mtlc_clocked_video_vid_h_sync(mtlc2_hs),    
		/*output wire        */    .alt_vip_itc_mtlc_clocked_video_vid_f(),         
		/*output wire        */    .alt_vip_itc_mtlc_clocked_video_vid_h(),         
		/*output wire        */    .alt_vip_itc_mtlc_clocked_video_vid_v(),         
    
	//audio
		/*output wire        */    .audio_avalon_controller_conduit_end_CLK(AUD_XCK),      
		/*output wire        */    .audio_avalon_controller_conduit_end_LRCIN(),    
		/*output wire        */    .audio_avalon_controller_conduit_end_DIN(AUD_DACDAT),      
		/*output wire        */    .audio_avalon_controller_conduit_end_LRCOUT(),   
		/*input  wire        */    .audio_avalon_controller_conduit_end_DOUT(AUD_ADCDAT),     
		/*output wire        */    .audio_avalon_controller_conduit_end_BCLK(AUD_BCLK)    
		
	);




heart_beat  heart_TD_CLK27 (.CLK  (TD_CLK27), .CLK_FREQ (27_000_000), .CK_1HZ (LEDR[9]) ) ;


		
// vga on board
assign {VGA_R, VGA_G, VGA_B} = {mtlc2_r,mtlc2_g,mtlc2_b};
assign VGA_BLANK_N = 1'b1;
assign VGA_SYNC_N = 1'b0;
assign VGA_HS = ~mtlc2_hs;
assign VGA_VS = ~mtlc2_vs;
assign VGA_CLK = mtlc2_clk;


// MTL - display
assign {LCD_R,LCD_G,LCD_B} = {mtlc2_r,mtlc2_g,mtlc2_b};
assign LCD_DCLK = mtlc2_clk;
assign LCD_HSD = ~mtlc2_hs;
assign LCD_VSD = ~mtlc2_vs;
assign LCD_DE  =  mtlc2_de;

  //wire clk_touch;
assign LCD_MODE = 1'b1;  //DE mode
assign LCD_RSTB = locked; //NO RESET
assign LCD_DIM  = 1'b1;
assign LCD_POWER_CTL = 1'b1;
assign LCD_SHLR  	= 1'b1;
assign LCD_UPDN 	= 1'b0;
assign LCD_DITH 	= 1'b0;
		

endmodule
