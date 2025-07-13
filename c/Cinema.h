#ifndef _Cinema_h
#define _Cinema_h

#include <stdint.h>
#include <stdbool.h>
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


#define Cinema__SALA__max Cinema__limit_salas
#define Cinema__FILME__max Cinema__limit_filmes
/* Clause SETS */
typedef int Cinema__SALA;
typedef int Cinema__FILME;
typedef enum
{
    Cinema__meia,
    Cinema__inteira
    
} Cinema__TIPO_INGRESSO;
#define Cinema__TIPO_INGRESSO__max 2

/* Clause CONCRETE_CONSTANTS */
/* Basic constants */
#define Cinema__limit_capacidade 10
#define Cinema__limit_salas 5
#define Cinema__limit_filmes 10
#define Cinema__limit_turnos 2
#define Cinema__horario_max 24
typedef int Cinema__HORARIO;
#define Cinema__dummyFilme 0
/* Array and record constants */








/* Clause CONCRETE_VARIABLES */

extern void Cinema__INITIALISATION(void);

/* Clause OPERATIONS */

extern void Cinema__AdicionarFilme(Cinema__FILME ff);
extern void Cinema__RemoverFilme(Cinema__FILME ff);
extern void Cinema__QueryFilmes(bool *ff);
extern void Cinema__AdicionarSala(Cinema__SALA ss, int32_t tt);
extern void Cinema__RemoverSala(Cinema__SALA ss);
extern void Cinema__QuerySalas(bool *ff);
extern void Cinema__DisponibilizarSalaEmHorarios(Cinema__SALA ss, int32_t hh);
extern void Cinema__IndisponibilizarSalaEmHorarios(Cinema__SALA ss, int32_t hh);
extern void Cinema__AdicionarSessao(Cinema__SALA ss, int32_t hh, Cinema__FILME ff);
extern void Cinema__RemoverSessao(Cinema__SALA ss, int32_t hh);
extern void Cinema__ComprarIngresso(Cinema__FILME ff, int32_t hh, Cinema__TIPO_INGRESSO tt, int32_t aa);
extern void Cinema__Passar_Hora(void);
extern void Cinema__ConsultarIngressosDisponiveisPorSessao(Cinema__SALA ss, int32_t hh, int32_t *ii);
extern void Cinema__ConsultarIngressosCompradosPorSessao(Cinema__SALA ss, int32_t hh, int32_t *ii);
extern void Cinema__visualizarFilmesEmCartaz(bool *rr);
extern void Cinema__VisualizarFilmesPorHorario(int32_t hh, bool *rr);
extern void Cinema__VisualizarHorariosPorFilme(Cinema__FILME ff, bool *rr);
extern void Cinema__pre_adicionarFilme(Cinema__FILME ff, bool *ok);
extern void Cinema__pre_removerFilme(Cinema__FILME ff, bool *ok);
extern void Cinema__pre_adicionarSala(Cinema__SALA ss, int32_t tt, bool *ok);
extern void Cinema__pre_removerSala(Cinema__SALA ss, bool *ok);
extern void Cinema__pre_indisponibilizarSalaEmHorarios(Cinema__SALA ss, int32_t hh, bool *ok);
extern void Cinema__pre_adicionarSessao(Cinema__SALA ss, int32_t hh, Cinema__FILME ff, bool *ok);
extern void Cinema__pre_removerSessao(Cinema__SALA ss, int32_t hh, bool *ok);
extern void Cinema__pre_comprarIngresso(Cinema__FILME ff, int32_t hh, Cinema__TIPO_INGRESSO tt, bool *ok);
extern void Cinema__pre_consultarIngressosPorSessao(Cinema__SALA ss, int32_t hh, bool *ok);
extern void Cinema__pre_disponibilizarSalaEmHorarios(Cinema__SALA ss, int32_t hh, bool *ok);

#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif /* _Cinema_h */
