import sys
from area_desenho import inquirir_cor, set_pixel, FORA_DA_AREA

# Os preenchimentos sao recursivos como no slide, o limite padrao do Python e pequeno
sys.setrecursionlimit(100000)


# Boundary Fill com 4 vizinhos (slide 08)
def boundary4(x, y, cor_preenche, cor_contorno):
    cor_atual = inquirir_cor(x, y)
    # Fora da matriz: nao ha o que pintar
    if cor_atual == FORA_DA_AREA:
        return
    if (cor_atual != cor_contorno) and (cor_atual != cor_preenche):
        set_pixel(x, y, cor_preenche)
        boundary4(x + 1, y, cor_preenche, cor_contorno)
        boundary4(x - 1, y, cor_preenche, cor_contorno)
        boundary4(x, y + 1, cor_preenche, cor_contorno)
        boundary4(x, y - 1, cor_preenche, cor_contorno)


# Boundary Fill com 8 vizinhos: tambem anda nas diagonais
def boundary8(x, y, cor_preenche, cor_contorno):
    cor_atual = inquirir_cor(x, y)
    if cor_atual == FORA_DA_AREA:
        return
    if (cor_atual != cor_contorno) and (cor_atual != cor_preenche):
        set_pixel(x, y, cor_preenche)
        boundary8(x + 1, y, cor_preenche, cor_contorno)
        boundary8(x - 1, y, cor_preenche, cor_contorno)
        boundary8(x, y + 1, cor_preenche, cor_contorno)
        boundary8(x, y - 1, cor_preenche, cor_contorno)
        # Diagonais: podem passar pela quina entre dois pixels do contorno
        boundary8(x + 1, y + 1, cor_preenche, cor_contorno)
        boundary8(x - 1, y + 1, cor_preenche, cor_contorno)
        boundary8(x + 1, y - 1, cor_preenche, cor_contorno)
        boundary8(x - 1, y - 1, cor_preenche, cor_contorno)


# Flood Fill com 4 vizinhos (slide 08): recolore enquanto a cor for cor_antiga
def flood4(x, y, cor_preenche, cor_antiga):
    if inquirir_cor(x, y) == cor_antiga:
        set_pixel(x, y, cor_preenche)
        flood4(x + 1, y, cor_preenche, cor_antiga)
        flood4(x - 1, y, cor_preenche, cor_antiga)
        flood4(x, y + 1, cor_preenche, cor_antiga)
        flood4(x, y - 1, cor_preenche, cor_antiga)


# Flood Fill com 8 vizinhos
def flood8(x, y, cor_preenche, cor_antiga):
    if inquirir_cor(x, y) == cor_antiga:
        set_pixel(x, y, cor_preenche)
        flood8(x + 1, y, cor_preenche, cor_antiga)
        flood8(x - 1, y, cor_preenche, cor_antiga)
        flood8(x, y + 1, cor_preenche, cor_antiga)
        flood8(x, y - 1, cor_preenche, cor_antiga)
        flood8(x + 1, y + 1, cor_preenche, cor_antiga)
        flood8(x - 1, y + 1, cor_preenche, cor_antiga)
        flood8(x + 1, y - 1, cor_preenche, cor_antiga)
        flood8(x - 1, y - 1, cor_preenche, cor_antiga)


# Boundary Fill com 8 vizinhos que nao atravessa as quinas do contorno
def boundary8_sem_vazamento(x, y, cor_preenche, cor_contorno):
    cor_atual = inquirir_cor(x, y)
    if cor_atual == FORA_DA_AREA:
        return
    if (cor_atual != cor_contorno) and (cor_atual != cor_preenche):
        set_pixel(x, y, cor_preenche)
        boundary8_sem_vazamento(x + 1, y, cor_preenche, cor_contorno)
        boundary8_sem_vazamento(x - 1, y, cor_preenche, cor_contorno)
        boundary8_sem_vazamento(x, y + 1, cor_preenche, cor_contorno)
        boundary8_sem_vazamento(x, y - 1, cor_preenche, cor_contorno)
        # So vai na diagonal se os dois vizinhos do lado nao forem ambos contorno
        if not (inquirir_cor(x + 1, y) == cor_contorno and inquirir_cor(x, y + 1) == cor_contorno):
            boundary8_sem_vazamento(x + 1, y + 1, cor_preenche, cor_contorno)
        if not (inquirir_cor(x - 1, y) == cor_contorno and inquirir_cor(x, y + 1) == cor_contorno):
            boundary8_sem_vazamento(x - 1, y + 1, cor_preenche, cor_contorno)
        if not (inquirir_cor(x + 1, y) == cor_contorno and inquirir_cor(x, y - 1) == cor_contorno):
            boundary8_sem_vazamento(x + 1, y - 1, cor_preenche, cor_contorno)
        if not (inquirir_cor(x - 1, y) == cor_contorno and inquirir_cor(x, y - 1) == cor_contorno):
            boundary8_sem_vazamento(x - 1, y - 1, cor_preenche, cor_contorno)


# No Flood, barreira e tudo que nao e cor_antiga nem cor_preenche
def barreira_flood(x, y, cor_preenche, cor_antiga):
    cor = inquirir_cor(x, y)
    return cor != cor_antiga and cor != cor_preenche


# Flood Fill com 8 vizinhos que nao atravessa as quinas
def flood8_sem_vazamento(x, y, cor_preenche, cor_antiga):
    if inquirir_cor(x, y) == cor_antiga:
        set_pixel(x, y, cor_preenche)
        flood8_sem_vazamento(x + 1, y, cor_preenche, cor_antiga)
        flood8_sem_vazamento(x - 1, y, cor_preenche, cor_antiga)
        flood8_sem_vazamento(x, y + 1, cor_preenche, cor_antiga)
        flood8_sem_vazamento(x, y - 1, cor_preenche, cor_antiga)
        # So vai na diagonal se os dois vizinhos do lado nao forem ambos barreira
        if not (barreira_flood(x + 1, y, cor_preenche, cor_antiga) and barreira_flood(x, y + 1, cor_preenche, cor_antiga)):
            flood8_sem_vazamento(x + 1, y + 1, cor_preenche, cor_antiga)
        if not (barreira_flood(x - 1, y, cor_preenche, cor_antiga) and barreira_flood(x, y + 1, cor_preenche, cor_antiga)):
            flood8_sem_vazamento(x - 1, y + 1, cor_preenche, cor_antiga)
        if not (barreira_flood(x + 1, y, cor_preenche, cor_antiga) and barreira_flood(x, y - 1, cor_preenche, cor_antiga)):
            flood8_sem_vazamento(x + 1, y - 1, cor_preenche, cor_antiga)
        if not (barreira_flood(x - 1, y, cor_preenche, cor_antiga) and barreira_flood(x, y - 1, cor_preenche, cor_antiga)):
            flood8_sem_vazamento(x - 1, y - 1, cor_preenche, cor_antiga)