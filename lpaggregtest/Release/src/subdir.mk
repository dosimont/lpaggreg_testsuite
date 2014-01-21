################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/CSVIterator.cpp \
../src/CSVRow.cpp \
../src/DLPAggreg2Test.cpp \
../src/DLPAggreg2Test2.cpp \
../src/NLPAggreg1Test.cpp \
../src/OLPAggreg1Test.cpp \
../src/Test.cpp 

OBJS += \
./src/CSVIterator.o \
./src/CSVRow.o \
./src/DLPAggreg2Test.o \
./src/DLPAggreg2Test2.o \
./src/NLPAggreg1Test.o \
./src/OLPAggreg1Test.o \
./src/Test.o 

CPP_DEPS += \
./src/CSVIterator.d \
./src/CSVRow.d \
./src/DLPAggreg2Test.d \
./src/DLPAggreg2Test2.d \
./src/NLPAggreg1Test.d \
./src/OLPAggreg1Test.d \
./src/Test.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


