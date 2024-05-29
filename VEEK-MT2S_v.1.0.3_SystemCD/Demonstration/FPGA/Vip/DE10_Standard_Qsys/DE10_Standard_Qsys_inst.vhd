	component DE10_Standard_Qsys is
		port (
			alt_vip_cl_cvi_0_clocked_video_vid_clk            : in    std_logic                     := 'X';             -- vid_clk
			alt_vip_cl_cvi_0_clocked_video_vid_data           : in    std_logic_vector(7 downto 0)  := (others => 'X'); -- vid_data
			alt_vip_cl_cvi_0_clocked_video_vid_de             : in    std_logic                     := 'X';             -- vid_de
			alt_vip_cl_cvi_0_clocked_video_vid_datavalid      : in    std_logic                     := 'X';             -- vid_datavalid
			alt_vip_cl_cvi_0_clocked_video_vid_locked         : in    std_logic                     := 'X';             -- vid_locked
			alt_vip_cl_cvi_0_clocked_video_vid_f              : in    std_logic                     := 'X';             -- vid_f
			alt_vip_cl_cvi_0_clocked_video_vid_v_sync         : in    std_logic                     := 'X';             -- vid_v_sync
			alt_vip_cl_cvi_0_clocked_video_vid_h_sync         : in    std_logic                     := 'X';             -- vid_h_sync
			alt_vip_cl_cvi_0_clocked_video_vid_color_encoding : in    std_logic_vector(7 downto 0)  := (others => 'X'); -- vid_color_encoding
			alt_vip_cl_cvi_0_clocked_video_vid_bit_width      : in    std_logic_vector(7 downto 0)  := (others => 'X'); -- vid_bit_width
			alt_vip_cl_cvi_0_clocked_video_sof                : out   std_logic;                                        -- sof
			alt_vip_cl_cvi_0_clocked_video_sof_locked         : out   std_logic;                                        -- sof_locked
			alt_vip_cl_cvi_0_clocked_video_refclk_div         : out   std_logic;                                        -- refclk_div
			alt_vip_cl_cvi_0_clocked_video_clipping           : out   std_logic;                                        -- clipping
			alt_vip_cl_cvi_0_clocked_video_padding            : out   std_logic;                                        -- padding
			alt_vip_cl_cvi_0_clocked_video_overflow           : out   std_logic;                                        -- overflow
			alt_vip_itc_mtlc_clocked_video_vid_clk            : in    std_logic                     := 'X';             -- vid_clk
			alt_vip_itc_mtlc_clocked_video_vid_data           : out   std_logic_vector(23 downto 0);                    -- vid_data
			alt_vip_itc_mtlc_clocked_video_underflow          : out   std_logic;                                        -- underflow
			alt_vip_itc_mtlc_clocked_video_vid_datavalid      : out   std_logic;                                        -- vid_datavalid
			alt_vip_itc_mtlc_clocked_video_vid_v_sync         : out   std_logic;                                        -- vid_v_sync
			alt_vip_itc_mtlc_clocked_video_vid_h_sync         : out   std_logic;                                        -- vid_h_sync
			alt_vip_itc_mtlc_clocked_video_vid_f              : out   std_logic;                                        -- vid_f
			alt_vip_itc_mtlc_clocked_video_vid_h              : out   std_logic;                                        -- vid_h
			alt_vip_itc_mtlc_clocked_video_vid_v              : out   std_logic;                                        -- vid_v
			audio_avalon_controller_conduit_end_CLK           : out   std_logic;                                        -- CLK
			audio_avalon_controller_conduit_end_LRCIN         : out   std_logic;                                        -- LRCIN
			audio_avalon_controller_conduit_end_DIN           : out   std_logic;                                        -- DIN
			audio_avalon_controller_conduit_end_LRCOUT        : out   std_logic;                                        -- LRCOUT
			audio_avalon_controller_conduit_end_DOUT          : in    std_logic                     := 'X';             -- DOUT
			audio_avalon_controller_conduit_end_BCLK          : out   std_logic;                                        -- BCLK
			av_i2c_clk_pio_external_connection_export         : out   std_logic;                                        -- export
			av_i2c_data_pio_external_connection_export        : inout std_logic                     := 'X';             -- export
			button_pio_external_connection_export             : in    std_logic_vector(3 downto 0)  := (others => 'X'); -- export
			clk_clk                                           : in    std_logic                     := 'X';             -- clk
			clk_mtlc_clk                                      : out   std_logic;                                        -- clk
			clk_sdram_clk                                     : out   std_logic;                                        -- clk
			clk_sys_clk                                       : out   std_logic;                                        -- clk
			led_pio_external_connection_export                : out   std_logic_vector(3 downto 0);                     -- export
			pll_0_locked_export                               : out   std_logic;                                        -- export
			reset_reset_n                                     : in    std_logic                     := 'X';             -- reset_n
			sdram_wire_addr                                   : out   std_logic_vector(12 downto 0);                    -- addr
			sdram_wire_ba                                     : out   std_logic_vector(1 downto 0);                     -- ba
			sdram_wire_cas_n                                  : out   std_logic;                                        -- cas_n
			sdram_wire_cke                                    : out   std_logic;                                        -- cke
			sdram_wire_cs_n                                   : out   std_logic;                                        -- cs_n
			sdram_wire_dq                                     : inout std_logic_vector(15 downto 0) := (others => 'X'); -- dq
			sdram_wire_dqm                                    : out   std_logic_vector(1 downto 0);                     -- dqm
			sdram_wire_ras_n                                  : out   std_logic;                                        -- ras_n
			sdram_wire_we_n                                   : out   std_logic;                                        -- we_n
			td_reset_pio_external_connection_export           : out   std_logic;                                        -- export
			touch_i2c_opencores_export_scl_pad_io             : inout std_logic                     := 'X';             -- scl_pad_io
			touch_i2c_opencores_export_sda_pad_io             : inout std_logic                     := 'X';             -- sda_pad_io
			touch_int_n_external_connection_export            : in    std_logic                     := 'X'              -- export
		);
	end component DE10_Standard_Qsys;

	u0 : component DE10_Standard_Qsys
		port map (
			alt_vip_cl_cvi_0_clocked_video_vid_clk            => CONNECTED_TO_alt_vip_cl_cvi_0_clocked_video_vid_clk,            --      alt_vip_cl_cvi_0_clocked_video.vid_clk
			alt_vip_cl_cvi_0_clocked_video_vid_data           => CONNECTED_TO_alt_vip_cl_cvi_0_clocked_video_vid_data,           --                                    .vid_data
			alt_vip_cl_cvi_0_clocked_video_vid_de             => CONNECTED_TO_alt_vip_cl_cvi_0_clocked_video_vid_de,             --                                    .vid_de
			alt_vip_cl_cvi_0_clocked_video_vid_datavalid      => CONNECTED_TO_alt_vip_cl_cvi_0_clocked_video_vid_datavalid,      --                                    .vid_datavalid
			alt_vip_cl_cvi_0_clocked_video_vid_locked         => CONNECTED_TO_alt_vip_cl_cvi_0_clocked_video_vid_locked,         --                                    .vid_locked
			alt_vip_cl_cvi_0_clocked_video_vid_f              => CONNECTED_TO_alt_vip_cl_cvi_0_clocked_video_vid_f,              --                                    .vid_f
			alt_vip_cl_cvi_0_clocked_video_vid_v_sync         => CONNECTED_TO_alt_vip_cl_cvi_0_clocked_video_vid_v_sync,         --                                    .vid_v_sync
			alt_vip_cl_cvi_0_clocked_video_vid_h_sync         => CONNECTED_TO_alt_vip_cl_cvi_0_clocked_video_vid_h_sync,         --                                    .vid_h_sync
			alt_vip_cl_cvi_0_clocked_video_vid_color_encoding => CONNECTED_TO_alt_vip_cl_cvi_0_clocked_video_vid_color_encoding, --                                    .vid_color_encoding
			alt_vip_cl_cvi_0_clocked_video_vid_bit_width      => CONNECTED_TO_alt_vip_cl_cvi_0_clocked_video_vid_bit_width,      --                                    .vid_bit_width
			alt_vip_cl_cvi_0_clocked_video_sof                => CONNECTED_TO_alt_vip_cl_cvi_0_clocked_video_sof,                --                                    .sof
			alt_vip_cl_cvi_0_clocked_video_sof_locked         => CONNECTED_TO_alt_vip_cl_cvi_0_clocked_video_sof_locked,         --                                    .sof_locked
			alt_vip_cl_cvi_0_clocked_video_refclk_div         => CONNECTED_TO_alt_vip_cl_cvi_0_clocked_video_refclk_div,         --                                    .refclk_div
			alt_vip_cl_cvi_0_clocked_video_clipping           => CONNECTED_TO_alt_vip_cl_cvi_0_clocked_video_clipping,           --                                    .clipping
			alt_vip_cl_cvi_0_clocked_video_padding            => CONNECTED_TO_alt_vip_cl_cvi_0_clocked_video_padding,            --                                    .padding
			alt_vip_cl_cvi_0_clocked_video_overflow           => CONNECTED_TO_alt_vip_cl_cvi_0_clocked_video_overflow,           --                                    .overflow
			alt_vip_itc_mtlc_clocked_video_vid_clk            => CONNECTED_TO_alt_vip_itc_mtlc_clocked_video_vid_clk,            --      alt_vip_itc_mtlc_clocked_video.vid_clk
			alt_vip_itc_mtlc_clocked_video_vid_data           => CONNECTED_TO_alt_vip_itc_mtlc_clocked_video_vid_data,           --                                    .vid_data
			alt_vip_itc_mtlc_clocked_video_underflow          => CONNECTED_TO_alt_vip_itc_mtlc_clocked_video_underflow,          --                                    .underflow
			alt_vip_itc_mtlc_clocked_video_vid_datavalid      => CONNECTED_TO_alt_vip_itc_mtlc_clocked_video_vid_datavalid,      --                                    .vid_datavalid
			alt_vip_itc_mtlc_clocked_video_vid_v_sync         => CONNECTED_TO_alt_vip_itc_mtlc_clocked_video_vid_v_sync,         --                                    .vid_v_sync
			alt_vip_itc_mtlc_clocked_video_vid_h_sync         => CONNECTED_TO_alt_vip_itc_mtlc_clocked_video_vid_h_sync,         --                                    .vid_h_sync
			alt_vip_itc_mtlc_clocked_video_vid_f              => CONNECTED_TO_alt_vip_itc_mtlc_clocked_video_vid_f,              --                                    .vid_f
			alt_vip_itc_mtlc_clocked_video_vid_h              => CONNECTED_TO_alt_vip_itc_mtlc_clocked_video_vid_h,              --                                    .vid_h
			alt_vip_itc_mtlc_clocked_video_vid_v              => CONNECTED_TO_alt_vip_itc_mtlc_clocked_video_vid_v,              --                                    .vid_v
			audio_avalon_controller_conduit_end_CLK           => CONNECTED_TO_audio_avalon_controller_conduit_end_CLK,           -- audio_avalon_controller_conduit_end.CLK
			audio_avalon_controller_conduit_end_LRCIN         => CONNECTED_TO_audio_avalon_controller_conduit_end_LRCIN,         --                                    .LRCIN
			audio_avalon_controller_conduit_end_DIN           => CONNECTED_TO_audio_avalon_controller_conduit_end_DIN,           --                                    .DIN
			audio_avalon_controller_conduit_end_LRCOUT        => CONNECTED_TO_audio_avalon_controller_conduit_end_LRCOUT,        --                                    .LRCOUT
			audio_avalon_controller_conduit_end_DOUT          => CONNECTED_TO_audio_avalon_controller_conduit_end_DOUT,          --                                    .DOUT
			audio_avalon_controller_conduit_end_BCLK          => CONNECTED_TO_audio_avalon_controller_conduit_end_BCLK,          --                                    .BCLK
			av_i2c_clk_pio_external_connection_export         => CONNECTED_TO_av_i2c_clk_pio_external_connection_export,         --  av_i2c_clk_pio_external_connection.export
			av_i2c_data_pio_external_connection_export        => CONNECTED_TO_av_i2c_data_pio_external_connection_export,        -- av_i2c_data_pio_external_connection.export
			button_pio_external_connection_export             => CONNECTED_TO_button_pio_external_connection_export,             --      button_pio_external_connection.export
			clk_clk                                           => CONNECTED_TO_clk_clk,                                           --                                 clk.clk
			clk_mtlc_clk                                      => CONNECTED_TO_clk_mtlc_clk,                                      --                            clk_mtlc.clk
			clk_sdram_clk                                     => CONNECTED_TO_clk_sdram_clk,                                     --                           clk_sdram.clk
			clk_sys_clk                                       => CONNECTED_TO_clk_sys_clk,                                       --                             clk_sys.clk
			led_pio_external_connection_export                => CONNECTED_TO_led_pio_external_connection_export,                --         led_pio_external_connection.export
			pll_0_locked_export                               => CONNECTED_TO_pll_0_locked_export,                               --                        pll_0_locked.export
			reset_reset_n                                     => CONNECTED_TO_reset_reset_n,                                     --                               reset.reset_n
			sdram_wire_addr                                   => CONNECTED_TO_sdram_wire_addr,                                   --                          sdram_wire.addr
			sdram_wire_ba                                     => CONNECTED_TO_sdram_wire_ba,                                     --                                    .ba
			sdram_wire_cas_n                                  => CONNECTED_TO_sdram_wire_cas_n,                                  --                                    .cas_n
			sdram_wire_cke                                    => CONNECTED_TO_sdram_wire_cke,                                    --                                    .cke
			sdram_wire_cs_n                                   => CONNECTED_TO_sdram_wire_cs_n,                                   --                                    .cs_n
			sdram_wire_dq                                     => CONNECTED_TO_sdram_wire_dq,                                     --                                    .dq
			sdram_wire_dqm                                    => CONNECTED_TO_sdram_wire_dqm,                                    --                                    .dqm
			sdram_wire_ras_n                                  => CONNECTED_TO_sdram_wire_ras_n,                                  --                                    .ras_n
			sdram_wire_we_n                                   => CONNECTED_TO_sdram_wire_we_n,                                   --                                    .we_n
			td_reset_pio_external_connection_export           => CONNECTED_TO_td_reset_pio_external_connection_export,           --    td_reset_pio_external_connection.export
			touch_i2c_opencores_export_scl_pad_io             => CONNECTED_TO_touch_i2c_opencores_export_scl_pad_io,             --          touch_i2c_opencores_export.scl_pad_io
			touch_i2c_opencores_export_sda_pad_io             => CONNECTED_TO_touch_i2c_opencores_export_sda_pad_io,             --                                    .sda_pad_io
			touch_int_n_external_connection_export            => CONNECTED_TO_touch_int_n_external_connection_export             --     touch_int_n_external_connection.export
		);

