/* Definitions
*
* Kept now on github https://github.com/BMRG-Holgat/Config-Files.git
*
* Definitions for operations
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
   signalLedTest(SIG_C2) \
   signalLedTest(SIG_D2) \
   signalLedTest(SIG_E2) \
   signalLedTest(SIG_F2) \
   signalLedTest(SIG_A3) \
   signalLedTest(SIG_B3) \
   signalLedTest(SIG_C3) \
   signalLedTest(SIG_D3) \
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
  turnTest(UGS_T1_H) \
  turnTest(UGS_T2_E__DFM_T1_A) \
  turnTest(UGS_T3_A__UFM_T3_E) \
  turnTest(UGS_T4_E__UFM_T5_A) \
  turnTest(UGS_T5_E__FYUG_T7_A) \
  turnTest(UGS_T6_A__FYUG_T10_E) \
  turnTest(UFM_T1_A__UGS_T2_E) \
  turnTest(UFM_T2_E__DMF_T2_A) \
  turnTest(DMF_T2_E__UGS_T1_A) \
  turnTest(DMF_T3_A__DMF_T1_E) \
  turnTest(UFM_T5_E__UMF_T3_A) \
  turnTest(UFM_T5_E__UMF_T3A_A) \
  turnTest(UFM_T6_A__UGS_T5_E) \
  turnTest(UMF_T7_E__UMF_T8_A) \
  turnTest(UFM_T8_E__UMF_T9_A) \
  turnTest(UMF_T9_E__UMF_T10_A) \
  turnTest(UMF_T10) \
  turnTest(UMF_T11_E__UMF_T12_A) \
  turnTest(UMF_T12_E__UMF_T13_A) \
  turnTest(UMF_T13_E__UMF_T14_A) \
  turnTest(UMF_T14_E) \
  turnTest(UMF_T15_E__UGS_T6_A) \
  turnTest(DMF_T1_E__UMF_T1_A) \
  turnTest(DMF_T2_A__DMF_T1_E) \
  turnTest(DMF_T3_E__DFM_T1_A) \
  turnTest(DMF_T4_E__DMF_T5_A) \
  turnTest(DMF_T5_E__DMF_T6_A) \
  turnTest(DMF_T6_E__DMF_T7_A) \
  turnTest(DMF_T7) \
  turnTest(DMF_T8_E__DMT_T9_A) \
  turnTest(DMF_T9_E__DMT_T10_A) \
  turnTest(DMF_T10_E__DMT_T11_A) \
  turnTest(DMF_T11_E) \
  turnTest(UMF_T1_A__DMF_T1_E) \
  turnTest(UMF_T2_E__UFM_T1_A) \
  turnTest(UFM_T3_E__UMF_T2_A) \
  turnTest(UFM_T4_E__UMF_T5_A) \
  turnTest(UFM_T5_E__UMF_T6_A) \
  turnTest(UFM_T6_E__UGS_T7_A) \
  turnTest(UFM_T7) \
  turnTest(UMF_T8_E__UMF_T9_A) \
  turnTest(UFM_T9_E__UFM_T10_A) \
  turnTest(UFM_T10_E__UFM_T11_A) \
  turnTest(DFM_T1_A__DFM_T2_E) \
  turnTest(DFM_T2_E__DFM_T1_A) \
  turnTest(DGS_T3_E__DFM) \
  turnTest(DFM_T4_A__DFM_T3_E) \
  turnTest(DFM_T5_E__DGS_T4_A) \
  turnTest(DFM_T6_E__DGS_T5_A) \
  turnTest(DFM_T7_E) \
  turnTest(DFM_T8_E__DFM_T7_A) \
  turnTest(DFM_T9_E__DFM_T8_A) \
  turnTest(DFM_T10_E__DFM_T9_A) \
  turnTest(DFM_T11) \
  turnTest(DFM_T12_E__DFM_T11) \
  turnTest(DFM_T13_E__DFM_T12_A) \
  turnTest(DFM_T14_E__DFM_T13_A) \
  turnTest(DFM_T15_A__DFM_T14_E) \
  turnTest(DFM_T16_A__DGS_T6_E) \
  turnTest(DGS_T1_A__HS_T2_E) \
  turnTest(DGS_T2_A__HS_T3_A) \
  turnTest(DGS_T3_A__DFM_T2_E) \
  turnTest(DGS_T4_A__DFM_T5_E) \
  turnTest(DGS_T5_A__DFM_T6_E) \
  turnTest(DGS_T6_E__DFM_T15_A) \
  turnTest(HS_T1_A__HS_T2_E) \
  turnTest(HS_T2_A__HS_T3_E) \
  turnTest(HS_T3) \
  turnTest(HS_T4_E__HS_T5_A) \
  turnTest(HS_T5_A__HS_T6) \
  turnTest(HS_T6) \
  turnoutReset \
  myLCDOutput(turnouts)

  //Turnout reset sequence
#define turnoutReset \
  turnReset(UGS_T1_E__UFM_T1_A) \
  turnReset(UFM_T1_A__UGS_T1_E) \
  turnReset(DMF_T1_A__UMF_T1_E) \
  turnReset(UMF_T1_E__DMF_T1_A) \
  turnReset(UGS_T1_H) \
  turnReset(UGS_T2_E__DFM_T1_A) \
  turnReset(UGS_T3_A__UFM_T3_E) \
  turnReset(UGS_T4_E__UFM_T5_A) \
  turnReset(UGS_T5_E__FYUG_T7_A) \
  turnReset(UGS_T6_A__FYUG_T10_E) \
  turnReset(UFM_T1_A__UGS_T2_E) \
  turnReset(UFM_T2_E__DMF_T2_A) \
  turnReset(DMF_T2_E__UGS_T1_A) \
  turnReset(DMF_T3_A__DMF_T1_E) \
  turnReset(UFM_T5_E__UMF_T3_A) \
  turnReset(UFM_T5_E__UMF_T3A_A) \
  turnReset(UFM_T6_A__UGS_T5_E) \
  turnReset(UMF_T7_E__UMF_T8_A) \
  turnReset(UFM_T8_E__UMF_T9_A) \
  turnReset(UMF_T9_E__UMF_T10_A) \
  turnReset(UMF_T10) \
  turnReset(UMF_T11_E__UMF_T12_A) \
  turnReset(UMF_T12_E__UMF_T13_A) \
  turnReset(UMF_T13_E__UMF_T14_A) \
  turnReset(UMF_T14_E) \
  turnReset(UMF_T15_E__UGS_T6_A) \
  turnReset(DMF_T1_E__UMF_T1_A) \
  turnReset(DMF_T2_A__DMF_T1_E) \
  turnReset(DMF_T3_E__DFM_T1_A) \
  turnReset(DMF_T4_E__DMF_T5_A) \
  turnReset(DMF_T5_E__DMF_T6_A) \
  turnReset(DMF_T6_E__DMF_T7_A) \
  turnReset(DMF_T7) \
  turnReset(DMF_T8_E__DMT_T9_A) \
  turnReset(DMF_T9_E__DMT_T10_A) \
  turnReset(DMF_T10_E__DMT_T11_A) \
  turnReset(DMF_T11_E) \
  turnReset(UMF_T1_A__DMF_T1_E) \
  turnReset(UMF_T2_E__UFM_T1_A) \
  turnReset(UFM_T3_E__UMF_T2_A) \
  turnReset(UFM_T4_E__UMF_T5_A) \
  turnReset(UFM_T5_E__UMF_T6_A) \
  turnReset(UFM_T6_E__UGS_T7_A) \
  turnReset(UFM_T7) \
  turnReset(UMF_T8_E__UMF_T9_A) \
  turnReset(UFM_T9_E__UFM_T10_A) \
  turnReset(UFM_T10_E__UFM_T11_A) \
  turnReset(UFM_T11) \
  turnReset(DFM_T1_A__DFM_T2_E) \
  turnReset(DFM_T2_E__DFM_T1_A) \
  turnReset(DGS_T3_E__DFM) \
  turnReset(DFM_T4_A__DFM_T3_E) \
  turnReset(DFM_T5_E__DGS_T4_A) \
  turnReset(DFM_T6_E__DGS_T5_A) \
  turnReset(DFM_T7_E) \
  turnReset(DFM_T8_E__DFM_T7_A) \
  turnReset(DFM_T9_E__DFM_T8_A) \
  turnReset(DFM_T10_E__DFM_T9_A) \
  turnReset(DFM_T11) \
  turnReset(DFM_T12_E__DFM_T11) \
  turnReset(DFM_T13_E__DFM_T12_A) \
  turnReset(DFM_T14_E__DFM_T13_A) \
  turnReset(DFM_T15_A__DFM_T14_E) \
  turnReset(DFM_T16_A__DGS_T6_E) \
  turnReset(DGS_T1_A__HS_T2_E) \
  turnReset(DGS_T2_A__HS_T3_A) \
  turnReset(DGS_T3_A__DFM_T2_E) \
  turnReset(DGS_T4_A__DFM_T5_E) \
  turnReset(DGS_T5_A__DFM_T6_E) \
  turnReset(DGS_T6_E__DFM_T15_A) \
  turnReset(HS_T1_A__HS_T2_E) \
  turnReset(HS_T2_A__HS_T3_E) \
  turnReset(HS_T3) \
  turnReset(HS_T4_E__HS_T5_A) \
  turnReset(HS_T5_A__HS_T6) \
  turnReset(HS_T6) \
  defaultPosition(UGS_T1_H) \
  defaultPosition(DGS_T4_A__DFM_T5_E)

   
//Test signals indicators macro
#define signalLedTest(id) \
  DELAY(1000)\
  BROADCAST("<* " #id " signal *>") \
  PRINT("Testing signal " #id) \
  PRINT(#id " Red") \
  RED(id) \
  DELAY(1000)\
  PRINT(#id " Amber") \
  AMBER(id) \
  DELAY(1000) \
  PRINT(#id " Green") \
  GREEN(id)
  
//Test all turnouts and double slips
 #define turnTest(id) \
  PRINT("Testing turnout " #id) \
  IFCLOSED(id) \
    THROW(id) \
    DELAY(3000) \
    CLOSE(id) \
  ELSE \
    CLOSE(id) \
    DELAY(3000) \
    THROW(id) \
  ENDIF \
  DELAY(3000)

  #define turnReset(id) \
    PRINT("Closing: " #id) \
    CLOSE(id) \
    DELAY(500)

  #define defaultPosition(id) \
    PRINT("Setting Default: " #id) \
      IFCLOSED(id) \
        THROW(id) \
        DELAY(100) \
      ENDIF

//Change paired turnouts
#define trackChange(id,ad)\
  IFTHROWN(id) \
        CLOSE(id) \
        CLOSE(ad) \
  ELSE \
        THROW(id) \
        THROW(ad) \
  ENDIF

//Fiddle Yard Ladder
#define throwFiddleYardLadder(t1) \
    IFCLOSED(t1) \
      THROW(t1) \
    ENDIF

#define closeFiddleYardLadder(t1) \
    IFTHROWN(t1) \
      CLOSE(t1) \
      ENDIF

#define forwardStop(speed,sns) \
  FWD(speed) \
  DELAY(5000)
  STOP 

//LCD information
#define myLCDOutput(item)\
  LCD(0, "Restting " #item)\
    LCD(1, "To default state")\
    LCD(2,"Test Completed")\
    LCD(3,"%z")
