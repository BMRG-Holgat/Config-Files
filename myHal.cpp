//  Sample myHal.cpp file.
//
// To use this file, copy it to myHal.cpp and uncomment the directives and/or
// edit them to satisfy your requirements.  If you only want to use up to 
// two MCP23017 GPIO Expander modules and/or up to two PCA9685 Servo modules,
// then you don't need this file as DCC++EX configures these for free!

// Note that if the file has a .cpp extension it WILL be compiled into the build
// and the halSetup() function WILL be invoked.
//
// To prevent this, temporarily rename the file to myHal.txt or similar.
//

// The #if directive prevent compile errors for Uno and Nano by excluding the 
//  HAL directives from the build.
#if !defined(IO_NO_HAL)

// Include devices you need.
#include "IODevice.h"
#include "IO_EXIOExpander.h"
#include "IO_MCP23017.h"
#include "IO_HCSR04.h"    // Ultrasonic range sensor
//#include "IO_VL53L0X.h"   // Laser time-of-flight sensor
//#include "IO_DFPlayer.h"  // MP3 sound player
#include "IO_I2CDFPlayer.h"
#include "IO_HALDisplay.h" // Haldisplays
#include "DCC.h"


//#include "IO_EXTurntable.h"   // Turntable-EX turntable controller
//#include "IO_EXFastClock.h"  // FastClock driver


//Shows current 8 locos running and direction on 2 screens
void updateLocoScreen() {

  for (int i=0; i<8; i++) {
    if (DCC::speedTable[i].loco > 0) {
      int speed = DCC::speedTable[i].speedCode;
      char direction = (speed & 0x80) ? 'F' : 'R';
      speed = speed & 0x7e;
      if (speed > 0) speed = speed - 1;
      SCREEN(2, i, F("Loco: %4d %3d %c"), DCC::speedTable[i].loco,
      speed, direction);
    }
  }
}  

//==========================================================================
// The function halSetup() is invoked from CS if it exists within the build.
// The setup calls are included between the open and close braces "{ ... }".
// Comments (lines preceded by "//") are optional.
//==========================================================================

void halSetup() {
//I2CManager.forceClock(100000);
I2CManager.forceClock(50000);


  //=======================================================================
  // The following directive defines a PCA9685 PWM Servo driver module.
  //=======================================================================
  // The parameters are: 
  //   First Vpin=100
  //   Number of VPINs=16 (numbered 100-115)
  //   I2C address of module=0x40
  //PCA9685::create(100, 16, {I2CMux_0,SubBus_7,0x45});
  //PCA9685::create(212, 16, 0x48);
 
  //PCF8574::create(318,8,{I2CMux_0,SubBus_3,0x20}); // IR Sensors
  MCP23017::create(318,16,{I2CMux_0,SubBus_3,0x26});
  MCP23017::create(858,16,{I2CMux_0,SubBus_3,0x25}); // Houses on Board 3
  
  EXIOExpander::create(300, 18, {I2CMux_0,SubBus_3,0x69}); // Board 1
  EXIOExpander::create(362, 62, {I2CMux_0,SubBus_3,0x61}); // Board 2
  EXIOExpander::create(424, 62, {I2CMux_0,SubBus_3,0x62}); // Board 3
  EXIOExpander::create(486, 62, {I2CMux_0,SubBus_3,0x63}); // Board 4 
  EXIOExpander::create(548, 62, {I2CMux_0,SubBus_1,0x65}); // Board 5
  EXIOExpander::create(610, 62, {I2CMux_0,SubBus_4,0x65}); // Board 6  
  EXIOExpander::create(672, 62, {I2CMux_0,SubBus_4,0x66}); // Board 7
  EXIOExpander::create(734, 62, {I2CMux_0,SubBus_4,0x67}); // Board 8
  EXIOExpander::create(796, 62, {I2CMux_0,SubBus_4,0x68}); // Board 9 

   //PCA9685::create(296, 16, {I2CMux_0,SubBus_2,0x45});
  PCA9685::create(120, 16, {I2CMux_0,SubBus_3,0x40}); // Board 1
   //PCA9685::create(136, 16, {I2CMux_0,SubBus_3,0x41}); // Board 2
   //PCA9685::create(152, 16, {I2CMux_0,SubBus_3,0x48}); // Board 2
   //PCA9685::create(168, 16, {I2CMux_0,SubBus_3,0x42}); // Board 3
  PCA9685::create(184, 16, {I2CMux_0,SubBus_3,0x43}); // Board 4 turnout and signals
  PCA9685::create(264, 16, {I2CMux_0,SubBus_3,0x45}); // Board 4 (signals?)
   //PCA9685::create(200, 16, {I2CMux_0,SubBus_1,0x44}); // Board 5
  PCA9685::create(280, 16, {I2CMux_0,SubBus_4,0x47}); // Board 7 Signals
   //PCA9685::create(216, 16, {I2CMux_0,SubBus_0,0x45}); // Board 8
  PCA9685::create(248, 16, {I2CMux_0,SubBus_4,0x42}); // Board 9

   //PCA9685::create(232, 16, {I2CMux_0,SubBus_4,0x46}); // Board 8 Fiddle Yard


  //=======================================================================
  // The following directive defines an MCP23017 16-port I2C GPIO Extender module.
  //=======================================================================
  // The parameters are: 
  //   First Vpin=196
  //   Number of VPINs=16 (numbered 196-211)
  //   I2C address of module=0x22

  
  //MCP23017::create(796, 16, {I2CMux_1,SubBus_0,0x26}); // Board 9


  // Alternative form, which allows the INT pin of the module to request a scan
  // by pulling Arduino pin 40 to ground.  Means that the I2C isn't being polled
  // all the time, only when a change takes place. Multiple modules' INT pins
  // may be connected to the same Arduino pin.

  //MCP23017::create(196, 16, 0x22, 40);


  //=======================================================================
  // The following directive defines an MCP23008 8-port I2C GPIO Extender module.
  //=======================================================================
  // The parameters are: 
  //   First Vpin=300
  //   Number of VPINs=8 (numbered 300-307)
  //   I2C address of module=0x22

  //MCP23008::create(300, 8, 0x22);



  //=======================================================================
  // The following directive defines a PCF8574 8-port I2C GPIO Extender module.
  //=======================================================================
  // The parameters are: 
  //   First Vpin=200
  //   Number of VPINs=8 (numbered 200-207)
  //   I2C address of module=0x23

  //PCF8574::create(812, 8, 0x23);
  


  // Alternative form using INT pin (see above)

  //PCF8574::create(200, 8, 0x23, 40);


  //=======================================================================
  // The following directive defines an HCSR04 ultrasonic ranging module.
  //=======================================================================
  // The parameters are: 
  //   Vpin=2000 (only one VPIN per directive)
  //   Number of VPINs=1
  //   Arduino pin connected to TRIG=30
  //   Arduino pin connected to ECHO=31
  //   Minimum trigger range=20cm (VPIN goes to 1 when <20cm)
  //   Maximum trigger range=25cm (VPIN goes to 0 when >25cm)
  // Note: Multiple devices can be configured by using a different ECHO pin
  // for each one.  The TRIG pin can be shared between multiple devices.
  // Be aware that the 'ping' of one device may be received by another
  // device and position them accordingly!

  //HCSR04::create(2000, 30, 31, 20, 25);
  //HCSR04::create(2001, 30, 32, 20, 25);


  //=======================================================================
  // The following directive defines a single VL53L0X Time-of-Flight range sensor.
  //=======================================================================
  // The parameters are:
  //   VPIN=5000
  //   Number of VPINs=1
  //   I2C address=0x29 (default for this chip)
  //   Minimum trigger range=200mm (VPIN goes to 1 when <20cm)
  //   Maximum trigger range=250mm (VPIN goes to 0 when >25cm)

  //VL53L0X::create(5000, 1, 0x29, 200, 250); 

  // For multiple VL53L0X modules, add another parameter which is a VPIN connected to the
  // module's XSHUT pin.  This allows the modules to be configured, at start,
  // with distinct I2C addresses.  In this case, the address 0x29 is only used during
  // initialisation to configure each device in turn with the desired unique I2C address.
  // The examples below have the modules' XSHUT pins connected to the first two pins of 
  // the first MCP23017 module (164 and 165), but Arduino pins may be used instead.
  // The first module here is given I2C address 0x30 and the second is 0x31.

  //VL53L0X::create(5000, 1, 0x30, 200, 250, 164); 
  //VL53L0X::create(5001, 1, 0x31, 200, 250, 165); 


  //=======================================================================
  // Play mp3 files from a Micro-SD card, using a DFPlayer MP3 Module.
  //=======================================================================
  // Parameters: 
  //   10000 = first VPIN allocated.
  //   10 = number of VPINs allocated.
  //   Serial1 = name of serial port (usually Serial1 or Serial2).
  // With these parameters, up to 10 files may be played on pins 10000-10009.
  // Play is started from EX-RAIL with SET(10000) for first mp3 file, SET(10001)
  // for second file, etc.  Play may also be initiated by writing an analogue
  // value to the first pin, e.g. SERVO(10000,23,0) will play the 23rd mp3 file.
  // SERVO(10000,23,30) will do the same thing, as well as setting the volume to 
  // 30 (maximum value).
  // Play is stopped by RESET(10000) (or any other allocated VPIN).
  // Volume may also be set by writing an analogue value to the second pin for the player, 
  // e.g. SERVO(10001,30,0) sets volume to maximum (30).
  // The EX-RAIL script may check for completion of play by calling WAITFOR(pin), which will only proceed to the
  // following line when the player is no longer busy.
  // E.g.
  //    SEQUENCE(1)
  //      AT(164)           // Wait for sensor attached to pin 164 to activate
  //      SET(10003)        // Play fourth MP3 file
  //      LCD(4, "Playing") // Display message on LCD/OLED
  //      WAITFOR(10003)    // Wait for playing to finish
  //      LCD(4, " ")       // Clear LCD/OLED line 
  //      FOLLOW(1)         // Go back to start

    //DFPlayer::create(1000, 5, Serial3, true);
    //DFPlayer::create(2000, 15, Serial5, true);
  //  DFPlayerPro::create(5000, 5, Serial2, true);


  //I2CDFPlayer::create(1st vPin,vPins,I2C address,UART{0|1},AM{0|1});
  I2CDFPlayer::create(1000, 4, {I2CMux_0,SubBus_3,0x4D}, 0);
  //I2CDFPlayer::create(10050, 1, 0x49, 0, 1);


  //=======================================================================
  // The following directive defines an EX-Turntable turntable instance.
  //=======================================================================
  // EXTurntable::create(VPIN, Number of VPINs, I2C Address)
  //
  // The parameters are:
  //   VPIN=600
  //   Number of VPINs=1 (Note there is no reason to change this)
  //   I2C address=0x60
  //
  // Note that the I2C address is defined in the EX-Turntable code, and 0x60 is the default.

  //EXTurntable::create(600, 1, 0x60);


  //=======================================================================
  // The following directive defines an EX-IOExpander instance.
  //=======================================================================
  // EXIOExpander::create(VPIN, Number of VPINs, I2C Address)
  //
  // The parameters are:
  //   VPIN=an available Vpin
  //   Number of VPINs=pin count (must match device in use as per documentation)
  //   I2C address=an available I2C address (default 0x65)
  //
  // Note that the I2C address is defined in the EX-IOExpander code, and 0x65 is the default.
  // The example is for an Arduino Nano.
    
    
    //EXIOExpander::create(486, 62,{I2CMux_0,SubBus_0,0x63}); // Testing board
    //EXIOExpander::create(250, 62, 0x63); // Testing board
    



  //=======================================================================
  // The following directive defines a rotary encoder instance.
  //=======================================================================
  // The parameters are: 
  //   firstVpin = First available Vpin to allocate
  //   numPins= Number of Vpins to allocate, can be either 1 or 2
  //   i2cAddress = Available I2C address (default 0x70)

  //RotaryEncoder::create(firstVpin, numPins, i2cAddress);
  //RotaryEncoder::create(700, 1, 0x70);
  //RotaryEncoder::create(701, 2, 0x71);

 //=======================================================================
  // The following directive defines an EX-FastClock instance.
  //=======================================================================
  // EXFastCLock::create(I2C Address)
  //
  // The parameters are:
  //   
  //   I2C address=0x55 (decimal 85)
  //
  // Note that the I2C address is defined in the EX-FastClock code, and 0x55 is the default.

 
  //   EXFastClock::create(0x55);

 //==========================================================================
 //  Folllowing sets up displays
 //==========================================================================
 // HALDisplay<LiquidCrystal>::create(2, {I2CMux_0,SubBus_0,0x27}, 20, 4);
 //
 // 

 //HALDisplay<LiquidCrystal>::create(4, { I2CMux_0,SubBus_0,0x27 }, 16, 2);
 //HALDisplay<LiquidCrystal>::create(3, { I2CMux_0,SubBus_1,0x26 }, 16, 2);
 //HALDisplay<LiquidCrystal>::create(2, { I2CMux_0,SubBus_,0x27 }, 16, 2);
HALDisplay<OLED>::create(3,{I2CMux_0,SubBus_1,0x3C},128,64);
HALDisplay<OLED>::create(2,{I2CMux_0,SubBus_1,0x3D},128,64);
HALDisplay<OLED>::create(4,{I2CMux_0,SubBus_0,0x3D},128,64);

  // Update displays with loco numbers and direction
UserAddin::create(updateLocoScreen, 1000);

}

#endif
