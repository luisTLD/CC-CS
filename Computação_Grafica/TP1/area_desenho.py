import tkinter as tk
import math

# Tamanho da matriz de pixels, na tela cada pixel vira um quadrado de TAM_PIXEL
LARGURA = 201
ALTURA = 151
TAM_PIXEL = 4

# Posicao da origem (0, 0) do plano dentro da matriz
X_ORIGEM = LARGURA // 2
Y_ORIGEM = ALTURA // 2

# Cada posicao da matriz guarda o numero de uma cor da PALETA
FUNDO = 0
PRETO = 1
VERMELHO = 2
AZUL = 3
VERDE = 4
AMARELO = 5
LARANJA = 6
ROXO = 7

PALETA = {
    FUNDO: "#ffffff",
    PRETO: "#000000",
    VERMELHO: "#e02020",
    AZUL: "#2050e0",
    VERDE: "#20a040",
    AMARELO: "#e0c000",
    LARANJA: "#ff8c00",
    ROXO: "#9030c0",
}

COR_EIXOS = "#d8d8d8"
# Valor que inquirir_cor devolve para posicoes fora da matriz
FORA_DA_AREA = -1

# Cor usada pelo set_pixel quando nenhuma cor e passada
cor_atual = PRETO

# Matriz de pixels, acessada como matriz[linha][coluna]
matriz = [[FUNDO] * LARGURA for _ in range(ALTURA)]


# Converte (x, y) do plano para (linha, coluna) da matriz
def mundo_para_matriz(x, y):
    coluna = x + X_ORIGEM
    # y cresce para cima no plano e para baixo na matriz
    linha = -y + Y_ORIGEM
    return linha, coluna


# Converte a posicao do mouse no canvas para (x, y) do plano
def tela_para_mundo(px, py):
    coluna = px // TAM_PIXEL
    linha = py // TAM_PIXEL
    x = coluna - X_ORIGEM
    y = -(linha - Y_ORIGEM)
    return x, y


# Verifica se a posicao existe na matriz
def dentro_da_matriz(linha, coluna):
    return 0 <= linha < ALTURA and 0 <= coluna < LARGURA


# Define a cor dos proximos set_pixel
def definir_cor(cor):
    global cor_atual
    cor_atual = cor


# Acende o pixel (x, y) com a cor dada ou com a cor atual
def set_pixel(x, y, cor=None):
    if cor is None:
        cor = cor_atual
    linha, coluna = mundo_para_matriz(x, y)
    # Pixel fora da matriz e ignorado
    if dentro_da_matriz(linha, coluna):
        matriz[linha][coluna] = cor


# Mesmo que set_pixel, com o nome usado no slide do Bresenham
def colora_pixel(x, y, cor=None):
    set_pixel(x, y, cor)


# Arredonda 0.5 para longe do zero, igual ao round do Pascal
def round(valor):
    if valor >= 0:
        return int(math.floor(valor + 0.5))
    else:
        return -int(math.floor(-valor + 0.5))


# Devolve a cor do pixel (x, y), usada nos preenchimentos
def inquirir_cor(x, y):
    linha, coluna = mundo_para_matriz(x, y)
    if dentro_da_matriz(linha, coluna):
        return matriz[linha][coluna]
    return FORA_DA_AREA


# Volta toda a matriz para a cor de fundo
def limpar():
    for linha in range(ALTURA):
        for coluna in range(LARGURA):
            matriz[linha][coluna] = FUNDO


# Objetos do Tkinter que mostram a matriz na tela
canvas_area = None
id_imagem = None
imagem_base = None
imagem_tela = None


# Liga a matriz ao canvas e mostra a primeira imagem
def iniciar(canvas):
    global canvas_area, id_imagem, imagem_base
    canvas_area = canvas
    imagem_base = tk.PhotoImage(width=LARGURA, height=ALTURA)
    id_imagem = canvas_area.create_image(0, 0, anchor="nw")
    atualizar_tela()


# Copia a matriz para a imagem do canvas
def atualizar_tela():
    global imagem_tela
    linhas_da_imagem = []
    for linha in range(ALTURA):
        cores = []
        for coluna in range(LARGURA):
            cor = matriz[linha][coluna]
            # Os eixos so aparecem na tela, nao sao gravados na matriz
            if cor == FUNDO and (linha == Y_ORIGEM or coluna == X_ORIGEM):
                cores.append(COR_EIXOS)
            else:
                cores.append(PALETA[cor])
        linhas_da_imagem.append("{" + " ".join(cores) + "}")
    imagem_base.put(" ".join(linhas_da_imagem), to=(0, 0))
    # Amplia a imagem para cada pixel da matriz ficar visivel
    imagem_tela = imagem_base.zoom(TAM_PIXEL, TAM_PIXEL)
    canvas_area.itemconfig(id_imagem, image=imagem_tela)