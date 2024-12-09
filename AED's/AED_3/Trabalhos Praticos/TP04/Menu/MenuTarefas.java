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
    ArquivoRotulo arq_rotulos;

    private static Scanner sc = new Scanner(System.in); // Scanner para entrada do usuário

    public MenuTarefas() throws Exception
    {
        arq_tarefa = new ArquivoTarefa();       // Inicializa o arquivo de tarefas
        arq_categoria = new ArquivoCategoria(); // Inicializa o arquivo de categorias
        arq_rotulos = new ArquivoRotulo(); // Inicializa o arquivo de categorias

    }

    public void menu() throws Exception
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
            System.out.println("5 - Atualizar Rotulo");
            System.out.println("6 - Listar Tarefas por Categoria");
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

            System.out.println();

            switch (opcao)
            {
                case 1:
                    listarTarefas(); // Método para buscar tarefa
                    break;
                case 2:
                    arq_categoria.listarCategoria();
                    incluirTarefa(); // Chama o método para incluir nova tarefa
                    break;
                case 3:
                    alterarTarefa(); // Método para alterar tarefa
                    break;
                case 4:
                    excluirTarefa(); // Método para excluir tarefa
                    break;
                case 5:
                    atualizarRotulo(); // Listar categorias
                    break;
                case 6:
                    arq_categoria.listarCategoria();
                    listarTarefa(); // Listar categorias
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
            ArrayList<Tarefa> t = arq_tarefa.readAll(c.getId()); // Lê todas as tarefas da categoria

            if (t.isEmpty())
            {
                System.out.println("Nao existem tarefas nesta categoria");
                return;
            }
            for (int i = 0; i < t.size(); i++)
            {
                System.out.println((i + 1) + ") " + t.get(i).getNome());
            }

            System.out.print("\nNome da tarefa: ");
            String nome_tarefa = sc.nextLine();
    
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

    public void incluirTarefa() throws Exception
    {
        String categoria; // Nome da categoria da tarefa
        int id_categoria = -1; // ID da categoria

        System.out.println("Nome da categoria da tarefa: ");
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

        int newRotulo = 1;
        ArrayList<Rotulo> rotulo = new ArrayList<>();
        ArrayList<Integer> posRotulosLista = new ArrayList<>();
        System.out.println("Deseja adicionar alguma Rotulo ? (1 para sim, 0 para não)");
        newRotulo = sc.nextInt();
        while (newRotulo == 1) {
          System.out.println("Digite o índice da Rotulo que deseja adicionar a esta tarefa");
          System.out.println();
          rotulo = arq_rotulos.listar();
          System.out.println();
          posRotulosLista.add(sc.nextInt() - 1);
          System.out.println("Deseja adicionar mais Rotulos? (1 para sim, 0 para não)");
          newRotulo = sc.nextInt();
        }
        ArrayList<Integer> aux = new ArrayList<>();
        for (int i = 0; i < posRotulosLista.size(); i++) {
          aux.add(rotulo.get(posRotulosLista.get(i)).getId());
        }

        sc.nextLine(); // Limpa o buffer
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
            Tarefa nova_tarefa = new Tarefa(id_categoria, nome, data_criacao, data_conclusao, status, prioridade,aux); // Cria nova tarefa
            arq_tarefa.create(nova_tarefa); // Salva a tarefa no arquivo
            System.out.println("Tarefa criada com sucesso."); // Mensagem de sucesso
        }
        catch (Exception e)
        {
            System.err.println("Erro do sistema. Não foi possível criar a tarefa!"); // Mensagem de erro em caso de falha
        }
    }

    public void alterarTarefa() throws Exception
    {
        String termo;
        int numero_tarefa = -1;
        Tarefa t = new Tarefa(), old;
        ArrayList<Tarefa> tarefas = null;
    
        try
        {
            while (tarefas == null || tarefas.size() == 0)
            {
                System.out.print("Digite o termo que deseja pesquisar no banco de tarefas: ");
                termo = sc.nextLine();
                try
                {
                    tarefas = listarTarefas(termo);
                    if (tarefas == null || tarefas.size() == 0)
                    {
                        System.out.println("Tarefas nao encontradas");
                        return;
                    }
                }
                catch (Exception e)
                {
                    System.err.println("Erro ao listar tarefas: " + e.getMessage());
                    return;
                }
            }
    
            while (numero_tarefa < 0 || numero_tarefa > tarefas.size())
            {
                System.out.println("Digite o número da Tarefa que deseja atualizar\nObs: digite 0 para cancelar");
                try
                {
                    numero_tarefa = Integer.valueOf(sc.nextLine());

                    if (numero_tarefa == 0)
                    {
                        System.out.println("Operação cancelada.");
                        return;
                    }
                    if (numero_tarefa < 0 || numero_tarefa > tarefas.size())
                    {
                        System.out.println("Tarefa não encontrada, tente novamente");
                    }
                }
                catch (Exception e)
                {
                    System.err.println("Erro ao selecionar tarefa: " + e.getMessage());
                }
            }
            old = tarefas.get(numero_tarefa - 1);
            System.out.println("Tarefa Selecionada: " + old.getNome());

            System.out.println("\nNovos dados da tarefa: ");
            System.out.print("Nome da Tarefa: ");
            String nome = sc.nextLine();
    
            // Criando o formatador para dd/MM/yyyy
            DateTimeFormatter formatter = DateTimeFormatter.ofPattern("dd/MM/yyyy");
    
            System.out.print("Data de Criação (dd/MM/yyyy): ");
            LocalDate data_criacao = LocalDate.parse(sc.nextLine(), formatter);
    
            System.out.print("Data de Conclusão (dd/MM/yyyy): ");
            String data = sc.nextLine();
            LocalDate data_conclusao = data.isEmpty() ? null : LocalDate.parse(data, formatter);
    
            System.out.print("Status da Tarefa (pendente / em progresso / concluída): ");
            String status = sc.nextLine();
    
            System.out.print("Prioridade da Tarefa (0 a 127): ");
            byte prioridade = Byte.parseByte(sc.nextLine());
    
            // Criar a nova tarefa usando o construtor
            t = new Tarefa(old.getId(), old.getIdCategoria(), nome, data_criacao, data_conclusao, status, prioridade, old.getIDRotulo());
            System.out.println("Confirma a alteracao da tarefa? (S/N) ");
            char resp = sc.nextLine().charAt(0);
    
            if (resp == 'S' || resp == 's')
            {
                try
                {
                    if (arq_tarefa.update(old, t))
                    {
                        System.out.println("Tarefa alterada com sucesso.");
                    }
                    else
                    {
                        System.out.println("Falha ao alterar tarefa.");
                    }
                }
                catch (Exception e)
                {
                    System.err.println("Erro do sistema. Não foi possível alterar a tarefa: " + e.getMessage());
                }
            }
            else
            {
                System.out.println("Alteração cancelada.");
            }
        }
        catch (Exception e)
        {
            System.err.println("Erro no sistema");
        }
    }
    
    public void excluirTarefa() throws Exception
    {
    try
    {
        String termo;
        int numero_tarefa = -1;
        ArrayList<Tarefa> tarefas = null;

        while(tarefas == null || tarefas.size() == 0)
        {
          System.out.print("Digite o termo que deseja pesquisar no banco de tarefas: ");
          termo = sc.nextLine();
          tarefas = listarTarefas(termo);
          if(tarefas == null || tarefas.size() == 0)
          {
            System.out.println("Tarefas nao encontradas");
            return;
          }
        }
        while (numero_tarefa < 0 || numero_tarefa > tarefas.size())
        {
          System.out.println("Digite o número da Tarefa que deseja deletar\nObs: digite 0 para cancelar");
          numero_tarefa = sc.nextInt();
          if (numero_tarefa < 0 || numero_tarefa > tarefas.size())
          {
            System.out.println("Tarefa não encontrada, tente novamente");
          }
        }
        if (arq_tarefa.delete(tarefas.get(numero_tarefa - 1)))
        {
          System.out.println("Tarefa deletada com sucesso");
        }
        else
        {
          System.out.println("Erro ao deletar a tarefa");
        }
    }
    catch (Exception e)
    {
        System.out.println(e.getMessage());
    }

    }

    public void listarTarefa()
    {
        String nome;

        System.out.print("\nDigite o nome da categoria que deseja ver as tarefas: ");
        nome = sc.nextLine(); // Lê o nome da categoria

        if (nome.length() == 0) return; // Se o nome for vazio, retorna

        try
        {
            Categoria c = arq_categoria.read(nome); // Lê a categoria do arquivo
            System.out.println(c.getNome());       // Exibe a categoria encontrada

            int id_categoria = c.getId();
            ArrayList<Tarefa> t = arq_tarefa.readAll(id_categoria);
            
            if (t.isEmpty())
            {
                System.out.println("Nao existem tarefas criadas nesta categoria!");
            }
            else
            {
                for (int i = 0; i < t.size(); i++)
                {
                    System.out.println((i + 1) + ") " + t.get(i).getNome());
                }
            }
        }
        catch (Exception e)
        {
            System.out.println("Categoria nao encontrada!"); // Categoria não encontrada
        }
    }
  

    public ArrayList<Tarefa> listarTarefas(String termo) throws Exception
    {
      ArrayList<Tarefa> tarefas = null;
      try
      {
        
          int numero_tarefa = 1;
          termo = termo.toLowerCase();
          tarefas = arq_tarefa.listar(termo);
          for (Tarefa tmp : tarefas)
          {
            System.out.print("\nN° Tarefa.....: " + numero_tarefa);
            System.out.println(tmp);
            numero_tarefa++;
          }
        }
        catch (Exception e)
        {
          System.out.println(e.getMessage());
        }
        return tarefas;
      }
  
      public void listarTarefas() throws Exception
      {
        
        try
        {
          int numero_tarefa = 1;
          System.out.print("Digite o termo que deseja buscar no banco de tarefas: ");
          String titulo = sc.nextLine();
          titulo = titulo.toLowerCase();
          
          ArrayList<Tarefa> tarefas = arq_tarefa.listar(titulo);

          if (tarefas.isEmpty())
          {
            System.err.println("Termo nao encontrado");
            return; 
          }

          for (Tarefa tmp : tarefas)
          {
            System.out.print("\nN° Tarefa.....: " + numero_tarefa);
            System.out.println(tmp);
            numero_tarefa++;

          }
        }
        catch (Exception e)
        {
          System.out.println(e.getMessage());
        }        
      }
  
    public void atualizarRotulo() throws Exception
    {
        String termo;
        int numero_tarefa = -1;
        Tarefa old = new Tarefa();
        ArrayList<Tarefa> tarefas = null;
        
        try
        {

          while (tarefas == null || tarefas.size() == 0)
          {
            System.out.print("Digite o termo que deseja pesquisar no banco de tarefas: ");
            termo = sc.nextLine();
            tarefas = listarTarefas(termo);
            //System.out.println("Tarefas: " + tarefas.size());
            if (tarefas == null || tarefas.size() == 0)
            {
              System.out.println("Tarefas nao encontradas");
              return;
            }
          }
          while (numero_tarefa < 0 || numero_tarefa > tarefas.size())
          {
            System.out.println("Digite o número da Tarefa que deseja atualizar");
            numero_tarefa = sc.nextInt();
            if (numero_tarefa < 0 || numero_tarefa > tarefas.size())
            {
              System.out.println("Tarefa não encontrada, tente novamente");
            }
            else if(numero_tarefa == 0)
            {
              return;
            }
          }
          old = tarefas.get(numero_tarefa - 1);
          System.out.println("Tarefa Selecionada: " + old.getNome());
        }
        catch (Exception e)
        {
          e.printStackTrace();
        }
  
        // Definindo Rotulos
        int newRotulo = 1;
        ArrayList<Rotulo> Rotulos = new ArrayList<>();
        ArrayList<Integer> posRotulosLista = new ArrayList<>();

        System.out.println("Deseja remover Rotulos ? (1 para sim, 0 para não)");
        newRotulo = sc.nextInt();
        while(newRotulo == 1)
        {
          System.out.println("Digite o índice da Rotulo que deseja remover dessa tarefa");
          System.out.println();
          Rotulos = arq_rotulos.listar();

          System.out.println();
          posRotulosLista.add(sc.nextInt() - 1);

          System.out.println("Deseja remover mais Rotulos? (1 para sim, 0 para não)");
          newRotulo = sc.nextInt();
        }

        ArrayList<Integer> removed = new ArrayList<>();
        for (int i = 0; i < posRotulosLista.size(); i++)
        {
          removed.add(Rotulos.get(posRotulosLista.get(i)).getId());
        }
        posRotulosLista.clear();
        System.out.println("Deseja adicionar Rotulos ? (1 para sim, 0 para não)");

        newRotulo = sc.nextInt();
        while(newRotulo == 1)
        {
          System.out.println("Digite o índice da Rotulo que deseja adicionar dessa tarefa");
          System.out.println();

          Rotulos = arq_rotulos.listar();
          System.out.println();
          posRotulosLista.add(sc.nextInt() - 1);

          System.out.println("Deseja adicionar mais Rotulos? (1 para sim, 0 para não)");
          newRotulo = sc.nextInt();
        }
        ArrayList<Integer> added = new ArrayList<>();
        for (int i = 0; i < posRotulosLista.size(); i++)
        {
          added.add(Rotulos.get(posRotulosLista.get(i)).getId());
        }
  
        if (arq_tarefa.updateRotulos(old, removed, added))
        {
          System.out.println("Rotulos atualizadas com sucesso");
        }
        else
        {
          System.out.println("Erro ao atualizar as Rotulos");
        }
      }
}
