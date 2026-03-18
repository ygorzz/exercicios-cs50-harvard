#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

// Vetor de pontos
int pontos[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

// Protótipo da função
int calcularPontos(string palavra);

int main(void)
{

    string palavra1 = get_string("Player 1: ");
    string palavra2 = get_string("Player 2: ");

    // Chamadas da função
    int pontuacao1 = calcularPontos(palavra1);
    int pontuacao2 = calcularPontos(palavra2);

    if(pontuacao1 > pontuacao2){
        printf("Player 1 wins!\n");
    }else if(pontuacao2 > pontuacao1){
        printf("Player 2 wins!\n");
    }else{
        printf("Tie!\n");
    }

}

int calcularPontos(string palavra){ // precisa de uma string como parâmetro

    int soma = 0;
    for(int i = 0, n = strlen(palavra); i < n; i++){ // percorre caractere por caractere da palavra

        if(islower(palavra[i])){
            int posicao = palavra[i] - 'a'; // subtrai o valor numérico do caractere pelo valor de 'a' e encontra a posição do caractere
            soma += pontos[posicao]; // acessa o vetor na posição do caractere e atribui o valor referente a posição

        }else if(isupper(palavra[i])){
            int posicao = palavra[i] - 'A';
            soma += pontos[posicao];
        }
    }
    return soma;
}

