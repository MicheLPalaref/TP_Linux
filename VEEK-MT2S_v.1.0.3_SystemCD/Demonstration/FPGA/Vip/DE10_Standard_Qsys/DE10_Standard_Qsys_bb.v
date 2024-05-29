
module DE10_Standard_Qsys (
	alt_vip_cl_cvi_0_clocked_video_vid_clk,
	alt_vip_cl_cvi_0_clocked_video_vid_data,
	alt_vip_cl_cvi_0_clocked_video_vid_de,
	alt_vip_cl_cvi_0_clocked_video_vid_datavalid,
	alt_vip_cl_cvi_0_clocked_video_vid_locked,
	alt_vip_cl_cvi_0_clocked_video_vid_f,
	alt_vip_cl_cvi_0_clocked_video_vid_v_sync,
	alt_vip_cl_cvi_0_clocked_video_vid_h_sync,
	alt_vip_cl_cvi_0_clocked_video_vid_color_encoding,
	alt_vip_cl_cvi_0_clocked_video_vid_bit_width,
	alt_vip_cl_cvi_0_clocked_video_sof,
	alt_vip_cl_cvi_0_clocked_video_sof_locked,
	alt_vip_cl_cvi_0_clocked_video_refclk_div,
	alt_vip_cl_cvi_0_clocked_video_clipping,
	alt_vip_cl_cvi_0_clocked_video_padding,
	alt_vip_cl_cvi_0_clocked_video_overflow,
	alt_vip_itc_mtlc_clocked_video_vid_clk,
	alt_vip_itc_mtlc_clocked_video_vid_data,
	alt_vip_itc_mtlc_clocked_video_underflow,
	alt_vip_itc_mtlc_clocked_video_vid_datavalid,
	alt_vip_itc_mtlc_clocked_video_vid_v_sync,
	alt_vip_itc_mtlc_clocked_video_vid_h_sync,
	alt_vip_itc_mtlc_clocked_video_vid_f,
	alt_vip_itc_mtlc_clocked_video_vid_h,
	alt_vip_itc_mtlc_clocked_video_vid_v,
	audio_avalon_controller_conduit_end_CLK,
	audio_avalon_controller_conduit_end_LRCIN,
	audio_avalon_controller_conduit_end_DIN,
	audio_avalon_controller_conduit_end_LRCOUT,
	audio_avalon_controller_conduit_end_DOUT,
	audio_avalon_controller_conduit_end_BCLK,
	av_i2c_clk_pio_external_connection_export,
	av_i2c_data_pio_external_connection_export,
	button_pio_external_connection_export,
	clk_clk,
	clk_mtlc_clk,
	clk_sdram_clk,
	clk_sys_clk,
	led_pio_external_connection_export,
	pll_0_locked_export,
	reset_reset_n,
	sdram_wire_addr,
	sdram_wire_ba,
	sdram_wire_cas_n,
	sdram_wire_cke,
	sdram_wire_cs_n,
	sdram_wire_dq,
	sdram_wire_dqm,
	sdram_wire_ras_n,
	sdram_wire_we_n,
	td_reset_pio_external_connection_export,
	touch_i2c_opencores_export_scl_pad_io,
	touch_i2c_opencores_export_sda_pad_io,
	touch_int_n_external_connection_export);	

	input		alt_vip_cl_cvi_0_clocked_video_vid_clk;
	input	[7:0]	alt_vip_cl_cvi_0_clocked_video_vid_data;
	input		alt_vip_cl_cvi_0_clocked_video_vid_de;
	input		alt_vip_cl_cvi_0_clocked_video_vid_datavalid;
	input		alt_vip_cl_cvi_0_clocked_video_vid_locked;
	input		alt_vip_cl_cvi_0_clocked_video_vid_f;
	input		alt_vip_cl_cvi_0_clocked_video_vid_v_sync;
	input		alt_vip_cl_cvi_0_clocked_video_vid_h_sync;
	input	[7:0]	alt_vip_cl_cvi_0_clocked_video_vid_color_encoding;
	input	[7:0]	alt_vip_cl_cvi_0_clocked_video_vid_bit_width;
	output		alt_vip_cl_cvi_0_clocked_video_sof;
	output		alt_vip_cl_cvi_0_clocked_video_sof_locked;
	output		alt_vip_cl_cvi_0_clocked_video_refclk_div;
	output		alt_vip_cl_cvi_0_clocked_video_clipping;
	output		alt_vip_cl_cvi_0_clocked_video_padding;
	output		alt_vip_cl_cvi_0_clocked_video_overflow;
	input		alt_vip_itc_mtlc_clocked_video_vid_clk;
	output	[23:0]	alt_vip_itc_mtlc_clocked_video_vid_data;
	output		alt_vip_itc_mtlc_clocked_video_underflow;
	output		alt_vip_itc_mtlc_clocked_video_vid_datavalid;
	output		alt_vip_itc_mtlc_clocked_video_vid_v_sync;
	output		alt_vip_itc_mtlc_clocked_video_vid_h_sync;
	output		alt_vip_itc_mtlc_clocked_video_vid_f;
	output		alt_vip_itc_mtlc_clocked_video_vid_h;
	output		alt_vip_itc_mtlc_clocked_video_vid_v;
	output		audio_avalon_controller_conduit_end_CLK;
	output		audio_avalon_controller_conduit_end_LRCIN;
	output		audio_avalon_controller_conduit_end_DIN;
	output		audio_avalon_controller_conduit_end_LRCOUT;
	input		audio_avalon_controller_conduit_end_DOUT;
	output		audio_avalon_controller_conduit_end_BCLK;
	output		av_i2c_clk_pio_external_connection_export;
	inout		av_i2c_data_pio_external_connection_export;
	input	[3:0]	button_pio_external_connection_export;
	input		clk_clk;
	output		clk_mtlc_clk;
	output		clk_sdram_clk;
	output		clk_sys_clk;
	output	[3:0]	led_pio_external_connection_export;
	output		pll_0_locked_export;
	input		reset_reset_n;
	output	[12:0]	sdram_wire_addr;
	output	[1:0]	sdram_wire_ba;
	output		sdram_wire_cas_n;
	output		sdram_wire_cke;
	output		sdram_wire_cs_n;
	inout	[15:0]	sdram_wire_dq;
	output	[1:0]	sdram_wire_dqm;
	output		sdram_wire_ras_n;
	output		sdram_wire_we_n;
	output		td_reset_pio_external_connection_export;
	inout		touch_i2c_opencores_export_scl_pad_io;
	inout		touch_i2c_opencores_export_sda_pad_io;
	input		touch_int_n_external_connection_export;
endmodule
