import random
import heapq
from collections import deque

# GOAL e o estado final desejado do puzzle 8
GOAL = '123456780'
# MOVES define os deslocamentos possiveis do zero no vetor
MOVES = [-1, 1, -3, 3]

def print_board(state):
    # imprime o tabuleiro 3x3 a partir da string de 9 caracteres
    for i in range(0, 9, 3):
        print(' '.join(state[i:i+3]))
    print()


def get_neighbors(state):
    # encontra a posicao do zero e gera todos os estados vizinhos
    zero = state.index('0')
    for m in MOVES:
        nz = zero + m
        # verifica se nova posicao fica dentro do tabuleiro linearizado
        if 0 <= nz < 9:
            # evita troca entre linhas erradas (quebra de linha)
            if (zero % 3 == 0 and m == -1) or (zero % 3 == 2 and m == 1):
                continue
            # cria nova configuracao trocando zero pelo numero vizinho
            s = list(state)
            s[zero], s[nz] = s[nz], s[zero]
            yield ''.join(s)


def search(start, method, h=lambda s: 0):
    # visited guarda estados ja visitados para evitar repeticao
    visited = {start}
    # parent mapeia cada estado ao seu estado pai para reconstruir caminho
    parent = {start: None}
    # g guarda custo (numero de passos) para alcancar cada estado
    g = {start: 0}
    # contador de expansoes de nos
    explorados = 0

    # inicializa fronteira dependendo do metodo escolhido
    if method == 'dfs':
        frontier = [start]           # pilha LIFO
    elif method == 'bfs':
        frontier = deque([start])    # fila FIFO
    else:
        # para A* usamos heap de prioridades (f = g + h)
        frontier = [(h(start), start)]
        heapq.heapify(frontier)

    # loop principal de busca
    while frontier:
        # retira proximo estado da fronteira
        if method == 'dfs':
            state = frontier.pop()
        elif method == 'bfs':
            state = frontier.popleft()
        else:
            _, state = heapq.heappop(frontier)
        explorados += 1  # incrementa contador a cada remocao (expansao)

        # verifica se encontramos solucao
        if state == GOAL:
            # reconstrucao de caminho do estado inicial ao final
            path = []
            while state is not None:
                path.append(state)
                state = parent[state]
            # retorna caminho invertido, custo final e numero de nos explorados
            return list(reversed(path)), g[GOAL], explorados

        # expande vizinhos do estado atual
        for nbr in get_neighbors(state):
            cost = g[state] + 1
            # verifica se e a primeira vez que visitamos ou encontramos custo menor
            if nbr not in visited or (method == 'astar' and cost < g.get(nbr, float('inf'))):
                visited.add(nbr)
                parent[nbr] = state
                g[nbr] = cost
                # adiciona vizinho na fronteira de acordo com o metodo
                if method in ('dfs', 'bfs'):
                    frontier.append(nbr)
                else:
                    heapq.heappush(frontier, (cost + h(nbr), nbr))

    # se fronteira esvaziar sem achar solucao, retorna sem caminho
    return [], None, explorados


def h_manhattan(s):
    # calcula heuristica de distancia de Manhattan
    dist = 0
    for i, c in enumerate(s):
        if c == '0':
            continue
        val = int(c) - 1
        # posicao alvo calculada de val
        dist += abs(i // 3 - val // 3) + abs(i % 3 - val % 3)
    return dist


def h_misplaced(s):
    # heuristica conta quantas pecas fora do lugar
    return sum(1 for i, c in enumerate(s) if c != GOAL[i])


def main():
    # escolha aleatoria de estado inicial
    # start = ''.join(random.sample(GOAL, 9))
    start = "724506831" # Teste para o PDF
    print('Tabuleiro inicial:')
    print_board(start)
    while True:
        # menu de opcoes
        print('1 - DFS')
        print('2 - BFS')
        print('3 - A* (Manhattan)')
        print('4 - A* (Misplaced)')
        print('0 - Sair')
        choice = input('Opcao: ')
        if choice == '0':
            print('Encerrando.')
            break
        # define metodo e heuristica
        method = {'1': 'dfs', '2': 'bfs', '3': 'astar', '4': 'astar'}[choice]
        h = h_manhattan if choice == '3' else (h_misplaced if choice == '4' else (lambda s: 0))

        # executa busca
        path, cost, explorados = search(start, method, h)
        if path:
            # imprime numero de movimentos otimos e nos explorados
            print(f'Movimentos (otimos): {len(path)-1}')
            print(f'Estados explorados: {explorados}')
            # opcao para mostrar sequencia de passos
            if input('Ver passo a passo? (Y/N): ').lower() == 'y':
                for st in path:
                    print_board(st)
        else:
            print('Solucao nao encontrada.')

if __name__ == '__main__':
    main()
