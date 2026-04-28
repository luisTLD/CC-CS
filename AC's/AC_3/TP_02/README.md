# Trabalho - Simulador do Algoritmo de Tomasulo

## Objetivo
Desenvolver um simulador didático do algoritmo de Tomasulo para execução de instruções MIPS, com foco em arquitetura superescalar, especulação e reordenação de instruções.

## Escopo do Simulador
O simulador deve representar o funcionamento completo do pipeline superescalar baseado no algoritmo de Tomasulo, permitindo visualizar e compreender o fluxo dinâmico de instruções.

## Funcionalidades Principais

### Execução de Instruções
- Suporte a instruções no formato MIPS
- Simulação do fluxo de instruções em ambiente superescalar
- Execução com base no algoritmo de Tomasulo

### Etapas do Pipeline
- Despacho de instruções
- Execução
- Commit (finalização ordenada)
- Visualização do estado das instruções em cada etapa

### Execução Passo a Passo
- Controle de execução ciclo a ciclo
- Permite observar mudanças internas do pipeline
- Foco educacional para entendimento do comportamento da arquitetura

### Especulação e Controle de Desvios
- Suporte a especulação de instruções de desvio condicional
- Execução especulativa com validação posterior
- Tratamento de correção em caso de predição incorreta

### Buffer de Reordenação (ROB)
- Implementação de buffer de reordenação
- Garantia de commit em ordem correta
- Suporte à execução fora de ordem com finalização ordenada

## Métricas de Desempenho
O simulador deve calcular e exibir:

- IPC (Instructions Per Cycle)
- Número total de ciclos de execução
- Ciclos de bolha (stalls)
- Eficiência do pipeline
- Impacto de dependências de dados e controle

## Interface Gráfica
O simulador deve possuir interface gráfica interativa para apoio didático, incluindo:

- Visualização do pipeline em tempo real
- Estado das instruções (despacho, execução, commit)
- Visualização do ROB e unidades funcionais
- Controle de execução (run / pause / step-by-step)
- Exibição de métricas de desempenho atualizadas

## Objetivo Educacional
- Compreender o funcionamento do algoritmo de Tomasulo
- Visualizar execução fora de ordem (out-of-order execution)
- Entender especulação e controle de dependências
- Analisar impacto de hazards no desempenho
- Relacionar arquitetura superescalar com ganhos de performance
