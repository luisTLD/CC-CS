from area_desenho import PRETO, LARANJA, ROXO, definir_cor, set_pixel, round, limpar
from rasterizacao import desenha_linha, circBresenham
import recorte
import preenchimento

# Cores de destaque da selecao, da janela e do ponto fixo
COR_SELECAO = LARANJA
COR_JANELA = ROXO
COR_PONTO_FIXO = ROXO


# Ponto do plano, tambem usado como vertice
class Ponto:
    def __init__(self, x, y, cor=PRETO):
        self.x = x
        self.y = y
        self.cor = cor


# Reta dada pelos dois extremos
class Reta:
    def __init__(self, x1, y1, x2, y2, cor=PRETO):
        self.x1 = x1
        self.y1 = y1
        self.x2 = x2
        self.y2 = y2
        self.cor = cor


# Poligono dado pela lista de vertices
class Poligono:
    def __init__(self, vertices, cor=PRETO):
        self.vertices = vertices
        self.cor = cor


# Circunferencia dada pelo centro e pelo raio
class Circunferencia:
    def __init__(self, xc, yc, r, cor=PRETO):
        self.xc = xc
        self.yc = yc
        self.r = r
        self.cor = cor


# Preenchimento guardado na cena e refeito a cada redesenho
class Preenchimento:
    def __init__(self, x, y, algoritmo, conectividade, cor_preenche, cor_contorno=None, cor_antiga=None, sem_vazamento=False):
        self.x = x
        self.y = y
        self.algoritmo = algoritmo
        self.conectividade = conectividade
        self.cor_preenche = cor_preenche
        self.cor_contorno = cor_contorno
        self.cor_antiga = cor_antiga
        # Com 8 vizinhos, usa a versao que nao atravessa as quinas do contorno
        self.sem_vazamento = sem_vazamento
        self.cor = cor_preenche


# Objetos desenhados, na ordem em que foram criados
cena = []
selecionados = []
# Referencia marcada pelo usuario para rotacao e escala
ponto_fixo = None
# Mensagem para a interface, como a de recursao estourada
aviso = ""


# Pontos que representam o objeto na selecao e no calculo do centro
def pontos_do_objeto(obj):
    if isinstance(obj, Ponto) or isinstance(obj, Preenchimento):
        return [(obj.x, obj.y)]
    if isinstance(obj, Reta):
        return [(obj.x1, obj.y1), (obj.x2, obj.y2)]
    if isinstance(obj, Poligono):
        return [(v.x, v.y) for v in obj.vertices]
    # Circunferencia: os quatro extremos (esquerda, direita, baixo e cima)
    if isinstance(obj, Circunferencia):
        return [(obj.xc - obj.r, obj.yc), (obj.xc + obj.r, obj.yc),
                (obj.xc, obj.yc - obj.r), (obj.xc, obj.yc + obj.r)]
    return []


# Verifica se (x, y) esta dentro do retangulo
def dentro_do_retangulo(x, y, xmin, xmax, ymin, ymax):
    return xmin <= x <= xmax and ymin <= y <= ymax


# Seleciona os objetos que ficam inteiros dentro do retangulo
def selecionar(xmin, xmax, ymin, ymax):
    selecionados.clear()
    for obj in cena:
        todos_dentro = True
        for (x, y) in pontos_do_objeto(obj):
            if not dentro_do_retangulo(x, y, xmin, xmax, ymin, ymax):
                todos_dentro = False
        if todos_dentro:
            selecionados.append(obj)


# Centro do retangulo que envolve todos os selecionados
def centro_da_selecao():
    xs = []
    ys = []
    # Selecionados por cima, com a cor de destaque
    for obj in selecionados:
        for (x, y) in pontos_do_objeto(obj):
            xs.append(x)
            ys.append(y)
    return (min(xs) + max(xs)) / 2, (min(ys) + max(ys)) / 2


# Desenha um retangulo com as retas do algoritmo escolhido
def desenhar_retangulo(xa, ya, xb, yb, cor):
    definir_cor(cor)
    desenha_linha(xa, ya, xb, ya)
    desenha_linha(xb, ya, xb, yb)
    desenha_linha(xb, yb, xa, yb)
    desenha_linha(xa, yb, xa, ya)


# Roda o algoritmo de preenchimento guardado no objeto
def executar_preenchimento(obj):
    global aviso
    x = round(obj.x)
    y = round(obj.y)
    try:
        if obj.algoritmo == "Boundary":
            if obj.conectividade == 4:
                preenchimento.boundary4(x, y, obj.cor_preenche, obj.cor_contorno)
            elif obj.sem_vazamento:
                preenchimento.boundary8_sem_vazamento(x, y, obj.cor_preenche, obj.cor_contorno)
            else:
                preenchimento.boundary8(x, y, obj.cor_preenche, obj.cor_contorno)
        else:
            if obj.conectividade == 4:
                preenchimento.flood4(x, y, obj.cor_preenche, obj.cor_antiga)
            elif obj.sem_vazamento:
                preenchimento.flood8_sem_vazamento(x, y, obj.cor_preenche, obj.cor_antiga)
            else:
                preenchimento.flood8(x, y, obj.cor_preenche, obj.cor_antiga)
    # Area grande demais para a recursao: avisa em vez de travar
    except RecursionError:
        aviso = "Preenchimento interrompido: a pilha de recursão estourou."


# Desenha o objeto com a sua cor ou com a cor de destaque
def desenhar_objeto(obj, cor=None):
    if isinstance(obj, Preenchimento):
        if cor is None:
            executar_preenchimento(obj)
        else:
            # Preenchimento selecionado: marca so o ponto de inicio
            set_pixel(round(obj.x), round(obj.y), cor)
        return
    if cor is None:
        cor = obj.cor
    definir_cor(cor)
    if isinstance(obj, Ponto):
        set_pixel(round(obj.x), round(obj.y))
    elif isinstance(obj, Reta):
        desenha_linha(round(obj.x1), round(obj.y1), round(obj.x2), round(obj.y2))
    elif isinstance(obj, Poligono):
        n = len(obj.vertices)
        for i in range(n):
            a = obj.vertices[i]
            # O ultimo vertice liga no primeiro para fechar o poligono
            b = obj.vertices[(i + 1) % n]
            desenha_linha(round(a.x), round(a.y), round(b.x), round(b.y))
    elif isinstance(obj, Circunferencia):
        circBresenham(round(obj.xc), round(obj.yc), round(obj.r))


# Desenha so a parte do objeto que fica dentro da janela
def desenhar_objeto_recortado(obj, cor=None):
    # Preenchimento e circunferencia nao aparecem durante o recorte
    if isinstance(obj, Preenchimento) or isinstance(obj, Circunferencia):
        return
    if cor is None:
        cor = obj.cor
    definir_cor(cor)
    if isinstance(obj, Ponto):
        # Ponto so aparece se estiver dentro da janela
        if recorte.ponto_visivel(obj.x, obj.y):
            set_pixel(round(obj.x), round(obj.y))
    elif isinstance(obj, Reta):
        recorte.recortar(obj.x1, obj.y1, obj.x2, obj.y2)
    elif isinstance(obj, Poligono):
        n = len(obj.vertices)
        for i in range(n):
            a = obj.vertices[i]
            b = obj.vertices[(i + 1) % n]
            # Cada lado do poligono e recortado como uma reta separada
            recorte.recortar(a.x, a.y, b.x, b.y)


# Contorno da janela de recorte
def desenhar_janela():
    desenhar_retangulo(recorte.xmin, recorte.ymin, recorte.xmax, recorte.ymax, COR_JANELA)


# Marca o ponto fixo com uma pequena cruz
def desenhar_ponto_fixo():
    x = round(ponto_fixo.x)
    y = round(ponto_fixo.y)
    for (dx, dy) in [(0, 0), (1, 0), (-1, 0), (0, 1), (0, -1)]:
        set_pixel(x + dx, y + dy, COR_PONTO_FIXO)


# Limpa a matriz e desenha a cena inteira de novo
def redesenhar():
    global aviso
    aviso = ""
    limpar()
    recortando = recorte.algoritmo_recorte is not None
    if recortando:
        desenhar_janela()
        for obj in cena:
            desenhar_objeto_recortado(obj)
        for obj in selecionados:
            desenhar_objeto_recortado(obj, COR_SELECAO)
    else:
        for obj in cena:
            desenhar_objeto(obj)
        for obj in selecionados:
            desenhar_objeto(obj, COR_SELECAO)
        if recorte.janela_definida:
            desenhar_janela()
    if ponto_fixo is not None:
        desenhar_ponto_fixo()