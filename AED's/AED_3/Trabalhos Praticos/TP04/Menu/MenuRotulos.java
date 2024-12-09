package Menu;

import Arquivo.*;
import Modelo.*;
import java.util.ArrayList;
import java.util.Scanner;

public class MenuRotulos
 {
    public static ArquivoRotulo arq_rotulo;
    Scanner scanf = new Scanner(System.in);

    public void menu() throws Exception {
      arq_rotulo = new ArquivoRotulo();
      int resposta = 0;
      System.out.println("\n> Inicio > Rotulos" );

      System.out.println("1 - Incluir" );
      System.out.println("2 - Buscar" );
      System.out.println("3 - Alterar" );
      System.out.println("4 - Excluir" );
      System.out.println("0 - Voltar" );
      System.out.print("Opção: " );
      resposta = Integer.valueOf(scanf.nextLine());

      System.out.println();

      switch (resposta)
      {
        case 1:
          criarRotulo();
          break;
        case 2:
          listarRotulo();
          break;
        case 3:
          atualizarRotulo();
          break;
        case 4:
          deletarRotulo();
          break;
        case 5:
          break;
        default:
          System.out.println("Opção Inválida");
          break;
      }
    }

    public void criarRotulo() throws Exception
    {
      try
      {
        System.out.println("Digite o nome da Rotulo a ser Criada");
        arq_rotulo.create(scanf.nextLine());
      }
      catch (Exception e)
      {
        System.out.println(e.getMessage());
      }
      System.out.println("Criado com sucesso");
      System.out.println();
      arq_rotulo.listar();
    }

    public void listarRotulo() throws Exception 
    {
      String nome_rotulo;
      try
      {
        arq_rotulo.listar();
        
        System.out.print("\nDigite o nome da Rotulo que deseja listar as tarefas: ");

        nome_rotulo = scanf.nextLine();

        ArrayList<Tarefa> t = arq_rotulo.read(nome_rotulo);

        // Itera sobre os rotulos
        for (Tarefa tmp : t)
        { 
            System.out.println(tmp);
        }

      }
      catch (Exception e)
      {
        System.out.println(e.getMessage());
      }
    }

    public void atualizarRotulo() throws Exception
    {
      String nome_rotulo, novo_rotulo;
      try
      {
        arq_rotulo.listar();

        System.out.print("Digite o nome do Rotulo que deseja atualizar: "); 
        nome_rotulo = scanf.nextLine();

        ArrayList<Rotulo> t = arq_rotulo.listar();
        boolean find = false;
        for (Rotulo tmp : t) 
        {
          if (tmp.getNome().equals(nome_rotulo)) find = true;
        }
        if (find == false)
        {
          System.out.println("Rotulo nao encontrado");
          return;
        }

        System.out.println("Digite o nome do novo Rotulo");
        novo_rotulo = scanf.nextLine();

        arq_rotulo.update(nome_rotulo, novo_rotulo);
      }
      catch (Exception e)
      {
        System.out.println(e.getMessage());
      }
      System.out.println("Atualizado com sucesso");
    }

    public void deletarRotulo() throws Exception
    {
      String nome_rotulo;
      try
      {
        ArrayList<Rotulo> Rotulos = arq_rotulo.listar();
        System.out.println();

        System.out.print("Digite o índice da Rotulo que deseja deletar: ");
        int index = scanf.nextInt();
        if(index < 0 || index > Rotulos.size())
        {
          System.out.println("Indice invalido");
          return;
        }
        
        nome_rotulo = Rotulos.get(index - 1).getNome();
        if (arq_rotulo.delete(nome_rotulo))
        {
          System.out.println("Deletado com sucesso");
        }
      }
      catch (Exception e)
      {
        System.out.println(e.getMessage());
      }
    }
  }

    

