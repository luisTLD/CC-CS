#ifndef IMAGE_H
#define IMAGE_H

#include <iostream>
#include <cstring>  // para memset, memcpy
#include <string>   // para std::string

// Tipo para pixel RGB (8 bits por canal)
typedef unsigned char uchar;
struct rgb { uchar r, g, b; };

enum class ImageType { PGM, PBM, PPM, UNKNOWN };

inline ImageType getImageType(const std::string& type)
{
    if (type == "PGM") return ImageType::PGM;
    if (type == "PBM") return ImageType::PBM;
    if (type == "PPM") return ImageType::PPM;
    return ImageType::UNKNOWN;
}

template <class T>
class image
{
private:
    int w, h;

public:
    T* data;
    T** access;

    image(int width, int height);
    ~image();

    void init(const T& val);
    image<T>* copy() const;

    int width() const;
    int height() const;

    const T& get_pixel(int x, int y) const;
    void set_pixel(int x, int y, const T& val);

    T& operator()(int x, int y);
    const T& operator()(int x, int y) const;
};

// ---------------- IMPLEMENTAÇÕES ---------------- //

template <class T>
image<T>::image(int width, int height)
{
    w = width;
    h = height;

    data = new T[w * h];
    access = new T*[h];

    for (int i = 0; i < h; i++)
        access[i] = data + i * w;

    memset(data, 0, w * h * sizeof(T));  // Zera a memória
}

template <class T>
image<T>::~image()
{
    delete[] access;
    delete[] data;
}

template <class T>
void image<T>::init(const T& val)
{
    for (int i = 0; i < w * h; i++)
        data[i] = val;
}

template <class T>
image<T>* image<T>::copy() const
{
    image<T>* im = new image<T>(w, h);
    memcpy(im->data, data, w * h * sizeof(T));
    return im;
}

template <class T>
int image<T>::width() const { return w; }

template <class T>
int image<T>::height() const { return h; }

template <class T>
const T& image<T>::get_pixel(int x, int y) const
{
    return access[y][x];
}

template <class T>
void image<T>::set_pixel(int x, int y, const T& val)
{
    access[y][x] = val;
}

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