# qsys scripting (.tcl) file for tv_decoder
package require -exact qsys 16.0

create_system {tv_decoder}

set_project_property DEVICE_FAMILY {Cyclone V}
set_project_property DEVICE {5CSXFC6D6F31C6}
set_project_property HIDE_FROM_IP_CATALOG {false}

# Instances and instance parameters
# (disabled instances are intentionally culled)
add_instance alt_vip_cl_clp_0 alt_vip_cl_clp 16.1
set_instance_parameter_value alt_vip_cl_clp_0 {BITS_PER_SYMBOL} {8}
set_instance_parameter_value alt_vip_cl_clp_0 {NUMBER_OF_COLOR_PLANES} {3}
set_instance_parameter_value alt_vip_cl_clp_0 {COLOR_PLANES_ARE_IN_PARALLEL} {1}
set_instance_parameter_value alt_vip_cl_clp_0 {PIXELS_IN_PARALLEL} {1}
set_instance_parameter_value alt_vip_cl_clp_0 {MAX_IN_WIDTH} {720}
set_instance_parameter_value alt_vip_cl_clp_0 {MAX_IN_HEIGHT} {576}
set_instance_parameter_value alt_vip_cl_clp_0 {CLIPPING_METHOD} {RECTANGLE}
set_instance_parameter_value alt_vip_cl_clp_0 {LEFT_OFFSET} {40}
set_instance_parameter_value alt_vip_cl_clp_0 {RIGHT_OFFSET} {0}
set_instance_parameter_value alt_vip_cl_clp_0 {TOP_OFFSET} {24}
set_instance_parameter_value alt_vip_cl_clp_0 {BOTTOM_OFFSET} {0}
set_instance_parameter_value alt_vip_cl_clp_0 {RECTANGLE_WIDTH} {640}
set_instance_parameter_value alt_vip_cl_clp_0 {RECTANGLE_HEIGHT} {480}
set_instance_parameter_value alt_vip_cl_clp_0 {EXTRA_PIPELINING} {0}
set_instance_parameter_value alt_vip_cl_clp_0 {USER_PACKET_SUPPORT} {PASSTHROUGH}
set_instance_parameter_value alt_vip_cl_clp_0 {USER_PACKET_FIFO_DEPTH} {0}
set_instance_parameter_value alt_vip_cl_clp_0 {RUNTIME_CONTROL} {0}
set_instance_parameter_value alt_vip_cl_clp_0 {LIMITED_READBACK} {0}

add_instance alt_vip_cl_cps_0 alt_vip_cl_cps 16.1
set_instance_parameter_value alt_vip_cl_cps_0 {BITS_PER_SYMBOL} {8}
set_instance_parameter_value alt_vip_cl_cps_0 {NUMBER_OF_INPUTS} {1}
set_instance_parameter_value alt_vip_cl_cps_0 {NUMBER_OF_OUTPUTS} {1}
set_instance_parameter_value alt_vip_cl_cps_0 {INPUT_0_FIFO} {0}
set_instance_parameter_value alt_vip_cl_cps_0 {INPUT_0_FIFO_SIZE} {8}
set_instance_parameter_value alt_vip_cl_cps_0 {INPUT_0_NUMBER_OF_COLOR_PLANES} {2}
set_instance_parameter_value alt_vip_cl_cps_0 {INPUT_0_COLOR_PLANES_ARE_IN_PARALLEL} {0}
set_instance_parameter_value alt_vip_cl_cps_0 {INPUT_0_PIXELS_IN_PARALLEL} {1}
set_instance_parameter_value alt_vip_cl_cps_0 {INPUT_0_TWO_PIXELS_PATTERN} {0}
set_instance_parameter_value alt_vip_cl_cps_0 {INPUT_0_PATTERN} {C0,C1}
set_instance_parameter_value alt_vip_cl_cps_0 {INPUT_1_FIFO} {0}
set_instance_parameter_value alt_vip_cl_cps_0 {INPUT_1_FIFO_SIZE} {8}
set_instance_parameter_value alt_vip_cl_cps_0 {INPUT_1_NUMBER_OF_COLOR_PLANES} {3}
set_instance_parameter_value alt_vip_cl_cps_0 {INPUT_1_COLOR_PLANES_ARE_IN_PARALLEL} {1}
set_instance_parameter_value alt_vip_cl_cps_0 {INPUT_1_PIXELS_IN_PARALLEL} {1}
set_instance_parameter_value alt_vip_cl_cps_0 {INPUT_1_TWO_PIXELS_PATTERN} {0}
set_instance_parameter_value alt_vip_cl_cps_0 {INPUT_1_PATTERN} {C0,C1,C2}
set_instance_parameter_value alt_vip_cl_cps_0 {OUTPUT_0_FIFO} {0}
set_instance_parameter_value alt_vip_cl_cps_0 {OUTPUT_0_FIFO_SIZE} {8}
set_instance_parameter_value alt_vip_cl_cps_0 {OUTPUT_0_NUMBER_OF_COLOR_PLANES} {2}
set_instance_parameter_value alt_vip_cl_cps_0 {OUTPUT_0_COLOR_PLANES_ARE_IN_PARALLEL} {1}
set_instance_parameter_value alt_vip_cl_cps_0 {OUTPUT_0_PIXELS_IN_PARALLEL} {1}
set_instance_parameter_value alt_vip_cl_cps_0 {OUTPUT_0_TWO_PIXELS_PATTERN} {0}
set_instance_parameter_value alt_vip_cl_cps_0 {OUTPUT_0_PATTERN} {C0,C1}
set_instance_parameter_value alt_vip_cl_cps_0 {OUTPUT_1_FIFO} {0}
set_instance_parameter_value alt_vip_cl_cps_0 {OUTPUT_1_FIFO_SIZE} {8}
set_instance_parameter_value alt_vip_cl_cps_0 {OUTPUT_1_NUMBER_OF_COLOR_PLANES} {3}
set_instance_parameter_value alt_vip_cl_cps_0 {OUTPUT_1_COLOR_PLANES_ARE_IN_PARALLEL} {1}
set_instance_parameter_value alt_vip_cl_cps_0 {OUTPUT_1_PIXELS_IN_PARALLEL} {1}
set_instance_parameter_value alt_vip_cl_cps_0 {OUTPUT_1_TWO_PIXELS_PATTERN} {0}
set_instance_parameter_value alt_vip_cl_cps_0 {OUTPUT_1_PATTERN} {C0,C1,C2}
set_instance_parameter_value alt_vip_cl_cps_0 {USER_PACKET_SUPPORT} {PASSTHROUGH}
set_instance_parameter_value alt_vip_cl_cps_0 {USER_PKT_0_TO_0} {0}
set_instance_parameter_value alt_vip_cl_cps_0 {USER_PKT_1_TO_0} {0}
set_instance_parameter_value alt_vip_cl_cps_0 {USER_PKT_0_TO_1} {0}
set_instance_parameter_value alt_vip_cl_cps_0 {USER_PKT_1_TO_1} {1}
set_instance_parameter_value alt_vip_cl_cps_0 {EXTRA_PIPELINING} {0}
set_instance_parameter_value alt_vip_cl_cps_0 {INPUT_VALIDATION} {1}
set_instance_parameter_value alt_vip_cl_cps_0 {OUTPUT_VALIDATION} {1}

add_instance alt_vip_cl_crs_0 alt_vip_cl_crs 16.1
set_instance_parameter_value alt_vip_cl_crs_0 {SHOW_HIDDEN_FEATURES} {0}
set_instance_parameter_value alt_vip_cl_crs_0 {BITS_PER_SYMBOL} {8}
set_instance_parameter_value alt_vip_cl_crs_0 {NUMBER_OF_COLOR_PLANES} {2}
set_instance_parameter_value alt_vip_cl_crs_0 {COLOR_PLANES_ARE_IN_PARALLEL} {1}
set_instance_parameter_value alt_vip_cl_crs_0 {PIXELS_IN_PARALLEL} {1}
set_instance_parameter_value alt_vip_cl_crs_0 {PIP_IN} {1}
set_instance_parameter_value alt_vip_cl_crs_0 {PIP_OUT} {1}
set_instance_parameter_value alt_vip_cl_crs_0 {MAX_WIDTH} {720}
set_instance_parameter_value alt_vip_cl_crs_0 {MAX_HEIGHT} {576}
set_instance_parameter_value alt_vip_cl_crs_0 {HORIZ_ALGORITHM} {BILINEAR}
set_instance_parameter_value alt_vip_cl_crs_0 {HORIZ_CO_SITING} {LEFT}
set_instance_parameter_value alt_vip_cl_crs_0 {HORIZ_ENABLE_LUMA_ADAPT} {0}
set_instance_parameter_value alt_vip_cl_crs_0 {VERT_ALGORITHM} {BILINEAR}
set_instance_parameter_value alt_vip_cl_crs_0 {VERT_CO_SITING} {TOP}
set_instance_parameter_value alt_vip_cl_crs_0 {VERT_ENABLE_LUMA_ADAPT} {0}
set_instance_parameter_value alt_vip_cl_crs_0 {VARIABLE_SIDE} {NEITHER}
set_instance_parameter_value alt_vip_cl_crs_0 {ENABLE_444_IN} {0}
set_instance_parameter_value alt_vip_cl_crs_0 {ENABLE_422_IN} {1}
set_instance_parameter_value alt_vip_cl_crs_0 {ENABLE_420_IN} {0}
set_instance_parameter_value alt_vip_cl_crs_0 {ENABLE_444_OUT} {1}
set_instance_parameter_value alt_vip_cl_crs_0 {ENABLE_422_OUT} {0}
set_instance_parameter_value alt_vip_cl_crs_0 {ENABLE_420_OUT} {0}
set_instance_parameter_value alt_vip_cl_crs_0 {USER_PACKET_SUPPORT} {PASSTHROUGH}
set_instance_parameter_value alt_vip_cl_crs_0 {USER_PACKET_FIFO_DEPTH} {0}
set_instance_parameter_value alt_vip_cl_crs_0 {PIPELINE_READY} {0}
set_instance_parameter_value alt_vip_cl_crs_0 {LIMITED_READBACK} {0}

add_instance alt_vip_cl_csc_0 alt_vip_cl_csc 16.1
set_instance_parameter_value alt_vip_cl_csc_0 {INPUT_BITS_PER_SYMBOL} {8}
set_instance_parameter_value alt_vip_cl_csc_0 {OUTPUT_BITS_PER_SYMBOL} {8}
set_instance_parameter_value alt_vip_cl_csc_0 {NUMBER_OF_COLOR_PLANES} {3}
set_instance_parameter_value alt_vip_cl_csc_0 {COLOR_PLANES_ARE_IN_PARALLEL} {1}
set_instance_parameter_value alt_vip_cl_csc_0 {PIXELS_IN_PARALLEL} {1}
set_instance_parameter_value alt_vip_cl_csc_0 {REQ_FCOEFF_A0} {2.018}
set_instance_parameter_value alt_vip_cl_csc_0 {REQ_FCOEFF_A1} {-0.391}
set_instance_parameter_value alt_vip_cl_csc_0 {REQ_FCOEFF_A2} {0.0}
set_instance_parameter_value alt_vip_cl_csc_0 {REQ_FCOEFF_B0} {0.0}
set_instance_parameter_value alt_vip_cl_csc_0 {REQ_FCOEFF_B1} {-0.813}
set_instance_parameter_value alt_vip_cl_csc_0 {REQ_FCOEFF_B2} {1.596}
set_instance_parameter_value alt_vip_cl_csc_0 {REQ_FCOEFF_C0} {1.164}
set_instance_parameter_value alt_vip_cl_csc_0 {REQ_FCOEFF_C1} {1.164}
set_instance_parameter_value alt_vip_cl_csc_0 {REQ_FCOEFF_C2} {1.164}
set_instance_parameter_value alt_vip_cl_csc_0 {REQ_FCOEFF_S0} {-276.928}
set_instance_parameter_value alt_vip_cl_csc_0 {REQ_FCOEFF_S1} {135.488}
set_instance_parameter_value alt_vip_cl_csc_0 {REQ_FCOEFF_S2} {-222.912}
set_instance_parameter_value alt_vip_cl_csc_0 {INPUT_DATA_TYPE_SIGNED} {0}
set_instance_parameter_value alt_vip_cl_csc_0 {INPUT_DATA_TYPE_GUARD_BAND} {0}
set_instance_parameter_value alt_vip_cl_csc_0 {INPUT_DATA_TYPE_MIN} {0}
set_instance_parameter_value alt_vip_cl_csc_0 {INPUT_DATA_TYPE_MAX} {255}
set_instance_parameter_value alt_vip_cl_csc_0 {OUTPUT_DATA_TYPE_SIGNED} {0}
set_instance_parameter_value alt_vip_cl_csc_0 {OUTPUT_DATA_TYPE_GUARD_BAND} {0}
set_instance_parameter_value alt_vip_cl_csc_0 {OUTPUT_DATA_TYPE_MIN} {0}
set_instance_parameter_value alt_vip_cl_csc_0 {OUTPUT_DATA_TYPE_MAX} {255}
set_instance_parameter_value alt_vip_cl_csc_0 {COEFFICIENT_SIGNED} {1}
set_instance_parameter_value alt_vip_cl_csc_0 {COEFFICIENT_INT_BITS} {2}
set_instance_parameter_value alt_vip_cl_csc_0 {SUMMAND_SIGNED} {1}
set_instance_parameter_value alt_vip_cl_csc_0 {SUMMAND_INT_BITS} {9}
set_instance_parameter_value alt_vip_cl_csc_0 {COEF_SUM_FRACTION_BITS} {8}
set_instance_parameter_value alt_vip_cl_csc_0 {MOVE_BINARY_POINT_RIGHT} {0}
set_instance_parameter_value alt_vip_cl_csc_0 {REMOVE_FRACTION_METHOD} {1}
set_instance_parameter_value alt_vip_cl_csc_0 {SIGN_TO_UNSIGN_METHOD} {0}
set_instance_parameter_value alt_vip_cl_csc_0 {PIPELINE_DATA_OUTPUT} {1}
set_instance_parameter_value alt_vip_cl_csc_0 {USER_PACKET_SUPPORT} {PASSTHROUGH}
set_instance_parameter_value alt_vip_cl_csc_0 {CONVERSION_MODE} {LSB}
set_instance_parameter_value alt_vip_cl_csc_0 {RUNTIME_CONTROL} {0}
set_instance_parameter_value alt_vip_cl_csc_0 {LIMITED_READBACK} {0}

add_instance alt_vip_cl_dil_0 alt_vip_cl_dil 16.1
set_instance_parameter_value alt_vip_cl_dil_0 {MAX_WIDTH} {720}
set_instance_parameter_value alt_vip_cl_dil_0 {MAX_HEIGHT} {576}
set_instance_parameter_value alt_vip_cl_dil_0 {USER_PACKET_SUPPORT} {PASSTHROUGH}
set_instance_parameter_value alt_vip_cl_dil_0 {USER_PACKET_FIFO_DEPTH} {0}
set_instance_parameter_value alt_vip_cl_dil_0 {PIXELS_IN_PARALLEL} {1}
set_instance_parameter_value alt_vip_cl_dil_0 {BITS_PER_SYMBOL} {8}
set_instance_parameter_value alt_vip_cl_dil_0 {NUMBER_OF_COLOR_PLANES} {2}
set_instance_parameter_value alt_vip_cl_dil_0 {COLOR_PLANES_ARE_IN_PARALLEL} {1}
set_instance_parameter_value alt_vip_cl_dil_0 {IS_422} {1}
set_instance_parameter_value alt_vip_cl_dil_0 {IS_YCBCR} {1}
set_instance_parameter_value alt_vip_cl_dil_0 {DEINTERLACE_ALGORITHM} {BOB}
set_instance_parameter_value alt_vip_cl_dil_0 {MOTION_BLEED} {1}
set_instance_parameter_value alt_vip_cl_dil_0 {RUNTIME_CONTROL} {0}
set_instance_parameter_value alt_vip_cl_dil_0 {MOTION_BPS} {7}
set_instance_parameter_value alt_vip_cl_dil_0 {FIELD_LATENCY} {0}
set_instance_parameter_value alt_vip_cl_dil_0 {BOB_BEHAVIOUR} {FRAME_FOR_FIELD}
set_instance_parameter_value alt_vip_cl_dil_0 {DISABLE_EMBEDDED_STREAM_CLEANER} {0}
set_instance_parameter_value alt_vip_cl_dil_0 {ENABLE_422_PROCESSING_FOR_INTERLACED_VIDEO} {1}
set_instance_parameter_value alt_vip_cl_dil_0 {CADENCE_DETECTION} {0}
set_instance_parameter_value alt_vip_cl_dil_0 {CADENCE_ALGORITHM_NAME} {CADENCE_32_22_VOF}
set_instance_parameter_value alt_vip_cl_dil_0 {CLOCKS_ARE_SEPARATE} {1}
set_instance_parameter_value alt_vip_cl_dil_0 {MEM_PORT_WIDTH} {32}
set_instance_parameter_value alt_vip_cl_dil_0 {WRITE_MASTER_FIFO_DEPTH} {64}
set_instance_parameter_value alt_vip_cl_dil_0 {WRITE_MASTER_BURST_TARGET} {32}
set_instance_parameter_value alt_vip_cl_dil_0 {EDI_READ_MASTER_FIFO_DEPTH} {64}
set_instance_parameter_value alt_vip_cl_dil_0 {EDI_READ_MASTER_BURST_TARGET} {32}
set_instance_parameter_value alt_vip_cl_dil_0 {MA_READ_MASTER_FIFO_DEPTH} {64}
set_instance_parameter_value alt_vip_cl_dil_0 {MA_READ_MASTER_BURST_TARGET} {32}
set_instance_parameter_value alt_vip_cl_dil_0 {MOTION_WRITE_MASTER_FIFO_DEPTH} {64}
set_instance_parameter_value alt_vip_cl_dil_0 {MOTION_WRITE_MASTER_BURST_TARGET} {32}
set_instance_parameter_value alt_vip_cl_dil_0 {MOTION_READ_MASTER_FIFO_DEPTH} {64}
set_instance_parameter_value alt_vip_cl_dil_0 {MOTION_READ_MASTER_BURST_TARGET} {32}
set_instance_parameter_value alt_vip_cl_dil_0 {MEM_BASE_ADDR} {0}
set_instance_parameter_value alt_vip_cl_dil_0 {USER_PACKETS_MAX_STORAGE} {0}
set_instance_parameter_value alt_vip_cl_dil_0 {MAX_SYMBOLS_PER_PACKET} {10}

add_instance alt_vip_cl_scl_0 alt_vip_cl_scl 16.1
set_instance_parameter_value alt_vip_cl_scl_0 {SYMBOLS_IN_SEQ} {1}
set_instance_parameter_value alt_vip_cl_scl_0 {SYMBOLS_IN_PAR} {3}
set_instance_parameter_value alt_vip_cl_scl_0 {BITS_PER_SYMBOL} {8}
set_instance_parameter_value alt_vip_cl_scl_0 {PIXELS_IN_PARALLEL} {1}
set_instance_parameter_value alt_vip_cl_scl_0 {EXTRA_PIPELINING} {0}
set_instance_parameter_value alt_vip_cl_scl_0 {IS_422} {0}
set_instance_parameter_value alt_vip_cl_scl_0 {NO_BLANKING} {0}
set_instance_parameter_value alt_vip_cl_scl_0 {MAX_IN_WIDTH} {640}
set_instance_parameter_value alt_vip_cl_scl_0 {MAX_IN_HEIGHT} {480}
set_instance_parameter_value alt_vip_cl_scl_0 {MAX_OUT_WIDTH} {270}
set_instance_parameter_value alt_vip_cl_scl_0 {MAX_OUT_HEIGHT} {200}
set_instance_parameter_value alt_vip_cl_scl_0 {RUNTIME_CONTROL} {0}
set_instance_parameter_value alt_vip_cl_scl_0 {ALGORITHM_NAME} {POLYPHASE}
set_instance_parameter_value alt_vip_cl_scl_0 {DEFAULT_EDGE_THRESH} {7}
set_instance_parameter_value alt_vip_cl_scl_0 {ARE_IDENTICAL} {1}
set_instance_parameter_value alt_vip_cl_scl_0 {V_TAPS} {8}
set_instance_parameter_value alt_vip_cl_scl_0 {V_PHASES} {16}
set_instance_parameter_value alt_vip_cl_scl_0 {H_TAPS} {8}
set_instance_parameter_value alt_vip_cl_scl_0 {H_PHASES} {16}
set_instance_parameter_value alt_vip_cl_scl_0 {V_SIGNED} {1}
set_instance_parameter_value alt_vip_cl_scl_0 {V_INTEGER_BITS} {1}
set_instance_parameter_value alt_vip_cl_scl_0 {V_FRACTION_BITS} {7}
set_instance_parameter_value alt_vip_cl_scl_0 {H_SIGNED} {1}
set_instance_parameter_value alt_vip_cl_scl_0 {H_INTEGER_BITS} {1}
set_instance_parameter_value alt_vip_cl_scl_0 {H_FRACTION_BITS} {7}
set_instance_parameter_value alt_vip_cl_scl_0 {PRESERVE_BITS} {0}
set_instance_parameter_value alt_vip_cl_scl_0 {LOAD_AT_RUNTIME} {0}
set_instance_parameter_value alt_vip_cl_scl_0 {V_BANKS} {1}
set_instance_parameter_value alt_vip_cl_scl_0 {V_FUNCTION} {LANCZOS_2}
set_instance_parameter_value alt_vip_cl_scl_0 {V_COEFF_FILE} {<enter file name (including full path)>}
set_instance_parameter_value alt_vip_cl_scl_0 {H_BANKS} {1}
set_instance_parameter_value alt_vip_cl_scl_0 {H_FUNCTION} {LANCZOS_2}
set_instance_parameter_value alt_vip_cl_scl_0 {H_COEFF_FILE} {<enter file name (including full path)>}
set_instance_parameter_value alt_vip_cl_scl_0 {USER_PACKET_SUPPORT} {PASSTHROUGH}
set_instance_parameter_value alt_vip_cl_scl_0 {USER_PACKET_FIFO_DEPTH} {0}
set_instance_parameter_value alt_vip_cl_scl_0 {LIMITED_READBACK} {0}
set_instance_parameter_value alt_vip_cl_scl_0 {IS_420} {0}
set_instance_parameter_value alt_vip_cl_scl_0 {ALWAYS_DOWNSCALE} {1}
set_instance_parameter_value alt_vip_cl_scl_0 {DEFAULT_UPPER_BLUR} {15}
set_instance_parameter_value alt_vip_cl_scl_0 {DEFAULT_LOWER_BLUR} {0}
set_instance_parameter_value alt_vip_cl_scl_0 {ENABLE_FIR} {0}
set_instance_parameter_value alt_vip_cl_scl_0 {V_SYMMETRIC} {0}
set_instance_parameter_value alt_vip_cl_scl_0 {H_SYMMETRIC} {0}

add_instance alt_vip_cl_vfb_0 alt_vip_cl_vfb 16.1
set_instance_parameter_value alt_vip_cl_vfb_0 {BITS_PER_SYMBOL} {8}
set_instance_parameter_value alt_vip_cl_vfb_0 {NUMBER_OF_COLOR_PLANES} {3}
set_instance_parameter_value alt_vip_cl_vfb_0 {COLOR_PLANES_ARE_IN_PARALLEL} {1}
set_instance_parameter_value alt_vip_cl_vfb_0 {PIXELS_IN_PARALLEL} {1}
set_instance_parameter_value alt_vip_cl_vfb_0 {READY_LATENCY} {1}
set_instance_parameter_value alt_vip_cl_vfb_0 {MAX_WIDTH} {270}
set_instance_parameter_value alt_vip_cl_vfb_0 {MAX_HEIGHT} {200}
set_instance_parameter_value alt_vip_cl_vfb_0 {CLOCKS_ARE_SEPARATE} {1}
set_instance_parameter_value alt_vip_cl_vfb_0 {MEM_PORT_WIDTH} {32}
set_instance_parameter_value alt_vip_cl_vfb_0 {MEM_BASE_ADDR} {0}
set_instance_parameter_value alt_vip_cl_vfb_0 {USE_BUFFER_OFFSET} {0}
set_instance_parameter_value alt_vip_cl_vfb_0 {MEM_BUFFER_OFFSET} {16777216}
set_instance_parameter_value alt_vip_cl_vfb_0 {BURST_ALIGNMENT} {1}
set_instance_parameter_value alt_vip_cl_vfb_0 {WRITE_FIFO_DEPTH} {256}
set_instance_parameter_value alt_vip_cl_vfb_0 {WRITE_BURST_TARGET} {4}
set_instance_parameter_value alt_vip_cl_vfb_0 {READ_FIFO_DEPTH} {256}
set_instance_parameter_value alt_vip_cl_vfb_0 {READ_BURST_TARGET} {4}
set_instance_parameter_value alt_vip_cl_vfb_0 {WRITER_RUNTIME_CONTROL} {0}
set_instance_parameter_value alt_vip_cl_vfb_0 {READER_RUNTIME_CONTROL} {0}
set_instance_parameter_value alt_vip_cl_vfb_0 {IS_FRAME_WRITER} {0}
set_instance_parameter_value alt_vip_cl_vfb_0 {IS_FRAME_READER} {0}
set_instance_parameter_value alt_vip_cl_vfb_0 {DROP_FRAMES} {0}
set_instance_parameter_value alt_vip_cl_vfb_0 {REPEAT_FRAMES} {0}
set_instance_parameter_value alt_vip_cl_vfb_0 {DROP_REPEAT_USER} {0}
set_instance_parameter_value alt_vip_cl_vfb_0 {INTERLACED_SUPPORT} {0}
set_instance_parameter_value alt_vip_cl_vfb_0 {CONTROLLED_DROP_REPEAT} {0}
set_instance_parameter_value alt_vip_cl_vfb_0 {DROP_INVALID_FIELDS} {0}
set_instance_parameter_value alt_vip_cl_vfb_0 {MULTI_FRAME_DELAY} {1}
set_instance_parameter_value alt_vip_cl_vfb_0 {IS_SYNC_MASTER} {0}
set_instance_parameter_value alt_vip_cl_vfb_0 {IS_SYNC_SLAVE} {0}
set_instance_parameter_value alt_vip_cl_vfb_0 {USER_PACKETS_MAX_STORAGE} {0}
set_instance_parameter_value alt_vip_cl_vfb_0 {MAX_SYMBOLS_PER_PACKET} {10}
set_instance_parameter_value alt_vip_cl_vfb_0 {TEST_INIT} {0}

add_instance alt_vip_cti_0 alt_vip_cti 14.0
set_instance_parameter_value alt_vip_cti_0 {BPS} {8}
set_instance_parameter_value alt_vip_cti_0 {NUMBER_OF_COLOUR_PLANES} {2}
set_instance_parameter_value alt_vip_cti_0 {COLOUR_PLANES_ARE_IN_PARALLEL} {0}
set_instance_parameter_value alt_vip_cti_0 {SYNC_TO} {0}
set_instance_parameter_value alt_vip_cti_0 {USE_EMBEDDED_SYNCS} {1}
set_instance_parameter_value alt_vip_cti_0 {ADD_DATA_ENABLE_SIGNAL} {0}
set_instance_parameter_value alt_vip_cti_0 {ACCEPT_COLOURS_IN_SEQ} {0}
set_instance_parameter_value alt_vip_cti_0 {USE_STD} {0}
set_instance_parameter_value alt_vip_cti_0 {STD_WIDTH} {1}
set_instance_parameter_value alt_vip_cti_0 {GENERATE_ANC} {0}
set_instance_parameter_value alt_vip_cti_0 {INTERLACED} {1}
set_instance_parameter_value alt_vip_cti_0 {H_ACTIVE_PIXELS_F0} {720}
set_instance_parameter_value alt_vip_cti_0 {V_ACTIVE_LINES_F0} {288}
set_instance_parameter_value alt_vip_cti_0 {V_ACTIVE_LINES_F1} {288}
set_instance_parameter_value alt_vip_cti_0 {FIFO_DEPTH} {1440}
set_instance_parameter_value alt_vip_cti_0 {CLOCKS_ARE_SAME} {0}
set_instance_parameter_value alt_vip_cti_0 {USE_CONTROL} {0}
set_instance_parameter_value alt_vip_cti_0 {GENERATE_SYNC} {0}

add_instance clk_50 clock_source 16.1
set_instance_parameter_value clk_50 {clockFrequency} {50000000.0}
set_instance_parameter_value clk_50 {clockFrequencyKnown} {1}
set_instance_parameter_value clk_50 {resetSynchronousEdges} {NONE}

add_instance clk_vip clock_source 16.1
set_instance_parameter_value clk_vip {clockFrequency} {100000000.0}
set_instance_parameter_value clk_vip {clockFrequencyKnown} {1}
set_instance_parameter_value clk_vip {resetSynchronousEdges} {NONE}

add_instance pll_sys altera_pll 16.1
set_instance_parameter_value pll_sys {debug_print_output} {0}
set_instance_parameter_value pll_sys {debug_use_rbc_taf_method} {0}
set_instance_parameter_value pll_sys {gui_device_speed_grade} {2}
set_instance_parameter_value pll_sys {gui_pll_mode} {Integer-N PLL}
set_instance_parameter_value pll_sys {gui_reference_clock_frequency} {50.0}
set_instance_parameter_value pll_sys {gui_channel_spacing} {0.0}
set_instance_parameter_value pll_sys {gui_operation_mode} {normal}
set_instance_parameter_value pll_sys {gui_feedback_clock} {Global Clock}
set_instance_parameter_value pll_sys {gui_fractional_cout} {32}
set_instance_parameter_value pll_sys {gui_dsm_out_sel} {1st_order}
set_instance_parameter_value pll_sys {gui_use_locked} {1}
set_instance_parameter_value pll_sys {gui_en_adv_params} {0}
set_instance_parameter_value pll_sys {gui_number_of_clocks} {2}
set_instance_parameter_value pll_sys {gui_multiply_factor} {1}
set_instance_parameter_value pll_sys {gui_frac_multiply_factor} {1.0}
set_instance_parameter_value pll_sys {gui_divide_factor_n} {1}
set_instance_parameter_value pll_sys {gui_cascade_counter0} {0}
set_instance_parameter_value pll_sys {gui_output_clock_frequency0} {120.0}
set_instance_parameter_value pll_sys {gui_divide_factor_c0} {1}
set_instance_parameter_value pll_sys {gui_actual_output_clock_frequency0} {0 MHz}
set_instance_parameter_value pll_sys {gui_ps_units0} {ps}
set_instance_parameter_value pll_sys {gui_phase_shift0} {0}
set_instance_parameter_value pll_sys {gui_phase_shift_deg0} {0.0}
set_instance_parameter_value pll_sys {gui_actual_phase_shift0} {0}
set_instance_parameter_value pll_sys {gui_duty_cycle0} {50}
set_instance_parameter_value pll_sys {gui_cascade_counter1} {0}
set_instance_parameter_value pll_sys {gui_output_clock_frequency1} {120.0}
set_instance_parameter_value pll_sys {gui_divide_factor_c1} {1}
set_instance_parameter_value pll_sys {gui_actual_output_clock_frequency1} {0 MHz}
set_instance_parameter_value pll_sys {gui_ps_units1} {degrees}
set_instance_parameter_value pll_sys {gui_phase_shift1} {7500}
set_instance_parameter_value pll_sys {gui_phase_shift_deg1} {-90.0}
set_instance_parameter_value pll_sys {gui_actual_phase_shift1} {0}
set_instance_parameter_value pll_sys {gui_duty_cycle1} {50}
set_instance_parameter_value pll_sys {gui_cascade_counter2} {0}
set_instance_parameter_value pll_sys {gui_output_clock_frequency2} {10.0}
set_instance_parameter_value pll_sys {gui_divide_factor_c2} {1}
set_instance_parameter_value pll_sys {gui_actual_output_clock_frequency2} {0 MHz}
set_instance_parameter_value pll_sys {gui_ps_units2} {ps}
set_instance_parameter_value pll_sys {gui_phase_shift2} {0}
set_instance_parameter_value pll_sys {gui_phase_shift_deg2} {0.0}
set_instance_parameter_value pll_sys {gui_actual_phase_shift2} {0}
set_instance_parameter_value pll_sys {gui_duty_cycle2} {50}
set_instance_parameter_value pll_sys {gui_cascade_counter3} {0}
set_instance_parameter_value pll_sys {gui_output_clock_frequency3} {65.0}
set_instance_parameter_value pll_sys {gui_divide_factor_c3} {1}
set_instance_parameter_value pll_sys {gui_actual_output_clock_frequency3} {0 MHz}
set_instance_parameter_value pll_sys {gui_ps_units3} {ps}
set_instance_parameter_value pll_sys {gui_phase_shift3} {0}
set_instance_parameter_value pll_sys {gui_phase_shift_deg3} {0.0}
set_instance_parameter_value pll_sys {gui_actual_phase_shift3} {0}
set_instance_parameter_value pll_sys {gui_duty_cycle3} {50}
set_instance_parameter_value pll_sys {gui_cascade_counter4} {0}
set_instance_parameter_value pll_sys {gui_output_clock_frequency4} {40.0}
set_instance_parameter_value pll_sys {gui_divide_factor_c4} {1}
set_instance_parameter_value pll_sys {gui_actual_output_clock_frequency4} {0 MHz}
set_instance_parameter_value pll_sys {gui_ps_units4} {ps}
set_instance_parameter_value pll_sys {gui_phase_shift4} {0}
set_instance_parameter_value pll_sys {gui_phase_shift_deg4} {0.0}
set_instance_parameter_value pll_sys {gui_actual_phase_shift4} {0}
set_instance_parameter_value pll_sys {gui_duty_cycle4} {50}
set_instance_parameter_value pll_sys {gui_cascade_counter5} {0}
set_instance_parameter_value pll_sys {gui_output_clock_frequency5} {100.0}
set_instance_parameter_value pll_sys {gui_divide_factor_c5} {1}
set_instance_parameter_value pll_sys {gui_actual_output_clock_frequency5} {0 MHz}
set_instance_parameter_value pll_sys {gui_ps_units5} {ps}
set_instance_parameter_value pll_sys {gui_phase_shift5} {0}
set_instance_parameter_value pll_sys {gui_phase_shift_deg5} {0.0}
set_instance_parameter_value pll_sys {gui_actual_phase_shift5} {0}
set_instance_parameter_value pll_sys {gui_duty_cycle5} {50}
set_instance_parameter_value pll_sys {gui_cascade_counter6} {0}
set_instance_parameter_value pll_sys {gui_output_clock_frequency6} {100.0}
set_instance_parameter_value pll_sys {gui_divide_factor_c6} {1}
set_instance_parameter_value pll_sys {gui_actual_output_clock_frequency6} {0 MHz}
set_instance_parameter_value pll_sys {gui_ps_units6} {ps}
set_instance_parameter_value pll_sys {gui_phase_shift6} {0}
set_instance_parameter_value pll_sys {gui_phase_shift_deg6} {0.0}
set_instance_parameter_value pll_sys {gui_actual_phase_shift6} {0}
set_instance_parameter_value pll_sys {gui_duty_cycle6} {50}
set_instance_parameter_value pll_sys {gui_cascade_counter7} {0}
set_instance_parameter_value pll_sys {gui_output_clock_frequency7} {100.0}
set_instance_parameter_value pll_sys {gui_divide_factor_c7} {1}
set_instance_parameter_value pll_sys {gui_actual_output_clock_frequency7} {0 MHz}
set_instance_parameter_value pll_sys {gui_ps_units7} {ps}
set_instance_parameter_value pll_sys {gui_phase_shift7} {0}
set_instance_parameter_value pll_sys {gui_phase_shift_deg7} {0.0}
set_instance_parameter_value pll_sys {gui_actual_phase_shift7} {0}
set_instance_parameter_value pll_sys {gui_duty_cycle7} {50}
set_instance_parameter_value pll_sys {gui_cascade_counter8} {0}
set_instance_parameter_value pll_sys {gui_output_clock_frequency8} {100.0}
set_instance_parameter_value pll_sys {gui_divide_factor_c8} {1}
set_instance_parameter_value pll_sys {gui_actual_output_clock_frequency8} {0 MHz}
set_instance_parameter_value pll_sys {gui_ps_units8} {ps}
set_instance_parameter_value pll_sys {gui_phase_shift8} {0}
set_instance_parameter_value pll_sys {gui_phase_shift_deg8} {0.0}
set_instance_parameter_value pll_sys {gui_actual_phase_shift8} {0}
set_instance_parameter_value pll_sys {gui_duty_cycle8} {50}
set_instance_parameter_value pll_sys {gui_cascade_counter9} {0}
set_instance_parameter_value pll_sys {gui_output_clock_frequency9} {100.0}
set_instance_parameter_value pll_sys {gui_divide_factor_c9} {1}
set_instance_parameter_value pll_sys {gui_actual_output_clock_frequency9} {0 MHz}
set_instance_parameter_value pll_sys {gui_ps_units9} {ps}
set_instance_parameter_value pll_sys {gui_phase_shift9} {0}
set_instance_parameter_value pll_sys {gui_phase_shift_deg9} {0.0}
set_instance_parameter_value pll_sys {gui_actual_phase_shift9} {0}
set_instance_parameter_value pll_sys {gui_duty_cycle9} {50}
set_instance_parameter_value pll_sys {gui_cascade_counter10} {0}
set_instance_parameter_value pll_sys {gui_output_clock_frequency10} {100.0}
set_instance_parameter_value pll_sys {gui_divide_factor_c10} {1}
set_instance_parameter_value pll_sys {gui_actual_output_clock_frequency10} {0 MHz}
set_instance_parameter_value pll_sys {gui_ps_units10} {ps}
set_instance_parameter_value pll_sys {gui_phase_shift10} {0}
set_instance_parameter_value pll_sys {gui_phase_shift_deg10} {0.0}
set_instance_parameter_value pll_sys {gui_actual_phase_shift10} {0}
set_instance_parameter_value pll_sys {gui_duty_cycle10} {50}
set_instance_parameter_value pll_sys {gui_cascade_counter11} {0}
set_instance_parameter_value pll_sys {gui_output_clock_frequency11} {100.0}
set_instance_parameter_value pll_sys {gui_divide_factor_c11} {1}
set_instance_parameter_value pll_sys {gui_actual_output_clock_frequency11} {0 MHz}
set_instance_parameter_value pll_sys {gui_ps_units11} {ps}
set_instance_parameter_value pll_sys {gui_phase_shift11} {0}
set_instance_parameter_value pll_sys {gui_phase_shift_deg11} {0.0}
set_instance_parameter_value pll_sys {gui_actual_phase_shift11} {0}
set_instance_parameter_value pll_sys {gui_duty_cycle11} {50}
set_instance_parameter_value pll_sys {gui_cascade_counter12} {0}
set_instance_parameter_value pll_sys {gui_output_clock_frequency12} {100.0}
set_instance_parameter_value pll_sys {gui_divide_factor_c12} {1}
set_instance_parameter_value pll_sys {gui_actual_output_clock_frequency12} {0 MHz}
set_instance_parameter_value pll_sys {gui_ps_units12} {ps}
set_instance_parameter_value pll_sys {gui_phase_shift12} {0}
set_instance_parameter_value pll_sys {gui_phase_shift_deg12} {0.0}
set_instance_parameter_value pll_sys {gui_actual_phase_shift12} {0}
set_instance_parameter_value pll_sys {gui_duty_cycle12} {50}
set_instance_parameter_value pll_sys {gui_cascade_counter13} {0}
set_instance_parameter_value pll_sys {gui_output_clock_frequency13} {100.0}
set_instance_parameter_value pll_sys {gui_divide_factor_c13} {1}
set_instance_parameter_value pll_sys {gui_actual_output_clock_frequency13} {0 MHz}
set_instance_parameter_value pll_sys {gui_ps_units13} {ps}
set_instance_parameter_value pll_sys {gui_phase_shift13} {0}
set_instance_parameter_value pll_sys {gui_phase_shift_deg13} {0.0}
set_instance_parameter_value pll_sys {gui_actual_phase_shift13} {0}
set_instance_parameter_value pll_sys {gui_duty_cycle13} {50}
set_instance_parameter_value pll_sys {gui_cascade_counter14} {0}
set_instance_parameter_value pll_sys {gui_output_clock_frequency14} {100.0}
set_instance_parameter_value pll_sys {gui_divide_factor_c14} {1}
set_instance_parameter_value pll_sys {gui_actual_output_clock_frequency14} {0 MHz}
set_instance_parameter_value pll_sys {gui_ps_units14} {ps}
set_instance_parameter_value pll_sys {gui_phase_shift14} {0}
set_instance_parameter_value pll_sys {gui_phase_shift_deg14} {0.0}
set_instance_parameter_value pll_sys {gui_actual_phase_shift14} {0}
set_instance_parameter_value pll_sys {gui_duty_cycle14} {50}
set_instance_parameter_value pll_sys {gui_cascade_counter15} {0}
set_instance_parameter_value pll_sys {gui_output_clock_frequency15} {100.0}
set_instance_parameter_value pll_sys {gui_divide_factor_c15} {1}
set_instance_parameter_value pll_sys {gui_actual_output_clock_frequency15} {0 MHz}
set_instance_parameter_value pll_sys {gui_ps_units15} {ps}
set_instance_parameter_value pll_sys {gui_phase_shift15} {0}
set_instance_parameter_value pll_sys {gui_phase_shift_deg15} {0.0}
set_instance_parameter_value pll_sys {gui_actual_phase_shift15} {0}
set_instance_parameter_value pll_sys {gui_duty_cycle15} {50}
set_instance_parameter_value pll_sys {gui_cascade_counter16} {0}
set_instance_parameter_value pll_sys {gui_output_clock_frequency16} {100.0}
set_instance_parameter_value pll_sys {gui_divide_factor_c16} {1}
set_instance_parameter_value pll_sys {gui_actual_output_clock_frequency16} {0 MHz}
set_instance_parameter_value pll_sys {gui_ps_units16} {ps}
set_instance_parameter_value pll_sys {gui_phase_shift16} {0}
set_instance_parameter_value pll_sys {gui_phase_shift_deg16} {0.0}
set_instance_parameter_value pll_sys {gui_actual_phase_shift16} {0}
set_instance_parameter_value pll_sys {gui_duty_cycle16} {50}
set_instance_parameter_value pll_sys {gui_cascade_counter17} {0}
set_instance_parameter_value pll_sys {gui_output_clock_frequency17} {100.0}
set_instance_parameter_value pll_sys {gui_divide_factor_c17} {1}
set_instance_parameter_value pll_sys {gui_actual_output_clock_frequency17} {0 MHz}
set_instance_parameter_value pll_sys {gui_ps_units17} {ps}
set_instance_parameter_value pll_sys {gui_phase_shift17} {0}
set_instance_parameter_value pll_sys {gui_phase_shift_deg17} {0.0}
set_instance_parameter_value pll_sys {gui_actual_phase_shift17} {0}
set_instance_parameter_value pll_sys {gui_duty_cycle17} {50}
set_instance_parameter_value pll_sys {gui_pll_auto_reset} {Off}
set_instance_parameter_value pll_sys {gui_pll_bandwidth_preset} {Auto}
set_instance_parameter_value pll_sys {gui_en_reconf} {0}
set_instance_parameter_value pll_sys {gui_en_dps_ports} {0}
set_instance_parameter_value pll_sys {gui_en_phout_ports} {0}
set_instance_parameter_value pll_sys {gui_phout_division} {1}
set_instance_parameter_value pll_sys {gui_mif_generate} {0}
set_instance_parameter_value pll_sys {gui_enable_mif_dps} {0}
set_instance_parameter_value pll_sys {gui_dps_cntr} {C0}
set_instance_parameter_value pll_sys {gui_dps_num} {1}
set_instance_parameter_value pll_sys {gui_dps_dir} {Positive}
set_instance_parameter_value pll_sys {gui_refclk_switch} {0}
set_instance_parameter_value pll_sys {gui_refclk1_frequency} {100.0}
set_instance_parameter_value pll_sys {gui_switchover_mode} {Automatic Switchover}
set_instance_parameter_value pll_sys {gui_switchover_delay} {0}
set_instance_parameter_value pll_sys {gui_active_clk} {0}
set_instance_parameter_value pll_sys {gui_clk_bad} {0}
set_instance_parameter_value pll_sys {gui_enable_cascade_out} {0}
set_instance_parameter_value pll_sys {gui_cascade_outclk_index} {0}
set_instance_parameter_value pll_sys {gui_enable_cascade_in} {0}
set_instance_parameter_value pll_sys {gui_pll_cascading_mode} {Create an adjpllin signal to connect with an upstream PLL}

add_instance sdram altera_avalon_new_sdram_controller 16.1
set_instance_parameter_value sdram {TAC} {5.5}
set_instance_parameter_value sdram {TRCD} {20.0}
set_instance_parameter_value sdram {TRFC} {70.0}
set_instance_parameter_value sdram {TRP} {20.0}
set_instance_parameter_value sdram {TWR} {14.0}
set_instance_parameter_value sdram {casLatency} {3}
set_instance_parameter_value sdram {columnWidth} {10}
set_instance_parameter_value sdram {dataWidth} {16}
set_instance_parameter_value sdram {generateSimulationModel} {1}
set_instance_parameter_value sdram {initRefreshCommands} {2}
set_instance_parameter_value sdram {model} {custom}
set_instance_parameter_value sdram {numberOfBanks} {4}
set_instance_parameter_value sdram {numberOfChipSelects} {1}
set_instance_parameter_value sdram {pinsSharedViaTriState} {0}
set_instance_parameter_value sdram {powerUpDelay} {100.0}
set_instance_parameter_value sdram {refreshPeriod} {15.625}
set_instance_parameter_value sdram {rowWidth} {13}
set_instance_parameter_value sdram {masteredTristateBridgeSlave} {0}
set_instance_parameter_value sdram {TMRD} {3.0}
set_instance_parameter_value sdram {initNOPDelay} {0.0}
set_instance_parameter_value sdram {registerDataIn} {1}

# exported interfaces
add_interface alt_vip_cl_vfb_0_dout avalon_streaming source
set_interface_property alt_vip_cl_vfb_0_dout EXPORT_OF alt_vip_cl_vfb_0.dout
add_interface alt_vip_cti_0_clocked_video conduit end
set_interface_property alt_vip_cti_0_clocked_video EXPORT_OF alt_vip_cti_0.clocked_video
add_interface clk_50 clock sink
set_interface_property clk_50 EXPORT_OF clk_50.clk_in
add_interface clk_50_reset reset sink
set_interface_property clk_50_reset EXPORT_OF clk_50.clk_in_reset
add_interface clk_sdram clock source
set_interface_property clk_sdram EXPORT_OF pll_sys.outclk1
add_interface sdram_wire conduit end
set_interface_property sdram_wire EXPORT_OF sdram.wire
add_interface vip_clk clock sink
set_interface_property vip_clk EXPORT_OF clk_vip.clk_in

# connections and connection parameters
add_connection alt_vip_cl_vfb_0.mem_master_rd sdram.s1
set_connection_parameter_value alt_vip_cl_vfb_0.mem_master_rd/sdram.s1 arbitrationPriority {1}
set_connection_parameter_value alt_vip_cl_vfb_0.mem_master_rd/sdram.s1 baseAddress {0x0000}
set_connection_parameter_value alt_vip_cl_vfb_0.mem_master_rd/sdram.s1 defaultConnection {0}

add_connection alt_vip_cl_vfb_0.mem_master_wr sdram.s1
set_connection_parameter_value alt_vip_cl_vfb_0.mem_master_wr/sdram.s1 arbitrationPriority {1}
set_connection_parameter_value alt_vip_cl_vfb_0.mem_master_wr/sdram.s1 baseAddress {0x0000}
set_connection_parameter_value alt_vip_cl_vfb_0.mem_master_wr/sdram.s1 defaultConnection {0}

add_connection alt_vip_cl_csc_0.dout alt_vip_cl_clp_0.din

add_connection alt_vip_cl_clp_0.dout alt_vip_cl_scl_0.din

add_connection alt_vip_cl_scl_0.dout alt_vip_cl_vfb_0.din

add_connection alt_vip_cl_dil_0.dout alt_vip_cl_crs_0.din

add_connection alt_vip_cti_0.dout alt_vip_cl_cps_0.din_0

add_connection alt_vip_cl_cps_0.dout_0 alt_vip_cl_dil_0.din

add_connection clk_vip.clk alt_vip_cl_dil_0.av_mm_clock

add_connection clk_vip.clk alt_vip_cl_dil_0.av_st_clock

add_connection clk_vip.clk alt_vip_cti_0.is_clk_rst

add_connection clk_vip.clk alt_vip_cl_csc_0.main_clock

add_connection clk_vip.clk alt_vip_cl_scl_0.main_clock

add_connection clk_vip.clk alt_vip_cl_clp_0.main_clock

add_connection clk_vip.clk alt_vip_cl_cps_0.main_clock

add_connection clk_vip.clk alt_vip_cl_vfb_0.main_clock

add_connection clk_vip.clk alt_vip_cl_crs_0.main_clock

add_connection clk_vip.clk alt_vip_cl_vfb_0.mem_clock

add_connection clk_50.clk pll_sys.refclk

add_connection pll_sys.outclk0 sdram.clk

add_connection clk_50.clk_reset alt_vip_cti_0.is_clk_rst_reset

add_connection clk_50.clk_reset alt_vip_cl_scl_0.main_reset

add_connection clk_50.clk_reset alt_vip_cl_csc_0.main_reset

add_connection clk_50.clk_reset sdram.reset

add_connection clk_50.clk_reset pll_sys.reset

add_connection alt_vip_cl_crs_0.dout alt_vip_cl_csc_0.din

add_connection clk_50.clk_reset alt_vip_cl_vfb_0.main_reset

add_connection clk_50.clk_reset alt_vip_cl_vfb_0.mem_reset

add_connection clk_50.clk_reset clk_vip.clk_in_reset

add_connection clk_50.clk_reset alt_vip_cl_crs_0.main_reset

add_connection clk_50.clk_reset alt_vip_cl_dil_0.av_st_reset

add_connection clk_50.clk_reset alt_vip_cl_dil_0.av_mm_reset

add_connection clk_50.clk_reset alt_vip_cl_cps_0.main_reset

add_connection clk_50.clk_reset alt_vip_cl_clp_0.main_reset

# interconnect requirements
set_interconnect_requirement {$system} {qsys_mm.clockCrossingAdapter} {HANDSHAKE}
set_interconnect_requirement {$system} {qsys_mm.maxAdditionalLatency} {3}

save_system {tv_decoder.qsys}
