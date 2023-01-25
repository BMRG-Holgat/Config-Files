/* myBlocks
*
* Kept now on github https://github.com/BMRG-Holgat/Config-Files.git
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
ALIAS(UGS_STN_App,1)  //Station approach from fiddle yard
ALIAS(UGS_STN_Hold,2) //wait in station
ALIAS(UGS_BK2_HEAD_1_AA_Ex,3)  //Header line
ALIAS(UGS_BK3_STN_1_AB_App,4)  //Exit from station
ALIAS(UGS_BK3_2_AC_App,5) //Approach points on board 3
ALIAS(UGS_BK4_3__8_Hold,6) // Wait here for board 4 to be clear
ALIAS(UGS_BK5_9_Hold,7) // Wait here for board 9 to be clear
ALIAS(USG_BK12_Hold,12) //Wait here for access to board 1


//Up Mixed Fast
ALIAS(UMF_BK1_1_STN_App) //Station approach from fiddleyard
ALIAS(UMF_BK2_1_STN_Ex) //Exit from station
ALIAS(UMF_BK3_2_BA_App) //Approach to ponts on board 2
ALIAS(UMF_BK4_BB__BD_3_Hold) //Wait here if double slip or BC is against us 
ALIAS(UMF_BK5_4__6_Hold) 
ALIAS(UMF_BK8_7_App) // Wait here if double slip is against us
ALIAS(UMF_BK9_8_App) //Wait here for board 9 to clear
ALIAS(UMF_BK10_9_Hold) //Wait here for fiddleyard entrance to clear

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
ALIAS(FYB_BK1_T1_F)
ALIAS(FYB_BK2_T1_M)
ALIAS(FYB_BK1_T2_F)
ALIAS(FYB_BK2_T2_M)
ALIAS(FYB_BK1_T3_F)
ALIAS(FYB_BK2_T3_M)
ALIAS(FYB_BK1_T4_F)
ALIAS(FYB_BK2_T4_M)
ALIAS(FYB_BK1_T5_F)
ALIAS(FYB_BK2_T5_M)

//Fiddle yard C
ALIAS(FYC_BK1_T1_F)
ALIAS(FYC_BK2_T1_M)
ALIAS(FYC_BK1_T2_F)
ALIAS(FYC_BK2_T2_M)
ALIAS(FYC_BK1_T3_F)
ALIAS(FYC_BK2_T3_M)
ALIAS(FYC_BK1_T4_F)
ALIAS(FYC_BK2_T4_M)
ALIAS(FYC_BK1_T5_F)
ALIAS(FYC_BK2_T5_M)

//Fiddle yard D
ALIAS(FYD_BK1_T1_F)
ALIAS(FYD_BK2_T1_M)
ALIAS(FYD_BK1_T2_F)
ALIAS(FYD_BK2_T2_M)
ALIAS(FYD_BK1_T3_F)
ALIAS(FYD_BK2_T3_M)
ALIAS(FYD_BK1_T4_F)
ALIAS(FYD_BK2_T4_M)
ALIAS(FYD_BK1_T5_F)
ALIAS(FYD_BK2_T5_M)

//Fiddle yard E
ALIAS(FYE_BK1_T1_F)
ALIAS(FYE_BK2_T1_M)
ALIAS(FYE_BK1_T2_F)
ALIAS(FYE_BK2_T2_M)
ALIAS(FYE_BK1_T3_F)
ALIAS(FYE_BK2_T3_M)
ALIAS(FYE_BK1_T4_F)
ALIAS(FYE_BK2_T4_M)
ALIAS(FYE_BK1_T5_F)
ALIAS(FYE_BK2_T5_M)
//Fiddle yard F access to E
