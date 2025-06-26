#ifndef GAUSSIAN_FILTER_HPP
#define GAUSSIAN_FILTER_HPP

#include <vector>
#include <cmath>
#include <algorithm>
#include "image.hpp"

// A constante GAUSS_WIDTH define a largura da janela do filtro Gaussiano em desvios padrão.
// Um valor maior resulta em um kernel mais largo, que produz um desfoque mais forte.
#define GAUSS_WIDTH 8.0f

namespace gaussian {

// Esta função auxiliar calcula o quadrado de um número.
// Será utilizada na definição da função Gaussiana.
inline float square(float x) { return x * x; }

// Esta função gera o kernel (máscara) 1D da função Gaussiana com base no sigma fornecido.
// Apenas metade do kernel mais o centro são computados, pois a função é simétrica.
inline std::vector<float> makeGaussianKernel(float sigma)
{
    // Evita que sigma seja muito pequeno e cause instabilidade numérica.
    sigma = std::max(sigma, 0.01f);

    // O tamanho do kernel é determinado como GAUSS_WIDTH * sigma arredondado para cima, mais 1.
    // Isto garante que a maior parte da energia da função Gaussiana seja capturada.
    int len = static_cast<int>(std::ceil(sigma * GAUSS_WIDTH)) + 1;
    std::vector<float> kernel(len);

    // Cada valor do kernel é calculado a partir da equação da função Gaussiana.
    for (int i = 0; i < len; i++)
    {
        float x = static_cast<float>(i);
        kernel[i] = std::exp(-0.5f * square(x / sigma));
    }

    // A soma dos valores do kernel é feita para normalização.
    // Como o kernel será refletido para ambos os lados, o centro soma uma vez e os outros somam duas.
    float sum = kernel[0];
    for (int i = 1; i < len; i++)
        sum += 2 * kernel[i];

    // O kernel é normalizado para garantir que a soma total seja 1.
    for (int i = 0; i < len; i++)
        kernel[i] /= sum;

    return kernel;
}

// Esta função trata os pixels que estão fora dos limites da imagem aplicando espelhamento simétrico.
// Essa técnica evita artefatos nas bordas durante a convolução.
inline int reflectIndex(int p, int max)
{
    if (p < 0)
        return -p - 1;
    else if (p >= max)
        return 2 * max - p - 1;
    else
        return p;
}

// Esta função aplica a convolução 1D horizontalmente com o kernel fornecido.
// As bordas são tratadas com espelhamento para preservar a continuidade visual.
inline void convolveHorizontal(const image<float>* src, image<float>* dst, const std::vector<float>& kernel)
{
    int width = src->width();
    int height = src->height();
    int radius = static_cast<int>(kernel.size()) - 1;

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            // O valor central é computado primeiro.
            float sum = kernel[0] * src->get_pixel(x, y);

            // Para cada offset, o valor correspondente é somado simetricamente dos dois lados.
            for (int i = 1; i <= radius; i++)
            {
                int x1 = reflectIndex(x - i, width);
                int x2 = reflectIndex(x + i, width);
                sum += kernel[i] * (src->get_pixel(x1, y) + src->get_pixel(x2, y));
            }

            dst->set_pixel(x, y, sum);
        }
    }
}

// A função abaixo aplica a convolução verticalmente utilizando o mesmo kernel.
// Esse processo separável (horizontal + vertical) reduz a complexidade computacional de O(n²) para O(n).
inline void convolveVertical(const image<float>* src, image<float>* dst, const std::vector<float>& kernel)
{
    int width = src->width();
    int height = src->height();
    int radius = static_cast<int>(kernel.size()) - 1;

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            float sum = kernel[0] * src->get_pixel(x, y);
            for (int i = 1; i <= radius; i++)
            {
                int y1 = reflectIndex(y - i, height);
                int y2 = reflectIndex(y + i, height);
                sum += kernel[i] * (src->get_pixel(x, y1) + src->get_pixel(x, y2));
            }

            dst->set_pixel(x, y, sum);
        }
    }
}

// Esta função realiza a suavização Gaussiana em imagens do tipo float.
// Ela aplica uma convolução separável (horizontal seguida de vertical).
// Este passo corresponde à primeira etapa do pipeline do artigo, que visa reduzir o ruído.
inline image<float>* gaussianSmooth(const image<float>* src, float sigma)
{
    std::vector<float> kernel = makeGaussianKernel(sigma);
    image<float>* tmp = new image<float>(src->width(), src->height());
    image<float>* dst = new image<float>(src->width(), src->height());

    convolveHorizontal(src, tmp, kernel);
    convolveVertical(tmp, dst, kernel);

    delete tmp;
    return dst;
}

// Esta função converte imagens do tipo unsigned char (0-255) para float (valores contínuos).
// Essa conversão é necessária para aplicar a suavização Gaussiana com maior precisão.
inline image<float>* imageUCHARtoFLOAT(const image<unsigned char>* src)
{
    int w = src->width();
    int h = src->height();
    image<float>* dst = new image<float>(w, h);
    for (int y = 0; y < h; y++)
        for (int x = 0; x < w; x++)
            dst->set_pixel(x, y, static_cast<float>(src->get_pixel(x, y)));
    return dst;
}

// Esta função aplica suavização Gaussiana em imagens em tons de cinza.
// Primeiro, a imagem é convertida para float e depois suavizada.
inline image<float>* gaussianSmooth(const image<unsigned char>* src, float sigma)
{
    image<float>* float_img = imageUCHARtoFLOAT(src);
    image<float>* smooth_img = gaussianSmooth(float_img, sigma);
    delete float_img;
    return smooth_img;
}

// Esta função aplica o filtro Gaussiano a imagens coloridas RGB.
// Cada canal (R, G, B) é processado independentemente.
inline std::vector<image<float>*> gaussianSmooth(const image<rgb>* src, float sigma)
{
    int w = src->width();
    int h = src->height();
    image<float>* r = new image<float>(w, h);
    image<float>* g = new image<float>(w, h);
    image<float>* b = new image<float>(w, h);

    // Cada canal é extraído da imagem original e convertido para float.
    for (int y = 0; y < h; y++)
    {
        for (int x = 0; x < w; x++)
        {
            rgb px = src->get_pixel(x, y);
            r->set_pixel(x, y, static_cast<float>(px.r));
            g->set_pixel(x, y, static_cast<float>(px.g));
            b->set_pixel(x, y, static_cast<float>(px.b));
        }
    }

    // O filtro Gaussiano é aplicado separadamente a cada canal.
    auto smooth_r = gaussianSmooth(r, sigma);
    auto smooth_g = gaussianSmooth(g, sigma);
    auto smooth_b = gaussianSmooth(b, sigma);

    delete r;
    delete g;
    delete b;

    // Os três canais suavizados são retornados como vetor.
    return { smooth_r, smooth_g, smooth_b };
}

// Esta função converte imagens float para unsigned char (0–255) com arredondamento.
// O valor é saturado para evitar overflow (valores acima de 255 ou abaixo de 0).
inline image<unsigned char>* convertFloatToUCharRounded(const image<float>* src)
{
    int w = src->width();
    int h = src->height();
    image<unsigned char>* dst = new image<unsigned char>(w, h);

    for (int y = 0; y < h; y++)
    {
        for (int x = 0; x < w; x++)
        {
            float val = src->get_pixel(x, y);
            int rounded = static_cast<int>(std::round(val));
            if (rounded < 0) rounded = 0;
            else if (rounded > 255) rounded = 255;
            dst->set_pixel(x, y, static_cast<unsigned char>(rounded));
        }
    }

    return dst;
}

// Esta função converte os três canais RGB suavizados (em float) para o formato uchar.
// Após a conversão, as imagens temporárias em float são liberadas.
inline std::vector<image<unsigned char>*> convertFloatRGBToUChar(const std::vector<image<float>*>& float_imgs)
{
    std::vector<image<unsigned char>*> result;
    for (auto img_f : float_imgs)
    {
        result.push_back(convertFloatToUCharRounded(img_f));
        delete img_f;
    }
    return result;
}

} // namespace gaussian

#endif // GAUSSIAN_FILTER_HPP
