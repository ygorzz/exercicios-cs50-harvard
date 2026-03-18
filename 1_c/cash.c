#include <cs50.h>
#include <math.h>
#include <stdio.h>

int main(void)
{

    float troco;

    do
    {
        troco = get_float("Digite o troco necessário: ");
    }
    while (troco <= 0);

    // Coverte para centavos
    int centavos = round(troco * 100); // round() -> arredonda valores que tem as ultimas casas decimais quebradas para o int +proximo
    printf("Troco para %i centavos: \n", centavos);

    // Quantidade de moedas de 25
    int vinteCinco = 0;
    while (centavos >= 25)
    {
        centavos -= 25;
        vinteCinco++;
    }
    printf("   Moedas de 25: %i\n", vinteCinco);

    // Quantidade de moedas de 10
    int dez = 0;
    while (centavos >= 10)
    {
        centavos -= 10;
        dez++;
    }
    printf("   Moedas de 10: %i\n", dez);

    // Quantidade de moedas de 5
    int cinco = 0;
    while (centavos >= 5)
    {
        centavos -= 5;
        cinco++;
    }
    printf("   Moedas de 5: %i\n", cinco);

    // Quantidade de moedas de 1
    int um = 0;
    while (centavos >= 1)
    {
        centavos -= 1;
        um++;
    }
    printf("   Moedas de 1: %i\n", um);
}
