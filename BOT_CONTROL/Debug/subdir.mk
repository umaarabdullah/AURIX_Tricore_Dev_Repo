################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Cpu0_Main.c \
../Cpu1_Main.c \
../Cpu2_Main.c \
../GTM_PWM.c \
../Navigation.c \
../SONAR.c \
../STM_Interrupt.c \
../UART.c \
../Ultrasonic_Based_Pid_Control.c 

COMPILED_SRCS += \
./Cpu0_Main.src \
./Cpu1_Main.src \
./Cpu2_Main.src \
./GTM_PWM.src \
./Navigation.src \
./SONAR.src \
./STM_Interrupt.src \
./UART.src \
./Ultrasonic_Based_Pid_Control.src 

C_DEPS += \
./Cpu0_Main.d \
./Cpu1_Main.d \
./Cpu2_Main.d \
./GTM_PWM.d \
./Navigation.d \
./SONAR.d \
./STM_Interrupt.d \
./UART.d \
./Ultrasonic_Based_Pid_Control.d 

OBJS += \
./Cpu0_Main.o \
./Cpu1_Main.o \
./Cpu2_Main.o \
./GTM_PWM.o \
./Navigation.o \
./SONAR.o \
./STM_Interrupt.o \
./UART.o \
./Ultrasonic_Based_Pid_Control.o 


# Each subdirectory must supply rules for building sources it contributes
%.src: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C/C++ Compiler'
	cctc -cs --dep-file="$(basename $@).d" --misrac-version=2004 -D__CPU__=tc37x "-fC:/Users/Umaar/AURIX-v1.9.0-workspace/Github/AURIX_Tricore_Dev_Repo/BOT_CONTROL/Debug/TASKING_C_C___Compiler-Include_paths.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc37x -Y0 -N0 -Z0 -o "$@" "$<" && \
	if [ -f "$(basename $@).d" ]; then sed.exe -r  -e 's/\b(.+\.o)\b/\/\1/g' -e 's/\\/\//g' -e 's/\/\//\//g' -e 's/"//g' -e 's/([a-zA-Z]:\/)/\L\1/g' -e 's/\d32:/@TARGET_DELIMITER@/g; s/\\\d32/@ESCAPED_SPACE@/g; s/\d32/\\\d32/g; s/@ESCAPED_SPACE@/\\\d32/g; s/@TARGET_DELIMITER@/\d32:/g' "$(basename $@).d" > "$(basename $@).d_sed" && cp "$(basename $@).d_sed" "$(basename $@).d" && rm -f "$(basename $@).d_sed" 2>/dev/null; else echo 'No dependency file to process';fi
	@echo 'Finished building: $<'
	@echo ' '

%.o: ./%.src subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean--2e-

clean--2e-:
	-$(RM) ./Cpu0_Main.d ./Cpu0_Main.o ./Cpu0_Main.src ./Cpu1_Main.d ./Cpu1_Main.o ./Cpu1_Main.src ./Cpu2_Main.d ./Cpu2_Main.o ./Cpu2_Main.src ./GTM_PWM.d ./GTM_PWM.o ./GTM_PWM.src ./Navigation.d ./Navigation.o ./Navigation.src ./SONAR.d ./SONAR.o ./SONAR.src ./STM_Interrupt.d ./STM_Interrupt.o ./STM_Interrupt.src ./UART.d ./UART.o ./UART.src ./Ultrasonic_Based_Pid_Control.d ./Ultrasonic_Based_Pid_Control.o ./Ultrasonic_Based_Pid_Control.src

.PHONY: clean--2e-

