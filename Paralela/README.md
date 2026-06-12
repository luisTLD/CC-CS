# COMPUTAÇÃO PARALELA

## Trabalho - Kmeans_paralelo
https://github.com/luisTLD/Kmeans-parallel

## FUNDAMENTOS

### Computação Paralela
- Execução simultânea
- Desempenho
- Throughput
- Escalabilidade

### Concorrência
- Interleaving
- Compartilhamento de recursos

### Paralelismo
- Execução simultânea real

### Paralelismo de Dados
- Particionamento de dados
- Mesmo fluxo de execução

### Paralelismo de Tarefas
- Tarefas independentes
- Fluxos distintos

---

## PADRÕES PARALELOS

### Fork-Join
- Decomposição
- Sincronização final

### Map
- Transformação paralela

### Reduce
- Agregação
- Operação associativa

### Scan
- Prefix Sum
- Dependência parcial

### Pipeline
- Paralelismo por estágios

### Divide & Conquer
- Decomposição recursiva

---

## THREADS E OPENMP

### Thread
- Unidade de execução

### OpenMP
- Memória compartilhada
- Diretivas
- Runtime

### Região Paralela
- Criação de equipe de threads

### Worksharing
- Distribuição de trabalho

### Tasking
- Paralelismo baseado em tarefas

### Critical
- Exclusão mútua

### Atomic
- Operação indivisível

### Barrier
- Sincronização coletiva

### Reduction
- Acumulação paralela

### Race Condition
- Acesso concorrente não sincronizado

### Deadlock
- Espera circular

### Load Balancing
- Distribuição uniforme

### Scheduling
- Static
- Dynamic
- Guided

---

## ARQUITETURAS

### SISD

### SIMD

### MISD

### MIMD

### CPU
- Baixa latência
- Controle complexo

### GPU
- Alto throughput
- Paralelismo massivo

### Multicore

### Manycore

### NUMA
- Localidade de memória

---

## MEMÓRIA

### Registradores

### Cache

### RAM

### Localidade Temporal

### Localidade Espacial

### Cache Miss

### False Sharing
- Compartilhamento de linha de cache

---

## DESEMPENHO

### Tempo de Execução

### Speedup

### Eficiência

### Escalabilidade

### Overhead

### Gargalo

### Lei de Amdahl
- Fração serial

### Lei de Gustafson
- Escalonamento do problema

---

## ALGORITMOS PARALELOS

### Decomposição

### Dependência de Dados

### Comunicação

### Sincronização

### Granularidade

### Escalonamento

---

## SIMD E VETORIZAÇÃO

### SIMD
- Data-level parallelism

### Vetorização
- Instruções vetoriais

### AVX

### AVX2

### AVX-512

### Auto-Vectorization

---

## CUDA E GPU

### CUDA

### Kernel

### Thread

### Block

### Grid

### Warp
- Unidade de escalonamento

### Occupancy

### Warp Divergence

### Coalesced Access

---

## MEMÓRIA EM GPU

### Registradores

### Shared Memory

### Local Memory

### Global Memory

### Constant Memory

### Texture Memory

### Hierarquia de Memória

---

## PADRÕES EM GPU

### Reduction

### Scan

### Tiling

### Stencil

### Paralelismo Massivo

---

## MPI

### MPI
- Memória distribuída

### Processo

### Rank

### Communicator

### Point-to-Point

### Send

### Receive

### Broadcast

### Scatter

### Gather

### Reduce

### AllReduce

### Barrier

### Comunicação Bloqueante

### Comunicação Não Bloqueante

### Cluster

### Latência

### Bandwidth
