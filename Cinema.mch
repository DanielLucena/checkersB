/* Cinema
 * Author: Eduardo
 * Creation date: 15/05/2025
 */
MACHINE
    Cinema
    
CONSTANTS
   limit_capacidade, limit_salas, limit_filmes, limit_turnos
   
PROPERTIES
   //valores das contantes
     limit_capacidade = 10
   & limit_salas = 5
   & limit_filmes = 10
   & limit_turnos = 2
   
   
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
     ,ingressos_ofertados

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
         //essa capacidade deve estar entre 1 e limit_capacidade
         & salaHasCapacidade : salas --> 1..limit_capacidade
         //todos os elementos de salas tem que estar mapeados
         //a uma capacidade
         //TODO: remover
         & dom(salaHasCapacidade) = salas 
         
     //3. Invariantes de horarios
         //horarios é uma sequencia de HORARIO que não possui repetição
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
         // salas so podem estar ligadas a horarios cadastrados
         & ran(salaHasHorarios) <: ran(horarios)
         //uma sala so pode ficar disponivel no maximo em 2 turnos
         &!ss .(ss:SALA => card({ss} <| salaHasHorarios) <= limit_turnos )
         
     //5. Invarintes de sessão
         //a função sessao mapeia pares de (salas,HORARIO) a filmes
         //cada par de sala e horario so pode estar ligado a um filme
         //um par de sala e horario pode sem nenhum filme associado
         & sessao : salaHasHorarios +-> filmes
         //a função ingressos_vendidos mapeia uma sessao
         //a uma quantidade de ingressos vendidos 
         //ente 0 e limit_capacidade
//TODO:remover  & ingressos_vendidos : (salaHasHorarios) +-> 0..limit_capacidade
         & ingressos_vendidos : sessao --> 0..limit_capacidade
         //a função ingressos_meia mapeia uma sessão
         //a uma quantidade de ingressos do tipo meia vendidos 
         //ente 0 e metade de limit_capacidade
//TODO:remover & ingressos_meia : (salaHasHorarios) +-> 0..(limit_capacidade/2)
         & ingressos_meia : sessao --> 0..(limit_capacidade/2)
         // função ingressos_ofertados mapeia uma sessao 
         // a quantidade de ingressos que poderão ser vendidos
         // para essa sessao
         & ingressos_ofertados : sessao --> 1..limit_capacidade
         
//         & !(ss, hh) .
//         ((ss:SALA & hh:HORARIO & (ss|->hh):dom(sessao)) =>     
//            ((ss|->hh):dom(ingressos_ofertados) 
//                & (ss|->hh):dom(ingressos_meia)))
         //Não é permitido exibir o mesmo filme em mais de uma sala 
         //no mesmo horário. 
         & !ff .(ff : FILME => !hh .(hh : HORARIO => 
         card({ss | ss : SALA 
              & (ss |-> hh) : dom(sessao) 
              & sessao(ss |-> hh)= ff}
              ) <= 1))
         //toda sessao deve estar tambem relacionada a quantidade de
         //ingressos_vendidos e quantidade de ingressos_meia
         //TODO: REMOVER
//         & !(ss, hh) .
//         ((ss:SALA & hh:HORARIO & (ss|->hh):dom(sessao)) =>     
//            ((ss|->hh):dom(ingressos_vendidos) 
//                & (ss|->hh):dom(ingressos_meia)))
        
    //6. Invariantes de ingressos
        
        //Para toda sessao
        & !(ss, hh) . 
        (ss:SALA & hh:HORARIO & (ss|->hh):dom(sessao) =>
        //O número de ingressos vendidos para uma sessão não pode
        //ultrapassar a capacidade da sala vinculada a ela.
            ingressos_vendidos( (ss|->hh) |-> sessao(ss|->hh) ) <= salaHasCapacidade(ss)
        //e o número de ingressos vendidos como meia entrada para uma 
        //sessão não pode ultrapassar mais da metade da capacidade da 
        //sala vinculada a esta sessão
        & ingressos_meia((ss|->hh) |-> sessao(ss|->hh)) <= 
    salaHasCapacidade(ss)/2
        //e a quantidade de ingressos ofertados é igual para uma
        //sessao é igual a capacidade da sala vinculada a ela.
        & ingressos_ofertados((ss|->hh) |-> sessao(ss|->hh)) = 
    salaHasCapacidade(ss)
        //e o número de ingressos vendidos como meia entrada para uma 
        //sessão não pode ultrapassar o número total de ingressos vendidos para a mesma sessão
        & ingressos_meia((ss|->hh)|->sessao(ss|->hh)) 
            <= ingressos_vendidos((ss|->hh)|->sessao(ss|->hh))
        )

       
     
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
    || ingressos_ofertados := {}
    
OPERATIONS
    AdicionarFilme(ff) =
    PRE
        ff : FILME & ff /: filmes & card(filmes) < limit_filmes
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
            ss : seq(FILME) & ran(ss) = filmes 
//            & card(ss) = card(filmes)
        THEN
            ff := ss
        END
    END;
    
    


    AdicionarSala(ss,tt)=
    PRE
       ss : SALA & ss /: salas & card(salas) < limit_salas
       & tt : NAT1 & tt <= limit_capacidade
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
            ss : iseq(SALA) & ran(ss) = salas 
//            & card(ss) = card(salas)
        THEN 
            ff := ss
        END
    END;
           
    
     
    DisponibilizarSalaEmHorarios(ss,hh) = 
    PRE
       ss:SALA & ss: salas 
       & hh:HORARIO & {ss|->hh} /\ salaHasHorarios ={} 
       & card({ss} <| salaHasHorarios) +1 <= limit_turnos
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
       //TODO: remover
//       || ingressos_vendidos := {ss|->hh} <<| ingressos_vendidos
//       || ingressos_meia := {ss|->hh} <<| ingressos_meia
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
       || ingressos_vendidos:= ingressos_vendidos \/ {((ss|->hh)|->ff)|->0} 
       || ingressos_meia := ingressos_meia \/ {((ss|->hh)|->ff)|->0}
       || ingressos_ofertados := ingressos_ofertados 
           \/ {((ss|->hh)|->ff)|-> salaHasCapacidade(ss)}
    END;
    
    RemoverSessao(ss,hh) =
    PRE
       ss:SALA & hh: HORARIO
       & ss:salas & ss|->hh : salaHasHorarios 
       & ss|->hh : dom(sessao) 
       & ingressos_vendidos((ss|->hh)|->sessao((ss|->hh))) =0
    THEN
       sessao :=  {ss|->hh} <<| sessao 
       || ingressos_vendidos:= {(ss|->hh)|->sessao((ss|->hh))} <<|  ingressos_vendidos 
       || ingressos_meia := {(ss|->hh)|->sessao((ss|->hh))} <<|  ingressos_meia 
       || ingressos_ofertados := {(ss|->hh)|->sessao((ss|->hh))} <<| ingressos_ofertados
    END;
    
    //TODO: alterar para nao determinismo
//    ss <-- QuerySessao=
//    BEGIN ss := sessao END;
    
    vv <-- QuerySessao =
    PRE sessao /= {}
    THEN
        ANY ff WHERE
            ff : seq((SALA*HORARIO)*FILME) & ran(ff) = sessao
//            & card(ff) = card(sessao)
        THEN
            vv := ran(ff)
        END
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
           & ingressos_vendidos((ss|->hh)|->ff ) < salaHasCapacidade(ss)
           //TODO: verificar se deve mesmo ser uma implicação
           & (tt=meia => ingressos_meia((ss|->hh)|->ff) < (salaHasCapacidade(ss)/2))
       )
       & hh: ran(horarios)
       & horarios~(hh) >= turno
    THEN
    ANY ss
    WHERE ss : SALA & (ss |-> hh) : dom(sessao) & sessao(ss |-> hh) = ff
    THEN
       ingressos_vendidos((ss|->hh)|->ff) := ingressos_vendidos((ss|->hh)|->ff) +1
       || IF tt=meia
       THEN ingressos_meia((ss|->hh)|->ff) := ingressos_meia((ss|->hh)|->ff) +1
       ELSE skip
           END
       END
    END;
    
    ii<--ConsultarIngressosDisponiveisPorSessao(ss,hh)=
    PRE ss:SALA & hh:HORARIO 
       & ss:salas & ss|->hh : salaHasHorarios 
       & ss|->hh : dom(sessao)
       & (ss|->hh)|->sessao(ss|->hh) : dom(ingressos_vendidos)
    THEN ii := ingressos_ofertados((ss|->hh)|->sessao(ss|->hh))
             - ingressos_vendidos((ss|->hh)|->sessao(ss|->hh))
    END;
    
    ii<--ConsultarIngressosCompradosPorSessao(ss,hh)=
    PRE ss:SALA & hh:HORARIO 
       & ss:salas & ss|->hh : salaHasHorarios 
       & ss|->hh : dom(sessao)
       & (ss|->hh)|->sessao(ss|->hh) : dom(ingressos_vendidos)
    THEN ii := ingressos_vendidos((ss|->hh)|->sessao(ss|->hh))
    END;
    
    //TODO: alterar para nao determinismo
    rr<--visualizarFilmesEmCartaz=
    PRE filmes /= {}
    THEN
        ANY ss WHERE
            ss : seq(FILME) & ran(ss) = ran(sessao) 
//            & card(ss) = card(ran(sessao))
        THEN
            rr := ss
        END
    END;
    
    //TODO: alterar para nao determinismo
     rr <-- VisualizarHorariosPorFilme(ff) =
   PRE 
       ff : FILME & ff : filmes
   THEN
       ANY hs WHERE
           hs : seq(HORARIO) &
           ran(hs) = {hh | hh : HORARIO &
                           #(ss).(ss : salas &
                                  (ss |-> hh) : dom(sessao) &
                                  sessao(ss |-> hh) = ff)} &
           card(hs) = card(ran(hs))
       THEN
           rr := hs
       END
   END;
    
   //TODO: alterar para nao determinismo 
   rr <-- VisualizarFilmesPorHorario(hh) =
   PRE 
       hh : HORARIO
   THEN
       ANY fs WHERE
           fs : seq(FILME) &
           ran(fs) = {ff | ff : filmes & 
                           #(ss).(ss : SALA & (ss |-> hh) : dom(sessao) & sessao(ss |-> hh) = ff)} 
//                       &card(fs) = card(ran(fs))
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

