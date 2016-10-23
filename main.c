#include <stdio.h>
#include <stdlib.h>

#define INICIALIZA_TEMPO 9999999

struct DadosProcesso
{
    int numeroProcesso;
    int prioridade;
    int tempoInicial;
    int tempoDuracao;
    int tempoEspera;
    int tempoTotalExecucao;

    int variavelAuxiliar;
};

void inserirDadosIniciais(int *opcaoUsuario, int *totalProcessos)
{
    printf("** ESCALONADOR DE PROCESSOS **\n");
    printf("\n1 = FIFO \n2 = SJF Preemptivo \n3 = Prioridades \n\nDigite o algoritmo a ser utilizado: ");
    scanf("%d", opcaoUsuario);

    while ((*opcaoUsuario > 3) || (*opcaoUsuario < 1))
    {
        printf("\nOpção inválida! Informe o algoritmo 1, 2 ou 3: ");
        scanf("%d", opcaoUsuario);
    }

    printf("\nDigite o número de processos a serem criados: ");
    scanf("%d", totalProcessos);

    while ((*totalProcessos > 6) || (*totalProcessos < 3))
    {
        printf("\nNúmero inválido! Digite um número de 3 até 6: ");
        scanf("%d", totalProcessos);
    }
}

void cadastrarProcessos(struct DadosProcesso processo[], int totalProcessos)
{
    int contadorProcessos;

    for (contadorProcessos = 0; contadorProcessos < totalProcessos; contadorProcessos++)
    {
        processo[contadorProcessos].numeroProcesso = contadorProcessos + 1;
        printf("\nPROCESSO P%d: \n", processo[contadorProcessos].numeroProcesso);
        printf("Digite o tempo inicial: ");
        scanf("%d", &processo[contadorProcessos].tempoInicial);
        printf("Digite o tempo de duração: ");
        scanf("%d", &processo[contadorProcessos].tempoDuracao);
        printf("Digite a prioridade: ");
        scanf("%d", &processo[contadorProcessos].prioridade);
        processo[contadorProcessos].variavelAuxiliar = 0;
        processo[contadorProcessos].tempoEspera = 0;
        processo[contadorProcessos].tempoTotalExecucao = processo[contadorProcessos].tempoDuracao;
    }
}

void inverterProcessos(struct DadosProcesso processo[], int i, int j)
{
    int variavelAuxiliar = processo[i].tempoInicial;

    processo[i].tempoInicial = processo[j].tempoInicial; // INVERTE O TEMPO INICIAL:
    processo[j].tempoInicial = variavelAuxiliar;

    variavelAuxiliar = processo[i].tempoDuracao;
    processo[i].tempoDuracao = processo[j].tempoDuracao; // INVERTE O TEMPO DA DURAÇÃO:
    processo[j].tempoDuracao = variavelAuxiliar;

    variavelAuxiliar = processo[i].numeroProcesso;
    processo[i].numeroProcesso = processo[j].numeroProcesso; // INVERTE O "NOME":
    processo[j].numeroProcesso = variavelAuxiliar;

    variavelAuxiliar = processo[i].prioridade;
    processo[i].prioridade = processo[j].prioridade;
    processo[i].prioridade = processo[j].prioridade;
}

void ordenarFirstInFirstOut(struct DadosProcesso processo[], int totalProcessos)
{
    int i, j;

    for (i = 0; i < totalProcessos; i++)
    {
        for (j = i + 1; j < totalProcessos; j++)
        {
            if (processo[i].tempoInicial > processo[j].tempoInicial)
            {
                inverterProcessos(processo, i, j);
            }
        }
    }
}

void ordenarProcessosPrioridade(struct DadosProcesso processo[], int totalProcessos)
{
    int i, j;

    for (i = 0; i < totalProcessos; i++)
    {
        for (j = i + 1; j < totalProcessos; j++)
        {
            if (processo[i].prioridade < processo[j].prioridade)
            {
                inverterProcessos(processo, i, j);
            }
        }
    }
}

void exibirProcessos(struct DadosProcesso processo[], int totalProcessos)
{
    int contadorProcessos;
    int tempo = processo[0].tempoInicial;

    for (contadorProcessos = 0; contadorProcessos < totalProcessos; contadorProcessos++)
    {
        processo[contadorProcessos].tempoEspera = processo[contadorProcessos].tempoInicial - tempo;

        if (processo[contadorProcessos].tempoInicial < tempo)
        {
            printf("\n%d-%d : P%d ", tempo, tempo + processo[contadorProcessos].tempoDuracao, processo[contadorProcessos].numeroProcesso);
            processo[contadorProcessos].tempoEspera = tempo - processo[contadorProcessos].tempoInicial;
            tempo += processo[contadorProcessos].tempoDuracao;
        }
        else
        {
            printf("\n%d-%d : P%d ", processo[contadorProcessos].tempoInicial, processo[contadorProcessos].tempoInicial + processo[contadorProcessos].tempoDuracao, processo[contadorProcessos].numeroProcesso);
            processo[contadorProcessos].tempoEspera = 0;
            tempo += (processo[contadorProcessos].tempoInicial - tempo) + processo[contadorProcessos].tempoDuracao;
        }
        printf("\nTEMPO ESPERA: %d.\n", processo[contadorProcessos].tempoEspera);
    }
}

int PercorreuTodosProcessos(struct DadosProcesso processo[],int totalProcessos)
{
    int contadorProcessos;

    for (contadorProcessos = 0; contadorProcessos < totalProcessos; contadorProcessos++)
        if (processo[contadorProcessos].variavelAuxiliar == 0)
            return 0;
    return 1;
}

int buscarTempo(struct DadosProcesso processo[], int tempoAuxiliar, int totalProcessos)
{
    int posicaoProcesso;
    int tempo = INICIALIZA_TEMPO;
    int contadorProcessos;

    for(contadorProcessos = 0; contadorProcessos < totalProcessos; contadorProcessos++)
    {
        if (processo[contadorProcessos].tempoInicial <= tempoAuxiliar && processo[contadorProcessos].variavelAuxiliar == 0)
            if(tempo > processo[contadorProcessos].tempoDuracao)
            {
                tempo = processo[contadorProcessos].tempoDuracao;
                posicaoProcesso = contadorProcessos;
            }
    }
    return posicaoProcesso;
}

int ContarQuantidadeTroca(struct DadosProcesso processo[], int processoAuxiliar[], int totalProcessos)
{
    int tempoAuxiliar = 0;
    int contadorProcessos = 0;
    int posicaoAuxiliar;

    while (1)
    {
        if (PercorreuTodosProcessos(processo, totalProcessos))
            break;

        posicaoAuxiliar = buscarTempo(processo, tempoAuxiliar, totalProcessos);
        processoAuxiliar[contadorProcessos] = posicaoAuxiliar;
        processo[posicaoAuxiliar].tempoDuracao--;

        if (processo[posicaoAuxiliar].tempoDuracao == 0)
            processo[posicaoAuxiliar].variavelAuxiliar = 1;

        tempoAuxiliar++;
        contadorProcessos++;
    }
    return contadorProcessos;
}

void ShortestRemainingTimeNext(struct DadosProcesso processo[], int totalProcessos) // SJF PREEMPTIVO
{
    int processoAuxiliar[50];
    int indiceAuxiliar;
    int contadorProcessosTrocados = 0;
    int tempoAnterior = 0;
    int tempoTotalPercorrido = 0;

    contadorProcessosTrocados = ContarQuantidadeTroca(processo, processoAuxiliar, totalProcessos);

    for (indiceAuxiliar = 0; indiceAuxiliar < contadorProcessosTrocados - 1; indiceAuxiliar++)
    {
        while(indiceAuxiliar < contadorProcessosTrocados - 1 && processoAuxiliar[indiceAuxiliar] == processoAuxiliar[indiceAuxiliar+1])
        {
            tempoTotalPercorrido++;
            indiceAuxiliar++;
        }

        tempoTotalPercorrido++;
        printf("\n%d-%d: P%d\n", tempoAnterior, tempoTotalPercorrido, processo[processoAuxiliar[indiceAuxiliar]].numeroProcesso);
        processo[processoAuxiliar[indiceAuxiliar]].tempoEspera = tempoTotalPercorrido - processo[processoAuxiliar[indiceAuxiliar]].tempoInicial - processo[processoAuxiliar[indiceAuxiliar]].tempoTotalExecucao;
        tempoAnterior = tempoTotalPercorrido;
    }
}

void calcularTempoMedioEspera(struct DadosProcesso processo[], int totalProcessos, float *tempoMedioEspera)
{
    int contadorProcessos;

    for (contadorProcessos = 0; contadorProcessos < totalProcessos; contadorProcessos++)
    {
        *tempoMedioEspera += processo[contadorProcessos].tempoEspera;
    }
    *tempoMedioEspera /= totalProcessos;
}

int main()
{
    int totalProcessos = 0;
    int opcaoUsuario = 0;
    float tempoMedioEspera = 0;
    struct DadosProcesso processo[6];

    inserirDadosIniciais(&opcaoUsuario, &totalProcessos);
    cadastrarProcessos(processo, totalProcessos);

    switch(opcaoUsuario)
    {
    case 1:
        ordenarFirstInFirstOut(processo, totalProcessos);
        exibirProcessos(processo, totalProcessos);
        break;
    case 2:
        ShortestRemainingTimeNext(processo, totalProcessos);
        break;
    case 3:
        ordenarProcessosPrioridade(processo, totalProcessos);
        exibirProcessos(processo, totalProcessos);
        break;
    }

    calcularTempoMedioEspera(processo, totalProcessos, &tempoMedioEspera);
    printf("\nTempo médio de espera : %.2f\n", tempoMedioEspera);

    return 0;
}
