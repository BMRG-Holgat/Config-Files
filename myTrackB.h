/*
* myTrackB.h
* Add in the routes for trackD only
*
* V 0.1.0
*           290 - 294 Free yard tracks
*           295 - 299 Reserve yard tracks
*           202 Around We Go
*           289 Auto Park
*
*/
//Release Block when loco is removed from track
SEQUENCE(250) //Disable routes
   ROUTE_DISABLED(202)
   ROUTE_DISABLED(1202)
   ROUTE_DISABLED(1211)
   ROUTE_DISABLED(1222)
   ROUTE_DISABLED(1223)
   ROUTE_DISABLED(1224)
   ROUTE_DISABLED(1225)

   RETURN
DONE

SEQUENCE(251) //Enable routes
    ROUTE_ACTIVE(202)
    ROUTE_ACTIVE(211)
    ROUTE_ACTIVE(1202)
    ROUTE_ACTIVE(1211)
    ROUTE_ACTIVE(1222)
    ROUTE_ACTIVE(1223)
    ROUTE_ACTIVE(1224)
    ROUTE_ACTIVE(1225)
RETURN
DONE


ROUTE(290,"B: Clear Track 1")
    ROUTE_HIDDEN(290)
    ROUTE_ACTIVE(295)
    FREE(B_B7)
    CLEAR_STASH(TB1) 
DONE
ROUTE(291,"B: Clear Track 2")
    ROUTE_HIDDEN(291)
    ROUTE_ACTIVE(296)
    FREE(B_B8)
    CLEAR_STASH(TB2)
DONE
ROUTE(292,"B: Clear Track 3 ")
    ROUTE_HIDDEN(292)
    ROUTE_ACTIVE(297)
    FREE(B_B9)
    CLEAR_STASH(TB3)
DONE
ROUTE(293,"B: Clear Track 4")
    ROUTE_HIDDEN(293)
    ROUTE_ACTIVE(298)
    FREE(B_B10)
    CLEAR_STASH(TB4)
DONE
ROUTE(294,"B: Clear Track 5")
    ROUTE_HIDDEN(294)
    ROUTE_ACTIVE(299)
    FREE(B_B11)
    CLEAR_STASH(TB5)
DONE

//Set reserves for locos in yard to prevent other locos entering
ROUTE(295,"B: Load Track 1") //Auto park the train in the yard
    ROUTE_HIDDEN(295)
    ROUTE_ACTIVE(290)
    RESERVE(B_B7)
DONE
ROUTE(296,"B: Load Track 2") //Auto park the train in the yard
    ROUTE_HIDDEN(296)
    ROUTE_ACTIVE(291)
    RESERVE(B_B8)
DONE
ROUTE(297,"B: Load Track 3") //Auto park the train in the yard
    ROUTE_HIDDEN(297)
    ROUTE_ACTIVE(292)
    RESERVE(B_B9)
DONE
ROUTE(298,"B: Load Track 4") //Auto park the train in the yard
    ROUTE_HIDDEN(298)
    ROUTE_ACTIVE(293)
    RESERVE(B_B10)
DONE
ROUTE(299,"B: Load Track 5") //Auto park the train in the yard
    ROUTE_HIDDEN(299)
    ROUTE_ACTIVE(294)
    RESERVE(B_B11)
DONE 

//Manually activate the auto park sequence
AUTOMATION(289,"B: Manual Auto Park")  
    ROUTE_HIDDEN(289) 
    CALL(201)
    ROUTE_ACTIVE(289)   
DONE

//parkRelease Release the block the train has come from dependant on turnout position
SEQUENCE(200) //Release Parked Block dependant on turnout thrown
    IFCLOSED(9115) //Track FD1
        FREE(B_B7)
        SCREEN(2,1,"")
        CLEAR_STASH(TB1)
        RETURN
    ENDIF
    IFTHROWN(9116) //Track FD2
        FREE(B_B8)
        SCREEN(2,2,"")
        CLEAR_STASH(TB2)
        RETURN
    ENDIF
    IFTHROWN(9117) //Track FD3
        FREE(B_B9)
        SCREEN(2,3,"")
        CLEAR_STASH(TB3)
        RETURN
    ENDIF
    IFCLOSED(9118) //Track FD4
        FREE(B_B10)
        SCREEN(2,4,"")
        CLEAR_STASH(TB4)
        RETURN
    ENDIF
    IFTHROWN(9118) //Track FD5
        FREE(B_B11)
        SCREEN(2,5,"")
        CLEAR_STASH(TB5)
        RETURN
    ENDIF
DONE

//Auto Park Sequence
SEQUENCE(201)
IFNOT(CD_F2_B1) 
    RESERVE(B_B7)
    SCREEN(2,1,"Block B7 Reserved")
    CLOSE(9110)
    FWD(20) 
    AT(CD_F2_B1) ESTOP
    FREE(B_B6)
    SCREEN(4,6,"")
    STASH(TB1)
    RETURN
ENDIF 
IFNOT(CD_F2_B2) 
    RESERVE(B_B8)
    SCREEN(2,2,"Block B8 Reserved")
    THROW(9111)
    FWD(20) 
    AT(CD_F2_B2) ESTOP
    FREE(B_B6)
    SCREEN(4,6,"")
    STASH(TB2)
    RETURN
ENDIF 
IFNOT(CD_F2_B3) 
    RESERVE(B_B9)
    SCREEN(2,3,"Block B9 Reserved")
    THROW(9112)
    FWD(20) 
    AT(CD_F2_B3) ESTOP
    FREE(B_B6)
    SCREEN(4,6,"")
    STASH(TB3)
    RETURN
ENDIF 
IFNOT(CD_F3_B4) 
    RESERVE(B_B10)
    SCREEN(2,4,"Block B10 Reserved")
    THROW(9113)
    FWD(20) 
    AT(CD_F3_B4) ESTOP
    FREE(B_B6)
    SCREEN(4,6,"")
    STASH(TB4)
    RETURN
ENDIF 
IFNOT(CD_F3_B5) 
    RESERVE(B_B11)
    SCREEN(2,5,"Block B11 Reserved")
    CLOSE(9113)
    FWD(20) 
    AT(CD_F3_B5) ESTOP
    FREE(B_B6)
    SCREEN(4,6,"")
    STASH(TB5)
    RETURN
ENDIF 
DONE


// Start of main AUTOMATIONS for track B
AUTOMATION(202, "B: Around We Go Manual") //Leave yard and proceed to block 1
   CALL(250) 
    RESERVE(B_B1) //Reserve Block 1
    SCREEN(4,1,"Block B1 Reserved")
    SPEED(20)
    IFTHROWN(9001)
        CLOSE(9001) //close turnouts A - B
    ENDIF
    IFTHROWN(9026)
        CLOSE(9026) //close turnouts B - A
    ENDIF   
    AT(CD_S1_B) //At Block 1
FOLLOW(203)

SEQUENCE(203) //Progress to Block2    
    CALL(200)
    CALL(251)
    AT(CD_S1_B1)
FOLLOW(204)

SEQUENCE(204) //Progress to Block2
    IFRESERVE(B_B2) //Reserve Next block
        SCREEN(4,2,"Block B2 Reserved")
        IFTHROWN(9004)
            CLOSE(9004) //close turnouts A->B
        ENDIF
        IFTHROWN(9007)
            CLOSE(9007) //close turnouts B->A   
        ENDIF
        IFTHROWN(9008)
            CLOSE(9008) //close turnouts D->B
        ENDIF
        IFTHROWN(9009)
            CLOSE(9009) //close turnouts D->A
        ENDIF
        IFTHROWN(9010)
            CLOSE(9010) //close turnouts D->B
        ENDIF
    ELSE
        RED(SIG_B1) //Set signal to red if block 2 not free
        STOP
        FOLLOW(204)
    ENDIF
    AT(CD_S2_B)
FOLLOW(205)

SEQUENCE(205) //Progress to Block3
    RED(SIG_B1)
    IFRESERVE(B_B3) //Reserve Next block
        SCREEN(4,3,"Block B3 Reserved")
        AT(CD_S4_B)
        FREE(B_B1) //Free previous block
        SCREEN(4,1,"")
    ELSE
        AT(CD_S3_B)
        STOP
        FOLLOW(205) 
    ENDIF 
    AT(CD_S5_B)
FOLLOW(206)

SEQUENCE(206)
    IFTHROWN(9004)
        CLOSE(9004) // close turnouts A->B
    ENDIF
    RED(SIG_B2)
    FREE(B_B2) //Free previous block
    SCREEN(4,2,"")
    AT(CD_S6_B) 
FOLLOW(207)

SEQUENCE(207) //Progress to Block4
    IFRESERVE(B_B4) //Reserve Next block
    SCREEN(4,4,"Block B4 Reserved")
        IFTHROWN(9020)
            CLOSE(9020) // prevent route A-B
            CLOSE(9021) // prevent route A-D
        ENDIF
    ELSE
    PRINT("WAITING FOR RESERVE")
        AT(CD_S7_B)
        STOP
        FOLLOW(207)
    ENDIF
    AT(CD_S8_B)  
FOLLOW(208)

SEQUENCE(208) //Progress to Block5
    AMBER(SIG_B1)
    RED(SIG_B3)
    IFRESERVE(B_B5) //Reserve Next block
    SCREEN(4,5,"Block B5 Reserved")
        FREE(B_B3)
        SCREEN(4,3,"")
        IFTHROWN(9023)
            CLOSE(9023) // prevent route A->B   
        ENDIF
    ELSE
        AT(CD_S9_B)
        STOP
        FOLLOW(208)
    ENDIF
    AT(CD_F9_B)
FOLLOW(209)

SEQUENCE(209) //Progress to Block6
    RED(SIG_B4)
    AMBER(SIG_B2)
    GREEN(SIG_B1)
    AT(CD_F8_B)
FOLLOW(210)

SEQUENCE(210) //Progress to Block6
    GREEN(SIG_B2)
    AMBER(SIG_B3)
    AT(CD_F7_B)
FOLLOW(211)

SEQUENCE(211) //Progress to Block6
    RESERVE(B_B6) //Reserve Next block
    SCREEN(4,6,"Block B6 Reserved")
    FREE(B_B4) //Free previous block
    SCREEN(4,4,"")
    GREEN(SIG_B3)
    AMBER(SIG_B4)
    AT(CD_F6_B)
FOLLOW(212)

SEQUENCE(212)
    GREEN(SIG_B4)
    FREE(B_B5)
    SCREEN(4,5,"")
    CALL(201)
    FOFF(0)
DONE


AUTOMATION(213,"B: Station Stop Manual") //Station Stop
    CALL(250)
    IFRESERVE(A_B1)
        RESERVE(B_B1) //Reserve Station block  
        IFTHROWN(9001)
            CLOSE(9001) //close turnouts A - B
        ENDIF
        IFCLOSED(9026)
            THROW(9026) //close turnouts B - A
        ENDIF 
        IFCLOSED(UGS_T2_H) //Close Header
            THROW(UGS_T2_H) 
        ENDIF  
        SPEED(20)
    ELSE
        FOLLOW(213)
    ENDIF
    AT(CD_S1_A)
FOLLOW(214)

SEQUENCE(214) //Stop at station
    CALL(251)
    STOP
    CALL(200)
    DELAYRANDOM(10000,15000)
FOLLOW(215)

SEQUENCE(215) //Release turnout block and set turnouts for return to A
    IFRESERVE(B_B2)
        IFRESERVE(A_B2) //reserve Block 2
            IFCLOSED(9004)
                THROW(9004) //close turnouts A->B
            ENDIF
        ENDIF
        IFTHROWN(9007)
            CLOSE(9007) //close turnouts B->A
        ENDIF
        GREEN(SIG_B1)
    ELSE
        RED(SIG_A1) //Set signal to red if block 2 not free
        STOP
        FOLLOW(215)
    ENDIF
    AT(CD_S2_A)
FOLLOW(216)

SEQUENCE(216)
    RED(SIG_A1)
    FREE(A_B1)
    IFTHROWN(9026)
        CLOSE(9026) //close turnouts B->A 
    ENDIF
FOLLOW(205)
    
// Start of main FULL AUTOMATIONS for track B
AUTOMATION(1202, "B: Around We Go Auto") //Leave yard and proceed to block 1
   CALL(250) 
   IFNOT(autoRunning_B)
    IFRESERVE(B_B1) //Reserve Block 1
        PRINT("Waiting for BLOCK B1")
    ELSE
        FOLLOW(1202)
    ENDIF
   ENDIF
    SCREEN(4,1,"Block B1 Reserved")
    SPEED(20)
    IFTHROWN(9001)
        CLOSE(9001) //close turnouts A - B
    ENDIF
    IFTHROWN(9026)
        CLOSE(9026) //close turnouts B - A
    ENDIF   
    AT(CD_S1_B) //At Block 1
FOLLOW(1203)

SEQUENCE(1203) //Progress to Block2    
    CALL(200)
    CALL(251)
    AT(CD_S1_B1)
FOLLOW(1204)

SEQUENCE(1204) //Progress to Block2
    IFRESERVE(B_B2) //Reserve Next block
        SCREEN(4,2,"Block B2 Reserved")
        IFTHROWN(9004)
            CLOSE(9004) //close turnouts A->B
        ENDIF
        IFTHROWN(9007)
            CLOSE(9007) //close turnouts B->A   
        ENDIF
        IFTHROWN(9008)
            CLOSE(9008) //close turnouts D->B
        ENDIF
        IFTHROWN(9009)
            CLOSE(9009) //close turnouts D->A
        ENDIF
        IFTHROWN(9010)
            CLOSE(9010) //close turnouts D->B
        ENDIF
        SPEED(35)
    ELSE
        PRINT("Not Reserved")
        WAIT_WHILE_RED(SIG_B1)
        FOLLOW(1204)
    ENDIF
    IFAMBER(SIG_B1)
        SPEED(20)
    ELSE 
        SPEED(30)
    ENDIF
    AT(CD_S2_B)
    RED(SIG_B1)
FOLLOW(1205)

SEQUENCE(1205) //Progress to Block 3
    IFRESERVE(B_B3) //Reserve Next block
    SCREEN(4,3,"Block B3 Reserved")
    SPEED(30)
    ELSE
       IF(CD_S3_B)
        WAIT_WHILE_RED(SIG_B2)
       ENDIF
      FOLLOW(1205)
    ENDIF
    IFAMBER(SIG_B2)
        SPEED(25)
    ELSE
        SPEED(35)
    ENDIF
    AT(CD_S4_B)
    FREE(B_B1)
    AT(CD_S5_B)  
FOLLOW(1206)

SEQUENCE(1206)
    IFTHROWN(9004)
        CLOSE(9004) // close turnouts A->B
    ENDIF
    RED(SIG_B2)   
    SCREEN(4,2,"") 
    IFRED(SIG_B3)
        SPEED(15)
    ENDIF
    IFAMBER(SIG_B3)
        SPEED(25)
    ENDIF
    AT(CD_S6_B)
FOLLOW(1207)

SEQUENCE(1207) //Progress to Block4
    IFRESERVE(B_B4) //Reserve Next block
    SCREEN(4,4,"Block B4 Reserved")
        IFTHROWN(9020)
            CLOSE(9020) // prevent route A-B
            CLOSE(9021) // prevent route A-D
        ENDIF
    ELSE
        AT(CD_S7_B)
        WAIT_WHILE_RED(SIG_B3)       
        FOLLOW(1207)
    ENDIF
    IFAMBER(SIG_B3)
        SPEED(25)
    ELSE
        SPEED(35)
    ENDIF
    AT(CD_S8_B)  
FOLLOW(1208)

SEQUENCE(1208) //Progress to Block5
    AMBER(SIG_B1)
    FREE(B_B2) //Free previous block
    RED(SIG_B3)
    IFRESERVE(B_B5) //Reserve Next block
    SCREEN(4,5,"Block B5 Reserved")        
        SCREEN(4,3,"")
        IFTHROWN(9023)
            CLOSE(9023) // prevent route A->B   
        ENDIF
    ELSE
        AT(CD_S9_B)
        WAIT_WHILE_RED(SIG_B4)
        FOLLOW(1208)
    ENDIF
    IFAMBER(SIG_B4)
        SPEED(25)
    ELSE
        SPEED(30)
    ENDIF
    AT(CD_F9_B)
FOLLOW(1209)

SEQUENCE(1209) //Progress to Block6
    RED(SIG_B4)
    AMBER(SIG_B2)
    FREE(B_B3)
    GREEN(SIG_B1)
    AT(CD_F8_B)
FOLLOW(1210)

SEQUENCE(1210) //Progress to Block6
    GREEN(SIG_B2)
    AMBER(SIG_B3)
    AT(CD_F7_B)
FOLLOW(1211)

SEQUENCE(1211) //Progress to Block6
    RESERVE(B_B6) //Reserve Next block
    SCREEN(4,6,"Block B6 Reserved")
    FREE(B_B4) //Free previous block
    SCREEN(4,4,"")
    GREEN(SIG_B3)
    AMBER(SIG_B4)
    SPEED(30)
    AT(CD_F6_B)
FOLLOW(1212)

SEQUENCE(1212)
    GREEN(SIG_B4)
    FREE(B_B5)
    SCREEN(4,5,"")
    CALL(201)
    FOFF(0)
    IF(autoRunning_B)
        RETURN
    ENDIF
DONE


AUTOMATION(1213,"B: Station Stop Auto") //Station Stop
    CALL(250)
    IFRESERVE(A_B1)
        RESERVE(B_B1) //Reserve Station block  
        IFTHROWN(9001)
            CLOSE(9001) //close turnouts A - B
        ENDIF
        IFCLOSED(9026)
            THROW(9026) //close turnouts B - A
        ENDIF 
        IFCLOSED(UGS_T2_H) //Close Header
            THROW(UGS_T2_H) 
        ENDIF  
        SPEED(20)
    ELSE
        FOLLOW(1213)
    ENDIF
    RED(SIG_STN_1)
    RED(SIG_STN_2)
    AT(CD_S1_AA)
FOLLOW(1214)

SEQUENCE(1214) //Stop at station
    CALL(251)
    STOP
    CALL(200)
    FREE(B_B1)
    DELAYRANDOM(10000,15000)
    GREEN(SIG_STN_1)
    GREEN(SIG_STN_2)
    SPEED(30)
FOLLOW(1215)

SEQUENCE(1215) //Release turnout block and set turnouts for return to A
    IFRESERVE(B_B2)
        IFRESERVE(A_B2) //reserve Block 2
            IFCLOSED(9004)
                THROW(9004) //close turnouts A->B
            ENDIF
        ENDIF
        IFTHROWN(9007)
            CLOSE(9007) //close turnouts B->A
        ENDIF
        GREEN(SIG_B1)
    ELSE
        RED(SIG_A1) //Set signal to red if block 2 not free
        STOP
        FOLLOW(1215)
    ENDIF
    AT(CD_S2_A)
FOLLOW(1216)

SEQUENCE(1216)
    SPEED(40)
    RED(SIG_A1)
    FREE(A_B1)
    FREE(A_B2)
    IFTHROWN(9026)
        CLOSE(9026) //close turnouts B->A 
    ENDIF
FOLLOW(1205)


AUTOMATION(1221,"B: Run Track 1") //Auto Track 1
   CALL(250)
   IFSTASH(TB1)
    IFRESERVE(B_B1)
      CLOSE(9115) //Close exit to allow roundy
      PICKUP_STASH(TB1)
      FON(0)
    ELSE
      FOLLOW(1221)
   ENDIF
   FOLLOW(1202)
   IF(autoRunning_B)
    RETURN
   ENDIF
   ENDIF
DONE

AUTOMATION(1222,"B: Run Track 2") //Auto Track 2
   CALL(250)
   IFSTASH(TB2)
   IFRESERVE(B_B1)
     THROW(9116) 
     PICKUP_STASH(TB2)
     FON(0)
    ELSE
     FOLLOW(1222)
   ENDIF
   FOLLOW(1202)
   IF(autoRunning_B)
    RETURN
   ENDIF
   ENDIF
DONE

AUTOMATION(1223,"B: Run Track 3") //Auto Track 3
   CALL(250)
   IFSTASH(TB3)
   IFRESERVE(B_B1)
     THROW(9117) 
     PICKUP_STASH(TB3)
     FON(0)
    ELSE 
     FOLLOW(1223)
    ENDIF
    FOLLOW(1202)
    IF(autoRunning_B)
        RETURN
    ENDIF
    ENDIF
DONE

AUTOMATION(1224,"B: Run Track 4") //Auto Track 4
   CALL(250)
   IFSTASH(TB4)
    IFRESERVE(B_B1)
     CLOSE(9118) 
     PICKUP_STASH(TB4)
     FON(0)
    ELSE 
     FOLLOW(1224) 
    ENDIF
     FOLLOW(1202)
     IF(autoRunning_B)
        RETURN
     ENDIF
    ENDIF
DONE

AUTOMATION(1225,"B: Run Track 5") //Auto Track 5
   CALL(250)
   IFSTASH(TB5) 
   IFRESERVE(B_B1)
     THROW(9118) 
     PICKUP_STASH(TB5)
     FON(0)
   ELSE
    FOLLOW(1225)
   ENDIF
    FOLLOW(1202)
    IF(autoRunning_B)
        RETURN
     ENDIF
    ENDIF
DONE
/*
//Suggested improvements for track selection
//select different route depending on reserve status of blocks
IFRESERVEB_B2) FOLLOW(1213) ENDIF
DELAY(.....) 
IFRESERVEB_B2) FOLLOW(1213) ENDIF
/// had two goes .. no banana
DONE
SEQUENCE1213)
.... carry on with block reserved


HAL(Bitmap,777,1)

RESET(777)
BITMAP_OR(777,5)  // start counter at 5

SEQUENCE(xxxx)
  IFRESERVE(yyyy) FOLLOW(zzzz) DONE
  DELAY(1000)
  BITMAP_DEC(777)
  IF(777) FOLLOW(xxxx)
  // no banana
  DONE
SEQUENCE(zzzz)
  // Have banana 
*/


ROUTE(1200,"B: Breaktime Select") //Select whether to run auto or not
    IF(autoSelected_B)
        UNLATCH(autoSelected_B)
        ROUTE_HIDDEN(1231)
    ELSE
        LATCH(autoSelected_B)
        ROUTE_ACTIVE(1231)
    ENDIF
DONE

/*AUTOMATION(1230,"SELECT A TRACK")
IF(autoSelected)
    IFRANDOM(50)
        IFRANDOM(50)
            IFSTASH(TB1)
                FOLLOW(1221) //Track 1
            ELSE
                FOLLOW(1230) //Try again
            ENDIF
        ELSE
            FOLLOW(1222) //Track 2
        ENDIF
    ELSE
        IFRANDOM(50)
            FOLLOW(1223) //Track 3
        ELSE
            FOLLOW(1224) //Track 4   
        ENDIF
    ELSE
        FOLLOW(1225) //Go round the loop
    ENDIF
ENDIF
FOLLOW(1230) */
/*
AUTOMATION(1231,"B: Break time Run")
IF(autoSelected_B)
    LATCH(autoRunning_B) //Full auto Track B
    ROUTE_DISABLED(1231)
    ROUTE_CAPTION(1231,"RUNNING")
    IFRANDOM(20) IFSTASH(TB1) CALL(1221) ENDIF ENDIF
    IFRANDOM(25) IFSTASH(TB2) CALL(1222) ENDIF ENDIF
    IFRANDOM(33) IFSTASH(TB3) CALL(1223) ENDIF ENDIF
    IFRANDOM(50) IFSTASH(TB4) CALL(1224) ENDIF ENDIF
    IFRANDOM(100) IFSTASH(TB5) CALL(1225) ENDIF ENDIF
ELSE
    ROUTE_ACTIVE(1231)
    UNLATCH(autoRunning_B) //Stop Full auto Track B
    DONE
ENDIF
FOLLOW(1231)*/

AUTOMATION(1231,"B: Break time Run")
IF(autoSelected_B)
    LATCH(autoRunning_B) //Full auto Track B
    ROUTE_DISABLED(1231)
    ROUTE_CAPTION(1231,"RUNNING")
    RANDOM_CALL(1221,1222,1223,1224,1225)
    PRINT("B: NO TRAIN")
    FOLLOW(1231)
ELSE
    ROUTE_ACTIVE(1231)
    UNLATCH(autoRunning_B) //Stop Full auto Track B
    DONE
ENDIF
DONE


