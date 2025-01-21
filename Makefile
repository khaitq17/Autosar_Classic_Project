# Compiler and flags
CC = gcc
CFLAGS = -Wall -g\
-I.\BSW\ECU_Abstraction\IoHwAb\
-I.\BSW\MCAL\Adc\
-I.\BSW\MCAL\Can\
-I.\BSW\MCAL\Dio\
-I.\BSW\MCAL\Pwm\
-I.\BSW\MCAL\
-I.\BSW\Services\Dcm\
-I.\BSW\Services\Dem\
-I.\BSW\Services\Mem\
-I.\BSW\Services\Os\
-I.\BSW\Services\Pdu_Router\
-I.\RTE\
-I.\SWC
# Object directory
OBJDIR = bin
# Executable
TARGET = $(OBJDIR)/ecu

SRC = .\BSW\ECU_Abstraction\IoHwAb\IoHwAb_BatterySOC.c \
.\BSW\ECU_Abstraction\IoHwAb\IoHwAb_BrakeSensor.c \
.\BSW\ECU_Abstraction\IoHwAb\IoHwAb_InclinationSensor.c \
.\BSW\ECU_Abstraction\IoHwAb\IoHwAb_LoadSensor.c \
.\BSW\ECU_Abstraction\IoHwAb\IoHwAb_MotorDriver.c \
.\BSW\ECU_Abstraction\IoHwAb\IoHwAb_SpeedSensor.c \
.\BSW\ECU_Abstraction\IoHwAb\IoHwAb_ThrottleSensor.c \
.\BSW\ECU_Abstraction\IoHwAb\IoHwAb_TorqueSensor.c \
.\BSW\ECU_Abstraction\IoHwAb\IoHwAb_WheelAngularVelocity.c \
.\BSW\MCAL\Adc\Adc.c \
.\BSW\MCAL\Can\Can.c \
.\BSW\MCAL\Dio\Dio.c \
.\BSW\MCAL\Pwm\Pwm.c \
.\BSW\Services\Dcm\Dcm.c \
.\BSW\Services\Dem\Dem.c \
.\BSW\Services\Mem\Mem.c \
.\BSW\Services\Os\Os.c \
.\BSW\Services\Pdu_Router\Pdu_Router.c \
.\Main.c \
.\RTE\Rte_RegenBrakeControl.c \
.\RTE\Rte_TorqueControl.c \
.\RTE\Rte_TractionControl.c \
.\SWC\Regen_Brake_Control.c \
.\SWC\Torque_Control.c \
.\SWC\Traction_Control.c 

# Object files
OBJ = $(SRC:%.c=$(OBJDIR)/%.o)

# Build executable
$(TARGET): $(OBJ)
	@echo "Linking all objects to create $(TARGET)..."
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)
	@echo "Build successful!"

# Compile object files
$(OBJDIR)/%.o: %.c
	if not exist "$(dir $@)" mkdir "$(dir $@)"
	$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled: $<"

# Clean up
.PHONY: clean
clean:
	@echo "Cleaning up..."
	del /Q $(OBJDIR)\*.*
	rmdir /S /Q $(OBJDIR)
	@echo "Clean done!"

# Run program
.PHONY: run
run: $(TARGET)
	@echo "Running program..."
	$(TARGET)
