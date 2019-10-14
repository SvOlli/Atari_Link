
PROJECT = bitsetter
SRCS = bitsetter.c
SRCTMP = $(SRCS:.cpp=.o)
OBJS = $(SRCTMP:.c=.o)
DEVICE = /dev/ttyUSB0
BAUD = 57600

MCU = atmega328p
CPU_FREQ = 16000000L
ARDUINO = 100

CROSS = avr-
CC = $(CROSS)gcc
CXX = $(CROSS)g++
OBJCOPY = $(CROSS)objcopy
AR = $(CROSS)ar
AVRDUDE = avrdude
TERMCOM = microcom
CFLAGS = -c -g -Os -Wall -pedantic -fno-exceptions -ffunction-sections -fdata-sections -mmcu=$(MCU) -DF_CPU=$(CPU_FREQ) -DARDUINO=$(ARDUINO)
CXXFLAGS = $(CFLAGS)
LDFLAGS = -Os -Wl,--gc-sections -mmcu=$(MCU) -lm

all: $(PROJECT).hex

clean:
	rm -f $(OBJS)

realclean: clean
	rm -f $(PROJECT).hex $(PROJECT).eep $(PROJECT).elf

trans: $(PROJECT).hex
	$(AVRDUDE) -v -v -p$(MCU) -carduino -P$(DEVICE) -b$(BAUD) -D -Uflash:w:$<:i

term:
	$(TERMCOM) -p $(DEVICE) -s $(BAUD)

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

%.elf: $(OBJS)
	$(CC) -o $@ $(OBJS) $(LDFLAGS)

%.eep: %.elf
	$(OBJCOPY) -O ihex -j .eeprom --set-section-flags=.eeprom=alloc,load --no-change-warnings --change-section-lma .eeprom=0 $< $@

%.hex: %.elf
	$(OBJCOPY) -O ihex -R .eeprom $< $@

