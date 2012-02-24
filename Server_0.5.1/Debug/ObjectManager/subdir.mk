################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../ObjectManager/ObjectManager.cpp 

OBJS += \
./ObjectManager/ObjectManager.o 

CPP_DEPS += \
./ObjectManager/ObjectManager.d 


# Each subdirectory must supply rules for building sources it contributes
ObjectManager/%.o: ../ObjectManager/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


