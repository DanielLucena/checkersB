/* Cinema
 * Author: Eduardo
 * Creation date: 15/05/2025
 */
MACHINE
    Cinema
    
CONSTANTS
   maxCapacidade, limit_salas, limit_filmes
   
PROPERTIES
   //valores das contantes
     maxCapacidade = 10 
   & limit_salas = 7
   & limit_filmes = 20
   

   
   
   
   
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
     ,turno
     ,horarios

INVARIANT
    
    //1. Invariantes de filmes
         //filmes são um subconjunto de FILME
         filmes <: FILME
         //filmes sao um conjunto finito de FILME
         & filmes : FIN(FILME)
         //So podem exister cadastrados ate 20 filmes
         & card(filmes) <= limit_filmes
         
     //2. Invariantes de salas
         //salas são um subconjunto de SALA
         & salas <: SALA
         //salas são um conjunto finito de SALA
         & salas : FIN(SALA)
         // So podem exister ate 7 salas
         & card(salas) <= limit_salas
         //a função salaHasCapacidade mapeia salas a uma capacidade
         //essa capacidade deve estar entre 1 e maxCapacidade
         & salaHasCapacidade : salas --> 1..maxCapacidade
         //todos os elementos de salas tem que estar mapeados
         //a uma capacidade
         & dom(salaHasCapacidade) = salas
         
     //3. Invariantes de horarios
         //horarios é uma sequencia injetiva de HORARIO
         & horarios: iseq(HORARIO)
         //horarios é um conjunto finito
         & horarios: FIN(horarios)
         //turno armazena um indicie de horarios 
         // que marca o horario atual
         & turno : NAT1
         //turno tem que ser menor do que a quantidade de horarios
         & turno <= card(horarios)
         
     //4. Invariantes de salaHasHorarios
         //salaHasHorarios é uma relação ente salas e HORARIO
         & salaHasHorarios : salas <-> HORARIO
         //uma sala so pode ficar disponivel no maximo em 2 turnos
         &!ss .( (ss:SALA => card({ss} <| salaHasHorarios) <=2))
         
     //5. Invarintes de sessão
         //a função sessao mapeia pares de (salas,HORARIO) a filmes
         //cada par de sala e horario so pode estar ligado a um filme
         //um par de sala e horario pode sem nenhum filme associado
         & sessao : salas * HORARIO +-> filmes
         //a função ingressos_vendidos mapeia um par(salas,HORARIO)
         //a uma quantidade de ingressos vendidos 
         //ente 0 e maxCapacidade
         & ingressos_vendidos : (salaHasHorarios) +-> 0..maxCapacidade
         //a função ingressos_meia mapeia um par(salas,HORARIO)
         //a uma quantidade de ingressos do tipo meia vendidos 
         //ente 0 e metade de maxCapacidade
         & ingressos_meia : (salaHasHorarios) +-> 0..(maxCapacidade/2)
         //Um filme só pode estar em uma sala por horário
         & !ff .(ff : FILME => !hh .(hh : HORARIO => 
         card({ss | ss : SALA 
              & (ss |-> hh) : dom(sessao) 
              & sessao(ss |-> hh)= ff}
              ) <= 1))
         //toda sessao deve estar tambem relacionada a quantidade de
         //ingressos_vendidos e quantidade de ingressos_meia
         & !(ss, hh) .
         ((ss:SALA & hh:HORARIO & (ss|->hh):dom(sessao)) =>     
            ((ss|->hh):dom(ingressos_vendidos) 
                & (ss|->hh):dom(ingressos_meia)))
        
    //6. Invariantes de ingressos
        //O número de ingressos vendidos para uma sessão não pode
        //ultrapassar a capacidade da sala vinculada a ela
        & !(ss, hh) . 
        (ss:SALA & hh:HORARIO & (ss|->hh):dom(ingressos_vendidos) =>     
            ingressos_vendidos(ss|->hh) <= salaHasCapacidade(ss))
        //O número de ingressos vendidos como meia entrada para uma 
        //sessão não pode ultrapassar mais da metade da capacidade da 
        //sala vinculada a esta sessão
        & !(ss, hh) . 
        (ss:SALA & hh:HORARIO & (ss|->hh):dom(ingressos_meia) =>     
            ingressos_meia(ss|->hh) <= (salaHasCapacidade(ss)/2))
        //ingressos_meia <= ingressos_vendidos
        & 1=1 //TODO
     
INITIALISATION
    filmes := {}
    || salas :={} 
    || salaHasCapacidade := {} 
    || salaHasHorarios :={} 
    || sessao := {}
    || ingressos_vendidos := {}
    || ingressos_meia := {}
    || turno := 1
    || horarios := {(1|->manha),(2|->tarde),(3|->noite)}
    
OPERATIONS
    AdicionarFilme(ff) =
    PRE
        ff : FILME & ff /: filmes & card(filmes) <20
    THEN
        filmes := filmes \/ {ff}
    END;
    
    RemoverFilme(ff) =
    PRE
       ff: FILME & ff:filmes 
//       & card (sessao |> {ff}) = 0
& sessao |> {ff} = {}
& filmes = ran(sessao) - {ff}
    THEN
       filmes := filmes - {ff}
    END;
    
    ff <--QueryFilmes =
    PRE filmes /= {}
    THEN
        ANY ss WHERE
            ss : seq(FILME) & ran(ss) = filmes & card(ss) = card(filmes)
        THEN
            ff := ss
        END
    END;
    
    


    AdicionarSala(ss,tt)=
    PRE
       ss : SALA & ss /: salas & card(salas) < limit_salas
       & tt : NAT1 & tt <= maxCapacidade
//       & tt > 0 
    THEN
       salas := salas \/ {ss} 
       || salaHasCapacidade(ss) := tt
//           := salaHasCapacidade \/ {ss |-> tt}
    END;
    
    RemoverSala(ss)=
    PRE
       ss : SALA & ss : salas 
       & {ss} <| salaHasHorarios = {}
    THEN
       salas := salas - {ss} 
       || salaHasCapacidade := {ss } <<| salaHasCapacidade
    END;
    
    ff <--QuerySalas =
    PRE salas /= {}
    THEN
        ANY ss WHERE 
            ss : seq(SALA) & ran(ss) = salas 
            & card(ss) = card(salas)
        THEN 
            ff := ss
        END
    END;
           
    
     
    DisponibilizarSalaEmHorarios(ss,hh) = 
    PRE
       ss:SALA & ss: salas 
       & hh:HORARIO & {ss|->hh} /\ salaHasHorarios ={} 
       & card({ss} <| salaHasHorarios) +1 <=2
       & hh: ran(horarios)
    THEN
       salaHasHorarios := {ss|->hh} \/ salaHasHorarios
    END;
    
    IndisponibilizarSalaEmHorarios(ss,hh) =
    PRE
       ss:SALA & ss: salas 
       & hh:HORARIO & {ss|->hh} /\ salaHasHorarios /={} 
       & (ss|->hh) /: dom(sessao)
    THEN
       salaHasHorarios := salaHasHorarios - {ss|->hh}
       || ingressos_vendidos := {ss|->hh} <<| ingressos_vendidos
       || ingressos_meia := {ss|->hh} <<| ingressos_meia
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
    
    RemoverSessao(ss,hh) =
    PRE
       ss:SALA & hh: HORARIO
       & ss:salas & ss|->hh : salaHasHorarios 
       & ss|->hh : dom(sessao) 
       & ingressos_vendidos(ss |-> hh) =0
    THEN
       sessao :=  {ss|->hh} <<| sessao 
       ||       ingressos_vendidos:= ingressos_vendidos - {(ss|->hh)|->0} 
       || ingressos_meia := ingressos_meia - {(ss|->hh)|->0}
    END;
    
    ss <-- QuerySessao=
    BEGIN ss := sessao END;
    
    
    
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
       & hh: ran(horarios)
       & horarios~(hh) >= turno
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
    END;
    
    ii<--ConsultarIngressosDisponiveisPorSessao(ss,hh)=
    PRE ss:SALA & hh:HORARIO 
       & ss:salas & ss|->hh : salaHasHorarios 
       & ss|->hh : dom(sessao)
       & ss|->hh : dom(ingressos_vendidos)
    THEN ii := salaHasCapacidade(ss) - ingressos_vendidos(ss,hh)
    END;
    
    ii<--ConsultarIngressosCompradosPorSessao(ss,hh)=
    PRE ss:SALA & hh:HORARIO 
       & ss:salas & ss|->hh : salaHasHorarios 
       & ss|->hh : dom(sessao)
       & ss|->hh : dom(ingressos_vendidos)
    THEN ii := ingressos_vendidos(ss,hh)
    END;
    
    rr<--visualizarFilmesEmCartaz=
    BEGIN rr:=ran(sessao)
    END;
    
     rr <-- VisualizarHorariosPorFilme(ff) =
   PRE 
       ff : FILME & ff : filmes
   THEN
       ANY hs WHERE
           hs : POW(HORARIO) &
           hs = {hh | hh : HORARIO & 
                      #(ss).(ss : salas & (ss |-> hh) : dom(sessao) & sessao(ss |-> hh) = ff)}
       THEN
           rr := hs
       END
   END;
    
   rr <-- VisualizarFilmesPorHorario(hh) =
   PRE 
       hh : HORARIO
   THEN
       ANY fs WHERE
           fs : POW(filmes) &
           fs = {ff | ff : filmes & 
                      #(ss).(ss : SALA & (ss |-> hh) : dom(sessao) & sessao(ss |-> hh) = ff)}
       THEN
           rr := fs
       END
   END;
        
      
    Passar_Turno =
      PRE  horarios /= {} & turno < card(horarios)
      THEN turno := turno + 1
          END
      ;
      
//      adicionar_horario(hh)=
//          PRE hh : HORARIO & hh /: ran(horarios)
//          THEN horarios := horarios <- hh
//      END;
      
      Passar_Dia=
      PRE turno = card(horarios)
          THEN turno := 1
          || ingressos_vendidos := dom(ingressos_vendidos)*{0}
          || ingressos_meia := dom(ingressos_meia)*{0}
      END
      
      
      
      
      
  
END
