// TODO  Dar ao utilizador a opção de escolher o output com um formato CSV, tabular,
// campo a campo, entre outros.
// TODO Lidar graciosamente com eventuais erros do utilizador (e.g., passar texto
// para uma query de top N, indicar uma pasta inválida para o dataset, . . . ).
//TODO paginação para outputs longos


#include "interactive.h"

#include <stdio.h>

void imprimeMenuFinal() {
    printf("\n");
    printf("0 - Terminar o programa\n");
    printf("1 - Executar outra query\n");
}

void imprimeMenuPrincipal() {
    printf("\n");
    printf("Digite o número da Query que deseja executar:\n");
    printf("0 - Terminar o programa.\n");
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
}

void interactiveMode(const char *folderPathDataset, void *users_catalog, void *flights_catalog, void *reservations_catalog, void *passengers_catalog, void *stats) {
    parseFiles(folderPathDataset, users_catalog, flights_catalog, reservations_catalog, passengers_catalog, stats);

    // cria um ficheiro chamado input.txt
    FILE *fp = fopen("input.txt", "w");
    char *inputPath = "input.txt";
    FILE *fpOutput;

    int opcao = -1;
    char queryInfo[256];
    char output[256];
    while (opcao != 0) {
        // imprime o menu principal
        imprimeMenuPrincipal();

        scanf("%d", &opcao);
        if (opcao == 0) break;

        printf("Digite as informações da query:\n");
        scanf("%s", queryInfo);

        // Dá rewind no ficheiro para escrever desde o início (apaga o conteúdo anterior)
        rewind(fp);

        // escreve a opção e as informações da query no ficheiro input.txt
        fprintf(fp, "%d %s\n", opcao, queryInfo);

        // Dá rewind no ficheiro para o parser ler desde o início
        rewind(fp);

        // Faz o parse do ficheiro de input (e executa a query)
        if (!inputParser(inputPath, users_catalog, flights_catalog, reservations_catalog, passengers_catalog, stats)) {
            printf("Error parsing input file\n");
            break;
        }

        // imprime o output da query (que está no ficheiro command1_output.txt)
        // TODO mudar isto para ter uma paginação para outputs longos
        fpOutput = fopen("Resultados/command1_output.txt", "r");
        if (fpOutput != NULL) {
            while (fgets(output, 256, fpOutput) != NULL) {
                printf("%s", output);
            }
        } else {
            printf("Error opening output file\n");
        }

        // imprime o menu final
        imprimeMenuFinal();

        scanf("%d", &opcao);
    }

    if (fp != NULL) fclose(fp);
    if (fpOutput != NULL) fclose(fpOutput);
    return;
}