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
    ; MOVE = {mno,mne,mso,mse,cno,cne,cso,cse}
    ; PLAYER={black_player,white_player}
//    ; side= {0..7}
//    ; cord= {side*side}

//     ;black_init={1,3,5,7,8,10,12,14,17,19,21,23}
//    ; white_init={40,42,44,46,49,51,53,55,56,58,60,62}
    
PROPERTIES
    black_init={1,3,5,7,8,10,12,14,17,19,21,23}
    & white_init={40,42,44,46,49,51,53,55,56,58,60,62}
VARIABLES
    board, moves, captured, chosenPiece
    ,turn

INVARIANT
    board: 0..63 --> SPOT 
    & moves: NAT +-> MOVE
    & captured: NAT +-> 0..63
    & chosenPiece: -1..63
    & turn: PLAYER
    
INITIALISATION
    board:= black_init*{black} \/ white_init*{white} 
    \/ ((black_init\/white_init)<<|(0..63)*{none})
    || moves := {}
    || captured := {}
    || chosenPiece := -1
    || turn := white_player
//    board:= cord*{none}
//    
OPERATIONS

//move_piece(position, mov)=
//PRE position: 0..63 & mov: MOVE
//THEN
//    CASE mov OF
//    EITHER mno THEN 

choose_piece(piece)=
PRE piece: 0..63 & moves ={} 
    & (turn=white_player => board(piece): {white,whiteq})
    & (turn=black_player => board(piece): {black,blackq})
THEN chosenPiece := piece
END

//mover_noroeste=
//PRE chosenPiece /= -1
//THEN IF 


    
    
    
END
