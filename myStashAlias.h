/*
Keep track of stash aliases for each track
Each track has a stash alias for each block in the yard
When a loco is placed in a block the stash alias is set to that block
When the loco is removed from the block the stash alias is cleared

syntax
ALIAS((track)(yard)(number),id) - define the alias
STASH(alias) - store the loco in the alias
PICKUP_STASH(alias) - remove the loco from the alias
*/

ALIAS(TA,900) //Fiddle yard A Track 1
ALIAS(TB1,901) //Fiddle yard B Track 1
ALIAS(TB2,902) //Fiddle yard B Track 2
ALIAS(TB3,903) //Fiddle yard B Track 3
ALIAS(TB4,904) //Fiddle yard B Track 4
ALIAS(TB5,905) //Fiddle yard B Track 5
ALIAS(TC1,906) //Fiddle yard C Track 1
ALIAS(TC2,907) //Fiddle yard C Track 2
ALIAS(TC3,908) //Fiddle yard C Track 3
ALIAS(TC4,909) //Fiddle yard C Track 4
ALIAS(TC5,910) //Fiddle yard C Track 5
ALIAS(TD1,911) //Fiddle yard D Track 1
ALIAS(TD2,912) //Fiddle yard D Track 2
ALIAS(TD3,913) //Fiddle yard D Track 3
ALIAS(TD4,914) //Fiddle yard D Track 4
ALIAS(TD5,915) //Fiddle yard D Track 5
ALIAS(TE1,916) //Fiddle yard E Track 1
ALIAS(TE2,917) //Fiddle yard E Track 2
ALIAS(TE3,918) //Fiddle yard E Track 3
ALIAS(TE4,919) //Fiddle yard E Track 4
ALIAS(TE5,920) //Fiddle yard E Track 5
ALIAS(TF,921) //Fiddle yard F Track 1
ALIAS(THA,921) //Holgate Yard Track A
ALIAS(THB,922) //Holgate Yard Track B
ALIAS(THC,923) //Holgate Yard Track C
ALIAS(THD,924) //Holgate Yard Track D
