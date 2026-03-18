    #include <stdio.h>
    #include <cs50.h>

    int main(void){

        int altura;
        do{
            altura = get_int("Escolha a altura da escada: ");
        }
        while(altura<1 || altura>8);

        // Implementa as linhas
        for(int i = 0; i<altura; i++){

            // Implementa os espaços na primeira parte da piramide
            for(int k = 0; k<altura-i; k++){
                printf(" ");
            }

            // Cria a primeira parte
            for(int j = 0; j<=i; j++){ //j<=i -> implementa a qtd de # de acordo com o num da linha
                printf("#");
            }
            // Espaço entre as partes
            printf("  ");
            // Cria a segunda parte
            for(int l=0;l<=i;l++){
                printf("#");
            }
            printf("\n");

        }
    }
