/*myTurnouts.h
* new replacement file incase something breaks
*Define turnouts here
*
*SERVO_TURNOUT(id,ping,throw,close,speed,desc)
*
*Final positions 
*/
//Turnout definitions need to set throw and close positions
//Up Goods Slow - Track A
SERVO_TURNOUT(UGS_T1_E__UFM_T1_A,120,300,405,Fast,HIDDEN) //AA 500 Board 1
SERVO_TURNOUT(UGS_T2_H,126,250,350,Fast,"Header") //AB 501 Board 1
SERVO_TURNOUT(UGS_T3_E__UFM_T2_A,152,350,210,Fast,HIDDEN) //AC 502 Board 2
SERVO_TURNOUT(UGS_T4_A__UMF_T3_E,174,215,330,Fast,HIDDEN) //AD 503 Board 3
SERVO_TURNOUT(UGS_T5_E__UFM_T6_A,231,230,100,Fast,HIDDEN) //AE 504 Board 8
SERVO_TURNOUT(UGS_T6_E__UFM_T8_A,248,380,250,Fast,HIDDEN) //AF 505 Board 9
SERVO_TURNOUT(UGS_T7_A__UFM_T17_E,170,350,250,Fast,HIDDEN) //AG 506 Board 3

//Up Fast Mixed - Track B
SERVO_TURNOUT(UFM_T1_A__UGS_T1_E,123,260,380,Fast,HIDDEN) //BA 509 Board 1
SERVO_TURNOUT(UFM_T2_A__UGS_T3_E,155,210,340,Fast,HIDDEN) //BB 510 Board 2
SERVO_TURNOUT(UFM_T3_E__UGS_T4_A,177,200,320,Fast,HIDDEN) //BC 511 Board 3
SERVO_TURNOUT(UFM_T4_A__DMF_T3_E,178,360,240,Fast,HIDDEN) //BD 512 Board 3
SERVO_TURNOUT(UFM_T5_A__UMF_T3_E,169,250,355,Fast,HIDDEN) //BE 513 Board 3
SERVO_TURNOUT(UFM_T6_A__UGS_T5_E,228,150,250,Fast,HIDDEN) //BF 514 Board 8
SERVO_TURNOUT(UFM_T7_E__UMF_T4_A,229,200,345,Fast,HIDDEN) //BG 515 Board 8
SERVO_TURNOUT(UFM_T8_A__UGS_T6_E,249,210,320,Fast,HIDDEN) //BH 516 Board 9
SERVO_TURNOUT(UFM_T9_E__UFM_T10_A,247,330,220,Fast,HIDDEN) //BI 517 Board 8
SERVO_TURNOUT(UFM_T10_E__UFM_T11_A,233,190,330,Fast,HIDDEN) //BJ 518 Board 8
SERVO_TURNOUT(UFM_T11_E__UFM_T12_A,246,205,290,Fast,HIDDEN) //BK 519 Board 8
SERVO_TURNOUT(UFM_T12,243,200,305,Fast,HIDDEN) //BL 520 Board 8
SERVO_TURNOUT(UFM_T13_E__UFM_T14_A,212,250,370,Fast,HIDDEN) //BM 521 Board 5    CHECK
SERVO_TURNOUT(UFM_T14_E__UFM_T15_A,207,280,380,Fast,HIDDEN) //BN 522 Board 5
SERVO_TURNOUT(UFM_T15_E__UFM_T16_A,204,350,450,Fast,HIDDEN) //BO 523 Board 5
SERVO_TURNOUT(UFM_T16_E,201,365,258,Fast,HIDDEN) //BP 524 Board 5
SERVO_TURNOUT(UFM_T17_E__UGS_T7_A,179,250,350,Fast,HIDDEN) //BR 573 Board 3

//Down Main Fast - Track C
SERVO_TURNOUT(DMF_T1_A__UMF_T1_E,122,230,350,Fast,HIDDEN) //CA 528 Board 1
SERVO_TURNOUT(DMF_T2_E__UMF_T2_A,160,360,250,Fast,HIDDEN) //CB 529 Board 2
SERVO_TURNOUT(DMF_T3_E__UFM_T4_A,173,375,180,Fast,HIDDEN) //CC 530 Board 3
SERVO_TURNOUT(DMF_T4_E__DFM_T4_A,176,370,245,Fast,HIDDEN) //CD 531 Board 3
SERVO_TURNOUT(DMF_T5_A__DFM_T4_E,252,340,200,Fast,HIDDEN) //CE 532 Board 9
SERVO_TURNOUT(DMF_T6_A__DMF_T7_E,215,250,370,Fast,HIDDEN) //CF 533 Board 5
SERVO_TURNOUT(DMF_T7_A__DMF_T8_E,213,400,300,Fast,HIDDEN) //CG 534 Board 5
SERVO_TURNOUT(DMF_T8_A__DMF_T9_E,210,315,220,Fast,HIDDEN) //CH 535 Board 5
SERVO_TURNOUT(DMF_T9,205,450,350,Fast,HIDDEN) //CI 536 Board 5              CHECK
SERVO_TURNOUT(DMF_T10,151,220,320,Fast,HIDDEN) //CJ 537 Board 2
SERVO_TURNOUT(DMF_T11_E__DMT_T10_A,147,370,250,Fast,HIDDEN) //CK 538 Board 2
SERVO_TURNOUT(DMF_T12_E__DMT_T11_A,150,260,370,Fast,HIDDEN) //CL 539 Board 2
SERVO_TURNOUT(DMF_T13_E__DMF_T12_A,144,220,300,Fast,HIDDEN) //CM 540 Board 2

//Up Main Fast - Track D
SERVO_TURNOUT(UMF_T1_E__DMF_T1_A,121,400,300,Fast,HIDDEN) //DA 543 Board 1
SERVO_TURNOUT(UMF_T2_A__DMF_T2_E,153,190,350,Fast,HIDDEN) //DB 544 Board 2
SERVO_TURNOUT(UMF_T3_E__UFM_T5_A,175,350,220,Fast,HIDDEN) //DC 545 Board 3
SERVO_TURNOUT(UMF_T4_A__UFM_T7_E,217,250,370,Fast,HIDDEN) //DD 546 Board 8
SERVO_TURNOUT(UMF_T5_E__UMF_T6_A,214,350,250,Fast,HIDDEN) //DE 547 Board 5
SERVO_TURNOUT(UMF_T6_E__UMF_T7_A,211,200,340,Fast,HIDDEN) //DF 548 Board 5
SERVO_TURNOUT(UMF_T7_E__UMF_T8_A,208,250,350,Fast,HIDDEN) //DG 549 Board 5
SERVO_TURNOUT(UFM_T8,202,250,350,Fast,HIDDEN) //DH 550 Board 5
SERVO_TURNOUT(UMF_T9,136,390,250,Fast,HIDDEN) //DI 551 Board 2
SERVO_TURNOUT(UMF_T10_A__UMF_T9_E,149,350,235,Fast,HIDDEN) //DJ 552 Board 2
SERVO_TURNOUT(UMF_T11_A__UMF_T10_E,146,350,240,Fast,HIDDEN) //DK 553 Board 2
SERVO_TURNOUT(UFM_T12_A__UFM_T11_E,145,250,350,Fast,HIDDEN) //DL 554 Board 2

// Down Mixed Fast - Track E
SERVO_TURNOUT(DFM_T1_A__DFM_T2_E,124,340,220,Fast,HIDDEN) //EA 557 Board 1
SERVO_TURNOUT(DFM_T2_E__DFM_T1_A,154,400,280,Fast,HIDDEN) //EB 558 Board 2
SERVO_TURNOUT(DFM_T3_A__DGS_T1_E,161,390,250,Fast,HIDDEN) //EC 559 Board 2
SERVO_TURNOUT(DFM_T4_A__DMF_T4_E,172,260,400,Fast,HIDDEN) //ED 560 Board 3
SERVO_TURNOUT(DFM_T5_E__DGS_T4_A,254,400,200,Fast,HIDDEN) //EE 561 Board 9
SERVO_TURNOUT(DFM_T6_E__DMF_T5_A,250,300,400,Fast,HIDDEN) //EF 562 Board 9
SERVO_TURNOUT(DFM_T7_E__DGS_T5_A,234,330,230,Fast,HIDDEN) //EG 563 Board 8
SERVO_TURNOUT(DFM_T8_E__DFM_T7_A,235,350,220,Fast,HIDDEN) //EH 564 Board 8
SERVO_TURNOUT(DFM_T9_E__DFM_T8_A,232,260,360,Fast,HIDDEN) //EI 565 Board 8
SERVO_TURNOUT(DFM_T10_E__DFM_T9_A,245,300,450,Fast,HIDDEN) //EJ 566 Board 8
SERVO_TURNOUT(DFM_T11_E__DFM_T10_A,244,250,420,Fast,HIDDEN) //EK 567 Board 8
SERVO_TURNOUT(DFM_T12,209,250,350,Fast,HIDDEN) //EL 568 Board 5
SERVO_TURNOUT(DFM_T13_E__DFM_T12_A,206,350,250,Fast,HIDDEN) //EM 569 Board 5
SERVO_TURNOUT(DFM_T14_E__DFM_T13_A,203,350,250,Fast,HIDDEN) //EN  570 Board 5
SERVO_TURNOUT(DFM_T15_E__DFM_T14_A,200,180,310,Fast,HIDDEN) //EO 571 Board 5
SERVO_TURNOUT(DFM_T16_A__DGS_T6_E,181,350,480,Fast,HIDDEN) //EP 572 Board 3

// Down Goods Slow
SERVO_TURNOUT(DGS_T1_E__DFM_T3_A,162,140,250,Fast,HIDDEN) //FA 576 Board 2
SERVO_TURNOUT(DGS_T2_A__HS_T1_E,168,380,250,Fast,HIDDEN) //FB 577 Board 3
SERVO_TURNOUT(DGS_T3_A__HS_T6_A,218,470,350,Fast,"Holgate: Holgate access") //FC 578 Board 8
SERVO_TURNOUT(DGS_T4_A__DFM_T5_E,253,100,230,Fast,HIDDEN) //FD 579 Board 9
SERVO_TURNOUT(DGS_T5_A__DFM_T7_E,251,280,375,Fast,HIDDEN) //FE 580 Board 9
SERVO_TURNOUT(DGS_T6_E__DFM_T16_A,180,330,200,Fast,HIDDEN) //FF 581 Board 3

// Holgate Sidings
SERVO_TURNOUT(HS_T1_E__DGS_T2_A,171,380,250,Fast,HIDDEN) //HA 584 Board 3
SERVO_TURNOUT(HS_T2_E__HS_T1_A,185,350,250,Fast,HIDDEN) //HB 585 Board 4`
SERVO_TURNOUT(HS_T3_E__HS_T2_A,184,500,400,Fast,HIDDEN) //HC 586 Board 4
SERVO_TURNOUT(HS_T4_A__HS_T5_E,230,260,370,Fast,HIDDEN) //HD 587 Board 8
SERVO_TURNOUT(HS_T5_A__HS_T6_E,216,410,250,Fast,HIDDEN) //HE 588 Board 8
SERVO_TURNOUT(HS_T6_A__DGS_T3_E,219,370,290,Fast,HIDDEN) //HF 589 Board 8

