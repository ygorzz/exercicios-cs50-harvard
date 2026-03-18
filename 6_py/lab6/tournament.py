# Simulate a sports tournament

import csv
import sys
import random

# Number of simluations to run
N = 1000

def main():

    # Ensure correct usage
    if len(sys.argv) != 2:
        sys.exit("Usage: python tournament.py FILENAME")

    # Lista de dicts
    teams = []
    # TODO: Read teams into memory from file
    teams_file = sys.argv[1]
    with open(teams_file, "r") as file:
        # Armazena a primeira linha do aquivo como as chavs do dict
        reader = csv.DictReader(file)
        # Para cada linha(equipe) do arquivo, adiciona a linha na lista
        for row in reader:
            # converte o raiting para int
            row["rating"] = int(row["rating"])
            teams.append(row)

    counts = {}
    # TODO: Simulate N tournaments and keep track of win counts
    # Popula counts com os nomes dos times sendo as chaves e tendo valor 0 inicialmente
    for team in teams:
        team_name = team["team"]
        counts[team_name] = 0

    # Simula N tournaments
    for i in range(N):
        # Com essa forma não precisaria fazer o for team in teams:
        # winner = simulate_tournament(teams)
        # if winner not in counts:
        #     counts[winner] = 0
        # counts[winner] += 1

        # Adiconar 1 no valor do time campeão
        counts[simulate_tournament(teams)] += 1




    # Print each team's chances of winning, according to simulation
    for team in sorted(counts, key=lambda team: counts[team], reverse=True):
        print(f"{team}: {counts[team] * 100 / N:.1f}% chance of winning")


def simulate_game(team1, team2):
    """Simulate a game. Return True if team1 wins, False otherwise."""
    rating1 = team1["rating"]
    rating2 = team2["rating"]
    probability = 1 / (1 + 10 ** ((rating2 - rating1) / 600))
    return random.random() < probability


def simulate_round(teams):
    """Simulate a round. Return a list of winning teams."""
    winners = []

    # Simulate games for all pairs of teams
    for i in range(0, len(teams), 2):
        # Se o primeiro time ganhou
        if simulate_game(teams[i], teams[i + 1]):
            winners.append(teams[i])
        else:
            winners.append(teams[i + 1])

    return winners


def simulate_tournament(teams): # Passamos como parâmetro todos as equipes - a lista teams[]
    """Simulate a tournament. Return name of winning team."""
    # TODO
    # Cria uma cópia da liste teams para que quando eu simular vários torneios eles sempre iniciem com 16 times
    copia = teams[:]
    # Loop para encontrar o campeão
    while len(copia) > 1:
        # Atualizo a lista teams para poder rodar o novo round
        copia = simulate_round(copia)

    # Armazena apenas o nome do time
    tournament_winner = copia[0]["team"]
    # Retorna o nome do time vencedor
    return tournament_winner

if __name__ == "__main__":
    main()
