#ifndef SEGMENTATIONFH_HPP
#define SEGMENTATIONFH_HPP

// Inclusão de bibliotecas padrão e utilitárias
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <random>
#include <cassert>

// Inclusão dos módulos utilizados na segmentação
#include "graph.hpp"         // Estrutura de grafo (arestas e pesos)
#include "disjointSet.hpp"   // Union-Find para agrupamento de componentes
#include "image.hpp"         // Manipulação de imagens

// --------------------------------------------------------------------------------
// Função threshold descrita no artigo (Equação 1): threshold(size, c) = c / size
// Essa função controla o grau de evidência necessário para unir dois componentes
// menores em um maior. Quanto maior o componente, menor o threshold.
// --------------------------------------------------------------------------------
inline float threshold(int size, float c)
{
    return c / size;
}

// --------------------------------------------------------------------------------
// Função principal de segmentação por agrupamento hierárquico baseada em grafos,
// conforme descrito por Felzenszwalb e Huttenlocher (2004), Seção 4.1 e 4.2.
// --------------------------------------------------------------------------------
template <typename T>
std::vector<int> segmentGraph(const Graph<T>& graph, float c)
{
    int num_vertices = graph.num_vertices;

    // Todas as arestas do grafo são obtidas
    auto edges = graph.get_edges();

    // As arestas são ordenadas por peso crescente
    // (isto garante que a árvore geradora mínima seja construída corretamente)
    std::sort(edges.begin(), edges.end(), [](const edge_full& a, const edge_full& b) {
        return a.w < b.w;
    });

    // Uma estrutura de conjuntos disjuntos é inicializada,
    // de modo que inicialmente cada vértice forma seu próprio componente
    DisjointSet ds(num_vertices);

    // Para cada componente, inicializa-se o threshold como sendo c/1 = c
    std::vector<float> threshold_vals(num_vertices, c);

    // Internal difference (diferença interna de cada componente)
    std::vector<float> internal_diff(num_vertices, 0.0f);

    // As arestas são processadas uma a uma, na ordem crescente de peso
    for (const auto& e : edges)
    {
        // Os representantes (componentes) dos vértices da aresta são obtidos
        int a = ds.find(e.a);
        int b = ds.find(e.b);

        // Se os dois vértices já pertencerem ao mesmo componente, a aresta é ignorada
        if (a != b)
        {
            // Se o peso da aresta for menor que o threshold dos dois componentes,
            // a fusão é permitida (como definido na Equação 2 do artigo)
            if (e.w <= threshold_vals[a] && e.w <= threshold_vals[b])
            {
                // Os dois componentes são unidos
                ds.unite(a, b);

                // O novo representante (pai) da componente unida é obtido
                int new_parent = ds.find(a);

                // A internal difference do novo componente é atualizada
                internal_diff[new_parent] = std::max({ e.w, internal_diff[a], internal_diff[b] });

                // O novo threshold é calculado conforme a Equação 2 do artigo
                threshold_vals[new_parent] = internal_diff[new_parent] + threshold(ds.get_size(new_parent), c);
            }
        }
    }

    // Após todas as fusões, os rótulos finais são extraídos
    // Cada vértice recebe o identificador do seu componente
    std::vector<int> labels(num_vertices);
    for (int i = 0; i < num_vertices; ++i)
    {
        labels[i] = ds.find(i);
    }

    return labels;
}

// --------------------------------------------------------------------------------
// Função de pós-processamento para unir componentes pequenos (Seção 4.3 do artigo)
// Componentes cuja cardinalidade é menor que 'min_size' são mesclados a vizinhos
// --------------------------------------------------------------------------------
template <typename T>
std::vector<int> mergeSmallComponents(std::vector<int> labels, const Graph<T>& graph, int min_size)
{
    int num_vertices = graph.num_vertices;

    // Uma nova estrutura de conjuntos disjuntos é criada
    DisjointSet ds(num_vertices);

    // Reconstrói os conjuntos de acordo com os labels já atribuídos
    std::unordered_map<int, int> label_repr;
    for (int i = 0; i < num_vertices; ++i)
    {
        int lbl = labels[i];
        if (label_repr.find(lbl) == label_repr.end())
            label_repr[lbl] = i;       // Um representante é associado a cada label

        ds.unite(i, label_repr[lbl]); // Todos os vértices com o mesmo label são unidos
    }

    // As arestas do grafo são obtidas novamente
    auto edges = graph.get_edges();

    // Para cada aresta, é verificado se um dos componentes tem tamanho < min_size
    // Se sim, a fusão entre eles é realizada
    for (const auto& e : edges)
    {
        int a = ds.find(e.a);
        int b = ds.find(e.b);
        if (a != b)
        {
            if (ds.get_size(a) < min_size || ds.get_size(b) < min_size)
            {
                ds.unite(a, b);
            }
        }
    }

    // Os labels são atualizados com os novos representantes
    for (int i = 0; i < num_vertices; ++i)
    {
        labels[i] = ds.find(i);
    }

    return labels;
}

// --------------------------------------------------------------------------------
// Função que compacta os rótulos em uma faixa contínua [0 .. num_components-1]
// Isso é útil para facilitar indexações e gerar imagens coloridas limpas
// --------------------------------------------------------------------------------
inline std::vector<int> compactLabels(const std::vector<int>& labels)
{
    std::unordered_map<int, int> label_map;
    std::vector<int> compacted(labels.size());
    int next_label = 0;

    for (size_t i = 0; i < labels.size(); ++i)
    {
        int lbl = labels[i];
        if (label_map.find(lbl) == label_map.end())
        {
            label_map[lbl] = next_label++;  // Um novo índice compacto é atribuído
        }
        compacted[i] = label_map[lbl];     // Label original é substituído pelo novo
    }

    return compacted;
}

// --------------------------------------------------------------------------------
// Função que gera uma imagem colorida com base nos labels de segmentação
// Cada componente é colorido com uma cor aleatória para visualização
// --------------------------------------------------------------------------------
inline image<rgb>* generateSegmentedImage(const std::vector<int>& labels, int width, int height)
{
    assert(labels.size() == static_cast<size_t>(width * height));

    image<rgb>* output = new image<rgb>(width, height);

    std::mt19937 rng(42); // Semente fixa é usada para garantir cores reprodutíveis
    std::uniform_int_distribution<int> dist(0, 255);

    std::unordered_map<int, rgb> color_map;

    // Para cada pixel da imagem, a cor correspondente ao seu label é definida
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            int idx = y * width + x;
            int label = labels[idx];

            // Se o label ainda não tiver cor, uma cor aleatória é gerada e associada
            if (color_map.find(label) == color_map.end())
            {
                color_map[label] = {
                    static_cast<unsigned char>(dist(rng)),
                    static_cast<unsigned char>(dist(rng)),
                    static_cast<unsigned char>(dist(rng))
                };
            }

            // A cor correspondente ao label é atribuída ao pixel na saída
            output->set_pixel(x, y, color_map[label]);
        }
    }

    return output;
}

#endif // SEGMENTATIONFH_HPP
