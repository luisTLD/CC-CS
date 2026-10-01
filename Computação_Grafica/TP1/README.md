# TP1 - Computação Gráfica

Implementação dos algoritmos da Unidade 1 com saída em uma matriz de pixels. Enunciado em `enunciado.pdf`.

## Algoritmos

- Transformações 2D: translação, rotação, escala e reflexões X, Y e XY
- Rasterização: DDA e Bresenham (retas), Bresenham (circunferência)
- Recorte: Cohen-Sutherland e Liang-Barsky
- Preenchimento: Boundary Fill e Flood Fill, com 4 ou 8 vizinhos

## Arquivos

| Arquivo | Conteúdo |
|---|---|
| `main.py` | Interface e eventos do mouse |
| `area_desenho.py` | Matriz de pixels |
| `rasterizacao.py` | DDA, Bresenham e circunferência |
| `transformacoes.py` | Matrizes de transformação |
| `recorte.py` | Cohen-Sutherland e Liang-Barsky |
| `preenchimento.py` | Boundary Fill e Flood Fill |
| `estruturas.py` | Objetos da cena, seleção e redesenho |
| `build.bat` | Gera o executável |
| `instalador.iss` | Gera o instalador |

## Executar

```
python main.py
```

## Executável e instalador

```
pip install pyinstaller
build.bat
```

Gera `dist\TP1_CG\TP1_CG.exe`. Depois, compilar `instalador.iss` no Inno Setup para gerar `Output\Setup_TP1_CG.exe`.
