/*
* routes for Holgate sidings
*/

//Holgate exit to track F
AUTOMATION(702,"H:  Holgate -> E")



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




