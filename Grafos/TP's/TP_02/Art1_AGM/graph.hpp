#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <cassert>
#include <cmath>

#include "image.hpp"

// ----------------------
// Estruturas de Dados
// ----------------------

// A estrutura `edge` é utilizada para representar uma aresta simples do grafo,
// contendo o índice do vértice destino (`to`) e o peso (`w`) da aresta.
struct edge
{
    int to;    // Vértice destino
    float w;   // Peso da aresta (diferença de cor)
};

// A estrutura `edge_full` é utilizada quando se deseja representar a aresta
// completa, com o vértice de origem `a`, destino `b` e o peso `w`.
// Essa estrutura é especialmente útil para ordenação das arestas na segmentação.
struct edge_full
{
    int a, b;
    float w;
};

// -------------------------------------
// Funções para calcular diferença de cor
// -------------------------------------

// A diferença entre dois tons de cinza (valores uchar) é calculada como
// valor absoluto da subtração.
inline float color_diff(const unsigned char &a, const unsigned char &b)
{
    return std::abs((float)a - (float)b);
}

// A diferença entre dois pixels RGB é calculada pela distância Euclidiana
// no espaço de cor, conforme descrito na Seção 4.2 do artigo.
inline float color_diff(const rgb &a, const rgb &b)
{
    int dr = (int)a.r - (int)b.r;
    int dg = (int)a.g - (int)b.g;
    int db = (int)a.b - (int)b.b;

    // A raiz quadrada da soma dos quadrados das diferenças é computada.
    // Esse valor é usado como o peso da aresta entre os dois pixels.
    return std::sqrt(dr * dr + dg * dg + db * db);
}

// -------------------------------------
// Classe do Grafo (Template para tipos de pixel)
// -------------------------------------

// A classe Graph<T> representa a estrutura de grafo onde:
// - Cada pixel da imagem é considerado um vértice.
// - As arestas são adicionadas entre vizinhos com base na diferença de cor.
template <typename T>
class Graph
{
public:
    int num_vertices;                        // Quantidade total de vértices (pixels)
    int num_edges;                           // Número de arestas adicionadas
    std::vector<std::vector<edge>> adjacency; // Lista de adjacência para cada vértice

    // Construtor do grafo: a imagem é recebida e o grafo é construído.
    Graph(const image<T>* img);

    // Retorna todas as arestas do grafo no formato completo (a, b, w)
    std::vector<edge_full> get_edges() const;
};

// -----------------------------
// Implementação das Funções
// -----------------------------

// O construtor da classe Graph realiza a construção do grafo de vizinhança.
// Conforme descrito no artigo (Seção 4.2), cada pixel é conectado aos seus
// vizinhos imediatos (4- ou 8-conexões). Aqui, são utilizadas 8 conexões.
template <typename T>
Graph<T>::Graph(const image<T>* img)
{
    assert(img != nullptr); // Verificação de segurança

    int width = img->width();    // Largura da imagem
    int height = img->height();  // Altura da imagem

    // O número total de vértices corresponde ao número de pixels.
    num_vertices = width * height;
    num_edges = 0;

    // Inicializa a lista de adjacência com `num_vertices` listas vazias.
    adjacency.assign(num_vertices, std::vector<edge>());

    // Função local para adicionar uma aresta entre dois vértices a e b, com peso w.
    auto add_edge = [&](int a, int b, float w)
    {
        // Como o grafo é não direcionado, a aresta é adicionada nos dois sentidos.
        adjacency[a].push_back({b, w});
        adjacency[b].push_back({a, w});
        num_edges++;
    };

    // Laço sobre todos os pixels da imagem para gerar as arestas.
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            // O índice linear do pixel atual é calculado.
            int idx = y * width + x;

            // O valor do pixel atual é armazenado.
            const T& current_pixel = img->get_pixel(x, y);

            // Adiciona aresta com o vizinho da direita (horizontal).
            if (x + 1 < width)
            {
                int right_idx = y * width + (x + 1);
                float w = color_diff(current_pixel, img->get_pixel(x + 1, y));
                add_edge(idx, right_idx, w);
            }

            // Adiciona aresta com o vizinho de baixo (vertical).
            if (y + 1 < height)
            {
                int down_idx = (y + 1) * width + x;
                float w = color_diff(current_pixel, img->get_pixel(x, y + 1));
                add_edge(idx, down_idx, w);
            }

            // Adiciona aresta com o vizinho diagonal inferior-direita.
            if ((x + 1 < width) && (y + 1 < height))
            {
                int diag_rd_idx = (y + 1) * width + (x + 1);
                float w = color_diff(current_pixel, img->get_pixel(x + 1, y + 1));
                add_edge(idx, diag_rd_idx, w);
            }

            // Adiciona aresta com o vizinho diagonal inferior-esquerda.
            if ((x - 1 >= 0) && (y + 1 < height))
            {
                int diag_ld_idx = (y + 1) * width + (x - 1);
                float w = color_diff(current_pixel, img->get_pixel(x - 1, y + 1));
                add_edge(idx, diag_ld_idx, w);
            }
        }
    }
}

// A função abaixo retorna todas as arestas do grafo no formato `edge_full`.
// Essa estrutura é usada na etapa de segmentação, onde as arestas precisam ser ordenadas.
template <typename T>
std::vector<edge_full> Graph<T>::get_edges() const
{
    std::vector<edge_full> all_edges;

    // Para evitar duplicatas, apenas as arestas com a < b são armazenadas.
    for (int a = 0; a < num_vertices; ++a)
    {
        for (const auto& e : adjacency[a])
        {
            int b = e.to;
            if (a < b)
                all_edges.push_back({a, b, e.w});
        }
    }

    return all_edges;
}

#endif // GRAPH_HPP
