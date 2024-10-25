package Menu;

import Arquivo.*;
import Modelo.*;

import java.time.LocalDate;
import java.time.format.DateTimeFormatter;
import java.util.ArrayList;
import java.util.Scanner;

public class MenuTarefas {

    ArquivoTarefa arq_tarefa;       // Arquivo para manipulação de tarefas
    ArquivoCategoria arq_categoria; // Arquivo para manipulação de categorias
    private static Scanner sc = new Scanner(System.in); // Scanner para entrada do usuário

    public MenuTarefas() throws Exception
    {
        arq_tarefa = new ArquivoTarefa();       // Inicializa o arquivo de tarefas
        arq_categoria = new ArquivoCategoria(); // Inicializa o arquivo de categorias
    }

    public void menu()
    {
        int opcao; // Opção selecionada pelo usuário
        do
        {
            // Exibe o menu
            System.out.println("\nAEDsIII");
            System.out.println("-------");
            System.out.println("> Inicio > Tarefas");
            System.out.println("1 - Buscar");
            System.out.println("2 - Incluir");
            System.out.println("3 - Alterar");
            System.out.println("4 - Excluir");
            System.out.println("0 - Voltar");

            System.out.print("Opcao: ");
            try
            {
                opcao = Integer.valueOf(sc.nextLine()); // Lê a opção do usuário
            }
            catch(NumberFormatException e)
            {
                opcao = -1; // Define opção inválida se ocorrer erro
            }

            switch (opcao) {
                case 1:
                    buscarTarefa(); // Método para buscar tarefa (ainda não implementado)
                    break;
                case 2:
                    incluirTarefa(); // Chama o método para incluir nova tarefa
                    break;
                case 3:
                    alterarTarefa(); // Método para alterar tarefa (ainda não implementado)
                    break;
                case 4:
                    excluirTarefa(); // Método para excluir tarefa (ainda não implementado)
                    break;
                case 0:
                    break; // Sai do loop se a opção for 0
                default:
                    System.out.println("Opcao invalida!"); // Mensagem de erro para opção inválida
                    break;
            }

        } while (opcao != 0); // Continua até que a opção seja 0
    }

    // Buscar uma tarefa, tendo que pesquisar pela categoria dela primeiro para acessar suas tarefas e depois fazer a busca
    public void buscarTarefa()
    {
        String nome_categoria;
        System.out.println("\nNome da categoria da tarefa: ");
        nome_categoria = sc.nextLine(); // Lê o nome da categoria
    
        try
        {
            Categoria c = arq_categoria.read(nome_categoria); // Busca a categoria pelo nome
            System.out.println("Nome da tarefa: ");
            String nome_tarefa = sc.nextLine();
            ArrayList<Tarefa> t = arq_tarefa.readAll(c.getId()); // Lê todas as tarefas da categoria
    
            for (Tarefa tmp : t) // Itera sobre as tarefas
            { 
                if (tmp.getNome().equals(nome_tarefa)) // Verifica se a tarefa corresponde ao nome fornecido
                {
                    System.out.println("Tarefa encontrada: ");
                    System.out.println(tmp); 
                    return; 
                }
            }
            System.out.println("Tarefa nao econtrada nesta categoria!");
        }
        catch (Exception e)
        {
            System.err.println("Erro no sistema");
        }
    }

    public void incluirTarefa()
    {
        String categoria; // Nome da categoria da tarefa
        int id_categoria = -1; // ID da categoria

        System.out.println("\nNome da categoria da tarefa: ");
        try
        {
            categoria = sc.nextLine();                            // Lê o nome da categoria
            id_categoria = arq_categoria.read(categoria).getId(); // Busca o ID da categoria
        }
        catch (Exception e)
        {
            System.err.println("Categoria não encontrada!"); // Mensagem de erro se a categoria não for encontrada
            return;
        }

        System.out.println("\nInclusao de tarefa");

        System.out.print("Nome da Tarefa: ");
        String nome = sc.nextLine(); // Lê o nome da tarefa

        // Criando o formatador para dd/MM/yyyy
        DateTimeFormatter formatter = DateTimeFormatter.ofPattern("dd/MM/yyyy");

        System.out.print("Data de Criação (dd/MM/yyyy): ");
        LocalDate data_criacao = LocalDate.parse(sc.nextLine(), formatter); // Lê a data de criação no formato dd/MM/yyyy

        System.out.print("Data de Conclusão (dd/MM/yyyy): ");
        String input = sc.nextLine();
        LocalDate data_conclusao = input.isEmpty() ? null : LocalDate.parse(input, formatter); // Lê a data de conclusão

        System.out.print("Status da Tarefa (pendente / em progresso / concluída): ");
        String status = sc.nextLine(); // Lê o status da tarefa

        System.out.print("Prioridade da Tarefa (0 a 127): ");
        byte prioridade = Byte.parseByte(sc.nextLine()); // Lê a prioridade da tarefa

        // Criar a nova tarefa usando o construtor
        try
        {
            Tarefa nova_tarefa = new Tarefa(id_categoria, nome, data_criacao, data_conclusao, status, prioridade); // Cria nova tarefa
            arq_tarefa.create(nova_tarefa); // Salva a tarefa no arquivo
            System.out.println("Tarefa criada com sucesso."); // Mensagem de sucesso
        }
        catch (Exception e)
        {
            System.err.println("Erro do sistema. Não foi possível criar a tarefa!"); // Mensagem de erro em caso de falha
        }
    }

    public void alterarTarefa()
    {
        String nome_categoria;
        System.out.println("\nNome da categoria da tarefa: ");
        nome_categoria = sc.nextLine(); // Lê o nome da categoria
    
        try
        {
            Categoria c = arq_categoria.read(nome_categoria); // Busca a categoria pelo nome
            System.out.println("Nome da tarefa: ");
            String nome_tarefa = sc.nextLine();
            ArrayList<Tarefa> t = arq_tarefa.readAll(c.getId()); // Lê todas as tarefas da categoria
    
            Tarefa velha_tarefa = new Tarefa();
            velha_tarefa.setId(-1);
            for (Tarefa tmp : t) // Itera sobre as tarefas
            { 
                if (tmp.getNome().equals(nome_tarefa)) // Verifica se a tarefa corresponde ao nome fornecido
                {
                    System.out.println("Tarefa encontrada: ");
                    System.out.println(tmp); 
                    velha_tarefa = tmp;
                    break;
                }
            }

            // Se a tarefa for achada
            if (velha_tarefa.getId() != -1)
            {
                System.out.println("Novos dados da tarefa: ");
                System.out.print("Nome da Tarefa: ");
                String nome = sc.nextLine(); // Lê o nome da tarefa

                // Criando o formatador para dd/MM/yyyy
                DateTimeFormatter formatter = DateTimeFormatter.ofPattern("dd/MM/yyyy");

                System.out.print("Data de Criação (dd/MM/yyyy): ");
                LocalDate data_criacao = LocalDate.parse(sc.nextLine(), formatter); // Lê a data de criação no formato dd/MM/yyyy

                System.out.print("Data de Conclusão (dd/MM/yyyy): ");
                String input = sc.nextLine();
                LocalDate data_conclusao = input.isEmpty() ? null : LocalDate.parse(input, formatter); // Lê a data de conclusão

                System.out.print("Status da Tarefa (pendente / em progresso / concluída): ");
                String status = sc.nextLine(); // Lê o status da tarefa

                System.out.print("Prioridade da Tarefa (0 a 127): ");
                byte prioridade = Byte.parseByte(sc.nextLine()); // Lê a prioridade da tarefa

                // Criar a nova tarefa usando o construtor
                Tarefa nova_tarefa = new Tarefa(velha_tarefa.getId(), velha_tarefa.getIdCategoria(), nome, data_criacao, data_conclusao, status, prioridade); // Cria nova tarefa
                
                System.out.println("Confirma a alteracao da tarefa? (S/N) ");
                char resp = sc.nextLine().charAt(0); // Confirmação do usuário
                if (resp == 'S' || resp == 's')
                {
                    try
                    {
                        if (arq_tarefa.update(nova_tarefa)) // Tenta alterar a tarefa
                        {
                            System.out.println("tarefa alterada com sucesso.");
                        }
                        else
                        {
                            System.out.println("Falha ao aletarar tarefa."); 
                        }
                    }
                    catch (Exception e)
                    {
                        System.err.println("Erro do sistema. Nao foi possível alterar a tarefa!"); // Erro ao alterar
                    }
                }
            }
            else
            {
                System.out.println("Tarefa nao econtrada nesta categoria!");
            }
        }
        catch (Exception e)
        {
            System.err.println("Erro no sistema");
        }
    }

    public void excluirTarefa()
    {
        String nome_categoria;
        System.out.println("\nNome da categoria da tarefa: ");
        nome_categoria = sc.nextLine(); // Lê o nome da categoria
    
        try
        {
            Categoria c = arq_categoria.read(nome_categoria); // Busca a categoria pelo nome
            System.out.println("Nome da tarefa: ");
            String nome_tarefa = sc.nextLine();
            ArrayList<Tarefa> t = arq_tarefa.readAll(c.getId()); // Lê todas as tarefas da categoria
    
            int id_tarefa = -1;
            for (Tarefa tmp : t) // Itera sobre as tarefas
            { 
                if (tmp.getNome().equals(nome_tarefa)) // Verifica se a tarefa corresponde ao nome fornecido
                {
                    System.out.println("Tarefa encontrada: ");
                    System.out.println(tmp); 
                    id_tarefa = tmp.getId();
                    break;
                }
            }

            // Se a tarefa for achada
            if (id_tarefa != -1)
            {
                System.out.println("Confirma a exclusao da tarefa? (S/N) ");
                char resp = sc.nextLine().charAt(0); // Confirmação do usuário
                if (resp == 'S' || resp == 's')
                {
                    try
                    {
                        if (arq_tarefa.delete(id_tarefa)) // Tenta excluir a tarefa
                        {
                            System.out.println("tarefa excluida com sucesso."); // Exclusão bem-sucedida
                        }
                        else
                        {
                            System.out.println("tarefa inexistente"); // tarefa não existe
                        }
                    }
                    catch (Exception e)
                    {
                        System.err.println("Erro do sistema. Nao foi possível excluir a tarefa!"); // Erro ao excluir
                    }
                }
            }
            else
            {
                System.out.println("Tarefa nao econtrada nesta categoria!");
            }
        }
        catch (Exception e)
        {
            System.err.println("Erro no sistema");
        }
    }
}
