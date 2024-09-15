import java.io.IOException;
import java.util.Scanner;

public class Main {
 
    public static void main(String[] args) throws IOException
    {
        Scanner sc = new Scanner(System.in);
 
        int qtd_felizNatal = Integer.parseInt(sc.nextLine());
        FelizNatal[] array_natal = new FelizNatal[qtd_felizNatal];
        for (int i = 0; i < qtd_felizNatal; i++)
        {
            String lingua = sc.nextLine();
            String traducao = sc.nextLine();
            FelizNatal aux = new FelizNatal(lingua, traducao);
            array_natal[i] = aux;
        }
        
        int qtd_pessoa = Integer.parseInt(sc.nextLine());
        Pessoa[] array_pessoa = new Pessoa[qtd_pessoa];
        for (int i = 0; i < qtd_pessoa; i++)
        {
            String nome = sc.nextLine();
            String lingua = sc.nextLine();
            Pessoa aux = new Pessoa(lingua, nome);
            array_pessoa[i] = aux;
        }
        
        for (int i = 0; i < qtd_pessoa; i++)
        {
            for (int j = 0; j < qtd_felizNatal; j++)
            {
                if (array_natal[j].lingua.equals(array_pessoa[i].lingua))
                {
                    System.out.println(array_pessoa[i].nome);
                    System.out.println(array_natal[j].traducao);
                    System.out.println();
                    break;
                }
            }
        }
        
        sc.close();
    }
 
}

class FelizNatal
{
    public String lingua;
    public String traducao;
    
    FelizNatal()
    {
        this.lingua = "";
        this.traducao = "";
    }
    
    FelizNatal(String l, String t)
    {
        this.lingua = l;
        this.traducao = t;
    }
}

class Pessoa
{
    public String lingua;
    public String nome;
    
    Pessoa()
    {
        this.lingua = "";
        this.nome = "";
    }
    
    Pessoa(String l, String n)
    {
        this.lingua = l;
        this.nome = n;
    }
}