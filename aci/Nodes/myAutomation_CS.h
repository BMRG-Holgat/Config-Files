/* This is an automation example file.
 *  The presence of a file called "myAutomation.h" brings EX-RAIL code into
 *  the command station.
 *  The automation may have multiple concurrent tasks.
 *  A task may 
 *  - Act as a ROUTE setup macro for a user to drive over 
 *  - drive a loco through an AUTOMATION 
 *  - automate some cosmetic part of the layout without any loco.
 *  
 *  At startup, a single task is created to execute the startup sequence.
 *  This task may simply follow a route, or may START  
 *  further tasks (that is.. send a loco out along a route).
 *  
 *  Where the loco id is not known at compile time, a new task 
 *  can be created with the command:
 *  </ START [cab] route> 
 *  
 *  A ROUTE, AUTOMATION or SEQUENCE are internally identical in ExRail terms  
 *  but are just represented differently to a Withrottle user:
 *  ROUTE(n,"name") - as Route_n .. to setup a route through a layout
 *  AUTOMATION(n,"name") as Auto_n .. to send the current loco off along an automated journey
 *  SEQUENCE(n) is not visible to Withrottle.
 *  
 */
HAL_IGNORE_DEFAULTS

#include "IODevice.h"
#include "IO_HALDisplay.h"


HAL(PCA9555,220,16,0x20)
HAL(MCP23017,200,16,0X27)
HAL(PCA9685,100,16,0X40)

SHARED_WRITE_VPINS(300,8)
REMOTE_SENSOR(8300, 8) 


SERVO_TURNOUT(TRN1,100,330,290,Slow,"Access")
SERVO_TURNOUT(TRN2,101,250,250,Slow,"Exit")
SERVO_TURNOUT(TRN3,102,250,250,Slow,"Header")


SIGNAL(104,0,105) //entry
SIGNAL(106,0,107) //stn
SIGNAL(108,0,109) //through


//Start of demonstration layout sequences
// taken from the big picture
//Turnout Aliases
ALIAS(TRN1, 100)
ALIAS(TRN2, 101)
ALIAS(TRN3, 102)
//Sensor Aliases
ALIAS(SNS1_TRN1_APP, 200)
ALIAS(SNS2_MAIN_TRN1_EX, 201)
ALIAS(SNS3_STN, 202)
ALIAS(SNS4_MAIN_TRN2_APP, 203)
ALIAS(SNS5_STN_TRN2_APP, 204)
ALIAS(SNS6_TRN2_EX, 205)
//Signal Aliases
ALIAS(SIG1_TRN1_APP, 104)
ALIAS(SIG2_TRN2_GO, 106)
ALIAS(SIG3_STN_EX, 108)
//Block Aliases
ALIAS(BLK1_TRN1_APP, 1)
ALIAS(BLK2_MAIN_HOLD, 2)
ALIAS(BLK3_STN, 3)
ALIAS(BLK4_TRN2_EX, 4)
//Sequence Aliases
ALIAS(BLK1_EXIT, 1)
ALIAS(BLK1_BLK2, 2)
ALIAS(BLK1_BLK3, 3)
ALIAS(BLK2_BLK4, 4)
ALIAS(BLK3_BLK4, 5)
ALIAS(BLK4_BLK1, 6)
ALIAS(CHOOSE_BLK2, 60)

// Start up with turnouts/points closed and signals red
CLOSE(TRN1)
CLOSE(TRN2)
CLOSE(TRN3)
RED(SIG1_TRN1_APP)
RED(SIG2_TRN2_GO)
RED(SIG3_STN_EX)


#define toggleRelay(pin,relay,route_num) IF(pin) RESET(relay) ROUTE_CAPTION( route_num,"ON") ELSE SET(relay) ROUTE_CAPTION( route_num,"OFF") ENDIF


// Reserve main blocks for loco locations.
RESERVE(BLK1_TRN1_APP)
RESERVE(BLK2_MAIN_HOLD)
RESERVE(BLK4_TRN2_EX)
// Set locos into correct locations
/*
SENDLOCO(1, BLK1_EXIT)
SENDLOCO(2, BLK2_BLK4)
SENDLOCO(3, BLK4_BLK1)
*/

DONE // Complete setup of layout.


//Main sequences to get the trains rolling after each other
// Sequence to exit block 1, and choose whether to go to the station or continue on main
SEQUENCE(BLK1_EXIT)
  IF(CHOOSE_BLK2)
    UNLATCH(CHOOSE_BLK2)
    FOLLOW(BLK1_BLK2)
  ELSE
    LATCH(CHOOSE_BLK2)
    FOLLOW(BLK1_BLK3)
  ENDIF

// Sequence to go from block 1 to block 2
SEQUENCE(BLK1_BLK2)
  RESERVE(BLK2_MAIN_HOLD)
  IFTHROWN(TRN1)
    AMBER(SIG1_TRN1_APP)
    DELAY(2000)
    RED(SIG1_TRN1_APP)
    CLOSE(TRN1)
    DELAY(2000)
  ENDIF
  GREEN(SIG1_TRN1_APP)
  FWD(20)
  AFTER(SNS2_MAIN_TRN1_EX)
  FREE(BLK1_TRN1_APP)
  AT(SNS4_MAIN_TRN2_APP)
  FOLLOW(BLK2_BLK4)

// Sequence to go from block 1 to block 3
SEQUENCE(BLK1_BLK3)
  RESERVE(BLK3_STN)
  IFCLOSED(TRN1)
    AMBER(SIG1_TRN1_APP)
    DELAY(2000)
    RED(SIG1_TRN1_APP)
    THROW(TRN1)
    DELAY(2000)
  ENDIF
  GREEN(SIG1_TRN1_APP)
  FWD(10)
  AT(SNS3_STN)
  STOP
  FREE(BLK1_TRN1_APP)
  DELAYRANDOM(10000, 15000)
  FWD(10)
  AT(SNS5_STN_TRN2_APP)
  FOLLOW(BLK3_BLK4)

// Sequence to go from block 2 to block 4
SEQUENCE(BLK2_BLK4)
  RESERVE(BLK4_TRN2_EX)
  IFTHROWN(TRN2)
    AMBER(SIG2_TRN2_GO)
    AMBER(SIG3_STN_EX)
    DELAY(2000)
    RED(SIG2_TRN2_GO)
    RED(SIG3_STN_EX)
    CLOSE(TRN2)
    DELAY(2000)
  ENDIF
  GREEN(SIG2_TRN2_GO)
  FWD(20)
  AFTER(SNS4_MAIN_TRN2_APP)
  FREE(BLK2_MAIN_HOLD)
  FOLLOW(BLK4_BLK1)

// Sequence to go from block 3 to block 4
SEQUENCE(BLK3_BLK4)
  RESERVE(BLK4_TRN2_EX)
  IFCLOSED(TRN2)
    AMBER(SIG2_TRN2_GO)
    AMBER(SIG3_STN_EX)
    DELAY(2000)
    RED(SIG2_TRN2_GO)
    RED(SIG3_STN_EX)
    THROW(TRN2)
    DELAY(2000)
  ENDIF
  GREEN(SIG3_STN_EX)
  FWD(20)
  AFTER(SNS5_STN_TRN2_APP)
  FREE(BLK3_STN)
  FOLLOW(BLK4_BLK1)

// Sequence to move from block 4 back to block 1
SEQUENCE(BLK4_BLK1)
  RESERVE(BLK1_TRN1_APP)
  FWD(30)
  AFTER(SNS1_TRN1_APP)
  FREE(BLK4_TRN2_EX)
  FOLLOW(BLK1_EXIT)

ROUTE(100,"Left_Side")
  toggleRelay(8307, 307, 100)
DONE
ROUTE(101,"Lower_Right_Side1")
  toggleRelay(8306, 306, 101)
DONE
ROUTE(102,"Lower_Right_Side2")
  toggleRelay(8305, 305, 102)
DONE
ROUTE(103,"Upper_Right_Side1")
  toggleRelay(8304, 304, 103)
DONE
ROUTE(104,"Upper_Right_Side2")
  toggleRelay(8303, 303, 104)
DONE

