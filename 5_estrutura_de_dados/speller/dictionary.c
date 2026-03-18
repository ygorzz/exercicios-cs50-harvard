// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <strings.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
// Número de buckets grande para que haja menos colisões
const unsigned int N = 10000;

// Hash table
node *table[N];

// Variável para contar as palavras - será usado em size() e as palavras sçao contadas em load()
int word_count = 0;

// --- CHECK() ---

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // indice da palavra a ser pesquisada
    unsigned int index = hash(word);

    // verifica se o buckcet da table está vazio
    if(table[index] == NULL){
        return false;
    }

    // Pointer temporário para não perder os anteriores ao passar pro próximo
    node *tmp = table[index];
    // Enquanto a palavra do node for diferente da palavra do parametro
    while(strcasecmp(tmp->word, word) != 0){ // strcasecmp -> ignora a diferença entre maiúscula e minúscula
        //Antes de ir pro proximo node verifica se há um proximo node
        if(tmp->next == NULL){
            // Não encontrou a palavra
            return false;
        }
        tmp = tmp->next;
    }
    // Encontrou a palavra
    return true;
}

// --- HASH() ---

// Hashes word to a number
unsigned int hash(const char *word)
{
    // FUNÇÃO DJB2
    // TODO: Improve this hash function
    unsigned long hash = 5381;
    int c;

    while ((c = *word++))
    {
        hash = ((hash << 5) + hash) + tolower(c); // hash * 33 + c
    }

    return hash % N;
}

// --- LOAD() ---

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Loop para inicializar todos os buckets da table como NULL
    for(int i = 0; i < N; i++){
        table[i] = NULL;
    }
    FILE *file = fopen(dictionary, "r");

    if (!file){
        printf("Não foi possível abrir o arquivo.\n");
        return false;
    }
    // bucket para aramazenar a palavra do dicionario
    char word_in_dictionary[LENGTH + 1];

    // Lê palavra por palavra enquanto for diferente de End Of File e armazena em
    // word_in_dictionary
    while (fscanf(file, "%s", word_in_dictionary) != EOF){
        // Cria um node para a palavra
        node *new_node = malloc(sizeof(node));
        if (!new_node){
            return false;
        }
        // O campo word do node criado recebe a palavra que foi armazenada
        strcpy(new_node->word, word_in_dictionary);

        // hash --> Retorna o índice do bucket q a palavra ficará
        unsigned int id = hash(word_in_dictionary);

        // LÓGICA PARA O NEW_NODE SER O PRIMEIRO DA LISTA
        // O campo next do node criado aponta para o último node até então
        new_node->next = table[id];
        // O bucket referente a palavra aponta para o node criado
        table[id] = new_node;

        word_count++;
    }
    fclose(file);
    return true;
}

// --- SIZE() ---

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return word_count;
}

// --- UNLOAD() ---

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for(int i = 0; i < N; i++){
        node* tmp;
        while(table[i] != NULL){
            tmp = table[i]->next;
            free(table[i]);
            table[i] = tmp;
        }

    }
    return true;
}
