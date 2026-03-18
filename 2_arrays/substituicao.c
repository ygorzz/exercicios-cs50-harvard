#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Protótipo de função
int verificaArgumento(string texto);

int main(int argc, string argv[])
{
    if (argc == 2){
        if(verificaArgumento(argv[1]) == 1){ // Se o retorno da função for 1 o programa é cancelado
            return 1;
        }
    }else{
        printf("É necessário um único e apenas um argumento.\n");
        return 1;
    }

    string plaintext = get_string("Texto simples: ");

    printf("Texto cifrado: ");

    int posicao;
    int ciphertext;
    for(int i = 0, n = strlen(plaintext); i < n; i++){
        char c = plaintext[i];
        if(islower(c)){
            // armazena a posição codo caracter
            posicao = c - 'a';
            // cifra o carcater de acordo com o caracter do argumento correspondente
            ciphertext = tolower(argv[1][posicao]);
            printf("%c", ciphertext);
        }else if(isupper(c)){
            posicao = c - 'A';
            ciphertext = toupper(argv[1][posicao]);
            printf("%c", ciphertext);
        }else{
            printf("%c", c);
        }

    }
    printf("\n");
}

int verificaArgumento(string texto){

    int n = strlen(texto);

    // Verifica se o exto de 26 caracteres
    if(n != 26){
        printf("O argumento deve ter 26 caracteres.\n");
        return 1;
    }

    // Vetor para armazenar os caracteres ja vistos e verificar se os mesmos repetem
    int frequencia[26] = {0};

    for(int i = 0; i < n; i++){
        char c = texto[i];

        // Verifica se é alfabético
        if(!isalpha(c)){
            printf("Todos os caracteres devem ser alfabéticos.\n");
            return 1;
        }

        // Passa para letra maiúscula para padronizar, já que o objetivo é apenas achar a posição.
        char c_upper = toupper(c);

        // Armazena a posição do caracter
        int posicao = c_upper - 'A';

        // Verifica se o caracter ja foi visto
        if(frequencia[posicao] == 1){
            printf("Os caracteres não podem ser repetidos.\n");
            return 1;
        }
        // Marca o caracter como visto
        frequencia[posicao] = 1;
    }
    return 0;
}
