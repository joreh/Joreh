################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Geom/Comp_Geom.cpp \
../Geom/Vector.cpp \
../Geom/Vector3D.cpp 

OBJS += \
./Geom/Comp_Geom.o \
./Geom/Vector.o \
./Geom/Vector3D.o 

CPP_DEPS += \
./Geom/Comp_Geom.d \
./Geom/Vector.d \
./Geom/Vector3D.d 


# Each subdirectory must supply rules for building sources it contributes
Geom/%.o: ../Geom/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


