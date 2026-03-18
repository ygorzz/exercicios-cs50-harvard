#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void){

    long populacaoInicial;
    do{
        populacaoInicial = get_long("População inical de lhamas (mínimo 9): ");
    }
    while(populacaoInicial < 9);

    long populacaoFinal;
    do{
        populacaoFinal = get_long("População final de lhamas (deve ser maior que a inicial): ");
    }
    while(populacaoFinal <= populacaoInicial);

    int anos = 0;
    int populacaoAtual = populacaoInicial;

    while(populacaoAtual < populacaoFinal){

        int nascimento = populacaoAtual/3;
        int morte = populacaoAtual/4;

        populacaoAtual += nascimento - morte;

        anos++;

    }

    printf("%i\n", anos);
}
