// TODO  Dar ao utilizador a opção de escolher o output com um formato CSV, tabular,
// campo a campo, entre outros.
// TODO Lidar graciosamente com eventuais erros do utilizador (e.g., passar texto
// para uma query de top N, indicar uma pasta inválida para o dataset, . . . ).
// TODO paginação para outputs longos

#include "interactive.h"

#include <stdio.h>
#include <unistd.h>

#define LINHAS_POR_PAGINA 15
#define TAMANHO_LINHA 256

void limparBufferTeclado() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

void imprimeMenuFinal() {
    printf("\n");
    printf("0 - Terminar o programa\n");
    printf("1 - Executar outra query\n");
}

void imprimeMenuFlag() {
    printf("\n");
    printf("Deseja adicionar a flag -F ao comando?\n");
    printf("0 - Não\n");
    printf("1 - Sim\n");
}

void imprimeMenuPrincipal() {
    printf("\n");
    printf("Digite o número da Query que deseja executar:\n\n");
    printf("1 - Listar o resumo de um utilizador, voo, ou reserva, consoante o identificador recebido por argumento.\n");
    printf("Uso: <ID>\n");
    printf("2 - Listar os voos ou reservas de um utilizador, se o segundo argumento for flights ou reservations, respetivamente, ordenados por data (da mais recente para a mais antiga).\n");
    printf("Uso: <ID> [flights|reservations]\n");
    printf("3 - Apresentar a classificação média de um hotel, a partir do seu identificador.\n");
    printf("Uso: <ID>\n");
    printf("4 - Listar as reservas de um hotel, ordenadas por data de início (da mais recente para a mais antiga).\n");
    printf("Uso: <ID>\n");
    printf("5 - Listar os voos com origem num dado aeroporto, entre duas datas, ordenados por data de partida estimada (da mais antiga para a mais recente).\n");
    printf("Uso: <Name> <Begin_date> <End_date>\n");
    printf("6 - Listar o top N aeroportos com mais passageiros, para um dado ano. Deverão ser contabilizados os voos com a data estimada de partida nesse ano.\n");
    printf("Uso: <Year> <N>\n");
    printf("7 - Listar o top N aeroportos com a maior mediana de atrasos.\n");
    printf("Uso: <N>\n");
    printf("8 - Apresentar a receita total de um hotel entre duas datas (inclusive), a partir do seu identificador.\n");
    printf("Uso: <Id> <Begin_date> <End_date>\n");
    printf("9 - Listar todos os utilizadores cujo nome começa com o prefixo passado por argumento, ordenados por nome (de forma crescente).\n");
    printf("Uso: <Prefix>\n");
    printf("10 - Apresentar várias métricas gerais da aplicação.\n");
    printf("Uso: [year [month]]\n");
    printf("0 - Terminar o programa.\n");
}

void interactiveMode(const char *folderPathDataset, void *users_catalog, void *flights_catalog, void *reservations_catalog, void *passengers_catalog, void *stats) {
    parseFiles(folderPathDataset, users_catalog, flights_catalog, reservations_catalog, passengers_catalog, stats);

    FILE *fpOutput;  // esta fora do ciclo para no futuro podermos "retornar" o ficheiro como output em vez de imprimir no terminal

    int opcao = -1;
    int flag = -1;
    char queryInfo[TAMANHO_LINHA];
    char output[TAMANHO_LINHA];

    while (opcao != 0) {
        // cria um ficheiro chamado input.txt
        FILE *fp = fopen("input.txt", "w");  // esta dentro do ciclo para limpar o ficheiro a cada iteração (execuntando uma query de cada vez)
        char *inputPath = "input.txt";

        opcao = -1;
        while (true) {
            // imprime o menu principal
            imprimeMenuPrincipal();

            scanf("%d", &opcao);
            if (opcao >= 0 && opcao <= 10) break;
            printf("Opção inválida\n");
        }

        if (opcao == 0) {
            if (fp != NULL) fclose(fp);
            break;
        }

        while (true) {
            // imprime o menu da flag
            imprimeMenuFlag();

            scanf("%d", &flag);
            if (flag == 0 || flag == 1) break;
            printf("Opção inválida\n");
        }

        printf("Digite as informações da query:\n");
        scanf("%s", queryInfo);
        limparBufferTeclado();  // para não ficar lixo no buffer que possa interferir com o getchar() ao imprimir o output

        // Dá rewind no ficheiro para escrever desde o início (apaga o conteúdo anterior)
        rewind(fp);

        // escreve a opção e as informações da query no ficheiro input.txt
        if (flag == 1) {
            fprintf(fp, "%dF %s\n", opcao, queryInfo);
        } else {
            fprintf(fp, "%d %s\n", opcao, queryInfo);
        }

        // Dá rewind no ficheiro para o parser ler desde o início
        rewind(fp);

        // Faz o parse do ficheiro de input (e executa a query)
        if (!inputParser(inputPath, users_catalog, flights_catalog, reservations_catalog, passengers_catalog, stats, false)) {
            printf("Error parsing input file\n");
            break;
        }

        // imprime o output da query (que está no ficheiro command1_output.txt)
        fpOutput = fopen("Resultados/command1_output.txt", "r");
        printf("\n");
        printf("Output:\n");
        if (fpOutput != NULL) {
            int count = 0;
            while (fgets(output, TAMANHO_LINHA, fpOutput) != NULL) {
                printf("%s", output);
                if (count++ == LINHAS_POR_PAGINA) {
                    getchar();
                    count = 0;
                }
            }
        } else {
            printf("Error opening output file\n");
        }
        if (fpOutput != NULL) fclose(fpOutput);
        printf("=== Fim do output ===\n\n");

        while (true) {
            // imprime o menu final
            imprimeMenuFinal();

            scanf("%d", &opcao);
            if (opcao == 0 || opcao == 1) break;
            printf("Opção inválida\n");
        }

        // limpa o ficheiro de input
        if (fp != NULL) fclose(fp);
    }

    if (fpOutput != NULL) fclose(fpOutput);

    return;
}