# TCL File Generated by Component Editor 8.1
# Wed Jan 28 09:42:07 JST 2009
# DO NOT MODIFY


# +-----------------------------------
# | 
# | alt_vip_custom_avst_duplicator "alt_vip_custom_avst_duplicator" v1.0
# | null 2009.01.28.09:42:07
# | 
# | 
# | C:/hhagiwar/VideoExample/NEEK_VIP_demo_v2_vga_lcd_bicubic_fb_sc/ip/my_avst_duplicator/avst_duplicator.v
# | 
# |    ./avst_duplicator.v syn, sim
# | 
# +-----------------------------------


# +-----------------------------------
# | module alt_vip_custom_avst_duplicator
# | 
set_module_property NAME alt_vip_custom_avst_duplicator
set_module_property VERSION 1.0
set_module_property GROUP my_vip
set_module_property DISPLAY_NAME alt_vip_custom_avst_duplicator
set_module_property TOP_LEVEL_HDL_FILE avst_duplicator.v
set_module_property TOP_LEVEL_HDL_MODULE avst_duplicator
set_module_property INSTANTIATE_IN_SYSTEM_MODULE true
set_module_property EDITABLE false
# | 
# +-----------------------------------

# +-----------------------------------
# | files
# | 
add_file avst_duplicator.v {SYNTHESIS SIMULATION}
# | 
# +-----------------------------------

# +-----------------------------------
# | parameters
# | 
# | 
# +-----------------------------------

# +-----------------------------------
# | connection point clock_reset
# | 
add_interface clock_reset clock end
set_interface_property clock_reset ptfSchematicName ""

add_interface_port clock_reset clock clk Input 1
add_interface_port clock_reset reset reset Input 1
# | 
# +-----------------------------------

# +-----------------------------------
# | connection point avalon_streaming_sink
# | 
add_interface avalon_streaming_sink avalon_streaming end
set_interface_property avalon_streaming_sink dataBitsPerSymbol 8
set_interface_property avalon_streaming_sink errorDescriptor ""
set_interface_property avalon_streaming_sink maxChannel 0
set_interface_property avalon_streaming_sink readyLatency 1
set_interface_property avalon_streaming_sink symbolsPerBeat 3

set_interface_property avalon_streaming_sink ASSOCIATED_CLOCK clock_reset

add_interface_port avalon_streaming_sink din_ready ready Output 1
add_interface_port avalon_streaming_sink din_valid valid Input 1
add_interface_port avalon_streaming_sink din_data data Input 24
add_interface_port avalon_streaming_sink din_sop startofpacket Input 1
add_interface_port avalon_streaming_sink din_eop endofpacket Input 1
# | 
# +-----------------------------------

# +-----------------------------------
# | connection point avalon_streaming_main_source
# | 
add_interface avalon_streaming_main_source avalon_streaming start
set_interface_property avalon_streaming_main_source dataBitsPerSymbol 8
set_interface_property avalon_streaming_main_source errorDescriptor ""
set_interface_property avalon_streaming_main_source maxChannel 0
set_interface_property avalon_streaming_main_source readyLatency 1
set_interface_property avalon_streaming_main_source symbolsPerBeat 3

set_interface_property avalon_streaming_main_source ASSOCIATED_CLOCK clock_reset

add_interface_port avalon_streaming_main_source dout_ready ready Input 1
add_interface_port avalon_streaming_main_source dout_valid valid Output 1
add_interface_port avalon_streaming_main_source dout_data data Output 24
add_interface_port avalon_streaming_main_source dout_sop startofpacket Output 1
add_interface_port avalon_streaming_main_source dout_eop endofpacket Output 1
add_interface_port avalon_streaming_main_source dout_empty empty Output 2
# | 
# +-----------------------------------

# +-----------------------------------
# | connection point avalon_streaming_sub_source
# | 
add_interface avalon_streaming_sub_source avalon_streaming start
set_interface_property avalon_streaming_sub_source dataBitsPerSymbol 8
set_interface_property avalon_streaming_sub_source errorDescriptor ""
set_interface_property avalon_streaming_sub_source maxChannel 0
set_interface_property avalon_streaming_sub_source readyLatency 1
set_interface_property avalon_streaming_sub_source symbolsPerBeat 3

set_interface_property avalon_streaming_sub_source ASSOCIATED_CLOCK clock_reset

add_interface_port avalon_streaming_sub_source dout_sub_ready ready Input 1
add_interface_port avalon_streaming_sub_source dout_sub_valid valid Output 1
add_interface_port avalon_streaming_sub_source dout_sub_data data Output 24
add_interface_port avalon_streaming_sub_source dout_sub_sop startofpacket Output 1
add_interface_port avalon_streaming_sub_source dout_sub_eop endofpacket Output 1
add_interface_port avalon_streaming_sub_source dout_sub_empty empty Output 2
# | 
# +-----------------------------------
