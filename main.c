#include <stdio.h>
#include <stdlib.h>
#define NUMCOLUNA 4

void cadastrarProcessos(int quantidadeProcessos, int processo[][NUMCOLUNA])
{
    int contadorAuxiliar;

    for (contadorAuxiliar = 0; contadorAuxiliar < quantidadeProcessos; contadorAuxiliar++)
    {
        printf("\n Digite o tempo de criação de P%d: ", contadorAuxiliar + 1);
        scanf("%d", &processo[contadorAuxiliar][0]);
        printf(" Digite o tempo de duração de P%d: ", contadorAuxiliar + 1);
        scanf("%d", &processo[contadorAuxiliar][1]);
        processo[contadorAuxiliar][3] = contadorAuxiliar + 1;
    }
}

void ordenarProcessos(int quantidadeProcesos, int processo[][NUMCOLUNA])
{
    int i, j, variavelAuxiliar;

    for (i = 0; i < quantidadeProcesos; i++)
    {
        for (j = i + 1; j < quantidadeProcesos; j++)
        {
            if (processo[i][0] > processo[j][0])
            {
                variavelAuxiliar = processo[i][0];
                processo[i][0] = processo[j][0]; // INVERTE O TEMPO DA CRIAÇÃO:
                processo[j][0] = variavelAuxiliar;

                variavelAuxiliar = processo[i][1];
                processo[i][1] = processo[j][1]; // INVERTE O TEMPO DA DURAÇÃO:
                processo[j][1] = variavelAuxiliar;

                processo[i][3] = j + 1; // INVERTE O "NOME":
                processo[j][3] = j;
            }
        }
    }
    /*for (i = 0; i < quantidadeProcesos; i++ )
    {
        printf("\n%d", processo[i][0]);
        printf("\n%d", processo[i][3]);
    } */
}

void FIFO(int quantidadeProcessos, int processo[][NUMCOLUNA])
{
    int contadorAuxiliar;
    int tempo = processo[0][0]; // TEMPO INICIAL

    for (contadorAuxiliar = 0; contadorAuxiliar < quantidadeProcessos; contadorAuxiliar++)
    {
        printf("\n %d-%d : P%d ", tempo, tempo + processo[contadorAuxiliar][1], processo[contadorAuxiliar][3]);
        tempo += processo[contadorAuxiliar][1];
    }
}

int main()
{
    int quantidadeProcessos, opcaoUsuario = 0;
    int processo[6][NUMCOLUNA] = {{0}}; // 4 COLUNAS: TEMPO DA CRIAÇÃO, DURAÇÃO, PRIORIDADE E "NOME".

    while ((opcaoUsuario > 3) || (opcaoUsuario < 1))
    {
        printf("\n 1 = FIFO \n 2 = SJF Preemptivo \n 3 = Prioridades \n\n Digite o algoritmo a ser utilizado: ");
        scanf("%d", &opcaoUsuario);
    }

    while ((quantidadeProcessos > 6) || (quantidadeProcessos < 3))
    {
        printf("\n Digite a quantidade de processos - SOMENTE DE 3 À 6: ");
        scanf("%d", &quantidadeProcessos);
    }

    cadastrarProcessos(quantidadeProcessos, processo);
    ordenarProcessos(quantidadeProcessos, processo);
    FIFO(quantidadeProcessos, processo);

    return 0;
}
