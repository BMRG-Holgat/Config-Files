/*
* myRoute
* for churchbells
*/
ALIAS(Bridge,348)
ALIAS(B2_Light1,348)
ALIAS(B2_Light2,349)
ALIAS(B2_Light3,351)
ALIAS(B3_Light1,431)
ALIAS(B2_Church,350)
ALIAS(House_1_Bed,432)
ALIAS(House_1_2_Bed,433)
/*
//Reset hidden routes
ROUTE(1200,"System: Reset Hidden")
ROUTE_INACTIVE(40)
ROUTE_INACTIVE(41)
DONE
*/
ROUTE(1000,"Main Bells")
   /* PLAYSOUND(10000,0,0,DF_RESET)
    DELAY(2000)
    PLAYSOUND(10000,0,0,DF_FOLDER) // Set folder to 01 player 1 */
    PLAYSOUND(10000,1,30,DF_PLAY)
DONE

ROUTE(1001,"Wedding Peel")
    PLAYSOUND(10000,0,0,DF_RESET)
    DELAY(2000)
    PLAYSOUND(10000,0,02,DF_FOLDER) // Set folder to 01 player 1
    PLAYSOUND(10000,002,30,DF_PLAY)
DONE

ROUTE(1002,"Bells. THe bells")
    SET(10002)
DONE

ROUTE(1003,"More bells")
    SET(10003)
DONE

ROUTE(1004,"Lights: Street")
IFNOT(Latch_light)
    SET(Bridge)
    SET(B2_Light1)
    SET(B2_Light2)
    SET(B2_Light3)
    SET(B3_Light1)
    LATCH(Latch_light)
ELSE 
    RESET(Bridge)
    RESET(B2_Light1)
    RESET(B2_Light2)
    RESET(B2_Light3)
    RESET(B3_Light1)
    UNLATCH(Latch_light)
ENDIF 
DONE

ROUTE(1014,"Lights: House")
IFNOT(Latch_light_house)
    SET(432)
    SET(433)
    SET(434)
    SET(435)
    LATCH(Latch_light_house)
ELSE 
    RESET(432)
    RESET(433)
    RESET(434)
    RESET(435)
    UNLATCH(Latch_light_house)
ENDIF 
DONE

ROUTE(1005,"Lights: Church")
IFNOT(Latch_church)
    SET(B2_Church)
    LATCH(Latch_church)
ELSE 
    RESET(B2_Church)
    UNLATCH(Latch_church)
ENDIF
DONE

ROUTE(1015,"Lights: House1_Bed")
IFNOT(Latch_House_1_Bed)
    SET(House_1_Bed)
    LATCH(Latch_House_1_Bed)
ELSE 
    RESET(House_1_Bed)
    UNLATCH(Latch_House_1_Bed)
ENDIF 
DONE

ROUTE(1016,"Lights: House2_Bed")
IFNOT(Latch_House_1_2_Bed)
    SET(House_1_2_Bed)
ELSE 
    RESET(House_1_2_Bed)
ENDIF 
DONE

ROUTE(1017,"Lights: House3")
IFNOT(Latch_light_house)
    SET(440)
ELSE 
    RESET(440)
ENDIF 
DONE

ROUTE(1018,"Lights: House4")
IFNOT(Latch_light_house)
    SET(441)
ELSE 
    RESET(442)
ENDIF 
DONE

ROUTE(1019,"Lights: House5")
IFNOT(Latch_light_house)
    SET(443)
ELSE 
    RESET(443)
ENDIF 
DONE

ROUTE(1020,"Lights: House6")
IFNOT(Latch_light_house)
    SET(444)
ELSE 
    RESET(444)
ENDIF 
DONE

ROUTE(1021,"Lights: House7")
IFNOT(Latch_light_house)
    SET(445)
ELSE 
    RESET(445)
ENDIF 
DONE

ROUTE(1022,"Lights: House8")
IFNOT(Latch_light_house)
    SET(446)
ELSE 
    RESET(446)
ENDIF 
DONE

ROUTE(1023,"Lights: House8")
IFNOT(Latch_light_house)
    SET(447)
ELSE 
    RESET(447)
ENDIF 
DONE

ROUTE(1024,"Lights: House8")
IFNOT(Latch_light_house)
    SET(448)
ELSE 
    RESET(448)
ENDIF 
DONE


ROUTE(1025,"Lights: Reset")
    RESET(432)
    RESET(433)
    RESET(434)
    RESET(435)
    RESET(436)
    RESET(437)
    RESET(438)
    RESET(439)
    RESET(440)
    RESET(441)
    RESET(442)
    RESET(443)
    RESET(444)
    RESET(445)
    RESET(446)
    RESET(447)
DONE