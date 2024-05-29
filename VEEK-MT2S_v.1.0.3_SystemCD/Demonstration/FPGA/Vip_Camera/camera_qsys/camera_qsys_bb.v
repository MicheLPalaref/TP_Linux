
module camera_qsys (
	alt_vip_cl_cvo_0_clocked_video_vid_clk,
	alt_vip_cl_cvo_0_clocked_video_vid_data,
	alt_vip_cl_cvo_0_clocked_video_underflow,
	alt_vip_cl_cvo_0_clocked_video_vid_datavalid,
	alt_vip_cl_cvo_0_clocked_video_vid_v_sync,
	alt_vip_cl_cvo_0_clocked_video_vid_h_sync,
	alt_vip_cl_cvo_0_clocked_video_vid_f,
	alt_vip_cl_cvo_0_clocked_video_vid_h,
	alt_vip_cl_cvo_0_clocked_video_vid_v,
	camera_pwdn_n_external_connection_export,
	clk_50_clk,
	clk_sdram_clk,
	clk_vga_clk,
	d8m_xclkin_clk,
	i2c_opencores_camera_export_scl_pad_io,
	i2c_opencores_camera_export_sda_pad_io,
	i2c_opencores_mipi_export_scl_pad_io,
	i2c_opencores_mipi_export_sda_pad_io,
	i2c_opencores_touch_export_scl_pad_io,
	i2c_opencores_touch_export_sda_pad_io,
	key_external_connection_export,
	led_external_connection_export,
	mipi_reset_n_external_connection_export,
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
	sw_external_connection_export,
	terasic_auto_focus_0_conduit_vcm_i2c_sda,
	terasic_auto_focus_0_conduit_clk50,
	terasic_auto_focus_0_conduit_vcm_i2c_scl,
	terasic_camera_conduit_end_camera_d,
	terasic_camera_conduit_end_camera_fval,
	terasic_camera_conduit_end_camera_lval,
	terasic_camera_conduit_end_camera_pixclk,
	touch_int_n_external_connection_export);	

	input		alt_vip_cl_cvo_0_clocked_video_vid_clk;
	output	[23:0]	alt_vip_cl_cvo_0_clocked_video_vid_data;
	output		alt_vip_cl_cvo_0_clocked_video_underflow;
	output		alt_vip_cl_cvo_0_clocked_video_vid_datavalid;
	output		alt_vip_cl_cvo_0_clocked_video_vid_v_sync;
	output		alt_vip_cl_cvo_0_clocked_video_vid_h_sync;
	output		alt_vip_cl_cvo_0_clocked_video_vid_f;
	output		alt_vip_cl_cvo_0_clocked_video_vid_h;
	output		alt_vip_cl_cvo_0_clocked_video_vid_v;
	output		camera_pwdn_n_external_connection_export;
	input		clk_50_clk;
	output		clk_sdram_clk;
	output		clk_vga_clk;
	output		d8m_xclkin_clk;
	inout		i2c_opencores_camera_export_scl_pad_io;
	inout		i2c_opencores_camera_export_sda_pad_io;
	inout		i2c_opencores_mipi_export_scl_pad_io;
	inout		i2c_opencores_mipi_export_sda_pad_io;
	inout		i2c_opencores_touch_export_scl_pad_io;
	inout		i2c_opencores_touch_export_sda_pad_io;
	input	[3:0]	key_external_connection_export;
	output	[9:0]	led_external_connection_export;
	output		mipi_reset_n_external_connection_export;
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
	input	[9:0]	sw_external_connection_export;
	inout		terasic_auto_focus_0_conduit_vcm_i2c_sda;
	input		terasic_auto_focus_0_conduit_clk50;
	inout		terasic_auto_focus_0_conduit_vcm_i2c_scl;
	input	[11:0]	terasic_camera_conduit_end_camera_d;
	input		terasic_camera_conduit_end_camera_fval;
	input		terasic_camera_conduit_end_camera_lval;
	input		terasic_camera_conduit_end_camera_pixclk;
	input		touch_int_n_external_connection_export;
endmodule
