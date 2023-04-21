#include "labirinto.hpp"
#include <chrono>

int main(){
    
    int tamanho;
    Jogo j1;
    string **matriz;
    
    tamanho = j1.lerTamanhoMatriz();

    matriz = new string*[tamanho];
    for (int i=0; i<tamanho; i++){
        matriz[i] = new string[tamanho];
    }

    j1.lerTodasMatrizes(matriz,tamanho);

    return 0;
}
