#include <stdio.h>
#include <stdlib.h>
#define NUMCOLUNA 2

void FIFO(int quantidadeProcessos, int processo[][NUMCOLUNA])
{
    int contadorAuxiliar;
    int tempo = processo[0][0];

    for (contadorAuxiliar = 0; contadorAuxiliar < quantidadeProcessos; contadorAuxiliar++)
    {
        tempo += processo[contadorAuxiliar][1];
        printf("\n %d-%d : P%d ", processo[contadorAuxiliar][0], tempo, contadorAuxiliar + 1);
    }
}

void cadastrarProcessos(int quantidadeProcessos, int processo[][NUMCOLUNA])
{
    int contadorAuxiliar;

    for (contadorAuxiliar = 0; contadorAuxiliar < quantidadeProcessos; contadorAuxiliar++)
    {
        printf("\n Digite o tempo de criação de P%d: ", contadorAuxiliar + 1);
        scanf("%d", &processo[contadorAuxiliar][0]);
        printf(" Digite o tempo de duração de P%d: ", contadorAuxiliar + 1);
        scanf("%d", &processo[contadorAuxiliar][1]);
    }
}

int main()
{
    int quantidadeProcessos = 0;
    int processo[6][NUMCOLUNA];
    int opcaoUsuario = 0;

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
    FIFO(quantidadeProcessos, processo);

    return 0;
}
