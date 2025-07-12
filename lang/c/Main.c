#include <stdio.h>
#include <stdbool.h> // Incluído para usar o tipo 'bool' de forma padrão

/* * Nota: Incluir o arquivo .c diretamente não é uma prática padrão em projetos maiores.
 * O correto seria incluir o "Cinema.h" e compilar os dois arquivos .c juntos.
 * No entanto, para seguir o padrão do seu exemplo original, incluímos o .c aqui.
 */
#include "Cinema_i.c" 

// Função auxiliar para imprimir o estado atual de todas as variáveis do cinema.
void print_cinema_data() {
    printf("<=======================================================>\n");
    
    // Imprime a lista de filmes existentes
    printf("FILMES EM CARTAZ (true = existe):\n");
    for (int i = 0; i <= Cinema__limit_filmes; i++) {
        // Acessa a variável estática diretamente, como no exemplo original
        printf("filmes_i(%d) = %s\n", i, Cinema__filmes_i[i] ? "true" : "false");
    }

    // Imprime a lista de salas existentes
    printf("\nSALAS DO CINEMA (true = existe):\n");
    for (int i = 0; i <= Cinema__limit_salas; i++) {
        printf("salas_i(%d) = %s\n", i, Cinema__salas_i[i] ? "true" : "false");
    }

    // Imprime a capacidade de cada sala
    printf("\nCAPACIDADE DAS SALAS:\n");
    for (int i = 0; i <= Cinema__limit_salas; i++) {
        printf("salaHasCapacidade_i(%d) = %d\n", i, Cinema__salaHasCapacidade_i[i]);
    }

    // Imprime as sessões (qual filme está em qual sala e horário)
    printf("\nSESSÕES (Sala x Horário = Filme):\n");
    for (int i = 0; i <= Cinema__limit_salas; i++) {
        for (int j = 0; j <= Cinema__horario_max; j++) {
            // Imprime apenas se houver um filme alocado para não poluir a tela
            if (Cinema__sessao_i[i][j] != Cinema__dummyFilme) {
                printf("sessao_i(Sala %d, Horario %d) = Filme %d\n", i, j, Cinema__sessao_i[i][j]);
            }
        }
    }
    
    printf("<=======================================================>\n");
}

int main(int argc, char** argv) {
    printf("INICIANDO SIMULAÇÃO DO CINEMA...\n\n");
    
    // 1. Inicializa todas as variáveis do sistema Cinema
    Cinema__INITIALISATION();

    printf("Estado inicial do sistema:\n");
    print_cinema_data();

    // 2. Executa algumas operações para popular o cinema
    printf("\nADICIONANDO FILMES E SALAS...\n");
    Cinema__AdicionarFilme(1); // Adiciona o filme com ID 1
    Cinema__AdicionarFilme(3); // Adiciona o filme com ID 3

    Cinema__AdicionarSala(1, 10); // Adiciona a sala 1 com capacidade 10
    Cinema__AdicionarSala(2, 8);  // Adiciona a sala 2 com capacidade 8

    // Disponibiliza a sala 1 no horário das 20h.
    // Nota: A função AdicionarSessao não está implementada, então isso apenas mudará a variável 'salaHasHorarios_i'.
    Cinema__DisponibilizarSalaEmHorarios(1, 20);

    printf("\nEstado do sistema após adições:\n");
    print_cinema_data();

    // 3. Executa uma operação de consulta (Query)
    printf("\nCONSULTANDO FILMES EM CARTAZ...\n");
    bool filmes_em_cartaz[Cinema__limit_filmes + 1];
    Cinema__QueryFilmes(filmes_em_cartaz);
    for (int i = 0; i <= Cinema__limit_filmes; i++) {
        printf("QueryFilmes(%d) = %s\n", i, filmes_em_cartaz[i] ? "true" : "false");
    }
    
    // 4. Demonstra o uso de funções de pré-condição
    printf("\nVERIFICANDO PRÉ-CONDIÇÕES...\n");
    bool ok;

    // Tenta adicionar um filme que já existe
    Cinema__pre_adicionarFilme(1, &ok);
    printf("É permitido adicionar o filme 1 novamente? Resposta: %s\n", ok ? "Sim" : "Não");

    // Tenta adicionar um filme novo
    Cinema__pre_adicionarFilme(5, &ok);
    printf("É permitido adicionar o filme 5? Resposta: %s\n", ok ? "Sim" : "Não");
    
    // Tenta adicionar uma sala com capacidade inválida (maior que o limite)
    Cinema__pre_adicionarSala(3, 15, &ok); // 15 > limit_capacidade (10)
    printf("É permitido adicionar a sala 3 com capacidade 15? Resposta: %s\n", ok ? "Sim" : "Não");
    
    // Tenta adicionar uma sala válida
    Cinema__pre_adicionarSala(4, 5, &ok);
    printf("É permitido adicionar a sala 4 com capacidade 5? Resposta: %s\n", ok ? "Sim" : "Não");

    printf("\nSIMULAÇÃO FINALIZADA!\n");

    return 0;
}