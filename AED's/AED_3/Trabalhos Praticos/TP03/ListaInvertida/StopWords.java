package ListaInvertida;

import java.util.ArrayList;
import java.util.Scanner;
import java.io.File;

public class StopWords
{
  // Lista para armazenar as palavras de parada (stop words)
  public ArrayList<String> stopWords = new ArrayList<String>();
  public ListaInvertida lista;

  // Método para verificar e remover stop words de um título
  public String[] stopWordsCheck(String titulo)
  {
    String chaves[] = titulo.split(" "); // Divide o título em palavras
    for (int i = 0; i < chaves.length; i++) 
    {
      chaves[i] = chaves[i].toLowerCase(); // Converte cada palavra para minúsculas
    }
    for (int i = 0; i < chaves.length; i++) 
    {
      for (int j = 0; j < stopWords.size(); j++) 
      {
        if (chaves[i].equals(stopWords.get(j))) // Se a palavra for uma stop word
        { 
          chaves[i] = ""; // Remove a palavra
        }
      }
    }
    return chaves; // Retorna o array de palavras processadas
  }

  // Método para contar palavras e calcular frequência relativa
  public void wordsCounter(ArrayList<ElementoLista> elementos, String[] chaves, int idChave)
  {
    int qtdChaves = 0;
    for (int i = 0; i < chaves.length; i++) 
    {
      if (!chaves[i].equals("") && !chaves[i].equals(" ")) // Conta palavras não vazias
      { 
        qtdChaves++;
      }
    }
    for (int i = 0; i < chaves.length; i++) 
    {
      float frequencia = 1;
      if (!chaves[i].equals("") && !chaves[i].equals(" ")) 
      {
        for (int j = 0; j < chaves.length; j++) 
        {
          if (chaves[i].equals(chaves[j]) && i != j) // Verifica palavras repetidas
          { 
            frequencia++; // Incrementa a frequência
            chaves[j] = ""; // Marca a palavra como processada
          }
        }
      }
      elementos.add(new ElementoLista(idChave, frequencia / qtdChaves)); // Adiciona à lista com frequência relativa
    }
  }

  // Construtor da classe StopWords
  public StopWords()
  {
    File arquivo;
    try
    {
      arquivo = new File("ListaInvertida/stopwords.txt");
      Scanner scanner = new Scanner(arquivo);
      while (scanner.hasNext()) {
        String linha = scanner.nextLine();
        linha = linha.toLowerCase(); // Converte cada linha para minúsculas
        linha = linha.substring(0, linha.length() - 1); // Remove o último caractere
        stopWords.add(linha); // Adiciona à lista de stop words
      }
      scanner.close();
    } catch (Exception e) 
    {
      e.printStackTrace();
      System.out.println("Erro ao abrir o arquivo de StopWords");
    }
    try 
    {
      File d = new File("dados");
      if (!d.exists())
        d.mkdir(); // Cria o diretório de dados se não existir
      lista = new ListaInvertida(4, "dados/dicionario.listainv.db", "dados/blocos.listainv.db"); // Inicializa a lista invertida
    } catch (Exception e) {
      e.printStackTrace();
      System.out.println("Erro ao criar a lista invertida");
    }
  }

  // Método para inserir palavras na lista invertida
  public void inserir(String titulo, int id)
  {
    String[] chaves;
    chaves = stopWordsCheck(titulo); // Remove as stop words do título
    ArrayList<ElementoLista> elementos = new ArrayList<ElementoLista>();
    wordsCounter(elementos, chaves, id); // Conta palavras e calcula frequência
    for (int i = 0; i < chaves.length; i++) 
    {
      if (chaves[i] != "" && chaves[i] != " ") 
      { // Insere palavras válidas
        try 
        {
          lista.create(chaves[i], elementos.get(i)); // Adiciona à lista invertida
        } catch (Exception e) 
        {
          e.printStackTrace();
          System.out.println("Erro ao inserir na lista invertida");
        }
      }
    }
    try 
    {
      lista.incrementaEntidades(); // Incrementa o contador de entidades
    } catch (Exception e) 
    {
      e.printStackTrace();
      System.out.println("Erro ao incrementar entidades");
    }
  }

  // Método principal para testes
  public void referencia(String[] args) 
  {
    StopWords stopWords = new StopWords(); // Inicializa a classe
    Scanner console = new Scanner(System.in);
    boolean novaFrase = true;

    try 
    {
      File d = new File("dados");
      if (!d.exists())
        d.mkdir(); // Cria o diretório de dados se não existir
      lista = new ListaInvertida(4, "dados/dicionario.listainv.db", "dados/blocos.listainv.db");

      // Loop para adicionar frases à lista invertida
      while (novaFrase) 
      {
        System.out.println("Digite o título da tarefa: ");
        String titulo = console.nextLine();
        String[] chaves;
        chaves = stopWords.stopWordsCheck(titulo); // Processa o título
        ArrayList<ElementoLista> elementos = new ArrayList<ElementoLista>();
        stopWords.wordsCounter(elementos, chaves, 0); // Conta palavras
        for (int i = 0; i < chaves.length; i++) 
        {
          if (chaves[i] != "" && chaves[i] != " ") 
          {
            lista.create(chaves[i], elementos.get(i)); // Adiciona palavras à lista
          }
        }
        System.out.println("Deseja adicionar outra tarefa? (S/N)");
        String resposta = console.nextLine();
        if (resposta.equals("N") || resposta.equals("n")) 
        {
          novaFrase = false; // Finaliza o loop
        }
      }
    } catch (Exception e) 
    {
      e.printStackTrace();
    }

    // Menu de opções
    try 
    {
      File d = new File("dados");
      if (!d.exists())
        d.mkdir(); // Cria o diretório de dados se não existir
      lista = new ListaInvertida(4, "dados/dicionario.listainv.db", "dados/blocos.listainv.db");

      int opcao;
      do 
      {
        System.out.println("---MENU---");
        System.out.println("1 - Inserir..............");
        System.out.println("2 - Buscar...............");
        System.out.println("3 - Excluir..............");
        System.out.println("4 - Imprimir.............");
        System.out.println("5 - Incrementar entidades");
        System.out.println("6 - Decrementar entidades");
        System.out.println("0 - Sair.................");
        try 
        {
          opcao = Integer.valueOf(console.nextLine()); // Lê a opção do menu
        } catch (NumberFormatException e) {
          opcao = -1; // Define como inválido se não for numérico
        }

        // Processa a opção escolhida
        switch (opcao) 
        {
          case 1: 
          {
            System.out.println("\nINCLUSÃO");
            System.out.print("Termo: ");
            String chave = console.nextLine();
            System.out.print("ID: ");
            int id = Integer.valueOf(console.nextLine());
            System.out.print("Frequência: ");
            float frequencia = Float.valueOf(console.nextLine());
            lista.create(chave, new ElementoLista(id, frequencia)); // Insere na lista
            lista.print();
          }
            break;
          case 2: 
          {
            System.out.println("\nBUSCA");
            System.out.print("Chave: ");
            String chave = console.nextLine();
            ElementoLista[] elementos = lista.read(chave); // Lê elementos pela chave
            System.out.print("Elementos: ");
            for (int i = 0; i < elementos.length; i++)
              System.out.print(elementos[i] + " ");
          }
            break;
          case 3: 
          {
            System.out.println("\nEXCLUSÃO");
            System.out.print("Chave: ");
            String chave = console.nextLine();
            System.out.print("ID: ");
            int id = Integer.valueOf(console.nextLine());
            lista.delete(chave, id); // Exclui o elemento
            lista.print();
          }
            break;
          case 4: 
          {
            lista.print(); // Imprime a lista invertida
          }
            break;
          case 5: 
          {
            lista.incrementaEntidades(); // Incrementa entidades
            System.out.println("Entidades: " + lista.numeroEntidades());
          }
            break;
          case 6: 
          {
            lista.decrementaEntidades(); // Decrementa entidades
            System.out.println("Entidades: " + lista.numeroEntidades());
          }
            break;
          case 0:
            break; // Sai do menu
          default:
            System.out.println("Opção inválida");
        }
      } while (opcao != 0);

    } catch (Exception e) 
    {
      e.printStackTrace();
    }
    console.close(); // Fecha o scanner
  }
}
