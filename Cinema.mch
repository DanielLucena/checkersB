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
     , ingressos_meia

INVARIANT
     filmes <: FILME
     & salas <: SALA
     & salaHasCapacidade : salas --> 1..10
     & salaHasHorarios : salas <-> HORARIO
     & sessao : salas * HORARIO +-> filmes
//     & ingressos_vendidos : salas * HORARIO +-> 0..maxCapacidade
     & ingressos_vendidos : (salaHasHorarios) +-> 0..maxCapacidade
     & ingressos_meia : (salaHasHorarios) +-> 0..(maxCapacidade/2)
         
     //COLOCAR ABAIXO AS REGRAS DE NEGOCIO
     //uma sala so pode ficar disponivel no maximo em 2 turnos
     &!ss .( (ss:SALA => card({ss} <| salaHasHorarios) <=2))
     
       //Um filme só pode estar em uma sala por horário
     & !ff .(ff : FILME => !hh .(hh : HORARIO => 
       card({ss | ss : SALA & (ss |-> hh) : dom(sessao) & sessao(ss |-> hh)= ff}) 
             <= 1))

        //O número de ingressos vendidos para uma sessão não pode ultrapassar a capacidade da sala vinculada a ela
        & !(ss, hh) . 
        (ss:SALA & hh:HORARIO & (ss|->hh):dom(ingressos_vendidos) =>     
            ingressos_vendidos(ss|->hh) <= salaHasCapacidade(ss))
        
        //O número de ingressos vendidos como meia entrada para uma sessão não pode ultrapassar mais da metade da capacidade da sala vinculada a esta sessão
        & !(ss, hh) . 
        (ss:SALA & hh:HORARIO & (ss|->hh):dom(ingressos_meia) =>     
            ingressos_meia(ss|->hh) <= (salaHasCapacidade(ss)/2))
        

     
INITIALISATION
    filmes := {}
    || salas :={} 
    || salaHasCapacidade := {} 
    || salaHasHorarios :={} 
    || sessao := {}
    || ingressos_vendidos := {}
    || ingressos_meia := {}
    
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
       || ingressos_meia := ingressos_meia \/ {(ss|->hh)|->0}
    END;
    
    
    
   ComprarIngresso(ff,hh,tt)=
    PRE
        ff: FILME
       & hh: HORARIO 
       & tt: TIPO_INGRESSO
       & #(ss).
       (ss : SALA 
           & (ss |-> hh) : dom(sessao) 
           & sessao(ss |-> hh) = ff 
           & ingressos_vendidos(ss|->hh) < salaHasCapacidade(ss) 
           & (tt=meia => ingressos_meia(ss|->hh) < (salaHasCapacidade(ss)/2))
           )   
    THEN
    ANY ss
    WHERE ss : SALA & (ss |-> hh) : dom(sessao) & sessao(ss |-> hh) = ff
    THEN
       ingressos_vendidos(ss|->hh) := ingressos_vendidos(ss|->hh) +1
       || IF tt=meia
       THEN ingressos_meia(ss|->hh) := ingressos_meia(ss|->hh) +1
       ELSE skip
           END
       END
    END
  
END