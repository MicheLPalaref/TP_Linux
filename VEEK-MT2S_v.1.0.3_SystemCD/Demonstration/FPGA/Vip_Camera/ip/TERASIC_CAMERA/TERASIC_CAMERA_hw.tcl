# TCL File Generated by Component Editor 16.1
# Sun Jan 08 00:30:35 CST 2017
# DO NOT MODIFY


# 
# TERASIC_CAMERA "TERASIC_CAMERA" v1.0
#  2017.01.08.00:30:35
# 
# 

# 
# request TCL package from ACDS 16.1
# 
package require -exact qsys 16.1


# 
# module TERASIC_CAMERA
# 
set_module_property DESCRIPTION ""
set_module_property NAME TERASIC_CAMERA
set_module_property VERSION 1.0
set_module_property INTERNAL false
set_module_property OPAQUE_ADDRESS_MAP true
set_module_property GROUP Terasic
set_module_property AUTHOR ""
set_module_property DISPLAY_NAME TERASIC_CAMERA
set_module_property INSTANTIATE_IN_SYSTEM_MODULE true
set_module_property EDITABLE true
set_module_property REPORT_TO_TALKBACK false
set_module_property ALLOW_GREYBOX_GENERATION false
set_module_property REPORT_HIERARCHY false


# 
# file sets
# 
add_fileset quartus_synth QUARTUS_SYNTH "" "Quartus Synthesis"
set_fileset_property quartus_synth TOP_LEVEL TERASIC_CAMERA10
set_fileset_property quartus_synth ENABLE_RELATIVE_INCLUDE_PATHS false
set_fileset_property quartus_synth ENABLE_FILE_OVERWRITE_MODE false
add_fileset_file TERASIC_CAMERA.v VERILOG PATH TERASIC_CAMERA.v TOP_LEVEL_FILE
add_fileset_file CAMERA_RGB.v VERILOG PATH CAMERA_RGB.v
add_fileset_file CAMERA_Bayer.v VERILOG PATH CAMERA_Bayer.v
add_fileset_file Bayer2RGB.v VERILOG PATH Bayer2RGB.v
add_fileset_file Bayer_LineBuffer.v VERILOG PATH Bayer_LineBuffer.v
add_fileset_file rgb_fifo.v VERILOG PATH rgb_fifo.v
add_fileset_file add4.v VERILOG PATH add4.v
add_fileset_file add2.v VERILOG PATH add2.v

add_fileset sim_verilog SIM_VERILOG "" "Verilog Simulation"
set_fileset_property sim_verilog TOP_LEVEL TERASIC_CAMERA10
set_fileset_property sim_verilog ENABLE_RELATIVE_INCLUDE_PATHS false
set_fileset_property sim_verilog ENABLE_FILE_OVERWRITE_MODE false
add_fileset_file TERASIC_CAMERA.v VERILOG PATH TERASIC_CAMERA.v
add_fileset_file CAMERA_RGB.v VERILOG PATH CAMERA_RGB.v
add_fileset_file CAMERA_Bayer.v VERILOG PATH CAMERA_Bayer.v
add_fileset_file Bayer2RGB.v VERILOG PATH Bayer2RGB.v
add_fileset_file Bayer_LineBuffer.v VERILOG PATH Bayer_LineBuffer.v
add_fileset_file rgb_fifo.v VERILOG PATH rgb_fifo.v
add_fileset_file add2.v VERILOG PATH add2.v
add_fileset_file add4.v VERILOG PATH add4.v


# 
# parameters
# 
add_parameter VIDEO_W INTEGER 1920 ""
set_parameter_property VIDEO_W DEFAULT_VALUE 1920
set_parameter_property VIDEO_W DISPLAY_NAME VIDEO_W
set_parameter_property VIDEO_W TYPE INTEGER
set_parameter_property VIDEO_W UNITS None
set_parameter_property VIDEO_W ALLOWED_RANGES -2147483648:2147483647
set_parameter_property VIDEO_W DESCRIPTION ""
set_parameter_property VIDEO_W HDL_PARAMETER true
add_parameter VIDEO_H INTEGER 1080 ""
set_parameter_property VIDEO_H DEFAULT_VALUE 1080
set_parameter_property VIDEO_H DISPLAY_NAME VIDEO_H
set_parameter_property VIDEO_H TYPE INTEGER
set_parameter_property VIDEO_H UNITS None
set_parameter_property VIDEO_H ALLOWED_RANGES -2147483648:2147483647
set_parameter_property VIDEO_H DESCRIPTION ""
set_parameter_property VIDEO_H HDL_PARAMETER true


# 
# display items
# 


# 
# connection point clock_reset
# 
add_interface clock_reset clock end
set_interface_property clock_reset clockRate 0
set_interface_property clock_reset ENABLED true
set_interface_property clock_reset EXPORT_OF ""
set_interface_property clock_reset PORT_NAME_MAP ""
set_interface_property clock_reset CMSIS_SVD_VARIABLES ""
set_interface_property clock_reset SVD_ADDRESS_GROUP ""

add_interface_port clock_reset clk clk Input 1


# 
# connection point clock_reset_reset
# 
add_interface clock_reset_reset reset end
set_interface_property clock_reset_reset associatedClock clock_reset
set_interface_property clock_reset_reset synchronousEdges DEASSERT
set_interface_property clock_reset_reset ENABLED true
set_interface_property clock_reset_reset EXPORT_OF ""
set_interface_property clock_reset_reset PORT_NAME_MAP ""
set_interface_property clock_reset_reset CMSIS_SVD_VARIABLES ""
set_interface_property clock_reset_reset SVD_ADDRESS_GROUP ""

add_interface_port clock_reset_reset reset_n reset_n Input 1


# 
# connection point conduit_end
# 
add_interface conduit_end conduit end
set_interface_property conduit_end associatedClock ""
set_interface_property conduit_end associatedReset ""
set_interface_property conduit_end ENABLED true
set_interface_property conduit_end EXPORT_OF ""
set_interface_property conduit_end PORT_NAME_MAP ""
set_interface_property conduit_end CMSIS_SVD_VARIABLES ""
set_interface_property conduit_end SVD_ADDRESS_GROUP ""

add_interface_port conduit_end CAMERA_D camera_d Input 12
add_interface_port conduit_end CAMERA_FVAL camera_fval Input 1
add_interface_port conduit_end CAMERA_LVAL camera_lval Input 1
add_interface_port conduit_end CAMERA_PIXCLK camera_pixclk Input 1


# 
# connection point avalon_streaming_source
# 
add_interface avalon_streaming_source avalon_streaming start
set_interface_property avalon_streaming_source associatedClock clock_reset
set_interface_property avalon_streaming_source associatedReset clock_reset_reset
set_interface_property avalon_streaming_source dataBitsPerSymbol 8
set_interface_property avalon_streaming_source errorDescriptor ""
set_interface_property avalon_streaming_source firstSymbolInHighOrderBits true
set_interface_property avalon_streaming_source maxChannel 0
set_interface_property avalon_streaming_source readyLatency 1
set_interface_property avalon_streaming_source ENABLED true
set_interface_property avalon_streaming_source EXPORT_OF ""
set_interface_property avalon_streaming_source PORT_NAME_MAP ""
set_interface_property avalon_streaming_source CMSIS_SVD_VARIABLES ""
set_interface_property avalon_streaming_source SVD_ADDRESS_GROUP ""

add_interface_port avalon_streaming_source st_data data Output 24
add_interface_port avalon_streaming_source st_valid valid Output 1
add_interface_port avalon_streaming_source st_sop startofpacket Output 1
add_interface_port avalon_streaming_source st_eop endofpacket Output 1
add_interface_port avalon_streaming_source st_ready ready Input 1

