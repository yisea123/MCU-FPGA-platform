# Run with quartus_sh -t <x_cons.tcl>

# Global assignments 
set_global_assignment -name TOP_LEVEL_ENTITY "|IntF"
set_global_assignment -name ROUTING_BACK_ANNOTATION_MODE NORMAL
set_global_assignment -name FAMILY "CYCLONE IVE"
set_global_assignment -name DEVICE "EP4CE10F17C8"
set_global_assignment -section_id IntF -name EDA_DESIGN_ENTRY_SYNTHESIS_TOOL "SYNPLIFY"
set_global_assignment -section_id eda_design_synthesis -name EDA_USE_LMF synplcty.lmf
set_global_assignment -name TAO_FILE "myresults.tao"
set_global_assignment -name SOURCES_PER_DESTINATION_INCLUDE_COUNT "1000" 
set_global_assignment -name ROUTER_REGISTER_DUPLICATION ON
set_global_assignment -name REMOVE_REDUNDANT_LOGIC_CELLS "OFF"
set_global_assignment -name REMOVE_DUPLICATE_REGISTERS "OFF"
set_global_assignment -name REMOVE_DUPLICATE_LOGIC "OFF"
# set_global_assignment -name FITTER_EFFORT "STANDARD FIT"
#set_global_assignment -name EDA_RESYNTHESIS_TOOL "AMPLIFY"
set_global_assignment -name ENABLE_CLOCK_LATENCY "ON"
set_global_assignment -name USE_TIMEQUEST_TIMING_ANALYZER ON
set_global_assignment -name SDC_FILE "proj_1.scf"
set_global_assignment -name TIMEQUEST_DO_REPORT_TIMING ON

set_location_assignment PIN_E1 -to CLK_25M
set_location_assignment PIN_C6 -to ADDRH\[16\]
set_location_assignment PIN_A5 -to ADDRH\[17\]
set_location_assignment PIN_B5 -to ADDRH\[18\]
set_location_assignment PIN_A11 -to ADDRH\[19\]
set_location_assignment PIN_B11 -to ADDRH\[20\]
set_location_assignment PIN_A12 -to ADDRH\[21\]
set_location_assignment PIN_B12 -to ADDRH\[22\]
set_location_assignment PIN_B10 -to ADDRH\[23\]
set_location_assignment PIN_A9 -to ADDRH\[24\]
set_location_assignment PIN_B9 -to ADDRH\[25\]
set_location_assignment PIN_A4 -to AD\[0\]
set_location_assignment PIN_B4 -to AD\[1\]
set_location_assignment PIN_B6 -to AD\[2\]
set_location_assignment PIN_A6 -to AD\[3\]
set_location_assignment PIN_D11 -to AD\[4\]
set_location_assignment PIN_C11 -to AD\[5\]
set_location_assignment PIN_E10 -to AD\[6\]
set_location_assignment PIN_D9 -to AD\[7\]
set_location_assignment PIN_C9 -to AD\[8\]
set_location_assignment PIN_E9 -to AD\[9\]
set_location_assignment PIN_F9 -to AD\[10\]
set_location_assignment PIN_F8 -to AD\[11\]
set_location_assignment PIN_E8 -to AD\[12\]
set_location_assignment PIN_D8 -to AD\[13\]
set_location_assignment PIN_F7 -to AD\[14\]
set_location_assignment PIN_E7 -to AD\[15\]
set_location_assignment PIN_A10 -to nADV
set_location_assignment PIN_C8 -to nE1
set_location_assignment PIN_B8 -to nWR
set_location_assignment PIN_A7 -to nRD
set_location_assignment PIN_A8 -to nWAIT
set_location_assignment PIN_K10 -to DAC_D\[0\]
set_location_assignment PIN_F10 -to DAC_D\[1\]
set_location_assignment PIN_G11 -to DAC_D\[2\]
set_location_assignment PIN_F11 -to DAC_D\[3\]
set_location_assignment PIN_D14 -to DAC_D\[4\]
set_location_assignment PIN_D12 -to DAC_D\[5\]
set_location_assignment PIN_C14 -to DAC_D\[6\]
set_location_assignment PIN_G16 -to DAC_D\[7\]
set_location_assignment PIN_F16 -to DAC_D\[8\]
set_location_assignment PIN_G15 -to DAC_D\[9\]
set_location_assignment PIN_F15 -to DAC_D\[10\]
set_location_assignment PIN_F6 -to DAC_D\[11\]
set_location_assignment PIN_K12 -to nDAC_CS
set_location_assignment PIN_J11 -to nDAC_WR
set_location_assignment PIN_K11 -to samp_complete
set_location_assignment PIN_J2 -to SRAM_D\[0\]
set_location_assignment PIN_K1 -to SRAM_D\[1\]
set_location_assignment PIN_G1 -to SRAM_D\[2\]
set_location_assignment PIN_J1 -to SRAM_D\[3\]
set_location_assignment PIN_F1 -to SRAM_D\[4\]
set_location_assignment PIN_G2 -to SRAM_D\[5\]
set_location_assignment PIN_D1 -to SRAM_D\[6\]
set_location_assignment PIN_F2 -to SRAM_D\[7\]
set_location_assignment PIN_E5 -to SRAM_D\[8\]
set_location_assignment PIN_F3 -to SRAM_D\[9\]
set_location_assignment PIN_D3 -to SRAM_D\[10\]
set_location_assignment PIN_E6 -to SRAM_D\[11\]
set_location_assignment PIN_D4 -to SRAM_D\[12\]
set_location_assignment PIN_C3 -to SRAM_D\[13\]
set_location_assignment PIN_D6 -to SRAM_D\[14\]
set_location_assignment PIN_D5 -to SRAM_D\[15\]
set_location_assignment PIN_R1 -to SRAM_A\[0\]
set_location_assignment PIN_T2 -to SRAM_A\[1\]
set_location_assignment PIN_P1 -to SRAM_A\[2\]
set_location_assignment PIN_P2 -to SRAM_A\[3\]
set_location_assignment PIN_L7 -to SRAM_A\[4\]
set_location_assignment PIN_P6 -to SRAM_A\[5\]
set_location_assignment PIN_N6 -to SRAM_A\[6\]
set_location_assignment PIN_N5 -to SRAM_A\[7\]
set_location_assignment PIN_M6 -to SRAM_A\[8\]
set_location_assignment PIN_P3 -to SRAM_A\[9\]
set_location_assignment PIN_N3 -to SRAM_A\[10\]
set_location_assignment PIN_L6 -to SRAM_A\[11\]
set_location_assignment PIN_L4 -to SRAM_A\[12\]
set_location_assignment PIN_L3 -to SRAM_A\[13\]
set_location_assignment PIN_K6 -to SRAM_A\[14\]
set_location_assignment PIN_K5 -to SRAM_A\[15\]
set_location_assignment PIN_K8 -to SRAM_A\[16\]
set_location_assignment PIN_L2 -to SRAM_A\[17\]
set_location_assignment PIN_K2 -to SRAM_A\[18\]
set_location_assignment PIN_L1 -to SRAM_A\[19\]
set_location_assignment PIN_N1 -to nSRAM_CE
set_location_assignment PIN_R3 -to nSRAM_WE
set_location_assignment PIN_T3 -to nSRAM_OE
set_location_assignment PIN_L14 -to AC573_LE
set_location_assignment PIN_F5 -to FPGA_F5
set_location_assignment PIN_J6 -to FPGA_J6
set_location_assignment PIN_P8 -to FPGA_P8
set_location_assignment PIN_M7 -to FPGA_M7
set_location_assignment PIN_N2 -to FPGA_N2
if {[file exists ___quartus_options.tcl]} {
	source ___quartus_options.tcl
}


# Incremental Compilation
    # this will synchronize any existing partitions declared in Synpilfy
    # with partitions existing in Quartus. If partitions exist,
    # incremental compilation will be enabled
    variable compile_point_list
    set compile_point_list [list]
    source "D:/Synopsys/fpga_H201303/lib/altera/qic.tcl"
