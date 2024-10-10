#include <iostream>
#include <fstream>

using namespace std;

// Funcao para retornar a expressao
char expressao(const string& mnemonico)
{
    // Realiza a expressao com base no mnemonico
    if (mnemonico == "umL") return '0';                    // Um logico umL
    else if (mnemonico == "AonB") return '1';              // A mais B negado
    else if (mnemonico == "copiaA") return '2';            // A copiaA
    else if (mnemonico == "nAxnB") return '3';             // A negado XOU B negado
    else if (mnemonico == "AeBn") return '4';              // A E B negado
    else if (mnemonico == "nA") return '5';                // A negado
    else if (mnemonico == "AenB") return '6';              // A E B negado
    else if (mnemonico == "nAonB") return '7';             // A negado ou B
    else if (mnemonico == "AxB") return '8';               // A XOU B
    else if (mnemonico == "zeroL") return '9';             // Zero logico zeroL
    else if (mnemonico == "copiaB") return 'A';            // B copiaB (retorna o primeiro caractere de B)
    else if (mnemonico == "AeB") return 'B';               // A E B (retorna resultado logico como caractere)
    else if (mnemonico == "nAeBn") return 'D';             // A negado E B negado
    else if (mnemonico == "AoB") return 'E';               // A ou B
    else if (mnemonico == "nAeB") return 'F';              // A negado E B
    else if (mnemonico == "nB") return 'C';                // B negado
    else return 'X';  
}

int main()
{
    // Variaveis para armazenar os valores de X, Y e W, alem de A e B
    string x = "0", y = "0", w = "0", A = "0", B = "0";

    try
    {
        // Leitura do arquivo testeula.ula
        ifstream arquivo("testeula.ula");
        ofstream arquivoHex("testeula.hex", ios::out);

        string linha;
        // Enquanto houver linhas no arquivo, le a linha
        while (getline(arquivo, linha))
        {
            // Verifica se a linha contem X, Y ou W e atribui a variavel correspondente
            if (linha.find("X=") != string::npos)
            {
                x = linha.substr(2);
                if (x[x.size() - 1] == ';') x.erase(x.size() - 1);
            }
            else if (linha.find("Y=") != string::npos)
            {
                y = linha.substr(2);
                if (y[y.size() - 1] == ';') y.erase(y.size() - 1);
            }
            else if (linha.find("W=") != string::npos)
            {
                string mnemonico = linha.substr(2); // Pegando o mnemonico a partir da linha
                if (mnemonico[mnemonico.size() - 1] == ';') mnemonico.erase(mnemonico.size() - 1);

                // Define A e B como valores hexadecimais baseados nos valores de X e Y
                A = x;  // A recebe o valor de X
                B = y;  // B recebe o valor de Y

                // Resolve a expressao de acordo com o mnemonico
                w = expressao(mnemonico);  // Retorna expressao
 
                // Escreve o resultado tambem em hexadecimal no arquivo
                arquivoHex << A << B << w << endl;
            }
        }

        // Fecha o arquivo
        arquivo.close();
        arquivoHex.close();
    }
    catch (const exception& e)
    {
        cerr << "Erro ao processar o arquivo: " << e.what() << endl;
        return 1;
    }

    return 0;
}
