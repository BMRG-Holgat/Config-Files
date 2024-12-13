/* Definitions
*
* Kept now on github https://github.com/BMRG-Holgat/Config-Files.git
*
* Definitions for operations
*
* V 0.0.1
* ledReset
* signalTest
* turnoutTest
* turnoutReset
* signalLedTest(id)
* turnTest(id)
* defaultPosition(id)
* turnReset(id)
*
* V 0.1.0
* endSession
*
*/

//Startup led sequence
#define ledReset \
   RED(SIG_A1) \
   RED(SIG_B1) \
   RED(SIG_D1) \
   RED(SIG_A2) \
   RED(SIG_B2) \
   RED(SIG_C2) \
   RED(SIG_D2) \
   RED(SIG_E2) \
   RED(SIG_F2) \
   RED(SIG_A3) \
   RED(SIG_B3) \
   RED(SIG_C3) \
   RED(SIG_D3) \
   RED(SIG_E3) \
   RED(SIG_F3)

//Test sequence of LED signals
 #define signalTest \
   signalLedTest(SIG_A1) \
   signalLedTest(SIG_B1) \
   signalLedTest(SIG_D1) \
   signalLedTest(SIG_A2) \
   signalLedTest(SIG_B2) \
   signalLedTest(SIG_D2) \
   signalLedTest(SIG_C2) \
   signalLedTest(SIG_E2) \
   signalLedTest(SIG_F2) \
   signalLedTest(SIG_H1) \
   signalLedTest(SIG_A3) \
   signalLedTest(SIG_B3) \
   signalLedTest(SIG_D3) \
   signalLedTest(SIG_C3) \
   signalLedTest(SIG_E3) \
   signalLedTest(SIG_F3) \
   ledReset \
   myLCDOutput(signals)
  
//Test turnout sequence
 #define turnoutTest \
  turnTest(UGS_T1_E__UFM_T1_A) \
  turnTest(UFM_T1_A__UGS_T1_E) \
  turnTest(DMF_T1_A__UMF_T1_E) \
  turnTest(UMF_T1_E__DMF_T1_A) \
  turnTest(DFM_T1_A__DFM_T2_E) \
  turnTest(UGS_T2_H) \
  turnTest(UGS_T3_E__UFM_T2_A) \
  turnTest(UFM_T2_A__UGS_T3_E) \
  turnTest(DMF_T2_E__UMF_T2_A) \
  turnTest(UMF_T2_A__DMF_T2_E) \
  turnTest(DFM_T2_E__DFM_T1_A) \
  turnTest(DFM_T3_A__DGS_T1_E) \
  turnTest(DGS_T1_E__DFM_T3_A) \
  turnTest(UGS_T4_A__UMF_T3_E) \
  turnTest(UFM_T3_E__UGS_T4_A) \
  turnTest(UFM_T4_A__DMF_T3_E) \
  turnTest(UFM_T5_A__UMF_T3_E) \
  turnTest(DMF_T3_E__UFM_T4_A) \
  turnTest(DMF_T4_E__DFM_T4_A) \
  turnTest(UMF_T3_E__UFM_T5_A) \
  turnTest(DFM_T4_A__DMF_T4_E) \
  turnTest(DGS_T2_A__HS_T1_E) \
  turnTest(HS_T1_E__DGS_T2_A) \
  turnTest(HS_T2_E__HS_T1_A) \
  turnTest(HS_T3_E__HS_T2_A) \
  turnTest(UGS_T5_E__UFM_T6_A) \
  turnTest(UFM_T6_A__UGS_T5_E) \
  turnTest(UFM_T7_E__UMF_T4_A) \
  turnTest(UMF_T4_A__UFM_T7_E) \
  turnTest(HS_T4_A__HS_T5_E) \
  turnTest(HS_T5_A__HS_T6_E) \
  turnTest(HS_T6_A__DGS_T3_E) \
  turnTest(DGS_T3_A__HS_T6_A) \
  turnTest(DFM_T5_E__DGS_T4_A) \
  turnTest(DGS_T4_A__DFM_T5_E) \
  turnTest(UGS_T6_E__UFM_T8_A) \
  turnTest(UFM_T8_A__UGS_T6_E) \
  turnTest(DMF_T5_A__DFM_T4_E) \
  turnTest(DFM_T6_E__DMF_T5_A) \
  turnTest(DGS_T5_A__DFM_T7_E) \
  turnTest(UFM_T9_E__UFM_T10_A) \
  turnTest(UFM_T10_E__UFM_T11_A) \
  turnTest(UFM_T11_E__UFM_T12_A) \
  turnTest(UFM_T12) \
  turnTest(DFM_T7_E__DGS_T5_A) \
  turnTest(DFM_T8_E__DFM_T7_A) \
  turnTest(DFM_T9_E__DFM_T8_A) \
  turnTest(DFM_T10_E__DFM_T9_A) \
  turnTest(DFM_T11_E__DFM_T10_A) \
  turnTest(UFM_T13_E__UFM_T14_A) \
  turnTest(UFM_T14_E__UFM_T15_A) \
  turnTest(UFM_T15_E__UFM_T16_A) \
  turnTest(UFM_T16_E) \
  turnTest(DMF_T6_A__DMF_T7_E) \
  turnTest(DMF_T7_A__DMF_T8_E) \
  turnTest(DMF_T8_A__DMF_T9_E) \
  turnTest(DMF_T9) \
  turnTest(UMF_T5_E__UMF_T6_A) \
  turnTest(UMF_T6_E__UMF_T7_A) \
  turnTest(UMF_T7_E__UMF_T8_A) \
  turnTest(UFM_T8) \
  turnTest(DFM_T12) \
  turnTest(DFM_T13_E__DFM_T12_A) \
  turnTest(DFM_T14_E__DFM_T13_A) \
  turnTest(DFM_T15_E__DFM_T14_A) \
  turnTest(UGS_T7_A__UFM_T17_E) \
  turnTest(UFM_T17_E__UGS_T7_A) \
  turnTest(DFM_T16_A__DGS_T6_E) \
  turnTest(DGS_T6_E__DFM_T16_A) \
  turnTest(DMF_T10) \
  turnTest(DMF_T11_E__DMT_T10_A) \
  turnTest(DMF_T12_E__DMT_T11_A) \
  turnTest(DMF_T13_E__DMF_T12_A) \
  turnTest(UMF_T9) \
  turnTest(UMF_T10_A__UMF_T9_E) \
  turnTest(UMF_T11_A__UMF_T10_E) \
  turnTest(UFM_T12_A__UFM_T11_E) \
  turnoutReset \
  myLCDOutput(turnouts)

  //Turnout reset sequence
#define turnoutReset \
  turnReset(UGS_T1_E__UFM_T1_A) \
  turnReset(UGS_T2_H) \
  turnReset(UFM_T1_A__UGS_T1_E) \
  turnReset(DMF_T1_A__UMF_T1_E) \
  turnReset(UMF_T1_E__DMF_T1_A) \
  turnReset(DFM_T1_A__DFM_T2_E) \
  turnReset(UGS_T3_E__UFM_T2_A) \
  turnReset(UFM_T2_A__UGS_T3_E) \
  turnReset(DMF_T2_E__UMF_T2_A) \
  turnReset(UMF_T2_A__DMF_T2_E) \
  turnReset(DFM_T2_E__DFM_T1_A) \
  turnReset(DFM_T3_A__DGS_T1_E) \
  turnReset(DGS_T1_E__DFM_T3_A) \
  turnReset(DMF_T10) \
  turnReset(DMF_T11_E__DMT_T10_A) \
  turnReset(DMF_T12_E__DMT_T11_A) \
  turnReset(DMF_T13_E__DMF_T12_A) \
  turnReset(UMF_T9) \
  turnReset(UMF_T10_A__UMF_T9_E) \
  turnReset(UMF_T11_A__UMF_T10_E) \
  turnReset(UFM_T12_A__UFM_T11_E) \
  turnReset(UGS_T4_A__UMF_T3_E) \
  turnReset(UFM_T3_E__UGS_T4_A) \
  turnReset(UFM_T4_A__DMF_T3_E) \
  turnReset(UFM_T5_A__UMF_T3_E) \
  turnReset(DMF_T3_E__UFM_T4_A) \
  turnReset(DMF_T4_E__DFM_T4_A) \
  turnReset(UMF_T3_E__UFM_T5_A) \
  turnReset(DFM_T4_A__DMF_T4_E) \
  turnReset(DGS_T2_A__HS_T1_E) \
  turnReset(UGS_T7_A__UFM_T17_E) \
  turnReset(UFM_T17_E__UGS_T7_A) \
  turnReset(DFM_T16_A__DGS_T6_E) \
  turnReset(DGS_T6_E__DFM_T16_A) \
  turnReset(HS_T1_E__DGS_T2_A) \
  turnReset(HS_T2_E__HS_T1_A) \
  turnReset(HS_T3_E__HS_T2_A) \
  turnReset(UFM_T13_E__UFM_T14_A) \
  turnReset(UFM_T14_E__UFM_T15_A) \
  turnReset(UFM_T15_E__UFM_T16_A) \
  turnReset(UFM_T16_E) \
  turnReset(DMF_T6_A__DMF_T7_E) \
  turnReset(DMF_T7_A__DMF_T8_E) \
  turnReset(DMF_T8_A__DMF_T9_E) \
  turnReset(DMF_T9) \
  turnReset(UMF_T5_E__UMF_T6_A) \
  turnReset(UMF_T6_E__UMF_T7_A) \
  turnReset(UMF_T7_E__UMF_T8_A) \
  turnReset(UFM_T8) \
  turnReset(DFM_T12) \
  turnReset(DFM_T13_E__DFM_T12_A) \
  turnReset(DFM_T14_E__DFM_T13_A) \
  turnReset(DFM_T15_E__DFM_T14_A) \
  turnReset(UGS_T5_E__UFM_T6_A) \
  turnReset(UFM_T6_A__UGS_T5_E) \
  turnReset(UFM_T7_E__UMF_T4_A) \
  turnReset(UMF_T4_A__UFM_T7_E) \
  turnReset(DGS_T3_A__HS_T6_A) \
  turnReset(UFM_T9_E__UFM_T10_A) \
  turnReset(UFM_T10_E__UFM_T11_A) \
  turnReset(UFM_T11_E__UFM_T12_A) \
  turnReset(UFM_T12) \
  turnReset(DFM_T7_E__DGS_T5_A) \
  turnReset(DFM_T8_E__DFM_T7_A) \
  turnReset(DFM_T9_E__DFM_T8_A) \
  turnReset(DFM_T10_E__DFM_T9_A) \
  turnReset(DFM_T11_E__DFM_T10_A) \
  turnReset(HS_T4_A__HS_T5_E) \
  turnReset(HS_T5_A__HS_T6_E) \
  turnReset(HS_T6_A__DGS_T3_E) \
  turnReset(DFM_T5_E__DGS_T4_A) \
  turnReset(DGS_T4_A__DFM_T5_E) \
  turnReset(UGS_T6_E__UFM_T8_A) \
  turnReset(UFM_T8_A__UGS_T6_E) \
  turnReset(DMF_T5_A__DFM_T4_E) \
  turnReset(DFM_T6_E__DMF_T5_A) \
  turnReset(DGS_T5_A__DFM_T7_E) 
  

//End Session settings
#define endSession \
  ledReset \
  THROW(UGS_T1_E__UFM_T1_A)\
  THROW(UGS_T2_H)\
  CLOSE(UGS_T3_E__UFM_T2_A)\
  THROW(UGS_T4_A__UMF_T3_E)\
  CLOSE(UGS_T5_E__UFM_T6_A)\
  CLOSE(UGS_T6_E__UFM_T8_A)\
  CLOSE(UGS_T7_A__UFM_T17_E)\
  THROW(UFM_T1_A__UGS_T1_E)\
  THROW(UFM_T2_A__UGS_T3_E)\
  THROW(UFM_T3_E__UGS_T4_A)\
  CLOSE(UFM_T4_A__DMF_T3_E)\
  THROW(UFM_T5_A__UMF_T3_E)\
  THROW(UFM_T8_A__UGS_T6_E)\
  CLOSE(UFM_T9_E__UFM_T10_A)\
  THROW(UFM_T10_E__UFM_T11_A)\
  THROW(UFM_T11_E__UFM_T12_A)\
  THROW(UFM_T12)\
  THROW(UFM_T13_E__UFM_T14_A)\
  THROW(UFM_T14_E__UFM_T15_A)\
  THROW(UFM_T15_E__UFM_T16_A)\
  CLOSE(UFM_T16_E)\
  THROW(UFM_T17_E__UGS_T7_A)\
  THROW(DMF_T1_A__UMF_T1_E)\
  CLOSE(DMF_T2_E__UMF_T2_A)\
  CLOSE(DMF_T3_E__UFM_T4_A)\
  CLOSE(DMF_T4_E__DFM_T4_A)\
  CLOSE(DMF_T5_A__DFM_T4_E)\
  THROW(DMF_T6_A__DMF_T7_E)\
  CLOSE(DMF_T7_A__DMF_T8_E)\
  CLOSE(DMF_T8_A__DMF_T9_E)\
  CLOSE(DMF_T9)\
  THROW(DMF_T10)\
  CLOSE(DMF_T11_E__DMT_T10_A)\
  THROW(DMF_T12_E__DMT_T11_A)\
  THROW(DMF_T13_E__DMF_T12_A)\
  CLOSE(UMF_T1_E__DMF_T1_A)\
  THROW(UMF_T2_A__DMF_T2_E)\
  CLOSE(UMF_T3_E__UFM_T5_A)\
  THROW(UMF_T4_A__UFM_T7_E)\
  CLOSE(UMF_T5_E__UMF_T6_A)\
  THROW(UMF_T6_E__UMF_T7_A)\
  THROW(UMF_T7_E__UMF_T8_A)\
  THROW(UFM_T8)\
  CLOSE(UMF_T9)\
  CLOSE(UMF_T10_A__UMF_T9_E)\
  CLOSE(UMF_T11_A__UMF_T10_E)\
  THROW(UFM_T12_A__UFM_T11_E)\
  CLOSE(DFM_T1_A__DFM_T2_E)\
  CLOSE(DFM_T2_E__DFM_T1_A)\
  CLOSE(DFM_T3_A__DGS_T1_E)\
  THROW(DFM_T4_A__DMF_T4_E)\
  CLOSE(DFM_T5_E__DGS_T4_A)\
  THROW(DFM_T6_E__DMF_T5_A)\
  CLOSE(DFM_T7_E__DGS_T5_A)\
  CLOSE(DFM_T8_E__DFM_T7_A)\
  THROW(DFM_T9_E__DFM_T8_A)\
  THROW(DFM_T10_E__DFM_T9_A)\
  THROW(DFM_T11_E__DFM_T10_A)\
  CLOSE(DFM_T12)\
  CLOSE(DFM_T13_E__DFM_T12_A)\
  CLOSE(DFM_T14_E__DFM_T13_A)\
  THROW(DFM_T15_E__DFM_T14_A)\
  THROW(DFM_T16_A__DGS_T6_E)\
  THROW(DGS_T1_E__DFM_T3_A)\
  CLOSE(DGS_T2_A__HS_T1_E)\
  CLOSE(DGS_T3_A__HS_T6_A)\
  THROW(DGS_T4_A__DFM_T5_E)\
  CLOSE(DGS_T5_A__DFM_T7_E)\
  CLOSE(DGS_T6_E__DFM_T16_A)\
  CLOSE(HS_T1_E__DGS_T2_A)\
  CLOSE(HS_T2_E__HS_T1_A)\
  CLOSE(HS_T3_E__HS_T2_A)\
  THROW(HS_T4_A__HS_T5_E)\
  CLOSE(HS_T5_A__HS_T6_E)\
  CLOSE(HS_T6_A__DGS_T3_E)
  

//Test signals indicators macro
#define signalLedTest(id) \
  SCREEN(2,0,"Testing Signal: ") \
  DELAY(1000)\
  BROADCAST("<* " #id " signal *>") \
  PRINT("Testing signal " #id) \
  SCREEN(2,1,#id) \
  PRINT(#id " Red") \
  SCREEN(2,2,"RED") \
  RED(id) \
  DELAY(1000)\
  PRINT(#id " Amber") \
  SCREEN(2,2,"       YELLOW") \
  AMBER(id) \
  DELAY(1000) \
  PRINT(#id " Green") \
  SCREEN(2,2,"               GREEN") \
  GREEN(id) \
  DELAY(1000)
  
//Test all turnouts and double slips
 #define turnTest(id) \
  SCREEN(4,0,"") \
  SCREEN(4,1,"") \
  PRINT("Testing turnout " #id) \
  SCREEN(2,0,"Testing Turnout:") \
  SCREEN(3,0,#id) \
  IFCLOSED(id) \
    SCREEN(3,1,"THROW") \
    THROW(id) \
    DELAY(2000) \
    SCREEN(3,1,"CLOSE") \
    CLOSE(id) \
  ELSE \
    SCREEN(3,1,"CLOSE") \
    CLOSE(id) \
    DELAY(2000) \
    SCREEN(3,1,"THROW") \
    THROW(id) \
  ENDIF \
  DELAY(2000)

  #define turnReset(id) \
    SCREEN(2,0,"Turnout Reset") \
    SCREEN(2,1,"") \
    SCREEN(2,2,"") \
    PRINT("Closing: " #id) \
    SCREEN(2,1,"Closing: ") \
    SCREEN(2,2,#id)\
    CLOSE(id) \
    DELAY(750)

  #define defaultPosition(turnout) \
    PRINT("Setting Default: " #turnout) \
      IFCLOSED(turnout) \
        THROW(turnout) \
      ENDIF 
    


#define forwardStop(speed,sns) \
  FWD(speed) \
  AT(sns) \
  STOP 

//Standard signal changer
#define blockSequence(signal,sensor1,sensor2,sensor3) \
    AT(sensor1) \
    RED(signal) \
    AT(sensor2) \
    AMBER(signal) \
    AT(sensor3) \
    GREEN(signal) 
  
#define blockSequenceTrackChange(signal,signal2,turnoutPair,sensor1,sensor2) \
  IFTHROWN(turnoutPair) \
      AFTER(sensor1) \
      RED(signal) \
    ENDIF \
    AT(sensor2) \
    CLOSE(turnoutPair) \
    GREEN(signal) \
  ENDIF

//not yet sure if this is required
#define signalSetTest(signal,slow,fast,seq)\
  IFGREEN(signal) \
    FWD(fast) \
    RETURN \
  ENDIF \
  IFAMBER(signal) \
    FWD(slow) \
    RETURN \
  ENDIF \
  IFRED(signal) \
    STOP \
    FOLLOW(seq) \
  ENDIF

//LCD information
#define myLCDOutput(item)\
  SCREEN(2,1,"") \
  SCREEN(2,1,"") \
  SCREEN(2,1,"") \
  SCREEN(2,0, "Resetting " #item)\
  SCREEN(2,1, "To default state")\
  SCREEN(2,2, "Test Completed")



  /* 

//Fiddle Yard Ladder
#define throwFiddleYardLadder(t1) \
    IFCLOSED(t1) \
      THROW(t1) \
    ENDIF

#define closeFiddleYardLadder(t1) \
    IFTHROWN(t1) \
      CLOSE(t1) \
      ENDIF
*/
// Not needed since myTunroutPairs.


/*
#define ladder(id,entryThrows,exitThrows) \
   IFRESERVE(ladder_block1_##id)
    closeFiddleYardLadder(entryThrows)
    FWD(10)
     AT(ladder_sensor1__##id)  // middle sensor 
     FREE(ladder_entry)        // free ladder entry
     RESERVE(ladder_block2_##id)
     FWD(10)
     AT(ladder_sensor2_##id)  // far end sensor
     ESTOP
     FREE(ladder_block1_##id) // free the first half track  
     UNSET(ladder_latch_##id)
     AT(ladder_latch_##id)   // USER requests exit this track
     RESERVE(ladder_exit)
     closeFiddleYardLadder(exitThrows)
     FWD(30)
     AT(train_out_of_ladder_sensor)
     FREE(ladder_block2_##id)
     FREE(ladder_exit)
     RETURN
     ENDIF


  //Used in the following way
  SEQUENCE(ladder_entry_seq)
   RESERVE(ladder_entry)
   SEQEUNCE(ladder_entry_loop)
      LADDER(1,9011,9210) 
      LADDER(2.....)
      PRINT("ladder full") DELAY(5000)
      FOLLOW(ladder_entry_loop)


  AUTOMATION(99,"AUTOPARK")
    SPEED(30) 
    AT(ladder_entry_sensor)
  CALL(ladder_entry_seq) 
  //
  //AT(ladder_entry_sensor)
  //CALL(ladder_entry_seq)   // will return when train exits ladder after user request
*/


