# TCL File Generated by Component Editor 16.1
# Tue Mar 07 10:37:06 CST 2017
# DO NOT MODIFY


# 
# TERASIC_STREAM_CAPTURE "TERASIC_STREAM_CAPTURE" v1.0
#  2017.03.07.10:37:06
# 
# 

# 
# request TCL package from ACDS 16.1
# 
package require -exact qsys 16.1


# 
# module TERASIC_STREAM_CAPTURE
# 
set_module_property DESCRIPTION ""
set_module_property NAME TERASIC_STREAM_CAPTURE
set_module_property VERSION 1.0
set_module_property INTERNAL false
set_module_property OPAQUE_ADDRESS_MAP true
set_module_property GROUP Terasic/
set_module_property AUTHOR ""
set_module_property DISPLAY_NAME TERASIC_STREAM_CAPTURE
set_module_property INSTANTIATE_IN_SYSTEM_MODULE true
set_module_property EDITABLE true
set_module_property REPORT_TO_TALKBACK false
set_module_property ALLOW_GREYBOX_GENERATION false
set_module_property REPORT_HIERARCHY false


# 
# file sets
# 
add_fileset QUARTUS_SYNTH QUARTUS_SYNTH "" ""
set_fileset_property QUARTUS_SYNTH TOP_LEVEL TERASIC_STREAM_CAPTURE
set_fileset_property QUARTUS_SYNTH ENABLE_RELATIVE_INCLUDE_PATHS false
set_fileset_property QUARTUS_SYNTH ENABLE_FILE_OVERWRITE_MODE false
add_fileset_file TERASIC_STREAM_CATPURE.v VERILOG PATH TERASIC_STREAM_CATPURE.v TOP_LEVEL_FILE
add_fileset_file FRAME_FIFO.v VERILOG PATH FRAME_FIFO.v


# 
# parameters
# 
add_parameter FRAME_WIDTH INTEGER 1024
set_parameter_property FRAME_WIDTH DEFAULT_VALUE 1024
set_parameter_property FRAME_WIDTH DISPLAY_NAME FRAME_WIDTH
set_parameter_property FRAME_WIDTH TYPE INTEGER
set_parameter_property FRAME_WIDTH UNITS None
set_parameter_property FRAME_WIDTH ALLOWED_RANGES -2147483648:2147483647
set_parameter_property FRAME_WIDTH HDL_PARAMETER true
add_parameter FRAME_HEIGHT INTEGER 768
set_parameter_property FRAME_HEIGHT DEFAULT_VALUE 768
set_parameter_property FRAME_HEIGHT DISPLAY_NAME FRAME_HEIGHT
set_parameter_property FRAME_HEIGHT TYPE INTEGER
set_parameter_property FRAME_HEIGHT UNITS None
set_parameter_property FRAME_HEIGHT ALLOWED_RANGES -2147483648:2147483647
set_parameter_property FRAME_HEIGHT HDL_PARAMETER true
add_parameter ENABLE_SOURCE INTEGER 0
set_parameter_property ENABLE_SOURCE DEFAULT_VALUE 0
set_parameter_property ENABLE_SOURCE DISPLAY_NAME ENABLE_SOURCE
set_parameter_property ENABLE_SOURCE TYPE INTEGER
set_parameter_property ENABLE_SOURCE UNITS None
set_parameter_property ENABLE_SOURCE ALLOWED_RANGES -2147483648:2147483647
set_parameter_property ENABLE_SOURCE HDL_PARAMETER true


# 
# display items
# 


# 
# connection point clock
# 
add_interface clock clock end
set_interface_property clock clockRate 0
set_interface_property clock ENABLED true
set_interface_property clock EXPORT_OF ""
set_interface_property clock PORT_NAME_MAP ""
set_interface_property clock CMSIS_SVD_VARIABLES ""
set_interface_property clock SVD_ADDRESS_GROUP ""

add_interface_port clock clk clk Input 1


# 
# connection point reset
# 
add_interface reset reset end
set_interface_property reset associatedClock clock
set_interface_property reset synchronousEdges DEASSERT
set_interface_property reset ENABLED true
set_interface_property reset EXPORT_OF ""
set_interface_property reset PORT_NAME_MAP ""
set_interface_property reset CMSIS_SVD_VARIABLES ""
set_interface_property reset SVD_ADDRESS_GROUP ""

add_interface_port reset reset_n reset_n Input 1


# 
# connection point avalon_master
# 
add_interface avalon_master avalon start
set_interface_property avalon_master addressUnits SYMBOLS
set_interface_property avalon_master associatedClock clock
set_interface_property avalon_master associatedReset reset
set_interface_property avalon_master bitsPerSymbol 8
set_interface_property avalon_master burstOnBurstBoundariesOnly false
set_interface_property avalon_master burstcountUnits WORDS
set_interface_property avalon_master doStreamReads false
set_interface_property avalon_master doStreamWrites false
set_interface_property avalon_master holdTime 0
set_interface_property avalon_master linewrapBursts false
set_interface_property avalon_master maximumPendingReadTransactions 0
set_interface_property avalon_master maximumPendingWriteTransactions 0
set_interface_property avalon_master readLatency 0
set_interface_property avalon_master readWaitTime 1
set_interface_property avalon_master setupTime 0
set_interface_property avalon_master timingUnits Cycles
set_interface_property avalon_master writeWaitTime 0
set_interface_property avalon_master ENABLED true
set_interface_property avalon_master EXPORT_OF ""
set_interface_property avalon_master PORT_NAME_MAP ""
set_interface_property avalon_master CMSIS_SVD_VARIABLES ""
set_interface_property avalon_master SVD_ADDRESS_GROUP ""

add_interface_port avalon_master master_chip_select_n chipselect_n Output 1
add_interface_port avalon_master master_addr address Output 32
add_interface_port avalon_master master_write write Output 1
add_interface_port avalon_master master_writedata writedata Output 32
add_interface_port avalon_master master_waitrequest_n waitrequest_n Input 1


# 
# connection point avalon_slave
# 
add_interface avalon_slave avalon end
set_interface_property avalon_slave addressUnits WORDS
set_interface_property avalon_slave associatedClock clock
set_interface_property avalon_slave associatedReset reset
set_interface_property avalon_slave bitsPerSymbol 8
set_interface_property avalon_slave burstOnBurstBoundariesOnly false
set_interface_property avalon_slave burstcountUnits WORDS
set_interface_property avalon_slave explicitAddressSpan 0
set_interface_property avalon_slave holdTime 0
set_interface_property avalon_slave linewrapBursts false
set_interface_property avalon_slave maximumPendingReadTransactions 0
set_interface_property avalon_slave maximumPendingWriteTransactions 0
set_interface_property avalon_slave readLatency 0
set_interface_property avalon_slave readWaitTime 1
set_interface_property avalon_slave setupTime 0
set_interface_property avalon_slave timingUnits Cycles
set_interface_property avalon_slave writeWaitTime 0
set_interface_property avalon_slave ENABLED true
set_interface_property avalon_slave EXPORT_OF ""
set_interface_property avalon_slave PORT_NAME_MAP ""
set_interface_property avalon_slave CMSIS_SVD_VARIABLES ""
set_interface_property avalon_slave SVD_ADDRESS_GROUP ""

add_interface_port avalon_slave slave_read read Input 1
add_interface_port avalon_slave slave_readdata readdata Output 32
add_interface_port avalon_slave slave_write write Input 1
add_interface_port avalon_slave slave_writedata writedata Input 32
add_interface_port avalon_slave slave_chip_select_n chipselect_n Input 1
add_interface_port avalon_slave slave_addr address Input 3
set_interface_assignment avalon_slave embeddedsw.configuration.isFlash 0
set_interface_assignment avalon_slave embeddedsw.configuration.isMemoryDevice 0
set_interface_assignment avalon_slave embeddedsw.configuration.isNonVolatileStorage 0
set_interface_assignment avalon_slave embeddedsw.configuration.isPrintableDevice 0


# 
# connection point avalon_streaming_sink
# 
add_interface avalon_streaming_sink avalon_streaming end
set_interface_property avalon_streaming_sink associatedClock clock
set_interface_property avalon_streaming_sink associatedReset reset
set_interface_property avalon_streaming_sink dataBitsPerSymbol 8
set_interface_property avalon_streaming_sink errorDescriptor ""
set_interface_property avalon_streaming_sink firstSymbolInHighOrderBits true
set_interface_property avalon_streaming_sink maxChannel 0
set_interface_property avalon_streaming_sink readyLatency 0
set_interface_property avalon_streaming_sink ENABLED true
set_interface_property avalon_streaming_sink EXPORT_OF ""
set_interface_property avalon_streaming_sink PORT_NAME_MAP ""
set_interface_property avalon_streaming_sink CMSIS_SVD_VARIABLES ""
set_interface_property avalon_streaming_sink SVD_ADDRESS_GROUP ""

add_interface_port avalon_streaming_sink sink_data data Input 24
add_interface_port avalon_streaming_sink sink_eop endofpacket Input 1
add_interface_port avalon_streaming_sink sink_ready ready Output 1
add_interface_port avalon_streaming_sink sink_sop startofpacket Input 1
add_interface_port avalon_streaming_sink sink_valid valid Input 1


# 
# connection point avalon_streaming_source
# 
add_interface avalon_streaming_source avalon_streaming start
set_interface_property avalon_streaming_source associatedClock clock
set_interface_property avalon_streaming_source associatedReset reset
set_interface_property avalon_streaming_source dataBitsPerSymbol 8
set_interface_property avalon_streaming_source errorDescriptor ""
set_interface_property avalon_streaming_source firstSymbolInHighOrderBits true
set_interface_property avalon_streaming_source maxChannel 0
set_interface_property avalon_streaming_source readyLatency 0
set_interface_property avalon_streaming_source ENABLED true
set_interface_property avalon_streaming_source EXPORT_OF ""
set_interface_property avalon_streaming_source PORT_NAME_MAP ""
set_interface_property avalon_streaming_source CMSIS_SVD_VARIABLES ""
set_interface_property avalon_streaming_source SVD_ADDRESS_GROUP ""

add_interface_port avalon_streaming_source source_data data Output 24
add_interface_port avalon_streaming_source source_eop endofpacket Output 1
add_interface_port avalon_streaming_source source_ready ready Input 1
add_interface_port avalon_streaming_source source_sop startofpacket Output 1
add_interface_port avalon_streaming_source source_valid valid Output 1
