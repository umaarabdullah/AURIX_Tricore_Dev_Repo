################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Libraries/iLLD/TC37A/Tricore/Gtm/Atom/Timer/IfxGtm_Atom_Timer.c 

COMPILED_SRCS += \
./Libraries/iLLD/TC37A/Tricore/Gtm/Atom/Timer/IfxGtm_Atom_Timer.src 

C_DEPS += \
./Libraries/iLLD/TC37A/Tricore/Gtm/Atom/Timer/IfxGtm_Atom_Timer.d 

OBJS += \
./Libraries/iLLD/TC37A/Tricore/Gtm/Atom/Timer/IfxGtm_Atom_Timer.o 


# Each subdirectory must supply rules for building sources it contributes
Libraries/iLLD/TC37A/Tricore/Gtm/Atom/Timer/%.src: ../Libraries/iLLD/TC37A/Tricore/Gtm/Atom/Timer/%.c Libraries/iLLD/TC37A/Tricore/Gtm/Atom/Timer/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C/C++ Compiler'
	cctc -cs --dep-file="$(basename $@).d" --misrac-version=2004 -D__CPU__=tc37x "-fC:/Users/Umaar/AURIX-v1.9.0-workspace/Assembly_C_Code_1_KIT_TC375_LK/Debug/TASKING_C_C___Compiler-Include_paths.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc37x -Y0 -N0 -Z0 -o "$@" "$<" && \
	if [ -f "$(basename $@).d" ]; then sed.exe -r  -e 's/\b(.+\.o)\b/Libraries\/iLLD\/TC37A\/Tricore\/Gtm\/Atom\/Timer\/\1/g' -e 's/\\/\//g' -e 's/\/\//\//g' -e 's/"//g' -e 's/([a-zA-Z]:\/)/\L\1/g' -e 's/\d32:/@TARGET_DELIMITER@/g; s/\\\d32/@ESCAPED_SPACE@/g; s/\d32/\\\d32/g; s/@ESCAPED_SPACE@/\\\d32/g; s/@TARGET_DELIMITER@/\d32:/g' "$(basename $@).d" > "$(basename $@).d_sed" && cp "$(basename $@).d_sed" "$(basename $@).d" && rm -f "$(basename $@).d_sed" 2>/dev/null; else echo 'No dependency file to process';fi
	@echo 'Finished building: $<'
	@echo ' '

Libraries/iLLD/TC37A/Tricore/Gtm/Atom/Timer/%.o: ./Libraries/iLLD/TC37A/Tricore/Gtm/Atom/Timer/%.src Libraries/iLLD/TC37A/Tricore/Gtm/Atom/Timer/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-Libraries-2f-iLLD-2f-TC37A-2f-Tricore-2f-Gtm-2f-Atom-2f-Timer

clean-Libraries-2f-iLLD-2f-TC37A-2f-Tricore-2f-Gtm-2f-Atom-2f-Timer:
	-$(RM) ./Libraries/iLLD/TC37A/Tricore/Gtm/Atom/Timer/IfxGtm_Atom_Timer.d ./Libraries/iLLD/TC37A/Tricore/Gtm/Atom/Timer/IfxGtm_Atom_Timer.o ./Libraries/iLLD/TC37A/Tricore/Gtm/Atom/Timer/IfxGtm_Atom_Timer.src

.PHONY: clean-Libraries-2f-iLLD-2f-TC37A-2f-Tricore-2f-Gtm-2f-Atom-2f-Timer
