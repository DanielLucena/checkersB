/* Checkers
 * Author: daniel
 * Creation date: 12/05/2025
 */
MACHINE
    Checkers
   
CONSTANTS
black_init
, white_init


SETS
    response= {yes, no}
    ; SPOT= {white, black, whiteq, blackq, none}
//    ; side= {0..7}
//    ; cord= {side*side}

//     ;black_init={1,3,5,7,8,10,12,14,17,19,21,23}
//    ; white_init={40,42,44,46,49,51,53,55,56,58,60,62}
    
PROPERTIES
    black_init={1,3,5,7,8,10,12,14,17,19,21,23}
    & white_init={40,42,44,46,49,51,53,55,56,58,60,62}
VARIABLES
    board

INVARIANT
    board: 0..63 --> SPOT
    
INITIALISATION
    board:= black_init*{black} \/ white_init*{white} 
    \/ ((black_init\/white_init)<<|(0..63)*{none})
//    board:= cord*{none}
//    
//OPERATIONS
//    
//    place_pawn(linha,coluna)=
//    PRE linha:0..7 & coluna:0..7
//    THEN board((linha,coluna)) := black
//    END
    
    


    
    
    
END
