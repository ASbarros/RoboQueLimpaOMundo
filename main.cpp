#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include<time.h>/// necessário p/ função time() ...

#define INDIVIDUOS 10
#define PASSOS 20
#define TOTAL_ITERACOES 100
#define TOTAL_MATRIZES 2

using namespace std;

const int linha = 10;
const int coluna = 10;
int matMundo[12][12];

int numAleatorio2()
{
    return rand() % 2;
}

int numAleatorio7()
{
    return rand() % 7;
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
            matMundo[i][j] = numAleatorio2();
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


void imprimeMatrizIndividuos(int **mat)
{
    for(int i = 0; i < INDIVIDUOS; i++)
    {
        for(int j = 0; j < PASSOS; j++)
        {
            cout << mat[i][j] << " ";
        }
        printf("\n");
    }
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
            mat[i][j] = numAleatorio7();
        }
    }
}

int pegaPontuacao(int **mat, int linha)
{
    int soma = 0;
    for(int j = 0; j < PASSOS; j++)
    {
        soma += mat[linha][j];
    }
    return soma;
}

int main()
{
    srand(time(NULL)); /// semente para gerar números aleátorios ...

    int **matIndividuos[TOTAL_MATRIZES];
    for(int i = 0; i < TOTAL_MATRIZES; i++)
    {
        matIndividuos[i] = new int*[INDIVIDUOS];
        for(int j = 0; j < INDIVIDUOS; j++)
        {
            matIndividuos[i][j] = new int[PASSOS];
        }
    }

    preencheMundo(); /// preenchendo a matriz mundo ...
    geraPontuacao(matIndividuos[0]); /// preenchendo a matriz de pontuação ...

    imprimeMatrizMundo();
    imprimeMatrizIndividuos(matIndividuos[0]);
    for(int iteracao = 0; iteracao < TOTAL_ITERACOES; iteracao++)
    {
        /// cruzamento ...
        /// mutacao ...
    }

    //cout << pegaPontuacao(5);
    return 0;
}
