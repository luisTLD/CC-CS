# Teoria dos Grafos

# 1. FUNDAMENTOS

## Grafo
Estrutura composta por:
- vértices
- arestas

Representa:
- redes
- conexões
- relações
- caminhos

## Tipos de Grafos

### Grafo Simples
Sem:
- laços
- arestas múltiplas

### Grafo Direcionado
Arestas possuem direção.

### Grafo Ponderado
Arestas possuem pesos.

### Multigrafo
Permite múltiplas arestas.

### Grafo Bipartido
Vértices divididos em dois conjuntos.

## Representação de Grafos

### Matriz de Adjacência
Representação em matriz NxN.

### Lista de Adjacência
Lista de vizinhos de cada vértice.

---

# 2. ESTRUTURAS E PROPRIEDADES

## Grau de um Vértice
Quantidade de arestas conectadas.

## Caminho
Sequência de vértices conectados.

## Ciclo
Caminho fechado.

## Subgrafo
Parte de um grafo.

## Grafo Completo
Todos os vértices conectados entre si.

## Conectividade
Verifica conexão entre vértices.

## Componentes Conexas
Grupos conectados do grafo.

## Ponte
Aresta crítica para conectividade.

## Articulação
Vértice crítico para conectividade.

---

# 3. CAMINHAMENTOS E BUSCAS

## DFS
Busca em profundidade.

Características:
- exploração profunda
- recursão
- pilha

## BFS
Busca em largura.

Características:
- exploração por níveis
- fila

## Ordenação Topológica
Ordena vértices por dependência.

---

# 4. ÁRVORES

## Árvore
Grafo conectado sem ciclos.

## Árvore Geradora
Conecta todos os vértices.

## Árvore Geradora Mínima (MST)
Árvore com menor conjunto de arestas.

## Kruskal
MST baseada em ordenação de arestas.

## Prim
MST baseada em expansão do grafo.

---

# 5. CAMINHOS MÍNIMOS

## Caminho Mínimo
Menor percurso entre vértices.

## Dijkstra
Pesos positivos.

## Bellman-Ford
Permite pesos negativos.

## Floyd-Warshall
Todos os pares de vértices.

---

# 6. FLUXO EM REDES

## Fluxo em Redes
Movimentação em grafos direcionados.

## Capacidade
Limite de fluxo na aresta.

## Ford-Fulkerson
Fluxo máximo.

## Caminho de Custo Mínimo
Fluxo com menor peso total.

---

# 7. PLANARIDADE

## Grafo Planar
Sem cruzamento de arestas.

## Teorema de Euler
Relação entre:
- vértices
- arestas
- faces

## Testes de Planaridade
Verificação de planaridade.

---

# 8. GRAFOS ESPECIAIS

## Grafo Euleriano
Percorre todas as arestas uma única vez.

## Grafo Semi-Euleriano
Possui caminho Euleriano.

## Grafo Hamiltoniano
Percorre todos os vértices uma única vez.

## Grafo Linha
Arestas transformadas em vértices.

## Isomorfismo
Grafos estruturalmente equivalentes.
