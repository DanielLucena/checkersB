/* Cinema
 * Author: Eduardo
 * Creation date: 15/05/2025
 */
MACHINE
    Cinema
    
CONSTANTS
   limit_capacidade, limit_salas, limit_filmes, limit_turnos, horario_max, HORARIO, dummyFilme, dummyAssento, dummyIngresso
   
PROPERTIES
     limit_capacidade : NAT1
   & limit_salas : NAT1
   & limit_filmes : NAT1
   & limit_turnos : NAT1
   & horario_max: NAT1
   

   & HORARIO = 0..horario_max
   & dummyFilme: FILME
   & dummyAssento: ASSENTO
   & dummyIngresso: INGRESSO
   
SETS
    SALA
    ;FILME
    ; ASSENTO
    ; INGRESSO

VARIABLES
     filmes, salas,
     salaHasCapacidade, salaHasHorarios, sessao
     ,ingressos_vendidos
     ,ingressos_meia
     ,horaAtual
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
         & horaAtual: HORARIO
         
     //4. Invariantes de salaHasHorarios
         & salaHasHorarios : salas <-> HORARIO
         & ran(salaHasHorarios) <: HORARIO
         &!ss .(ss:SALA => card({ss} <| salaHasHorarios) <= limit_turnos )
         
     //5. Invarintes de sessão
         & sessao : salaHasHorarios +-> filmes
         & ingressos_vendidos : salaHasHorarios +-> 0..limit_capacidade
         & dom(sessao) = dom(ingressos_vendidos)
         & ingressos_meia : salaHasHorarios +-> 0..(limit_capacidade/2)
         & dom(sessao) = dom(ingressos_meia)
         & acentos_sessao : salaHasHorarios +-> (0..limit_capacidade-1 +-> BOOL)
         & dom(sessao) = dom(acentos_sessao)
         
         
         & !ff .(ff : FILME => !hh .(hh : HORARIO => 
         card({ss | ss : SALA 
              & (ss |-> hh) : dom(sessao) 
              & sessao(ss |-> hh)= ff}
              ) <= 1))
        
    //6. Invariantes de ingressos
       //Para toda sessao
        & !(ss, hh) . 
        (ss:SALA & hh:HORARIO & (ss|->hh):dom(sessao) =>
            ingressos_vendidos( (ss|->hh) ) <= salaHasCapacidade(ss)

            & ingressos_meia((ss|->hh) ) <= 
        salaHasCapacidade(ss)/2

            & ingressos_meia((ss|->hh)) 
                <= ingressos_vendidos((ss|->hh))
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
        ff : FILME & ff /: filmes & card(filmes) < limit_filmes & ff /= dummyFilme
    THEN
        filmes := filmes \/ {ff}
    END;
    
    RemoverFilme(ff) =
    PRE
        ff: FILME & ff:filmes 
        & sessao |> {ff} = {}
    THEN
       filmes := filmes - {ff}
    END;
    
    ff <--QueryFilmes =
    PRE filmes /= {}
    THEN
        ANY ss WHERE
            ss : FILME --> BOOL
            & dom(ss|> {TRUE}) = filmes
            
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
    
     ff <-- QuerySalas =
    PRE salas /= {}
    THEN
        ANY ss WHERE 
            ss : SALA --> BOOL 
            & dom(ss|> {TRUE}) = salas
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
       & ss:salas & ff:filmes & ff/= dummyFilme
       & ss|->hh : salaHasHorarios 
       & ss|->hh /: dom(sessao)

       & !s2 .(s2 : SALA & (s2 |-> hh) : dom(sessao) => sessao(s2 |-> hh) /= ff)
    THEN
       sessao := sessao \/ {(ss|->hh)|->ff} 
       || ingressos_vendidos:= ingressos_vendidos \/ {(ss|->hh)|->0} 
       || ingressos_meia := ingressos_meia \/ {(ss|->hh)|->0}
       || acentos_sessao := acentos_sessao 
           \/ {(ss|->hh)|-> ((0..limit_capacidade-1)*{FALSE})}
    END;
    
 RemoverSessao(ss,hh) =
    PRE
       ss:SALA & hh: HORARIO
       & ss:salas & ss|->hh : salaHasHorarios 
       & ss|->hh : dom(sessao) 
       & ingressos_vendidos((ss|->hh)) =0
    THEN
       sessao :=  {ss|->hh} <<| sessao 
       || ingressos_vendidos:= {(ss|->hh)} <<|  ingressos_vendidos 
       || ingressos_meia := {(ss|->hh)} <<|  ingressos_meia 
       || acentos_sessao := {(ss|->hh)} <<| acentos_sessao
    END;


    // Ingresso
   ComprarIngresso(ff,hh,tt,aa)=
    PRE
        ff: FILME
       & hh: HORARIO 
       & tt: 0..1
       & aa: NAT
       & aa: 0..limit_capacidade-1
       & #(ss).
       (ss : SALA 
           & (ss |-> hh) : dom(sessao) 
           & sessao(ss |-> hh) = ff 
            & ingressos_vendidos(ss|->hh) < salaHasCapacidade(ss)
           & (tt=0 => ingressos_meia(ss|->hh) < (salaHasCapacidade(ss)/2))
           & (aa|->FALSE): acentos_sessao(ss |-> hh)
       )
       & hh >= horaAtual
    THEN
    ANY ss
    WHERE ss : SALA & (ss |-> hh) : dom(sessao) & sessao(ss |-> hh) = ff
    THEN
      ingressos_vendidos(ss|->hh) := ingressos_vendidos(ss|->hh) +1
       || acentos_sessao(ss |-> hh) := 
       acentos_sessao(ss |-> hh) <+ {aa|->TRUE}
       || 
       IF tt=0
      THEN ingressos_meia(ss|->hh) := ingressos_meia(ss|->hh) +1
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
              || acentos_sessao := dom(acentos_sessao)* {(0..limit_capacidade-1)*{FALSE}}
          ELSE
              horaAtual := horaAtual + 1
          END
      END;
      
      
      ii<--query_Passar_Hora=
      BEGIN
          ii:= horaAtual
      END;
      
      //Querrys mais complexas
    
    ii<--ConsultarIngressosDisponiveisPorSessao(ss,hh)=
    PRE ss:SALA & hh:HORARIO 
       & ss:salas & ss|->hh : salaHasHorarios 
       & ss|->hh : dom(sessao)
      & (ss|->hh) : dom(ingressos_vendidos)
    THEN ii := salaHasCapacidade(ss)
             - ingressos_vendidos(ss|->hh)
    END;
    
    ii<--ConsultarIngressosCompradosPorSessao(ss,hh)=
    PRE ss:SALA & hh:HORARIO 
       & ss:salas & ss|->hh : salaHasHorarios 
       & ss|->hh : dom(sessao)
       & (ss|->hh) : dom(ingressos_vendidos)
    THEN ii := ingressos_vendidos(ss|->hh)
    END;
    
    rr <-- visualizarFilmesEmCartaz =
    PRE filmes /= {}
    THEN
        ANY ss WHERE
            ss : FILME --> BOOL &
            dom(ss |> {TRUE}) = ran(sessao)
        THEN
            rr := ss
        END
    END;

    
   rr <-- VisualizarFilmesPorHorario(hh) =
    PRE 
        hh : HORARIO
    THEN
        ANY fs WHERE
            fs: FILME --> BOOL
            & dom(fs |> {TRUE}) = sessao[salaHasHorarios |> {hh}]
        THEN
            rr := fs
        END
    END;

   
   
     rr <-- VisualizarHorariosPorFilme(ff) =
    PRE 
        ff : FILME & ff : filmes
    THEN
        ANY hs WHERE
            hs : HORARIO --> BOOL
            & dom(hs |> {TRUE}) = ran(dom(sessao |> {ff}))
        THEN
            rr := hs
        END
    END;

   
// Operaçoes de PRE
   
   ok<-- pre_adicionarFilme(ff) =
   PRE ff: FILME
   THEN
      IF ff /: filmes & card(filmes) < limit_filmes & ff/= dummyFilme
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
    PRE
        ss:SALA & hh:HORARIO
    THEN
        IF ss: salas 
           & ss|->hh : salaHasHorarios 
           & ss|->hh : dom(sessao) 
           & ingressos_vendidos(ss |-> hh) = 0
        THEN
            ok := TRUE
        ELSE
            ok := FALSE
        END
    END;

   
ok <-- pre_comprarIngresso(ff, hh, tt,aa) =
   PRE ff : FILME & hh : HORARIO & tt : 0..1 & aa: NAT
   THEN
       IF 
          hh >= horaAtual
          & aa: 0..limit_capacidade-1
          & #(ss).(
              ss : SALA &
              (ss |-> hh) : dom(sessao) &
              sessao(ss |-> hh) = ff &
              ingressos_vendidos(ss |-> hh) < salaHasCapacidade(ss) &
              (tt = 0 => ingressos_meia(ss |-> hh) < salaHasCapacidade(ss) / 2)
              & (aa|->FALSE): acentos_sessao(ss |-> hh)
          )
       THEN ok := TRUE
       ELSE ok := FALSE
       END
   END;

   
   ok <-- pre_consultarIngressosDisponiveisPorSessao(ss, hh) =
   PRE ss : SALA & hh : HORARIO
   THEN
      IF (ss |-> hh) : dom(sessao)
      THEN ok := TRUE
      ELSE ok := FALSE
      END
   END;
   
   ok <-- pre_consultarIngressosCompradosPorSessao(ss, hh) =
   PRE ss : SALA & hh : HORARIO
   THEN
      IF (ss |-> hh) : dom(sessao)
      THEN ok := TRUE
      ELSE ok := FALSE
      END
   END;
   
   
   ok <-- pre_disponibilizarSalaEmHorarios(ss,hh) = 
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
   END
      
END