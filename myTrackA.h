/*
* myTrackA.h
*
* Sequences for Track A
* Up Goods Slow
*
* V. 0.0.1
*  Setup basics
*  All Sequences start from Board 1 and end on Board 2
*
* V 0.1.0
* First single loop created
* All basic sequences created
*
*/
//initsl starting positions
AUTOMATION(40,"A: Start 2")
RESERVE(A_B7)
SCREEN(3,7,"A_B7 Reserved")
FWD(15)
ROUTE_HIDDEN(40)
FOLLOW(51)

AUTOMATION(41,"A: Start 3")
RESERVE(A_B6)
SCREEN(3,6,"A_B6 Reserved")
FWD(15)
ROUTE_HIDDEN(41)
FOLLOW(50)

//Track A from yard
//Leave yard and approach station
AUTOMATION(43,"A: A STN Stop") 
RESERVE(A_B1) //Reserve Station block 
SCREEN(3,1,"A_B1      Reserved")
IFTHROWN(9026) //close B-A turnouts
  CLOSE(9026)
ENDIF 
IFTHROWN(9001) //Close A-B turnouts
  CLOSE(9001)
ENDIF
IFCLOSED(UGS_T2_H) //Close Header
    THROW(UGS_T2_H)
  ENDIF
FWD(40)       //Move forward
  AT(322)
  FREE(A_B7)  //Release previous ladder
  SCREEN(3,7,"A_B7 Free") 
  RED(SIG_A1)
    FON(2)
    AFTER(322)
    FOFF(2)    
FOLLOW(44)

SEQUENCE(44)
//Stop at station
  AT(308)
  STOP 
  DELAYRANDOM(10000,15000)
  RESERVE(A_B2) //reserve Block 2
  SCREEN(3,2,"A_B2 Reserved")
  GREEN(SIG_A1)
  FON(4)
  DELAY(500)
  FOFF(4)
  DELAY(300)
  FON(3)
  DELAY(300)
  FOFF(3)
  FWD(40)
FOLLOW(45)

SEQUENCE(45)
//Move to gantry 1
 AT(396)
 RESERVE(A_B3)
 SCREEN(3,3,"A_B3 Reserved")
 SPEED(50) // Increase Speed
 //Now station is clear free it
 FREE(A_B1)
 SCREEN(3,1,"A_B1 Free")
FOLLOW(46)

SEQUENCE(46)
//block A_B3
AT(628) //Board 6
SPEED(60) // Increase speed
FOLLOW(47)

SEQUENCE(47)
//Board 8
AT(772)
RESERVE(A_B4)
SCREEN(3,4,"A_B4 Reserved")
FREE(A_B2)
SCREEN(3,2,"A_B2 Free")
FOLLOW(48)

SEQUENCE(48)
AT(828)
RESERVE(A_B5)
SCREEN(3,5,"A_B5 Reserved")
FREE(A_B3)
SCREEN(3,3,"A_B3 Free")
SPEED(20)
FOLLOW(49)

SEQUENCE(49) //Block A_B5
AT(721)
RESERVE(A_B6)
SCREEN(3,6,"A_B6 Reserved")
FREE(A_B4)
SCREEN(3,4,"A_B4 Free")
//SPEED(20)
FOLLOW(50)

SEQUENCE(50) //Block A_B6
AT(576)
RESERVE(A_B7)
SCREEN(3,7,"A_B7 Reserved")
FREE(A_B5)
SCREEN(3,5,"A_B5 Free")
//SPEED(30)
FOLLOW(51)

SEQUENCE(51) // Block A_B7
 AT(482)
 STOP
 FOFF(0)
 FREE(A_B6)
SCREEN(3,6,"A_B6 Free")
DONE 


//Track A through station to track B

AUTOMATION(60,"A: A STN Bypass")
RESERVE(B_B1)
SCREEN(3,1,"     B_B1")
  IFTHROWN(9026)
    CLOSE(9026)
  ENDIF
  IFCLOSED(9001)
    THROW(9001)
  ENDIF
  FWD(40)
FOLLOW(61)

SEQUENCE(61)
  AT(396) //TRACK B1 SENSOR
  FREE(A_B7)  //Release previous ladder
  SCREEN(3,7,"A_B7 Free") 
  RESERVE(A_B2)
  SCREEN(3,2,"A_B2 Reserved")
  RESERVE(A_B3)
  SCREEN(3,3,"     A_B3")
  RESERVE(B_B2)
  SCREEN(3,2,"     B_B2")
  IFCLOSED(9007)
    THROW(9007)
  ENDIF
FOLLOW(62)

SEQUENCE(62)
  AT(123) //SENSOR B6
  SPEED(60)
  IFTHROWN(9007)
    CLOSE(9007)
  ENDIF
  IFRED(SIG_B1)
    FREE(B_B2)
    SCREEN(3,2,"B_B2 Free")
    GREEN(SIG_B1)
  ENDIF 
FOLLOW(47)



