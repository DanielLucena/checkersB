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
     , ingressos_vendidos
     , ingressos_meia
     ,turno
     ,horarios

INVARIANT
     filmes <: FILME
     & filmes : FIN(FILME)
     & salas <: SALA
     & horarios: iseq(HORARIO)
     & horarios: FIN(horarios)
     & salaHasCapacidade : salas --> 1..10
     & salaHasHorarios : salas <-> HORARIO
     & sessao : salas * HORARIO +-> filmes
//     & ingressos_vendidos : salas * HORARIO +-> 0..maxCapacidade
     & ingressos_vendidos : (salaHasHorarios) +-> 0..maxCapacidade
     & ingressos_meia : (salaHasHorarios) +-> 0..(maxCapacidade/2)
     & turno : NAT1
         
     //COLOCAR ABAIXO AS REGRAS DE NEGOCIO
     //uma sala so pode ficar disponivel no maximo em 2 turnos
     &!ss .( (ss:SALA => card({ss} <| salaHasHorarios) <=2))
     
     // So podem exister ate 7 salas
     & card(salas) <= 7
     
     //So podem exister cadastrados ate 20 filmes
     & card(filmes) <=20
     
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
        
        //ingressos_meia <= ingressos_vendidos
        
        //toda sessao deve estar tambem relacionada a quantidade de ingressos_vendidos e quantidade de ingressos_meia
        & !(ss, hh) .
        ((ss:SALA & hh:HORARIO & (ss|->hh):dom(sessao)) =>     
            ((ss|->hh):dom(ingressos_vendidos) 
                & (ss|->hh):dom(ingressos_meia))
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
       ss : SALA & ss /: salas & card(salas \/ {ss}) <= 10
       & tt : NAT & tt <=10 
       & tt > 0 
    THEN
       salas := salas \/ {ss} 
       || salaHasCapacidade := {ss |-> tt} \/ salaHasCapacidade
    END;
    
    RemoverSala(ss)=
    PRE
       ss : SALA & ss : salas 
       & card({ss} <| salaHasHorarios) =0
       
    THEN
       salas := salas - {ss} 
       || salaHasCapacidade := {ss } <<| salaHasCapacidade
    END;
    
    ss <--QuerySalas =
    BEGIN ss := salas END;
    
     
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
