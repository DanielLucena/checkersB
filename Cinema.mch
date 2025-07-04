/* Cinema
 * Author: Eduardo
 * Creation date: 15/05/2025
 */
MACHINE
    Cinema
    
CONSTANTS
   limit_capacidade, limit_salas, limit_filmes, limit_turnos, horario_max, HORARIO
   
PROPERTIES
   //valores das contantes
   //CORRECAO: passar valores das constantes para arquivo Cinema_ProB
     limit_capacidade : NAT1
   & limit_salas : NAT1
   & limit_filmes : NAT1
   & limit_turnos : NAT1
   & horario_max: NAT1
   //CORRECAO: Horário tem que ser uma constante
    //Solucao: 24 horas 
//   & HORARIO <: NAT
   & HORARIO = 0..horario_max
   
SETS
    SALA
    ;FILME
    ;TIPO_INGRESSO = {meia,inteira}

VARIABLES
     filmes, salas,
     salaHasCapacidade, salaHasHorarios, sessao
     ,ingressos_vendidos
     ,ingressos_meia
     //CORRECAO: Remover conceito de turno 
     //e inserir conceito de hora
     ,horaAtual
     //CORRECAO: remover variavel ingressos_ofertados 
     ,acentos_sessao

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
     //CORRECAO: Refinar o conceito de horário para (inicio, fim)
//         & horaAtual: NAT
         & horaAtual: HORARIO
         
     //4. Invariantes de salaHasHorarios
         & salaHasHorarios : salas <-> HORARIO
         & ran(salaHasHorarios) <: HORARIO
         &!ss .(ss:SALA => card({ss} <| salaHasHorarios) <= limit_turnos )
         
     //5. Invarintes de sessão
     //CORRECAO: Inserir o conceito de assento marcado para a sessão
         & sessao : salaHasHorarios +-> filmes
         & ingressos_vendidos : sessao --> 0..limit_capacidade
         & ingressos_meia : sessao --> 0..(limit_capacidade/2)
         & acentos_sessao : sessao --> (0..limit_capacidade-1 +-> BOOL)
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

//            & ingressos_ofertados((ss|->hh) |-> sessao(ss|->hh)) = 
//        salaHasCapacidade(ss)

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
    || horaAtual := 0
    || acentos_sessao := {}

    
OPERATIONS
    // Filmes
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
            ss : 0..card(filmes)-1 +->FILME
            & ran(ss) = filmes
            
        THEN
            ff := ss
        END
    END;
    
    //Sala
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
    
    //CORRECAO: Remover tipos abstratos da assinatura das operações
    //Solucao: trocar sequencia por array
    ff <-- QuerySalas =
    PRE salas /= {}
    THEN
        ANY ss WHERE 
            ss : 0..card(salas)-1 +-> SALA &
            ran(ss) = salas
        THEN 
            ff := ss
        END
    END;
       
    
    //SalaHasHorario 
    DisponibilizarSalaEmHorarios(ss,hh) = 
    PRE
       ss:SALA & ss: salas 
       & hh:HORARIO 
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
      
    // Sessao
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
       || acentos_sessao := acentos_sessao 
           \/ {((ss|->hh)|->ff)|-> ((0..limit_capacidade-1)*{FALSE})}
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
       || acentos_sessao := {(ss|->hh)|->sessao((ss|->hh))} <<| acentos_sessao
    END;
  
     //CORRECAO: Remover tipos abstratos da assinatura das operações
    //Solucao: trocar sequencia por array
    vv <-- QuerySessao =
    PRE sessao /= {}
    THEN
        ANY ff WHERE
            ff : 0..card(sessao)-1 +-> (SALA*HORARIO)*FILME &
            ran(ff) = sessao
        THEN
            vv := ran(ff)
        END
    END;


    // Ingresso
   ComprarIngresso(ff,hh,tt,aa)=
    PRE
        ff: FILME
       & hh: HORARIO 
       & tt: TIPO_INGRESSO
       & aa: NAT
       & aa: 0..limit_capacidade-1
       & #(ss).
       (ss : SALA 
           & (ss |-> hh) : dom(sessao) 
           & sessao(ss |-> hh) = ff 
           & ingressos_vendidos((ss|->hh)|->ff ) < salaHasCapacidade(ss)
           & (tt=meia => ingressos_meia((ss|->hh)|->ff) < (salaHasCapacidade(ss)/2))
           & (aa|->FALSE): acentos_sessao((ss |-> hh)|->ff )
       )
       & hh >= horaAtual
    THEN
    ANY ss
    WHERE ss : SALA & (ss |-> hh) : dom(sessao) & sessao(ss |-> hh) = ff
    THEN
       ingressos_vendidos((ss|->hh)|->ff) := ingressos_vendidos((ss|->hh)|->ff) +1
       || acentos_sessao((ss |-> hh)|->ff ) := 
       acentos_sessao((ss |-> hh)|->ff ) <+ {aa|->TRUE}
       || 
       IF tt=meia
       THEN ingressos_meia((ss|->hh)|->ff) := ingressos_meia((ss|->hh)|->ff) +1
       ELSE skip
           END
       END
    END;
    
     //Passagem de temp
     Passar_Hora =
     BEGIN
          IF horaAtual+1 /: HORARIO
          THEN 
              ingressos_vendidos := dom(ingressos_vendidos)*{0}
              || ingressos_meia := dom(ingressos_meia)*{0}
              || horaAtual := 0
              //zerar acentos das sessoes
              || acentos_sessao := dom(acentos_sessao)* {(0..limit_capacidade-1)*{FALSE}}
          ELSE
              horaAtual := horaAtual + 1
          END
      END;
      
      //Querrys mais complexas
    
    ii<--ConsultarIngressosDisponiveisPorSessao(ss,hh)=
    PRE ss:SALA & hh:HORARIO 
       & ss:salas & ss|->hh : salaHasHorarios 
       & ss|->hh : dom(sessao)
       & (ss|->hh)|->sessao(ss|->hh) : dom(ingressos_vendidos)
    THEN ii := salaHasCapacidade(ss)
             - ingressos_vendidos((ss|->hh)|->sessao(ss|->hh))
    END;
    
    ii<--ConsultarIngressosCompradosPorSessao(ss,hh)=
    PRE ss:SALA & hh:HORARIO 
       & ss:salas & ss|->hh : salaHasHorarios 
       & ss|->hh : dom(sessao)
       & (ss|->hh)|->sessao(ss|->hh) : dom(ingressos_vendidos)
    THEN ii := ingressos_vendidos((ss|->hh)|->sessao(ss|->hh))
    END;
    
    //CORRECAO: Remover tipos abstratos da assinatura das operações
    //Solucao: trocar sequencia por array
    rr <-- visualizarFilmesEmCartaz =
    PRE filmes /= {}
    THEN
        ANY ss WHERE
            ss : 0..card(ran(sessao))-1 +-> FILME &
            ran(ss) = ran(sessao)
        THEN
            rr := ss
        END
    END;

    
   //CORRECAO: Remover tipos abstratos da assinatura das operações
    //Solucao: trocar sequencia por array 
   rr <-- VisualizarFilmesPorHorario(hh) =
    PRE 
        hh : HORARIO
    THEN
        ANY fs WHERE
            fs : 0..
            card({ff | ff : filmes & 
               #(ss).(ss : SALA & (ss |-> hh) : dom(sessao) 
                  & sessao(ss |-> hh) = ff)}) - 1 +-> FILME 
                  & ran(fs) = {ff | ff : filmes & 
                    #(ss).(ss : SALA & (ss |-> hh) : dom(sessao) 
                                        & sessao(ss |-> hh) = ff)}
        THEN
            rr := fs
        END
    END;

   
   
    
    //CORRECAO: Remover tipos abstratos da assinatura das operações
    //Solucao: trocar sequencia por array
     rr <-- VisualizarHorariosPorFilme(ff) =
    PRE 
        ff : FILME & ff : filmes
    THEN
        ANY hs WHERE
            hs : 0..
            card({hh | hh : HORARIO &
                    #(ss).(ss : salas & (ss |-> hh) : dom(sessao) 
                       & sessao(ss |-> hh) = ff)}) - 1 +-> HORARIO 
                       & ran(hs) = {hh | hh : HORARIO &
                              #(ss).(ss : salas &
                                     (ss |-> hh) : dom(sessao) 
                                     & sessao(ss |-> hh) = ff)}
        THEN
            rr := hs
        END
    END;

   
   
   //CORRECAO: Todas as operações que serão chamadas pela interface deverão adotar uma das duas abordagens discutidas em sala da aula. QUalquer dúvida pode me procurar.
   
   ok<-- pre_adicionarFilme(ff) =
   PRE ff: FILME
   THEN
      IF ff /: filmes & card(filmes) < limit_filmes
      THEN ok := TRUE
      ELSE ok:= FALSE
      END
   END;
   
   ok <-- pre_removerFilme(ff) =
   PRE ff: FILME
   THEN
      IF ff : filmes & ff /: ran(sessao)
      THEN ok := TRUE
      ELSE ok := FALSE
      END
   END;
    
   ok<-- pre_adicionarSala(ss, tt) =
   PRE ss: SALA & tt: NAT
   THEN
      IF ss /: salas & card(salas) < limit_salas & tt : 1..limit_capacidade
      THEN ok := TRUE
      ELSE ok:= FALSE
      END
   END;
   
   ok <-- pre_removerSala(ss)= 
   PRE ss : SALA
   THEN
      IF ss : salas & {ss} <| salaHasHorarios = {} 
      THEN ok := TRUE
      ELSE ok := FALSE
      END
   END;
   
   ok <-- pre_disponibilizarSalaEmHorarios(ss, hh) =
   PRE ss : SALA & hh : HORARIO
   THEN
       IF ss : salas &
          hh : HORARIO &
          (ss |-> hh) /: salaHasHorarios &
          card({ss} <| salaHasHorarios) < limit_turnos
       THEN ok := TRUE
       ELSE ok := FALSE
       END
   END;

   ok <-- pre_indisponibilizarSalaEmHorarios(ss, hh) =
   PRE ss : SALA & hh : HORARIO
   THEN
       IF ss : salas &
          (ss |-> hh) : salaHasHorarios &
          (ss |-> hh) /: dom(sessao)
       THEN ok := TRUE
       ELSE ok := FALSE
       END
   END;
   
   ok <-- pre_adicionarSessao(ss, hh, ff) =
   PRE ss : SALA & hh : HORARIO & ff : FILME
   THEN
       IF ss : salas &
          ff : filmes &
          (ss |-> hh) : salaHasHorarios &
          (ss |-> hh) /: dom(sessao) &
          !s2 .(s2 : SALA & (s2 |-> hh) : dom(sessao) => sessao(s2 |-> hh) /= ff)
       THEN ok := TRUE
       ELSE ok := FALSE
       END
   END;

   ok <-- pre_removerSessao(ss, hh) =
   PRE ss : SALA & hh : HORARIO
   THEN
       IF (ss |-> hh) : dom(sessao) &
          ingressos_vendidos((ss |-> hh) |-> sessao(ss |-> hh)) = 0
       THEN ok := TRUE
       ELSE ok := FALSE
       END
   END;
   
   ok <-- pre_comprarIngresso(ff, hh, tt) =
   PRE ff : FILME & hh : HORARIO & tt : TIPO_INGRESSO
   THEN
       IF 
          hh >= horaAtual
          & #(ss).(
              ss : SALA &
              (ss |-> hh) : dom(sessao) &
              sessao(ss |-> hh) = ff &
              ingressos_vendidos((ss |-> hh) |-> ff) < salaHasCapacidade(ss) &
              (tt = meia => ingressos_meia((ss |-> hh) |-> ff) < salaHasCapacidade(ss) / 2)
          )
       THEN ok := TRUE
       ELSE ok := FALSE
       END
   END;
   


   ok <-- pre_consultarIngressosPorSessao(ss, hh) =
   PRE ss : SALA & hh : HORARIO
   THEN
      IF (ss |-> hh) : dom(sessao)
      THEN ok := TRUE
      ELSE ok := FALSE
      END
   END;
   
   
   ok <-- pre_DisponibilizarSalaEmHorarios(ss,hh) = 
    PRE
       ss:SALA & hh:HORARIO 
    THEN
       IF 
           ss: salas
           & {ss|->hh} /\ salaHasHorarios ={} 
           & card({ss} <| salaHasHorarios) < limit_turnos
       THEN 
           ok := TRUE
       ELSE
           ok := FALSE
       END
   END;
   
   ok <-- pre_IndisponibilizarSalaEmHorarios(ss, hh) =
    PRE
        ss:SALA & hh:HORARIO
    THEN
        IF ss: salas 
           & {ss|->hh} /\ salaHasHorarios /= {} 
           & (ss|->hh) /: dom(sessao)
        THEN
            ok := TRUE
        ELSE
            ok := FALSE
        END
    END;
    
    ok <-- pre_AdicionarSessao(ss, hh, ff) =
    PRE
        ss:SALA & hh:HORARIO & ff:FILME
    THEN
        IF ss: salas 
           & ff: filmes 
           & ss|->hh : salaHasHorarios 
           & ss|->hh /: dom(sessao)
           & (!s2 . (s2: SALA & (s2 |-> hh) : dom(sessao) => sessao(s2 |-> hh) /= ff))
        THEN
            ok := TRUE
        ELSE
            ok := FALSE
        END
    END;
    
    ok <-- pre_RemoverSessao(ss, hh) =
    PRE
        ss:SALA & hh:HORARIO
    THEN
        IF ss: salas 
           & ss|->hh : salaHasHorarios 
           & ss|->hh : dom(sessao) 
           & ingressos_vendidos((ss|->hh)|->sessao((ss|->hh))) = 0
        THEN
            ok := TRUE
        ELSE
            ok := FALSE
        END
    END



   
END
