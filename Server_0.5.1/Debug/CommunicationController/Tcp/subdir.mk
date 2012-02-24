################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../CommunicationController/Tcp/ClientSocket.cpp 

OBJS += \
./CommunicationController/Tcp/ClientSocket.o 

CPP_DEPS += \
./CommunicationController/Tcp/ClientSocket.d 


# Each subdirectory must supply rules for building sources it contributes
CommunicationController/Tcp/%.o: ../CommunicationController/Tcp/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


