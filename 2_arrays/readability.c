#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int main(void){

	string input = get_string("Texto: ");

	int letras = 0;
	int palavras = 1; // começa em 1 pq a última palavra não tem espaço
	int frases = 0;

	// Conta as letras, palavras e frases
	for(int i = 0, n = strlen(input); i < n; i++){
		char c = input[i];
		if(islower(c) || isupper(c)){ // ou isalpha(c)
			letras++;
		}else if(c == ' '){
			palavras++;
		}else if(c == '.' || c == '!' || c == '?'){
			frases++;
		}

	}

	// media de letras a cada 100 palavras
	float L = letras/ (float) palavras*100;
	// media de palavras a cada 100 frases
	float S = frases/ (float) palavras*100;

	// Índice Coleman Liau para legibilidade
	float index = 0.0588*L - 0.296*S - 15.8;

	if(index < 1){
		printf("Antes da Série 1\n");
	}else if(index > 16){
		printf("Série 16+\n");
	}else{
		printf("Série %f\n", index);
	}

}

