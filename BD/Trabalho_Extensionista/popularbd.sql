USE `mydb`;

-- Populando a tabela `CATEGORIAS`
INSERT INTO `CATEGORIAS` (`id_categoria`, `nome_categoria`) VALUES
(1, 'Roupas'),
(2, 'Alimentos'),
(3, 'Brinquedos'),
(4, 'Medicamentos');

-- Populando a tabela `DOADORES`
INSERT INTO `DOADORES` (`id_doador`, `nome_doador`, `sobrenome`, `Rua`, `Bairro`, `CEP`, `Numero`, `email`, `data_ultima_doacao`) VALUES
(1, 'João', 'Silva', 'Rua A', 'Centro', 12345678, '100', 'joao.silva@gmail.com', '2024-11-20'),
(2, 'Maria', 'Oliveira', 'Rua B', 'Zona Sul', 87654321, '200', 'maria.oliveira@gmail.com', '2024-11-15');

-- Populando a tabela `PRODUTOS`
INSERT INTO `PRODUTOS` (`id_produto`, `nome_produto`, `Valor`, `Quantidade`, `CATEGORIAS_id_categoria`) VALUES
(1, 'Camisa Infantil', 25.00, 10, 1),
(2, 'Arroz 1kg', 5.50, 50, 2),
(3, 'Boneca', 30.00, 20, 3),
(4, 'Paracetamol', 3.00, 100, 4);

-- Populando a tabela `funcionário`
INSERT INTO `funcionário` (`idfuncionário`, `nome`, `cargo`, `data_entrada`, `telefone`) VALUES
(1, 'Carlos Souza', 'Cuidador', '2022-01-15', '11987654321'),
(2, 'Ana Paula', 'Gerente', '2021-05-20', '11912345678');

-- Populando a tabela `criança acolhida`
INSERT INTO `criança acolhida` (`id_crianca`, `grauparalisia`, `nome`, `data_nascimento`, `funcionário_idfuncionário`) VALUES
(1, 2, 'Lucas', '2015-03-10', 1),
(2, 1, 'Sofia', '2014-07-25', 1);

-- Populando a tabela `instituições _parceiras`
INSERT INTO `instituições _parceiras` (`id_instituicao`, `nome`, `cep`, `bairro`, `rua`, `numero`) VALUES
(1, 'Casa do Bem', '12345000', 'Vila Nova', 'Rua das Flores', 500),
(2, 'Acolher Sempre', '54321000', 'Jardim Alegre', 'Av. Principal', 1000);

-- Populando a tabela `DOACOES`
INSERT INTO `DOACOES` (`id_doacoes`, `Valor`, `Quantidade`, `DOADORES_id_doador`, `PRODUTOS_id_produto`, `CATEGORIAS_id_categoria`, `funcionário_idfuncionário`, `criança acolhida_id_crianca`, `instituições _parceiras_id_instituicao`) VALUES
(1, 50.00, 10, 1, 1, 1, 2, 1, 1),
(2, 27.50, 5, 2, 2, 2, 1, 2, 2);

-- Populando a tabela `TELEFONE`
INSERT INTO `TELEFONE` (`telefone_fixo`, `celular`, `DOADORES_id_doador`) VALUES
(NULL, 11999999999, 1),
(1123456789, 11988888888, 2);
