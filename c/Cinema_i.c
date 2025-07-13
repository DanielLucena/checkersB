/* WARNING if type checker is not performed, translation could contain errors ! */

#include "Cinema.h"

/* Clause CONCRETE_CONSTANTS */
/* Basic constants */

#define Cinema__limit_capacidade 10
#define Cinema__limit_salas 5
#define Cinema__limit_filmes 10
#define Cinema__limit_turnos 2
#define Cinema__horario_max 24
#define Cinema__dummyFilme 0
/* Array and record constants */
/* Clause CONCRETE_VARIABLES */

static bool Cinema__filmes_i[Cinema__limit_filmes+1];
static bool Cinema__salas_i[Cinema__limit_salas+1];
static int32_t Cinema__salaHasCapacidade_i[Cinema__limit_salas+1];
static bool Cinema__salaHasHorarios_i[Cinema__limit_salas+1][Cinema__horario_max+1];
static int32_t Cinema__sessao_i[Cinema__limit_salas+1][Cinema__horario_max+1];
static int32_t Cinema__ingressos_vendidos_i[Cinema__limit_salas+1][Cinema__horario_max+1];
static int32_t Cinema__ingressos_meia_i[Cinema__limit_salas+1][Cinema__horario_max+1];
static int32_t Cinema__horaAtual_i;
/* Clause INITIALISATION */
void Cinema__INITIALISATION(void)
{
    
    unsigned int i = 0, j= 0;
    for(i = 0; i <= Cinema__limit_filmes;i++)
    {
        Cinema__filmes_i[i] = false;
    }
    for(i = 0; i <= Cinema__limit_salas;i++)
    {
        Cinema__salas_i[i] = false;
    }
    for(i = 0; i <= Cinema__limit_salas;i++)
    {
        Cinema__salaHasCapacidade_i[i] = 0;
    }
    for(i = 0; i <= Cinema__limit_salas;i++)
    {
        for(j = 0; j <= Cinema__horario_max;j++)
        {
            Cinema__salaHasHorarios_i[i][j] = false;
        }
    }
    for(i = 0; i <= Cinema__limit_salas;i++)
    {
        for(j = 0; j <= Cinema__horario_max;j++)
        {
            Cinema__sessao_i[i][j] = Cinema__dummyFilme;
        }
    }
    Cinema__horaAtual_i = 0;
    for(i = 0; i <= Cinema__limit_salas;i++)
    {
        for(j = 0; j <= Cinema__horario_max;j++)
        {
            Cinema__ingressos_vendidos_i[i][j] = 0;
        }
    }
    for(i = 0; i <= Cinema__limit_salas;i++)
    {
        for(j = 0; j <= Cinema__horario_max;j++)
        {
            Cinema__ingressos_meia_i[i][j] = 0;
        }
    }
}

/* Clause OPERATIONS */

void Cinema__AdicionarFilme(Cinema__FILME ff)
{
    Cinema__filmes_i[ff] = true;
}

void Cinema__RemoverFilme(Cinema__FILME ff)
{
    Cinema__filmes_i[ff] = false;
}

void Cinema__QueryFilmes(bool *ff)
{
    {
        int32_t ii;
        bool filmeAtual;
        
        ii = 0;
        filmeAtual = false;
        while((ii) < (Cinema__limit_filmes))
        {
            filmeAtual = Cinema__filmes_i[ii];
            ff[ii] = filmeAtual;
            ii = ii+1;
        }
    }
}

void Cinema__AdicionarSala(Cinema__SALA ss, int32_t tt)
{
    Cinema__salas_i[ss] = true;
    Cinema__salaHasCapacidade_i[ss] = tt;
}

void Cinema__RemoverSala(Cinema__SALA ss)
{
    Cinema__salas_i[ss] = false;
    Cinema__salaHasCapacidade_i[ss] = 0;
}

void Cinema__QuerySalas(bool *ff)
{
    unsigned int i = 0;
    {
        {
            int32_t cc;
            
            cc = 0;
            for(i = 0; i <= Cinema__limit_salas;i++)
            {
                ff[i] = false;
            }
            while((cc) < (Cinema__limit_salas))
            {
                ff[cc] = Cinema__salas_i[cc];
                cc = cc+1;
            }
        }
    }
}

void Cinema__DisponibilizarSalaEmHorarios(Cinema__SALA ss, int32_t hh)
{
    Cinema__salaHasHorarios_i[ss][hh] = true;
}

void Cinema__IndisponibilizarSalaEmHorarios(Cinema__SALA ss, int32_t hh)
{
    Cinema__salaHasHorarios_i[ss][hh] = false;
}

void Cinema__AdicionarSessao(Cinema__SALA ss, int32_t hh, Cinema__FILME ff)
{
    Cinema__sessao_i[ss][hh] = ff;
    Cinema__ingressos_vendidos_i[ss][hh] = 0;
    Cinema__ingressos_meia_i[ss][hh] = 0;
    {
        int32_t ii;
        int32_t capacidadeSala;
        
        ii = 0;
        capacidadeSala = Cinema__salaHasCapacidade_i[ss];
        while((ii) < (capacidadeSala))
        {
            ii = ii+1;
        }
    }
}

void Cinema__RemoverSessao(Cinema__SALA ss, int32_t hh)
{
    ;
}

void Cinema__Passar_Hora(void)
{
    unsigned int i = 0, j= 0;
    {
        if((Cinema__horaAtual_i) < (Cinema__horario_max))
        {
            Cinema__horaAtual_i = Cinema__horaAtual_i+1;
        }
        else
        {
            Cinema__horaAtual_i = 0;
            for(i = 0; i <= Cinema__limit_salas;i++)
            {
                for(j = 0; j <= Cinema__horario_max;j++)
                {
                    Cinema__salaHasHorarios_i[i][j] = false;
                }
            }
            for(i = 0; i <= Cinema__limit_salas;i++)
            {
                for(j = 0; j <= Cinema__horario_max;j++)
                {
                    Cinema__sessao_i[i][j] = Cinema__dummyFilme;
                }
            }
            for(i = 0; i <= Cinema__limit_salas;i++)
            {
                for(j = 0; j <= Cinema__horario_max;j++)
                {
                    Cinema__ingressos_vendidos_i[i][j] = 0;
                }
            }
            for(i = 0; i <= Cinema__limit_salas;i++)
            {
                for(j = 0; j <= Cinema__horario_max;j++)
                {
                    Cinema__ingressos_meia_i[i][j] = 0;
                }
            }
        }
    }
}

void Cinema__ComprarIngresso(Cinema__FILME ff, int32_t hh, Cinema__TIPO_INGRESSO tt, int32_t aa)
{
    ;
}

void Cinema__ConsultarIngressosDisponiveisPorSessao(Cinema__SALA ss, int32_t hh, int32_t *ii)
{
    ;
}

void Cinema__ConsultarIngressosCompradosPorSessao(Cinema__SALA ss, int32_t hh, int32_t *ii)
{
    ;
}

void Cinema__visualizarFilmesEmCartaz(bool *rr)
{
    unsigned int i = 0;
    for(i = 0; i <= Cinema__limit_filmes;i++)
    {
        rr[i] = false;
    }
}

void Cinema__VisualizarFilmesPorHorario(int32_t hh, bool *rr)
{
    unsigned int i = 0;
    for(i = 0; i <= Cinema__limit_filmes;i++)
    {
        rr[i] = false;
    }
}

void Cinema__VisualizarHorariosPorFilme(Cinema__FILME ff, bool *rr)
{
    unsigned int i = 0;
    for(i = 0; i <= Cinema__horario_max;i++)
    {
        rr[i] = false;
    }
}

void Cinema__pre_adicionarFilme(Cinema__FILME ff, bool *ok)
{
    {
        bool filme;
        
        filme = Cinema__filmes_i[ff];
        if(filme == false)
        {
            (*ok) = true;
        }
        else
        {
            (*ok) = false;
        }
    }
}

void Cinema__pre_removerFilme(Cinema__FILME ff, bool *ok)
{
    {
        bool filme;
        
        filme = Cinema__filmes_i[ff];
        if(filme == true)
        {
            (*ok) = true;
        }
        else
        {
            (*ok) = false;
        }
    }
}

void Cinema__pre_adicionarSala(Cinema__SALA ss, int32_t tt, bool *ok)
{
    {
        bool sala;
        
        sala = Cinema__salas_i[ss];
        if(((sala == false) &&
            ((tt) >= (1))) &&
        ((tt) <= (Cinema__limit_capacidade)))
        {
            (*ok) = true;
        }
        else
        {
            (*ok) = false;
        }
    }
}

void Cinema__pre_removerSala(Cinema__SALA ss, bool *ok)
{
    {
        bool sala;
        
        sala = Cinema__salas_i[ss];
        if(sala == true)
        {
            (*ok) = true;
        }
        else
        {
            (*ok) = false;
        }
    }
}

void Cinema__pre_disponibilizarSalaEmHorarios(Cinema__SALA ss, int32_t hh, bool *ok)
{
    {
        bool disponivel;
        bool existeSala;
        
        existeSala = Cinema__salas_i[ss];
        disponivel = Cinema__salaHasHorarios_i[ss][hh];
        if((disponivel == false) &&
        (existeSala == true))
        {
            (*ok) = true;
        }
        else
        {
            (*ok) = false;
        }
    }
}

void Cinema__pre_indisponibilizarSalaEmHorarios(Cinema__SALA ss, int32_t hh, bool *ok)
{
    {
        bool disponivel;
        bool existeSala;
        
        existeSala = Cinema__salas_i[ss];
        disponivel = Cinema__salaHasHorarios_i[ss][hh];
        if((disponivel == true) &&
        (existeSala == true))
        {
            (*ok) = true;
        }
        else
        {
            (*ok) = false;
        }
    }
}

void Cinema__pre_adicionarSessao(Cinema__SALA ss, int32_t hh, Cinema__FILME ff, bool *ok)
{
    ;
}

void Cinema__pre_removerSessao(Cinema__SALA ss, int32_t hh, bool *ok)
{
    ;
}

void Cinema__pre_comprarIngresso(Cinema__FILME ff, int32_t hh, Cinema__TIPO_INGRESSO tt, bool *ok)
{
    ;
}

void Cinema__pre_consultarIngressosPorSessao(Cinema__SALA ss, int32_t hh, bool *ok)
{
    ;
}

