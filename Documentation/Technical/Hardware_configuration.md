
# TECHNICAL DOCUMENTATION IS STILL IN BUILD PROCESS

# components:

## Technical Specifications of the analog dissolved oxygen sensor X-SEN0237-A
  
![oxygen_sensor photo](../Images/oxygen_sensor.jpg)
  
### main parameter  
Supply Voltage: 3.3 V to 5 V  
Output Signal: 0 V to 3 V  
Probe Type: Galvanic  
Detection Range: 0 to 20 mg/L  
Response Time: Up to 98% within 90 s  
Pressure Range: 0 to 50 PSI  
Electrode Lifespan: 1 year
  
### physical size  
Cable Length: 2 m  
Probe Connector: BNC  
Signal Connector: Gravity analog interface  
Board Size: 42 x 32 mm  
  
### Maintenance Interval:  
Membrane replacement: 1 to 2 months in turbid water, 4 to 5 months in clear water  
Solution replacement: Once a month  


## Technical Specifications of  Analog pH Sensor SEN0161
  
![ph_meter photo](../Images/ph_meter.jpg)
  
### main parameter  
Supply Voltage: 5 V  
Measurement Range: 0 pH to 14 pH  
Operating Temperature: 0 °C to 60 °C  
Accuracy: +/- 0.1 pH (at 25 °C)  
Response Time: Up to 1 minute  

### physical size  
pH Sensor with BNC Connector  
Interface: PH2.0  
Gain Adjustment: Via potentiometer  
Cable for Connection to DFRobot IO Expansion Shield  
Board Size: 43 x 32 mm  

## Technical Specifications of  peristaltic pump DFR0523
  
![peristaltic pump](../Images/perystaltic_pump.jpg)

### Motor Driver Specifications
  
Input Voltage: 5 - 6 V  
Max Continuous Operating Current: 1.8 A  
Peak Current: 2.5 A  
Idle Current: < 1 mA  
PPM Signal Resolution: 1 µs  
PPM Signal Positive Pulse Width: 500 µs - 2500 µs  
Pulse Width Range - Movement: 500 µs - 1400 µs (500 µs: maximum speed)  
Pulse Width Range - Stop: 1400 µs - 1600 µs  
Reversed Pulse Width Range: 1600 µs - 2500 µs (2500 µs: maximum speed)  
PPM Signal Frequency: 50 Hz (servo control signal)  
  
### physical size  

Connector: Gravity  
Size: 27.4 x 28.7 mm  


## Peristaltic Pump Specifications VMA447

![peristaltic pump](../Images/perystaltic_pump_2.jpg)

### Motor Driver Specifications

Drive Type: DC motor  
Rated Voltage: 6 V  
Rated Power: 5 W  

### Tube parameter:

Tube Material: BPT (Biocompatible Polymer Tubing)  
Inner Diameter: 2.5 mm  
Outer Diameter: 4.5 mm  
Pump Material: Plastic  
Pulsation: 3 rollers, low pulsation  
Flow Rate: > 45 ml/min  
Operating Temperature: 0 to 40 °C  


## Arduino Uno Rev3 microcontroller:

![arduino board](../Images/arduino_board.jpg)

### main parameter

Supply voltage: 7V to 12V  
Model: Arduino Uno  
Microcontroller: ATmega328  
Maximum clock frequency: 16 MHz  
SRAM memory: 2 kB  
Flash memory: 32 kB (5 kB reserved for bootloader)  
EEPROM memory: 1 kB  

## XL4016 step down converter TODO check parameter

![step down converter](../Images/step-down_conventer.jpg)

Converter type: Step-down  
Input voltage: 5 – 40 V  
Output voltage: 1.25 – 36 V (adjustable)  
Converter chip: XL4016  
Output current: 0 – 5 A  
Maximum output current: 8 A (with heatsink, included)  
Maximum output power: 250W  
Power LED  
Reverse polarity protection.  
Efficiency: Max 95%  
Frequency: 180 kHz  
Built-in voltmeter to measure the output voltage  
Operating temperature: -40 ÷ 85 °C  
Mounting holes  
Size: 60 x 37 mm  

## 2-channel HW-95 L298N motor controller

![motor controller](../Images/motor_controller.jpg)

1 Driver chip: L298N dual H-bridge driver chip  
2 Terminal driver part of the supply area VMS: +5V ~ +35V  
3 Drive part of the peak current Io: 2A / Bridge  
4 Logical part of the terminal power supply range Vss :4.5-5 .5V  
5 Logical part of the operating current range: 0 - 36mA  
6 The control signal input voltage range: 4.5-5.5V low 0V high  
7 Maximum power consumption: 20W  
8 Storage temperature: -25 to +130  
9 Driver Board Size: 55mm * 60mm * 30mm  
10 Driver board Weight: 33g  
11 Other features: control direction indicator, power indicator, current detection, logical part of  
the plate to take power interface.  

## LCD - LCM1602 with I2C adapter - HW-61
![LCD](../Images/I2C_LCD.jpg)  

LCD display 2x16 characters  
Character color: white  
Backlight: blue  
Module size: 80 x 36 mm  
Character dimensions: 2.45 x 5.00 mm  
I2C bus converter  
No resistors pulling up the I2C bus lines (switched on in Arduino)  
Converter based on the PCF8574  
Soldered-in potentiometer for contrast adjustment  
Possibility to control the backlight via the I2C bus  

## Encoder with button - Iduino SE055
![Encoder](../Images/Encode.jpg)  

Power supply voltage: 5 V  
Detects clockwise and counterclockwise rotation  
Knob button  
Number of steps in 360°: 20 steps  
Knob diameter: 6 mm  
Knob type: beveled (D)  
Module dimensions: 32 x 30 x 20 mm  
Weight: 20 g  

## SD reader - HW-125
![SD reader](../Images/SD_reader.jpg)  

Supply voltage: 3.3 V or 5 V  
Communication interface: SPI  
Built-in 3.3 V voltage regulator (LM1117)  
Installed SD card slot with ejector  
Module dimensions: 50 x 31 mm  
Mounting hole diameter: 2.2 mm  