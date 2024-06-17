/*
Crie um método recursivo que recebe uma string como parâmetro e retorna true se essa é um Palíndromo.

Na saída padrão, para cada linha de entrada, escreva uma linha de saída com SIM/NÃO 
indicando se a linha é um palíndromo. Destaca-se que uma linha de entrada pode ter caracteres não letras.
*/

import java.util.*;

class Main {

    public static void main(String[] args){
        Scanner sc = new Scanner(System.in);

        String input = new String();

        while ( !(input = sc.nextLine()).equals("FIM")){
            System.out.println(Ver(input, 0, input.length() - 1));
        }

        sc.close();
    }

    static String Ver(String palavra, int inicio, int tam) {
        if (inicio >= tam) return "SIM";
        else if (palavra.charAt(inicio) != palavra.charAt(tam)) return "NAO";
        
        return Ver(palavra, inicio + 1, tam - 1);
    }

}
