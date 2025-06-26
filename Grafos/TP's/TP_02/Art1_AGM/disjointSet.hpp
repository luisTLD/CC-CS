#ifndef DISJOINT_SET_HPP
#define DISJOINT_SET_HPP

#include <vector>

// Estrutura de conjuntos disjuntos (Union-Find com path compression e union by size)
// Essa estrutura é essencial para o algoritmo de Felzenszwalb e Huttenlocher,
// pois permite manter e unir componentes conforme as arestas do grafo são processadas.
class DisjointSet
{
private:
    std::vector<int> parent; // Vetor que armazena o pai (ou representante) de cada elemento
    std::vector<int> size;   // Tamanho de cada conjunto (usado para união por tamanho)

public:
    // Construtor: inicializa n conjuntos disjuntos, um para cada vértice do grafo
    DisjointSet(int n);

    // Retorna o representante (raiz) do conjunto ao qual x pertence
    // Aplica compressão de caminho para tornar futuras buscas mais rápidas
    int find(int x);

    // Une os conjuntos que contêm x e y, respeitando a heurística de união por tamanho
    void unite(int x, int y);

    // Retorna o tamanho atual do conjunto ao qual x pertence
    int get_size(int x);
};

// -------- IMPLEMENTAÇÕES -------- //

// Construtor da estrutura DisjointSet
inline DisjointSet::DisjointSet(int n)
{
    // Inicializa vetor de pais com n elementos: cada vértice é seu próprio representante
    parent.resize(n);
    // Inicializa todos os tamanhos como 1, pois cada conjunto começa com um único elemento
    size.resize(n, 1);
    for (int i = 0; i < n; ++i)
        parent[i] = i; // Cada vértice é o representante de si mesmo inicialmente
}

// Função find com compressão de caminho (path compression)
// Otimiza a estrutura achatando as árvores para acesso rápido
inline int DisjointSet::find(int x)
{
    if (parent[x] != x)
        parent[x] = find(parent[x]); // Aponta diretamente para a raiz (representante)
    return parent[x]; // Retorna o representante do conjunto
}

// Função que une dois conjuntos disjuntos (representados por x e y)
inline void DisjointSet::unite(int x, int y)
{
    // Encontra os representantes (raízes) dos conjuntos de x e y
    int root_x = find(x);
    int root_y = find(y);
    if (root_x == root_y) return; // Já estão no mesmo conjunto, não faz nada

    // Estratégia de união por tamanho: o conjunto menor é anexado ao maior
    if (size[root_x] < size[root_y])
    {
        parent[root_x] = root_y;            // root_x passa a apontar para root_y
        size[root_y] += size[root_x];       // atualiza o tamanho do novo conjunto unido
    }
    else
    {
        parent[root_y] = root_x;            // root_y passa a apontar para root_x
        size[root_x] += size[root_y];       // atualiza o tamanho do novo conjunto unido
    }
}

// Função que retorna o tamanho atual do conjunto ao qual x pertence
inline int DisjointSet::get_size(int x)
{
    return size[find(x)]; // acessa o tamanho do conjunto a partir do representante de x
}

#endif // DISJOINT_SET_HPP
