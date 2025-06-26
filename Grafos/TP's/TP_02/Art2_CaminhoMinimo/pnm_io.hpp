    #ifndef PNM_IO_HPP
    #define PNM_IO_HPP

    #include <fstream>
    #include <cstring>
    #include <cstdlib>

    #include "image.hpp"

    class pnm_error { };

    // Lê largura, altura e max_val em um único loop, ignorando comentários
    static void pnm_read_all_header_info(std::ifstream &file, int &width, int &height, int &max_val, bool has_max_val)
    {
        char buf[256];
        int values_read = 0;

        while (values_read < (has_max_val ? 3 : 2))
        {
            char c;
            file >> c;

            if (c == '#')
            {
                file.ignore(256, '\n');
                continue;
            }

            file.putback(c);
            file.width(256);
            file >> buf;
            file.ignore();

            int val = std::atoi(buf);
            switch (values_read)
            {
                case 0: width = val; break;
                case 1: height = val; break;
                case 2: max_val = val; break;
            }

            values_read++;
        }

        if (!has_max_val)
            max_val = 1; // padrão para PBM
    }

    // Função para ler PBM (P4, 1 bit por pixel)
    static void read_packed(unsigned char* data, int size, std::ifstream &f)
    {
        unsigned char byte = 0;
        int bitshift = -1;
        for (int pos = 0; pos < size; pos++)
        {
            if (bitshift == -1)
            {
                byte = f.get();
                bitshift = 7;
            }
            data[pos] = (byte >> bitshift) & 1;
            bitshift--;
        }
    }

    // Carrega PBM (P4)
    static image<unsigned char>* loadPBM(std::ifstream &file)
    {
        int width, height, max_val;
        pnm_read_all_header_info(file, width, height, max_val, false);

        image<unsigned char>* img = new image<unsigned char>(width, height);
        for (int y = 0; y < height; y++) 
            read_packed(img->access[y], width, file);

        return img;
    }

    // Carrega PGM (P5)
    static image<unsigned char>* loadPGM(std::ifstream &file)
    {
        int width, height, max_val;
        pnm_read_all_header_info(file, width, height, max_val, true);
        if (max_val > 255) throw pnm_error();

        image<unsigned char>* img = new image<unsigned char>(width, height);
        file.read(reinterpret_cast<char*>(img->data), width * height);
        if (!file) throw pnm_error();

        return img;
    }

    // Carrega PPM (P6)
    static image<rgb>* loadPPM(std::ifstream &file)
    {
        int width, height, max_val;
        pnm_read_all_header_info(file, width, height, max_val, true);
        if (max_val > 255) throw pnm_error();

        image<rgb>* img = new image<rgb>(width, height);
        file.read(reinterpret_cast<char*>(img->data), width * height * sizeof(rgb));
        if (!file) throw pnm_error();

        return img;
    }

    // Função genérica: carrega PBM, PGM ou PPM dependendo do cabeçalho
    static void* loadPNMImage(const char* filename, std::string& type)
    {
        std::ifstream file(filename, std::ios::binary);
        if (!file) throw pnm_error();

        char header[3];
        file.read(header, 2);
        header[2] = '\0';

        if (header[0] != 'P')
        {
            throw pnm_error();
        }

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
                throw pnm_error(); // tipo desconhecido
        }

    }
    
    // Função para salvar imagem rgb em arquivo PPM (P6)
    void savePPM(const char* filename, const image<rgb>* img)
    {
        std::ofstream ofs(filename, std::ios::binary);
        if (!ofs)
        {
            std::cerr << "Erro ao abrir arquivo para salvar imagem\n";
            return;
        }

        int width = img->width();
        int height = img->height();

        ofs << "P6\n" << width << " " << height << "\n255\n";

        ofs.write(reinterpret_cast<const char*>(img->data), width * height * sizeof(rgb));
        ofs.close();
    }

    #endif