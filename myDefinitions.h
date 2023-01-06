/* Definitions
*
* Kept now on github https://github.com/BMRG-Holgat/Config-Files.git
*
* Definitions for operations
*
*/
//Turnout reset sequence
#define turnoutReset \
    CLOSE(UGS_T1_H) \
    CLOSE(UGS_T2_E__DFM_T1_A) \
    CLOSE(UGS_T3_A__UFM_T3_E) \
    CLOSE(UGS_T4_E__UFM_T5_A) \
    CLOSE(UGS_T5_E__FYUG_T7_A) \
    CLOSE(UGS_T6_A__FYUG_T10_E) \
    CLOSE(UFM_T1_A__UGS_T2_E) \
    CLOSE(UMF_T1_A__DMF_T1_A) \
    CLOSE(DMF_T1_E__UGS_T1_A) \
    CLOSE(DMF_T3_A__DMF_T1_E) \
    CLOSE(UFM_T4_A__UGS_T5_E) \
    CLOSE(UFM_T5_E__UMF_T3_A) \
    CLOSE(UFM_T6_A__UGS_T5_E) \
    CLOSE(UMF_T7_E__UMF_T8_A) \
    CLOSE(UFM_T8_E__UMT_T9_A) \
    CLOSE(UMF_T9_E__UMF_T10_A) \
    CLOSE(UMF_T10) \
    CLOSE(UMF_T11_E__UMF_T12_A) \
    CLOSE(UMF_T12_E__UMF_T13_A) \
    CLOSE(UMF_T13_E__UMF_T14_A) \
    CLOSE(UMT_T14_E) \
    CLOSE(DMF_T1_E__UMF_T1_A) \
    CLOSE(DMF_T2_A__DMF_T1_E) \
    CLOSE(DMF_T3_E__DFM_T1_A) \
    CLOSE(DMF_T4_E__DMF_T5_A) \
    CLOSE(DMF_T5_E__DMF_T6_A) \
    CLOSE(DMF_T6_E__DMF_T7_A) \
    CLOSE(DMF_T7) \
    CLOSE(DMF_T8_E__DMF_T9_A) \
    CLOSE(DMF_T9_E__DMT_T10_A) \
    CLOSE(DMF_T10_E__DMT_T11_A) \
    CLOSE(DMF_T11_E) \
    CLOSE(UMF_T1_A__DMF_T1_E) \
    CLOSE(UMF_T2_E__UFM_T1_A) \
    CLOSE(UFM_T3_E__UMF_T2_A) \
    CLOSE(UFM_T4_E__UMF_T5_A) \
    CLOSE(UFM_T5_E__UMF_T6_A) \
    CLOSE(UFM_T6_E__UGS_T7_A) \
    CLOSE(UFM_T7) \
    CLOSE(UFM_T8_E__UMT_T9_A) \
    CLOSE(UFM_T9_E__UFM_T10_A) \
    CLOSE(UFM_T10_E__UFM_T11_A) \
    CLOSE(UFM_T11) \
    CLOSE(DFM_T1_A__DFM_T2_E) \
    CLOSE(DFM_T2_E__DFM_T1_A) \
    CLOSE(DGS_T3_E__DFM) \
    CLOSE(DFM_T4_A__DFMT3_E) \
    CLOSE(DFM_T5_E__DGS_T4_A) \
    CLOSE(DFM_T6_E__DGS_T5_A) \
    CLOSE(DFM_T7_E) \
    CLOSE(DFM_T8_E__DFM_T7_A) \
    CLOSE(DFM_T9_E__DFM_T8_A) \
    CLOSE(DFM_T10_E__DFM_T9_A) \
    CLOSE(DFM_T11) \
    CLOSE(DFM_T12_E__DFM_T11) \
    CLOSE(DFM_T13_E__DFM_T12_A) \
    CLOSE(DFM_T14_E__DFM_T13_A) \
    CLOSE(DFM_T15_A__DGS_T6_E) \
    CLOSE(DGS_T1_A__HS_T2_E) \
    CLOSE(DGS_T2_A__HS_T3_A) \
    CLOSE(DGS_T3_A__DFM_T2_E) \
    CLOSE(DGS_T4_A__DFM_T5_E) \
    CLOSE(DGS_T5_A__DFM_T6_E) \
    CLOSE(DGS_T6_E__DFM_T15_A) \
    CLOSE(HS_T1_A__HS_T2_E) \
    CLOSE(HS_T2_A__HS_T3_E) \
    CLOSE(HS_T3) \
    CLOSE(HS_T4_E__HS_T5_A) \
    CLOSE(HS_T5_A__HS_T6) \
    CLOSE(HS_T6) \


//Startup led sequence
#define ledReset \
    RED(SIG_N1) \
    RED(SIG_N2) \
    RED(SIG_N3) \
    RED(SIG_N4) \
    RED(SIG_N5) \
    RED(SIG_N6) \
    RED(SIG_S1) \
    RED(SIG_S2) \
    RED(SIG_S3) 

//Test sequence of LED signals
 #define signalTest \
   //signalLedTest(SIG_N1) \
   //signalLedTest(SIG_N2) \
   //signalLedTest(SIG_N3) \
   //signalLedTest(SIG_N4) \
   //signalLedTest(SIG_N5) \
   //signalLedTest(SIG_N6) \
   //signalLedTest(SIG_S1) \
   //signalLedTest(SIG_S2) \
   //signalLedTest(SIG_S3) \
   ledReset \
   myLCDOutput(signals)
   
//Test turnout sequence
 #define turnoutTest \
  turnTest(UGS_T1_H) \
  turnTest(UGS_T2_E__DFM_T1_A) \
  turnTest(UGS_T3_A__UFM_T3_E) \
  turnTest(UGS_T4_E__UFM_T5_A) \
  turnTest(UGS_T5_E__FYUG_T7_A) \
  turnTest(UGS_T6_A__FYUG_T10_E) \
  turnTest(UFM_T1_A__UGS_T2_E) \
  turnTest(UMF_T1_A__DMF_T1_A) \
  turnTest(DMF_T1_E__UGS_T1_A) \
  turnTest(DMF_T3_A__DMF_T1_E) \
  turnTest(UFM_T4_A__UGS_T5_E) \
  turnTest(UFM_T5_E__UMF_T3_A) \
  turnTest(UFM_T6_A__UGS_T5_E) \
  turnTest(UMF_T7_E__UMF_T8_A) \
  turnTest(UFM_T8_E__UMT_T9_A) \
  turnTest(UMF_T9_E__UMF_T10_A) \
  turnTest(UMF_T10) \
  turnTest(UMF_T11_E__UMF_T12_A) \
  turnTest(UMF_T12_E__UMF_T13_A) \
  turnTest(UMF_T13_E__UMF_T14_A) \
  turnTest(UMT_T14_E) \
  turnTest(DMF_T1_E__UMF_T1_A) \
  turnTest(DMF_T2_A__DMF_T1_E) \
  turnTest(DMF_T3_E__DFM_T1_A) \
  turnTest(DMF_T4_E__DMF_T5_A) \
  turnTest(DMF_T5_E__DMF_T6_A) \
  turnTest(DMF_T6_E__DMF_T7_A) \
  turnTest(DMF_T7) \
  turnTest(DMF_T8_E__DMF_T9_A) \
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
  turnTest(UFM_T8_E__UMT_T9_A) \
  turnTest(UFM_T9_E__UFM_T10_A) \
  turnTest(UFM_T10_E__UFM_T11_A) \
  turnTest(UFM_T11) \
  turnTest(DFM_T1_A__DFM_T2_E) \
  turnTest(DFM_T2_E__DFM_T1_A) \
  turnTest(DGS_T3_E__DFM) \
  turnTest(DFM_T4_A__DFMT3_E) \
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
  turnTest(DFM_T15_A__DGS_T6_E) \
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

//LCD information
#define myLCDOutput(item)\
  LCD(0, "Restting " #item)\
  LCD(1, "To default state")\
  LCD(2,"Test Completed")\
  LCD(3,"%z")
