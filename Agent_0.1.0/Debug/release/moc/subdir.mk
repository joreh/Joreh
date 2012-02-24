################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../release/moc/moc_Agent.cpp \
../release/moc/moc_Connection.cpp \
../release/moc/moc_GraphicsView.cpp \
../release/moc/moc_MainWindow.cpp 

OBJS += \
./release/moc/moc_Agent.o \
./release/moc/moc_Connection.o \
./release/moc/moc_GraphicsView.o \
./release/moc/moc_MainWindow.o 

CPP_DEPS += \
./release/moc/moc_Agent.d \
./release/moc/moc_Connection.d \
./release/moc/moc_GraphicsView.d \
./release/moc/moc_MainWindow.d 


# Each subdirectory must supply rules for building sources it contributes
release/moc/%.o: ../release/moc/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


