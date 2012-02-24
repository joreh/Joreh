################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Config/Config.cpp 

C_SRCS += \
../Config/ConfigParser.y.c \
../Config/ConfigParser.yy.c 

OBJS += \
./Config/Config.o \
./Config/ConfigParser.y.o \
./Config/ConfigParser.yy.o 

C_DEPS += \
./Config/ConfigParser.y.d \
./Config/ConfigParser.yy.d 

CPP_DEPS += \
./Config/Config.d 


# Each subdirectory must supply rules for building sources it contributes
Config/%.o: ../Config/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Config/%.o: ../Config/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


