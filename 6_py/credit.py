from cs50 import get_string
import re

def main():
    # Obtenho a entrada como string para usar o modulo re ao final
    num_cartao = get_string("Digite o número do seu cartão: ")

    # Se checksum() retornou true
    if checksum(num_cartao):
        definir_bandeira(num_cartao)



# Checksum
def checksum(num):

    penultimo_digito = len(num) -2
    ultimo_digito = len(num) -1
    soma1 = 0
    soma2 = 0

    # A partir do penultimo digito vou pulando um
    for i in range(penultimo_digito, -1, -2):
        # Converte o digito para int e multiplica
        digito_int = int(num[i]) * 2
        soma1 += (digito_int // 10) + (digito_int % 10)
    # A partir do ultimo digito vou pulando um
    for i in range(ultimo_digito, -1, -2):
        digito = int(num[i])
        # Soma os digitos de cada posição
        soma2 += digito

    soma_final = soma1 + soma2

    #Se o uúltimo dígito for = 0
    if soma_final % 10 == 0:
        return True
    else:
        print("INVALID")
        return False

def definir_bandeira(num):

    tam = len(num)
    if tam == 15 and re.match(r'^(34|37)', num):
        print("AMEX")
    # de 51 a 55
    elif tam == 16 and re.match(r'^5[1-5]', num):
        print("MASTERCARD")
    elif tam == 13 or tam == 16 and re.match(r'^4', num):
        print("VISA")
    else:
        print("INVALID")

main()
