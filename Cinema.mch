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
    ;TIPO_INGRESSO = {meia,inteira}

VARIABLES
     filmes, salas,
     salaHasCapacidade, salaHasHorarios, sessao
     ,ingressos_vendidos
     ,ingressos_meia
     ,turno
     ,horarios
     ,ingressos_ofertados

INVARIANT
    
    //1. Invariantes de filmes
         filmes <: FILME
         & filmes : FIN(FILME)
         & card(filmes) <= limit_filmes
         
     //2. Invariantes de salas
         & salas <: SALA
         & salas : FIN(SALA)
         & card(salas) <= limit_salas
         & salaHasCapacidade : salas --> 1..limit_capacidade
         
     //3. Invariantes de horarios
         & horarios: iseq(HORARIO)
         & horarios: FIN(horarios)
         & turno : NAT1
         & turno <= card(horarios)
         
     //4. Invariantes de salaHasHorarios
         & salaHasHorarios : salas <-> HORARIO
         & ran(salaHasHorarios) <: ran(horarios)
         &!ss .(ss:SALA => card({ss} <| salaHasHorarios) <= limit_turnos )
         
     //5. Invarintes de sessão
         & sessao : salaHasHorarios +-> filmes
         & ingressos_vendidos : sessao --> 0..limit_capacidade
         & ingressos_meia : sessao --> 0..(limit_capacidade/2)
         & ingressos_ofertados : sessao --> 1..limit_capacidade
         & !ff .(ff : FILME => !hh .(hh : HORARIO => 
         card({ss | ss : SALA 
              & (ss |-> hh) : dom(sessao) 
              & sessao(ss |-> hh)= ff}
              ) <= 1))
        
    //6. Invariantes de ingressos
        //Para toda sessao
        & !(ss, hh) . 
        (ss:SALA & hh:HORARIO & (ss|->hh):dom(sessao) =>
            ingressos_vendidos( (ss|->hh) |-> sessao(ss|->hh) ) <= salaHasCapacidade(ss)

            & ingressos_meia((ss|->hh) |-> sessao(ss|->hh)) <= 
        salaHasCapacidade(ss)/2

            & ingressos_ofertados((ss|->hh) |-> sessao(ss|->hh)) = 
        salaHasCapacidade(ss)

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
        THEN
            ff := ss
        END
    END;
    

    AdicionarSala(ss,tt)=
    PRE
       ss : SALA & ss /: salas & card(salas) < limit_salas
       & tt : NAT1 & tt <= limit_capacidade
    THEN
       salas := salas \/ {ss} 
       || salaHasCapacidade(ss) := tt
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
        THEN 
            ff := ss
        END
    END;       
    
     
    DisponibilizarSalaEmHorarios(ss,hh) = 
    PRE
       ss:SALA & ss: salas 
       & hh:HORARIO 
       & hh: ran(horarios)
       & {ss|->hh} /\ salaHasHorarios ={} 
       & card({ss} <| salaHasHorarios) < limit_turnos
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
  
  
    vv <-- QuerySessao =
    PRE sessao /= {}
    THEN
        ANY ff WHERE
            ff : seq((SALA*HORARIO)*FILME) & ran(ff) = sessao
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
    
    rr<--visualizarFilmesEmCartaz=
    PRE filmes /= {}
    THEN
        ANY ss WHERE
            ss : iseq(FILME) & ran(ss) = ran(sessao) 
        THEN
            rr := ss
        END
    END;
    
    //TODO: verificar se ta ok
     rr <-- VisualizarHorariosPorFilme(ff) =
   PRE 
       ff : FILME & ff : filmes
   THEN
       ANY hs WHERE
           hs : iseq(HORARIO) &
           ran(hs) = {hh | hh : HORARIO &
                           #(ss).(ss : salas &
                                  (ss |-> hh) : dom(sessao) &
                                  sessao(ss |-> hh) = ff)} 
       THEN
           rr := hs
       END
   END;
   
    
   //TODO: verificar se ta ok
   rr <-- VisualizarFilmesPorHorario(hh) =
   PRE 
       hh : HORARIO
   THEN
       ANY fs WHERE
           fs : iseq(FILME) &
           ran(fs) = {ff | ff : filmes & 
                           #(ss).(ss : SALA & (ss |-> hh) : dom(sessao) 
                               & sessao(ss |-> hh) = ff)} 
       THEN
           rr := fs
       END
   END;
  
      
    Passar_Turno =
      PRE  horarios /= {} & turno < card(horarios)
      THEN turno := turno + 1
      END;
      
      
      Passar_Dia=
      PRE turno = card(horarios)
          THEN turno := 1
          || ingressos_vendidos := dom(ingressos_vendidos)*{0}
          || ingressos_meia := dom(ingressos_meia)*{0}
      END
      
  
END

