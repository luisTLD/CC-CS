#ifndef PNM_IO_HPP
#define PNM_IO_HPP

// Inclusões de bibliotecas necessárias para leitura e escrita de arquivos
#include <fstream>     // Para manipulação de arquivos binários
#include <iostream>    // Para mensagens de erro
#include <string>      // Para manipulação de strings
#include <cstring>     // Para funções C de string
#include <cstdlib>     // Para funções de conversão
#include <limits>      // Para leitura de linha inteira com ignore

#include "image.hpp"   // Inclusão da estrutura de imagem usada pelo algoritmo

// ------------------------------------------------------------
// Classe de exceção personalizada para lidar com erros PNM
// ------------------------------------------------------------

class pnm_error : public std::runtime_error
{
public:
    pnm_error(const std::string& msg = "Erro ao ler arquivo PNM") : std::runtime_error(msg) {}
};

// ------------------------------------------------------------
// Função auxiliar para ler valores do cabeçalho PNM, ignorando comentários
// ------------------------------------------------------------

// No formato PNM, podem ser encontrados comentários iniciados por '#'.
// Esta função garante que valores válidos sejam lidos, pulando comentários.
inline void readNextValue(std::ifstream &file, int &value)
{
    std::string token;
    while (true)
    {
        file >> token;
        if (token.empty())
            throw pnm_error("Fim de arquivo inesperado no cabeçalho");

        if (token[0] == '#') // Se o token começar com '#', a linha é ignorada
            file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        else
        {
            try {
                value = std::stoi(token);  // O valor é convertido de string para inteiro
                return;
            } catch (...) {
                throw pnm_error("Formato inválido no cabeçalho");
            }
        }
    }
}

// ------------------------------------------------------------
// Função auxiliar para ler o cabeçalho completo da imagem
// ------------------------------------------------------------

// Largura, altura e (se aplicável) o valor máximo de intensidade são extraídos
inline void pnm_read_all_header_info(std::ifstream &file, int &width, int &height, int &max_val, bool has_max_val)
{
    readNextValue(file, width);
    readNextValue(file, height);
    if (has_max_val)
        readNextValue(file, max_val);
    else
        max_val = 1; // Para PBM, o valor máximo padrão é 1
}

// ------------------------------------------------------------
// Leitura de imagem PBM (formato P4): 1 bit por pixel
// ------------------------------------------------------------

// Os bits são lidos empacotados (8 pixels por byte)
// Os valores lidos são convertidos para 0 (preto) ou 255 (branco)
inline void read_packed(unsigned char* data, int size, std::ifstream &file)
{
    int bytes = (size + 7) / 8;  // Número total de bytes para a linha
    for (int i = 0; i < bytes; i++)
    {
        int byte = file.get();  // Um byte é lido do arquivo
        if (byte == EOF) throw pnm_error("Erro ao ler dados PBM");

        for (int bit = 7; bit >= 0; bit--)
        {
            int pos = i * 8 + (7 - bit);
            if (pos >= size) break;
            data[pos] = ((byte >> bit) & 1) ? 255 : 0; // Bit é expandido para 0 ou 255
        }
    }
}

// ------------------------------------------------------------
// Função para carregar uma imagem PBM binária
// ------------------------------------------------------------

inline image<unsigned char>* loadPBM(std::ifstream &file)
{
    int width, height, max_val;
    pnm_read_all_header_info(file, width, height, max_val, false);  // max_val não é necessário em PBM

    image<unsigned char>* img = new image<unsigned char>(width, height);
    for (int y = 0; y < height; y++)
        read_packed(img->access[y], width, file);  // Cada linha é lida com os bits empacotados

    return img;
}

// ------------------------------------------------------------
// Função para carregar imagem PGM (tons de cinza) em P5
// ------------------------------------------------------------

inline image<unsigned char>* loadPGM(std::ifstream &file)
{
    int width, height, max_val;
    pnm_read_all_header_info(file, width, height, max_val, true);

    if (max_val > 255) throw pnm_error("PGM com max_val > 255 não suportado");

    image<unsigned char>* img = new image<unsigned char>(width, height);

    // Os dados da imagem são lidos diretamente na memória
    file.read(reinterpret_cast<char*>(img->data), width * height);
    if (!file) throw pnm_error("Erro ao ler dados PGM");

    return img;
}

// ------------------------------------------------------------
// Função para carregar imagem PPM (colorida RGB) em P6
// ------------------------------------------------------------

inline image<rgb>* loadPPM(std::ifstream &file)
{
    int width, height, max_val;
    pnm_read_all_header_info(file, width, height, max_val, true);

    if (max_val > 255) throw pnm_error("PPM com max_val > 255 não suportado");

    image<rgb>* img = new image<rgb>(width, height);
    file.read(reinterpret_cast<char*>(img->data), width * height * sizeof(rgb));
    if (!file) throw pnm_error("Erro ao ler dados PPM");

    return img;
}

// ------------------------------------------------------------
// Função genérica para ler qualquer imagem PNM (P4, P5, P6)
// ------------------------------------------------------------

inline void* loadPNMImage(const char* filename, std::string& type)
{
    std::ifstream file(filename, std::ios::binary);
    if (!file) throw pnm_error("Não foi possível abrir o arquivo");

    char header[3] = {0};               // Os dois primeiros caracteres são lidos (ex: P6)
    file.read(header, 2);
    if (file.gcount() != 2 || header[0] != 'P')
        throw pnm_error("Formato inválido de arquivo PNM");

    header[2] = '\0';                   // String terminada em nulo

    // Com base no segundo caractere do cabeçalho, decide-se qual função de leitura usar
    switch (header[1])
    {
        case '4':
            type = "PBM";
            return loadPBM(file);
        case '5':
            type = "PGM";
            return loadPGM(file);
        case '6':
            type = "PPM";
            return loadPPM(file);
        default:
            throw pnm_error("Tipo PNM não suportado");
    }
}

// ------------------------------------------------------------
// Função para salvar uma imagem RGB no formato PPM (P6)
// ------------------------------------------------------------

inline void savePPM(const char* filename, const image<rgb>* img)
{
    std::ofstream ofs(filename, std::ios::binary);
    if (!ofs)
    {
        std::cerr << "Erro ao abrir arquivo para salvar imagem\n";
        return;
    }

    int width = img->width();
    int height = img->height();

    // Cabeçalho do formato P6 é escrito no arquivo de saída
    ofs << "P6\n" << width << " " << height << "\n255\n";

    // Os dados RGB da imagem são escritos em sequência
    ofs.write(reinterpret_cast<const char*>(img->data), width * height * sizeof(rgb));
    ofs.close();
}

#endif // PNM_IO_HPP
