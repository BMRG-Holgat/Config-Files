/*
 * Holgate automation file
 *  
 * Kept now on github https://github.com/BMRG-Holgat/Config-Files.git
 *
 * V 0.0.1
 * Moved config files to github for better control
 *
 * V 0.0.0
 * Adding Fiddleyards & main lines
 *  aliases for turnouts
 *  Define turnouts
 * 
*/


EXRAIL   // myAutomation must start with the EXRAIL instruction
  // This is the default starting route, AKA SEQUENCE(0)  
//  SENDLOCO(3,1) // send loco 3 off along route 1
//  SENDLOCO(10,2) // send loco 10 off along route 2
  DONE     // This just ends the startup thread, leaving 2 others running.

//LCD Displays
  //HAL(HALDisplay<LiquidCrystal>, 2, {I2CMux_0,SubBus_0,0x27}, 20, 4) 
  //HAL(HALDisplay<LiquidCrystal>, 3, {I2CMux_0,SubBus_0,0x26}, 20, 4) 
  //HAL(HALDisplay<LiquidCrystal>, 4, {I2CMux_0,SubBus_2,0x27}, 20, 4)
/*
 * Holgate
 * Key 
 * York
 * DGS -> Down Goods Slow   - Track F
 * DFM -> Down Fast Mixed   - Track E
 * DMF -> Down Main Fast    - Track C
 * DSS -> Down Slow Sidings - Track G
 * London
 * UGS -> Up Goods Slow     - Track A
 * UMF -> Up Main Fast      - Track D
 * UFM -> Up Fast Mixed     - Track B
 * 
 * H -> Header track
 * 
 * FY -> Fiddle Yard
 * A -> Access
 * E -> Exit
 * 
 * DS -> Double Slip
 * 
 */

 

/* Include the following files
* 
* myTurnouts defines the servo turnouts
* mySensors defines sensor pins
* myDefinitions controls the user definitions
* myTurnoutAliases user values of turnouts
* myBlocks defines the blocks on each track
* myBlockAliases user values for each block
* mySetup inital setup sequence
* mySignals define signal pin allocation
* mySignalAliases user value for signal
* myStartupSequence defines how and what to start on power on
* 
*/
#include "mySequenceAliase.h"
#include "myTurnouts.h"
#include "myTurnoutAliases.h"
#include "myTurnoutPairs.h"
#include "mySensors.h"
#include "myBlocks.h"
#include "myBlockDetectors.h"
#include "myDefinitions.h"
#include "mySignals.h"
#include "mySignalAliases.h"
#include "myStartupSequence.h"
#include "myRoster.h"
#include "myRoutes.h"


DONE

//byPass latch aliases
ALIAS(AC_ByPass,100)

// Track sequences to be replace with call/return sequences.

#include "myTrackA-alt.h"
#include "myTrackA-Seq-Alias.h"
#include "myTrackA-Blocks.h"
#include "myTrackA-BD.h"
//#include "myTrackA-Call.h"
/*#include "myTrackB.h"
#include "myTrackB_FiddleYard.h"
#include "myTrackC.h"
#include "myTrackC_FiddleYard.h"
#include "myTrackD.h"
#include "myTrackD_FiddleYard.h"
#include "myTrackE.h"
#include "myTrackE_FiddleYard.h"
#include "myTrackF.h"
*/

/* set standard reserves at startup
RESERVE(A_Store_1)
RESERVE(A_Store_2)
RESERVE(A_Store_3)
*/
/* Build Routes
*
*/
//#include "myRoutes-TrackA.h"
/*#include "myRoutes-TrackB.h"
*/

AUTOMATION(10,"HST B test to Station Auto")
    /*RESERVE(UGS_FY_Exit)
    IFCLOSED(UGS_T6_A__FYUG_T10_E) //Board 2 lane cross
        trackChange(UGS_T6_A__FYUG_T10_E,UMF_T15_E__UGS_T6_A)
    ENDIF
    IFCLOSED(UGS_T1_H)
      THROW(UGS_T1_H)
    ENDIF
    RESERVE(UGS_STN_Hold)
    SET(1004)
    //set station signal red
    FWD(30)
    AT(BD_S1_AA)
    DELAY(2000)
    FWD(0)
    DELAYRANDOM(10000,15000)
    RESERVE(UGS_BK4_Stn_Exit)
    IFCLOSED(UGS_T2_E__DFM_T1_A)
      trackChange(UGS_T2_E__DFM_T1_A,UFM_T1_A__UGS_T2_E)
    ENDIF
    DELAY(1000)
    IFTHROWN(UGS_T6_A__FYUG_T10_E) //Board 2 lane cross
        trackChange(UGS_T6_A__FYUG_T10_E,UMF_T15_E__UGS_T6_A)
    ENDIF
    FWD(50)
    DELAY(18000)
    FWD(80)
    FREE(UGS_BK1_Stn_App)
    FREE(UGS_BK2_HEAD_1_AA_Ex)
    AT(32)
    IFTHROWN(UGS_T2_E__DFM_T1_A)
      trackChange(UGS_T2_E__DFM_T1_A,UFM_T1_A__UGS_T2_E)
    ENDIF
    FWD(0)*/
DONE
/*
SEQUENCE(30)
AT(566)
  GREEN(519)
    AT(504)
    STOP
    DELAYRANDOM(5000,10000)
    FWD(30)
    RED(519)
    THROW(9009)
    
FOLLOW(30)
*/

AUTOSTART SEQUENCE(33)
  SCREEN(2,0,"Fiddle Yard")
  SCREEN(2,1," Left TEST")
  SCREEN(3,0,"SCENIC")
  SCREEN(3,1,"TEST")
  SCREEN(4,0,"Fiddle Yard")
  SCREEN(4,1," Right TEST")
  DONE

//AUTOSTART SEQUENCE(22)
//  DELAY(10000)
//  PRINT("Playing sound Now!")
//  ANOUT(10010,1,10,0x0F)
  //PLAYSOUND(10010,1,10,PLAY)


  /*AUTOSTART
   ANOUT(10000,0,0,0x1A) // set DACON
   ANOUT(10000,0,0,0x07) // set EQ to NORMAL
   ANOUT(10000,0,0,0x16) // Stop any ongoing play
   DELAY(2000)
   ANOUT(10000,0,0,0x0C) // Do reset
   DELAY(2000)
   START(1)
   //START(2)
  DONE     // This just ends the startup thread, leaving 2 others running.

SEQUENCE(1)
ANOUT(10100,0,0,0x0C) // Do reset
   DELAY(2000)
PRINT("Starting seq 1")
  //ANOUT(10000,0,0,0x0C) // Do reset
   //DELAY(2000)
  ANOUT(10100,0,1,0x2B)   // Set folder to 1
  DELAY(2000)
  PRINT("Playing sound4")
  ANOUT(10100,4,10,0x0F)  // Grant Central
  WAITFOR(10100)
  //ANOUT(10000,0,0,0x0C) // Do reset
  //DELAY(2000)
  PRINT("Playing railway crossing")
  ANOUT(10000,0,2,0x2B)   // Set folder to 2
  DELAY(2000)
  ANOUT(10000,3,10,0x0F)  // Japanese railway crossing
  WAITFOR(10000)
  //ANOUT(10001,0,4,0x2B)   // Set folder to 4
  //DELAY(2000)
  //ANOUT(10001,4,15,0x0F)  // Sheep
  //WAITFOR(10001)
  //ANOUT(10001,0,6,0x2B)   // Set folder to 6
  //DELAY(2000)
  //ANOUT(10001,3,5,0x0F)  // Ships realy big horn 3 times
  //WAITFOR(10001)
  //DELAY(2000)
  PRINT("Ending Seq 1")
DONE

SEQUENCE(2)
  DELAY(2000)
  ANOUT(10000,0,10,0x06)
  DELAY(2000)
  ANOUT(10000,0,13,0x06)
  DELAY(2000)
  ANOUT(10000,0,17,0x06)
  DELAY(2000)
  ANOUT(10000,0,19,0x06)
  DELAY(2000)
  ANOUT(10000,0,21,0x06)
  DELAY(2000)
  ANOUT(10000,0,23,0x06)
  DELAY(2000)
  ANOUT(10000,0,21,0x06)
  DELAY(2000)
  ANOUT(10000,0,19,0x06)
  DELAY(2000)
  ANOUT(10000,0,17,0x06)
  DELAY(2000)
  ANOUT(10000,0,13,0x06)  
FOLLOW(2)
DONE */
  

ENDEXRAIL    // marks the end of the EXRAIL program. 
    
   
