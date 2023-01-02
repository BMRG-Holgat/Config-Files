 //Test turnout sequence
 #define turnoutTest \
 //Board 1
 turnTest(UGS_T1_H) \ //AA  
 turnTest(DFM_T1_A__DFM_T2_E) \//EA 
 //Board 2 Scenic
 turnTest(UGS_T2_E__DFM_T1_A) \//AB
 turnTest(UFM_T1_A__UGS_T2_E) \ //BA
 turnTest(UMF_T1_A__DMF_T1_E) \//DA
 turnTest(UFM_T1_A__UGS_T2_E) \//BA
 turnTest(DMF_T1_E__UMF_T1_A) \//CA
 turnTest(DFM_T2_E__DFM_T1_A) \//EB
 turnTest(DGS_T3_E__DFM) \ //EC
 turnTest(DGS_T1_A__HS_T2_E)  \//FA
 //Board 3 Scenic
 turnTest(UGS_T3_A__UFM_T3_E) \//AC
 turnTest(UMF_T1_A__DMF_T1_A) \//BC Double slip part 1
 turnTest(DMF_T2_E__UGS_T1_A) \//BD Double slip pt 2
 turnTest(UFM_T4_A__UGS_T5_E) \//BE
 turnTest(DMF_T2_A__DMF_T1_E) \ //CB
 turnTest(UMF_T2_E__UFM_T1_A) \ //DB
 turnTest(DFM_T4_A__DFMT3_E) \ //ED
 turnTest(DGS_T2_A__HS_T3_A) \ //FB
 
