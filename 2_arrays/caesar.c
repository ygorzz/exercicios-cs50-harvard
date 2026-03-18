#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, string argv[]){

    int key;

    // Se tiver um argumento de linha de comando
    if(argc == 2){

        // Verifica se p-o argumento é um número
        for(int i=0, n = strlen(argv[1]); i < n; i++){
            char c = argv[1][i];

            if(!isdigit(c)){ //Se o argumento for diferente de um dígito
                printf("Usage: ./cesar key\n");
                return 1;
            }
        }

        key = atoi(argv[1]); // converte string em int

    }else{
        printf("Aceitamos apenas 1 comando como argumento.\n");
        return 1;
    }

    string plaintext = get_string("Plaintext: ");

    printf("Ciphertext: ");

    // Algoritmo de César:
    char c3;
    for(int i=0, n=strlen(plaintext); i < n; i++){

        char c = plaintext[i];

        // Criptografa o caracter
        if(isalpha(c)){

            if(islower(c)){
                int c2 = c - 'a';

                int ci = (c2 + key) % 26;

                c3 = ci + 'a';
                printf("%c", c3);
            }else{
                int c2 = c - 'A';

                int ci = (c2 + key) % 26;

                c3 = ci + 'A';
                printf("%c", c3);
            }
        }else{
            printf("%c", c);
        }
    }
    printf("\n");
    return 0;
}
