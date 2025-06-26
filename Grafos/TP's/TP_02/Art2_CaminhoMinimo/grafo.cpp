#include <iostream>
#include <vector>
#include <utility>
#include <queue>
#include <limits>
#include <cmath>
#include <algorithm> 
#include <cstdlib>
#include <ctime>  
#include "pnm_io.hpp"
#include "image.hpp"
#include <map>

using namespace std;

struct No {
    int indice;
    int x, y;   //posicao
    rgb cor;
    vector<pair<int, double>> vizinhos;  // vizinhos
    double custoF;
    double custoMax;
    double custoMin;
    int pai;
    int p0;
    bool processado;
};

struct Comparador {
    bool operator()(const pair<double, int>& a, const pair<double, int>& b) const {
        return a.first > b.first; // menor custo sai primeiro
    }
};

int largura;
int altura;
int total_nos;
vector<No> nos;
vector<int> sementes;


int indice(int x, int y) {  // de 2d pra 1d
    return y * largura + x;
}

bool dentro_da_imagem(int x, int y) {   // pra nao pegar limite fora
    return (x >= 0 && x < largura && y >= 0 && y < altura);
}

double calcular_peso(const rgb& cor1, const rgb& cor2) {    // distancia euclidiana pra dar peso
    double dr = cor1.r - cor2.r;
    double dg = cor1.g - cor2.g;
    double db = cor1.b - cor2.b;
    return sqrt(dr * dr + dg * dg + db * db);
}

void criar_grafo(image<rgb>* imagem) {  
    largura = imagem->width();
    altura = imagem->height();
    total_nos = largura * altura;

    nos.resize(total_nos);

    for (int y = 0; y < altura; y++) {
        for (int x = 0; x < largura; x++) {
            int idx = indice(x, y);

            nos[idx].indice = idx;      // seta os dados do no
            nos[idx].x = x;
            nos[idx].y = y;
            nos[idx].cor = (*imagem)(x, y);

            nos[idx].pai = -1;
            nos[idx].p0 = -1;
            nos[idx].processado = false;
            nos[idx].custoF = numeric_limits<double>::infinity();   // custo infinito porque so semente é 0
            nos[idx].custoMax = 0;
            nos[idx].custoMin = numeric_limits<double>::infinity();

            int dx[] = {0, -1, 1, 0};
            int dy[] = {-1, 0, 0, 1};

            for (int i = 0; i < 4; i++) {   //pegando os vizinhos
                int nx = x + dx[i];
                int ny = y + dy[i];

                if (dentro_da_imagem(nx, ny)) {
                    int vizinho_idx = indice(nx, ny);
                    rgb cor_vizinho = (*imagem)(nx, ny);

                    double peso = calcular_peso(nos[idx].cor, cor_vizinho);
                    nos[idx].vizinhos.push_back({vizinho_idx, peso});
                }
            }
        }
    }
    cout << "Grafo criado com " << total_nos << " nós." << endl;
}



void gerar_sementes_aleatorias() {
    int num_sementes = static_cast<int>( (largura * altura) * 0.0002 );
    if (num_sementes < 1) num_sementes = 1;
    cout << "Gerando " << num_sementes << " sementes." << endl;

    sementes.clear();
    srand(time(NULL));  // Inicializa aleatoriedade

    while (sementes.size() < num_sementes) {
        int x = rand() % largura;
        int y = rand() % altura;
        int idx = indice(x, y);

        // Garante que não pega sementes duplicadas
        if (find(sementes.begin(), sementes.end(), idx) == sementes.end()) {
            sementes.push_back(idx);
        }
    }

    cout << "Sementes geradas nos indices: ";
    for (int s : sementes) {
        cout << s << " ";
    }
    cout << endl;
}

void inicializar_IFT() {
    for (No& no : nos) {
        no.custoF = numeric_limits<double>::infinity();
        no.pai = -1;
        no.p0 = -1;
        no.processado = false;
    }

    for (int semente : sementes) {
        nos[semente].custoF = 0;        //quem ficou semente recebe 0 ao inves de infinito para ter prioridade na fila
        nos[semente].p0 = semente;
    }
}

void executar_IFT() {
    // Criando a fila de prioridade
    priority_queue<pair<double, int>, vector<pair<double, int>>, Comparador> fila;
    for (int semente : sementes) {
        fila.push({nos[semente].custoF, semente});
    }

    while (!fila.empty()) {
        auto atual = fila.top();
        fila.pop();

        double custo_atual = atual.first;
        int idx_atual = atual.second;

        No& no_atual = nos[idx_atual];

        // Se já processado, ignora
        if (no_atual.processado) continue;
        // Marca como processado
        no_atual.processado = true;

        // Percorre os vizinhos
        for (auto viz : no_atual.vizinhos) {
            int idx_vizinho = viz.first;
            double peso = viz.second;

            No& no_vizinho = nos[idx_vizinho];

            if (no_vizinho.processado) continue;

            // Calcula novo custo
            double novo_custo = no_atual.custoF + peso;

            // Se o custo for melhor, atualiza
            if (novo_custo < no_vizinho.custoF) {
                no_vizinho.custoF = novo_custo;
                no_vizinho.pai = idx_atual;
                no_vizinho.p0 = no_atual.p0;

                // Adiciona/atualiza na fila
                fila.push({novo_custo, idx_vizinho});
            }
        }
    }

    cout << "IFT executado com sucesso!" << endl;
}


void gerar_mapa_de_variacao(const char* nome_arquivo, double porcentagem) {
    image<unsigned char>* mapa = new image<unsigned char>(largura, altura);

    // Primeiro, encontrar o maior peso do grafo
    double maior_peso = -1.0;
    for (const No& no : nos) {
        for (const auto& viz : no.vizinhos) {
            if (viz.second > maior_peso) {
                maior_peso = viz.second;
            }
        }
    }

    // Inicializa tudo como branco
    for (int y = 0; y < altura; y++) {
        for (int x = 0; x < largura; x++) {
            mapa->set_pixel(x, y, 255); // branco
        }
    }

    // Agora percorre as arestas e pinta as transições fortes
    for (const No& no : nos) {
        for (const auto& viz : no.vizinhos) {
            int idx_vizinho = viz.first;
            double peso = viz.second;

            double variacao = (peso / maior_peso) * 100.0;

            if (variacao >= porcentagem) {
                // Pinta os dois pixels da aresta de preto
                mapa->set_pixel(no.x, no.y, 0);
                mapa->set_pixel(nos[idx_vizinho].x, nos[idx_vizinho].y, 0);
            }
        }
    }

    // Salvar como PGM
    ofstream ofs(nome_arquivo, ios::binary);
    ofs << "P5\n" << largura << " " << altura << "\n255\n";
    ofs.write(reinterpret_cast<char*>(mapa->data), largura * altura);
    ofs.close();

    delete mapa;
}



int main() {
    string tipo;

    try {
        image<rgb>* imagem = (image<rgb>*)loadPNMImage("mar.ppm", tipo);
        cout << "Imagem carregada com sucesso!" << endl;
        cout << "Tipo: " << tipo << endl;
        cout << "Largura: " << imagem->width() << endl;
        cout << "Altura: " << imagem->height() << endl;

        criar_grafo(imagem);
        gerar_sementes_aleatorias();
        inicializar_IFT();
        executar_IFT();

        gerar_mapa_de_variacao("variacao_30.pgm", 5.0);  // 30% de variação como limiar - ficou melhor com 5

        delete imagem;

    } catch (pnm_error&) {
        cerr << "Erro ao carregar a imagem!" << endl;
    }

    return 0;
}
