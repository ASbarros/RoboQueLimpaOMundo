#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include<time.h>/// necessário p/ função time() ...

#define INDIVIDUOS 10
#define PASSOS 20

using namespace std;

const int linha = 10;
const int coluna = 10;
int matMundo[12][12];
int matIndividuos[INDIVIDUOS][PASSOS];

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

void imprimeMatriz(){
    for(int i = 0; i < linha +2;i++){
        for(int j = 0; j < coluna +2; j++){
            cout << matMundo[i][j] << " ";
        }
        printf("\n");
    }
}

int pontuacao(int linha){
    int soma = 0;
    for(int i = 1; i <= coluna; i++){
        soma += matMundo[linha][i];
    }
    return soma;
}

void geraPontuacao(int *mat[INDIVIDUOS][PASSOS]){
    for(int i = 0; i < INDIVIDUOS; i++){
        for(int j = 0; j < PASSOS; j++){
            *mat[i][j] = numAleatorio7();
        }
    }
}

int main()
{
    srand(time(NULL));
    preencheMundo();
    imprimeMatriz();
    geraPontuacao(&matIndividuos]);
    return 0;
}
