#include "helpers.h"
#include "math.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i ++){
        for(int j = 0; j < width; j++){

            int vermelho = image[i][j].rgbtRed;
            int verde = image[i][j].rgbtGreen;
            int azul = image[i][j].rgbtBlue;

            int media = round((vermelho+verde+azul)/3.0);

            image[i][j].rgbtRed = media;
            image[i][j].rgbtGreen = media;
            image[i][j].rgbtBlue = media;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
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

    for(int i = 0; i < height; i ++){
        for(int j = 0; j < true_width/2; j++){

            tmp[i][j] = image[i][j];
            image[i][j] = image[i][width - j -1];
            image[i][width - j - 1] = tmp[i][j];

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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{

    // Matrizes do Sistema Sobel
    int gx [3][3]= {{-1, 0, 1},
              {-2, 0, 2},
              {-1, 0, 1}};

    int gy [3][3]= {{-1, -2, -1},
              {0, 0, 0},
              {1, 2, 1}};

    // Cópia da matriz para não alterar a original
    RGBTRIPLE copy[height][width];
    for(int i =0; i< height; i++){
        for(int j = 0; j < width; j++){
            copy[i][j] = image[i][j];
        }
    }

    // Para cada índice
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){

            // valores que multiplicam pela matriz gx e gy
            float vermelhoX = 0, verdeX = 0, azulX = 0;
            float vermelhoY = 0, verdeY = 0, azulY = 0;
            // total final
            float totalVermelho, totalVerde, totalAzul;

            // Acessa a matriz 3x3 em volta de cada pixel
            for(int x = -1; x <= 1; x++){
                for(int y = -1; y <= 1; y++){

                    int posicaoX = i + x;
                    int posicaoY = j + y;

                    // Se estiver dentro da imagem
                    if(posicaoX >= 0 && posicaoX < height && posicaoY >= 0 && posicaoY < width ){

                        // Armazena os valores RGB com o cálculo de sobel
                        vermelhoX += copy[posicaoX][posicaoY].rgbtRed * gx[x + 1][y + 1];
                        vermelhoY += copy[posicaoX][posicaoY].rgbtRed * gy[x + 1][y + 1];

                        verdeX += copy[posicaoX][posicaoY].rgbtGreen * gx[x + 1][y + 1];
                        verdeY += copy[posicaoX][posicaoY].rgbtGreen * gy[x + 1][y + 1];

                        azulX += copy[posicaoX][posicaoY].rgbtBlue * gx[x + 1][y + 1];
                        azulY += copy[posicaoX][posicaoY].rgbtBlue * gy[x + 1][y + 1];
                    }
                }
            }

            // Armazena o valor totral com o cálculo de sobel
            totalVermelho = round(sqrt(vermelhoX * vermelhoX + vermelhoY * vermelhoY));
            totalVerde = round(sqrt(verdeX * verdeX + verdeY * verdeY));
            totalAzul = round(sqrt(azulX * azulX + azulY * azulY));

            // Verifica se é ou não maior que 255 para definir o valor RGB do pixel da imagem original
            image[i][j].rgbtRed = (totalVermelho > 255) ? 255 : totalVermelho;
            image[i][j].rgbtGreen = (totalVerde > 255) ? 255 : totalVerde;
            image[i][j].rgbtBlue = (totalAzul > 255) ? 255 : totalAzul;
        }
    }
    return;
}
