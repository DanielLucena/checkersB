// main.c
#include <stdio.h>
#include <stdlib.h>
#include "Cinema.h" // Inclui o seu header exato

// Protótipos das funções da interface
void handle_adicionar_filme();
void handle_remover_filme();
void handle_adicionar_sala();
void handle_remover_sala();
void handle_adicionar_sessao();
void handle_remover_sessao();
void handle_comprar_ingresso();
void handle_disponibilizar_sala();
void handle_indisponibilizar_sala();

void exibir_menu()
{
    printf("\n--- 🎟️ Sistema de Gerenciamento de Cinema 🎟️ ---\n");
    printf("--- Filmes e Salas ---\n");
    printf(" 1. Adicionar Filme\n");
    printf(" 2. Remover Filme\n");
    printf(" 3. Adicionar Sala\n");
    printf(" 4. Remover Sala\n");
    printf("--- Horários e Sessões ---\n");
    printf(" 5. Disponibilizar Sala em Horário\n");
    printf(" 6. Indisponibilizar Sala em Horário\n");
    printf(" 7. Adicionar Sessão\n");
    printf(" 8. Remover Sessão\n");
    printf(" 9. Comprar Ingresso\n");
    printf("------------------------------------------------\n");
    printf(" 0. Sair\n");
    printf("------------------------------------------------\n");
    printf("Escolha uma opção: ");
}

int main()
{
    // Inicializa o sistema do cinema uma única vez
    Cinema__INITIALISATION();
    printf("Bem-vindo! Sistema de Cinema inicializado.\n");

    int escolha;
    while (1)
    {
        exibir_menu();
        if (scanf("%d", &escolha) != 1)
        {
            // Limpa o buffer de entrada em caso de input inválido
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

// Funções "Manipuladoras" que interagem com o usuário e o código do cinema

void handle_adicionar_filme()
{
    Cinema__FILME id_filme;
    printf("-> Digite o ID do filme para adicionar (0 a %d): ", Cinema__FILME__max - 1);
    scanf("%d", &id_filme);

    bool pre_condicao_ok = false;
    Cinema__pre_adicionarFilme(id_filme, &pre_condicao_ok);

    if (pre_condicao_ok)
    {
        Cinema__AdicionarFilme(id_filme);
        printf("✅ SUCESSO: Filme %d adicionado.\n", id_filme);
    }
    else
    {
        printf("❌ FALHA: Não foi possível adicionar o filme. A pré-condição não foi atendida (filme já existe ou ID inválido).\n");
    }
}

void handle_remover_filme()
{
    Cinema__FILME id_filme;
    printf("-> Digite o ID do filme para remover (0 a %d): ", Cinema__FILME__max - 1);
    scanf("%d", &id_filme);

    bool pre_condicao_ok = false;
    Cinema__pre_removerFilme(id_filme, &pre_condicao_ok);

    if (pre_condicao_ok)
    {
        Cinema__RemoverFilme(id_filme);
        printf("✅ SUCESSO: Filme %d removido.\n", id_filme);
    }
    else
    {
        printf("❌ FALHA: Não foi possível remover o filme. A pré-condição não foi atendida (filme não existe).\n");
    }
}

void handle_adicionar_sala()
{
    Cinema__SALA id_sala;
    int capacidade;
    printf("-> Digite o ID da sala para adicionar (0 a %d): ", Cinema__SALA__max - 1);
    scanf("%d", &id_sala);
    printf("-> Digite a capacidade da sala (1 a %d): ", Cinema__limit_capacidade);
    scanf("%d", &capacidade);

    bool pre_condicao_ok = false;
    Cinema__pre_adicionarSala(id_sala, capacidade, &pre_condicao_ok);

    if (pre_condicao_ok)
    {
        Cinema__AdicionarSala(id_sala, capacidade);
        printf("✅ SUCESSO: Sala %d com capacidade %d adicionada.\n", id_sala, capacidade);
    }
    else
    {
        printf("❌ FALHA: Não foi possível adicionar a sala. A pré-condição não foi atendida (sala já existe ou capacidade inválida).\n");
    }
}

void handle_remover_sala()
{
    Cinema__SALA id_sala;
    printf("-> Digite o ID da sala para remover (0 a %d): ", Cinema__SALA__max - 1);
    scanf("%d", &id_sala);

    bool pre_condicao_ok = false;
    Cinema__pre_removerSala(id_sala, &pre_condicao_ok);

    if (pre_condicao_ok)
    {
        Cinema__RemoverSala(id_sala);
        printf("✅ SUCESSO: Sala %d removida.\n", id_sala);
    }
    else
    {
        printf("❌ FALHA: Não foi possível remover a sala. A pré-condição não foi atendida (sala não existe).\n");
    }
}

void handle_disponibilizar_sala()
{
    Cinema__SALA id_sala;
    int horario;
    printf("-> Digite o ID da sala: ");
    scanf("%d", &id_sala);
    printf("-> Digite o horário a ser disponibilizado (0 a %d): ", Cinema__horario_max);
    scanf("%d", &horario);

    bool pre_condicao_ok = false;
    Cinema__pre_disponibilizarSalaEmHorarios(id_sala, horario, &pre_condicao_ok);

    if (pre_condicao_ok)
    {
        Cinema__DisponibilizarSalaEmHorarios(id_sala, horario);
        printf("✅ SUCESSO: Sala %d disponibilizada no horário %dh.\n", id_sala, horario);
    }
    else
    {
        printf("❌ FALHA: A pré-condição não foi atendida. Verifique se a função está implementada e se os dados são válidos.\n");
    }
}

void handle_indisponibilizar_sala()
{
    Cinema__SALA id_sala;
    int horario;
    printf("-> Digite o ID da sala: ");
    scanf("%d", &id_sala);
    printf("-> Digite o horário a ser indisponibilizado (0 a %d): ", Cinema__horario_max);
    scanf("%d", &horario);

    bool pre_condicao_ok = false;
    Cinema__pre_indisponibilizarSalaEmHorarios(id_sala, horario, &pre_condicao_ok);

    if (pre_condicao_ok)
    {
        Cinema__IndisponibilizarSalaEmHorarios(id_sala, horario);
        printf("✅ SUCESSO: Sala %d indisponibilizada no horário %dh.\n", id_sala, horario);
    }
    else
    {
        printf("❌ FALHA: A pré-condição não foi atendida. Verifique se a função está implementada e se os dados são válidos.\n");
    }
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

    bool pre_condicao_ok = false;
    Cinema__pre_adicionarSessao(id_sala, horario, id_filme, &pre_condicao_ok);

    if (pre_condicao_ok)
    {
        Cinema__AdicionarSessao(id_sala, horario, id_filme);
        printf("✅ SUCESSO: Sessão adicionada.\n");
    }
    else
    {
        printf("❌ FALHA: A pré-condição não foi atendida. Verifique se a função está implementada e se os dados são válidos.\n");
    }
}

void handle_remover_sessao()
{
    Cinema__SALA id_sala;
    int horario;

    printf("-> Digite o ID da sala: ");
    scanf("%d", &id_sala);
    printf("-> Digite o horário da sessão a ser removida: ");
    scanf("%d", &horario);

    bool pre_condicao_ok = false;
    Cinema__pre_removerSessao(id_sala, horario, &pre_condicao_ok);

    if (pre_condicao_ok)
    {
        Cinema__RemoverSessao(id_sala, horario);
        printf("✅ SUCESSO: Sessão removida.\n");
    }
    else
    {
        printf("❌ FALHA: A pré-condição não foi atendida. Verifique se a função está implementada e se os dados são válidos.\n");
    }
}

void handle_comprar_ingresso()
{
    Cinema__FILME id_filme;
    int horario, tipo_int, quantidade;
    Cinema__TIPO_INGRESSO tipo_ingresso;

    printf("-> Digite o ID do filme: ");
    scanf("%d", &id_filme);
    printf("-> Digite o horário da sessão: ");
    scanf("%d", &horario);
    printf("-> Digite o tipo de ingresso (0 para Meia, 1 para Inteira): ");
    scanf("%d", &tipo_int);
    printf("-> Digite a quantidade de ingressos: ");
    scanf("%d", &quantidade);

    if (tipo_int == 0)
    {
        tipo_ingresso = Cinema__meia;
    }
    else if (tipo_int == 1)
    {
        tipo_ingresso = Cinema__inteira;
    }
    else
    {
        printf("❌ FALHA: Tipo de ingresso inválido.\n");
        return;
    }

    bool pre_condicao_ok = false;
    // O último parâmetro 'aa' em ComprarIngresso não está claro, usamos a quantidade aqui.
    // A pre_comprarIngresso tem uma assinatura diferente, adaptamos para o que faz sentido.
    Cinema__pre_comprarIngresso(id_filme, horario, tipo_ingresso, &pre_condicao_ok);

    if (pre_condicao_ok)
    {
        Cinema__ComprarIngresso(id_filme, horario, tipo_ingresso, quantidade);
        printf("✅ SUCESSO: Compra de %d ingresso(s) realizada.\n", quantidade);
    }
    else
    {
        printf("❌ FALHA: A pré-condição não foi atendida. Verifique se a função está implementada e se os dados são válidos.\n");
    }
}