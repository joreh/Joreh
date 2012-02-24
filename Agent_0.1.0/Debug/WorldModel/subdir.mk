################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../WorldModel/Field.cpp \
../WorldModel/Object.cpp \
../WorldModel/WorldModel.cpp 

OBJS += \
./WorldModel/Field.o \
./WorldModel/Object.o \
./WorldModel/WorldModel.o 

CPP_DEPS += \
./WorldModel/Field.d \
./WorldModel/Object.d \
./WorldModel/WorldModel.d 


# Each subdirectory must supply rules for building sources it contributes
WorldModel/%.o: ../WorldModel/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


