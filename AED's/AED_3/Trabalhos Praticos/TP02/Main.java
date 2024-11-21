//package Main;

import java.util.Scanner;

import Menu.*;

public class Main {

    public static void main(String[] args)
    {
        Scanner sc;

        try
        {
            sc = new Scanner(System.in);
            int opcao;

            do
            {
                System.out.println("\n> Inicio");
                System.out.println("-------");
                System.out.println("1 - Categorias");
                System.out.println("2 - Tarefas");
                System.out.println("0 - Sair");

                System.out.print("Opcao: ");
                try
                {
                    opcao = Integer.valueOf(sc.nextLine());
                }
                catch (NumberFormatException e)
                {
                    opcao = -1;
                }

                switch (opcao)
                {
                    case 1:
                        (new MenuCategorias()).menu();
                        break;
                    case 2:
                        (new MenuTarefas()).menu();
                        break;
                    case 0:
                        break;
                    default:
                        System.out.println("Opcao invalida!");
                        break;
                }

            } while (opcao != 0);
        }
        catch (Exception e)
        {
            e.printStackTrace();
        }
    }
}