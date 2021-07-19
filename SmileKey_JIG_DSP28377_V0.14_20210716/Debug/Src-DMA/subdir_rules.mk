################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
Src-DMA/%.obj: ../Src-DMA/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1010/ccs/tools/compiler/ti-cgt-c2000_20.2.4.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu0 -O1 --opt_for_speed=2 --fp_mode=relaxed --include_path="C:/ti/ccs1010/ccs/tools/compiler/ti-cgt-c2000_20.2.4.LTS/include" --include_path="C:/tools/F2837xD_common/include" --include_path="C:/tools/F2837xD_headers/include" --include_path="C:/tools/F2837xD_common" --include_path="C:/tools/driverlib/f2837xd/driverlib" --define=CPU1 --define=_FLASH --undefine=_STAND_ALONE -g --diag_warning=225 --diag_wrap=off --display_error_number --abi=coffabi --preproc_with_compile --preproc_dependency="Src-DMA/$(basename $(<F)).d_raw" --obj_directory="Src-DMA" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


