################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ASCLIN_UART.c \
../Cpu0_Main.c \
../Cpu1_Main.c \
../Cpu2_Main.c \
../GTM_PWM.c \
../RPLIDAR_A2.c \
../UART.c 

COMPILED_SRCS += \
./ASCLIN_UART.src \
./Cpu0_Main.src \
./Cpu1_Main.src \
./Cpu2_Main.src \
./GTM_PWM.src \
./RPLIDAR_A2.src \
./UART.src 

C_DEPS += \
./ASCLIN_UART.d \
./Cpu0_Main.d \
./Cpu1_Main.d \
./Cpu2_Main.d \
./GTM_PWM.d \
./RPLIDAR_A2.d \
./UART.d 

OBJS += \
./ASCLIN_UART.o \
./Cpu0_Main.o \
./Cpu1_Main.o \
./Cpu2_Main.o \
./GTM_PWM.o \
./RPLIDAR_A2.o \
./UART.o 


# Each subdirectory must supply rules for building sources it contributes
%.src: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C/C++ Compiler'
	cctc -cs --dep-file="$(basename $@).d" --misrac-version=2004 -D__CPU__=tc37x "-fC:/Users/Umaar/Documents/GitHub/AURIX_Tricore_Dev_Repo/RPLIDAR_A2_TC375_SB/Debug/TASKING_C_C___Compiler-Include_paths.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc37x -Y0 -N0 -Z0 -o "$@" "$<" && \
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
	-$(RM) ./ASCLIN_UART.d ./ASCLIN_UART.o ./ASCLIN_UART.src ./Cpu0_Main.d ./Cpu0_Main.o ./Cpu0_Main.src ./Cpu1_Main.d ./Cpu1_Main.o ./Cpu1_Main.src ./Cpu2_Main.d ./Cpu2_Main.o ./Cpu2_Main.src ./GTM_PWM.d ./GTM_PWM.o ./GTM_PWM.src ./RPLIDAR_A2.d ./RPLIDAR_A2.o ./RPLIDAR_A2.src ./UART.d ./UART.o ./UART.src

.PHONY: clean--2e-

