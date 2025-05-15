/* cinema_porb
 * Author: daniel
 * Creation date: 14/05/2025
 */
MACHINE
    Cinema_ProB
EXTENDS Cinema
    
CONSTANTS
    /*SALA*/
    SALA1, SALA2
    
    /*FILME*/
    ,vigadores, homem_aranha
PROPERTIES
    SALA1: SALA & SALA2: SALA
    & SALA={SALA1,SALA2} 
    & card(SALA) = 2
    
    
    & vigadores:FILME & homem_aranha:FILME
    & FILME={vigadores, homem_aranha}
    & card(FILME) = 2

END
