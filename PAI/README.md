# Processamento e Análise de Imagens (PAI)

==================================================
1. FUNDAMENTOS
==================================================

## Processamento de Imagens
Manipulação de imagens para:
- melhorar qualidade
- remover ruído
- destacar informações
- preparar para análise

Aplicações:
- pré-processamento
- segmentação
- reconhecimento
- inspeção

--------------------------------------------------

## Visão Computacional
Área que busca interpretar imagens e vídeos automaticamente.

Aplicações:
- reconhecimento facial
- detecção de objetos
- OCR
- veículos autônomos
- inspeção industrial

--------------------------------------------------

## Análise de Imagens
Extração de informações úteis da imagem.

Exemplos:
- medidas
- padrões
- regiões
- classificação

--------------------------------------------------

## Reconhecimento de Padrões
Classificação automática baseada em características extraídas.

Pipeline comum:
Imagem → Pré-processamento → Segmentação →
Extração de características → Classificação

==================================================
2. AQUISIÇÃO E REPRESENTAÇÃO
==================================================

## Aquisição de Imagens
Captura da imagem por:
- câmera
- scanner
- satélite
- microscópio
- raio-x

--------------------------------------------------

## Amostragem
Define resolução espacial.

Mais pixels:
- mais detalhe
- maior custo computacional

--------------------------------------------------

## Quantização
Define quantidade de níveis de intensidade.

Mais níveis:
- maior precisão
- maior armazenamento

--------------------------------------------------

## Representação de Imagens
Imagem representada como matriz de pixels.

Cada pixel possui:
- posição
- intensidade
- cor

--------------------------------------------------

## Fundamentos de Cor

### RGB
Representação baseada em:
- vermelho
- verde
- azul

Usado em:
- exibição
- captura

### HSV
Representação baseada em:
- matiz
- saturação
- brilho

Vantagem:
- facilita segmentação por cor

==================================================
3. HISTOGRAMAS E REALCE
==================================================

## Histograma
Distribuição das intensidades da imagem.

Usado para analisar:
- contraste
- brilho
- concentração de tons

--------------------------------------------------

## Equalização de Histograma
Redistribui intensidades para melhorar contraste.

Vantagem:
- melhora imagens com baixo contraste

Desvantagem:
- pode amplificar ruído

--------------------------------------------------

## CLAHE
Equalização adaptativa local.

Vantagem:
- reduz amplificação excessiva de ruído
- melhora contraste local

Aplicações:
- imagens médicas
- visão noturna
- iluminação irregular

==================================================
4. CONVOLUÇÃO E FILTRAGEM
==================================================

## Convolução
Operação usada para aplicar filtros na imagem.

Utiliza:
- máscaras
- kernels

--------------------------------------------------

## Filtragem
Usada para:
- suavização
- remoção de ruído
- detecção de bordas
- realce

--------------------------------------------------

## Suavização

### Filtro da Média
Reduz ruído através da média dos pixels vizinhos.

Desvantagem:
- perde detalhes

### Filtro Gaussiano
Suavização baseada em distribuição gaussiana.

Vantagem:
- preserva melhor a estrutura da imagem

--------------------------------------------------

## Uso Combinado de Filtros
Aplicação sequencial de múltiplos filtros.

Exemplo:
- suavização antes da detecção de bordas

==================================================
5. BORDAS E DERIVADAS
==================================================

## Bordas
Mudanças bruscas de intensidade.

Representam:
- contornos
- limites
- objetos

--------------------------------------------------

## Primeira Derivada
Detecta variações rápidas de intensidade.

Base para:
- gradiente
- operadores de borda

--------------------------------------------------

## Gradiente
Indica intensidade e direção da mudança.

Usado em:
- detecção de bordas
- segmentação

--------------------------------------------------

## Operadores de Primeira Ordem

### Sobel
Calcula gradientes horizontal e vertical.

Vantagem:
- reduz parcialmente ruído

--------------------------------------------------

## Segunda Derivada
Detecta mudanças no gradiente.

Desvantagem:
- alta sensibilidade a ruído

--------------------------------------------------

## Laplaciano
Baseado na segunda derivada.

Usado para:
- destacar regiões de mudança rápida

--------------------------------------------------

## Detector de Bordas Canny
Detector de bordas baseado em múltiplas etapas.

Etapas:
- suavização
- gradiente
- supressão
- histerese

Vantagens:
- alta precisão
- menos falsas bordas

==================================================
6. SEGMENTAÇÃO
==================================================

## Segmentação
Separação da imagem em regiões relevantes.

Objetivo:
- separar objetos
- identificar regiões

--------------------------------------------------

## Limiarização
Segmentação baseada em intensidade.

Vantagem:
- simples e rápida

Desvantagem:
- ruim para iluminação irregular

--------------------------------------------------

## Segmentação por Região
Agrupa pixels semelhantes.

Critérios:
- cor
- intensidade
- textura

--------------------------------------------------

## Segmentação por Contorno
Segmentação baseada em bordas.

Usada quando:
- contornos são bem definidos

--------------------------------------------------

## Transformada de Hough
Detecta formas geométricas.

Aplicações:
- linhas
- círculos
- pistas
- estruturas geométricas

==================================================
7. MORFOLOGIA MATEMÁTICA
==================================================

## Morfologia Matemática
Opera sobre formas e estruturas da imagem.

Usada principalmente em:
- imagens binárias
- pós-processamento

--------------------------------------------------

## Erosão
Remove pixels das bordas.

Usada para:
- eliminar pequenos ruídos

--------------------------------------------------

## Dilatação
Expande regiões da imagem.

Usada para:
- preencher falhas
- conectar regiões

--------------------------------------------------

## Abertura
Erosão seguida de dilatação.

Usada para:
- remover pequenos objetos

--------------------------------------------------

## Fechamento
Dilatação seguida de erosão.

Usada para:
- fechar buracos
- unir regiões próximas

==================================================
8. DOMÍNIO ESPACIAL E FREQUÊNCIA
==================================================

## Domínio Espacial
Operações realizadas diretamente nos pixels.

--------------------------------------------------

## Domínio da Frequência
Análise das frequências da imagem.

Baixa frequência:
- regiões suaves

Alta frequência:
- bordas
- detalhes

==================================================
9. FOURIER E TRANSFORMADAS
==================================================

## Série de Fourier
Representa sinais periódicos através de componentes senoidais.

--------------------------------------------------

## Transformada de Fourier
Converte imagem do domínio espacial para frequência.

Aplicações:
- filtragem
- compressão
- análise espectral

--------------------------------------------------

## DFT
Versão discreta da Transformada de Fourier.

Usada em processamento digital.

--------------------------------------------------

## FFT
Algoritmo rápido para calcular DFT.

Vantagem:
- reduz custo computacional

==================================================
10. FILTRAGEM NO DOMÍNIO DA FREQUÊNCIA
==================================================

## Filtro Passa-Baixa
Mantém baixas frequências.

Resultado:
- suavização
- redução de ruído

--------------------------------------------------

## Filtro Passa-Alta
Mantém altas frequências.

Resultado:
- realce
- destaque de bordas

--------------------------------------------------

## Filtro Ideal
Realiza corte brusco de frequências.

Desvantagem:
- pode gerar ringing

--------------------------------------------------

## Janelamento
Suaviza transições na frequência.

Usado para:
- reduzir artefatos

==================================================
11. REPRESENTAÇÃO DE PADRÕES
==================================================

## Descritores
Transformam imagem em vetor de características.

--------------------------------------------------

## Descritores de Cor
Representam distribuição de cores.

--------------------------------------------------

## Descritores de Forma
Representam geometria do objeto.

Exemplos:
- área
- perímetro
- circularidade

--------------------------------------------------

## Descritores de Textura
Representam padrões visuais.

Exemplos:
- rugosidade
- repetição
- direção

==================================================
12. CLASSIFICAÇÃO
==================================================

## Classificação
Determina a classe de um padrão.

Aplicações:
- reconhecimento
- inspeção
- diagnóstico

--------------------------------------------------

## Classificadores Determinísticos
Baseados em regras fixas.

--------------------------------------------------

## Classificadores Probabilísticos
Baseados em probabilidade.

==================================================
13. APRENDIZADO DE MÁQUINA
==================================================

## Perceptron
Modelo simples de neurônio artificial.

Vantagem:
- simples e rápido

Desvantagem:
- resolve apenas problemas lineares

--------------------------------------------------

## Backpropagation
Algoritmo de treinamento de redes neurais.

Usado para:
- ajuste de pesos
- redução de erro

--------------------------------------------------

## MLP
Rede neural com múltiplas camadas.

Vantagem:
- aprende relações não lineares

Desvantagem:
- maior custo computacional

--------------------------------------------------

## SVM
Classificador baseado em hiperplano ótimo.

Vantagens:
- funciona bem com poucos dados
- eficiente em alta dimensão

Desvantagem:
- custo elevado em grandes bases

--------------------------------------------------

## CNN
Rede neural convolucional especializada em imagens.

Aprende automaticamente:
- bordas
- texturas
- formas
- objetos

Vantagem:
- alto desempenho em visão computacional

Desvantagem:
- necessita grande volume de dados

==================================================
14. APLICAÇÕES
==================================================

## OCR
Reconhecimento automático de caracteres.

--------------------------------------------------

## Imagens Médicas
Aplicações:
- tomografia
- ressonância
- raio-x

--------------------------------------------------

## Recuperação de Imagens
Busca imagens similares por conteúdo visual.

--------------------------------------------------

## Segurança
Aplicações:
- biometria
- vigilância
- reconhecimento facial

--------------------------------------------------

## Controle de Qualidade
Inspeção automática industrial.

Detecta:
- defeitos
- falhas
- peças fora do padrão

==================================================
15. QUANDO USAR CADA TÉCNICA
==================================================

Ruído:
- Média
- Gaussiano

Baixo contraste:
- Equalização
- CLAHE

Detectar bordas:
- Sobel
- Laplaciano
- Canny

Detectar linhas e círculos:
- Hough

Separar objeto do fundo:
- Limiarização

Remover pequenos ruídos:
- Morfologia

Realçar detalhes:
- Passa-alta

Suavizar imagem:
- Passa-baixa

Extrair padrões:
- Descritores

Classificar imagens:
- SVM
- MLP
- CNN

Poucos dados:
- SVM

Grandes bases visuais:
- CNN

Problemas simples:
- Perceptron
