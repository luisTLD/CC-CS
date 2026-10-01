from area_desenho import set_pixel, colora_pixel, round
# Algoritmo usado por desenha_linha: DDA ou Bresenham
algoritmo_reta = "DDA"

# DDA (slide 04)
def DDA(x1, y1, x2, y2):
    dx = x2 - x1
    dy = y2 - y1
    # O maior delta define o numero de passos: um pixel por coluna ou por linha
    if abs(dx) > abs(dy):
        passos = abs(dx)
    else:
        passos = abs(dy)
    x_incr = dx / passos
    y_incr = dy / passos
    x = x1
    y = y1
    # x e y continuam reais, so arredonda na hora de acender o pixel
    set_pixel(round(x), round(y))
    for k in range(1, passos + 1):
        x = x + x_incr
        y = y + y_incr
        set_pixel(round(x), round(y))

# Bresenham generico para retas (slide 05)
def bres_gen(x1, y1, x2, y2):
    dx = x2 - x1
    dy = y2 - y1
    # Deixa dx e dy positivos e guarda o sentido em incrx e incry
    if dx >= 0:
        incrx = 1
    else:
        incrx = -1
        dx = -dx
    if dy >= 0:
        incry = 1
    else:
        incry = -1
        dy = -dy
    x = x1
    y = y1
    colora_pixel(x, y)
    # 1o caso: inclinacao menor que 1, anda um pixel por vez em x
    if dy < dx:
        p = 2 * dy - dx
        const1 = 2 * dy
        const2 = 2 * (dy - dx)
        for i in range(0, dx):
            x += incrx
            if p < 0:
                p += const1
            else:
                y += incry
                p += const2
            colora_pixel(x, y)
    else:
        # 2o caso: inclinacao maior ou igual a 1, anda um pixel por vez em y
        p = 2 * dx - dy
        const1 = 2 * dx
        const2 = 2 * (dx - dy)
        for i in range(0, dy):
            y += incry
            if p < 0:
                p += const1
            else:
                x += incrx
                p += const2
            colora_pixel(x, y)

# Bresenham para circunferencia (slide 06)
def circBresenham(xc, yc, r):
    # Acende os 8 pontos simetricos de (x, y) em volta do centro
    def plot_circle_points():
        set_pixel(xc + x, yc + y)
        set_pixel(xc - x, yc + y)
        set_pixel(xc + x, yc - y)
        set_pixel(xc - x, yc - y)
        set_pixel(xc + y, yc + x)
        set_pixel(xc - y, yc + x)
        set_pixel(xc + y, yc - x)
        set_pixel(xc - y, yc - x)

    x = 0
    y = r
    p = 3 - 2 * r
    plot_circle_points()
    # Calcula so o 2o octante (45 a 90 graus), o resto sai pela simetria
    while x < y:
        if p < 0:
            p = p + 4 * x + 6
        else:
            p = p + 4 * (x - y) + 10
            y = y - 1
        x = x + 1
        plot_circle_points()

# Desenha a reta com o algoritmo escolhido na interface
def desenha_linha(x1, y1, x2, y2):
    # Reta de um ponto so: evita a divisao por zero no DDA
    if x1 == x2 and y1 == y2:
        set_pixel(x1, y1)
    elif algoritmo_reta == "DDA":
        DDA(x1, y1, x2, y2)
    else:
        bres_gen(x1, y1, x2, y2)