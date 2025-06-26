// main.cpp

#include <iostream>
#include <string>
#include <cmath>  // Para std::round

#include "pnmio.hpp"       // Leitura de imagens no formato PNM (P4, P5, P6)
#include "image.hpp"       // Classe genérica de imagem (template)
#include "graph.hpp"       // Definição de grafo construído a partir da imagem
#include "disjointSet.hpp" // Estrutura Disjoint Set (Union-Find)
#include "segmentationFH.hpp" // Implementação do algoritmo FH (Árvore Geradora Mínima)
#include "gaussianFilter.hpp" // Filtro Gaussiano para suavização pré-segmentação

//------------------------------------------------------------------------------
// Função auxiliar: realiza a saturação de um valor em float para [0,255]
// com arredondamento. Usada na conversão dos canais suavizados de volta
// para unsigned char em imagens coloridas.
//------------------------------------------------------------------------------
inline unsigned char saturate_float_to_uchar(float val)
{
    // O valor em float é convertido para inteiro com std::round
    int iv = static_cast<int>(std::round(val));
    // Se o valor for menor que 0, é saturado para 0
    if (iv < 0) return 0;
    // Se o valor exceder 255, é saturado para 255
    if (iv > 255) return 255;
    // Caso contrário, faz-se o cast para unsigned char
    return static_cast<unsigned char>(iv);
}

// Protótipos das funções que processam e salvam a imagem segmentada
template <typename T>
void processAndSave(image<T>* img, const char* output_file, float k, float sigma);

// Sobrecarga para o tipo RGB
void processAndSave(image<rgb>* img, const char* output_file, float k, float sigma);

//------------------------------------------------------------------------------
// Função principal (entry point)
//------------------------------------------------------------------------------
int main(int argc, char** argv)
{
    // Parâmetros padrão:
    // k controla a granularidade da segmentação (threshold adaptativo)
    float k = 1000.0f;
    // sigma define o desvio padrão do filtro Gaussiano (suavização)
    float sigma = 1.0f;

    // Verificação da quantidade de argumentos
    if (argc < 3 || argc > 5)
    {
        std::cerr << "Uso: " << argv[0] << " <input.pnm> <output.ppm> [<k> <sigma>]\n";
        std::cerr << "Onde k controla a segmentação (default 1000) e sigma o filtro Gaussiano (default 1.0)\n";
        return 1; // Encerra com erro de uso
    }

    // Arquivos de entrada e saída são extraídos dos argumentos
    const char* input_file = argv[1];
    const char* output_file = argv[2];

    // Se parâmetros opcionais forem fornecidos, atualiza-se k e sigma
    if (argc >= 4) k = std::stof(argv[3]);
    if (argc >= 5) sigma = std::stof(argv[4]);

    // Variáveis para armazenar o tipo da imagem e o ponteiro genérico
    std::string type;
    void* raw_img = nullptr;

    // Tentativa de leitura da imagem PNM
    try {
        raw_img = loadPNMImage(input_file, type);
    } catch (...) {
        std::cerr << "Erro ao carregar imagem " << input_file << "\n";
        return 1; // Erro na leitura do arquivo
    }

    // Seleção do fluxo de processamento conforme o tipo da imagem
    switch (getImageType(type))
    {
    case ImageType::PBM:  // imagens PBM binárias
    case ImageType::PGM:  // imagens PGM tons de cinza
        // O ponteiro bruto é convertido para image<unsigned char>*
        processAndSave(static_cast<image<unsigned char>*>(raw_img), output_file, k, sigma);
        break;

    case ImageType::PPM:  // imagens PPM coloridas
        // O ponteiro bruto é convertido para image<rgb>*
        processAndSave(static_cast<image<rgb>*>(raw_img), output_file, k, sigma);
        break;

    default:
        std::cerr << "Formato PNM não suportado: " << type << "\n";
        return 1; // Erro de formato não suportado
    }

    // Mensagem de sucesso
    std::cout << "Segmentação concluída com sucesso. Saída: " << output_file << "\n";
    return 0;
}

//------------------------------------------------------------------------------
// Implementação de processAndSave para imagens PBM/PGM (unsigned char)
//------------------------------------------------------------------------------
template <typename T>
void processAndSave(image<T>* img, const char* output_file, float k, float sigma)
{
    // Passo 1: suavização com filtro Gaussiano (float)
    image<float>* smoothed = gaussian::gaussianSmooth(img, sigma);

    // Passo 2: construção do grafo a partir da imagem suavizada
    Graph<float> graph(smoothed);

    // Passo 3: segmentação via MST modificado (FH 2004)
    auto labels = segmentGraph(graph, k);

    // Passo 4: pós-processamento para mesclar componentes pequenas
    const int min_component_size = 500;
    labels = mergeSmallComponents(labels, graph, min_component_size);

    // Passo 5: geração de imagem segmentada colorida para visualização
    auto output = generateSegmentedImage(labels, img->width(), img->height());

    // Passo 6: salvamento em disco no formato PPM
    savePPM(output_file, output);

    // Limpeza de memória alocada dinamicamente
    delete img;
    delete smoothed;
    delete output;
}

//------------------------------------------------------------------------------
// Implementação de processAndSave para imagens PPM (rgb)
//------------------------------------------------------------------------------
void processAndSave(image<rgb>* img, const char* output_file, float k, float sigma)
{
    // Passo 1: suavização Gaussiana por canal (retorna 3 imagens<float>)
    auto smoothed_channels = gaussian::gaussianSmooth(img, sigma);

    // Obtém dimensões da imagem
    int w = img->width();
    int h = img->height();

    // Passo 2: combinação dos canais suavizados em uma única imagem<rgb>
    image<rgb>* smoothed_img = new image<rgb>(w, h);
    for (int y = 0; y < h; ++y)
    {
        for (int x = 0; x < w; ++x)
        {
            rgb px;
            // Cada canal é saturado e convertido de float para uchar
            px.r = saturate_float_to_uchar(smoothed_channels[0]->get_pixel(x, y));
            px.g = saturate_float_to_uchar(smoothed_channels[1]->get_pixel(x, y));
            px.b = saturate_float_to_uchar(smoothed_channels[2]->get_pixel(x, y));
            smoothed_img->set_pixel(x, y, px);
        }
    }

    // Passo 3: construção do grafo a partir da imagem RGB suavizada
    Graph<rgb> graph(smoothed_img);

    // Passo 4: segmentação via MST modificado
    auto labels = segmentGraph(graph, k);

    // Passo 5: fusão de componentes pequenas
    const int min_component_size = 500;
    labels = mergeSmallComponents(labels, graph, min_component_size);

    // Passo 6: geração de imagem segmentada colorida
    auto output = generateSegmentedImage(labels, w, h);

    // Passo 7: salvamento da imagem segmentada em disco
    savePPM(output_file, output);

    // Liberação de memória alocada
    delete img;
    for (auto ch : smoothed_channels)
        delete ch;
    delete smoothed_img;
    delete output;
}
