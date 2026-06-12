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
### Computação Heterogênea
- CPU + acelerador (GPU)
- Offload de computação
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
### Privatização
- Cópias locais por thread
- Merge ao final
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
- parallel for
### Cláusulas de Escopo
- shared
- private
- firstprivate
- default
### Tasking
- Paralelismo baseado em tarefas
### Critical
- Exclusão mútua
### Atomic
- Operação indivisível
### Barrier
- Sincronização coletiva
### Nowait
- Remove barreira implícita
### Single / Master
- Execução por uma thread
### Reduction
- Acumulação paralela
- Reduction de arrays (manual: privatização + critical)
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
### Collapse
- Junção de laços aninhados
### Controle de Threads
- OMP_NUM_THREADS
- num_threads()
- omp_get_max_threads()
### Medição de Tempo
- omp_get_wtime()
- Relógio de parede (wall clock)
---
## OPENMP PARA GPU (TARGET OFFLOAD)
### Target
- Execução no device
### Target Data
- Região de dados persistente na GPU
- Evita transferências repetidas
### Map
- to / from / tofrom / alloc
### Target Update
- Sincronização parcial host <-> device
### Teams
- Ligas de threads (≈ blocos)
### Distribute
- Distribuição entre teams
### Teams Distribute Parallel For
- Construção combinada para GPU
### SIMD em GPU
- gcc/nvptx: parallel → warps, simd → lanes
- Sem simd: 1 de 32 lanes por warp
### Host Fallback
- Sem device disponível: executa na CPU
### Compiladores com Offload
- gcc (-foffload=nvptx-none)
- nvc (-mp=gpu)
- clang (-fopenmp-targets)
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
### FP32 vs FP64
- GPUs domésticas: FP64 fraco (1/32)
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
### Layout de Dados
- AoS (array of structs)
- SoA (struct of arrays)
- SoA favorece coalescência/vetorização
---
## DESEMPENHO
### Tempo de Execução
- Medição: wall clock (omp_get_wtime, clock_gettime)
### Speedup
- T_seq / T_par
### Eficiência
- Speedup / nº de processadores
### Escalabilidade
- Strong scaling (problema fixo)
- Weak scaling (problema cresce com recursos)
### Saturação
- Limite: nº de núcleos físicos
### Overhead
- Criação de threads, sincronização, transferências
### Gargalo
### Lei de Amdahl
- Fração serial
### Lei de Gustafson
- Escalonamento do problema
### Profiling
- nvprof, gprof, perf
---
## ALGORITMOS PARALELOS
### Decomposição
### Dependência de Dados
### Comunicação
### Sincronização
### Granularidade
### Escalonamento
### Corretude
- Reprodutibilidade (seed fixa)
- Comparação com versão sequencial
### Convergência Iterativa
- Laço externo serial
- Iteração interna paralela
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
### nvcc
### Kernel
- __global__
### Lançamento
- kernel<<<grid, block, shmem>>>()
### Thread
### Block
### Grid
### Warp
- Unidade de escalonamento
- 32 threads
### Occupancy
### Warp Divergence
### Coalesced Access
### Sincronização
- __syncthreads() (intra-bloco)
- cudaDeviceSynchronize() (host)
### Atomics
- atomicAdd
- atomicCAS (fallback p/ double em GPUs antigas)
### Transferência de Dados
- cudaMalloc / cudaFree
- cudaMemcpy (H2D / D2H)
- cudaMemset
- Minimizar cópias: dados residentes na GPU
### Grid-Stride Loop
### Tratamento de Erros
- cudaError_t / cudaGetLastError
### Streams
- Sobreposição de cópia e computação
---
## MEMÓRIA EM GPU
### Registradores
### Shared Memory
- Compartilhada por bloco
- Cache manual (ex.: centroides)
### Local Memory
### Global Memory
### Constant Memory
### Texture Memory
### Pinned Memory
- Transferências mais rápidas
### Hierarquia de Memória
---
## PADRÕES EM GPU
### Reduction
### Scan
### Tiling
### Stencil
### Histograma
- Acumulação com atomics
### Paralelismo Massivo
- Um thread por elemento
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
