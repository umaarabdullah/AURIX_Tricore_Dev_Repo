################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../PID_Control_System/Ultrasonic_Based_Pid_Control.c 

COMPILED_SRCS += \
./PID_Control_System/Ultrasonic_Based_Pid_Control.src 

C_DEPS += \
./PID_Control_System/Ultrasonic_Based_Pid_Control.d 

OBJS += \
./PID_Control_System/Ultrasonic_Based_Pid_Control.o 


# Each subdirectory must supply rules for building sources it contributes
PID_Control_System/%.src: ../PID_Control_System/%.c PID_Control_System/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C/C++ Compiler'
	cctc -cs --dep-file="$(basename $@).d" --misrac-version=2004 -D__CPU__=tc37x "-fC:/Users/Umaar/Documents/GitHub/AURIX_Tricore_Dev_Repo/BOT_CONTROL/Debug/TASKING_C_C___Compiler-Include_paths.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc37x -Y0 -N0 -Z0 -o "$@" "$<" && \
	if [ -f "$(basename $@).d" ]; then sed.exe -r  -e 's/\b(.+\.o)\b/PID_Control_System\/\1/g' -e 's/\\/\//g' -e 's/\/\//\//g' -e 's/"//g' -e 's/([a-zA-Z]:\/)/\L\1/g' -e 's/\d32:/@TARGET_DELIMITER@/g; s/\\\d32/@ESCAPED_SPACE@/g; s/\d32/\\\d32/g; s/@ESCAPED_SPACE@/\\\d32/g; s/@TARGET_DELIMITER@/\d32:/g' "$(basename $@).d" > "$(basename $@).d_sed" && cp "$(basename $@).d_sed" "$(basename $@).d" && rm -f "$(basename $@).d_sed" 2>/dev/null; else echo 'No dependency file to process';fi
	@echo 'Finished building: $<'
	@echo ' '

PID_Control_System/%.o: ./PID_Control_System/%.src PID_Control_System/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-PID_Control_System

clean-PID_Control_System:
	-$(RM) ./PID_Control_System/Ultrasonic_Based_Pid_Control.d ./PID_Control_System/Ultrasonic_Based_Pid_Control.o ./PID_Control_System/Ultrasonic_Based_Pid_Control.src

.PHONY: clean-PID_Control_System

