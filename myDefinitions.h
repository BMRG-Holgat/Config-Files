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
    CLOSE(UGS_T6_A__FYUG_T10_E)

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
  // signalLedTest(SIG_S3) \
   //ledReset \
   myLCDOutput(signals)
   
//Test turnout sequence
 #define turnoutTest \
  turnTest(UGS_T1_H) \
  turnTest(UGS_T2_E__DFM_T1_A) \
  turnTest(UGS_T3_A__UFM_T3_E) \
  turnTest(UGS_T4_E__UFM_T5_A) \
  turnTest(UGS_T5_E__FYUG_T7_A) \
  turnTest(UGS_T6_A__FYUG_T10_E) \
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
