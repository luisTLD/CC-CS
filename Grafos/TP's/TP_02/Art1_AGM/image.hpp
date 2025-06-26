#ifndef IMAGE_H
#define IMAGE_H

#include <cstring>  // Para uso de memset e memcpy
#include <string>   // Para manipulação de strings (std::string)

// ------------------------------
// Representação de pixel RGB
// ------------------------------

// Foi definido um tipo para representar um canal de cor (valores de 0 a 255)
typedef unsigned char uchar;

// A estrutura 'rgb' representa um pixel com três componentes (vermelho, verde e azul),
// sendo usada para imagens coloridas (PPM).
struct rgb { uchar r, g, b; };

// ------------------------------
// Enumeração dos tipos de imagem
// ------------------------------

// O enum `ImageType` foi definido para categorizar imagens do tipo:
// - PGM: tons de cinza
// - PBM: binária
// - PPM: colorida RGB
enum class ImageType { PGM, PBM, PPM, UNKNOWN };

// A função auxiliar abaixo retorna o tipo da imagem a partir de uma string.
// Isso é usado na leitura do cabeçalho de arquivos PNM (P4, P5, P6).
inline ImageType getImageType(const std::string& type)
{
    if (type == "PGM") return ImageType::PGM;
    if (type == "PBM") return ImageType::PBM;
    if (type == "PPM") return ImageType::PPM;
    return ImageType::UNKNOWN;
}

// -------------------------------------
// Classe genérica de imagem (template)
// -------------------------------------

// A classe image<T> é usada para armazenar e manipular imagens com qualquer tipo de pixel:
// - T = uchar: para imagens PBM/PGM
// - T = rgb:   para imagens PPM
template <class T>
class image
{
private:
    int w, h;      // Largura (w) e altura (h) da imagem

public:
    T* data;       // Vetor linear de pixels
    T** access;    // Vetor de ponteiros para cada linha (acesso 2D)

    // Construtor: recebe largura e altura
    image(int width, int height);

    // Destrutor: libera memória
    ~image();

    // Inicializa todos os pixels com um valor
    void init(const T& val);

    // Cria uma cópia da imagem
    image<T>* copy() const;

    // Retorna largura e altura
    int width() const;
    int height() const;

    // Acesso a pixels de forma segura
    const T& get_pixel(int x, int y) const;
    void set_pixel(int x, int y, const T& val);

    // Operador () para acesso mais prático
    T& operator()(int x, int y);
    const T& operator()(int x, int y) const;
};

// ---------------------------
// Implementações
// ---------------------------

// O construtor reserva a memória para os pixels e para o vetor de acesso por linha.
// Os ponteiros de linha são ajustados para facilitar o acesso 2D.
template <class T>
image<T>::image(int width, int height)
{
    w = width;
    h = height;

    // A memória para os dados da imagem é alocada.
    data = new T[w * h];

    // Um vetor de ponteiros é criado para cada linha.
    access = new T*[h];

    // Cada ponteiro da linha aponta para o início da linha correspondente.
    for (int i = 0; i < h; i++)
        access[i] = data + i * w;

    // A memória dos dados é zerada (todos os pixels ficam inicialmente com valor 0).
    memset(data, 0, w * h * sizeof(T));
}

// O destrutor libera a memória alocada anteriormente.
template <class T>
image<T>::~image()
{
    delete[] access;  // Liberação do vetor de linhas
    delete[] data;    // Liberação do vetor de dados
}

// A função init() permite que todos os pixels da imagem sejam preenchidos com um valor específico.
template <class T>
void image<T>::init(const T& val)
{
    for (int i = 0; i < w * h; i++)
        data[i] = val;
}

// A função copy() realiza uma cópia profunda da imagem, alocando uma nova área de memória.
template <class T>
image<T>* image<T>::copy() const
{
    image<T>* im = new image<T>(w, h);
    memcpy(im->data, data, w * h * sizeof(T)); // Copia o conteúdo dos pixels
    return im;
}

// As funções width() e height() retornam, respectivamente, a largura e altura da imagem.
template <class T>
int image<T>::width() const { return w; }

template <class T>
int image<T>::height() const { return h; }

// A função get_pixel() retorna uma referência constante para o pixel na posição (x, y).
template <class T>
const T& image<T>::get_pixel(int x, int y) const
{
    return access[y][x];
}

// A função set_pixel() atribui um valor ao pixel na posição (x, y).
template <class T>
void image<T>::set_pixel(int x, int y, const T& val)
{
    access[y][x] = val;
}

// Os operadores () sobrecarregados permitem acesso prático como se fosse uma matriz: img(x, y)
template <class T>
T& image<T>::operator()(int x, int y)
{
    return access[y][x];
}

template <class T>
const T& image<T>::operator()(int x, int y) const
{
    return access[y][x];
}

#endif // IMAGE_H
