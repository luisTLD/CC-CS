# Computação Paralela

# 1. FUNDAMENTOS

## Computação Paralela
Execução simultânea de múltiplas operações.

Objetivos:
- acelerar processamento
- dividir trabalho
- aumentar desempenho

## Paralelismo de Dados
Mesmo processamento aplicado em vários dados.

## Paralelismo de Tarefas
Tarefas diferentes executadas simultaneamente.

---

# 2. MODELOS E PADRÕES

## FORK-JOIN
Divide tarefas e sincroniza ao final.

## MAP
Aplica operação em múltiplos elementos.

## REDUCE
Combina múltiplos valores em um resultado.

Exemplos:
- soma
- máximo
- média

## SCAN
Soma prefixada acumulativa.

## PIPELINE
Execução em estágios sequenciais paralelos.

## DIVIDE & CONQUER
Divide problema em subproblemas menores.

---

# 3. THREADS E OPENMP

## OpenMP
API de paralelismo para CPU.

Baseado em:
- diretivas
- threads
- memória compartilhada

## Paralelismo com Threads
Execução simultânea de fluxos de execução.

## Região Paralela
Bloco executado por múltiplas threads.

## Seção Crítica
Região com acesso exclusivo.

## Sincronização
Controle de execução entre threads.

## Barreira
Sincroniza todas as threads.

## Race Condition
Conflito de acesso concorrente.

## Balanceamento de Carga
Distribuição equilibrada de trabalho.

## Paralelismo de Tarefas
Execução paralela de tarefas independentes.

---

# 4. ARQUITETURAS PARALELAS

## Arquiteturas Paralelas
Sistemas com múltiplas unidades de processamento.

## Multicore
Múltiplos núcleos em uma CPU.

## Manycore
Grande quantidade de núcleos paralelos.

## CPU
Processamento geral e controle.

## GPU
Processamento massivamente paralelo.

## Hierarquia de Memória
Organização da memória por níveis.

Tipos:
- registradores
- cache
- RAM
- memória global

---

# 5. DESEMPENHO

## Avaliação de Desempenho
Análise da eficiência paralela.

## Speedup
Comparação entre execução serial e paralela.

## Eficiência
Aproveitamento dos processadores.

## Escalabilidade
Capacidade de aumentar desempenho com mais recursos.

## Gargalo
Parte que limita desempenho.

## Overhead
Custo adicional do paralelismo.

---

# 6. ALGORITMOS PARALELOS

## Algoritmos Paralelos
Algoritmos executados simultaneamente.

Características:
- divisão de tarefas
- sincronização
- comunicação

## Dependência de Dados
Quando uma operação depende de outra.

## Granularidade
Quantidade de trabalho por tarefa.

---

# 7. SIMD E VETORIZAÇÃO

## SIMD
Single Instruction Multiple Data.

Mesma instrução aplicada em vários dados.

## Vetorização
Execução vetorial de operações.

Aplicações:
- matrizes
- imagens
- álgebra linear

## Processamento Vetorial
Uso de registradores vetoriais.

---

# 8. GPU E CUDA

## Programação em GPU
Execução paralela massiva na GPU.

## CUDA
Plataforma de programação da NVIDIA.

## OpenMP para GPU
Uso de diretivas OpenMP em GPU.

## Arquitetura de GPU
Baseada em milhares de threads paralelas.

## Modelo de Execução CUDA
Organização em:
- grids
- blocos
- threads

## Thread
Menor unidade de execução.

## Bloco
Conjunto de threads.

## Warp
Grupo de threads executadas juntas.

---

# 9. MEMÓRIA EM GPU

## Memória Global
Grande capacidade e maior latência.

## Memória Compartilhada
Memória rápida compartilhada entre threads do bloco.

## Memória Local
Privada para cada thread.

## Registradores
Memória mais rápida da GPU.

## Hierarquia de Memória em GPU
Organização dos tipos de memória da GPU.

---

# 10. PADRÕES EM GPU

## REDUCE em GPU
Redução paralela de valores.

## SCAN em GPU
Soma prefixada paralela.

## Paralelismo Massivo
Grande quantidade de threads simultâneas.

---

# 11. MPI

## MPI
Message Passing Interface.

Modelo baseado em múltiplos processos.

## Comunicação entre Processos
Troca de dados entre processos distribuídos.

## Send / Receive
Envio e recebimento de mensagens.

## Broadcast
Um processo envia dados para todos.

## Scatter
Distribui partes dos dados.

## Gather
Reúne dados dos processos.

## Pipeline em MPI
Execução distribuída em estágios.

## Cluster
Conjunto de máquinas conectadas.

## Memória Distribuída
Cada processo possui memória própria.
