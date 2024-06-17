/*
Crie um método recursivo que recebe uma string e retorna true se a mesma é composta somente por vogais.
Crie outro método recursivo que recebe uma string e retorna true se a mesma é composta somente por consoantes. 
Crie um terceiro método recursivo que recebe uma string e retorna true se a mesma corresponde a um número inteiro. 
Crie um quarto método recursivo que recebe uma string e retorna true se a mesma corresponde a um número real. 
Na saída padrão, para cada linha de entrada, escreva outra de saída da seguinte forma X1 X2 X3 X4 onde cada Xi é um booleano indicando 
se a é entrada é: composta somente por vogais (X1); composta somente somente por consoantes (X2); 
um número inteiro (X3); um número real (X4). Se Xi for verdadeiro, seu valor será SIM, caso contrário, NÃO.
*/

import java.util.*;

class Main {

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        String input = new String();
        int tam = 0;
        int line = 0;

        char[] allCons = {
                'B', 'b', 'C', 'c', 'D', 'd', 'F', 'f', 'G', 'g',
                'H', 'h', 'J', 'j', 'K', 'k', 'L', 'l', 'M', 'm',
                'N', 'n', 'P', 'p', 'Q', 'q', 'R', 'r', 'S', 's',
                'T', 't', 'V', 'v', 'W', 'w', 'X', 'x', 'Y', 'y', 'Z', 'z'
        };

        while (!(input = sc.nextLine()).equals("FIM")) {
            if (line == 1) {
                System.out.println();
            }
            line = 1;

            tam = input.length();

            System.out.print(verVog(input, tam, 0) + ' ');
            System.out.print(verCons(input, tam, allCons, 0) + ' ');
            System.out.print(verInt(input, tam, 0) + ' ');
            System.out.print(verReal(input, tam, 0, 0));

        }

        sc.close();
    }

    static String verVog(String input, int tam, int index) {
        if (index == tam) {
            return "SIM";
        }

        if (input.charAt(index) != 'a' &&
                input.charAt(index) != 'e' &&
                input.charAt(index) != 'i' &&
                input.charAt(index) != 'o' &&
                input.charAt(index) != 'u') {
            return "NAO";
        }

        return verVog(input, tam, index + 1);
    }

    static String verCons(String input, int tam, char[] allCons, int index) {
        if (index == tam) {
            return "SIM";
        }

        boolean ver = false;
        for ( int i = 0; i < allCons.length; i++ ) {
            if (input.charAt(index) == allCons[i]) {
                ver = true;
                break;
            }
        }

        if (!ver) return "NAO";

        return verCons(input, tam, allCons, index + 1);
    }

    static String verInt(String input, int tam, int index) {
        if (index == tam) return "SIM";

        if (input.charAt(index) < '1' || input.charAt(index) > '9') return "NAO";

        return verInt(input, tam, index + 1);
    }

    static String verReal(String input, int tam, int index, int dotCount) {
        if (index == tam)  return "SIM";

        if (input.charAt(index) == '.' || input.charAt(index) == ',') {
            dotCount++;
            if (dotCount > 1) {
                return "NAO";
            }
        } else if (input.charAt(index) < '0' || input.charAt(index) > '9') return "NAO";

        return verReal(input, tam, index + 1, dotCount);
    }

}
