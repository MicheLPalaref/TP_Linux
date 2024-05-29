/*
 * system.h - SOPC Builder system and BSP software package information
 *
 * Machine generated for CPU 'nios2_gen2_0' in SOPC Builder design 'DE10_Standard_Qsys'
 * SOPC Builder design path: ../../DE10_Standard_Qsys.sopcinfo
 *
 * Generated: Mon Feb 06 14:30:36 CST 2017
 */

/*
 * DO NOT MODIFY THIS FILE
 *
 * Changing this file will have subtle consequences
 * which will almost certainly lead to a nonfunctioning
 * system. If you do modify this file, be aware that your
 * changes will be overwritten and lost when this file
 * is generated again.
 *
 * DO NOT MODIFY THIS FILE
 */

/*
 * License Agreement
 *
 * Copyright (c) 2008
 * Altera Corporation, San Jose, California, USA.
 * All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * This agreement shall be governed in all respects by the laws of the State
 * of California and by the laws of the United States of America.
 */

#ifndef __SYSTEM_H_
#define __SYSTEM_H_

/* Include definitions from linker script generator */
#include "linker.h"


/*
 * CPU configuration
 *
 */

#define ALT_CPU_ARCHITECTURE "altera_nios2_gen2"
#define ALT_CPU_BIG_ENDIAN 0
#define ALT_CPU_BREAK_ADDR 0x04000820
#define ALT_CPU_CPU_ARCH_NIOS2_R1
#define ALT_CPU_CPU_FREQ 120000000u
#define ALT_CPU_CPU_ID_SIZE 1
#define ALT_CPU_CPU_ID_VALUE 0x00000000
#define ALT_CPU_CPU_IMPLEMENTATION "fast"
#define ALT_CPU_DATA_ADDR_WIDTH 0x1c
#define ALT_CPU_DCACHE_LINE_SIZE 0
#define ALT_CPU_DCACHE_LINE_SIZE_LOG2 0
#define ALT_CPU_DCACHE_SIZE 0
#define ALT_CPU_EXCEPTION_ADDR 0x00000020
#define ALT_CPU_FLASH_ACCELERATOR_LINES 0
#define ALT_CPU_FLASH_ACCELERATOR_LINE_SIZE 0
#define ALT_CPU_FLUSHDA_SUPPORTED
#define ALT_CPU_FREQ 120000000
#define ALT_CPU_HARDWARE_DIVIDE_PRESENT 0
#define ALT_CPU_HARDWARE_MULTIPLY_PRESENT 1
#define ALT_CPU_HARDWARE_MULX_PRESENT 0
#define ALT_CPU_HAS_DEBUG_CORE 1
#define ALT_CPU_HAS_DEBUG_STUB
#define ALT_CPU_HAS_EXTRA_EXCEPTION_INFO
#define ALT_CPU_HAS_ILLEGAL_INSTRUCTION_EXCEPTION
#define ALT_CPU_HAS_JMPI_INSTRUCTION
#define ALT_CPU_ICACHE_LINE_SIZE 32
#define ALT_CPU_ICACHE_LINE_SIZE_LOG2 5
#define ALT_CPU_ICACHE_SIZE 4096
#define ALT_CPU_INST_ADDR_WIDTH 0x1b
#define ALT_CPU_NAME "nios2_gen2_0"
#define ALT_CPU_NUM_OF_SHADOW_REG_SETS 0
#define ALT_CPU_OCI_VERSION 1
#define ALT_CPU_RESET_ADDR 0x00000000


/*
 * CPU configuration (with legacy prefix - don't use these anymore)
 *
 */

#define NIOS2_BIG_ENDIAN 0
#define NIOS2_BREAK_ADDR 0x04000820
#define NIOS2_CPU_ARCH_NIOS2_R1
#define NIOS2_CPU_FREQ 120000000u
#define NIOS2_CPU_ID_SIZE 1
#define NIOS2_CPU_ID_VALUE 0x00000000
#define NIOS2_CPU_IMPLEMENTATION "fast"
#define NIOS2_DATA_ADDR_WIDTH 0x1c
#define NIOS2_DCACHE_LINE_SIZE 0
#define NIOS2_DCACHE_LINE_SIZE_LOG2 0
#define NIOS2_DCACHE_SIZE 0
#define NIOS2_EXCEPTION_ADDR 0x00000020
#define NIOS2_FLASH_ACCELERATOR_LINES 0
#define NIOS2_FLASH_ACCELERATOR_LINE_SIZE 0
#define NIOS2_FLUSHDA_SUPPORTED
#define NIOS2_HARDWARE_DIVIDE_PRESENT 0
#define NIOS2_HARDWARE_MULTIPLY_PRESENT 1
#define NIOS2_HARDWARE_MULX_PRESENT 0
#define NIOS2_HAS_DEBUG_CORE 1
#define NIOS2_HAS_DEBUG_STUB
#define NIOS2_HAS_EXTRA_EXCEPTION_INFO
#define NIOS2_HAS_ILLEGAL_INSTRUCTION_EXCEPTION
#define NIOS2_HAS_JMPI_INSTRUCTION
#define NIOS2_ICACHE_LINE_SIZE 32
#define NIOS2_ICACHE_LINE_SIZE_LOG2 5
#define NIOS2_ICACHE_SIZE 4096
#define NIOS2_INST_ADDR_WIDTH 0x1b
#define NIOS2_NUM_OF_SHADOW_REG_SETS 0
#define NIOS2_OCI_VERSION 1
#define NIOS2_RESET_ADDR 0x00000000


/*
 * Define for each module class mastered by the CPU
 *
 */

#define __ALTERA_AVALON_JTAG_UART
#define __ALTERA_AVALON_NEW_SDRAM_CONTROLLER
#define __ALTERA_AVALON_ONCHIP_MEMORY2
#define __ALTERA_AVALON_PIO
#define __ALTERA_AVALON_SYSID_QSYS
#define __ALTERA_AVALON_TIMER
#define __ALTERA_NIOS2_GEN2
#define __ALT_VIP_CL_CLP
#define __ALT_VIP_CL_MIXER
#define __ALT_VIP_CL_SCL
#define __ALT_VIP_CTS
#define __ALT_VIP_VFR
#define __AUDIO_AVALON_CONTROLLER
#define __I2C_OPENCORES


/*
 * System configuration
 *
 */

#define ALT_DEVICE_FAMILY "Cyclone V"
#define ALT_ENHANCED_INTERRUPT_API_PRESENT
#define ALT_IRQ_BASE NULL
#define ALT_LOG_PORT "/dev/null"
#define ALT_LOG_PORT_BASE 0x0
#define ALT_LOG_PORT_DEV null
#define ALT_LOG_PORT_TYPE ""
#define ALT_NUM_EXTERNAL_INTERRUPT_CONTROLLERS 0
#define ALT_NUM_INTERNAL_INTERRUPT_CONTROLLERS 1
#define ALT_NUM_INTERRUPT_CONTROLLERS 1
#define ALT_STDERR "/dev/jtag_uart"
#define ALT_STDERR_BASE 0x94016d0
#define ALT_STDERR_DEV jtag_uart
#define ALT_STDERR_IS_JTAG_UART
#define ALT_STDERR_PRESENT
#define ALT_STDERR_TYPE "altera_avalon_jtag_uart"
#define ALT_STDIN "/dev/jtag_uart"
#define ALT_STDIN_BASE 0x94016d0
#define ALT_STDIN_DEV jtag_uart
#define ALT_STDIN_IS_JTAG_UART
#define ALT_STDIN_PRESENT
#define ALT_STDIN_TYPE "altera_avalon_jtag_uart"
#define ALT_STDOUT "/dev/jtag_uart"
#define ALT_STDOUT_BASE 0x94016d0
#define ALT_STDOUT_DEV jtag_uart
#define ALT_STDOUT_IS_JTAG_UART
#define ALT_STDOUT_PRESENT
#define ALT_STDOUT_TYPE "altera_avalon_jtag_uart"
#define ALT_SYSTEM_NAME "DE10_Standard_Qsys"


/*
 * alt_vip_cl_mixer_0 configuration
 *
 */

#define ALT_MODULE_CLASS_alt_vip_cl_mixer_0 alt_vip_cl_mixer
#define ALT_VIP_CL_MIXER_0_BASE 0x9401000
#define ALT_VIP_CL_MIXER_0_IRQ -1
#define ALT_VIP_CL_MIXER_0_IRQ_INTERRUPT_CONTROLLER_ID -1
#define ALT_VIP_CL_MIXER_0_NAME "/dev/alt_vip_cl_mixer_0"
#define ALT_VIP_CL_MIXER_0_SPAN 512
#define ALT_VIP_CL_MIXER_0_TYPE "alt_vip_cl_mixer"


/*
 * alt_vip_clip_0 configuration
 *
 */

#define ALT_MODULE_CLASS_alt_vip_clip_0 alt_vip_cl_clp
#define ALT_VIP_CLIP_0_BASE 0x9401580
#define ALT_VIP_CLIP_0_IRQ -1
#define ALT_VIP_CLIP_0_IRQ_INTERRUPT_CONTROLLER_ID -1
#define ALT_VIP_CLIP_0_NAME "/dev/alt_vip_clip_0"
#define ALT_VIP_CLIP_0_SPAN 32
#define ALT_VIP_CLIP_0_TYPE "alt_vip_cl_clp"


/*
 * alt_vip_cts_0 configuration
 *
 */

#define ALT_MODULE_CLASS_alt_vip_cts_0 alt_vip_cts
#define ALT_VIP_CTS_0_BASE 0x9401300
#define ALT_VIP_CTS_0_IRQ 6
#define ALT_VIP_CTS_0_IRQ_INTERRUPT_CONTROLLER_ID 0
#define ALT_VIP_CTS_0_NAME "/dev/alt_vip_cts_0"
#define ALT_VIP_CTS_0_SPAN 128
#define ALT_VIP_CTS_0_TYPE "alt_vip_cts"


/*
 * alt_vip_scl_0 configuration
 *
 */

#define ALT_MODULE_CLASS_alt_vip_scl_0 alt_vip_cl_scl
#define ALT_VIP_SCL_0_BASE 0x9401800
#define ALT_VIP_SCL_0_IRQ -1
#define ALT_VIP_SCL_0_IRQ_INTERRUPT_CONTROLLER_ID -1
#define ALT_VIP_SCL_0_NAME "/dev/alt_vip_scl_0"
#define ALT_VIP_SCL_0_SPAN 512
#define ALT_VIP_SCL_0_TYPE "alt_vip_cl_scl"


/*
 * alt_vip_vfr_0 configuration
 *
 */

#define ALT_MODULE_CLASS_alt_vip_vfr_0 alt_vip_vfr
#define ALT_VIP_VFR_0_BASE 0x9401200
#define ALT_VIP_VFR_0_IRQ 5
#define ALT_VIP_VFR_0_IRQ_INTERRUPT_CONTROLLER_ID 0
#define ALT_VIP_VFR_0_NAME "/dev/alt_vip_vfr_0"
#define ALT_VIP_VFR_0_SPAN 128
#define ALT_VIP_VFR_0_TYPE "alt_vip_vfr"


/*
 * audio_avalon_controller configuration
 *
 */

#define ALT_MODULE_CLASS_audio_avalon_controller audio_avalon_controller
#define AUDIO_AVALON_CONTROLLER_BASE 0x9401660
#define AUDIO_AVALON_CONTROLLER_IRQ 4
#define AUDIO_AVALON_CONTROLLER_IRQ_INTERRUPT_CONTROLLER_ID 0
#define AUDIO_AVALON_CONTROLLER_NAME "/dev/audio_avalon_controller"
#define AUDIO_AVALON_CONTROLLER_SPAN 32
#define AUDIO_AVALON_CONTROLLER_TYPE "audio_avalon_controller"


/*
 * av_i2c_clk_pio configuration
 *
 */

#define ALT_MODULE_CLASS_av_i2c_clk_pio altera_avalon_pio
#define AV_I2C_CLK_PIO_BASE 0x9401620
#define AV_I2C_CLK_PIO_BIT_CLEARING_EDGE_REGISTER 0
#define AV_I2C_CLK_PIO_BIT_MODIFYING_OUTPUT_REGISTER 0
#define AV_I2C_CLK_PIO_CAPTURE 0
#define AV_I2C_CLK_PIO_DATA_WIDTH 1
#define AV_I2C_CLK_PIO_DO_TEST_BENCH_WIRING 0
#define AV_I2C_CLK_PIO_DRIVEN_SIM_VALUE 0
#define AV_I2C_CLK_PIO_EDGE_TYPE "NONE"
#define AV_I2C_CLK_PIO_FREQ 120000000
#define AV_I2C_CLK_PIO_HAS_IN 0
#define AV_I2C_CLK_PIO_HAS_OUT 1
#define AV_I2C_CLK_PIO_HAS_TRI 0
#define AV_I2C_CLK_PIO_IRQ -1
#define AV_I2C_CLK_PIO_IRQ_INTERRUPT_CONTROLLER_ID -1
#define AV_I2C_CLK_PIO_IRQ_TYPE "NONE"
#define AV_I2C_CLK_PIO_NAME "/dev/av_i2c_clk_pio"
#define AV_I2C_CLK_PIO_RESET_VALUE 0
#define AV_I2C_CLK_PIO_SPAN 16
#define AV_I2C_CLK_PIO_TYPE "altera_avalon_pio"


/*
 * av_i2c_data_pio configuration
 *
 */

#define ALT_MODULE_CLASS_av_i2c_data_pio altera_avalon_pio
#define AV_I2C_DATA_PIO_BASE 0x9401640
#define AV_I2C_DATA_PIO_BIT_CLEARING_EDGE_REGISTER 0
#define AV_I2C_DATA_PIO_BIT_MODIFYING_OUTPUT_REGISTER 0
#define AV_I2C_DATA_PIO_CAPTURE 0
#define AV_I2C_DATA_PIO_DATA_WIDTH 1
#define AV_I2C_DATA_PIO_DO_TEST_BENCH_WIRING 1
#define AV_I2C_DATA_PIO_DRIVEN_SIM_VALUE 0
#define AV_I2C_DATA_PIO_EDGE_TYPE "NONE"
#define AV_I2C_DATA_PIO_FREQ 120000000
#define AV_I2C_DATA_PIO_HAS_IN 0
#define AV_I2C_DATA_PIO_HAS_OUT 0
#define AV_I2C_DATA_PIO_HAS_TRI 1
#define AV_I2C_DATA_PIO_IRQ -1
#define AV_I2C_DATA_PIO_IRQ_INTERRUPT_CONTROLLER_ID -1
#define AV_I2C_DATA_PIO_IRQ_TYPE "NONE"
#define AV_I2C_DATA_PIO_NAME "/dev/av_i2c_data_pio"
#define AV_I2C_DATA_PIO_RESET_VALUE 0
#define AV_I2C_DATA_PIO_SPAN 16
#define AV_I2C_DATA_PIO_TYPE "altera_avalon_pio"


/*
 * button_pio configuration
 *
 */

#define ALT_MODULE_CLASS_button_pio altera_avalon_pio
#define BUTTON_PIO_BASE 0x94015c0
#define BUTTON_PIO_BIT_CLEARING_EDGE_REGISTER 0
#define BUTTON_PIO_BIT_MODIFYING_OUTPUT_REGISTER 0
#define BUTTON_PIO_CAPTURE 1
#define BUTTON_PIO_DATA_WIDTH 4
#define BUTTON_PIO_DO_TEST_BENCH_WIRING 1
#define BUTTON_PIO_DRIVEN_SIM_VALUE 15
#define BUTTON_PIO_EDGE_TYPE "RISING"
#define BUTTON_PIO_FREQ 120000000
#define BUTTON_PIO_HAS_IN 1
#define BUTTON_PIO_HAS_OUT 0
#define BUTTON_PIO_HAS_TRI 0
#define BUTTON_PIO_IRQ 0
#define BUTTON_PIO_IRQ_INTERRUPT_CONTROLLER_ID 0
#define BUTTON_PIO_IRQ_TYPE "EDGE"
#define BUTTON_PIO_NAME "/dev/button_pio"
#define BUTTON_PIO_RESET_VALUE 0
#define BUTTON_PIO_SPAN 16
#define BUTTON_PIO_TYPE "altera_avalon_pio"


/*
 * hal configuration
 *
 */

#define ALT_INCLUDE_INSTRUCTION_RELATED_EXCEPTION_API
#define ALT_MAX_FD 32
#define ALT_SYS_CLK SYS_CLK_TIMER
#define ALT_TIMESTAMP_CLK none


/*
 * jtag_uart configuration
 *
 */

#define ALT_MODULE_CLASS_jtag_uart altera_avalon_jtag_uart
#define JTAG_UART_BASE 0x94016d0
#define JTAG_UART_IRQ 1
#define JTAG_UART_IRQ_INTERRUPT_CONTROLLER_ID 0
#define JTAG_UART_NAME "/dev/jtag_uart"
#define JTAG_UART_READ_DEPTH 256
#define JTAG_UART_READ_THRESHOLD 4
#define JTAG_UART_SPAN 8
#define JTAG_UART_TYPE "altera_avalon_jtag_uart"
#define JTAG_UART_WRITE_DEPTH 256
#define JTAG_UART_WRITE_THRESHOLD 4


/*
 * led_pio configuration
 *
 */

#define ALT_MODULE_CLASS_led_pio altera_avalon_pio
#define LED_PIO_BASE 0x94015e0
#define LED_PIO_BIT_CLEARING_EDGE_REGISTER 0
#define LED_PIO_BIT_MODIFYING_OUTPUT_REGISTER 0
#define LED_PIO_CAPTURE 0
#define LED_PIO_DATA_WIDTH 4
#define LED_PIO_DO_TEST_BENCH_WIRING 0
#define LED_PIO_DRIVEN_SIM_VALUE 0
#define LED_PIO_EDGE_TYPE "NONE"
#define LED_PIO_FREQ 120000000
#define LED_PIO_HAS_IN 0
#define LED_PIO_HAS_OUT 1
#define LED_PIO_HAS_TRI 0
#define LED_PIO_IRQ -1
#define LED_PIO_IRQ_INTERRUPT_CONTROLLER_ID -1
#define LED_PIO_IRQ_TYPE "NONE"
#define LED_PIO_NAME "/dev/led_pio"
#define LED_PIO_RESET_VALUE 0
#define LED_PIO_SPAN 16
#define LED_PIO_TYPE "altera_avalon_pio"


/*
 * onchip_memory2_0 configuration
 *
 */

#define ALT_MODULE_CLASS_onchip_memory2_0 altera_avalon_onchip_memory2
#define ONCHIP_MEMORY2_0_ALLOW_IN_SYSTEM_MEMORY_CONTENT_EDITOR 0
#define ONCHIP_MEMORY2_0_ALLOW_MRAM_SIM_CONTENTS_ONLY_FILE 0
#define ONCHIP_MEMORY2_0_BASE 0x8000000
#define ONCHIP_MEMORY2_0_CONTENTS_INFO ""
#define ONCHIP_MEMORY2_0_DUAL_PORT 0
#define ONCHIP_MEMORY2_0_GUI_RAM_BLOCK_TYPE "AUTO"
#define ONCHIP_MEMORY2_0_INIT_CONTENTS_FILE "DE10_Standard_Qsys_onchip_memory2_0"
#define ONCHIP_MEMORY2_0_INIT_MEM_CONTENT 1
#define ONCHIP_MEMORY2_0_INSTANCE_ID "NONE"
#define ONCHIP_MEMORY2_0_IRQ -1
#define ONCHIP_MEMORY2_0_IRQ_INTERRUPT_CONTROLLER_ID -1
#define ONCHIP_MEMORY2_0_NAME "/dev/onchip_memory2_0"
#define ONCHIP_MEMORY2_0_NON_DEFAULT_INIT_FILE_ENABLED 0
#define ONCHIP_MEMORY2_0_RAM_BLOCK_TYPE "AUTO"
#define ONCHIP_MEMORY2_0_READ_DURING_WRITE_MODE "DONT_CARE"
#define ONCHIP_MEMORY2_0_SINGLE_CLOCK_OP 0
#define ONCHIP_MEMORY2_0_SIZE_MULTIPLE 1
#define ONCHIP_MEMORY2_0_SIZE_VALUE 131072
#define ONCHIP_MEMORY2_0_SPAN 131072
#define ONCHIP_MEMORY2_0_TYPE "altera_avalon_onchip_memory2"
#define ONCHIP_MEMORY2_0_WRITABLE 1


/*
 * sdram configuration
 *
 */

#define ALT_MODULE_CLASS_sdram altera_avalon_new_sdram_controller
#define SDRAM_BASE 0x0
#define SDRAM_CAS_LATENCY 3
#define SDRAM_CONTENTS_INFO
#define SDRAM_INIT_NOP_DELAY 0.0
#define SDRAM_INIT_REFRESH_COMMANDS 2
#define SDRAM_IRQ -1
#define SDRAM_IRQ_INTERRUPT_CONTROLLER_ID -1
#define SDRAM_IS_INITIALIZED 1
#define SDRAM_NAME "/dev/sdram"
#define SDRAM_POWERUP_DELAY 100.0
#define SDRAM_REFRESH_PERIOD 15.625
#define SDRAM_REGISTER_DATA_IN 1
#define SDRAM_SDRAM_ADDR_WIDTH 0x19
#define SDRAM_SDRAM_BANK_WIDTH 2
#define SDRAM_SDRAM_COL_WIDTH 10
#define SDRAM_SDRAM_DATA_WIDTH 16
#define SDRAM_SDRAM_NUM_BANKS 4
#define SDRAM_SDRAM_NUM_CHIPSELECTS 1
#define SDRAM_SDRAM_ROW_WIDTH 13
#define SDRAM_SHARED_DATA 0
#define SDRAM_SIM_MODEL_BASE 1
#define SDRAM_SPAN 67108864
#define SDRAM_STARVATION_INDICATOR 0
#define SDRAM_TRISTATE_BRIDGE_SLAVE ""
#define SDRAM_TYPE "altera_avalon_new_sdram_controller"
#define SDRAM_T_AC 5.5
#define SDRAM_T_MRD 3
#define SDRAM_T_RCD 20.0
#define SDRAM_T_RFC 70.0
#define SDRAM_T_RP 20.0
#define SDRAM_T_WR 14.0


/*
 * sys_clk_timer configuration
 *
 */

#define ALT_MODULE_CLASS_sys_clk_timer altera_avalon_timer
#define SYS_CLK_TIMER_ALWAYS_RUN 0
#define SYS_CLK_TIMER_BASE 0x9401500
#define SYS_CLK_TIMER_COUNTER_SIZE 32
#define SYS_CLK_TIMER_FIXED_PERIOD 0
#define SYS_CLK_TIMER_FREQ 120000000
#define SYS_CLK_TIMER_IRQ 2
#define SYS_CLK_TIMER_IRQ_INTERRUPT_CONTROLLER_ID 0
#define SYS_CLK_TIMER_LOAD_VALUE 1199999
#define SYS_CLK_TIMER_MULT 0.001
#define SYS_CLK_TIMER_NAME "/dev/sys_clk_timer"
#define SYS_CLK_TIMER_PERIOD 10.0
#define SYS_CLK_TIMER_PERIOD_UNITS "ms"
#define SYS_CLK_TIMER_RESET_OUTPUT 0
#define SYS_CLK_TIMER_SNAPSHOT 1
#define SYS_CLK_TIMER_SPAN 32
#define SYS_CLK_TIMER_TICKS_PER_SEC 100
#define SYS_CLK_TIMER_TIMEOUT_PULSE_OUTPUT 0
#define SYS_CLK_TIMER_TYPE "altera_avalon_timer"


/*
 * sysid configuration
 *
 */

#define ALT_MODULE_CLASS_sysid altera_avalon_sysid_qsys
#define SYSID_BASE 0x4001030
#define SYSID_ID 0
#define SYSID_IRQ -1
#define SYSID_IRQ_INTERRUPT_CONTROLLER_ID -1
#define SYSID_NAME "/dev/sysid"
#define SYSID_SPAN 8
#define SYSID_TIMESTAMP 1486360670
#define SYSID_TYPE "altera_avalon_sysid_qsys"


/*
 * td_reset_pio configuration
 *
 */

#define ALT_MODULE_CLASS_td_reset_pio altera_avalon_pio
#define TD_RESET_PIO_BASE 0x94016a0
#define TD_RESET_PIO_BIT_CLEARING_EDGE_REGISTER 0
#define TD_RESET_PIO_BIT_MODIFYING_OUTPUT_REGISTER 0
#define TD_RESET_PIO_CAPTURE 0
#define TD_RESET_PIO_DATA_WIDTH 1
#define TD_RESET_PIO_DO_TEST_BENCH_WIRING 0
#define TD_RESET_PIO_DRIVEN_SIM_VALUE 0
#define TD_RESET_PIO_EDGE_TYPE "NONE"
#define TD_RESET_PIO_FREQ 120000000
#define TD_RESET_PIO_HAS_IN 0
#define TD_RESET_PIO_HAS_OUT 1
#define TD_RESET_PIO_HAS_TRI 0
#define TD_RESET_PIO_IRQ -1
#define TD_RESET_PIO_IRQ_INTERRUPT_CONTROLLER_ID -1
#define TD_RESET_PIO_IRQ_TYPE "NONE"
#define TD_RESET_PIO_NAME "/dev/td_reset_pio"
#define TD_RESET_PIO_RESET_VALUE 0
#define TD_RESET_PIO_SPAN 16
#define TD_RESET_PIO_TYPE "altera_avalon_pio"


/*
 * touch_i2c_opencores configuration
 *
 */

#define ALT_MODULE_CLASS_touch_i2c_opencores i2c_opencores
#define TOUCH_I2C_OPENCORES_BASE 0x4001000
#define TOUCH_I2C_OPENCORES_IRQ 7
#define TOUCH_I2C_OPENCORES_IRQ_INTERRUPT_CONTROLLER_ID 0
#define TOUCH_I2C_OPENCORES_NAME "/dev/touch_i2c_opencores"
#define TOUCH_I2C_OPENCORES_SPAN 32
#define TOUCH_I2C_OPENCORES_TYPE "i2c_opencores"


/*
 * touch_int_n configuration
 *
 */

#define ALT_MODULE_CLASS_touch_int_n altera_avalon_pio
#define TOUCH_INT_N_BASE 0x4001020
#define TOUCH_INT_N_BIT_CLEARING_EDGE_REGISTER 0
#define TOUCH_INT_N_BIT_MODIFYING_OUTPUT_REGISTER 0
#define TOUCH_INT_N_CAPTURE 1
#define TOUCH_INT_N_DATA_WIDTH 1
#define TOUCH_INT_N_DO_TEST_BENCH_WIRING 0
#define TOUCH_INT_N_DRIVEN_SIM_VALUE 0
#define TOUCH_INT_N_EDGE_TYPE "FALLING"
#define TOUCH_INT_N_FREQ 50000000
#define TOUCH_INT_N_HAS_IN 1
#define TOUCH_INT_N_HAS_OUT 0
#define TOUCH_INT_N_HAS_TRI 0
#define TOUCH_INT_N_IRQ 3
#define TOUCH_INT_N_IRQ_INTERRUPT_CONTROLLER_ID 0
#define TOUCH_INT_N_IRQ_TYPE "EDGE"
#define TOUCH_INT_N_NAME "/dev/touch_int_n"
#define TOUCH_INT_N_RESET_VALUE 0
#define TOUCH_INT_N_SPAN 16
#define TOUCH_INT_N_TYPE "altera_avalon_pio"

#endif /* __SYSTEM_H_ */
