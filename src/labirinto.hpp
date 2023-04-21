#ifndef LABIRINTO_HPP
#define LABIRINTO_HPP
#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <vector>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <utility>
#include <stdlib.h>
#include <vector>

using namespace std;

typedef struct Posicao{
    string nome;
    vector<pair<int,int>>endereco;
    bool endereco_zerados;
}Posicao;

class Jogo{

    private:

    int vida,sacola;
    int pontuacao;
    int perigo;

    public:

    Jogo(int vida,int sacola,int pontuacao,int perigo);
    Jogo();
    void setVida(int nJogo);
    int getVida();
    void setSacola(int sacola);
    int getSacola();
    void setPontuacao(int pontuacao);
    int getPontuacao();
    void setPerigo(int perigo);
    int getPerigo();

    int lerTamanhoMatriz();
    void imprimirVida();
    void verificador_Nivel_SemPortal(string** matriz, int tamanho, int &f);
    void atualizandoJogo(string** matriz, int &i, int &j);
    void iniciarMatriz(string** matriz, int tamanho);
    void imprimirMatriz(string** matriz, int tamanho);
    void salvarMatrizArq(string** matriz, int tamanho, int numeroNivel);
    void iniciarCorrida(string** matriz, int tamanho,int i, int j,int inicialLinha,int inicialColuna, int numeroNivel,int qtdMatriz,vector<Posicao> &vetor_Coordenada);
    void lerTodasMatrizes(string** matriz, int tamanho);
    void iniciarJogo(string** matriz, int tamanho, int numeroNivel,int qtdMatriz);
    void lerMatrizUnica(string** matriz, int tamanho,string endereco);
    void imprimir_posicoes(int numeroNivel, vector<Posicao> &vetor_Coordenada);
    void conferir_CaminhoZero(string** matriz,int tamanho,int numeroNivel,vector<Posicao> &vetor_Coordenada);
    void andar_dpsSorteio(string** matriz, int tamanho,int &i, int &j, int numeroNivel,int qtdMatriz,vector<Posicao> &vetor_Coordenada,int sorteio);        
    void direita(string** matriz, int tamanho, int &i, int &j,int numeroNivel, int qtdMatriz,vector<Posicao> &vetor_Coordenada);
    void esquerda(string** matriz, int &i, int &j,int numeroNivel, int qtdMatriz,vector<Posicao> &vetor_Coordenada);
    void baixo(string** matriz, int tamanho, int &i, int &j,int numeroNivel, int qtdMatriz,vector<Posicao> &vetor_Coordenada);
    void emCima(string** matriz, int &i, int &j,int numeroNivel, int qtdMatriz,vector<Posicao> &vetor_Coordenada);
    void diagonalDireitaEmBaixo(string** matriz, int tamanho, int &i, int &j,int numeroNivel, int qtdMatriz,vector<Posicao> &vetor_Coordenada);
    void diagonalEsquerdaEmBaixo(string** matriz, int tamanho, int &i, int &j,int numeroNivel, int qtdMatriz,vector<Posicao> &vetor_Coordenada);
    void diagonalDireitaEmCima(string** matriz, int tamanho, int &i, int &j,int numeroNivel, int qtdMatriz,vector<Posicao> &vetor_Coordenada);
    void diagonalEsquerdaEmCima(string** matriz, int &i, int &j,int numeroNivel, int qtdMatriz,vector<Posicao> &vetor_Coordenada);
    void salvar_coordenada(int i, int j, int numeroNivel,int qtdMatriz,vector<Posicao> &vetor_Coordenada);
    void verificadorPortal(string** matriz, int tamanho,int &i, int &j,int inicialLinha,int inicialColuna,int &numeroNivel,int qtdMatriz,vector<Posicao> &vetor_Coordenada);
    void endgame(string**matriz, int tamanho, int numeroNivel, int qtdMatriz, vector<Posicao> &vetor_Coordenada);
    bool contador_Total_CaminhoZero(int qtdMatriz, vector<Posicao> &vetor_Coordenada);
    bool posicao_Bloqueada(string** matriz, int tamanho,int i, int j);
    void salvar_output(string** matriz, int tamanho, int qtdMatriz);
};

#endif