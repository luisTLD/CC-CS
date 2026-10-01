import tkinter as tk
from tkinter import ttk
import math
import area_desenho as ad
import rasterizacao as rast
import estruturas as est
import recorte as rec
import transformacoes as trans

# Vertices do poligono que esta sendo desenhado
pontos_clicados = []
# Onde o arraste comecou (reta, circunferencia, selecao e janela)
inicio_arraste = None


# Mostra um aviso no painel
def mostrar_mensagem(texto):
    rotulo_mensagem.config(text=texto)


# Redesenha a cena na matriz e mostra na tela
def atualizar():
    est.redesenhar()
    ad.atualizar_tela()
    if est.aviso != "":
        mostrar_mensagem(est.aviso)


# Muda o modo do clique e descarta o poligono pela metade
def trocar_modo():
    pontos_clicados.clear()
    rotulo_modo.config(text="Modo: " + modo_escolhido.get())
    atualizar()


# Muda o modo a partir de um botao
def mudar_modo(novo_modo):
    modo_escolhido.set(novo_modo)
    trocar_modo()


# Apaga objetos, selecao, ponto fixo e recorte
def limpar_area():
    pontos_clicados.clear()
    est.cena.clear()
    est.selecionados.clear()
    est.ponto_fixo = None
    rec.janela_definida = False
    rec.algoritmo_recorte = None
    mostrar_mensagem("")
    atualizar()


# Troca entre DDA e Bresenham e redesenha tudo
def trocar_algoritmo():
    rast.algoritmo_reta = algoritmo_escolhido.get()
    atualizar()


# Mostra os lados ja clicados e um lado ate o mouse
def mostrar_poligono_em_construcao(x_mouse, y_mouse):
    est.redesenhar()
    ad.definir_cor(cor_escolhida.get())
    for i in range(len(pontos_clicados) - 1):
        a = pontos_clicados[i]
        b = pontos_clicados[i + 1]
        rast.desenha_linha(a.x, a.y, b.x, b.y)
    ultimo = pontos_clicados[-1]
    rast.desenha_linha(ultimo.x, ultimo.y, x_mouse, y_mouse)
    ad.atualizar_tela()


# Mostra as coordenadas do mouse e a previa do poligono
def ao_mover_mouse(evento):
    x, y = ad.tela_para_mundo(evento.x, evento.y)
    rotulo_coordenadas.config(text=f"x = {x}   y = {y}")
    if modo_escolhido.get() == "Polígono" and len(pontos_clicados) > 0:
        mostrar_poligono_em_construcao(x, y)


# Cria o preenchimento no ponto clicado com as opcoes da aba Preencher
def preencher_em(x, y):
    cor = cor_preenchimento.get()
    algoritmo = algoritmo_fill.get()
    if algoritmo == "Boundary":
        obj = est.Preenchimento(x, y, algoritmo, conectividade.get(), cor, cor_contorno=cor_contorno.get(),
                                sem_vazamento=evitar_vazamento.get())
    else:
        # No Flood, a cor antiga e a cor do pixel clicado
        cor_antiga = ad.inquirir_cor(x, y)
        if cor_antiga == cor:
            mostrar_mensagem("Esse pixel já tem a cor de preenchimento.")
            return
        obj = est.Preenchimento(x, y, algoritmo, conectividade.get(), cor, cor_antiga=cor_antiga,
                                sem_vazamento=evitar_vazamento.get())
    est.cena.append(obj)
    mostrar_mensagem("")
    atualizar()


# Clique esquerdo: a acao depende do modo
def ao_pressionar(evento):
    global inicio_arraste
    x, y = ad.tela_para_mundo(evento.x, evento.y)
    modo = modo_escolhido.get()
    if modo == "Ponto":
        est.cena.append(est.Ponto(x, y, cor_escolhida.get()))
        atualizar()
    elif modo in ["Reta", "Circunferência", "Selecionar", "Janela de recorte"]:
        # Modos de arraste: por enquanto so guarda o inicio
        inicio_arraste = est.Ponto(x, y)
    elif modo == "Polígono":
        pontos_clicados.append(est.Ponto(x, y))
        mostrar_poligono_em_construcao(x, y)
    elif modo == "Ponto fixo":
        est.ponto_fixo = est.Ponto(x, y)
        referencia.set("Ponto fixo")
        mostrar_mensagem(f"Ponto fixo em ({x}, {y}).")
        atualizar()
    elif modo == "Preencher":
        preencher_em(x, y)


# Cria a reta ou a circunferencia do arraste
def criar_objeto_arrastado(x, y):
    cor = cor_escolhida.get()
    x1 = inicio_arraste.x
    y1 = inicio_arraste.y
    if modo_escolhido.get() == "Reta":
        return est.Reta(x1, y1, x, y, cor)
    else:
        # Circunferencia: o arraste e o diametro
        xc = (x1 + x) / 2
        yc = (y1 + y) / 2
        r = math.sqrt((x - x1) ** 2 + (y - y1) ** 2) / 2
        return est.Circunferencia(xc, yc, r, cor)


# Mostra a previa do que esta sendo arrastado
def ao_arrastar(evento):
    ao_mover_mouse(evento)
    if inicio_arraste is None:
        return
    x, y = ad.tela_para_mundo(evento.x, evento.y)
    modo = modo_escolhido.get()
    est.redesenhar()
    if modo == "Selecionar":
        est.desenhar_retangulo(inicio_arraste.x, inicio_arraste.y, x, y, est.COR_SELECAO)
    elif modo == "Janela de recorte":
        est.desenhar_retangulo(inicio_arraste.x, inicio_arraste.y, x, y, est.COR_JANELA)
    else:
        est.desenhar_objeto(criar_objeto_arrastado(x, y))
    ad.atualizar_tela()


# Fim do arraste: seleciona, define a janela ou cria o objeto
def ao_soltar(evento):
    global inicio_arraste
    if inicio_arraste is None:
        return
    x, y = ad.tela_para_mundo(evento.x, evento.y)
    modo = modo_escolhido.get()
    x1 = inicio_arraste.x
    y1 = inicio_arraste.y
    if modo == "Selecionar":
        est.selecionar(min(x1, x), max(x1, x), min(y1, y), max(y1, y))
        mostrar_mensagem(f"{len(est.selecionados)} selecionados.")
    elif modo == "Janela de recorte":
        rec.definir_janela(x1, y1, x, y)
        mostrar_mensagem(f"Janela: {rec.xmin} ≤ x ≤ {rec.xmax}, {rec.ymin} ≤ y ≤ {rec.ymax}")
    else:
        est.cena.append(criar_objeto_arrastado(x, y))
    inicio_arraste = None
    atualizar()


# Clique direito fecha o poligono (precisa de 3 vertices)
def ao_clicar_direito(evento):
    if modo_escolhido.get() == "Polígono" and len(pontos_clicados) >= 3:
        est.cena.append(est.Poligono(list(pontos_clicados), cor_escolhida.get()))
    pontos_clicados.clear()
    atualizar()


# Ponto de referencia escolhido para rotacao e escala
def ponto_de_referencia():
    ref = referencia.get()
    if ref == "Origem":
        return 0, 0
    if ref == "Ponto fixo":
        if est.ponto_fixo is None:
            return None
        return est.ponto_fixo.x, est.ponto_fixo.y
    return est.centro_da_selecao()


# Aplica a matriz nos selecionados, em volta da referencia quando pedido
def aplicar_transformacao(M, usar_referencia, fator_raio=1):
    if len(est.selecionados) == 0:
        mostrar_mensagem("Selecionar objetos")
        return
    if usar_referencia:
        ref = ponto_de_referencia()
        if ref is None:
            mostrar_mensagem("Marcar o ponto")
            return
        M = trans.em_relacao_a(M, ref[0], ref[1])
    for obj in est.selecionados:
        trans.transformar_objeto(obj, M, fator_raio)
    mostrar_mensagem("")
    atualizar()


# Cada botao monta a matriz com os valores dos controles
def transladar():
    aplicar_transformacao(trans.translacao(tx.get(), ty.get()), False)


def rotacionar():
    aplicar_transformacao(trans.rotacao(angulo.get()), True)


def escalar():
    # O raio da circunferencia usa a media dos fatores de escala
    fator_raio = (abs(sx.get()) + abs(sy.get())) / 2
    aplicar_transformacao(trans.escala(sx.get(), sy.get()), True, fator_raio)


# Reflexoes sao em relacao aos eixos, sem ponto de referencia
def refletir_x():
    aplicar_transformacao(trans.reflexao_x(), False)


def refletir_y():
    aplicar_transformacao(trans.reflexao_y(), False)


def refletir_xy():
    aplicar_transformacao(trans.reflexao_xy(), False)


# Liga o recorte com o algoritmo escolhido
def aplicar_recorte(nome):
    if not rec.janela_definida:
        mostrar_mensagem("Marque a janela")
        return
    rec.algoritmo_recorte = nome
    mostrar_mensagem("Recorte: " + nome)
    atualizar()


# Desliga o recorte e volta a mostrar tudo
def remover_recorte():
    rec.algoritmo_recorte = None
    mostrar_mensagem("")
    atualizar()


# Cria um grupo de botoes de opcao em colunas
def grade_de_opcoes(pai, variavel, opcoes, colunas, comando=None):
    quadro = tk.Frame(pai)
    quadro.pack(anchor="w", fill="x")
    for i, (texto, valor) in enumerate(opcoes):
        botao = tk.Radiobutton(quadro, text=texto, variable=variavel, value=valor, command=comando)
        botao.grid(row=i // colunas, column=i % colunas, sticky="w")


# Titulo em negrito dentro de uma aba
def titulo(pai, texto):
    tk.Label(pai, text=texto, font=("Arial", 9, "bold")).pack(anchor="w", pady=(6, 0))


# Controle deslizante para escolher um valor com o mouse
def controle_deslizante(pai, texto, variavel, minimo, maximo, passo, tamanho=220):
    tk.Scale(pai, label=texto, variable=variavel, from_=minimo, to=maximo, resolution=passo,
             orient="horizontal", length=tamanho).pack(side="left", anchor="w")


# Janela principal
janela = tk.Tk()
janela.title("TP1")
janela.resizable(False, False)

# Area de Desenho: cada pixel da matriz ocupa TAM_PIXEL pixels da tela
canvas = tk.Canvas(janela, width=ad.LARGURA * ad.TAM_PIXEL, height=ad.ALTURA * ad.TAM_PIXEL, bg="white", cursor="crosshair")
canvas.grid(row=0, column=0, sticky="n", padx=8, pady=8)
canvas.bind("<Motion>", ao_mover_mouse)
canvas.bind("<ButtonPress-1>", ao_pressionar)
canvas.bind("<B1-Motion>", ao_arrastar)
canvas.bind("<ButtonRelease-1>", ao_soltar)
canvas.bind("<Button-3>", ao_clicar_direito)

# Painel da direita com as informacoes e as abas
painel = tk.Frame(janela)
painel.grid(row=0, column=1, sticky="n", padx=8, pady=8)

rotulo_coordenadas = tk.Label(painel, text="x = 0   y = 0", font=("Consolas", 11))
rotulo_coordenadas.pack(anchor="w")
rotulo_modo = tk.Label(painel, text="Modo: Ponto", font=("Arial", 10, "bold"))
rotulo_modo.pack(anchor="w")
rotulo_mensagem = tk.Label(painel, text="", fg="#b00000", wraplength=240, justify="left", height=2, anchor="nw")
rotulo_mensagem.pack(anchor="w", fill="x")

abas = ttk.Notebook(painel)
abas.pack(fill="both")

aba_desenho = tk.Frame(abas, padx=6, pady=4)
aba_transformar = tk.Frame(abas, padx=6, pady=4)
aba_recorte = tk.Frame(abas, padx=6, pady=4)
aba_preencher = tk.Frame(abas, padx=6, pady=4)
abas.add(aba_desenho, text="Desenho")
abas.add(aba_transformar, text="Transformar")
abas.add(aba_recorte, text="Recorte")
abas.add(aba_preencher, text="Preencher")

# Opcoes escolhidas na interface
modo_escolhido = tk.StringVar(value="Ponto")
algoritmo_escolhido = tk.StringVar(value="DDA")
cor_escolhida = tk.IntVar(value=ad.PRETO)
referencia = tk.StringVar(value="Centro")
tx = tk.DoubleVar(value=0)
ty = tk.DoubleVar(value=0)
angulo = tk.DoubleVar(value=0)
sx = tk.DoubleVar(value=1)
sy = tk.DoubleVar(value=1)
algoritmo_fill = tk.StringVar(value="Boundary")
conectividade = tk.IntVar(value=4)
evitar_vazamento = tk.BooleanVar(value=False)
cor_preenchimento = tk.IntVar(value=ad.VERMELHO)
cor_contorno = tk.IntVar(value=ad.PRETO)

cores = [("Preto", ad.PRETO), ("Vermelho", ad.VERMELHO), ("Azul", ad.AZUL),
         ("Verde", ad.VERDE), ("Amarelo", ad.AMARELO)]

# Aba Desenho
titulo(aba_desenho, "Desenhar:")
grade_de_opcoes(aba_desenho, modo_escolhido,
                [("Ponto", "Ponto"), ("Reta", "Reta"), ("Polígono", "Polígono"),
                 ("Circunferência", "Circunferência"), ("Selecionar", "Selecionar")], 2, trocar_modo)
titulo(aba_desenho, "Algoritmo da reta:")
grade_de_opcoes(aba_desenho, algoritmo_escolhido, [("DDA", "DDA"), ("Bresenham", "Bresenham")], 2, trocar_algoritmo)
titulo(aba_desenho, "Cor:")
grade_de_opcoes(aba_desenho, cor_escolhida, cores, 3)
tk.Button(aba_desenho, text="Limpar Área de Desenho", width=24, command=limpar_area).pack(anchor="w", pady=(10, 0))

# Aba Transformar
tk.Button(aba_transformar, text="Selecionar objetos", width=24, command=lambda: mudar_modo("Selecionar")).pack(anchor="w")
titulo(aba_transformar, "Referência (rotação e escala):")
grade_de_opcoes(aba_transformar, referencia, [("Origem", "Origem"), ("Centro", "Centro"), ("Ponto fixo", "Ponto fixo")], 3)
tk.Button(aba_transformar, text="Marcar ponto fixo", width=24, command=lambda: mudar_modo("Ponto fixo")).pack(anchor="w")
quadro_translacao = tk.Frame(aba_transformar)
quadro_translacao.pack(anchor="w")
controle_deslizante(quadro_translacao, "tx", tx, -100, 100, 1, 115)
controle_deslizante(quadro_translacao, "ty", ty, -100, 100, 1, 115)
tk.Button(aba_transformar, text="Transladar", width=24, command=transladar).pack(anchor="w")
quadro_rotacao = tk.Frame(aba_transformar)
quadro_rotacao.pack(anchor="w")
controle_deslizante(quadro_rotacao, "Ângulo (graus)", angulo, -180, 180, 1)
tk.Button(aba_transformar, text="Rotacionar", width=24, command=rotacionar).pack(anchor="w")
quadro_escala = tk.Frame(aba_transformar)
quadro_escala.pack(anchor="w")
controle_deslizante(quadro_escala, "sx", sx, 0.1, 3, 0.1, 115)
controle_deslizante(quadro_escala, "sy", sy, 0.1, 3, 0.1, 115)
tk.Button(aba_transformar, text="Escalar", width=24, command=escalar).pack(anchor="w")
titulo(aba_transformar, "Reflexão:")
quadro_reflexao = tk.Frame(aba_transformar)
quadro_reflexao.pack(anchor="w")
tk.Button(quadro_reflexao, text="Em X", width=7, command=refletir_x).pack(side="left")
tk.Button(quadro_reflexao, text="Em Y", width=7, command=refletir_y).pack(side="left")
tk.Button(quadro_reflexao, text="Em XY", width=7, command=refletir_xy).pack(side="left")

# Aba Recorte
tk.Button(aba_recorte, text="Marcar janela de recorte", width=24, command=lambda: mudar_modo("Janela de recorte")).pack(anchor="w")
titulo(aba_recorte, "Recortar com:")
tk.Button(aba_recorte, text="Cohen-Sutherland", width=24, command=lambda: aplicar_recorte("Cohen-Sutherland")).pack(anchor="w")
tk.Button(aba_recorte, text="Liang-Barsky", width=24, command=lambda: aplicar_recorte("Liang-Barsky")).pack(anchor="w")
tk.Button(aba_recorte, text="Sem recorte", width=24, command=remover_recorte).pack(anchor="w", pady=(6, 0))

# Aba Preencher
titulo(aba_preencher, "Algoritmo:")
grade_de_opcoes(aba_preencher, algoritmo_fill, [("Boundary Fill", "Boundary"), ("Flood Fill", "Flood")], 2)
titulo(aba_preencher, "Conectividade:")
grade_de_opcoes(aba_preencher, conectividade, [("4 vizinhos", 4), ("8 vizinhos", 8)], 2)
tk.Checkbutton(aba_preencher, text="Evitar vazamento", variable=evitar_vazamento).pack(anchor="w")
titulo(aba_preencher, "Cor de preenchimento:")
grade_de_opcoes(aba_preencher, cor_preenchimento, cores, 3)
titulo(aba_preencher, "Cor do contorno (Boundary):")
grade_de_opcoes(aba_preencher, cor_contorno, cores, 3)
tk.Button(aba_preencher, text="Clicar para preencher", width=24, command=lambda: mudar_modo("Preencher")).pack(anchor="w", pady=(10, 0))

# Triangulo da lista de exercicios, ja desenhado ao abrir
est.cena.append(est.Poligono([est.Ponto(-1, -3), est.Ponto(-2, 8), est.Ponto(9, 2)], ad.AZUL))
est.redesenhar()

ad.iniciar(canvas)

janela.mainloop()