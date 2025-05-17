/* cinema_porb
 * Author: daniel
 * Creation date: 14/05/2025
 */
MACHINE
    Cinema_ProB
EXTENDS Cinema
    
CONSTANTS
    /*SALA*/
    VIP, tradicional
    
    /*FILME*/
    ,vingadores, homem_aranha
PROPERTIES
    VIP: SALA & tradicional: SALA
    & SALA={VIP,tradicional} 
    & card(SALA) = 2
    
    
    & vingadores:FILME & homem_aranha:FILME
    & FILME={vingadores, homem_aranha}
    & card(FILME) = 2

END
