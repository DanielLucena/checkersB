#include <stdio.h>
#include <stdlib.h>
#include "Cinema_i.c" // Inclui o seu header exato

// Protótipos das funções executoras (lógica principal)
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

// Protótipos das funções "handle" (interface com o usuário)
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
void handle_query_filmes();
void handle_query_salas();
void handle_visualizar_filmes_em_cartaz();
void handle_visualizar_filmes_por_horario();
void handle_visualizar_horarios_por_filme();
void handle_executar_cenario_teste();

void exibir_menu()
{
    printf("\n--- 🎟️ Sistema de Gerenciamento de Cinema 🎟️ ---\n");
    printf("--- Gerenciamento ---\n");
    printf(" 1. Adicionar Filme\n");
    printf(" 2. Remover Filme\n");
    printf(" 3. Adicionar Sala\n");
    printf(" 4. Remover Sala\n");
    printf(" 5. Disponibilizar Sala em Horário\n");
    printf(" 6. Indisponibilizar Sala em Horário\n");
    printf(" 7. Adicionar Sessão\n");
    printf(" 8. Remover Sessão\n");
    printf(" 9. Comprar Ingresso (por assento)\n"); // Descrição atualizada
    printf("--- Consultas e Visualização ---\n");
    printf(" 11. Listar Todos os Filmes Cadastrados\n");
    printf(" 12. Listar Todas as Salas Cadastradas\n");
    printf(" 13. Listar Filmes com Sessão (Em Cartaz)\n");
    printf(" 14. Visualizar Filmes por Horário\n");
    printf(" 15. Visualizar Horários por Filme\n");
    printf("--- Testes ---\n");
    printf(" 10. Executar Cenário de Teste Completo\n");
    printf("------------------------------------------------\n");
    printf(" 0. Sair\n");
    printf("------------------------------------------------\n");
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
        case 10:
            handle_executar_cenario_teste();
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
        case 0:
            printf("Encerrando o sistema. Até logo! 👋\n");
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
// =============================================================================
//          FUNÇÕES DE EXECUÇÃO (LÓGICA REAL COM VALORES DE RETORNO)
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
        printf("❌ FALHA: Não foi possível adicionar o filme %d.\n", id_filme);
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
        printf("❌ FALHA: Não foi possível adicionar a sala %d.\n", id_sala);
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
        printf("❌ FALHA: Não foi possível adicionar a sessão.\n");
        return false;
    }
}

bool executar_comprar_ingresso(Cinema__FILME id_filme, int horario, Cinema__TIPO_INGRESSO tipo, int assento)
{
    bool pre_condicao_ok = false;
    Cinema__pre_comprarIngresso(id_filme, horario, tipo, &pre_condicao_ok);
    if (pre_condicao_ok)
    {
        Cinema__ComprarIngresso(id_filme, horario, tipo, assento);
        printf("✅ SUCESSO: Compra realizada para o assento %d.\n", assento);
        return true;
    }
    else
    {
        printf("❌ FALHA: Não foi possível comprar ingresso para o assento %d.\n", assento);
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
        printf("❌ FALHA: Não foi possível remover o filme %d.\n", id_filme);
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
        printf("❌ FALHA: Não foi possível remover a sala %d.\n", id_sala);
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
        printf("❌ FALHA: Não foi possível disponibilizar a sala %d no horário %dh.\n", id_sala, horario);
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
        printf("❌ FALHA: Não foi possível indisponibilizar a sala %d no horário %dh.\n", id_sala, horario);
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
        printf("❌ FALHA: Não foi possível remover a sessão da sala %d no horário %dh.\n", id_sala, horario);
        return false;
    }
}

int executar_query_salas()
{
    bool salas_cadastradas[Cinema__limit_salas + 1];
    Cinema__QuerySalas(salas_cadastradas);
    printf("\n--- 🏛️ Salas Cadastradas no Sistema 🏛️ ---\n");
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

int executar_query_filmes()
{
    bool filmes_cadastrados[Cinema__limit_filmes];
    Cinema__QueryFilmes(filmes_cadastrados);
    printf("\n--- 🎬 Filmes Atualmente Cadastrados 🎬 ---\n");
    int contador = 0;
    for (int i = 0; i < Cinema__limit_filmes; i++)
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
    // Para evitar overflow, dimensionamos o array com +1, conforme a lógica da função original
    bool filmes_encontrados[Cinema__limit_filmes + 1];
    Cinema__VisualizarFilmesPorHorario(horario, filmes_encontrados);

    printf("\n--- 🎞️ Filmes em Exibição às %dh 🎞️ ---\n", horario);
    int contador = 0;
    // O loop original vai até <= limit_filmes, então replicamos
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
    // Dimensionamos o array com +1 para corresponder à lógica da função original
    bool horarios_encontrados[Cinema__horario_max + 1];
    Cinema__VisualizarHorariosPorFilme(id_filme, horarios_encontrados);

    printf("\n--- 🕒 Horários para o Filme %d 🕒 ---\n", id_filme);
    int contador = 0;
    // O loop original vai até <= horario_max
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

// =============================================================================
//                 FUNÇÕES HANDLE (INTERFACE COM USUÁRIO - SCANF)
// =============================================================================

void handle_adicionar_filme()
{
    Cinema__FILME id_filme;
    printf("-> Digite o ID do filme para adicionar (0 a %d): ", Cinema__limit_filmes - 1);
    scanf("%d", &id_filme);
    executar_adicionar_filme(id_filme);
}

void handle_remover_filme()
{
    Cinema__FILME id_filme;
    printf("-> Digite o ID do filme para remover (0 a %d): ", Cinema__limit_filmes - 1);
    scanf("%d", &id_filme);
    executar_remover_filme(id_filme);
}

void handle_adicionar_sala()
{
    Cinema__SALA id_sala;
    int capacidade;
    printf("-> Digite o ID da sala para adicionar (0 a %d): ", Cinema__limit_salas - 1);
    scanf("%d", &id_sala);
    printf("-> Digite a capacidade da sala (1 a %d): ", Cinema__limit_capacidade);
    scanf("%d", &capacidade);
    executar_adicionar_sala(id_sala, capacidade);
}

void handle_remover_sala()
{
    Cinema__SALA id_sala;
    printf("-> Digite o ID da sala para remover (0 a %d): ", Cinema__limit_salas - 1);
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
    printf("-> Digite o horário da sessão: ");
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
    int horario, tipo_int, assento;
    Cinema__TIPO_INGRESSO tipo_ingresso;

    printf("-> Digite o ID do filme: ");
    scanf("%d", &id_filme);
    printf("-> Digite o horário da sessão: ");
    scanf("%d", &horario);
    printf("-> Digite o tipo de ingresso (0 para Meia, 1 para Inteira): ");
    scanf("%d", &tipo_int);
    printf("-> Digite o número do assento: ");
    scanf("%d", &assento);

    if (tipo_int == 0)
        tipo_ingresso = Cinema__meia;
    else if (tipo_int == 1)
        tipo_ingresso = Cinema__inteira;
    else
    {
        printf("❌ FALHA: Tipo de ingresso inválido.\n");
        return;
    }
    executar_comprar_ingresso(id_filme, horario, tipo_ingresso, assento);
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
    printf("-> Digite o ID do filme para consultar (0 a %d): ", Cinema__limit_filmes - 1);
    scanf("%d", &id_filme);
    executar_visualizar_horarios_por_filme(id_filme);
}

// =============================================================================
//           FUNÇÃO DE TESTE AUTOMÁTICO (COM VERIFICAÇÕES CRUZADAS)
// =============================================================================
void handle_executar_cenario_teste()
{
    printf("\n\n--- 🤖 INICIANDO CENÁRIO DE TESTE AUTOMÁTICO COMPLETO 🤖 ---\n");
    printf("--- Este teste valida tanto os caminhos felizes quanto os de falha. ---\n");

    // Parâmetros do Teste
    Cinema__FILME id_filme_teste = 2;
    Cinema__SALA id_sala_teste = 1;
    int capacidade_teste = 10;
    int horario_teste = 18;
    int assento_teste_1 = 1;
    int assento_teste_2 = 2;

    // ETAPA 1 e 2: SETUP E AGENDAMENTO
    printf("\n--- [AÇÃO] Adicionando Itens e Agendando Sessão ---\n");
    if (!executar_adicionar_filme(id_filme_teste) ||
        !executar_adicionar_sala(id_sala_teste, capacidade_teste) ||
        !executar_disponibilizar_sala(id_sala_teste, horario_teste) ||
        !executar_adicionar_sessao(id_sala_teste, horario_teste, id_filme_teste))
    {
        printf("🔴 TESTE FALHOU: Erro na etapa inicial de setup. Abortando.\n");
        return;
    }

    // ETAPA 3: VERIFICAÇÕES CRUZADAS PÓS-AGENDAMENTO
    printf("\n--- [VERIFICAÇÃO] Checando a sessão criada com múltiplas consultas ---\n");
    if (executar_visualizar_filmes_em_cartaz() != 1)
    {
        printf("🔴 TESTE FALHOU: A contagem de filmes em cartaz deveria ser 1.\n");
        return;
    }
    // NOVA VERIFICAÇÃO: Dado o horário, devemos encontrar 1 filme.
    if (executar_visualizar_filmes_por_horario(horario_teste) != 1)
    {
        printf("🔴 TESTE FALHOU: A consulta por horário deveria retornar 1 filme.\n");
        return;
    }
    // NOVA VERIFICAÇÃO: Dado o filme, devemos encontrar 1 horário.
    if (executar_visualizar_horarios_por_filme(id_filme_teste) != 1)
    {
        printf("🔴 TESTE FALHOU: A consulta por filme deveria retornar 1 horário.\n");
        return;
    }
    printf("✅ SUCESSO: Todas as verificações de sessão passaram.\n");

    // ETAPA 4: TESTES DE FALHA
    printf("\n\n--- [TESTES DE FALHA] Verificando se o sistema impede operações inválidas ---\n");
    if (executar_remover_filme(id_filme_teste))
    {
        printf("🔴 LÓGICA DO SISTEMA FALHOU: Permitiu remover um filme com sessão ativa!\n");
        return;
    }
    else
    {
        printf("✅ SUCESSO ESPERADO: O sistema corretamente impediu a remoção do filme.\n");
    }
    // ... (outros testes de falha)

    // ETAPA 5: VENDAS
    printf("\n\n--- [AÇÃO] Vendendo Ingressos (retornando ao caminho feliz) ---\n");
    if (!executar_comprar_ingresso(id_filme_teste, horario_teste, Cinema__meia, assento_teste_1) ||
        !executar_comprar_ingresso(id_filme_teste, horario_teste, Cinema__inteira, assento_teste_2))
    {
        printf("🔴 TESTE FALHOU: Erro ao vender ingressos. Abortando.\n");
        return;
    }

    // ETAPA 6: LIMPEZA
    printf("\n--- [AÇÃO] Removendo a Sessão e Itens ---\n");
    if (!executar_remover_sessao(id_sala_teste, horario_teste))
    {
        printf("🔴 TESTE FALHOU: Não foi possível remover a sessão. Abortando.\n");
        return;
    }

    // ETAPA 7: VERIFICAÇÃO PÓS-LIMPEZA DA SESSÃO
    printf("\n--- [VERIFICAÇÃO] Checando se a sessão foi removida ---\n");
    if (executar_visualizar_filmes_em_cartaz() != 0)
    {
        printf("🔴 TESTE FALHOU: A contagem de filmes em cartaz deveria ser 0.\n");
        return;
    }
    // NOVA VERIFICAÇÃO: A consulta agora deve retornar 0.
    if (executar_visualizar_filmes_por_horario(horario_teste) != 0)
    {
        printf("🔴 TESTE FALHOU: A consulta por horário deveria retornar 0 filmes.\n");
        return;
    }
    // NOVA VERIFICAÇÃO: A consulta agora deve retornar 0.
    if (executar_visualizar_horarios_por_filme(id_filme_teste) != 0)
    {
        printf("🔴 TESTE FALHOU: A consulta por filme deveria retornar 0 horários.\n");
        return;
    }
    printf("✅ SUCESSO: Todas as verificações de remoção de sessão passaram.\n");

    // Continua a limpeza final
    if (!executar_indisponibilizar_sala(id_sala_teste, horario_teste) ||
        !executar_remover_sala(id_sala_teste) ||
        !executar_remover_filme(id_filme_teste))
    {
        printf("🔴 TESTE FALHOU: Erro na limpeza final de sala e filme. Abortando.\n");
        return;
    }

    // ETAPA 8: VERIFICAÇÃO FINAL
    printf("\n--- [VERIFICAÇÃO FINAL] Checando se o sistema está limpo ---\n");
    if (executar_query_filmes() != 0 || executar_query_salas() != 0)
    {
        printf("🔴 TESTE FALHOU: O sistema não está limpo no final do teste.\n");
        return;
    }

    printf("\n\n--- ✨ CENÁRIO DE TESTE CONCLUÍDO COM SUCESSO! (Caminhos felizes e infelizes validados) ✨ ---\n\n");
}
