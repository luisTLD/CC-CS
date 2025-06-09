# Contagem de Ciclos em Grafos

Implementação em C++ para contar ciclos simples em um grafo não direcionado e simples.

Foram utilizados dois métodos:

- **Permutações:** Gera todas as permutações possíveis de vértices para identificar ciclos.
- **Busca em Profundidade (DFS):** Explora o grafo para encontrar ciclos únicos, evitando repetições.

O grafo é representado por uma matriz de adjacência fixa, e o código considera apenas ciclos simples (sem repetir vértices, exceto o primeiro e o último).