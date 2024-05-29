# TCL File Generated by Component Editor 9.1
# Thu Dec 31 00:17:39 PST 2009
# DO NOT MODIFY


# +-----------------------------------
# | 
# | alt_vip_custom_tpg "alt_vip_custom_tpg" v2.0
# | null 2009.12.31.00:17:39
# | 
# | 
# | /data/hhagiwar/NEEK/VIP_v91/NEEK_VIP_demo_LCD_SVGA_v91/ip/my_test_pat_generator/test_pat_generator.v
# | 
# |    ./test_pat_generator.v syn, sim
# | 
# +-----------------------------------

# +-----------------------------------
# | request TCL package from ACDS 9.1
# | 
package require -exact sopc 9.1
# | 
# +-----------------------------------

# +-----------------------------------
# | module alt_vip_custom_tpg
# | 
set_module_property NAME alt_vip_custom_tpg
set_module_property VERSION 2.0
set_module_property INTERNAL false
set_module_property GROUP my_vip
set_module_property DISPLAY_NAME alt_vip_custom_tpg
set_module_property TOP_LEVEL_HDL_FILE test_pat_generator.v
set_module_property TOP_LEVEL_HDL_MODULE test_pat_generator
set_module_property INSTANTIATE_IN_SYSTEM_MODULE true
set_module_property EDITABLE true
set_module_property ANALYZE_HDL TRUE
# | 
# +-----------------------------------

# +-----------------------------------
# | files
# | 
add_file test_pat_generator.v {SYNTHESIS SIMULATION}
# | 
# +-----------------------------------

# +-----------------------------------
# | parameters
# | 
add_parameter WIDTH INTEGER 1024
set_parameter_property WIDTH DEFAULT_VALUE 1024
set_parameter_property WIDTH DISPLAY_NAME WIDTH
set_parameter_property WIDTH UNITS None
set_parameter_property WIDTH ALLOWED_RANGES -2147483648:2147483647
set_parameter_property WIDTH DISPLAY_HINT ""
set_parameter_property WIDTH AFFECTS_GENERATION false
set_parameter_property WIDTH HDL_PARAMETER true
add_parameter HEIGHT INTEGER 768
set_parameter_property HEIGHT DEFAULT_VALUE 768
set_parameter_property HEIGHT DISPLAY_NAME HEIGHT
set_parameter_property HEIGHT UNITS None
set_parameter_property HEIGHT ALLOWED_RANGES -2147483648:2147483647
set_parameter_property HEIGHT DISPLAY_HINT ""
set_parameter_property HEIGHT AFFECTS_GENERATION false
set_parameter_property HEIGHT HDL_PARAMETER true
add_parameter CTRL_PKT_NUM INTEGER 3
set_parameter_property CTRL_PKT_NUM DEFAULT_VALUE 3
set_parameter_property CTRL_PKT_NUM DISPLAY_NAME CTRL_PKT_NUM
set_parameter_property CTRL_PKT_NUM ENABLED false
set_parameter_property CTRL_PKT_NUM UNITS None
set_parameter_property CTRL_PKT_NUM ALLOWED_RANGES -2147483648:2147483647
set_parameter_property CTRL_PKT_NUM DISPLAY_HINT ""
set_parameter_property CTRL_PKT_NUM AFFECTS_GENERATION false
set_parameter_property CTRL_PKT_NUM HDL_PARAMETER true
add_parameter CTRL_PKT_HEADER INTEGER 15
set_parameter_property CTRL_PKT_HEADER DEFAULT_VALUE 15
set_parameter_property CTRL_PKT_HEADER DISPLAY_NAME CTRL_PKT_HEADER
set_parameter_property CTRL_PKT_HEADER ENABLED false
set_parameter_property CTRL_PKT_HEADER UNITS None
set_parameter_property CTRL_PKT_HEADER ALLOWED_RANGES -2147483648:2147483647
set_parameter_property CTRL_PKT_HEADER DISPLAY_HINT ""
set_parameter_property CTRL_PKT_HEADER AFFECTS_GENERATION false
set_parameter_property CTRL_PKT_HEADER HDL_PARAMETER true
add_parameter DATA_PKT_HEADER INTEGER 0
set_parameter_property DATA_PKT_HEADER DEFAULT_VALUE 0
set_parameter_property DATA_PKT_HEADER DISPLAY_NAME DATA_PKT_HEADER
set_parameter_property DATA_PKT_HEADER ENABLED false
set_parameter_property DATA_PKT_HEADER UNITS None
set_parameter_property DATA_PKT_HEADER ALLOWED_RANGES -2147483648:2147483647
set_parameter_property DATA_PKT_HEADER DISPLAY_HINT ""
set_parameter_property DATA_PKT_HEADER AFFECTS_GENERATION false
set_parameter_property DATA_PKT_HEADER HDL_PARAMETER true
add_parameter STATE_CTRL_PKT_SOP INTEGER 0
set_parameter_property STATE_CTRL_PKT_SOP DEFAULT_VALUE 0
set_parameter_property STATE_CTRL_PKT_SOP DISPLAY_NAME STATE_CTRL_PKT_SOP
set_parameter_property STATE_CTRL_PKT_SOP ENABLED false
set_parameter_property STATE_CTRL_PKT_SOP UNITS None
set_parameter_property STATE_CTRL_PKT_SOP ALLOWED_RANGES -2147483648:2147483647
set_parameter_property STATE_CTRL_PKT_SOP DISPLAY_HINT ""
set_parameter_property STATE_CTRL_PKT_SOP AFFECTS_GENERATION false
set_parameter_property STATE_CTRL_PKT_SOP HDL_PARAMETER true
add_parameter STATE_CTRL_PKT_DAT INTEGER 1
set_parameter_property STATE_CTRL_PKT_DAT DEFAULT_VALUE 1
set_parameter_property STATE_CTRL_PKT_DAT DISPLAY_NAME STATE_CTRL_PKT_DAT
set_parameter_property STATE_CTRL_PKT_DAT ENABLED false
set_parameter_property STATE_CTRL_PKT_DAT UNITS None
set_parameter_property STATE_CTRL_PKT_DAT ALLOWED_RANGES -2147483648:2147483647
set_parameter_property STATE_CTRL_PKT_DAT DISPLAY_HINT ""
set_parameter_property STATE_CTRL_PKT_DAT AFFECTS_GENERATION false
set_parameter_property STATE_CTRL_PKT_DAT HDL_PARAMETER true
add_parameter STATE_DATA_PKT_SOP INTEGER 2
set_parameter_property STATE_DATA_PKT_SOP DEFAULT_VALUE 2
set_parameter_property STATE_DATA_PKT_SOP DISPLAY_NAME STATE_DATA_PKT_SOP
set_parameter_property STATE_DATA_PKT_SOP ENABLED false
set_parameter_property STATE_DATA_PKT_SOP UNITS None
set_parameter_property STATE_DATA_PKT_SOP ALLOWED_RANGES -2147483648:2147483647
set_parameter_property STATE_DATA_PKT_SOP DISPLAY_HINT ""
set_parameter_property STATE_DATA_PKT_SOP AFFECTS_GENERATION false
set_parameter_property STATE_DATA_PKT_SOP HDL_PARAMETER true
add_parameter STATE_DATA_PKT_DAT INTEGER 3
set_parameter_property STATE_DATA_PKT_DAT DEFAULT_VALUE 3
set_parameter_property STATE_DATA_PKT_DAT DISPLAY_NAME STATE_DATA_PKT_DAT
set_parameter_property STATE_DATA_PKT_DAT ENABLED false
set_parameter_property STATE_DATA_PKT_DAT UNITS None
set_parameter_property STATE_DATA_PKT_DAT ALLOWED_RANGES -2147483648:2147483647
set_parameter_property STATE_DATA_PKT_DAT DISPLAY_HINT ""
set_parameter_property STATE_DATA_PKT_DAT AFFECTS_GENERATION false
set_parameter_property STATE_DATA_PKT_DAT HDL_PARAMETER true
# | 
# +-----------------------------------

# +-----------------------------------
# | display items
# | 
# | 
# +-----------------------------------

# +-----------------------------------
# | connection point avalon_streaming_source
# | 
add_interface avalon_streaming_source avalon_streaming start
set_interface_property avalon_streaming_source associatedClock clock_sink
set_interface_property avalon_streaming_source dataBitsPerSymbol 8
set_interface_property avalon_streaming_source errorDescriptor ""
set_interface_property avalon_streaming_source maxChannel 0
set_interface_property avalon_streaming_source readyLatency 1
set_interface_property avalon_streaming_source symbolsPerBeat 3

set_interface_property avalon_streaming_source ASSOCIATED_CLOCK clock_sink
set_interface_property avalon_streaming_source ENABLED true

add_interface_port avalon_streaming_source dout_ready ready Input 1
add_interface_port avalon_streaming_source dout_valid valid Output 1
add_interface_port avalon_streaming_source dout_data data Output 24
add_interface_port avalon_streaming_source dout_sop startofpacket Output 1
add_interface_port avalon_streaming_source dout_eop endofpacket Output 1
add_interface_port avalon_streaming_source dout_empty empty Output 2
# | 
# +-----------------------------------

# +-----------------------------------
# | connection point avalon_slave
# | 
add_interface avalon_slave avalon end
set_interface_property avalon_slave addressAlignment DYNAMIC
set_interface_property avalon_slave associatedClock clock_sink
set_interface_property avalon_slave burstOnBurstBoundariesOnly false
set_interface_property avalon_slave explicitAddressSpan 0
set_interface_property avalon_slave holdTime 0
set_interface_property avalon_slave isMemoryDevice false
set_interface_property avalon_slave isNonVolatileStorage false
set_interface_property avalon_slave linewrapBursts false
set_interface_property avalon_slave maximumPendingReadTransactions 0
set_interface_property avalon_slave printableDevice false
set_interface_property avalon_slave readLatency 0
set_interface_property avalon_slave readWaitTime 1
set_interface_property avalon_slave setupTime 0
set_interface_property avalon_slave timingUnits Cycles
set_interface_property avalon_slave writeWaitTime 0

set_interface_property avalon_slave ASSOCIATED_CLOCK clock_sink
set_interface_property avalon_slave ENABLED true

add_interface_port avalon_slave control_av_chipselect chipselect Input 1
add_interface_port avalon_slave control_av_write write Input 1
add_interface_port avalon_slave control_av_address address Input 1
add_interface_port avalon_slave control_av_writedata writedata Input 32
add_interface_port avalon_slave control_av_readdata readdata Output 32
# | 
# +-----------------------------------

# +-----------------------------------
# | connection point clock_sink
# | 
add_interface clock_sink clock end

set_interface_property clock_sink ENABLED true

add_interface_port clock_sink reset reset Input 1
add_interface_port clock_sink clock clk Input 1
# | 
# +-----------------------------------