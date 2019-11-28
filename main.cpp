#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include<time.h>/// necessário p/ função time() ...

#define INDIVIDUOS 100
#define PASSOS 200
#define TOTAL_ITERACOES 100
#define TOTAL_MATRIZES TOTAL_ITERACOES

using namespace std;

const int linha = 10;
const int coluna = 10;
int matMundo[12][12];

int posicoes[INDIVIDUOS];



int numAleatorio(int range)
{
    return rand() % range;
}

void preencheMundo()
{
    /// colocando o muro na vertical ...
    for(int i = 0; i <= linha+1; i++)
    {
        matMundo[i][0] = 2;
        matMundo[i][coluna+1] = 2;
    }
    /// colocando o muro na horizontal ...
    for(int i = 0; i <= coluna+1; i++)
    {
        matMundo[0][i] = 2;
        matMundo[linha+1][i] = 2;
    }
    /// preenchendo o mundo com valores aleatorios ...
    for(int i = 1; i <= linha ; i++)
    {
        for(int j = 1; j <= coluna ; j++)
        {
            matMundo[i][j] = numAleatorio(2);
        }
    }
}

void imprimeMatrizMundo()
{
    for(int i = 0; i < linha +2; i++)
    {
        for(int j = 0; j < coluna +2; j++)
        {
            cout << matMundo[i][j] << " ";
        }
        printf("\n");
    }
}


void imprimeMatrizIndividuos(int **mat, int geracao)
{
    printf("\n---------  geracao %d  ---------------\n", geracao+1);
    for(int i = 0; i < INDIVIDUOS; i++)
    {
        for(int j = 0; j < PASSOS; j++)
        {
            cout << mat[i][j] << " ";
        }
        printf("\n");
    }
    printf("\n");
}

int pontuacao(int linha)
{
    int soma = 0;
    for(int i = 1; i <= coluna; i++)
    {
        soma += matMundo[linha][i];
    }
    return soma;
}

void geraPontuacao(int **mat)
{
    for(int i = 0; i < INDIVIDUOS; i++)
    {
        for(int j = 0; j < PASSOS; j++)
        {
            mat[i][j] = numAleatorio(7);
        }
    }
}

int pegaPontuacao(int **mat, int l)
{
    int soma = 0;
    for(int j = 0; j < PASSOS; j++)
    {
        soma += mat[l][j];
    }
    return soma;
}

void proxGeracao(int **mat, int matProx[INDIVIDUOS][PASSOS], int l, int atual)
{
    for(int j = 0; j < PASSOS; j++)
    {
        matProx[atual][j] = mat[l][j];
    }
}

void cruzamento (int **mat, int individuo1, int individuo2, int individuo3)
{
    for(int i = 0; i < PASSOS; i++)
    {
        if(i <= PASSOS/2)
        {
            mat[individuo3][i] = mat[individuo1][i];
        }
        else
        {
            mat[individuo3][i] = mat[individuo2][i];
        }
    }
}

void mutacao(int **mat)
{
    int aleatorio = 1;
    for (int i = 0; i < INDIVIDUOS; i++)
    {
        for (int j = 0; j < PASSOS; j++)
        {
            aleatorio = numAleatorio(7);
            if(aleatorio == 0)
                aleatorio = 1;
            mat[i][j] = (mat[i][j] * aleatorio) % 7;
        }
    }
}

int main()
{
    srand(time(NULL)); /// semente para gerar números aleátorios ...

    int **matIndividuos[TOTAL_MATRIZES];
    int matAux[INDIVIDUOS][PASSOS];
    int individuo1 = 0, individuo2 = 0, individuo3 = 0;
    int ponIndividuo1 = 0, ponIndividuo2 = 0;

    for (int i = 0; i < INDIVIDUOS; i++)
    {
        posicoes[i] = i;
    }

    for(int i = 0; i < TOTAL_MATRIZES; i++)
    {
        matIndividuos[i] = new int*[INDIVIDUOS];
        for(int j = 0; j < INDIVIDUOS; j++)
        {
            matIndividuos[i][j] = new int[PASSOS];
            for(int k=0; k < PASSOS; k++)
            {
                matIndividuos[i][j][k] = 0;
            }
        }
    }

    preencheMundo(); /// preenchendo a matriz mundo ...
    geraPontuacao(matIndividuos[0]); /// preenchendo a matriz de pontuação ...

    imprimeMatrizMundo();
    imprimeMatrizIndividuos(matIndividuos[0], 0);
    for(int iteracao = 1; iteracao < TOTAL_ITERACOES; iteracao++) /// for responsável por cada geração ...
    {
        for (int i = 0; i < INDIVIDUOS; i++)
        {
            for (int j = 0; j < PASSOS; j++)
            {
                matAux[i][j] = matIndividuos[iteracao-1][i][j];
            }
        }

        for (int j = 0; j < INDIVIDUOS/2; j++) /// for para pegar preencher a nova matriz de individuos com os representantes da anterior ...
        {

            individuo1 = numAleatorio(INDIVIDUOS);
            individuo2 = numAleatorio(INDIVIDUOS);

            ponIndividuo1 = pegaPontuacao(matIndividuos[iteracao-1], individuo1);
            ponIndividuo2 = pegaPontuacao(matIndividuos[iteracao-1], individuo2);
            /// pegando os representantes ...

            if(ponIndividuo1 > ponIndividuo2)
                proxGeracao(matIndividuos[iteracao], matAux, individuo1, j);
            else
                proxGeracao(matIndividuos[iteracao], matAux, individuo2, j);
        }
        for (int j = INDIVIDUOS/2; j < INDIVIDUOS; j++) /// for para fazer o cruzamento ...
        {
            individuo1 = numAleatorio(INDIVIDUOS);
            individuo2 = numAleatorio(INDIVIDUOS);
            individuo3 = numAleatorio(INDIVIDUOS);

            /// cruzamento ...
            cruzamento(matIndividuos[iteracao], individuo1, individuo2, individuo3);
        }

        /// mutacao ...
        mutacao(matIndividuos[iteracao]);

        geraPontuacao(matIndividuos[iteracao]);
        imprimeMatrizIndividuos(matIndividuos[iteracao], iteracao);
    }
    return 0;
}
