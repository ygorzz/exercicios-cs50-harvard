import csv
import sys

def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        sys.exit(1)

    # TODO: Read database file into a variable
    # Criamos uma lista de dicionarios para armazenar todas as pessoas
    database = []
    database_file = sys.argv[1]
    with open(database_file, "r") as file:
        # armazenar a primeira linha do csv como as chaves do dict
        reader = csv.DictReader(file)
        # Armazena a lista dos STRS - 1: -> primeira coluna adiante
        strs = reader.fieldnames[1:]
        for row in reader:
            database.append(row)

    # TODO: Read DNA sequence file into a variable
    sequence_file = sys.argv[2]
    with open(sequence_file, "r") as file:
        # file.read() -> lê todo o arquivo como uma única string
        dna_sequence = file.read()


    # TODO: Find longest match of each STR in DNA sequence
    # Cria um dicionário para armazenar as repetições de cada str (chaves: valores)
    results = {}
    # Pra cada item da lista, ou seja, para cada STR
    for s in strs:
        # A função retorna a qtd de vezes que aquele str aparece na maior sequência
        # e armazena no dicionario results no valor da chave s(que é o str)
        # No final temos algo como: AGAT: 3
        results[s] = longest_match(dna_sequence, s)

    # TODO: Check database for matching profiles
    # Para cada pessoa no db (lista de dicionarios)
    for person in database:
        # Para cada STR
        for s in strs:
            # o CSV retorna uma string, por isso passamos pra int
            # Se algum dos valores do str forem diferentes
            if int(person[s]) != results[s]:
                # e saio do for (vou pra outra pessoa)
                break
        # Podemos usar um else no for
        else:
            print(person["name"])
            return

    print("No match")
    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run

main()
