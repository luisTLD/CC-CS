import math
import estruturas as est


# Matrizes 3x3 em coordenadas homogeneas, usadas como P linha = M vezes P (slide 02)
def translacao(tx, ty):
    return [[1, 0, tx],
            [0, 1, ty],
            [0, 0, 1]]


def escala(sx, sy):
    return [[sx, 0, 0],
            [0, sy, 0],
            [0, 0, 1]]


# Rotacao em volta da origem, com o angulo em graus
def rotacao(angulo_graus):
    teta = math.radians(angulo_graus)
    return [[math.cos(teta), -math.sin(teta), 0],
            [math.sin(teta), math.cos(teta), 0],
            [0, 0, 1]]


# Reflexao em relacao ao eixo x: y vira -y
def reflexao_x():
    return [[1, 0, 0],
            [0, -1, 0],
            [0, 0, 1]]


# Reflexao em relacao ao eixo y: x vira -x
def reflexao_y():
    return [[-1, 0, 0],
            [0, 1, 0],
            [0, 0, 1]]


# Reflexao em relacao a origem: x e y trocam de sinal
def reflexao_xy():
    return [[-1, 0, 0],
            [0, -1, 0],
            [0, 0, 1]]


# Multiplica duas matrizes 3x3 (composicao de transformacoes)
def multiplicar(A, B):
    C = [[0, 0, 0], [0, 0, 0], [0, 0, 0]]
    for i in range(3):
        for j in range(3):
            for k in range(3):
                C[i][j] = C[i][j] + A[i][k] * B[k][j]
    return C


# Aplica a matriz no ponto (x, y, 1) usado como vetor coluna
def aplicar(M, x, y):
    x_novo = M[0][0] * x + M[0][1] * y + M[0][2] * 1
    y_novo = M[1][0] * x + M[1][1] * y + M[1][2] * 1
    return x_novo, y_novo


# Transforma em volta da referencia: leva para a origem, transforma e volta
def em_relacao_a(M, xref, yref):
    # T(xref, yref) vezes M vezes T(-xref, -yref), montada da ultima para a primeira
    return multiplicar(translacao(xref, yref), multiplicar(M, translacao(-xref, -yref)))


# Aplica a matriz em todos os pontos do objeto
def transformar_objeto(obj, M, fator_raio=1):
    if isinstance(obj, est.Ponto) or isinstance(obj, est.Preenchimento):
        obj.x, obj.y = aplicar(M, obj.x, obj.y)
    elif isinstance(obj, est.Reta):
        obj.x1, obj.y1 = aplicar(M, obj.x1, obj.y1)
        obj.x2, obj.y2 = aplicar(M, obj.x2, obj.y2)
    elif isinstance(obj, est.Poligono):
        for v in obj.vertices:
            v.x, v.y = aplicar(M, v.x, v.y)
    elif isinstance(obj, est.Circunferencia):
        obj.xc, obj.yc = aplicar(M, obj.xc, obj.yc)
        # O raio nao passa pela matriz, entao ele e ajustado pelo fator da escala
        obj.r = obj.r * fator_raio