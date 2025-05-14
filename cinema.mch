/* cinema
 * Author: daniel
 * Creation date: 14/05/2025
 */
MACHINE
    cinema
SETS
    SALA
    ;HORARIO = {manha,tarde,noite}
    ;FILME
    ; TIPO_INGRESSO = {meia,inteira}
    
VARIABLES
    sessoes, programacao, FILMES

INVARIANT
    sessoes: SALA +-> HORARIO
    & FILMES <: FILME
    & programacao: sessoes +-> FILME
    
    
//    & ! ff . (ff: ran(programacao) => sessoes~[(programacao |> ff)]   )


/*verificar se atingiu a quantidade limite de uma sala*/
//& !(ss ,hh).(ss : SALA & hh: HORARIO & (ss,hh) : dom(INGRESSOS_VENDIDOS) =>
//    (INGRESSOS_VENDIDOS(ss,hh)) = (mm,ii) &
//    mm : NAT & ii : NAT &
//    mm + ii <= CAPACIDADE(ss)
//)
    
INITIALISATION
    sessoes := {}
    || programacao := {}
    || FILMES := {}
    

OPERATIONS
    AdicionarFilme(ff) =
    PRE
        ff : FILME & ff /: FILMES
    THEN
        FILMES := FILMES \/ {ff}
    END;

    RemoverFilme(ff) =
    PRE
        ff : FILMES 
    THEN
        programacao := programacao |>> {ff}
        
        || FILMES := FILMES - {ff}
    END;
    
    RemoverFilmeDaSessao(ss)=
    PRE ss: sessoes
    THEN programacao := ss  <<| programacao
    END
    

END
