#include "helpers.h"
#include "math.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{

    // Percorre cada bit da imagem
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {

            // Faz a média das cores RGB
            float media = round(
                ((float) image[i][j].rgbtRed + image[i][j].rgbtBlue + image[i][j].rgbtGreen) / 3);

            // Aplica a grayscale
            image[i][j].rgbtRed = media;
            image[i][j].rgbtBlue = media;
            image[i][j].rgbtGreen = media;
        }
    }

    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {

            float sepiaRed = round(.393*(float) image[i][j].rgbtRed + .769*image[i][j].rgbtGreen + .189*image[i][j].rgbtBlue);
            if (sepiaRed > 255){
                sepiaRed = 255;
            }

            float sepiaGreen = round(.349*(float) image[i][j].rgbtRed + .686*image[i][j].rgbtGreen +.168*image[i][j].rgbtBlue);
            if (sepiaGreen > 255) {
                sepiaGreen = 255;
            }

            float sepiaBlue = round(.272*(float) image[i][j].rgbtRed + .534*image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);
            if (sepiaBlue > 255){
                sepiaBlue = 255;
            }

            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Array para armazenar e auxiliar nas trocas de posições
    RGBTRIPLE tmp[height][width];

    int true_width = 0;

    // Verifica largura
    if (width % 2 == 0)
    {
        true_width = width;
    }
    else
    {
        true_width = width + 1;
    }

    // Toca as posições
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < true_width / 2; j++)
        {

            tmp[i][j] = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = tmp[i][j];
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{

        // Cópia para modificar
        RGBTRIPLE copy[height][width];
        for(int i = 0; i < height; i++){
            for(int j = 0; j < width; j++){
                copy[i][j] = image[i][j];
            }
        }

        // Percorre cada pixel
        for(int i = 0; i < height; i++){
            for(int j = 0; j < width; j++){

                int totalVermelho = 0;
                int totalVerde = 0;
                int totalAzul = 0;
                float counter = 0;

                // Percore uma matriz 3x3 - os pixels em volta
                for(int x = -1; x <= 1; x++){
                    for(int y = -1; y <= 1; y++){

                        int posicaoX = i + x;
                        int posicaoY = j + y;

                        // Verifica se esta nos limites da matriz
                        if(posicaoX >= 0 && posicaoX < height && posicaoY >= 0 && posicaoY < width){

                            // Armazena o total de cada cor da matriz 3x3
                            totalVermelho += copy[posicaoX][posicaoY].rgbtRed;
                            totalVerde += copy[posicaoX][posicaoY].rgbtGreen;
                            totalAzul += copy[posicaoX][posicaoY].rgbtBlue;
                        // Conta quantos pixels foram para dividir - para n dar erro com os pixels da borda
                            counter++;
                        }
                    }
                }

                // Faz a média e armazena na imagem original
                image[i][j].rgbtRed = round(totalVermelho/counter);
                image[i][j].rgbtGreen = round(totalVerde/counter);
                image[i][j].rgbtBlue = round(totalAzul/counter);

            }
        }
    return;
}
