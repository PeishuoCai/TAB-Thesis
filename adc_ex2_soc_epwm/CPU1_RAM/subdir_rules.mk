################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
%.obj: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"/Applications/ti/ccs1281/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla2 --float_support=fpu64 --idiv_support=idiv0 --tmu_support=tmu0 --vcu_support=vcrc -Ooff --include_path="/Users/Shenshen/workspace_ccstheia/adc_ex2_soc_epwm" --include_path="/Users/Shenshen/ti/C2000Ware_5_00_00_00" --include_path="/Users/Shenshen/workspace_ccstheia/adc_ex2_soc_epwm/device" --include_path="/Users/Shenshen/ti/C2000Ware_5_00_00_00/driverlib/f2838x/driverlib" --include_path="/Applications/ti/ccs1281/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/include" --advice:performance=all --define=RAM --define=DEBUG --define=CPU1 --diag_suppress=10063 --diag_warning=225 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" --include_path="/Users/Shenshen/workspace_ccstheia/adc_ex2_soc_epwm/CPU1_RAM/syscfg" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

build-1627764449: ../adc_ex2_soc_epwm.syscfg
	@echo 'Building file: "$<"'
	@echo 'Invoking: SysConfig'
	"/Applications/ti/ccs1281/ccs/utils/sysconfig_1.21.0/sysconfig_cli.sh" --script "/Users/Shenshen/workspace_ccstheia/adc_ex2_soc_epwm/adc_ex2_soc_epwm.syscfg" -o "syscfg" -s "/Users/Shenshen/ti/C2000Ware_5_00_00_00/.metadata/sdk.json" -d "F2838x" --package 337bga --part F2838x_337bga --compiler ccs
	@echo 'Finished building: "$<"'
	@echo ' '

syscfg/board.c: build-1627764449 ../adc_ex2_soc_epwm.syscfg
syscfg/board.h: build-1627764449
syscfg/board.cmd.genlibs: build-1627764449
syscfg/board.opt: build-1627764449
syscfg/pinmux.csv: build-1627764449
syscfg/epwm.dot: build-1627764449
syscfg/adc.dot: build-1627764449
syscfg/c2000ware_libraries.cmd.genlibs: build-1627764449
syscfg/c2000ware_libraries.opt: build-1627764449
syscfg/c2000ware_libraries.c: build-1627764449
syscfg/c2000ware_libraries.h: build-1627764449
syscfg/clocktree.h: build-1627764449
syscfg: build-1627764449

syscfg/%.obj: ./syscfg/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"/Applications/ti/ccs1281/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla2 --float_support=fpu64 --idiv_support=idiv0 --tmu_support=tmu0 --vcu_support=vcrc -Ooff --include_path="/Users/Shenshen/workspace_ccstheia/adc_ex2_soc_epwm" --include_path="/Users/Shenshen/ti/C2000Ware_5_00_00_00" --include_path="/Users/Shenshen/workspace_ccstheia/adc_ex2_soc_epwm/device" --include_path="/Users/Shenshen/ti/C2000Ware_5_00_00_00/driverlib/f2838x/driverlib" --include_path="/Applications/ti/ccs1281/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/include" --advice:performance=all --define=RAM --define=DEBUG --define=CPU1 --diag_suppress=10063 --diag_warning=225 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --preproc_with_compile --preproc_dependency="syscfg/$(basename $(<F)).d_raw" --include_path="/Users/Shenshen/workspace_ccstheia/adc_ex2_soc_epwm/CPU1_RAM/syscfg" --obj_directory="syscfg" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


