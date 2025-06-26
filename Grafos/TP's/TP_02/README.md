# Segmentação de Imagens com Grafos

Este repositório contém a implementação de dois algoritmos de segmentação de imagens baseados em grafos:

- **Árvore Geradora Mínima (MST)**  
  Referência: Pedro F. Felzenszwalb e Daniel P. Huttenlocher, *"Efficient graph-based image segmentation"*.

- **Caminho Mínimo (IFT)**  
  Referência: Alexandre X. Falcão, Jorge Stolfi e Roberto de Alencar Lotufo, *"The image foresting transform"*.

## Descrição

Cada pixel é representado como um vértice, e as relações de vizinhança formam as arestas. A segmentação é realizada por particionamento do grafo, considerando critérios de similaridade local.

## Formatos de Imagem

Os algoritmos **leem imagens nos formatos `.ppm` (coloridas), seguindo o padrão PNM.

## Algoritmos

| Método | Estratégia | Entrada | Características |
|--------|------------|---------|-----------------|
| MST (Felzenszwalb) | Agrupamento bottom-up | Apenas imagem | Rápido, automático |
| IFT (Falcão)        | Caminho mínimo | Imagem + sementes | Flexível, supervisionado ou automático |

