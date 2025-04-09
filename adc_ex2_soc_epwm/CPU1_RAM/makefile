################################################################################
# Automatically-generated file. Do not edit!
################################################################################

CG_TOOL_ROOT := /Applications/ti/ccs1281/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS

GEN_OPTS__FLAG := --cmd_file="syscfg/board.opt" --cmd_file="syscfg/c2000ware_libraries.opt" 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./adc_ex2_soc_epwm.obj" \
"./syscfg/board.obj" \
"./syscfg/c2000ware_libraries.obj" \
"./device/device.obj" \
"./device/f2838x_codestartbranch.obj" \
"../2838x_RAM_lnk_cpu1.cmd" \
"/Users/Shenshen/ti/C2000Ware_5_00_00_00/driverlib/f2838x/driverlib/ccs/Debug/driverlib.lib" \
$(GEN_CMDS__FLAG) \
-lc2000ware_libraries.cmd.genlibs \
-llibc.a \

-include ../makefile.init

RM := rm -rf
RMDIR := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include device/subdir_vars.mk
-include subdir_rules.mk
-include device/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(SV7A_DEPS)),)
-include $(SV7A_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
adc_ex2_soc_epwm.out 

EXE_OUTPUTS__QUOTED += \
"adc_ex2_soc_epwm.out" 


# All Target
all: $(OBJS) $(CMD_SRCS) $(LIB_SRCS) $(GEN_CMDS)
	@$(MAKE) --no-print-directory -Onone "adc_ex2_soc_epwm.out"

# Tool invocations
adc_ex2_soc_epwm.out: $(OBJS) $(CMD_SRCS) $(LIB_SRCS) $(GEN_CMDS)
	@echo 'Building target: "$@"'
	@echo 'Invoking: C2000 Linker'
	"/Applications/ti/ccs1281/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla2 --float_support=fpu64 --idiv_support=idiv0 --tmu_support=tmu0 --vcu_support=vcrc -Ooff --advice:performance=all --define=RAM --define=DEBUG --define=CPU1 --diag_suppress=10063 --diag_warning=225 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi -z -m"adc_ex2_soc_epwm.map" --heap_size=0x200 --stack_size=0x3F8 --warn_sections -i"/Applications/ti/ccs1281/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/lib" -i"/Users/Shenshen/ti/C2000Ware_5_00_00_00" -i"/Users/Shenshen/workspace_ccstheia/adc_ex2_soc_epwm/CPU1_RAM/syscfg" -i"/Applications/ti/ccs1281/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/include" --reread_libs --define=RAM --diag_wrap=off --display_error_number --xml_link_info="adc_ex2_soc_epwm_linkInfo.xml" --entry_point=code_start --rom_model -o "adc_ex2_soc_epwm.out" $(ORDERED_OBJS)
	@echo 'Finished building target: "$@"'
	@echo ' '
	@$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(GEN_MISC_FILES__QUOTED)$(GEN_FILES__QUOTED)$(EXE_OUTPUTS__QUOTED)
	-$(RM) "adc_ex2_soc_epwm.obj" "syscfg/board.obj" "syscfg/c2000ware_libraries.obj" "device/device.obj" "device/f2838x_codestartbranch.obj" 
	-$(RM) "adc_ex2_soc_epwm.d" "syscfg/board.d" "syscfg/c2000ware_libraries.d" "device/device.d" 
	-$(RM) "device/f2838x_codestartbranch.d" 
	-$(RMDIR) $(GEN_MISC_DIRS__QUOTED)
	-@echo 'Finished clean'
	-@echo ' '

post-build:
	-echo "========= Build of the CLB simulation has moved to the CLB Tool. Click the '?' icon by the _Generate CLB Simulation File_ enable for more details (located in the Global Parameters of the Tile Design SysConfig module) ============="
	-if 0 == 1  /Applications/ti/ccs1281/ccs/tools/node/node "/Users/Shenshen/ti/C2000Ware_5_00_00_00/utilities/clb_tool/clb_syscfg/dot_file_libraries/clbDotUtility.js"  "/Users/Shenshen/ti/C2000Ware_5_00_00_00/utilities/clb_tool/clb_syscfg/" "/Users/Shenshen/workspace_ccstheia/adc_ex2_soc_epwm/CPU1_RAM/syscfg" "/Users/Shenshen/workspace_ccstheia/adc_ex2_soc_epwm/CPU1_RAM/syscfg/clb.dot"
	-if 0 == 1  mkdir "/Users/Shenshen/workspace_ccstheia/adc_ex2_soc_epwm/CPU1_RAM/diagrams"
	-if 0 == 1  /Applications/ti/ccs1281/ccs/tools/node/node "/Users/Shenshen/ti/C2000Ware_5_00_00_00/driverlib/.meta/generate_diagrams.js" "/Users/Shenshen/ti/C2000Ware_5_00_00_00" "/Users/Shenshen/workspace_ccstheia/adc_ex2_soc_epwm/CPU1_RAM/diagrams" "/Users/Shenshen/workspace_ccstheia/adc_ex2_soc_epwm/CPU1_RAM/syscfg"
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

