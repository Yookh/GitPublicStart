################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
Src-GPIO/%.obj: ../Src-GPIO/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1031/ccs/tools/compiler/ti-cgt-c2000_20.2.4.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 -O2 --include_path="C:/ti/ccs1031/ccs/tools/compiler/ti-cgt-c2000_20.2.4.LTS/include" --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="Src-GPIO/$(basename $(<F)).d_raw" --obj_directory="Src-GPIO" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


