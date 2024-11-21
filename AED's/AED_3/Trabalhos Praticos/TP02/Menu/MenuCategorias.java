package Menu;

import Arquivo.*;
import Modelo.*;

import java.util.Scanner;
import java.util.ArrayList;

public class MenuCategorias
{
    ArquivoTarefa arq_tarefa;       // Arquivo para manipulação de tarefas
    ArquivoCategoria arq_categoria; // Instância para manipular o arquivo de categorias
    private static Scanner sc = new Scanner(System.in); // Scanner para entrada de dados

    // Construtor inicializa o gerenciador de arquivos de categorias
    public MenuCategorias() throws Exception
    {
        arq_tarefa = new ArquivoTarefa(); 
        arq_categoria = new ArquivoCategoria();
    }

    // Exibe o menu de categorias e gerencia as opções
    public void menu()
    {
        int opcao;
        do
        {
            // Exibe as opções do menu de categorias
            System.out.println("\nAEDsIII");
            System.out.println("-------");
            System.out.println("> Inicio > Categorias");
            System.out.println("1 - Buscar");
            System.out.println("2 - Incluir");
            System.out.println("3 - Alterar");
            System.out.println("4 - Excluir");
            System.out.println("5 - Listar Categorias");
            System.out.println("0 - Voltar");

            System.out.print("Opção: ");
            try
            {
                opcao = Integer.valueOf(sc.nextLine()); // Lê a escolha do usuário
            }
            catch (NumberFormatException e)
            {
                opcao = -1; // Se ocorrer erro, define opção como inválida
            }

            // Executa a operação correspondente à escolha
            switch (opcao)
            {
                case 1:
                    arq_categoria.listarCategoria();
                    
                    buscarCategoria(); // Busca uma categoria
                    break;
                case 2:
                    incluirCategoria(); // Inclui uma nova categoria
                    break;
                case 3:
                    arq_categoria.listarCategoria();

                    alterarCategoria(); // Altera uma categoria existente
                    break;
                case 4:
                    arq_categoria.listarCategoria();

                    excluirCategoria(); // Exclui uma categoria
                    break;
                case 5:
                    arq_categoria.listarCategoria(); // Listar categorias
                    break;
                case 0:
                    break; // Volta ao menu anterior
                default:
                    System.out.println("Opcao invalida!"); // Opção inválida informada
                    break;
            }

        } while (opcao != 0); // Continua até que o usuário escolha sair
    }

    // Busca uma categoria pelo nome
    public void buscarCategoria()
    {
        String nome;

        System.out.println("\nBuscar categoria");
        System.out.print("\nNome da categoria: ");
        nome = sc.nextLine(); // Lê o nome da categoria

        if (nome.length() == 0) return; // Se o nome for vazio, retorna

        try
        {
            Categoria c = arq_categoria.read(nome); // Lê a categoria do arquivo
            System.out.println(c.toString());       // Exibe a categoria encontrada

            int id_categoria = c.getId();
            ArrayList<Tarefa> t = arq_tarefa.readAll(id_categoria);
            for (Tarefa tmp : t) System.out.println(tmp);
        }
        catch (Exception e)
        {
            System.out.println("Categoria nao encontrada!"); // Categoria não encontrada
        }
    }

    // Inclui uma nova categoria no sistema
    public void incluirCategoria()
    {
        String nome;
        boolean dadosCompletos = false;

        System.out.println("\nInclusao de categoria");
        do
        {
            // Solicita o nome da nova categoria
            System.out.print("\nNome da categoria (min. de 5 letras): ");
            nome = sc.nextLine();
            if (nome.length() >= 5 || nome.length() == 0) 
            {
                dadosCompletos = true; // Verifica se o nome é válido
            }
            else
            {
                System.err.println("O nome da categoria deve ter no mínimo 5 caracteres."); // Nome inválido
            }
        } while (!dadosCompletos);

        if (nome.length() == 0) return; // Se o nome for vazio, retorna

        System.out.println("Confirma a inclusao da categoria? (S/N) ");
        char resp = sc.nextLine().charAt(0); // Confirmação do usuário
        if (resp == 'S' || resp == 's') {
            try
            {
                Categoria c = new Categoria(nome); // Cria uma nova categoria
                arq_categoria.create(c); // Adiciona a categoria ao arquivo
                System.out.println("Categoria criada com sucesso.");
            }
            catch (Exception e)
            {
                System.err.println("Erro do sistema. Não foi possivel criar a categoria!"); // Erro ao criar
            }
        }
    }

    // Altera uma categoria existente
    public void alterarCategoria()
    {
        String nome;

        System.out.println("\nAlterar categoria");
        System.out.print("\nNome da categoria (min. de 5 letras): ");
        nome = sc.nextLine(); // Lê o nome da categoria a ser alterada

        if (nome.length() == 0) return; // Se o nome for vazio, retorna
        try
        {
            Categoria c = arq_categoria.read(nome); // Lê a categoria do arquivo

            System.out.println("Confirma a alteracao da categoria? (S/N) ");
            char resp = sc.nextLine().charAt(0); // Confirmação do usuário
            if (resp == 'S' || resp == 's')
            {
                System.out.println("Digite o novo nome da categoria: ");
                nome = sc.nextLine(); // Lê o novo nome

                c.setNome(nome); // Atualiza o nome da categoria
                arq_categoria.update(c); // Atualiza a categoria no arquivo

                System.out.println("Categoria atualizada com sucesso.");
            }
        }
        catch (Exception e)
        {
            System.err.println("Categoria nao econtrada"); // Erro ao alterar
        }
    }

    // Exclui uma categoria existente
    public void excluirCategoria()
    {
        String nome;

        System.out.println("\nExcluir categoria: ");
        nome = sc.nextLine(); // Lê o nome da categoria a ser excluída

        if (nome.length() == 0) return; // Se o nome for vazio, retorna

        try
        {   
            int id_categoria = arq_categoria.read(nome).getId();
            if (!arq_tarefa.readAll(id_categoria).isEmpty())
            {
                System.err.println("Nao eh possivel excluir, existem tarefas relacionadas");
                return;
            }
        }
        catch (Exception e)
        {
            System.err.println("Erro no sistema");
            return;
        }

        System.out.println("Confirma a exclusao da categoria? (S/N) ");
        char resp = sc.nextLine().charAt(0); // Confirmação do usuário
        if (resp == 'S' || resp == 's')
        {
            try
            {
                if (arq_categoria.delete(nome)) // Tenta excluir a categoria
                {
                    System.out.println("Categoria excluida com sucesso."); // Exclusão bem-sucedida
                }
                else
                {
                    System.out.println("Categoria inexistente"); // Categoria não existe
                }
            }
            catch (Exception e)
            {
                System.err.println("Erro do sistema. Nao foi possível excluir a categoria!"); // Erro ao excluir
            }
        }
    }
}
