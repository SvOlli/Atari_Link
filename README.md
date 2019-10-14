Atari 2600 VCS Link Cable Software
==================================

Hardware:
The design is based upon the Ardiuno platform. I suggest you go for a clone of
the Arduino Nano board. ( http://arduino.cc/en/Main/ArduinoBoardNano ) It's
cheaper than the current standard boards Duemilanove and Uno, and the layout
fits the design of the cable slightly better. Duemilanove and Uno will also
work, but either the wiring will be not so straight forward, or the software
needs to be set up for the different pin layout you decide.

  This is the wiring I used for the software:

```  
            __|USB|__
   D13(PB5)|  |___|  |(PB4)D12---B SUB-D 1
   3V3(3V3)|  _____  |(PB3)D11---B SUB-D 2
  AREF     | |     | |(PB2)D10---B SUB-D 3
    A7     | | AVR | |(PB1)D9----B SUB-D 4
    A6     | | MCU | |(PB0)D8----B SUB-D 6
    A5(PC5)| |_____| |(PD7)D7----B SUB-D 8
    A4(PC4)|         |(PD6)D6----A SUB-D 1
    A3(PC3)|         |(PD5)D5----A SUB-D 2
    A2(PC2)|         |(PD4)D4----A SUB-D 3
    A1(PC1)|         |(PD3)D3----A SUB-D 4
    A0(PC0)|         |(PD2)D2----A SUB-D 6
   +5V     |         |     GND---A SUB-D 8
   RST(PC6)|         |(PC6)RST
   GND     |   JTAG  |(PD0)D0RX
   VIN(*)  |_________|(PD1)D1TX
```

(*) If you want to use the board without supplying power via USB, connect VIN
to "A SUB-D 7". Do NOT use "B SUB-D", since a dataline has been misused for
GND there.

All five lines of lines used for a standard joystick are also used for linking.
Assume that the cable is plugged into the right controller port the cable is
used like this:

SWCHA & $08 (write): write clock
SWCHA & $04 (write): write data
SWCHA & $02 (write): read clock
SWCHA & $01 (read) : read data
INPT5 & $80 (read) : high = buffer in the cable is empty

The clock lines are toggled with
```
  lda SWCHA
  eor #$02 ; or #$08
  sta SWCHA
```
to signalize that the data bit has been read (or written)


Software:
- The Atari 2600 code is written using ca65 from the cc65-package.
- The Arduino software is built using avr-gcc.
- The Arduino software can be transferred using avrdude.
- The Arduino software does NOT support the Arduino IDE, since the whole system
  including the libraries for the target are just a pile of crap.

If both avr-gcc and cc65 are installed all the software necessary for testing
the cable can be build just by running "make".

There are five pieces of software included:
- bitsetter: Arduino test program for setting all GPIOs (for debugging)
- bittester: 2600 test programm displaying all io-ports
- linkcable: The firmware for the link cable
- looptest:  2600 test programm for a loopback-test connecting link cable to both
  controller ports
- queuetest: a small test utility to verify functionality of the software queue.

I guess there will be some questions left, so contact me on AtariAge,
SvOlli
