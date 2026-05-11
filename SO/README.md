# Sistemas Operacionais - PUC Minas

Repositório destinado à organização de conteúdos e estudos realizados na disciplina de Sistemas Operacionais do curso de Ciência da Computação.

### 1. Gerência de Memória
Estudo de como o SO gerencia a memória principal e fornece abstrações para os processos.
* **Fundamentos**: Espaço de endereçamento lógico vs. físico.
* **MMU (Memory Management Unit)**: Mapeamento de endereços e registradores de realocação.
* **Swapping**: Troca de processos entre memória e disco.
* **Alocação Contígua**: Partições simples e múltiplas, problemas de fragmentação (interna e externa) e estratégias de alocação (First-fit, Best-fit, Worst-fit).
* **Paginação**: Tabela de páginas, TLB (Translation Look-aside Buffers), proteção de memória e paginação multinível.
* **Memória Virtual**: Paginação sob demanda, tratamento de falta de página (page fault) e algoritmos de substituição (FIFO, Ótimo, LRU).

### 2. Sistemas de Arquivos
Organização lógica e física dos dados em armazenamento secundário.
* **Conceito de Arquivo**: Atributos, operações, tipos e estruturas.
* **Diretórios**: Estruturas em um nível, dois níveis, árvore e grafos.
* **Proteção**: Controle de acesso (Listas de acesso e permissões RWX).
* **Alocação de Espaço**: Métodos de alocação contígua, encadeada e indexada.
* **Gerência de Espaço Livre**: Vetores de bits e listas encadeadas.
* **Sistemas Conhecidos**: Diferenças entre Ext2, Ext3, Ext4, FAT e o conceito de Journaling.

### 3. Subsistema de Entrada e Saída (I/O)
Interface entre o sistema operacional e o hardware periférico.
* **Hardware de I/O**: Portas, barramentos, controladoras e drivers.
* **Comunicação**: E/S programada, Interrupções e DMA (Direct Memory Access).
* **Interface do Kernel**: Dispositivos de bloco vs. dispositivos de caractere, clocks e timers.
* **I/O Bloqueante e Não-bloqueante**: Diferenças de implementação e sincronismo.
* **Subsistema de I/O**: Escalonamento de requisições, Buffering, Caching e Spooling.

### 4. Deadlocks
* **O Problema do Impasse**: Definição e condições necessárias para ocorrência.
* **Modelagem**: Grafo de alocação de recursos e estratégias de prevenção e recuperação.
