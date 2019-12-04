#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h> /// necessário p/ função time() ...

#define INDIVIDUOS 100
#define PASSOS 200
#define TOTAL_ITERACOES 1000
#define TOTAL_MATRIZES TOTAL_ITERACOES

using namespace std;

const int linha = 10;
const int coluna = 10;

int matMundo[linha+2][coluna+2];

struct posicaoRobo
{
    int x;
    int y;
};

posicaoRobo posRobo;

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
        int num = numAleatorio(4);
            switch(mat[l][j])
            {
            // matriz de passos dos robos ...
            case 6:
                // caso se abaixou para pegar a lata ...
                if (matMundo[l][j] == 1)
                    soma +=10;
                else
                    soma = soma - 1;
                break;
            case 5:
                // fica parado ...
                break;
            case 4:
                // move aleatoriamente ...


                if(num == 0)
                {
                    // move para o oeste ...
                    if(matMundo[posRobo.x-1][posRobo.y] == 2)
                    {
                        // bater no muro ...
                        soma = soma - 5;
                    }
                    else
                    {
                        posRobo.x--;
                    }
                }
                else if(num==1)
                {
                    // move para leste ...
                    if(matMundo[posRobo.x+1][posRobo.y] == 2)
                    {
                        // bater no muro ...
                        soma = soma - 5;
                    }
                    else
                    {
                        posRobo.x++;
                    }
                }
                else if(num == 2)
                {
                    // move para sul ...
                    if(matMundo[posRobo.x][posRobo.y-1] == 2)
                    {
                        // bater no muro ...
                        soma = soma - 5;
                    }
                    else
                    {
                        posRobo.y--;
                    }
                }
                else if(num == 3)
                {
                    // move para o norte ...
                    if(matMundo[posRobo.x][posRobo.y+1] == 2)
                    {
                        // bater no muro ...
                        soma = soma - 5;
                    }
                    else
                    {
                        posRobo.y++;
                    }
                }
                break;
            case 3:
                // move para o oeste ...
                if(matMundo[posRobo.x-1][posRobo.y] == 2)
                {
                    // bater no muro ...
                    soma = soma - 5;
                }
                else
                {
                    posRobo.x--;
                }
                break;
            case 2:
                // move para leste ...
                if(matMundo[posRobo.x+1][posRobo.y] == 2)
                {
                    // bater no muro ...
                    soma = soma - 5;
                }
                else
                {
                    posRobo.x++;
                }
                break;
            case 1:
                // move para sul ...
                if(matMundo[posRobo.x][posRobo.y-1] == 2)
                {
                    // bater no muro ...
                    soma = soma - 5;
                }
                else
                {
                    posRobo.y--;
                }
                break;
            case 0:
                // move para o norte ...
                if(matMundo[posRobo.x][posRobo.y+1] == 2)
                {
                    // bater no muro ...
                    soma = soma - 5;
                }
                else
                {
                    posRobo.y++;
                }
                break;
            }
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
            mat[i][j] = (mat[i][j] + aleatorio) % 7;
        }
    }
}

void restauraPosRobo()
{
    // sempre começa na posição 1x1, por que a matriz tem as paredes ao redor ...
    posRobo.x = 1;
    posRobo.y = 1;
}

void inicializa()
{
    restauraPosRobo();
}

int melhorPontuacao(int **mat)
{
    // função para pegar a melhor pontuacao de uma geração ...
    int soma = 0;
    int aux = 0;
    for (int i = 0; i < INDIVIDUOS; i++)
    {
        for (int j = 0; j < PASSOS; j++)
        {
            int num = numAleatorio(4);
            switch(mat[i][j])
            {
            // matriz de passos dos robos ...
            case 6:
                // caso se abaixou para pegar a lata ...
                if (matMundo[i][j] == 1)
                    soma +=10;
                else
                    soma = soma - 1;
                break;
            case 5:
                // fica parado ...
                break;
            case 4:
                // move aleatoriamente ...


                if(num == 0)
                {
                    // move para o oeste ...
                    if(matMundo[posRobo.x-1][posRobo.y] == 2)
                    {
                        // bater no muro ...
                        soma = soma - 5;
                    }
                    else
                    {
                        posRobo.x--;
                    }
                }
                else if(num==1)
                {
                    // move para leste ...
                    if(matMundo[posRobo.x+1][posRobo.y] == 2)
                    {
                        // bater no muro ...
                        soma = soma - 5;
                    }
                    else
                    {
                        posRobo.x++;
                    }
                }
                else if(num == 2)
                {
                    // move para sul ...
                    if(matMundo[posRobo.x][posRobo.y-1] == 2)
                    {
                        // bater no muro ...
                        soma = soma - 5;
                    }
                    else
                    {
                        posRobo.y--;
                    }
                }
                else if(num == 3)
                {
                    // move para o norte ...
                    if(matMundo[posRobo.x][posRobo.y+1] == 2)
                    {
                        // bater no muro ...
                        soma = soma - 5;
                    }
                    else
                    {
                        posRobo.y++;
                    }
                }
                break;
            case 3:
                // move para o oeste ...
                if(matMundo[posRobo.x-1][posRobo.y] == 2)
                {
                    // bater no muro ...
                    soma = soma - 5;
                }
                else
                {
                    posRobo.x--;
                }
                break;
            case 2:
                // move para leste ...
                if(matMundo[posRobo.x+1][posRobo.y] == 2)
                {
                    // bater no muro ...
                    soma = soma - 5;
                }
                else
                {
                    posRobo.x++;
                }
                break;
            case 1:
                // move para sul ...
                if(matMundo[posRobo.x][posRobo.y-1] == 2)
                {
                    // bater no muro ...
                    soma = soma - 5;
                }
                else
                {
                    posRobo.y--;
                }
                break;
            case 0:
                // move para o norte ...
                if(matMundo[posRobo.x][posRobo.y+1] == 2)
                {
                    // bater no muro ...
                    soma = soma - 5;
                }
                else
                {
                    posRobo.y++;
                }
                break;
            }

        }
        if (soma > aux)
            aux = soma;
        soma = 0;
    }
    return aux;
}

int main()
{
    srand(time(NULL)); /// semente para gerar números aleátorios ...

    int **matIndividuos[TOTAL_MATRIZES];
    int matAux[INDIVIDUOS][PASSOS];
    int individuo1 = 0, individuo2 = 0, individuo3 = 0;
    int ponIndividuo1 = 0, ponIndividuo2 = 0;

    inicializa();


    for(int i = 0; i < TOTAL_MATRIZES; i++)
    {
        matIndividuos[i] = new int*[INDIVIDUOS];
        for(int j = 0; j < INDIVIDUOS; j++)
        {
            matIndividuos[i][j] = new int[PASSOS];
            for(int k =0; k < PASSOS; k++)
            {
                // inicializando a matriz ...
                matIndividuos[i][j][k] = numAleatorio(7);
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
                // pegando a geração anterior ...
                matAux[i][j] = matIndividuos[iteracao-1][i][j];
            }
        }
        for (int j = INDIVIDUOS/2; j < INDIVIDUOS; j++) /// for para fazer o cruzamento ...
        {
            individuo1 = numAleatorio(INDIVIDUOS);
            individuo2 = numAleatorio(INDIVIDUOS);

            /// cruzamento ...
            cruzamento(matIndividuos[iteracao], individuo1, individuo2, j);
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

        /// mutacao ...
        mutacao(matIndividuos[iteracao]);

        //geraPontuacao(matIndividuos[iteracao]);
        imprimeMatrizIndividuos(matIndividuos[iteracao], iteracao);

        cout << melhorPontuacao(matIndividuos[iteracao]);
    }
    return 0;
}
