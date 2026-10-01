from area_desenho import round
from rasterizacao import desenha_linha

# Limites da janela com os nomes do Cohen-Sutherland
xmin = 0
xmax = 0
ymin = 0
ymax = 0

# Mesmos limites com os nomes do Liang-Barsky
xjmin = 0
xjmax = 0
yjmin = 0
yjmax = 0

janela_definida = False
# None quando o recorte esta desligado
algoritmo_recorte = None


# Guarda a janela marcada com o mouse, arrastada em qualquer direcao
def definir_janela(xa, ya, xb, yb):
    global xmin, xmax, ymin, ymax, xjmin, xjmax, yjmin, yjmax, janela_definida
    xmin = min(xa, xb)
    xmax = max(xa, xb)
    ymin = min(ya, yb)
    ymax = max(ya, yb)
    xjmin = xmin
    xjmax = xmax
    yjmin = ymin
    yjmax = ymax
    janela_definida = True


# Recorte de pontos: visivel se estiver dentro da janela (slide 07)
def ponto_visivel(x, y):
    return xjmin <= x <= xjmax and yjmin <= y <= yjmax


# Codigo de regiao: esquerda 1, direita 2, abaixo 4, acima 8
def region_code(x, y):
    codigo = 0
    if x < xmin:
        codigo = codigo + 1
    if x > xmax:
        codigo = codigo + 2
    if y < ymin:
        codigo = codigo + 4
    if y > ymax:
        codigo = codigo + 8
    return codigo


# Devolve o bit da posicao dada (0 a 3)
def bit(valor, posicao):
    return (valor >> posicao) & 1


# Cohen-Sutherland (slide 07)
def Cohen_Sutherland(x1, y1, x2, y2):
    aceite = False
    feito = False
    while not feito:
        c1 = region_code(x1, y1)
        c2 = region_code(x2, y2)
        # Os dois codigos zerados: segmento todo dentro
        if c1 == 0 and c2 == 0:
            aceite = True
            feito = True
        # Bit 1 na mesma posicao nos dois: segmento todo fora
        elif (c1 & c2) != 0:
            feito = True
        else:
            # Escolhe um extremo que esta fora da janela
            if c1 != 0:
                cfora = c1
            else:
                cfora = c2
            # Intersecao com a borda do bit ligado
            if bit(cfora, 0) == 1:
                xint = xmin
                yint = y1 + (y2 - y1) * (xmin - x1) / (x2 - x1)
            elif bit(cfora, 1) == 1:
                xint = xmax
                yint = y1 + (y2 - y1) * (xmax - x1) / (x2 - x1)
            elif bit(cfora, 2) == 1:
                yint = ymin
                xint = x1 + (x2 - x1) * (ymin - y1) / (y2 - y1)
            elif bit(cfora, 3) == 1:
                yint = ymax
                xint = x1 + (x2 - x1) * (ymax - y1) / (y2 - y1)
            # Troca o extremo de fora pela intersecao e testa de novo
            if c1 == cfora:
                x1 = xint
                y1 = yint
            else:
                x2 = xint
                y2 = yint
    # So arredonda na hora de desenhar
    if aceite:
        desenha_linha(round(x1), round(y1), round(x2), round(y2))


# Testa uma borda e atualiza u1 (entrada) ou u2 (saida) (slide 07)
def cliptest(p, q, u1, u2):
    result = True
    # p menor que 0: a reta vai de fora para dentro dessa borda
    if p < 0.0:
        r = q / p
        if r > u2:
            result = False
        elif r > u1:
            u1 = r
    # p maior que 0: vai de dentro para fora
    elif p > 0.0:
        r = q / p
        if r < u1:
            result = False
        elif r < u2:
            u2 = r
    # p igual a 0: paralela a borda, com q menor que 0 esta fora
    elif q < 0.0:
        result = False
    # Python nao passa u1 e u2 por referencia, entao eles voltam no retorno
    return result, u1, u2


# Liang-Barsky (slide 07)
def Liang_Barsky(x1, y1, x2, y2):
    u1 = 0.0
    u2 = 1.0
    dx = x2 - x1
    dy = y2 - y1
    # Bordas na ordem esquerda, direita, abaixo e acima, os se ficam aninhados
    result, u1, u2 = cliptest(-dx, x1 - xjmin, u1, u2)
    if result:
        result, u1, u2 = cliptest(dx, xjmax - x1, u1, u2)
        if result:
            result, u1, u2 = cliptest(-dy, y1 - yjmin, u1, u2)
            if result:
                result, u1, u2 = cliptest(dy, yjmax - y1, u1, u2)
                if result:
                    # Atualiza so no final, x2 primeiro, porque usa o x1 original
                    if u2 < 1.0:
                        x2 = x1 + u2 * dx
                        y2 = y1 + u2 * dy
                    if u1 > 0.0:
                        x1 = x1 + u1 * dx
                        y1 = y1 + u1 * dy
                    desenha_linha(round(x1), round(y1), round(x2), round(y2))


# Recorta e desenha o segmento com o algoritmo escolhido
def recortar(x1, y1, x2, y2):
    if algoritmo_recorte == "Cohen-Sutherland":
        Cohen_Sutherland(x1, y1, x2, y2)
    else:
        Liang_Barsky(x1, y1, x2, y2)