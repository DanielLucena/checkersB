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
     , ingressos_vendidos

INVARIANT
     filmes <: FILME
     & salas <: SALA
     & salaHasCapacidade : salas --> 1..10
     & salaHasHorarios : salas <-> HORARIO
     & sessao : salas * HORARIO +-> filmes
     & ingressos_vendidos : salas * HORARIO +-> 0..maxCapacidade
         
     //COLOCAR ABAIXO AS REGRAS DE NEGOCIO
     //uma sala so pode ficar disponivel no maximo em 2 turnos
     &!ss .( (ss:SALA => card({ss} <| salaHasHorarios) <=2))
     
       //Um filme só pode estar em uma sala por horário
     & !ff .(ff : FILME => !hh .(hh : HORARIO => 
       card({ss | ss : SALA & (ss |-> hh) : dom(sessao) & sessao(ss |-> hh)= ff}) 
             <= 1))


     
INITIALISATION
    filmes := {}
    || salas :={} 
    || salaHasCapacidade := {} 
    || salaHasHorarios :={} 
    || sessao := {}
    || ingressos_vendidos := {}
    
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
       & !s2 .(s2 : SALA & (s2 |-> hh) : dom(sessao) => sessao(s2 |-> hh) /= ff)
    THEN
       sessao := sessao \/ {(ss|->hh)|->ff} 
       ||       ingressos_vendidos:= ingressos_vendidos \/ {(ss|->hh)|->0} 
    END;
   ComprarIngresso(ff,hh)=
    PRE
//       ss: SALA 
        ff: FILME
       & hh: HORARIO 
//       & ss: salas
       & #(ss).(ss : SALA & (ss |-> hh) : dom(sessao) & sessao(ss |-> hh) = ff & ingressos_vendidos(ss|->hh) < salaHasCapacidade(ss)) 
//       &(ss |-> hh) : dom(sessao)
//       & ingressos_vendidos(ss|->hh) < salaHasCapacidade(ss)
     
    THEN
    ANY ss
    WHERE ss : SALA & (ss |-> hh) : dom(sessao) & sessao(ss |-> hh) = ff
    THEN
       ingressos_vendidos(ss|->hh) := ingressos_vendidos(ss|->hh) +1
       END
    END
  
END