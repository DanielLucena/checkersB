#include <stdio.h>
#include <stdlib.h>
#include "Cinema.h" // Inclui o seu header exato
// Adicionado para garantir que as constantes de tipo de ingresso estejam definidas
#ifndef Cinema__meia
#define Cinema__meia 0
#endif
#ifndef Cinema__inteira
#define Cinema__inteira 1
#endif

// Definições ausentes do seu header para o main (se necessário)
typedef int Cinema__FILME;
typedef int Cinema__SALA;
typedef int Cinema__TIPO_INGRESSO;

// =============================================================================
//                       PROTÓTIPOS DE FUNÇÕES
// =============================================================================

// --- Funções executoras (lógica principal) ---
bool executar_adicionar_filme(Cinema__FILME id_filme);
bool executar_remover_filme(Cinema__FILME id_filme);
bool executar_adicionar_sala(Cinema__SALA id_sala, int capacidade);
bool executar_remover_sala(Cinema__SALA id_sala);
bool executar_disponibilizar_sala(Cinema__SALA id_sala, int horario);
bool executar_indisponibilizar_sala(Cinema__SALA id_sala, int horario);
bool executar_adicionar_sessao(Cinema__SALA id_sala, int horario, Cinema__FILME id_filme);
bool executar_remover_sessao(Cinema__SALA id_sala, int horario);
bool executar_comprar_ingresso(Cinema__FILME id_filme, int horario, Cinema__TIPO_INGRESSO tipo, int assento);
int executar_query_filmes();
int executar_query_salas();
int executar_visualizar_filmes_em_cartaz();
int executar_visualizar_filmes_por_horario(int horario);
int executar_visualizar_horarios_por_filme(Cinema__FILME id_filme);
void executar_passar_hora();
int executar_consultar_ingressos_comprados(Cinema__SALA id_sala, int horario);
int executar_consultar_ingressos_disponiveis(Cinema__SALA id_sala, int horario);

// --- Funções "handle" (interface com o usuário) ---
void handle_adicionar_filme();
void handle_remover_filme();
void handle_adicionar_sala();
void handle_remover_sala();
void handle_adicionar_sessao();
void handle_remover_sessao();
void handle_comprar_ingresso();
void handle_disponibilizar_sala();
void handle_indisponibilizar_sala();
void handle_executar_cenario_teste();
void handle_executar_cenario_teste_limites_e_bordas();
void handle_query_filmes();
void handle_query_salas();
void handle_visualizar_filmes_em_cartaz();
void handle_visualizar_filmes_por_horario();
void handle_visualizar_horarios_por_filme();
void handle_passar_hora();
void handle_consultar_ingressos_comprados();
void handle_consultar_ingressos_disponiveis();

// =============================================================================
//                       MENU E FUNÇÃO PRINCIPAL
// =============================================================================
void exibir_menu()
{
    int hora_atual = -1;
    Cinema__query_Passar_Hora(&hora_atual);
    printf("\n--- 🎟️  Sistema de Gerenciamento Multicine cinemas (Hora Atual: %02dh) 🎟️  ---\n", hora_atual);
    printf("--- Gerenciamento ---\n");
    printf(" 1. Adicionar Filme\n");
    printf(" 2. Remover Filme\n");
    printf(" 3. Adicionar Sala\n");
    printf(" 4. Remover Sala\n");
    printf(" 5. Disponibilizar Sala em Horário\n");
    printf(" 6. Indisponibilizar Sala em Horário\n");
    printf(" 7. Adicionar Sessão\n");
    printf(" 8. Remover Sessão\n");
    printf(" 9. Comprar Ingresso\n");
    printf("--- Consultas e Visualização ---\n");
    printf(" 11. Listar Todos os Filmes Cadastrados\n");
    printf(" 12. Listar Todas as Salas Cadastradas\n");
    printf(" 13. Listar Filmes com Sessão (Em Cartaz)\n");
    printf(" 14. Visualizar Filmes por Horário\n");
    printf(" 15. Visualizar Horários por Filme\n");
    printf(" 16. Consultar Ingressos Comprados por Sessão\n");
    printf(" 17. Consultar Ingressos Disponíveis por Sessão\n");
    printf("--- Sistema e Testes ---\n");
    printf(" 18. Avançar Hora do Sistema\n");
    printf(" 19. Executar Cenário de Teste Completo\n");
    printf(" 20. Executar Cenário de Teste Completo de borda\n");
    printf("----------------------------------------------------------\n");
    printf(" 0. Sair\n");
    printf("----------------------------------------------------------\n");
    printf("Escolha uma opção: ");
}

int main()
{
    Cinema__INITIALISATION();
    printf("Bem-vindo! Sistema de Cinema inicializado.\n");
    int escolha;
    while (1)
    {
        exibir_menu();
        if (scanf("%d", &escolha) != 1)
        {
            printf("\n>>> ERRO: Entrada inválida. Por favor, digite um número.\n");
            while (getchar() != '\n')
                ;
            continue;
        }
        switch (escolha)
        {
        case 1:
            handle_adicionar_filme();
            break;
        case 2:
            handle_remover_filme();
            break;
        case 3:
            handle_adicionar_sala();
            break;
        case 4:
            handle_remover_sala();
            break;
        case 5:
            handle_disponibilizar_sala();
            break;
        case 6:
            handle_indisponibilizar_sala();
            break;
        case 7:
            handle_adicionar_sessao();
            break;
        case 8:
            handle_remover_sessao();
            break;
        case 9:
            handle_comprar_ingresso();
            break;
        case 11:
            handle_query_filmes();
            break;
        case 12:
            handle_query_salas();
            break;
        case 13:
            handle_visualizar_filmes_em_cartaz();
            break;
        case 14:
            handle_visualizar_filmes_por_horario();
            break;
        case 15:
            handle_visualizar_horarios_por_filme();
            break;
        case 16:
            handle_consultar_ingressos_comprados();
            break;
        case 17:
            handle_consultar_ingressos_disponiveis();
            break;
        case 18:
            handle_passar_hora();
            break;
        case 19:
            handle_executar_cenario_teste();
            break;
        case 20:
            handle_executar_cenario_teste_limites_e_bordas();
            break;
        case 0:
            printf("Encerrando o sistema. O multicine cinemas agradece sua visita! 👋\n");
            return 0;
        default:
            printf("\n>>> ERRO: Opção inválida! Tente novamente.\n");
            break;
        }
    }
    return 0;
}

// =============================================================================
//                       FUNÇÕES DE EXECUÇÃO (LÓGICA REAL)
// =============================================================================
bool executar_adicionar_filme(Cinema__FILME id_filme)
{
    bool pre_condicao_ok = false;
    Cinema__pre_adicionarFilme(id_filme, &pre_condicao_ok);
    if (pre_condicao_ok)
    {
        Cinema__AdicionarFilme(id_filme);
        printf("✅ SUCESSO: Filme %d adicionado.\n", id_filme);
        return true;
    }
    else
    {
        printf("❌ FALHA: Não foi possível adicionar o filme %d (já existe, é inválido ou limite atingido).\n", id_filme);
        return false;
    }
}

bool executar_remover_filme(Cinema__FILME id_filme)
{
    bool pre_condicao_ok = false;
    Cinema__pre_removerFilme(id_filme, &pre_condicao_ok);
    if (pre_condicao_ok)
    {
        Cinema__RemoverFilme(id_filme);
        printf("✅ SUCESSO: Filme %d removido.\n", id_filme);
        return true;
    }
    else
    {
        printf("❌ FALHA: Não foi possível remover o filme %d (não existe ou está em sessão).\n", id_filme);
        return false;
    }
}

bool executar_adicionar_sala(Cinema__SALA id_sala, int capacidade)
{
    bool pre_condicao_ok = false;
    Cinema__pre_adicionarSala(id_sala, capacidade, &pre_condicao_ok);
    if (pre_condicao_ok)
    {
        Cinema__AdicionarSala(id_sala, capacidade);
        printf("✅ SUCESSO: Sala %d com capacidade %d adicionada.\n", id_sala, capacidade);
        return true;
    }
    else
    {
        printf("❌ FALHA: Não foi possível adicionar a sala %d (já existe, capacidade inválida ou limite atingido).\n", id_sala);
        return false;
    }
}

bool executar_remover_sala(Cinema__SALA id_sala)
{
    bool pre_condicao_ok = false;
    Cinema__pre_removerSala(id_sala, &pre_condicao_ok);
    if (pre_condicao_ok)
    {
        Cinema__RemoverSala(id_sala);
        printf("✅ SUCESSO: Sala %d removida.\n", id_sala);
        return true;
    }
    else
    {
        printf("❌ FALHA: Não foi possível remover a sala %d (não existe ou tem horários disponíveis).\n", id_sala);
        return false;
    }
}

bool executar_disponibilizar_sala(Cinema__SALA id_sala, int horario)
{
    bool pre_condicao_ok = false;
    Cinema__pre_disponibilizarSalaEmHorarios(id_sala, horario, &pre_condicao_ok);
    if (pre_condicao_ok)
    {
        Cinema__DisponibilizarSalaEmHorarios(id_sala, horario);
        printf("✅ SUCESSO: Sala %d disponibilizada no horário %dh.\n", id_sala, horario);
        return true;
    }
    else
    {
        printf("❌ FALHA: Não foi possível disponibilizar a sala %d no horário %dh (sala não existe, horário já disponível ou limite de turnos atingido).\n", id_sala, horario);
        return false;
    }
}

bool executar_indisponibilizar_sala(Cinema__SALA id_sala, int horario)
{
    bool pre_condicao_ok = false;
    Cinema__pre_indisponibilizarSalaEmHorarios(id_sala, horario, &pre_condicao_ok);
    if (pre_condicao_ok)
    {
        Cinema__IndisponibilizarSalaEmHorarios(id_sala, horario);
        printf("✅ SUCESSO: Sala %d indisponibilizada no horário %dh.\n", id_sala, horario);
        return true;
    }
    else
    {
        printf("❌ FALHA: Não foi possível indisponibilizar a sala %d no horário %dh (sala/horário não disponível ou há uma sessão agendada).\n", id_sala, horario);
        return false;
    }
}

bool executar_adicionar_sessao(Cinema__SALA id_sala, int horario, Cinema__FILME id_filme)
{
    bool pre_condicao_ok = false;
    Cinema__pre_adicionarSessao(id_sala, horario, id_filme, &pre_condicao_ok);
    if (pre_condicao_ok)
    {
        Cinema__AdicionarSessao(id_sala, horario, id_filme);
        printf("✅ SUCESSO: Sessão adicionada (Filme %d, Sala %d, %dh).\n", id_filme, id_sala, horario);
        return true;
    }
    else
    {
        printf("❌ FALHA: Não foi possível adicionar a sessão (sala/horário indisponível, já ocupado ou filme já em exibição no mesmo horário).\n");
        return false;
    }
}

bool executar_remover_sessao(Cinema__SALA id_sala, int horario)
{
    bool pre_condicao_ok = false;
    Cinema__pre_removerSessao(id_sala, horario, &pre_condicao_ok);
    if (pre_condicao_ok)
    {
        Cinema__RemoverSessao(id_sala, horario);
        printf("✅ SUCESSO: Sessão da sala %d no horário %dh removida.\n", id_sala, horario);
        return true;
    }
    else
    {
        printf("❌ FALHA: Não foi possível remover a sessão (não existe ou possui ingressos vendidos).\n");
        return false;
    }
}

/**
 * ATUALIZADO: A mensagem de erro agora inclui a nova regra de negócio sobre meia-entrada.
 */
bool executar_comprar_ingresso(Cinema__FILME id_filme, int horario, Cinema__TIPO_INGRESSO tipo, int assento)
{
    bool pre_condicao_ok = false;
    Cinema__pre_comprarIngresso(id_filme, horario, tipo, assento, &pre_condicao_ok);
    if (pre_condicao_ok)
    {
        Cinema__ComprarIngresso(id_filme, horario, tipo, assento);
        printf("✅ SUCESSO: Compra realizada para o filme %d às %dh (Tipo: %s).\n", id_filme, horario, (tipo == Cinema__meia ? "Meia" : "Inteira"));
        return true;
    }
    else
    {
        printf("❌ FALHA: Não foi possível comprar ingresso (sessão não existe, horário já passou, ingressos esgotados ou limite de meia-entrada atingido).\n");
        return false;
    }
}

int executar_query_filmes()
{
    bool filmes_cadastrados[Cinema__limit_filmes + 1];
    Cinema__QueryFilmes(filmes_cadastrados);
    printf("\n--- 🎬 Filmes Atualmente Cadastrados 🎬 ---\n");
    int contador = 0;
    for (int i = 0; i <= Cinema__limit_filmes; i++)
    {
        if (filmes_cadastrados[i] == true)
        {
            printf(" -> Filme com ID: %d\n", i);
            contador++;
        }
    }
    if (contador == 0)
    {
        printf(" -> Nenhum filme cadastrado no momento.\n");
    }
    printf("-------------------------------------------\n");
    return contador;
}

int executar_query_salas()
{
    bool salas_cadastradas[Cinema__limit_salas + 1];
    Cinema__QuerySalas(salas_cadastradas);
    printf("\n--- 🏛️  Salas Cadastradas no Sistema 🏛️  ---\n");
    int contador = 0;
    for (int i = 0; i <= Cinema__limit_salas; i++)
    {
        if (salas_cadastradas[i] == true)
        {
            printf(" -> Sala com ID: %d\n", i);
            contador++;
        }
    }
    if (contador == 0)
    {
        printf(" -> Nenhuma sala cadastrada no momento.\n");
    }
    printf("-------------------------------------------\n");
    return contador;
}

int executar_visualizar_filmes_em_cartaz()
{
    bool filmes_com_sessao[Cinema__limit_filmes + 1];
    Cinema__visualizarFilmesEmCartaz(filmes_com_sessao);
    printf("\n--- 🍿 Filmes com Sessões Agendadas (Em Cartaz) 🍿 ---\n");
    int contador = 0;
    for (int i = 0; i <= Cinema__limit_filmes; i++)
    {
        if (filmes_com_sessao[i] == true)
        {
            printf(" -> Filme com ID: %d\n", i);
            contador++;
        }
    }
    if (contador == 0)
    {
        printf(" -> Nenhum filme com sessão agendada no momento.\n");
    }
    printf("-------------------------------------------------------\n");
    return contador;
}

int executar_visualizar_filmes_por_horario(int horario)
{
    bool filmes_encontrados[Cinema__limit_filmes + 1];
    Cinema__VisualizarFilmesPorHorario(horario, filmes_encontrados);
    printf("\n--- 🎞️  Filmes em Exibição às %dh 🎞️  ---\n", horario);
    int contador = 0;
    for (int i = 0; i <= Cinema__limit_filmes; i++)
    {
        if (filmes_encontrados[i] == true)
        {
            printf(" -> Filme com ID: %d\n", i);
            contador++;
        }
    }
    if (contador == 0)
    {
        printf(" -> Nenhum filme sendo exibido neste horário.\n");
    }
    printf("------------------------------------------\n");
    return contador;
}

int executar_visualizar_horarios_por_filme(Cinema__FILME id_filme)
{
    bool horarios_encontrados[Cinema__horario_max + 1];
    Cinema__VisualizarHorariosPorFilme(id_filme, horarios_encontrados);
    printf("\n--- 🕒 Horários para o Filme %d 🕒 ---\n", id_filme);
    int contador = 0;
    for (int i = 0; i <= Cinema__horario_max; i++)
    {
        if (horarios_encontrados[i] == true)
        {
            printf(" -> Sessão às: %dh\n", i);
            contador++;
        }
    }
    if (contador == 0)
    {
        printf(" -> Nenhuma sessão encontrada para este filme.\n");
    }
    printf("---------------------------------------\n");
    return contador;
}

void executar_passar_hora()
{
    Cinema__Passar_Hora();
    int hora_atual = -1;
    Cinema__query_Passar_Hora(&hora_atual);
    printf("✅ SUCESSO: Hora do sistema avançada para %dh.\n", hora_atual);
}

int executar_consultar_ingressos_comprados(Cinema__SALA id_sala, int horario)
{
    bool pre_condicao_ok = false;
    Cinema__pre_consultarIngressosCompradosPorSessao(id_sala, horario, &pre_condicao_ok);
    if (pre_condicao_ok)
    {
        int qtd = -1;
        Cinema__ConsultarIngressosCompradosPorSessao(id_sala, horario, &qtd);
        printf("📊 INFO: %d ingressos comprados para a sessão na sala %d às %dh.\n", qtd, id_sala, horario);
        return qtd;
    }
    else
    {
        printf("❌ FALHA: Não foi possível consultar. Sessão na sala %d às %dh não existe.\n", id_sala, horario);
        return -1;
    }
}

int executar_consultar_ingressos_disponiveis(Cinema__SALA id_sala, int horario)
{
    bool pre_condicao_ok = false;
    Cinema__pre_consultarIngressosDisponiveisPorSessao(id_sala, horario, &pre_condicao_ok);
    if (pre_condicao_ok)
    {
        int qtd = -1;
        Cinema__ConsultarIngressosDisponiveisPorSessao(id_sala, horario, &qtd);
        printf("📊 INFO: %d ingressos disponíveis para a sessão na sala %d às %dh.\n", qtd, id_sala, horario);
        return qtd;
    }
    else
    {
        printf("❌ FALHA: Não foi possível consultar. Sessão na sala %d às %dh não existe.\n", id_sala, horario);
        return -1;
    }
}

// =============================================================================
//                 FUNÇÕES HANDLE (INTERFACE COM USUÁRIO)
// =============================================================================
void handle_adicionar_filme()
{
    Cinema__FILME id_filme;
    printf("-> Digite o ID do filme para adicionar (1 a %d): ", Cinema__limit_filmes);
    scanf("%d", &id_filme);
    executar_adicionar_filme(id_filme);
}

void handle_remover_filme()
{
    Cinema__FILME id_filme;
    printf("-> Digite o ID do filme para remover (1 a %d): ", Cinema__limit_filmes);
    scanf("%d", &id_filme);
    executar_remover_filme(id_filme);
}

void handle_adicionar_sala()
{
    Cinema__SALA id_sala;
    int capacidade;
    printf("-> Digite o ID da sala para adicionar (0 a %d): ", Cinema__limit_salas);
    scanf("%d", &id_sala);
    printf("-> Digite a capacidade da sala (1 a %d): ", Cinema__limit_capacidade);
    scanf("%d", &capacidade);
    executar_adicionar_sala(id_sala, capacidade);
}

void handle_remover_sala()
{
    Cinema__SALA id_sala;
    printf("-> Digite o ID da sala para remover (0 a %d): ", Cinema__limit_salas);
    scanf("%d", &id_sala);
    executar_remover_sala(id_sala);
}

void handle_disponibilizar_sala()
{
    Cinema__SALA id_sala;
    int horario;
    printf("-> Digite o ID da sala: ");
    scanf("%d", &id_sala);
    printf("-> Digite o horário a ser disponibilizado (0 a %d): ", Cinema__horario_max);
    scanf("%d", &horario);
    executar_disponibilizar_sala(id_sala, horario);
}

void handle_indisponibilizar_sala()
{
    Cinema__SALA id_sala;
    int horario;
    printf("-> Digite o ID da sala: ");
    scanf("%d", &id_sala);
    printf("-> Digite o horário a ser indisponibilizado (0 a %d): ", Cinema__horario_max);
    scanf("%d", &horario);
    executar_indisponibilizar_sala(id_sala, horario);
}

void handle_adicionar_sessao()
{
    Cinema__SALA id_sala;
    int horario;
    Cinema__FILME id_filme;
    printf("-> Digite o ID da sala: ");
    scanf("%d", &id_sala);
    printf("-> Digite o horário da sessão (0 a %d): ", Cinema__horario_max);
    scanf("%d", &horario);
    printf("-> Digite o ID do filme: ");
    scanf("%d", &id_filme);
    executar_adicionar_sessao(id_sala, horario, id_filme);
}

void handle_remover_sessao()
{
    Cinema__SALA id_sala;
    int horario;
    printf("-> Digite o ID da sala: ");
    scanf("%d", &id_sala);
    printf("-> Digite o horário da sessão a ser removida: ");
    scanf("%d", &horario);
    executar_remover_sessao(id_sala, horario);
}

void handle_comprar_ingresso()
{
    Cinema__FILME id_filme;
    int horario, tipo_int;
    Cinema__TIPO_INGRESSO tipo_ingresso;
    printf("-> Digite o ID do filme: ");
    scanf("%d", &id_filme);
    printf("-> Digite o horário da sessão: ");
    scanf("%d", &horario);
    printf("-> Digite o tipo de ingresso (0 para Meia, 1 para Inteira): ");
    scanf("%d", &tipo_int);

    int assento_dummy = 0;
    if (tipo_int == 0)
        tipo_ingresso = Cinema__meia;
    else if (tipo_int == 1)
        tipo_ingresso = Cinema__inteira;
    else
    {
        printf("❌ FALHA: Tipo de ingresso inválido.\n");
        return;
    }
    executar_comprar_ingresso(id_filme, horario, tipo_ingresso, assento_dummy);
}

void handle_query_filmes() { executar_query_filmes(); }
void handle_query_salas() { executar_query_salas(); }
void handle_visualizar_filmes_em_cartaz() { executar_visualizar_filmes_em_cartaz(); }

void handle_visualizar_filmes_por_horario()
{
    int horario;
    printf("-> Digite o horário para consultar (0 a %d): ", Cinema__horario_max);
    scanf("%d", &horario);
    executar_visualizar_filmes_por_horario(horario);
}

void handle_visualizar_horarios_por_filme()
{
    Cinema__FILME id_filme;
    printf("-> Digite o ID do filme para consultar (1 a %d): ", Cinema__limit_filmes);
    scanf("%d", &id_filme);
    executar_visualizar_horarios_por_filme(id_filme);
}

void handle_passar_hora()
{
    executar_passar_hora();
}

void handle_consultar_ingressos_comprados()
{
    Cinema__SALA id_sala;
    int horario;
    printf("-> Digite o ID da sala: ");
    scanf("%d", &id_sala);
    printf("-> Digite o horário da sessão: ");
    scanf("%d", &horario);
    executar_consultar_ingressos_comprados(id_sala, horario);
}

void handle_consultar_ingressos_disponiveis()
{
    Cinema__SALA id_sala;
    int horario;
    printf("-> Digite o ID da sala: ");
    scanf("%d", &id_sala);
    printf("-> Digite o horário da sessão: ");
    scanf("%d", &horario);
    executar_consultar_ingressos_disponiveis(id_sala, horario);
}

// =============================================================================
//           FUNÇÃO DE TESTE AUTOMÁTICO (COM VERIFICAÇÕES CRUZADAS)
// =============================================================================

/**
 * ATUALIZADO: O cenário de teste foi expandido para validar a nova regra de limite de meia-entrada.
 * - ETAPA 4: Vende ingressos até atingir o limite de 50% de meia-entrada.
 * - ETAPA 5: Tenta comprar um ingresso de meia-entrada a mais (deve falhar) e um de inteira (deve passar).
 * - ETAPAS subsequentes renumeradas e ajustadas.
 */
void handle_executar_cenario_teste()
{
    printf("\n\n--- 🤖 INICIANDO CENÁRIO DE TESTE AUTOMÁTICO COMPLETO 🤖 ---\n");
    printf("--- Este teste valida tanto os caminhos felizes quanto os de falha. ---\n");

    // Zera o estado para um teste limpo
    Cinema__INITIALISATION();

    // Parâmetros do Teste
    Cinema__FILME id_filme_teste = 2;
    Cinema__FILME id_filme_teste2 = 4;
    Cinema__SALA id_sala_teste = 1;
    Cinema__SALA id_sala_teste2 = 2;
    int capacidade_teste = 10; // Limite de meia-entrada será 5
    int horario_teste = 18;
    int horario_teste2 = 20;

    // ETAPA 1: SETUP
    printf("\n--- [ETAPA 1: AÇÃO] Adicionando Itens e Agendando Sessões ---\n");
    if (!executar_adicionar_filme(id_filme_teste) ||
        !executar_adicionar_filme(id_filme_teste2) ||
        !executar_adicionar_sala(id_sala_teste, capacidade_teste) ||
        !executar_adicionar_sala(id_sala_teste2, capacidade_teste) ||
        !executar_disponibilizar_sala(id_sala_teste, horario_teste) ||
        !executar_disponibilizar_sala(id_sala_teste2, horario_teste2) ||
        !executar_adicionar_sessao(id_sala_teste, horario_teste, id_filme_teste) ||
        !executar_adicionar_sessao(id_sala_teste2, horario_teste2, id_filme_teste2))
    {
        printf("🔴 TESTE FALHOU: Erro na etapa inicial de setup. Abortando.\n");
        return;
    }

    // ETAPA 2: VERIFICAÇÕES PÓS-AGENDAMENTO
    printf("\n--- [ETAPA 2: VERIFICAÇÃO] Checando as sessões criadas ---\n");
    if (executar_visualizar_filmes_em_cartaz() != 2)
    {
        printf("🔴 TESTE FALHOU: Contagem de filmes em cartaz deveria ser 2.\n");
        return;
    }
    printf("✅ SUCESSO: Verificações de sessão passaram.\n");

    // ETAPA 3: TESTES DE FALHA (Lógica de Negócio)
    printf("\n--- [ETAPA 3: TESTE DE FALHA] Verificando impedimentos de operações inválidas ---\n");
    if (executar_remover_filme(id_filme_teste))
    {
        printf("🔴 LÓGICA DO SISTEMA FALHOU: Permitiu remover filme com sessão ativa!\n");
        return;
    }
    else
        printf("✅ SUCESSO ESPERADO: Sistema impediu a remoção do filme em cartaz.\n");
    if (executar_remover_sala(id_sala_teste))
    {
        printf("🔴 LÓGICA DO SISTEMA FALHOU: Permitiu remover sala com horário disponibilizado!\n");
        return;
    }
    else
        printf("✅ SUCESSO ESPERADO: Sistema impediu a remoção da sala com horário.\n");

    // ETAPA 4: VENDAS ATÉ O LIMITE DA MEIA-ENTRADA
    printf("\n--- [ETAPA 4: AÇÃO] Vendendo ingressos de meia-entrada até o limite de 50%% ---\n");
    int limite_meia = capacidade_teste / 2;
    for (int i = 0; i < limite_meia; i++)
    {
        if (!executar_comprar_ingresso(id_filme_teste, horario_teste, Cinema__meia, 0))
        {
            printf("🔴 TESTE FALHOU: Erro ao vender o %dº ingresso de meia-entrada. Abortando.\n", i + 1);
            return;
        }
    }
    if (executar_consultar_ingressos_comprados(id_sala_teste, horario_teste) != limite_meia)
    {
        printf("🔴 TESTE FALHOU: A contagem de ingressos comprados deveria ser %d.\n", limite_meia);
        return;
    }
    printf("✅ SUCESSO: %d ingressos de meia-entrada vendidos.\n", limite_meia);

    // ETAPA 5: TESTE DE FALHA E SUCESSO NA VENDA APÓS LIMITE
    printf("\n--- [ETAPA 5: TESTE DE FALHA] Tentando comprar além do limite de meia-entrada ---\n");
    if (executar_comprar_ingresso(id_filme_teste, horario_teste, Cinema__meia, 0))
    {
        printf("🔴 LÓGICA DO SISTEMA FALHOU: Permitiu comprar meia-entrada além do limite!\n");
        return;
    }
    else
    {
        printf("✅ SUCESSO ESPERADO: Sistema impediu a compra do %dº ingresso de meia-entrada.\n", limite_meia + 1);
    }
    printf("--- [ETAPA 5.1: TESTE DE SUCESSO] Comprando ingresso de inteira após limite de meia ---\n");
    if (!executar_comprar_ingresso(id_filme_teste, horario_teste, Cinema__inteira, 0))
    {
        printf("🔴 LÓGICA DO SISTEMA FALHOU: Não permitiu comprar ingresso de inteira!\n");
        return;
    }
    else
    {
        printf("✅ SUCESSO ESPERADO: Sistema permitiu a compra de ingresso de inteira.\n");
    }

    // ETAPA 6: VERIFICAÇÃO PÓS-VENDAS
    printf("\n--- [ETAPA 6: VERIFICAÇÃO] Checando ingressos após vendas ---\n");
    int total_vendido = limite_meia + 1;
    if (executar_consultar_ingressos_comprados(id_sala_teste, horario_teste) != total_vendido)
    {
        printf("🔴 TESTE FALHOU: A contagem de ingressos comprados deveria ser %d.\n", total_vendido);
        return;
    }
    if (executar_consultar_ingressos_disponiveis(id_sala_teste, horario_teste) != capacidade_teste - total_vendido)
    {
        printf("🔴 TESTE FALHOU: A contagem de ingressos disponíveis deveria ser %d.\n", capacidade_teste - total_vendido);
        return;
    }
    printf("✅ SUCESSO: Vendas e consultas de ingressos funcionaram como esperado.\n");

    // ETAPA 7: TESTE DE AVANÇO DE HORA
    printf("\n--- [ETAPA 7: TESTE DE FALHA] Avançando a hora para invalidar compras ---\n");
    for (int i = 0; i <= horario_teste; i++)
    {
        executar_passar_hora();
    }
    if (executar_comprar_ingresso(id_filme_teste, horario_teste, Cinema__inteira, 0))
    {
        printf("🔴 LÓGICA DO SISTEMA FALHOU: Permitiu comprar ingresso para sessão que já passou!\n");
        return;
    }
    else
    {
        printf("✅ SUCESSO ESPERADO: Sistema impediu a compra para sessão passada.\n");
    }

    // ETAPA 8: LIMPEZA E VERIFICAÇÕES FINAIS
    printf("\n--- [ETAPA 8: AÇÃO] Limpando o ambiente de teste ---\n");
    if (executar_remover_sessao(id_sala_teste, horario_teste))
    {
        printf("🔴 LÓGICA DO SISTEMA FALHOU: Permitiu remover sessão com ingressos vendidos!\n");
        return;
    }
    else
    {
        printf("✅ SUCESSO ESPERADO: Sistema impediu a remoção de sessão com ingressos.\n");
    }
    if (!executar_remover_sessao(id_sala_teste2, horario_teste2) ||
        !executar_indisponibilizar_sala(id_sala_teste2, horario_teste2) ||
        !executar_remover_sala(id_sala_teste2) ||
        !executar_remover_filme(id_filme_teste2))
    {
        printf("🔴 TESTE FALHOU: Erro na limpeza final de sala e filme. Abortando.\n");
        return;
    }

    // ETAPA 9: VERIFICAÇÃO PÓS-LIMPEZA
    printf("\n--- [ETAPA 9: VERIFICAÇÃO FINAL] Checando se o sistema está parcialmente limpo ---\n");
    if (executar_query_filmes() != 1 || executar_query_salas() != 1)
    {
        printf("🔴 TESTE FALHOU: O número de filmes ou salas remanescentes está incorreto.\n");
        return;
    }
    if (executar_visualizar_filmes_em_cartaz() != 1)
    {
        printf("🔴 TESTE FALHOU: Ainda há mais de uma sessão em cartaz após a limpeza.\n");
        return;
    }
    printf("\n\n--- ✨ CENÁRIO DE TESTE CONCLUÍDO COM SUCESSO! (Caminhos felizes e infelizes validados) ✨ ---\n\n");
}
/**
 * ATUALIZADO: Cenário de teste exaustivo que valida regras de negócio e limites físicos do sistema.
 * - Adiciona testes para os limites de quantidade de filmes e salas (ex: Cinema__limit_salas).
 * - Adiciona testes para o limite de turnos (sessões) por sala (Cinema__limit_turnos).
 * - Mantém todos os testes de borda anteriores, como lotação esgotada e remoção de itens em uso.
 */
void handle_executar_cenario_teste_limites_e_bordas()
{
    printf("\n\n--- 🤖 INICIANDO CENÁRIO DE TESTE DE LIMITES E BORDAS 🤖 ---\n");
    printf("--- Valida regras de negócio e limites físicos definidos no .h ---\n");

    // Zera o estado para um teste limpo
    Cinema__INITIALISATION();

    // --- Parâmetros do Teste ---
    Cinema__FILME id_filme_principal = 1;
    Cinema__SALA id_sala_principal = 1;
    int capacidade_padrao = 10; // Cinema__limit_capacidade
    int horario_principal = 18;
    int horario_secundario = 21;
    int horario_terceiro = 16;


    // --- ETAPA 1: TESTES DE ESGOTAMENTO DE RECURSOS (LIMITES FÍSICOS) ---
    printf("\n--- [ETAPA 1: TESTE] Validando limites de criação (Máx Salas e Filmes) ---\n");

    // Teste: Atingir o limite de salas e tentar ultrapassar
    printf("--- [ETAPA 1.1] Adicionando %d salas para atingir o limite...\n", Cinema__limit_salas);
    for (int i = 0; i < Cinema__limit_salas; i++) {
        // Usar IDs diferentes para não conflitar. Ex: 10, 11, 12, 13
        if (!executar_adicionar_sala(0 + i, capacidade_padrao)) {
             printf("🔴 TESTE FALHOU: Não foi possível adicionar a %dª sala.\n", i + 1);
             return;
        }
    }
    if (executar_adicionar_sala(99, capacidade_padrao)) { // Tenta adicionar a 5ª sala
        printf("🔴 LÓGICA FALHOU: Permitiu adicionar sala além do limite de %d!\n", Cinema__limit_salas);
        return;
    }
    printf("✅ SUCESSO ESPERADO: Sistema impediu criação de sala além do limite.\n");

    // Teste: Atingir o limite de filmes e tentar ultrapassar
    printf("--- [ETAPA 1.2] Adicionando %d filmes para atingir o limite...\n", Cinema__limit_filmes);
    for (int i = 0; i < Cinema__limit_filmes; i++) {
        // Usar IDs diferentes. Ex: 100, 101, ...
        if (!executar_adicionar_filme(1 + i)) {
             printf("🔴 TESTE FALHOU: Não foi possível adicionar o %dº filme.\n", i + 1);
             return;
        }
    }
    if (executar_adicionar_filme(999)) { // Tenta adicionar o 11º filme
        printf("🔴 LÓGICA FALHOU: Permitiu adicionar filme além do limite de %d!\n", Cinema__limit_filmes);
        return;
    }
    printf("✅ SUCESSO ESPERADO: Sistema impediu criação de filme além do limite.\n");

    // Reinicia o estado para os testes de lógica não serem afetados pelo esgotamento
    printf("--- [INFO] Reiniciando estado do cinema para próximos testes lógicos ---\n");
    Cinema__INITIALISATION();


    // --- ETAPA 2: TESTES DE BORDA NO AGENDAMENTO (LIMITES DE TURNO E HORÁRIO) ---
    printf("\n--- [ETAPA 2: TESTE] Validando limites de agendamento (Turnos e Horários) ---\n");
    executar_adicionar_sala(id_sala_principal, capacidade_padrao);
    executar_adicionar_filme(id_filme_principal);

    // Teste: Agendar nos turnos permitidos
    printf("--- [ETAPA 2.1] Ocupando os %d turnos permitidos da sala %d...\n", Cinema__limit_turnos, id_sala_principal);
    if (!executar_disponibilizar_sala(id_sala_principal, horario_principal) ||
        !executar_disponibilizar_sala(id_sala_principal, horario_secundario)) {
        printf("🔴 TESTE FALHOU: Não foi possível agendar os turnos permitidos.\n");
        return;
    }
    printf("✅ SUCESSO: Os %d turnos da sala foram preenchidos.\n", Cinema__limit_turnos);

    // Teste: Tentar agendar um turno extra na mesma sala
    if (executar_disponibilizar_sala(id_sala_principal, horario_terceiro)) {
        printf("🔴 LÓGICA FALHOU: Permitiu agendar um 3º turno na mesma sala (limite é %d)!\n", Cinema__limit_turnos);
        return;
    }
    printf("✅ SUCESSO ESPERADO: Sistema impediu agendamento de turno extra na sala.\n");

    // Teste: Tentar agendar em horário inválido (máximo e negativo)
    if (executar_disponibilizar_sala(id_sala_principal, Cinema__horario_max) || executar_disponibilizar_sala(id_sala_principal, -1)) {
        printf("🔴 LÓGICA FALHOU: Permitiu agendar em horário inválido (>= %d ou < 0)!\n", Cinema__horario_max);
        return;
    }
    printf("✅ SUCESSO ESPERADO: Sistema impediu agendamento em horários inválidos.\n");


    // --- ETAPA 3: TESTES DE BORDA NA VENDA DE INGRESSOS (ESGOTAMENTO) ---
    printf("\n--- [ETAPA 3: TESTE] Validando venda de ingressos até a lotação esgotar ---\n");
    executar_adicionar_sessao(id_sala_principal, horario_principal, id_filme_principal);

    printf("--- [ETAPA 3.1] Vendendo ingressos até o limite da sala (%d)...\n", capacidade_padrao);
    // Vende todas as meias (5)
    for (int i = 0; i < (capacidade_padrao / 2); i++) {
        executar_comprar_ingresso(id_filme_principal, horario_principal, Cinema__meia, 0);
    }
    // Vende todas as inteiras (5)
    for (int i = 0; i < (capacidade_padrao / 2); i++) {
        executar_comprar_ingresso(id_filme_principal, horario_principal, Cinema__inteira, 0);
    }

    if (executar_consultar_ingressos_disponiveis(id_sala_principal, horario_principal) != 0) {
        printf("🔴 TESTE FALHOU: Sala deveria estar com 0 ingressos disponíveis!\n");
        return;
    }
    printf("✅ SUCESSO: Sala consta como esgotada.\n");

    if (executar_comprar_ingresso(id_filme_principal, horario_principal, Cinema__inteira, 0)) {
        printf("🔴 LÓGICA FALHOU: Permitiu comprar ingresso para sala lotada!\n");
        return;
    }
    printf("✅ SUCESSO ESPERADO: Sistema impediu compra para sala lotada.\n");

    // --- ETAPA 4: TESTES DE INTEGRIDADE E REMOÇÃO ---
    printf("\n--- [ETAPA 4: TESTE] Validando integridade na remoção de itens em uso ---\n");
    if (executar_remover_sessao(id_sala_principal, horario_principal)) {
        printf("🔴 LÓGICA FALHOU: Permitiu remover sessão com ingressos vendidos!\n");
        return;
    }
    printf("✅ SUCESSO ESPERADO: Sistema impediu remoção de sessão com ingressos.\n");


    printf("\n\n--- ✨ CENÁRIO COMPLETO DE LIMITES E BORDAS CONCLUÍDO COM SUCESSO! ✨ ---\n\n");
}