# TP4

### Alunos
- Edson Pimenta de Almeida
- Luís Augusto Starling Toledo
- Luiz Gabriel Milione Assis

### Descrição do Projeto

Este projeto expande as funcionalidades do trabalho TP3, adicionando as classes `Backup` e `MenuBackup` para permitir que o usuário crie, gerencie e utilize backups dos arquivos.
Além disso, as classes `LZW` e `VetorDeBits` fazem a compactação e descompactação dos arquivos.

### Estrutura de Classes

#### Principais Classes

- **Arquivo**: Classe base para operações CRUD genéricas.
- **ArquivoCategoria**: Extensão de `Arquivo` para manipulação de objetos `Categoria`, com índice indireto de categorias.
- **ArquivoTarefa**: Extensão de `Arquivo` para manipulação de objetos `Tarefa`, com índice indireto para busca de tarefas por categoria.
- **ArquivoRotulo**: Extensão de `Arquivo` para manipulação de objetos `Rotulo`, com índice indireto para busca de tarefas por rótulo.
- **Backup**: Manipula os arquivos de backup, garantindo que eles sejam compactados e descompactados corretamente.
- **ArvoreBMais**: Implementação da árvore B+ para índices secundários.
- **HashExtensivel**: Índice direto baseado em hashing extensível.
- **MenuCategorias**, **MenuTarefas**, **MenuRotulos** e **MenuBackup**: Interfaces de interação com o usuário para gerenciamento de categorias, tarefas, rótulos e backups.
- **Categoria** e **Tarefa**: Representam as entidades principais, com atributos específicos.
- **Rotulo**: Representa a entidade rótulo, com seus atributos.
- **ElementoLista**, **ListaInvertida** e **StopWords**: Compõe a lista invertida, capaz de identificar palavras sem importância (stop words) e verificar a frequencia de cada palavra nos rótulos.
- **LZW** e **VetorDeBits**: Fazem a compactação e descompactação dos arquivos.
- **Main**: Classe principal que inicia a aplicação e gerencia a interação do usuário.

#### Interfaces

- **Registro**: Interface para operações genéricas de persistência.
- **RegistroArvoreBMais**: Interface para uso em estruturas de índice indireto B+.
- **RegistroHashExtensivel**: Interface para indexação direta com hash extensível.

### Detalhes das Classes

#### Classe `Arquivo`
Responsável pelo CRUD genérico de objetos do tipo `T`, que devem implementar a interface `Registro`.

- **Atributos**:
  - `int tamanho_cabecalho`: Tamanho do cabeçalho.
  - `RandomAccessFile arquivo`: Arquivo de dados.
  - `String nome_arquivo`: Nome do arquivo.
  - `Constructor<T> construtor`: Construtor da classe T.
  - `HashExtensivel indice_direto`: Índice direto para acesso rápido.

- **Métodos**:
  - `create(T obj)`: Insere um novo objeto, atribui ID, e escreve o índice direto.
  - `read(int id)`: Recupera o objeto pelo ID.
  - `delete(int id)`: Marca o registro como inválido.
  - `update(T obj)`: Atualiza o registro, realocando-o se necessário.
  - `close()`: Fecha o arquivo.

#### Classe `ArquivoCategoria`
Extende `Arquivo` para `Categoria`, com índice indireto para busca de categorias por nome.

- **Atributos**:
  - `ArvoreBMais<ParNomeId> indice_indireto_nome`: Índice para pares `nome_categoria` e `id_categoria`.

- **Métodos**:
  - `int create(Categoria categoria)`: Insere a categoria e atualiza o índice.
  - `Categoria read(String nome)`: Pesquisa uma categoria por nome.
  - `boolean delete(String nome)`: Remove uma categoria pelo nome.
  - `void list()`: Lista todas as categorias.
  - `boolean update(Categoria categoria)`: Atualiza uma categoria existente.

#### Classe `ArquivoTarefa`
Extende `Arquivo` para `Tarefa`, com índice indireto para acesso a tarefas por categoria.

- **Atributos**:
  - `ArvoreBMais<ParIdId> indice_indireto_id`: Índice para pares `id_categoria` e `id_tarefa`.

- **Métodos**:
  - `int create(Tarefa tarefa)`: Insere a tarefa e atualiza o índice.
  - `ArrayList<Tarefa> readAll(int id_categoria)`: Retorna todas as tarefas de uma categoria.
  - `boolean delete(int id)`: Remove uma tarefa e atualiza o índice.
  - `boolean update(Tarefa tarefa)`: Atualiza uma tarefa existente.

#### Classe `Backup`
Responsável por gerenciar backups de arquivos e diretórios, incluindo compressão e descompressão utilizando o algoritmo LZW.

- **Constantes**:
  - `String BACKUP`: Caminho do diretório de backups (`.\\backups`).
  - `String DATA`: Caminho do diretório de dados originais (`.\\dados`).

- **Construtor**:
  - `Backup()`: Garante que os diretórios de backup e dados existem.

- **Métodos**:
  - `void createDirectory(String path)`: Cria um diretório especificado caso ele não exista.
  - `byte[] serializeFiles(File[] files)`: Serializa arquivos em um array de bytes.
  - `byte[] readFile(File file)`: Lê o conteúdo de um arquivo como um array de bytes.
  - `void writeFile(String filepath, byte[] data)`: Escreve um array de bytes em um arquivo.
  - `double calculateCompressRatio(byte[] data_o, byte[] data_c)`: Calcula a taxa de compressão entre dados originais e comprimidos.
  - `void createBackup(String backup_file)`: Cria um backup comprimido no diretório de backups.
  - `void restoreBackup(String backup_file)`: Restaura os dados de um backup para o diretório original.
  - `void clearDirectory(String dir_path)`: Remove todos os arquivos e subdiretórios de um diretório especificado.
  - `ArrayList<String> listBackups()`: Lista os subdiretórios no diretório de backups.

#### Classe `StopWords`
A classe `StopWords` é responsável por gerenciar e processar palavras de parada (stop words) para auxiliar na criação de listas invertidas, removendo palavras irrelevantes de textos e calculando a frequência relativa das palavras restantes.

- **Atributos**:

- **`stopWords`**: (`ArrayList<String>`) - Lista que armazena as palavras de parada lidas do arquivo `stopwords.txt`.
- **`lista`**: (`ListaInvertida`) - Objeto que representa a lista invertida utilizada para gerenciar palavras e suas frequências.

- **Métodos**:
- `String[] stopWordsCheck(String titulo)`: Verifica e remove palavras de parada de uma string de entrada.
- `void wordsCounter(ArrayList<ElementoLista> elementos, String[] chaves, int idChave)`: Conta palavras em um array, calcula suas frequências relativas e as adiciona à lista de elementos.
- `StopWords()`: Construtor que inicializa a lista de palavras de parada e a lista invertida.
- `void inserir(String titulo, int id)`: Insere palavras de um título na lista invertida após remover as palavras de parada e calcular suas frequências.
- `void referencia(String[] args)`: Método principal que possibilita testes da classe. Inclui um menu interativo para gerenciar a lista invertida.


### Classes de Suporte

- **ParIdId** e **ParNomeId**: Representam pares de valores para indexação em árvore B+.
- **HashExtensivel**: Implementa a indexação direta para classes que estendem `RegistroHashExtensivel`.
- **ElementoLista** e **ListaInvertida**: Implementam uma lista invertida.
- **LZW** e **VetorDeBits**: Fazem a compactação e descompactação dos arquivos.

### Menus de Interação

- **MenuCategorias**, **MenuTarefas** e **MenuRotulos**: Interagem com o usuário, permitindo inclusão, busca, alteração e exclusão de categorias, tarefas e rótulos.

### Classe `Main`
Executa a aplicação, gerenciando o menu principal e capturando interações do usuário.

### Implementação Técnica

#### Índices e Consistência

- Há uma rotina de compactação usando o algoritmo LZW para fazer backup dos arquivos? **Sim**
- Há uma rotina de descompactação usando o algoritmo LZW para recuperação dos arquivos? **Sim**
- O usuário pode escolher a versão a recuperar? **Sim**
- Qual foi a taxa de compressão alcançada por esse backup? ~**47%**

#### Estado do Projeto

- Funcionando corretamente? **Sim**
- Completo? **Sim**
- Trabalho original? **Sim**
