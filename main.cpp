#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "Pilha.h"

using namespace std;

int verificaExpressao(char operacao[100] , char colcheteA, char colcheteF, char parenteseA, char parenteseF){
    Pilha_Construtor();
    char simbolos[] = {colcheteA, colcheteF, parenteseA, parenteseF};

    int p = 0;

    //se o caracter da operacao for igual a um dos sinais graficos, empilha na pilha
    while(operacao[p]!= '\0'){
        for(int o=0; o<4; o++){
            if(operacao[p]==simbolos[o]){
                Pilha_Empilhar(operacao[p]);
            }
        }
        p++;
    }

    //se nao houver nenhum sinal grafico, ja retorna como true
    if(Pilha_Tamanho()==0){
        return 1;
    }

    int validaC = 0, validaP = 0; // indica que nao ha sinal grafico aberto

    while(Pilha_Tamanho()!=0){
        if(Pilha_Topo(operacao[p])){
            //testo se o caracter eh um ], se for, salvo pela variavel de controle validaC
            if(operacao[p] == colcheteF && !validaC){
                Pilha_Desempilhar(operacao[p]);
                Pilha_Topo(operacao[p]);
                validaC = 1;
            }else if(validaC && operacao[p] == colcheteF){ //caso a pessoa digite 2 colchetes em seguida "]]"
                return 0;
            }

            //testo se o caracter eh um ), se sim, salvo com a variavel de controle validaP
            if(operacao[p] == parenteseF){
                Pilha_Desempilhar(operacao[p]);
                Pilha_Topo(operacao[p]);
                validaP = 1;
            }

            //testo se o proximo ja eh o (, se sim, transformo a variavel indicando que o parentese que foi aberto ja esta fechado
            if(operacao[p] == parenteseA && validaP){
                Pilha_Desempilhar(operacao[p]);
                Pilha_Topo(operacao[p]);
                validaP = 0;
            }else if(operacao[p] != parenteseA && validaP){ //se existe o ')' e esse nao eh o '(', ja retorna false
                return 0;
            }else if(operacao[p] == parenteseA && !validaP){ //se o parentese for '(' e o ')' nao existir, ja retorna false
                return 0;
            }

            //testo se o colchete se fecha
            if(operacao[p] == colcheteA && validaC){
                Pilha_Desempilhar(operacao[p]);
                Pilha_Topo(operacao[p]);
                validaC = 0;
            }else if(operacao[p] == colcheteA && !validaC){ // se for [ e nao existir o ], ja retorna false
                return 0;
            }
        }
    }

    if(validaC == 1 || validaP == 1){ //se sair do while e algum sinal grafico estiver sem seu par retorna false
        return 0;
    }

    return 1; //se passar por tudo e estiver ok, chega aqui e retorna true;
}

int main(){

    char operacao[100];

    cout << "Digite a operacao: ";
    cin >> operacao;

    if(verificaExpressao(operacao, '[', ']', '(', ')')){
        cout << "\nOperacao valida!\n";
    }else{
        cout << "\nOperacao invalida\n";
    }
}
