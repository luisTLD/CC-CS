# Trabalho Prático 01

## Descrição
Este projeto implementa um CRUD genérico utilizando Java, capaz de realizar operações de inclusão, leitura, atualização e exclusão em um arquivo. O foco do trabalho foi desenvolver um CRUD para gerenciar **tarefas**, além de implementar um **índice com tabela hash extensível**, para mapear o ID de cada tarefa ao seu endereço no arquivo.

### Entidade: Tarefa
Cada tarefa possui os seguintes atributos:
- **Nome**: Identificação da tarefa
- **Data de criação**: Data em que a tarefa foi criada
- **Data de conclusão**: Data de finalização da tarefa
- **Status**: Pendente, Em Progresso, Concluída, etc.
- **Prioridade**: Nível de prioridade da tarefa

### Estrutura do Registro
Cada registro no arquivo é composto por três partes:
1. **Lápide**: Indica se o registro foi excluído.
2. **Indicador de tamanho**: Representa o tamanho do vetor de bytes que descreve o registro.
3. **Vetor de bytes**: Contém os dados da tarefa serializados.

## Operações CRUD
As operações CRUD manipulam exclusivamente o arquivo de dados e são definidas pela interface abaixo:

- `int create(T objeto)`: Insere uma nova tarefa no arquivo e retorna seu ID.
- `T read(int id)`: Retorna a tarefa associada ao ID informado.
- `boolean update(T objeto)`: Atualiza a tarefa existente com o ID especificado.
- `boolean delete(int id)`: Marca a tarefa como excluída no arquivo.

### Índice
Para gerenciar os IDs das tarefas, utilizamos uma **tabela hash extensível**, que armazena o ID da tarefa e o endereço do registro no arquivo. Essa tabela é atualizada automaticamente nas operações de inclusão, exclusão e atualização de registros.

## Testes
O projeto inclui um programa de testes que insere, altera, consulta e exclui tarefas no arquivo de forma automática, validando o correto funcionamento do CRUD e do índice hash.

## Tecnologias Utilizadas
- **Java**
- **RandomAccessFile** para manipulação de arquivos
- **Tabela Hash Extensível** para indexação direta dos registros


