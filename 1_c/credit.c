#include <cs50.h>
#include <stdio.h>

int main(void)
{
    printf("Quer saber qual a bandeira do seu cartão?\n");
    long numCartao = get_long("Digite o númmero do cartão: ");

    long copia = numCartao;
    int numDigitos = 0;
    int soma = 0;
    int somaProduto = 0;

    // CHECKSUM
    while (copia > 0)
    {

        // Pega cada dígito do número
        int digito = copia % 10;

        // Verifica se o dígito está na posição par ou ímpar de acordo com o contador
        // par = primeiros digitos / ímpar = segundos dígitos
        if (numDigitos % 2 == 0)
        {
            soma += digito;
        }
        else
        {
            int produto = digito * 2;
            somaProduto += (produto / 10) + (produto % 10);
        }

        // Atualiza o valor de copia para recomeçar o loop
        copia /= 10;
        numDigitos++;
    }

    int somaTotal = soma + somaProduto;

    // Verifica se passou no CHECKSUM - retorna true or false
    bool valido = (somaTotal % 10 == 0);

    // Pega os dois primeiros dígitos para American expresss e Mastercard
    long doisPrimeiros = numCartao;
    while (doisPrimeiros >= 100)
    {
        doisPrimeiros /= 10;
    }

    // Pega o primeiro numero para Visa
    long primeiroDigito = numCartao;
    while (primeiroDigito > 10)
    {
        primeiroDigito /= 10;
    }

    // Verifica qual a bandeira do cartão
    if (valido){

        if (numDigitos == 15 && (doisPrimeiros == 34 || doisPrimeiros == 37)){
            printf("AMERICAN ESPRESS\n");

        }else if (numDigitos == 16 && doisPrimeiros >= 51 && doisPrimeiros <= 55 ){
            printf("MASTERCARD\n");
        }else if(numDigitos >= 13 && numDigitos <= 16 && primeiroDigito == 4){
            printf("VISA\n");
        }else{
            printf("INVÁLIDO\n");
        }
    }
}
