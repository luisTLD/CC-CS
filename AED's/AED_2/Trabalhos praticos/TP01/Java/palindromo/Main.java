/*
Crie um método iterativo que recebe uma string como parâmetro e retorna true se essa é um Palíndromo.

Na saída padrão, para cada linha de entrada, escreva uma linha de saída com SIM/NÃO 
indicando se a linha é um palíndromo. Destaca-se que uma linha de entrada pode ter caracteres não letras.
*/

import java.util.Scanner;

class Main {

    public static void main(String args[]) {

        String input;
        Scanner sc = new Scanner(System.in);

        while (!(input = sc.nextLine()).equals("FIM")) {
            System.out.println(Ver(input));
        }

        sc.close();
    }

    public static String Ver(String input) {

        int max = input.length();

        for (int i = 0, j = max - 1; i < max / 2; i++, j--) {
            if (input.charAt(i) != input.charAt(j)) return "NAO";
        }

        return "SIM";

    }

}
