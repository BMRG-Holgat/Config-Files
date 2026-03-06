/*
* routes for Holgate sidings
*/
SEQUENCE(750)
    ROUTE_DISABLED(1700)
    ROUTE_DISABLED(1701)    
    ROUTE_DISABLED(1721)
    ROUTE_DISABLED(1722)
    ROUTE_DISABLED(1723)
    ROUTE_DISABLED(1724)
    RETURN
DONE    

SEQUENCE(751)
    ROUTE_ACTIVE(1700)
    ROUTE_ACTIVE(1701)
    ROUTE_ACTIVE(1721)
    ROUTE_ACTIVE(1722)
    ROUTE_ACTIVE(1723)
    ROUTE_ACTIVE(1724)
    RETURN
DONE

AUTOMATION(1700,"H: Exit to F")
    CALL(750)
    IFSTASH(THET)
        IFRESERVE(F_B3)
            PRINT("Ready to leave")
            THROW(9028)
            PICKUP_STASH(THET)
            FWD(30)
            AT(CD_S3_F1)
            RED(SIG_H1)
        ELSE
            PRINT("Waiting for block F3")
            FOLLOW(1700)
        ENDIF
    ELSE
        PRINT("No Train")
        RETURN
    ENDIF   
DONE

AUTOMATION(1701,"H: Exit to E")
    CALL(750)
    IFSTASH(THET)
        IFRESERVE(E_B3)
            IFRESERVE(F_B3)
                PRINT("Ready to leave")
                THROW(9029)
                THROW(9003)
                PICKUP_STASH(THET)
                FWD(30)
                AT(CD_S3_F1)
                RED(SIG_H1)
                CALL(1505)
            ELSE
                PRINT("Waiting for block F3")
                FREE(E_B3) //Free E3 in case it is reserved by the previous train
                DELAY(5000)
                FOLLOW(1701)
            ENDIF
        ELSE
            PRINT("Waiting for block E3")   
            FOLLOW(1701)
        ENDIF
    ELSE
        PRINT("No Train")
        RETURN
    ENDIF
DONE


//Holgate exit to track F
AUTOMATION(1721,"H:  Exit Track 1")
    CALL(750)
    IFSTASH(THA)
        THROW(9012) 
        PICKUP_STASH(THA)
        FON(0)
        IFLOCO(SoundLoco)
            FON(1)
        ENDIF
    ELSE
        PRINT("No Train")
        RETURN
    ENDIF
    FWD(20)
    AT(CD_S3_H_ext)
    STOP
    STASH(THET)
    CALL(702)
    CALL(751)
    RETURN
DONE

AUTOMATION(1722,"H:  Exit Track 2")
    CALL(750)
    IFSTASH(THB)
        THROW(9013) 
        PICKUP_STASH(THB)
        FON(0)
        IFLOCO(SoundLoco)
            FON(1)
        ENDIF
    ELSE
        PRINT("No Train")
        RETURN
    ENDIF
    FWD(20)
    AT(CD_S3_H_ext)
    STOP
    STASH(THET)
    CALL(702)
    CALL(751)
    RETURN
DONE

AUTOMATION(1723,"H:  Exit Track 3")
    CALL(750)
    IFSTASH(THC)
        THROW(9014) 
        PICKUP_STASH(THC)
        FON(0)
        IFLOCO(SoundLoco)
            FON(1)
        ENDIF
    ELSE
        PRINT("No Train")
        RETURN
    ENDIF
    FWD(20)
    AT(CD_S3_H_ext)
    STOP
    STASH(THET)
    CALL(702)
    CALL(751)
    RETURN
DONE

AUTOMATION(1724,"H:  Exit Track 4")
    CALL(750)
    IFSTASH(THD)
        CLOSE(9014) 
        PICKUP_STASH(THD)
        FON(0)
        IFLOCO(SoundLoco)
            FON(1)
        ENDIF
    ELSE
        PRINT("No Train")
        RETURN
    ENDIF
    FWD(20)
    AT(CD_S3_H_ext)
    STOP
    STASH(THET)
    CALL(702)
    CALL(751)
    RETURN
DONE


//Auto park Holgate sidings
SEQUENCE(701)
IFNOT(CD_S4_HA) 
    RESERVE(H_T1)
    SCREEN(4,1,"H1 Occupied")
    CLOSE(9019)
    FWD(20) 
    AT(CD_S4_HA) 
    DELAY(1000)
    ESTOP
    STASH(THA)
    IFTHROWN(9030)
        CLOSE(9030)
        FREE(E_B1)
    ENDIF
    IFTHROWN(9031)
        CLOSE(9031)
        IF(F_H)
            FREE(F_B1)
            UNLATCH(F_H)
        ENDIF
        FREE(F_B2)
    ENDIF
    RETURN
ENDIF 
IFNOT(CD_S4_HB) 
    RESERVE(H_T2)
    SCREEN(4,2,"H2 Occupied")
    THROW(9019)
    FWD(20) 
    AT(CD_S4_HB) 
    DELAY(1000)
    ESTOP
    STASH(THB)
    IFTHROWN(9030)
        CLOSE(9030)
        FREE(E_B1)
    ENDIF
    IFTHROWN(9031)
        CLOSE(9031)
        IF(F_H)
            FREE(F_B1)
            UNLATCH(F_H)
        ENDIF
        FREE(F_B2)
    ENDIF
    RETURN
ENDIF 
IFNOT(CD_S4_HC) 
    RESERVE(H_T3)
    SCREEN(4,3,"H3 Occupied")
    THROW(9017)
    FWD(20) 
    AT(CD_S4_HC) 
    DELAY(1000)
    ESTOP
    STASH(THC)
    IFTHROWN(9030)
        CLOSE(9030)
        FREE(E_B1)
    ENDIF
    IFTHROWN(9031)
        CLOSE(9031)
        IF(F_H)
            FREE(F_B1)
            UNLATCH(F_H)
        ENDIF
        FREE(F_B2)
    ENDIF
    FREE(F_B2)
    RETURN
ENDIF 
IFNOT(CD_S4_HD) 
    RESERVE(H_T4)
    SCREEN(4,4,"H4 Occupied")
    THROW(9016)
    FWD(20) 
    AT(CD_S4_HD) 
    DELAY(1000)
    STASH(THD)
    ESTOP
    IFTHROWN(9030)
        CLOSE(9030)
        FREE(E_B1)
    ENDIF
    IFTHROWN(9031)
        CLOSE(9031)
        IF(F_H)
            FREE(F_B1)
            UNLATCH(F_H)
        ENDIF 
    ENDIF
    FREE(F_B2)
    RETURN
ENDIF 
DONE

//parkRelease Release the block the train has come from dependant on turnout position
SEQUENCE(702) //Release Parked Block dependant on turnout thrown
    IFTHROWN(9012) //Track FD1
        FREE(H_T1)
        SCREEN(2,1,"")
        CLEAR_STASH(THA)
        RETURN
    ENDIF
    IFTHROWN(9013) //Track FD2
        FREE(H_T2)
        SCREEN(2,2,"")
        CLEAR_STASH(THB)
        RETURN
    ENDIF
    IFTHROWN(9014) //Track FD3
        FREE(H_T3)
        SCREEN(2,3,"")
        CLEAR_STASH(THC)
        RETURN
    ENDIF
    IFCLOSED(9014) //Track FD4
        FREE(H_T4)
        SCREEN(2,4,"")
        CLEAR_STASH(THD)
        RETURN
    ENDIF
 DONE   


