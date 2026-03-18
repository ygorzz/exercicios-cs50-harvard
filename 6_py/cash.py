from cs50 import get_float

# Soloicitano a entrada do usuario e forçando a digitar um num > 0
while True:
    troco = get_float("Troco: ")
    if troco > 0:
        break
    else:
        print("Digite um troco maior que 0")

# Quando fazemos operações com float temos uma imprecisão no resultado
# por isso arrendondamos pro inteiro + porximo, porém para que n arredonde
# 0.15 para 0, por exemplo, transformamos ele em um inteiro antes de tudo
troco = round(troco * 100)

coins = 0

# Para cada elemento da lista 
for i in [25, 10, 5, 1]:
    while troco >= i:
        troco -= i
        coins += 1
print(coins)


