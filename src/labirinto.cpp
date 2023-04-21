#include "labirinto.hpp"

Jogo::Jogo(){
    this->setVida(10);
    this->setSacola(0);
    this->setPontuacao(0);
    this->setPerigo(0);
}

Jogo::Jogo(int vida,int sacola,int pontuacao,int perigo){
    this->setVida(vida);
    this->setSacola(sacola);
    this->setPontuacao(pontuacao);
    this->setPerigo(perigo);
}

void Jogo::setVida(int vida){
    this->vida=vida;
}
int  Jogo::getVida(){
    return this->vida;
}

void Jogo::setSacola(int sacola){
    this->sacola=sacola;
}
int  Jogo::getSacola(){
    return this->sacola;
}

void Jogo::setPontuacao(int pontuacao){
    this->pontuacao=pontuacao;
}
int  Jogo::getPontuacao(){
    return this->pontuacao;
}

void Jogo::setPerigo(int perigo){
    this->perigo=perigo;
}
int Jogo::getPerigo(){
    return this->perigo;
}

int Jogo::lerTamanhoMatriz(){

    ifstream arquivo;
    int contadorLinha=0, contadorEspaco=0, intTamMatriz=0;
    string caractere="", tamMatriz="";

    arquivo.open("dataset/input.data",ios::in);

    if(arquivo.is_open()){
        while(getline(arquivo,caractere)){
            for(int i=0; i<=(int)caractere.size(); i++){
                if(caractere[i]==' '){
                    contadorEspaco++;
                }
                if(caractere[i]=='\0'){
                    contadorLinha++;
                }
                if(contadorLinha==0 && contadorEspaco==0){
                    tamMatriz+=caractere[i];
                }
            }   
        }
        intTamMatriz = atoi(tamMatriz.c_str());
    }

    arquivo.close();
    return intTamMatriz;
}

void Jogo::iniciarMatriz(string** matriz, int tamanho){
    for(int l=0; l<tamanho; l++){
        for(int c=0; c<tamanho; c++){
            matriz[l][c] = "!";
        }
    }
}

void Jogo::imprimirMatriz(string** matriz, int tamanho){

    cout<<endl;

    for(int l=0; l<tamanho; l++){
        for(int c=0; c<tamanho; c++){
            cout<<matriz[l][c]<<" ";
        }
        cout<<endl;
    }

}

void Jogo::salvarMatrizArq(string** matriz, int tamanho, int numeroNivel){

    string pasta="dataset/", numero="", tipo=".data", endereco="";
    ofstream nivel;

    numero = to_string(numeroNivel);
    endereco = pasta+numero+tipo;
    nivel.open(endereco,ios::out);

    if(nivel.is_open()){
        for(int i=0; i<tamanho; i++){
            for(int j=0; j<tamanho; j++){
                nivel<<matriz[i][j]<<" ";
                if(j==(tamanho-1)){
                    nivel<<endl;
                }
            }
        }
        nivel.close();
    }
    else{
        cout<<"\n[E] - Erro na criação de nível - [E]";
    }
    
}

void Jogo::lerMatrizUnica(string** matriz, int tamanho,string endereco){

    ifstream arquivo;
    string caractere="",number="";
    int l=0,c=0;
    arquivo.open(endereco,ios::in);

    iniciarMatriz(matriz, tamanho);

    if(arquivo.is_open()){ 
        while(getline(arquivo,caractere)){
            for(int i=0; i<=(int)caractere.size(); i++){
                if(caractere[i]!='\n' && caractere[i]!= '\0'){
                    if(caractere[i]!=' '){
                        number+=caractere[i];
                    }
                    else{
                        if(matriz[l][c]=="!"){
                            matriz[l][c]=number;
                            c++;
                        }
                        if(c>(tamanho-1)){
                            l++;
                            c=0;
                        }
                        if(matriz[tamanho-1][tamanho-1] != "!"){
                            l=0;
                        }
                        number.clear();
                    }
                }
            }
        }
    }
}

void Jogo::lerTodasMatrizes(string** matriz, int tamanho){

    ifstream arquivo;
    arquivo.open("dataset/input.data",ios::in);
    int cont=0,l=0,c=0,f=0,espaco=0,qtdMatriz=0;
    string caractere="", number="", quantidade="";
    
    iniciarMatriz(matriz, tamanho);

    if(arquivo.is_open()){ 
        while(getline(arquivo,caractere)){
            for(int i=0; i<=(int)caractere.size(); i++){
                if(caractere[i]=='\0'){
                    cont++;
                }
                if(caractere[i]==' '){
                    espaco++;
                }
                if(cont==0 && espaco==2){
                    quantidade+=caractere[i];
                }

                if(cont>=1){
                    qtdMatriz = stoi(quantidade);
                            
                    if(caractere[i]!='\n' && caractere[i]!= '\0'){

                        if(caractere[i]!=' '){
                            number+=caractere[i];
                        }
                        else{
                            if(matriz[l][c]=="!"){
                                matriz[l][c]=number;
                                c++;
                            }
                            if(c>(tamanho-1)){
                                l++;
                                c=0;
                            }
                            if(matriz[tamanho-1][tamanho-1] != "!"){
                                l=0;
                                verificador_Nivel_SemPortal(matriz,tamanho,f);
                                iniciarMatriz(matriz, tamanho);
                            }
                            number.clear();
                        }
                    }
                }
            }
        }
    }
    else{
        cout<<"\n[E] - ERRO - [E]";
    }

    iniciarJogo(matriz,tamanho,0,qtdMatriz);
    
}

void Jogo::verificador_Nivel_SemPortal(string** matriz, int tamanho, int &f){

    int coluna = 0, linha = 0;

    for(int x=0; x<tamanho; x++){
        if(matriz[x][tamanho-1]=="#"){
            coluna ++;
        }
        
        if(matriz[tamanho-1][x]=="#"){
            linha ++;
        }
    }

    if(linha<tamanho || coluna<tamanho){
        salvarMatrizArq(matriz,tamanho,f);
        f++;
    }
}

void Jogo::iniciarJogo(string** matriz, int tamanho, int numeroNivel,int qtdMatriz){

    int i,j;
    int inicialColuna=0, inicialLinha=0;
    bool bloqueado;
    vector<Posicao>vetor_Coordenada;

    vetor_Coordenada.resize(qtdMatriz);

    string pasta="dataset/", numero="", tipo=".data", endereco="";
    numero = to_string(numeroNivel);
    endereco = pasta+numero+tipo;

    lerMatrizUnica(matriz,tamanho,endereco);

    cout<<"\n\t -[START]-"<<endl;
    cout<<"\n [>] Posição i: ";
    cin>>inicialLinha;
    cout<<" [>] Posição j: ";
    cin>>inicialColuna;
    cout<<" [>] - "<<matriz[inicialLinha][inicialColuna];

    i = inicialLinha;
    j = inicialColuna;

    bloqueado = posicao_Bloqueada(matriz,tamanho,i,j);

    if(matriz[i][j]!="#" && bloqueado==0){
        atualizandoJogo(matriz,i,j);
        vetor_Coordenada[numeroNivel].nome = numero;
        vetor_Coordenada[numeroNivel].endereco.push_back({i,j});
        vetor_Coordenada[numeroNivel].endereco_zerados = false;
    }
    else if(matriz[i][j]!="#" && bloqueado==1){
        while(bloqueado==1){
            i = rand()%tamanho;
            j = rand()%tamanho;
            bloqueado = posicao_Bloqueada(matriz,tamanho,i,j);
        }
        atualizandoJogo(matriz,i,j);
        vetor_Coordenada[numeroNivel].nome = numero;
        vetor_Coordenada[numeroNivel].endereco.push_back({i,j});
        vetor_Coordenada[numeroNivel].endereco_zerados = false;
    }
    else{
        while(matriz[i][j]=="#"){
            i = rand()%tamanho;
            j = rand()%tamanho;
        }
        atualizandoJogo(matriz,i,j);
        vetor_Coordenada[numeroNivel].nome = numero;
        vetor_Coordenada[numeroNivel].endereco.push_back({i,j});
        vetor_Coordenada[numeroNivel].endereco_zerados = false;
    }
    iniciarCorrida(matriz,tamanho,i,j,inicialLinha,inicialColuna,numeroNivel,qtdMatriz,vetor_Coordenada);
}

bool Jogo::posicao_Bloqueada(string** matriz, int tamanho,int i, int j){

    bool bloqueado=false;

    if(i==0 && j==0){
        if(matriz[i][j+1]=="#" && matriz[i+1][j]=="#" && matriz[i+1][j+1]=="#"){
            bloqueado = true;
        }
    }
    else if(i>0 && i<(tamanho-1) && j==0){
        if(matriz[i][j+1]=="#" && matriz[i+1][j]=="#" && matriz[i+1][j+1]=="#" && matriz[i-1][j]=="#" && matriz[i-1][j+1]=="#"){
            bloqueado = true;
        }
    }
    else if(i==0 && j>0 && j<(tamanho-1)){
        if(matriz[i][j-1]=="#" && matriz[i][j+1]=="#" && matriz[i+1][j]=="#" && matriz[i+1][j+1]=="#" && matriz[i+1][j-1]=="#"){
            bloqueado = true;
        }
    }
    else if(i>0 && i<(tamanho-1) && j>0 && j<(tamanho-1)){
        if(matriz[i][j-1]=="#" && matriz[i-1][j-1]=="#" && matriz[i-1][j]=="#" && matriz[i-1][j+1]=="#" && matriz[i][j+1]=="#" && matriz[i+1][j+1]=="#" && matriz[i+1][j]=="#" && matriz[i+1][j-1]=="#"){
            bloqueado = true;
        }
    }
    return bloqueado;    
}

void Jogo::iniciarCorrida(string** matriz, int tamanho,int i, int j,int inicialLinha,int inicialColuna, int numeroNivel,int qtdMatriz,vector<Posicao> &vetor_Coordenada){

    int sorteio=0,gameOver=0;
    bool caminhos_Zeros=false;
    string pasta="dataset/", numero="", tipo=".data", endereco="";

    numero = to_string(numeroNivel);
    endereco = pasta+numero+tipo;
    srand(42);  

    while(gameOver!=1){

        caminhos_Zeros = contador_Total_CaminhoZero(qtdMatriz,vetor_Coordenada);

        if(getVida()==0 || caminhos_Zeros == true){
            cout<<endl;
            imprimirVida();
            endgame(matriz,tamanho,numeroNivel,qtdMatriz,vetor_Coordenada);
            if(getVida()==0){
                cout<<"\n\t[RIP]---[VOCÊ MORREU]---[RIP]\n\n";
            }
            else{
                cout<<"\n\n\t[GG]---[VOCÊ GANHOU]---[GG]\n\n";
            }
            salvar_output(matriz, tamanho, qtdMatriz);
            gameOver=1;
        }
        else{
            sorteio = rand()%8+1;
            if(i==(tamanho-1)){
                if(sorteio==3 || sorteio==7 || sorteio==8){
                    verificadorPortal(matriz,tamanho,i,j,inicialLinha,inicialColuna,numeroNivel,qtdMatriz,vetor_Coordenada);
                    sorteio = rand()%8+1;
                }
            }
            //verificar portal ultima coluna...
            else if(j==(tamanho-1)){
                if(sorteio==1 || sorteio==5 || sorteio==7){
                    verificadorPortal(matriz,tamanho,i,j,inicialLinha,inicialColuna,numeroNivel,qtdMatriz,vetor_Coordenada);
                    sorteio = rand()%8+1;
                }
            }
            caminhos_Zeros = contador_Total_CaminhoZero(qtdMatriz,vetor_Coordenada);
            if(caminhos_Zeros!=true){
                andar_dpsSorteio(matriz,tamanho,i,j,numeroNivel,qtdMatriz,vetor_Coordenada,sorteio); 
            } 
        }
    }
}

bool Jogo::contador_Total_CaminhoZero(int qtdMatriz, vector<Posicao> &vetor_Coordenada){

    bool validacao;

    for(int x=0; x<qtdMatriz; x++){
        if(vetor_Coordenada[x].endereco_zerados == true){
            validacao = true;
        }
        else{
            validacao = false;
            break;
        }
    }
    return validacao;
}

void Jogo::conferir_CaminhoZero(string** matriz,int tamanho,int numeroNivel,vector<Posicao> &vetor_Coordenada){

    string pasta="dataset/", numero="", tipo=".data", endereco="";
    bool fim_LerMatriz = true;
    int aux=0,x,y,size;

    numero = to_string(numeroNivel);
    endereco = pasta+numero+tipo;
    size = vetor_Coordenada[numeroNivel].endereco.size();

    lerMatrizUnica(matriz,tamanho,endereco);

    while(fim_LerMatriz){

        x = vetor_Coordenada[numeroNivel].endereco[aux].first;
        y = vetor_Coordenada[numeroNivel].endereco[aux].second;

        if(matriz[x][y]=="0" || matriz[x][y]=="#" || matriz[x][y]=="*"){
            if(aux < size){
                aux++;
            }
            else{
                vetor_Coordenada[numeroNivel].endereco_zerados = true;
                fim_LerMatriz = false;
            }
        }
        else{
            vetor_Coordenada[numeroNivel].endereco_zerados = false;
            fim_LerMatriz = false;

        }
    }
}

void Jogo::verificadorPortal(string** matriz, int tamanho,int &i, int &j,int inicialLinha,int inicialColuna,int &numeroNivel,int qtdMatriz,vector<Posicao> &vetor_Coordenada){
    
    string pasta="dataset/", numero="", tipo=".data", endereco="";
    bool bloqueado = false;

    salvarMatrizArq(matriz,tamanho,numeroNivel);
    conferir_CaminhoZero(matriz,tamanho,numeroNivel,vetor_Coordenada);
    
    if(numeroNivel<(qtdMatriz-1)){

        numeroNivel++;
        numero = to_string(numeroNivel);
        endereco = pasta+numero+tipo;
        lerMatrizUnica(matriz,tamanho,endereco);

        vetor_Coordenada[numeroNivel].nome = numero;

        i=inicialLinha;
        j=inicialColuna;
        bloqueado = posicao_Bloqueada(matriz,tamanho,i,j);

        if(matriz[i][j]=="#" && bloqueado==0){
            while(matriz[i][j]=="#"){
                i = rand()%tamanho;
                j = rand()%tamanho;
            }
            atualizandoJogo(matriz,i,j);
            salvar_coordenada(i,j,numeroNivel,qtdMatriz,vetor_Coordenada);
        }
        if(matriz[i][j]!="#" && bloqueado==1){
            while(bloqueado==1){
                i = rand()%tamanho;
                j = rand()%tamanho;
                bloqueado = posicao_Bloqueada(matriz,tamanho,i,j);
            }
            atualizandoJogo(matriz,i,j);
            salvar_coordenada(i,j,numeroNivel,qtdMatriz,vetor_Coordenada);
        }
        else{
            atualizandoJogo(matriz,i,j);
            salvar_coordenada(i,j,numeroNivel,qtdMatriz,vetor_Coordenada);
        }
    }
    else{
        numeroNivel=0;
        i=inicialLinha;
        j=inicialColuna;
        numero = to_string(numeroNivel);
        endereco = pasta+numero+tipo;
        lerMatrizUnica(matriz,tamanho,endereco);
    }                
}

void Jogo::andar_dpsSorteio(string** matriz, int tamanho,int &i, int &j, int numeroNivel,int qtdMatriz,vector<Posicao> &vetor_Coordenada,int sorteio){
    //direita
    if(sorteio==1){
        direita(matriz,tamanho,i,j,numeroNivel,qtdMatriz,vetor_Coordenada);
    }
    //esquerda
    else if(sorteio==2){
        esquerda(matriz,i,j,numeroNivel,qtdMatriz,vetor_Coordenada);
    }
    //baixo
    else if(sorteio==3){
        baixo(matriz,tamanho,i,j,numeroNivel,qtdMatriz,vetor_Coordenada);
    }
    //em cima
    else if(sorteio==4){
        emCima(matriz,i,j,numeroNivel,qtdMatriz,vetor_Coordenada);
    }
    //diagonal direita em cima
    else if(sorteio==5){
        diagonalDireitaEmCima(matriz,tamanho,i,j,numeroNivel,qtdMatriz,vetor_Coordenada);
    }
    //diagonal esquerda em cima
    else if(sorteio==6){
        diagonalEsquerdaEmCima(matriz,i,j,numeroNivel,qtdMatriz,vetor_Coordenada);
    }
    //diagonal direita embaixo
    else if(sorteio==7){
        diagonalDireitaEmBaixo(matriz,tamanho,i,j,numeroNivel,qtdMatriz,vetor_Coordenada);
    }
    //diagonal esquerda embaixo
    else if(sorteio==8){
        diagonalEsquerdaEmBaixo(matriz,tamanho,i,j,numeroNivel,qtdMatriz,vetor_Coordenada);
    }
}

void Jogo::atualizandoJogo(string** matriz,int &i, int &j){
    
    int valorPosicao=0;

    if(matriz[i][j]!="*"){
        valorPosicao = atoi(matriz[i][j].c_str());

        if(valorPosicao>0){

            setPontuacao(getPontuacao()+1);
            valorPosicao -= 1;
            matriz[i][j]= to_string(valorPosicao);

            if(getSacola()+1<4){
                setSacola(getSacola()+1);
            }
            else if(getSacola()+1==4){
                if(getVida()<10){
                    setVida(getVida()+1);
                    setSacola(0);
                }
                else{
                    setSacola(0);
                }
            }
        }
    }
    else{
        setVida(getVida()-1);
        setPerigo(getPerigo()+1);
    }
}

void Jogo::salvar_coordenada(int i, int j, int numeroNivel,int qtdMatriz,vector<Posicao> &vetor_Coordenada){

    string aux_Nome;
    bool controle;
    int posicao_Matriz,size;

    aux_Nome = to_string(numeroNivel);

    for(int c=0; c<qtdMatriz; c++){
        if(vetor_Coordenada[c].nome == aux_Nome){
            posicao_Matriz = c;
            size = vetor_Coordenada[posicao_Matriz].endereco.size();
            break;
        }
    }

    for(int k=0; k<size; k++){
        if(vetor_Coordenada[posicao_Matriz].endereco[k].first == i && vetor_Coordenada[posicao_Matriz].endereco[k].second == j){
            controle = true;
        }
    }

    if(!controle){
        vetor_Coordenada[numeroNivel].endereco.push_back({i,j});
    }
}

void Jogo::direita(string** matriz, int tamanho,int &i, int &j,int numeroNivel, int qtdMatriz,vector<Posicao> &vetor_Coordenada){
    if(j<(tamanho-1)){
        if(matriz[i][j+1]!="#"){
            j++;
            atualizandoJogo(matriz,i,j);
            salvar_coordenada(i,j,numeroNivel,qtdMatriz,vetor_Coordenada);
        }
    }
}

void Jogo::diagonalDireitaEmBaixo(string** matriz, int tamanho,int &i, int &j,int numeroNivel, int qtdMatriz,vector<Posicao> &vetor_Coordenada){
    if(i<(tamanho-1) && (j<tamanho-1)){
        if(matriz[i+1][j+1]!="#"){
            i++;
            j++;
            atualizandoJogo(matriz,i,j);
            salvar_coordenada(i,j,numeroNivel,qtdMatriz,vetor_Coordenada);
        }
    }
}

void Jogo::diagonalDireitaEmCima(string** matriz, int tamanho,int &i, int &j,int numeroNivel, int qtdMatriz,vector<Posicao> &vetor_Coordenada){
    if(i>0 && j<(tamanho-1)){
        if(matriz[i-1][j+1]!="#"){
            i--;
            j++;
            atualizandoJogo(matriz,i,j);        
            salvar_coordenada(i,j,numeroNivel,qtdMatriz,vetor_Coordenada);
        }
    }
}

void Jogo::diagonalEsquerdaEmCima(string** matriz,int &i, int &j,int numeroNivel, int qtdMatriz,vector<Posicao> &vetor_Coordenada){
    if(i>0 && j>0){
        if(matriz[i-1][j-1]!="#"){
            i--;
            j--;
            atualizandoJogo(matriz,i,j);
            salvar_coordenada(i,j,numeroNivel,qtdMatriz,vetor_Coordenada);
        }
    }
}

void Jogo::diagonalEsquerdaEmBaixo(string** matriz, int tamanho,int &i, int &j,int numeroNivel, int qtdMatriz,vector<Posicao> &vetor_Coordenada){
    if((i<tamanho-1) && (j>0)){
        if(matriz[i+1][j-1]!="#"){
            i++;
            j--;
            atualizandoJogo(matriz,i,j);
            salvar_coordenada(i,j,numeroNivel,qtdMatriz,vetor_Coordenada);
        }
    }
}

void Jogo::esquerda(string** matriz,int &i, int &j,int numeroNivel, int qtdMatriz,vector<Posicao> &vetor_Coordenada){
    if(j>0){
        if(matriz[i][j-1]!="#"){
            j--;
            atualizandoJogo(matriz,i,j);
            salvar_coordenada(i,j,numeroNivel,qtdMatriz,vetor_Coordenada);
        }
    }
}

void Jogo::baixo(string** matriz, int tamanho,int &i, int &j,int numeroNivel, int qtdMatriz,vector<Posicao> &vetor_Coordenada){
    if(i<tamanho){
        if(matriz[i+1][j]!="#"){
            i++;
            atualizandoJogo(matriz,i,j);
            salvar_coordenada(i,j,numeroNivel,qtdMatriz,vetor_Coordenada);
        }
    }
}

void Jogo::emCima(string** matriz, int &i, int &j,int numeroNivel, int qtdMatriz,vector<Posicao> &vetor_Coordenada){
    if(i>0){
        if(matriz[i-1][j]!="#"){
            i--;
            atualizandoJogo(matriz,i,j);
            salvar_coordenada(i,j,numeroNivel,qtdMatriz,vetor_Coordenada);
        }
    }
}

void Jogo::endgame(string**matriz, int tamanho, int numeroNivel, int qtdMatriz, vector<Posicao> &vetor_Coordenada){

    int caminhoFeitos_total=0,size,caminhosNOT_feitos=0;

    size = vetor_Coordenada.size();

    salvarMatrizArq(matriz,tamanho,numeroNivel);

    for(int x=0; x<size; x++){
        caminhoFeitos_total+=vetor_Coordenada[x].endereco.size();
    }

    caminhosNOT_feitos = pow(tamanho,2)*qtdMatriz - caminhoFeitos_total;

    cout<<"\n\n\t  ---[RESULTADO]---";
    cout<<"\n\n [N] Nível parada = "<<numeroNivel;
    cout<<"\n [+] Qtd.Nível explorado = "<<vetor_Coordenada.size();
    cout<<"\n [!] Perigos = "<<getPerigo();
    cout<<"\n [C] Caminhos feitos = "<<caminhoFeitos_total;
    cout<<"\n [C] Caminhos não feitos = "<<caminhosNOT_feitos;
    cout<<"\n [*] Pontuação = "<<getPontuacao()<<endl;
}

void Jogo::imprimir_posicoes(int numeroNivel,vector<Posicao> &vetor_Coordenada){

    int size;
    int p1,p2;

    size = vetor_Coordenada[numeroNivel].endereco.size();

    for(int c=0; c<size; c++){
        p1 = vetor_Coordenada[numeroNivel].endereco[c].first;
        p2 = vetor_Coordenada[numeroNivel].endereco[c].second;
        cout<<" \n("<<p1<<","<<p2<<")";
    }
}

void Jogo::imprimirVida(){
    int cont=0;
    string Vida="";

    for(int i=0; i<10; i++){
        if(cont<getVida()){
            Vida+="=";
            cont++;
        }
        else{
            Vida+=" ";

        }
    }
    cout<<"\n\t Vida ["<<Vida<<"]  "<<getVida();
}

void Jogo::salvar_output(string** matriz, int tamanho, int qtdMatriz){

    ifstream niveis;
    ofstream output;

    string endereco_Output="dataset/output.data";
    string endereco="",pasta = "dataset/", numero ="", tipo = ".data";

    output.open(endereco_Output,ios::out);
  
    for(int x=0; x<qtdMatriz; x++){
        if(output.is_open()){

            numero = to_string(x);
            endereco = pasta+numero+tipo;
            lerMatrizUnica(matriz,tamanho,endereco);

            for(int i=0; i<=tamanho; i++){
                if(i<tamanho){
                    for(int j=0; j<tamanho; j++){
                    output<<matriz[i][j]<<" ";
                        if(j==(tamanho-1)){
                            output<<endl;
                        }
                    }
                }
                else if(i==tamanho){
                    output<<endl;
                }
                
            }
            const char* remover = endereco.c_str();
            remove(remover);
            endereco.clear();
        }
        else{
            cout<<"\n[E] - Erro na criação de nível - [E]";
        }
    }
}
