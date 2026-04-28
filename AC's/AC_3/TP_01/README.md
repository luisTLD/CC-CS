# Trabalho - Hierarquia de Memória (Simulação com Amnesia)

## Objetivo
Estudar a hierarquia de memória e demonstrar, por meio de simulações, os impactos da exploração da localidade temporal e espacial no desempenho do sistema de memória.

## Ferramenta de Simulação
- Simulador Amnesia
- Uso de traces de execução para análise de acessos à memória
- Configuração de arquiteturas via arquivos XML

## Conceitos Estudados
- Hierarquia de memória
- Cache (organização, tamanho, associatividade, políticas de substituição e coerência)
- Memória virtual
- Localidade temporal e espacial
- Impacto de parâmetros de memória no desempenho
- Relação entre padrão de acesso e taxa de hit/miss

## Metodologia de Simulação
- Definição de cenários de teste:
  - 3 cenários de cache
  - 3 cenários de memória virtual
- Variação controlada de parâmetros:
  - Tamanho de linha/bloco
  - Tamanho da cache
  - Associatividade
  - Políticas de substituição
  - Políticas de coerência
- Alteração de apenas um parâmetro por vez para análise isolada de impacto

## Dados de Entrada (Traces)
- Uso de traces de execução como base de simulação
- Importância do padrão de acesso à memória
- Traces devem conter localidade temporal e espacial
- Evitar traces irreais (ex: 99% miss sem localidade)
- Tamanho médio de trace recomendado para melhor análise
- Foco nos endereços de memória (não nas instruções)

## Análise de Resultados
- Geração de gráficos para comparação de cenários
- Avaliação de impacto de cada parâmetro no desempenho
- Interpretação de taxas de hit e miss
- Relação entre arquitetura e comportamento do programa
