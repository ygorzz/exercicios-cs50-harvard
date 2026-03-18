// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]); // atof -> string para float

    // Array header, uint8_t -> 1byte
    uint8_t header[HEADER_SIZE];
    // Lê 44 bytes do file input e armazena no endereço de header
    fread(&header, sizeof(uint8_t), 44, input);
    // Escreve no file output os 44 bytes que estão no endereço de header
    fwrite(&header, sizeof(uint8_t), 44, output);

    // APÓS ISSO, O CURSOR ESTÁ PARADO NAS AMOSTRAS LOGO APÓS OS 44 BYTES

    // Variável buffer de 2 bytes
    int16_t buffer;
    // fread retorna o num de elementos lidos
    // Então, enquanto tiver elementos para serem lidos:
    while(fread(&buffer, sizeof(int16_t), 1, input)){ // Lê 1 amostra de 2 bytes do arquivo input e armazena no endereço de buffer
        buffer = buffer*factor;
        // Escreve no file output a amostra de 2 bytes que está no endereço de buffer.
        fwrite(&buffer, sizeof(int16_t), 1, output);
    }
    // Close files
    fclose(input);
    fclose(output);
}
