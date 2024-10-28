# TP2

### Alunos
- Edson Pimenta de Almeida
- Luís Augusto Starling Toledo
- Luiz Gabriel Milione Assis

### Descrição do Projeto

Este projeto expande as funcionalidades do trabalho TP1, adicionando as classes `ArquivoTarefa` e `ArquivoCategoria` para realizar operações CRUD e gerenciar um índice indireto. Como cada tarefa está associada a uma categoria, é necessário um índice secundário para manter essa relação, implementado por meio de uma árvore B+.

### Estrutura de Classes

#### Principais Classes

- **Arquivo**: Classe base para operações CRUD genéricas.
- **ArquivoCategoria**: Extensão de `Arquivo` para manipulação de objetos `Categoria`, com índice indireto de categorias.
- **ArquivoTarefa**: Extensão de `Arquivo` para manipulação de objetos `Tarefa`, com índice indireto para busca de tarefas por categoria.
- **ArvoreBMais**: Implementação da árvore B+ para índices secundários.
- **HashExtensivel**: Índice direto baseado em hashing extensível.
- **MenuCategorias** e **MenuTarefas**: Interfaces de interação com o usuário para gerenciamento de categorias e tarefas.
- **Categoria** e **Tarefa**: Representam as entidades principais, com atributos específicos.
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

### Classes de Suporte

- **ParIdId** e **ParNomeId**: Representam pares de valores para indexação em árvore B+.
- **HashExtensivel**: Implementa a indexação direta para classes que estendem `RegistroHashExtensivel`.

### Menus de Interação

- **MenuCategorias** e **MenuTarefas**: Interagem com o usuário, permitindo inclusão, busca, alteração e exclusão de categorias e tarefas.

### Classe `Main`
Executa a aplicação, gerenciando o menu principal e capturando interações do usuário.

### Implementação Técnica

#### Índices e Consistência

- Índice direto de categorias implementado? **Sim**
- Índice indireto para categorias por nome? **Sim**
- ID de categoria como chave estrangeira em tarefas? **Sim**
- Árvore B+ para relação 1:N entre categorias e tarefas? **Sim**
- Listagem de tarefas por categoria? **Sim**
- Exclusão de categorias verifica tarefas vinculadas? **Sim**
- Inclusão de tarefa é limitada a categorias existentes? **Sim**

#### Estado do Projeto

- Funcionando corretamente? **Sim**
- Completo? **Sim**
- Trabalho original? **Sim**
