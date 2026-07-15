//myTrackD_alt.h


//Test new autopark sequence
//TD1       916
//TD2       917
//TD3       918
//TD4       919
//TD5       920
//Track 1 
SEQUENCE(454)
    IFSTASH(TD1)
        FOLLOW(455)
    ELSE
        IFRESERVE(D_B7)
            SCREEN(1,5,"Loading Track 1")
            SCREEN(2,5,"Loading Track D1")
            CLOSE(9130)
            FWD(PARKING)
            AT(CD_F2_D1)
            DELAY(2500)
            ESTOP
            FREE(D_B6)
            STASH(TD1)
            SCREEN(1,5,"")
            SCREEN(2,5,"")
            RETURN
        ENDIF
    ENDIF
DONE

//Track 2
SEQUENCE(455)
    IFSTASH(TD2)
        FOLLOW(456)
    ELSE
        IFRESERVE(D_B8)
            SCREEN(1,5,"Loading Track 2")
            SCREEN(2,5,"Loading Track D2")
            THROW(9131)
            FWD(PARKING)
            AT(CD_F2_D2)
            DELAY(1500)
            ESTOP
            FREE(D_B6)
            STASH(TD2)
            SCREEN(1,5,"")
            SCREEN(2,5,"")
            RETURN
        ENDIF
    ENDIF
DONE

//Track3
SEQUENCE(456)
    IFSTASH(TD3)
        FOLLOW(457)
    ELSE
        IFRESERVE(D_B9)
            SCREEN(1,5,"Loading Track 3")
            SCREEN(2,5,"Loading Track D3")
            THROW(9132)
            FWD(PARKING)
            AT(CD_F2_D3)
            DELAY(700)
            ESTOP
            FREE(D_B6)
            STASH(TD3)
            SCREEN(1,5,"")
            SCREEN(2,5,"")
            RETURN
        ENDIF
    ENDIF
DONE

//Track 4
SEQUENCE(457)
    IFSTASH(TD4)
        FOLLOW(458)
    ELSE
        IFRESERVE(D_B10)
            SCREEN(1,5,"Loading Track 4")
            SCREEN(2,5,"Loading Track D4")
            THROW(9133)
            FWD(PARKING)
            AT(CD_F2_D4)
            DELAY(750)
            ESTOP
            FREE(D_B6)
            STASH(TD4)
            SCREEN(1,5,"")
            SCREEN(2,5,"")
            RETURN
        ENDIF
    ENDIF
DONE

//Track 5
SEQUENCE(458)
    IFSTASH(TD5)
        SCREEN(1,5,"Yard B full!")
        SCREEN(2,5,"Yard B Full")
        ESTOP
        FOLLOW(454)
    ELSE
        IFRESERVE(D_B11)
            SCREEN(1,5,"Loading Track 5")
            SCREEN(2,5,"Loading Track D5")
            CLOSE(9133)
            FWD(PARKING)
            AT(CD_F2_D5)
            DELAY(500)
            ESTOP
            FREE(D_B6)
            STASH(TD5)
            SCREEN(1,5,"")
            SCREEN(2,5,"")
            RETURN
        ENDIF
    ENDIF
DONE

