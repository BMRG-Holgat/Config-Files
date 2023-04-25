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
 * /
 
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
#include "mySensors.h"
#include "myDefinitions.h"
#include "myTurnoutAliases.h"
//#include "myTrackA.h"
#include "myBlocks.h"
#include "mySignals.h"
#include "mySignalAliases.h"
#include "myStartupSequence.h"
#include "myRoutes-TrackB.h"



/* Startup test sequence for signals and servos
 *  Use this on rebuild
 */
/* #define reBuildLEDTest(id)
   RED(id) \
   DELAY(1000) \
   AMBER(id) \
   DELAY(1000) \
   GREEN(id) \
   DELAY(1000) \
   DONE

 #define seqTest
   reBuildLEDTest(100) \
   DELAY(2000) \
   rebuildLEDTest(101) \
   DELAY(2000) \
   DONE
  */

DONE



/* Build sequences
*
*/
#include "myTrackA.h"
#include "myTrackB.h"

/* Build Routes
*
*/
AUTOMATION(10,"HST B to Station Auto")
    RESERVE(UGS_BK1_Stn_App)
    RESERVE(UGS_BK2_HEAD_1_AA_Ex)
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
    AT(-1004)
    
    PRINT("DID IT WORK!")
    AT(USG_SNS_STN)
    FWD(0)
    RANDOMDELAY(10000,15000)
    RESERVE(UGS_BK4_Stn_Exit)
    FWD(50)
    DELAY(1000)
    FREE(UGS_BK1_Stn_App)
    FREE(UGS_BK2_HEAD_1_AA_Ex)
DONE

ENDEXRAIL    // marks the end of the EXRAIL program. 
    
   
