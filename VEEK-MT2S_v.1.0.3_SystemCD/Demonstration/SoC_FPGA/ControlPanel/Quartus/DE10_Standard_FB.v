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
//Date:  Tue Sep 27 10:46:00 2016
// ============================================================================

`define ENABLE_HPS
//`define ENABLE_HSMC

module DE10_Standard_FB(

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
    output             HPS_LCM_SPIM_CLK,
    output             HPS_LCM_SPIM_MOSI,
    input              HPS_LCM_SPIM_MISO,
    output             HPS_LCM_SPIM_SS,
    inout              HPS_LED,
    inout              HPS_LTC_GPIO,
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
      inout 	      		MPU_AD0_SDO,
      output	      		MPU_CS_n,
      output	      		MPU_FSYNC,
      input 	      		MPU_INT,
      inout 	      		MPU_SCL_SCLK,
      inout 	      		MPU_SDA_SDI,
      inout 	      		TOUCH_I2C_SCL,
      inout 	      		TOUCH_I2C_SDA,
      input 	      		TOUCH_INT_n,


    ///////// IR /////////
    output             IRDA_TXD,
    input              IRDA_RXD
);

wire               clk_disp, clk_vip;
wire [7:0]         vid_r,vid_g,vid_b;
wire               vid_v_sync;
wire               vid_h_sync;
wire               vid_datavalid;


//=======================================================
//  REG/WIRE declarations
//=======================================================
wire        hps_fpga_reset_n;
wire [3:0]  fpga_debounced_buttons;
wire [9:0]  fpga_led_internal;
wire [2:0]  hps_reset_req;
wire        hps_cold_reset;
wire        hps_warm_reset;
wire        hps_debug_reset;
wire [27:0] stm_hw_events;
wire        fpga_clk_50;
// connection of internal logics
assign LEDR[9:1] = fpga_led_internal[9:1];
assign stm_hw_events = {{4{1'b0}}, SW, fpga_led_internal[8:0], fpga_debounced_buttons};
assign fpga_clk_50 = CLOCK_50;


wire HEX0P;
wire HEX1P;
wire HEX2P;
wire HEX3P;
wire HEX4P;
wire HEX5P;

wire hps_0_f2h_dma_req0_dma_req;
wire hps_0_f2h_dma_req0_dma_single;
wire hps_0_f2h_dma_req0_dma_ack;
wire hps_0_f2h_dma_req1_dma_req;
wire hps_0_f2h_dma_req1_dma_single;
wire hps_0_f2h_dma_req1_dma_ack;
wire hps_0_f2h_dma_req2_dma_req;
wire hps_0_f2h_dma_req2_dma_single;
wire hps_0_f2h_dma_req2_dma_ack;
wire hps_0_f2h_dma_req3_dma_req;
wire hps_0_f2h_dma_req3_dma_single;
wire hps_0_f2h_dma_req3_dma_ack;

wire clk_48, clk_44;
//=======================================================
//  Structural coding
//=======================================================

vga_pll  vga_pll_inst(
        .refclk(CLOCK_50),   //  refclk.clk
        .rst(1'b0),      //   reset.reset
        .outclk_0(clk_vip), // 100MHz
        .outclk_1(DRAM_CLK), // 100Mhz + phase shift
        .outclk_2(MIPI_REFCLK), // 20MHz
        .outclk_3(clk_disp), // 33MHz
        .locked()    //  locked.export
);

audio_pll audio_pll_inst(
        .refclk(CLOCK_50),  //  refclk.clk
        .rst(1'b0),         //   reset.reset
        .outclk_0(clk_48),  // outclk0.clk
        .outclk_1(clk_44),  // outclk1.clk
        .locked()           //  locked.export
);

soc_system u0 (
        .clk_clk                               (CLOCK_50),              //                            clk.clk
        .reset_reset_n                         (1'b1),                  //                          reset.reset_n
       //HPS ddr3
        .memory_mem_a                          (HPS_DDR3_ADDR),         //                         memory.mem_a
        .memory_mem_ba                         (HPS_DDR3_BA),           //                               .mem_ba
        .memory_mem_ck                         (HPS_DDR3_CK_P),         //                               .mem_ck
        .memory_mem_ck_n                       (HPS_DDR3_CK_N),         //                               .mem_ck_n
        .memory_mem_cke                        (HPS_DDR3_CKE),          //                               .mem_cke
        .memory_mem_cs_n                       (HPS_DDR3_CS_N),         //                               .mem_cs_n
        .memory_mem_ras_n                      (HPS_DDR3_RAS_N),        //                               .mem_ras_n
        .memory_mem_cas_n                      (HPS_DDR3_CAS_N),        //                               .mem_cas_n
        .memory_mem_we_n                       (HPS_DDR3_WE_N),         //                               .mem_we_n
        .memory_mem_reset_n                    (HPS_DDR3_RESET_N),      //                               .mem_reset_n
        .memory_mem_dq                         (HPS_DDR3_DQ),           //                               .mem_dq
        .memory_mem_dqs                        (HPS_DDR3_DQS_P),        //                               .mem_dqs
        .memory_mem_dqs_n                      (HPS_DDR3_DQS_N),        //                               .mem_dqs_n
        .memory_mem_odt                        (HPS_DDR3_ODT),          //                               .mem_odt
        .memory_mem_dm                         (HPS_DDR3_DM),           //                               .mem_dm
        .memory_oct_rzqin                      (HPS_DDR3_RZQ),          //                               .oct_rzqin
       //HPS ethernet
        .hps_0_hps_io_hps_io_emac1_inst_TX_CLK (HPS_ENET_GTX_CLK),      //                   hps_0_hps_io.hps_io_emac1_inst_TX_CLK
        .hps_0_hps_io_hps_io_emac1_inst_TXD0   (HPS_ENET_TX_DATA[0]),   //                               .hps_io_emac1_inst_TXD0
        .hps_0_hps_io_hps_io_emac1_inst_TXD1   (HPS_ENET_TX_DATA[1]),   //                               .hps_io_emac1_inst_TXD1
        .hps_0_hps_io_hps_io_emac1_inst_TXD2   (HPS_ENET_TX_DATA[2]),   //                               .hps_io_emac1_inst_TXD2
        .hps_0_hps_io_hps_io_emac1_inst_TXD3   (HPS_ENET_TX_DATA[3]),   //                               .hps_io_emac1_inst_TXD3
        .hps_0_hps_io_hps_io_emac1_inst_RXD0   (HPS_ENET_RX_DATA[0]),   //                               .hps_io_emac1_inst_RXD0
        .hps_0_hps_io_hps_io_emac1_inst_MDIO   (HPS_ENET_MDIO),         //                               .hps_io_emac1_inst_MDIO
        .hps_0_hps_io_hps_io_emac1_inst_MDC    (HPS_ENET_MDC),          //                               .hps_io_emac1_inst_MDC
        .hps_0_hps_io_hps_io_emac1_inst_RX_CTL (HPS_ENET_RX_DV),        //                               .hps_io_emac1_inst_RX_CTL
        .hps_0_hps_io_hps_io_emac1_inst_TX_CTL (HPS_ENET_TX_EN),        //                               .hps_io_emac1_inst_TX_CTL
        .hps_0_hps_io_hps_io_emac1_inst_RX_CLK (HPS_ENET_RX_CLK),       //                               .hps_io_emac1_inst_RX_CLK
        .hps_0_hps_io_hps_io_emac1_inst_RXD1   (HPS_ENET_RX_DATA[1]),   //                               .hps_io_emac1_inst_RXD1
        .hps_0_hps_io_hps_io_emac1_inst_RXD2   (HPS_ENET_RX_DATA[2]),   //                               .hps_io_emac1_inst_RXD2
        .hps_0_hps_io_hps_io_emac1_inst_RXD3   (HPS_ENET_RX_DATA[3]),   //                               .hps_io_emac1_inst_RXD3
       //HPS QSPI
        .hps_0_hps_io_hps_io_qspi_inst_IO0     (HPS_FLASH_DATA[0]),     //                               .hps_io_qspi_inst_IO0
        .hps_0_hps_io_hps_io_qspi_inst_IO1     (HPS_FLASH_DATA[1]),     //                               .hps_io_qspi_inst_IO1
        .hps_0_hps_io_hps_io_qspi_inst_IO2     (HPS_FLASH_DATA[2]),     //                               .hps_io_qspi_inst_IO2
        .hps_0_hps_io_hps_io_qspi_inst_IO3     (HPS_FLASH_DATA[3]),     //                               .hps_io_qspi_inst_IO3
        .hps_0_hps_io_hps_io_qspi_inst_SS0     (HPS_FLASH_NCSO),        //                               .hps_io_qspi_inst_SS0
        .hps_0_hps_io_hps_io_qspi_inst_CLK     (HPS_FLASH_DCLK),        //                               .hps_io_qspi_inst_CLK
       //HPS SD card
        .hps_0_hps_io_hps_io_sdio_inst_CMD     (HPS_SD_CMD),            //                               .hps_io_sdio_inst_CMD
        .hps_0_hps_io_hps_io_sdio_inst_D0      (HPS_SD_DATA[0]),        //                               .hps_io_sdio_inst_D0
        .hps_0_hps_io_hps_io_sdio_inst_D1      (HPS_SD_DATA[1]),        //                               .hps_io_sdio_inst_D1
        .hps_0_hps_io_hps_io_sdio_inst_CLK     (HPS_SD_CLK),            //                               .hps_io_sdio_inst_CLK
        .hps_0_hps_io_hps_io_sdio_inst_D2      (HPS_SD_DATA[2]),        //                               .hps_io_sdio_inst_D2
        .hps_0_hps_io_hps_io_sdio_inst_D3      (HPS_SD_DATA[3]),        //                               .hps_io_sdio_inst_D3
       //HPS USB
        .hps_0_hps_io_hps_io_usb1_inst_D0      (HPS_USB_DATA[0]),       //                               .hps_io_usb1_inst_D0
        .hps_0_hps_io_hps_io_usb1_inst_D1      (HPS_USB_DATA[1]),       //                               .hps_io_usb1_inst_D1
        .hps_0_hps_io_hps_io_usb1_inst_D2      (HPS_USB_DATA[2]),       //                               .hps_io_usb1_inst_D2
        .hps_0_hps_io_hps_io_usb1_inst_D3      (HPS_USB_DATA[3]),       //                               .hps_io_usb1_inst_D3
        .hps_0_hps_io_hps_io_usb1_inst_D4      (HPS_USB_DATA[4]),       //                               .hps_io_usb1_inst_D4
        .hps_0_hps_io_hps_io_usb1_inst_D5      (HPS_USB_DATA[5]),       //                               .hps_io_usb1_inst_D5
        .hps_0_hps_io_hps_io_usb1_inst_D6      (HPS_USB_DATA[6]),       //                               .hps_io_usb1_inst_D6
        .hps_0_hps_io_hps_io_usb1_inst_D7      (HPS_USB_DATA[7]),       //                               .hps_io_usb1_inst_D7
        .hps_0_hps_io_hps_io_usb1_inst_CLK     (HPS_USB_CLKOUT),        //                               .hps_io_usb1_inst_CLK
        .hps_0_hps_io_hps_io_usb1_inst_STP     (HPS_USB_STP),           //                               .hps_io_usb1_inst_STP
        .hps_0_hps_io_hps_io_usb1_inst_DIR     (HPS_USB_DIR),           //                               .hps_io_usb1_inst_DIR
        .hps_0_hps_io_hps_io_usb1_inst_NXT     (HPS_USB_NXT),           //                               .hps_io_usb1_inst_NXT
       //HPS LCD
        .hps_0_hps_io_hps_io_spim0_inst_CLK    (HPS_LCM_SPIM_CLK),      //                               .hps_io_spim0_inst_CLK
        .hps_0_hps_io_hps_io_spim0_inst_MOSI   (HPS_LCM_SPIM_MOSI),     //                               .hps_io_spim0_inst_MOSI
        .hps_0_hps_io_hps_io_spim0_inst_MISO   (HPS_LCM_SPIM_MISO),     //                               .hps_io_spim0_inst_MISO
        .hps_0_hps_io_hps_io_spim0_inst_SS0    (HPS_LCM_SPIM_SS),       //                               .hps_io_spim0_inst_SS0
       //HPS SPI
        .hps_0_hps_io_hps_io_spim1_inst_CLK    (HPS_SPIM_CLK),          //                               .hps_io_spim1_inst_CLK
        .hps_0_hps_io_hps_io_spim1_inst_MOSI   (HPS_SPIM_MOSI),         //                               .hps_io_spim1_inst_MOSI
        .hps_0_hps_io_hps_io_spim1_inst_MISO   (HPS_SPIM_MISO),         //                               .hps_io_spim1_inst_MISO
        .hps_0_hps_io_hps_io_spim1_inst_SS0    (HPS_SPIM_SS),           //                               .hps_io_spim1_inst_SS0
       //HPS UART
        .hps_0_hps_io_hps_io_uart0_inst_RX     (HPS_UART_RX),           //                               .hps_io_uart0_inst_RX
        .hps_0_hps_io_hps_io_uart0_inst_TX     (HPS_UART_TX),           //                               .hps_io_uart0_inst_TX
       //HPS I2C1
        .hps_0_hps_io_hps_io_i2c0_inst_SDA     (HPS_I2C1_SDAT),         //                               .hps_io_i2c0_inst_SDA
        .hps_0_hps_io_hps_io_i2c0_inst_SCL     (HPS_I2C1_SCLK),         //                               .hps_io_i2c0_inst_SCL
       //HPS I2C2
        .hps_0_hps_io_hps_io_i2c1_inst_SDA     (HPS_I2C2_SDAT),         //                               .hps_io_i2c1_inst_SDA
        .hps_0_hps_io_hps_io_i2c1_inst_SCL     (HPS_I2C2_SCLK),         //                               .hps_io_i2c1_inst_SCL
       //HPS GPIO
        .hps_0_hps_io_hps_io_gpio_inst_GPIO09  (HPS_CONV_USB_N),        //                               .hps_io_gpio_inst_GPIO09
        .hps_0_hps_io_hps_io_gpio_inst_GPIO35  (HPS_ENET_INT_N),        //                               .hps_io_gpio_inst_GPIO35
        .hps_0_hps_io_hps_io_gpio_inst_GPIO37  (HPS_LCM_BK),            //                               .hps_io_gpio_inst_GPIO37
        .hps_0_hps_io_hps_io_gpio_inst_GPIO40  (HPS_LTC_GPIO),          //                               .hps_io_gpio_inst_GPIO40
        .hps_0_hps_io_hps_io_gpio_inst_GPIO41  (HPS_LCM_D_C),           //                               .hps_io_gpio_inst_GPIO41
        .hps_0_hps_io_hps_io_gpio_inst_GPIO44  (HPS_LCM_RST_N),         //                               .hps_io_gpio_inst_GPIO44
        .hps_0_hps_io_hps_io_gpio_inst_GPIO48  (HPS_I2C_CONTROL),       //                               .hps_io_gpio_inst_GPIO48
        .hps_0_hps_io_hps_io_gpio_inst_GPIO53  (HPS_LED),               //                               .hps_io_gpio_inst_GPIO53
        .hps_0_hps_io_hps_io_gpio_inst_GPIO54  (HPS_KEY),               //                               .hps_io_gpio_inst_GPIO54
        .hps_0_hps_io_hps_io_gpio_inst_GPIO61  (HPS_GSENSOR_INT),       //                               .hps_io_gpio_inst_GPIO61
       //HPS reset output
        .hps_0_h2f_reset_reset_n               (hps_fpga_reset_n),      //                hps_0_h2f_reset.reset_n
        .hps_0_f2h_cold_reset_req_reset_n      (~hps_cold_reset),       //       hps_0_f2h_cold_reset_req.reset_n
        .hps_0_f2h_debug_reset_req_reset_n     (~hps_debug_reset),      //      hps_0_f2h_debug_reset_req.reset_n
        .hps_0_f2h_stm_hw_events_stm_hwevents  (stm_hw_events),         //        hps_0_f2h_stm_hw_events.stm_hwevents
        .hps_0_f2h_warm_reset_req_reset_n      (~hps_warm_reset),       //       hps_0_f2h_warm_reset_req.reset_n
       //itc
        .alt_vip_itc_0_clocked_video_vid_clk        (clk_disp),                     // alt_vip_itc_0_clocked_video.vid_clk
        .alt_vip_itc_0_clocked_video_vid_data       ({vid_r,vid_g,vid_b}),          //                            .vid_data
        .alt_vip_itc_0_clocked_video_underflow      (),                             //                            .underflow
        .alt_vip_itc_0_clocked_video_vid_datavalid  (vid_datavalid),                //                            .vid_datavalid
        .alt_vip_itc_0_clocked_video_vid_v_sync     (vid_v_sync),                   //                            .vid_v_sync
        .alt_vip_itc_0_clocked_video_vid_h_sync     (vid_h_sync),                   //                            .vid_h_sync
        .alt_vip_itc_0_clocked_video_vid_f          (),                             //                            .vid_f
        .alt_vip_itc_0_clocked_video_vid_h          (),                             //                            .vid_h
        .alt_vip_itc_0_clocked_video_vid_v          (),                             //                            .vid_v
        .vga_stream_clk                             (clk_vip),                      //                  vga_stream.clk

        //FPGA
       //pio
        .key_external_connection_export             (fpga_debounced_buttons),       //                key_external_connection.export
        .ledr_external_connection_export            (fpga_led_internal),            //               ledr_external_connection.export
        .sw_external_connection_export              (SW),                           //                 sw_external_connection.export
       //7-seg display
        .seg7_conduit_end_writedata                 ({HEX5P,HEX5,HEX4P,HEX4,
                                                      HEX3P,HEX3,HEX2P,HEX2,
                                                      HEX1P,HEX1,HEX0P,HEX0}),      //                       seg7_conduit_end.writedata
       //ir
        .ir_rx_conduit_end_export                   (IRDA_RXD),                     //                      ir_rx_conduit_end.export

       //tv decoder video input
        .tv_decoder_alt_vip_cl_cvi_0_clocked_video_vid_clk              (TD_CLK27), // tv_decoder_alt_vip_cl_cvi_0_clocked_video.vid_clk
        .tv_decoder_alt_vip_cl_cvi_0_clocked_video_vid_data             (TD_DATA),  //                                          .vid_data
        .tv_decoder_alt_vip_cl_cvi_0_clocked_video_vid_de               (1'b1),     //                                          .vid_de
        .tv_decoder_alt_vip_cl_cvi_0_clocked_video_vid_datavalid        (1'b1),     //                                          .vid_datavalid
        .tv_decoder_alt_vip_cl_cvi_0_clocked_video_vid_locked           (1'b1),     //                                          .vid_locked
        .tv_decoder_alt_vip_cl_cvi_0_clocked_video_vid_f                (),         //                                          .vid_f
        .tv_decoder_alt_vip_cl_cvi_0_clocked_video_vid_v_sync           (),         //                                          .vid_v_sync
        .tv_decoder_alt_vip_cl_cvi_0_clocked_video_vid_h_sync           (),         //                                          .vid_h_sync
        .tv_decoder_alt_vip_cl_cvi_0_clocked_video_vid_color_encoding   (),         //                                          .vid_color_encoding
        .tv_decoder_alt_vip_cl_cvi_0_clocked_video_vid_bit_width        (),         //                                          .vid_bit_width
        .tv_decoder_alt_vip_cl_cvi_0_clocked_video_sof                  (),         //                                          .sof
        .tv_decoder_alt_vip_cl_cvi_0_clocked_video_sof_locked           (),         //                                          .sof_locked
        .tv_decoder_alt_vip_cl_cvi_0_clocked_video_refclk_div           (),         //                                          .refclk_div
        .tv_decoder_alt_vip_cl_cvi_0_clocked_video_clipping             (),         //                                          .clipping
        .tv_decoder_alt_vip_cl_cvi_0_clocked_video_padding              (),         //                                          .padding
        .tv_decoder_alt_vip_cl_cvi_0_clocked_video_overflow             (),         //                                          .overflow


       //sdram
        .tv_decoder_sdram_wire_addr     (DRAM_ADDR),                //                  tv_decoder_sdram_wire.addr
        .tv_decoder_sdram_wire_ba       (DRAM_BA),                  //                                       .ba
        .tv_decoder_sdram_wire_cas_n    (DRAM_CAS_N),               //                                       .cas_n
        .tv_decoder_sdram_wire_cke      (DRAM_CKE),                 //                                       .cke
        .tv_decoder_sdram_wire_cs_n     (DRAM_CS_N),                //                                       .cs_n
        .tv_decoder_sdram_wire_dq       (DRAM_DQ),                  //                                       .dq
        .tv_decoder_sdram_wire_dqm      ({DRAM_UDQM,DRAM_LDQM}),    //                                       .dqm
        .tv_decoder_sdram_wire_ras_n    (DRAM_RAS_N),               //                                       .ras_n
        .tv_decoder_sdram_wire_we_n     (DRAM_WE_N),                //                                       .we_n

       //touch screen
        .ts_i2c_export_scl_pad_io                   (TOUCH_I2C_SCL),    //                    ts_i2c_export.scl_pad_io
        .ts_i2c_export_sda_pad_io                   (TOUCH_I2C_SDA),    //                                 .sda_pad_io
        .ts_interrupt_external_connection_export    (TOUCH_INT_n),      // ts_interrupt_external_connection.export

       //camera
        .tv_decoder_camera_conduit_end_camera_d         ({MIPI_PIXEL_D[9:0],2'b00}),               //     terasic_camera_0_conduit_end.D
        .tv_decoder_camera_conduit_end_camera_fval      (MIPI_PIXEL_VS),            //                                 .FVAL
        .tv_decoder_camera_conduit_end_camera_lval      (MIPI_PIXEL_HS),            //                                 .LVAL
        .tv_decoder_camera_conduit_end_camera_pixclk    (~MIPI_PIXEL_CLK),          //                                 .PIXCLK

        .i2c_opencores_camera_export_scl_pad_io     (CAMERA_I2C_SCL),   //      i2c_opencores_camera_export.scl_pad_io
        .i2c_opencores_camera_export_sda_pad_io     (CAMERA_I2C_SDA),   //                                 .sda_pad_io
        .camera_pwdn_n_external_connection_export   (CAMERA_PWDN_n),    //  mipi_pwdn_n_external_connection.export

       //mipi
        .i2c_opencores_mipi_export_scl_pad_io       (MIPI_I2C_SCL),     //        i2c_opencores_mipi_export.scl_pad_io
        .i2c_opencores_mipi_export_sda_pad_io       (MIPI_I2C_SDA),     //                                 .sda_pad_io
        .mipi_reset_n_external_connection_export    (MIPI_RESET_n),     // mipi_reset_n_external_connection.export

       //light sensor
        .i2c_opencores_light_export_scl_pad_io      (LSENSOR_SCL),      //                i2c_opencores_light_export.scl_pad_io
        .i2c_opencores_light_export_sda_pad_io      (LSENSOR_SDA),      //                                          .sda_pad_io
        .light_int_external_connection_export       (LSENSOR_INT),      //             light_int_external_connection.export

       //9-axis sensor
        .spi_mpu_external_MISO                      (MPU_AD0_SDO),      //                          spi_mpu_external.MISO
        .spi_mpu_external_MOSI                      (MPU_SDA_SDI),      //                                          .MOSI
        .spi_mpu_external_SCLK                      (MPU_SCL_SCLK),     //                                          .SCLK
        .spi_mpu_external_SS_n                      (MPU_CS_n),         //                                          .SS_n
        .mpu_int_external_connection_export         (MPU_INT),          //               mpu_int_external_connection.export

       //ALSA
        .terasic_alsa_dma_conduit_end_capture_dma_ack  (hps_0_f2h_dma_req1_dma_ack),    //  terasic_alsa_dma_conduit_end.capture_dma_ack
        .terasic_alsa_dma_conduit_end_capture_dma_req  (hps_0_f2h_dma_req1_dma_single), //                              .capture_dma_req
        .terasic_alsa_dma_conduit_end_playback_dma_ack (hps_0_f2h_dma_req0_dma_ack),    //                              .playback_dma_ack
        .terasic_alsa_dma_conduit_end_playback_dma_req (hps_0_f2h_dma_req0_dma_single), //                              .playback_dma_req
        .terasic_alsa_chip_conduit_end_xck             (AUD_XCK),                       // terasic_alsa_chip_conduit_end.xck
        .terasic_alsa_chip_conduit_end_adclrck         (AUD_ADCLRCK),                   //                              .adclrck
        .terasic_alsa_chip_conduit_end_adcdat          (AUD_ADCDAT),                    //                              .adcdat
        .terasic_alsa_chip_conduit_end_bclk            (AUD_BCLK),                      //                              .bclk
        .terasic_alsa_chip_conduit_end_dacdat          (AUD_DACDAT),                    //                              .dacdat
        .terasic_alsa_chip_conduit_end_daclrck         (AUD_DACLRCK),                   //                              .daclrck
        .hps_0_f2h_dma_req0_dma_req         (hps_0_f2h_dma_req0_dma_req),               //            hps_0_f2h_dma_req0.dma_req
        .hps_0_f2h_dma_req0_dma_single      (hps_0_f2h_dma_req0_dma_single),            //                              .dma_single
        .hps_0_f2h_dma_req0_dma_ack         (hps_0_f2h_dma_req0_dma_ack),               //                              .dma_ack
        .hps_0_f2h_dma_req1_dma_req         (hps_0_f2h_dma_req1_dma_req),               //            hps_0_f2h_dma_req1.dma_req
        .hps_0_f2h_dma_req1_dma_single      (hps_0_f2h_dma_req1_dma_single),            //                              .dma_single
        .hps_0_f2h_dma_req1_dma_ack         (hps_0_f2h_dma_req1_dma_ack),               //                              .dma_ack
        .terasic_alsa_clock_sink_44_clk     (clk_44),                                   //    terasic_alsa_clock_sink_44.clk
        .terasic_alsa_clock_sink_48_clk     (clk_48)                                    //    terasic_alsa_clock_sink_48.clk


);


////////////////////////////////////////////////////////
// mipi camera config
////assign MIPI_WP      = 1'b0;
assign MIPI_CS_n    = 1'b0;

////////////////////////////////////////////////////////
// MTLC2's Sensors
// mtlc2: light sensor
assign LSENSOR_ADDR_SEL = 1'b0;


////////////////////////////////////////////////////////
// VGA & MTLC2's LCD

// vga
assign VGA_BLANK_N = 1'b1;
assign VGA_SYNC_N = 1'b0;
assign VGA_CLK = clk_disp;
assign {VGA_B,VGA_G,VGA_R} = {vid_b,vid_g,vid_r};
assign VGA_VS = vid_v_sync;
assign VGA_HS = vid_h_sync;

// mtlc2 lcd
assign LCD_DCLK = clk_disp;
assign {LCD_B,LCD_G,LCD_R} = {vid_b,vid_g,vid_r};
assign LCD_VSD = ~vid_v_sync;
assign LCD_HSD = ~vid_h_sync;
assign LCD_DE = vid_datavalid;



assign LCD_MODE = 1'b0;  //HSD/VSD mode
assign LCD_RSTB = 1'b1; //NO RESET
assign LCD_DIM  = 1'b1;
assign LCD_POWER_CTL = 1'b1;
assign LCD_SHLR         = 1'b1;
assign LCD_UPDN         = 1'b0;
// assign LCD_DITH

////////////////////////////////////////////////////////
//	Audio CODEC and video decoder setting
I2C_AV_Config 	AV_CONFIG	(	//	Host Side
						.iCLK(CLOCK_50),
						.iRST_N(1'b1),
						//	I2C Side
						.I2C_SCLK(FPGA_I2C_SCLK),
						.I2C_SDAT(FPGA_I2C_SDAT)	);

assign TD_RESET_N = 1'b1;


////////////////////////////////////////////////////////
// Debounce logic to clean out glitches within 1ms
debounce debounce_inst (
        .clk                                  (fpga_clk_50),
        .reset_n                              (hps_fpga_reset_n),
        .data_in                              (KEY),
        .data_out                             (fpga_debounced_buttons)
);
defparam debounce_inst.WIDTH = 4;
defparam debounce_inst.POLARITY = "LOW";
defparam debounce_inst.TIMEOUT = 50000;               // at 50Mhz this is a debounce time of 1ms
defparam debounce_inst.TIMEOUT_WIDTH = 16;            // ceil(log2(TIMEOUT))

// Source/Probe megawizard instance
hps_reset hps_reset_inst (
        .source_clk (fpga_clk_50),
        .source     (hps_reset_req)
);

altera_edge_detector pulse_cold_reset (
        .clk       (fpga_clk_50),
        .rst_n     (hps_fpga_reset_n),
        .signal_in (hps_reset_req[0]),
        .pulse_out (hps_cold_reset)
);
defparam pulse_cold_reset.PULSE_EXT = 6;
defparam pulse_cold_reset.EDGE_TYPE = 1;
defparam pulse_cold_reset.IGNORE_RST_WHILE_BUSY = 1;

altera_edge_detector pulse_warm_reset (
        .clk       (fpga_clk_50),
        .rst_n     (hps_fpga_reset_n),
        .signal_in (hps_reset_req[1]),
        .pulse_out (hps_warm_reset)
);
defparam pulse_warm_reset.PULSE_EXT = 2;
defparam pulse_warm_reset.EDGE_TYPE = 1;
defparam pulse_warm_reset.IGNORE_RST_WHILE_BUSY = 1;

altera_edge_detector pulse_debug_reset (
        .clk       (fpga_clk_50),
        .rst_n     (hps_fpga_reset_n),
        .signal_in (hps_reset_req[2]),
        .pulse_out (hps_debug_reset)
);
defparam pulse_debug_reset.PULSE_EXT = 32;
defparam pulse_debug_reset.EDGE_TYPE = 1;
defparam pulse_debug_reset.IGNORE_RST_WHILE_BUSY = 1;

reg [25:0] counter;
reg  led_level;
always @(posedge fpga_clk_50 or negedge hps_fpga_reset_n)
begin
    if(~hps_fpga_reset_n)
    begin
        counter<=0;
        led_level<=0;
    end

    else if(counter==24999999)
    begin
        counter<=0;
        led_level<=~led_level;
    end
    else
        counter<=counter+1'b1;
end

assign LEDR[0]=led_level | fpga_led_internal[0];
//assign LEDR[9:1] = qsys_led[9:1];
endmodule

