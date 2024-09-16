/*
Batuke é um cachorro com comportamento repetitivo que tem uma rotina particular quando sai para caminhar na sua vizinhança.
A vizinhança também é de certa forma particular: uma matriz N x N que batuke percorre rotineiramente em espiral. 
Batuke inicia percorrendo: 1 célula à direita, uma abaixo, 
seguida por duas à esquerda, duas acima, então 3 à direita, 3 para baixo, então 4, e assim por diante.

Lucas (o dono de Batuke), leva Batuke de carro para a célula inicial 
e o cão sempre segue sua rotina de corrida pelas células de sua vizinhança.

Por exemplo, se a vizinhança tem tamanho N = 4, as células são enumeradas como segue:

e o percurso feito por Batuke, iniciando na célula 1,1 
(célula superior esquerda é 0,0) é: 6,7,11,10,9,5,1,2,3,4,8,12,16,15,14,13

Neste caso, a rotina de Batuke o faz caminhar por 16 células no total.

Mas Batuke não compreende nada sobre fronteiras e ele sempre faz sua rotina 
(mesmo se ele tem que caminhar por diversas células a mais), para atravessar todas as células da vizinhança. Se a célula inicial for 2,2 por exemplo, 
a travessia em espiral (apenas as células da vizinhança são mostradas) é: 11,12,16,15,14,10,6,7,8,13,9,5,1,2,3,4. Neste caso, Batuke caminha por 24 células no total. 
Lucas sabe que você está estudando Computação e ele pediu a você um programa para resolver este problema: dado a vizinhança de N linhas por N colunas e uma célula inicial, 
você deverá mostrar o percurso em espiral e o total células percorridas.

Entrada
A entrada consiste em três números inteiros: N (2 < N ≤ 10), 
F e C. N é o número de linhas na vizinhança 
(células enumeradas em 1..NxN, por linhas, da esquerda para a direita). 
F e C indica linha e coluna aonde Batuke inicia o seu percurso.

Saída
A saída consiste em 2 linhas. 
A primeira linha contém uma lista contendo as células da vizinhança, 
ordenadas pelo percurso que Batuke e separadas por um espaço em branco. 
A segunda linha mostra o número total de células percorridas por Batuke.  
*/

import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class Main
{
 
    public static void main(String[] args)
    {
 
        Scanner sc = new Scanner(System.in);

        List<String> oeste = new ArrayList<>();
        List<String> sul = new ArrayList<>();
        List<String> norte = new ArrayList<>();
        List<String> leste = new ArrayList<>();

        // 0 -> oeste; 1 -> sul; 2 -> norte; 3 -> leste
        String aux = new String();
        String caso = new String();
        

        // Adicionar o Voo em seu respectivo Array
        aux = sc.nextLine();
        caso = aux;
        while (!aux.equals("0"))
        {
            aux = sc.nextLine();
            if (aux.equals("0")) break;
            if (aux.charAt(0) == '-') caso = aux;
            else
            {
                switch (caso)
                {
                    case "-1":
                        oeste.add(aux);
                    break;
                    case "-2":
                        sul.add(aux);
                    break;
                    case "-3":
                        norte.add(aux);
                    break;
                    case "-4":
                        leste.add(aux);
                    break;
                }
            }

        }

        List<String> merge = new ArrayList<>();
        // -1, -3, -2, -4

        // Fazer um merge dos arrays para o array de sainda
        // Apenas adicionar caso aquele indice existir no array
        int bigger = maiorLista(oeste, norte, sul, leste);
        for (int i = 0; i < bigger; i++)
        {
            if (existe(i, oeste)) merge.add(oeste.get(i));
            if (existe(i, norte)) merge.add(norte.get(i));
            if (existe(i, sul)) merge.add(sul.get(i));
            if (existe(i, leste)) merge.add(leste.get(i));
        }

        // Printar a Saida formatada para dar 100%
        for (int i = 0; i < merge.size(); i++)
        {
            System.out.print(merge.get(i));
            // Se for o ultimo print, nao printar um espaco a +
            if (i != (merge.size() - 1)) System.out.print(" ");
        }
        
         System.out.println();

        sc.close();
    }

    // Verificar se o Indice existe no array
    public static boolean existe(int index, List<String> aux)
    {
        boolean resp = true;
        if (aux.size() <= index) resp = false;
        return resp;
    }

    // Obter maior lista para controlar o tamanho do loop de merge
    public static int maiorLista(List<String> lista1, List<String> lista2, List<String> lista3, List<String> lista4){
        int maior = lista1.size();

        if (maior < lista2.size()) maior = lista2.size();
        if (maior < lista3.size()) maior = lista3.size();
        if (maior < lista4.size()) maior = lista4.size();

        return maior;
    }
 
}