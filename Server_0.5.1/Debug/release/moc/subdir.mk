################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../release/moc/moc_ClientSocket.cpp \
../release/moc/moc_CommunicationController.cpp \
../release/moc/moc_Connection.cpp \
../release/moc/moc_Kernel.cpp \
../release/moc/moc_Server.cpp \
../release/moc/moc_TcpController.cpp \
../release/moc/moc_server.cpp 

OBJS += \
./release/moc/moc_ClientSocket.o \
./release/moc/moc_CommunicationController.o \
./release/moc/moc_Connection.o \
./release/moc/moc_Kernel.o \
./release/moc/moc_Server.o \
./release/moc/moc_TcpController.o \
./release/moc/moc_server.o 

CPP_DEPS += \
./release/moc/moc_ClientSocket.d \
./release/moc/moc_CommunicationController.d \
./release/moc/moc_Connection.d \
./release/moc/moc_Kernel.d \
./release/moc/moc_Server.d \
./release/moc/moc_TcpController.d \
./release/moc/moc_server.d 


# Each subdirectory must supply rules for building sources it contributes
release/moc/%.o: ../release/moc/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


