from sys import argv, exit

def main():

    if len(argv) != 2:
        print("Error")
        exit(1)

    file = argv[1]

    index = reading_level(file)
    print_level(index)

def reading_level(file):

    with open(file, 'r') as file:

        letters = 0
        words = 0
        phrases = 0

        for line in file:
            words += len(line.split())
            for char in line:
                if char.isalpha():
                    letters += 1
                elif char in [".", "!", "?"]:
                    phrases += 1

        # índice Coleman-Liau
        L = (letters/words) * 100
        S = (phrases/words) * 100

        index = round(0.0588 * L - 0.296 * S - 15.8)

    return index

def print_level(index):
    if index >= 16:
        print("Grade 16+")
    elif index < 1:
        print("Before Grade 1")
    else:
        print(f"Grade {index}")

main()
