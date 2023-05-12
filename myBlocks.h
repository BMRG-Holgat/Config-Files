/* myBlocks
*
* Define blocks Aliases
*
* ALIAS(block, [value])
*
* Block syntax
* (track value_sequence_[description]_turnout_board_type)
* App __ Approach
* Hold = Wait
* Ex __ Exit
*/

//Up Goods Slow
ALIAS(UGS_BK1_Stn_App,10) //Station approach from fiddle yard B1
ALIAS(UGS_BK2_HEAD_1_AA_Ex,11)  //Header line B1
ALIAS(UGS_STN_Hold,12) //Station Hold for effect B1
ALIAS(UGS_BK4_Stn_Exit,13)  //Exit from station B1
ALIAS(UGS_BK4_3__8_Hold,14)
ALIAS(UGS_BK5_9_Hold,15)
ALIAS(UGS_BK5_UFM_Access_Hold,16) // Wait here for board 4 to be clear B3
ALIAS(UGS_BK6,17) // Wait here for board 8 to be clear B4
ALIAS(UGS_BK7,18) // Wait here for board 9 to be clear B8
ALIAS(UGS_BK8_BF_App,19) //Wait for Fiddle yard clearance B9
ALIAS(USG_BK9_Hold,20) //Fiddle yard bypass holding 4
ALIAS(USG_BK10_Hold,21) //Fiddle yard bypass holding 3
ALIAS(USG_BK11_Hold,22) //Fiddle yard bypass holding 2
ALIAS(USG_BK12_Hold,23) //Fiddle yard bypass holding 1

//Up Mixed Fast
ALIAS(UMF_FY_Ex) // Leave Fiddle Yard Board 4->3
ALIAS(UMF_BK1_1_STN_App) //Station approach from fiddleyard board 2->1
ALIAS(UMF_BK2_1_STN_Ex) //Exit from station
ALIAS(UMF_BK3_2_BA_App) //Approach to points on board 2
ALIAS(UMF_BK4_BB__BD_3_Hold) //Wait here if double slip or BC is against us 
ALIAS(UMF_BK5_4__6_Hold)
ALIAS(UMF_BK8_7_App) // Wait here if single slip is against us
ALIAS(UMF_BK9_8_App) //Wait here for board 9 to clear
ALIAS(UMF_BK10_9_Hold) //Wait here for fiddleyard entrance to clear
ALIAS(FB_App,48) // FB approach track from Board 9 all trains wait here until space available
ALIAS(FB_T1_E_Hold,49) //FB Track 1 exit block
ALIAS(FB_T1_A_Hold,50) // FB Track 1 access block
ALIAS(FB_T2_E_Hold,51) // FB Track 2 exit block
ALIAS(FB_T2_A_Hold,52) // FB Track 2 access block
ALIAS(FB_T3_E_Hold,53) //FB Track 3 exit block
ALIAS(FB_T3_A_Hold,54) // FB Track 3 access block
ALIAS(FB_T4_E_Hold,55) // FB Track 4 exit block
ALIAS(FB_T4_A_Hold,56) // FB Track 4 access block
ALIAS(FB_T5_E_Hold,57) // FB Track 5 exit block
ALIAS(FB_T5_A_Hold,58) // FB Track 5 access block

//Down Main Fast
ALIAS(DMF_BK1_1_DF_App) //Wait here for D Fiddle yard to clear
ALIAS(DMF_BK2_2_STN_Hold) //Wait in Station simulation
ALIAS(DMF_BK3_7__4_CB_App) //wait before CB on board 3
ALIAS(DMF_BK4_9__8_App) //Wait before xover on board 8

//Up Main Fast
ALIAS(UFM_BK1_1_STN_App) //Station approach from fiddleyard
ALIAS(UFM_BK2_1_STN_Hold) //Hold in station
ALIAS(UFM_BK3_2__7)
ALIAS(UFM_BK3_8_DC_App) //Approach to DC turnout
ALIAS(UFM_BK5_9_FY_App)

//Down Mixed Fast

//Down Goods Slow

//Holgate Sidings

//Fiddle yard A access to B

//Fiddle yard B
ALIAS(FYB_BK1_T1_F,200)
ALIAS(FYB_BK2_T1_M,201)
ALIAS(FYB_BK1_T2_F,202)
ALIAS(FYB_BK2_T2_M,203)
ALIAS(FYB_BK1_T3_F,204)
ALIAS(FYB_BK2_T3_M,205)
ALIAS(FYB_BK1_T4_F,206)
ALIAS(FYB_BK2_T4_M,207)
ALIAS(FYB_BK1_T5_F,208)
ALIAS(FYB_BK2_T5_M,209)

//Fiddle yard C
ALIAS(FYC_BK1_T1_F,210)
ALIAS(FYC_BK2_T1_M,211)
ALIAS(FYC_BK1_T2_F,212)
ALIAS(FYC_BK2_T2_M,213)
ALIAS(FYC_BK1_T3_F,214)
ALIAS(FYC_BK2_T3_M,215)
ALIAS(FYC_BK1_T4_F,216)
ALIAS(FYC_BK2_T4_M,217)
ALIAS(FYC_BK1_T5_F,218)
ALIAS(FYC_BK2_T5_M,219)

//Fiddle yard D
ALIAS(FYD_BK1_T1_F,220)
ALIAS(FYD_BK2_T1_M,221)
ALIAS(FYD_BK1_T2_F,222)
ALIAS(FYD_BK2_T2_M,223)
ALIAS(FYD_BK1_T3_F,224)
ALIAS(FYD_BK2_T3_M,225)
ALIAS(FYD_BK1_T4_F,226)
ALIAS(FYD_BK2_T4_M,227)
ALIAS(FYD_BK1_T5_F,228)
ALIAS(FYD_BK2_T5_M,229)

//Fiddle yard E
ALIAS(FYE_BK1_T1_F,230)
ALIAS(FYE_BK2_T1_M,231)
ALIAS(FYE_BK1_T2_F,232)
ALIAS(FYE_BK2_T2_M,233)
ALIAS(FYE_BK1_T3_F,234)
ALIAS(FYE_BK2_T3_M,235)
ALIAS(FYE_BK1_T4_F,236)
ALIAS(FYE_BK2_T4_M,237)
ALIAS(FYE_BK1_T5_F,238)
ALIAS(FYE_BK2_T5_M,239)
//Fiddle yard F access to E
ALIAS(DGS_BK8_BF_App)
ALIAS(DSG_BK9_Hold,240)
ALIAS(DSG_BK10_Hold,241)
ALIAS(DSG_BK11_Hold,242)
ALIAS(DSG_BK12_Hold,243)