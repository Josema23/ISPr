################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Agenda.cpp \
../src/Contacto.cpp \
../src/Ficherotexto.cpp \
../src/Funciones.cpp \
../src/Menu.cpp 

OBJS += \
./src/Agenda.o \
./src/Contacto.o \
./src/Ficherotexto.o \
./src/Funciones.o \
./src/Menu.o 

CPP_DEPS += \
./src/Agenda.d \
./src/Contacto.d \
./src/Ficherotexto.d \
./src/Funciones.d \
./src/Menu.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


