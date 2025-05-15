/* Cinema
 * Author: Eduardo
 * Creation date: 15/05/2025
 */
MACHINE
    Cinema
    
CONSTANTS
   maxCapacidade
   
PROPERTIES
   maxCapacidade = 10
SETS
    SALA
    ;HORARIO = {manha,tarde,noite}
    ;FILME
    ; TIPO_INGRESSO = {meia,inteira}
VARIABLES
     filmes, salas,
     salaHasCapacidade, salaHasHorarios, sessao

INVARIANT
     filmes <: FILME
     & salas <: SALA
     & salaHasCapacidade : salas --> 1..10
     & salaHasHorarios : salas <-> HORARIO
     & sessao : salas * HORARIO >+> filmes
         
     //COLOCAR ABAIXO AS REGRAS DE NEGOCIO
     //uma sala so pode ficar disponivel no maximo em 2 turnos
     &!ss .( (ss:SALA => card({ss} <| salaHasHorarios) <=2))
     
INITIALISATION
    filmes := {}
    || salas :={} 
    || salaHasCapacidade := {} 
    || salaHasHorarios :={} 
    || sessao := {}
    
OPERATIONS
    AdicionarFilme(ff) =
    PRE
        ff : FILME & ff /: filmes 
    THEN
        filmes := filmes \/ {ff}
    END;
    
    AdicionarSala(ss,tt)=
    PRE
       ss : SALA & ss /: salas 
       & tt : NAT & tt <=10 
       & tt > 0 
    THEN
       salas := salas \/ {ss} 
       || salaHasCapacidade := {ss |-> tt} \/ salaHasCapacidade
    END;
     
    DisponibilizarSalaEmHorarios(ss,hh) = 
    PRE
       ss:SALA & ss: salas 
       & hh:HORARIO & {ss|->hh} /\ salaHasHorarios ={} 
       & card({ss} <| salaHasHorarios) +1 <=2
    THEN
       salaHasHorarios := {ss|->hh} \/ salaHasHorarios
    END;
    
    AdicionarSessao(ss, hh, ff) = 
    PRE
       ss:SALA & hh: HORARIO & ff: FILME
       & ss:salas & ff:filmes 
       & ss|->hh : salaHasHorarios 
       & ss|->hh /: dom(sessao)
    THEN
       sessao := sessao \/ {(ss|->hh)|->ff}
    END
    
END
