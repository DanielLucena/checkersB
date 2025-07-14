// main.c
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

// ... (todas as outras funções de remoção e modificação seguiriam o padrão 'bool')
// Exemplo:
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
    // O loop em sua função vai até 'limit_salas', então iteramos da mesma forma.
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

// Funções de consulta agora retornam a contagem de itens
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

// =============================================================================
//                 FUNÇÕES HANDLE (INTERFACE COM USUÁRIO - SCANF)
// =============================================================================
// ... (demais funções handle inalteradas) ...
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

// ATUALIZADA: Pede um assento em vez de quantidade
void handle_comprar_ingresso()
{
    Cinema__FILME id_filme;
    int horario, tipo_int, assento; // <-- 'assento' em vez de 'quantidade'
    Cinema__TIPO_INGRESSO tipo_ingresso;

    printf("-> Digite o ID do filme: ");
    scanf("%d", &id_filme);
    printf("-> Digite o horário da sessão: ");
    scanf("%d", &horario);
    printf("-> Digite o tipo de ingresso (0 para Meia, 1 para Inteira): ");
    scanf("%d", &tipo_int);
    printf("-> Digite o número do assento: "); // <-- Prompt atualizado
    scanf("%d", &assento);                     // <-- Lê para a variável 'assento'

    if (tipo_int == 0)
        tipo_ingresso = Cinema__meia;
    else if (tipo_int == 1)
        tipo_ingresso = Cinema__inteira;
    else
    {
        printf("❌ FALHA: Tipo de ingresso inválido.\n");
        return;
    }
    executar_comprar_ingresso(id_filme, horario, tipo_ingresso, assento); // <-- Passa 'assento'
}

void handle_query_filmes() { executar_query_filmes(); }
void handle_query_salas() { executar_query_salas(); }
void handle_visualizar_filmes_em_cartaz() { executar_visualizar_filmes_em_cartaz(); }

// =============================================================================
//           FUNÇÃO DE TESTE AUTOMÁTICO (VERSÃO FINAL E COMPLETA)
// =============================================================================
void handle_executar_cenario_teste()
{
    printf("\n\n--- 🤖 INICIANDO CENÁRIO DE TESTE AUTOMÁTICO COMPLETO 🤖 ---\n");

    // Parâmetros do Teste
    Cinema__FILME id_filme_teste = 2;
    Cinema__SALA id_sala_teste = 1;
    int capacidade_teste = 10;
    int horario_teste = 18;
    int assento_teste_1 = 1;
    int assento_teste_2 = 2;

    // --- ETAPA 1: SETUP ---
    printf("\n--- [AÇÃO] Adicionando Itens Básicos ---\n");
    if (!executar_adicionar_filme(id_filme_teste))
    {
        printf("🔴 TESTE FALHOU: Não foi possível adicionar o filme inicial. Abortando.\n");
        return;
    }
    if (!executar_adicionar_sala(id_sala_teste, capacidade_teste))
    {
        printf("🔴 TESTE FALHOU: Não foi possível adicionar a sala inicial. Abortando.\n");
        return;
    }

    // --- ETAPA 2: VERIFICAÇÃO PÓS-SETUP ---
    printf("\n--- [VERIFICAÇÃO] Checando se os itens foram adicionados ---\n");
    if (executar_query_filmes() != 1)
    {
        printf("🔴 TESTE FALHOU: A contagem de filmes deveria ser 1.\n");
        return;
    }
    if (executar_query_salas() != 1)
    {
        printf("🔴 TESTE FALHOU: A contagem de salas deveria ser 1.\n");
        return;
    }

    // --- ETAPA 3: AGENDAMENTO DE SESSÃO ---
    printf("\n--- [AÇÃO] Agendando uma Sessão ---\n");
    if (!executar_disponibilizar_sala(id_sala_teste, horario_teste))
    {
        printf("🔴 TESTE FALHOU: Não foi possível disponibilizar a sala. Abortando.\n");
        return;
    }
    if (!executar_adicionar_sessao(id_sala_teste, horario_teste, id_filme_teste))
    {
        printf("🔴 TESTE FALHOU: Não foi possível adicionar a sessão. Abortando.\n");
        return;
    }

    // --- ETAPA 4: VERIFICAÇÃO DE FILMES EM CARTAZ ---
    printf("\n--- [VERIFICAÇÃO] Checando se o filme está em cartaz ---\n");
    if (executar_visualizar_filmes_em_cartaz() != 1)
    {
        printf("🔴 TESTE FALHOU: A contagem de filmes em cartaz deveria ser 1.\n");
        return;
    }

    // --- ETAPA 5: VENDAS ---
    // printf("\n--- [AÇÃO] Vendendo Ingressos ---\n");
    // if (!executar_comprar_ingresso(id_filme_teste, horario_teste, Cinema__meia, assento_teste_1))
    // {
    //     printf("🔴 TESTE FALHOU: Não foi possível vender o primeiro ingresso. Abortando.\n");
    //     return;
    // }
    // if (!executar_comprar_ingresso(id_filme_teste, horario_teste, Cinema__inteira, assento_teste_2))
    // {
    //     printf("🔴 TESTE FALHOU: Não foi possível vender o segundo ingresso. Abortando.\n");
    //     return;
    // }

    // --- ETAPA 6: LIMPEZA ---
    printf("\n--- [AÇÃO] Removendo a Sessão e Itens ---\n");
    if (!executar_remover_sessao(id_sala_teste, horario_teste))
    {
        printf("🔴 TESTE FALHOU: Não foi possível remover a sessão. Abortando.\n");
        return;
    }
    if (!executar_indisponibilizar_sala(id_sala_teste, horario_teste))
    {
        printf("🔴 TESTE FALHOU: Não foi possível indisponibilizar a sala. Abortando.\n");
        return;
    }
    if (!executar_remover_sala(id_sala_teste))
    {
        printf("🔴 TESTE FALHOU: Não foi possível remover a sala. Abortando.\n");
        return;
    }
    if (!executar_remover_filme(id_filme_teste))
    {
        printf("🔴 TESTE FALHOU: Não foi possível remover o filme. Abortando.\n");
        return;
    }

    // --- ETAPA 7: VERIFICAÇÃO FINAL ---
    printf("\n--- [VERIFICAÇÃO] Checando se o sistema está limpo ---\n");
    if (executar_query_filmes() != 0)
    {
        printf("🔴 TESTE FALHOU: A contagem de filmes final deveria ser 0.\n");
        return;
    }
    if (executar_query_salas() != 0)
    {
        printf("🔴 TESTE FALHOU: A contagem de salas final deveria ser 0.\n");
        return;
    }
    if (executar_visualizar_filmes_em_cartaz() != 0)
    {
        printf("🔴 TESTE FALHOU: A contagem de filmes em cartaz final deveria ser 0.\n");
        return;
    }

    printf("\n\n--- ✨ CENÁRIO DE TESTE CONCLUÍDO COM SUCESSO! ✨ ---\n\n");
}