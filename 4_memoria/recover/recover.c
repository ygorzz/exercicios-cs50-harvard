#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    // Verifica a quantidade de argumentos
    if(argc != 2){
        printf("Uso: ./recover imagem\n");
        return 1;
    }

    // Abre o arquivo passado como argumento
    FILE *file = fopen(argv[1], "r");

    // Verifica se conseguiu abrir
    if(!file){
        printf("Não foi possível abrir o arquivo.\n");
        return 1;
    }

    uint8_t bytes[512]; // vetor para armazenar cada bloco de 512 bytes
    int counter = 0;  // contador para numerar os nomes dos arquivos
    char filename[8]; //vetor para armazenar os nomes dos arquivos

    // Inicializa o arquivo vazio
    FILE *jpeg = NULL;

    // Enquanto houver elementos a serem lidos
    // Lê 512 bytes de file e armazena em bytes
    while(fread(bytes, sizeof(uint8_t), 512, file)){

        // Se é o inicio de um novo jpeg
        if(bytes[0] == 0xff && bytes[1] == 0xd8 && bytes[2] == 0xff && (bytes[3] & 0xf0) == 0xe0){

            // Se já existir um arquivo aberto
            if(jpeg != NULL){
                fclose(jpeg);
            }

            // sprintf(onde vai ser armazenado, a string a ser armazenada)
            // %03 -> 3 valores vão ser preenchidos a esquerda e preenche espaços vazios com zeros
            sprintf(filename, "%03i.jpg", counter); // Define o nome do arquivo
            // Abre/cria o arquivo
            jpeg = fopen(filename, "w");

            // Verifica se foi possível abrir o arquivo
            if(!jpeg){
                printf("Não foi possível abrir/criar o arquivo\n");
                return 1;
            }

            // itera o counter para mudar o nome do proximo arquivo
            counter++;
        }

        // Se tem algum arquivo aberto...
        // Nesse caso, se n for um novo jpeg e sim a continuação de um arquivo
        if(jpeg != NULL){
            fwrite(bytes, sizeof(uint8_t), 512, jpeg);
        }

    }

    fclose(file);
    return 0;
}
