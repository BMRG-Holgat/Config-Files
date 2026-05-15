/*
* routes for Holgate sidings
*/

//Holgate exit to track F
//AUTOMATION(702,"H:  Holgate -> E")
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
            IFGREEN(SIG_F4)
                AMBER(SIG_F4)
            ENDIF
            PICKUP_STASH(THET)
            FWD(10)
            AT(CD_S3_F1)
            RED(SIG_H1)
            SPEED(20)
            CALL(753)
        ELSE
            PRINT("Waiting for block F3")
            FOLLOW(1700)
        ENDIF
    ELSE
        PRINT("No Train")
        FOLLOW(1700)
    ENDIF  
    AT(CD_S1_F)
    SPEED(30)
    FOLLOW(620)
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
    CALL(751)
    RETURN
DONE


//Auto park Holgate sidings
SEQUENCE(701)
IFNOT(CD_S4_HA) 
PRINT("Trying to get into HA")
    RESERVE(H_T1)
    CLOSE(9019)
    FWD(20) 
    AT(CD_S4_HA) 
    DELAY(2000)
    PRINT("STOP")
    STOP
    SCREEN(4,1,"H1 Occupied")
    ROUTE_CAPTION(1721,"Occupied")
    ROUTE_ACTIVE(1721)
    STASH(THA)
    IFTHROWN(9030)
        CLOSE(9030)
        FREE(E_B1)
    ENDIF
    IFTHROWN(9031)
        CLOSE(9031)
    ENDIF
    FREE(F_B1)
    FREE(F_B2)
    PRINT("FREED b1 & b2")
    PRINT("HA Complete")
    RETURN
    PRINT("DID NOT RETURN")
ENDIF 
IFNOT(CD_S4_HB) 
PRINT("trying to get into HB")
    RESERVE(H_T2)
    THROW(9019)
    FWD(20) 
    AT(CD_S4_HB) 
    DELAY(1500)
    STOP
    SCREEN(4,2,"H2 Occupied")
    ROUTE_CAPTION(1722,"Occupied")
    ROUTE_ACTIVE(1722)
    STASH(THB)
    IFTHROWN(9030)
        CLOSE(9030)
        FREE(E_B1)
    ENDIF
    IFTHROWN(9031)
        CLOSE(9031)
    ENDIF
        FREE(F_B1)
        FREE(F_B2)
    RETURN
ENDIF 
IFNOT(CD_S4_HC) 
    RESERVE(H_T3)
    THROW(9017)
    FWD(20) 
    AT(CD_S4_HC) 
    DELAY(1500)
    STOP
    SCREEN(4,3,"H3 Occupied")
    ROUTE_CAPTION(1723,"Occupied")
    ROUTE_ACTIVE(1723)
    STASH(THC)
    IFTHROWN(9030)
        CLOSE(9030)
        FREE(E_B1)
    ENDIF
    IFTHROWN(9031)
        CLOSE(9031)
    ENDIF
        FREE(F_B1)
        FREE(F_B2)
    RETURN
ENDIF 
IFNOT(CD_S4_HD) 
    RESERVE(H_T4)
    THROW(9016)
    FWD(20) 
    AT(CD_S4_HD) 
    DELAY(1500)
    STASH(THD)
    STOP
    SCREEN(4,4,"H4 Occupied")
    ROUTE_CAPTION(1724,"Occupied")
    ROUTE_ACTIVE(1724)
    IFTHROWN(9030)
        CLOSE(9030)
        FREE(E_B1)
    ENDIF
    IFTHROWN(9031)
        CLOSE(9031)
    ENDIF
        FREE(F_B1) 
        FREE(F_B2)
    RETURN
ENDIF 
DONE


SEQUENCE(702)
    AT(CD_F3_F1)
    AMBER(SIG_F4)
    FREE(F_B2)
    IFTHROWN(9027)
        CLOSE(9027)
    ENDIF
    IFTHROWN(9028)
        CLOSE(9028)
    ENDIF
    RETURN
DONE

//ParkRelease Release the block and stash of the relevant track
SEQUENCE(753) 
    IFCLOSED(9012)
        IFTHROWN(9013)
            FREE(H_T2)
            CLEAR_STASH(THB)
            ROUTE_DISABLED(1722)
            ROUTE_CAPTION(1722,"Empty")
            SCREEN(4,2,"H2 Empty")
            RETURN
        ENDIF
        IFCLOSED(9013)
            IFTHROWN(9014)
                FREE(H_T3)
                ROUTE_DISABLED(1723)
                ROUTE_CAPTION(1723,"Empty")
                CLEAR_STASH(THC)
                SCREEN(4,3,"H3 Empty")
                RETURN
            ENDIF
            IFCLOSED(9014)
                FREE(H_T4)
                CLEAR_STASH(THD)
                ROUTE_DISABLED(1724)
                ROUTE_CAPTION(1724,"Empty")
                SCREEN(4,4,"H4 Empty")
                RETURN 
            ENDIF
        ENDIF
    ELSE
            IFTHROWN(9012)
                FREE(H_T1)
                CLEAR_STASH(THA)
                ROUTE_DISABLED(1721)
                ROUTE_CAPTION(1721,"Empty")
                SCREEN(4,1,"H1 Empty")
                RETURN  
        ENDIF
DONE