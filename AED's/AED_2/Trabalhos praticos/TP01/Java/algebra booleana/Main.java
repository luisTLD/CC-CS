/*
Crie um método iterativo que recebe uma string contendo uma expressão booleana 
e o valor de suas entradas e retorna um booleano indicando se a expressão é verdadeira ou falsa. 
Cada string de entrada é composta por um número inteiro n indicando o número de entradas da expressão booleana corrente. 
Em seguida, a string contém n valores binários (um para cada entrada) e a expressão booleana. 
Na saída padrão, para cada linha de entrada, escreva uma linha de saída com SIM / NÃO indicando se a expressão corrente é verdadeira ou falsa.
*/

import java.util.Scanner;

class Main{
    public static void main(String[] args){
        Scanner sc = new Scanner(System.in);
        String input = new String();
        
        while ( !((input = sc.nextLine()).equals("0")) ){

            int max = input.charAt(0) - '0';

            int[] door = new int[max];

            for(int i = 1; i <= max; i++) door[i-1] = input.charAt(i*2) - '0';

            input = input.substring((max*2) + 1); 

            input = input.replace(",","");
            input = input.replace(" ", "");
            
            for ( int i = 0; i < max; i++ ) input = input.replace((char)('A' + i), (char)(door[i] + '0'));

            input = input.replace("and", "a");
            input = input.replace("not", "n");
            input = input.replace("or", "o");

            input = booleanString(input);
            System.out.println(input);

        }
        sc.close();
    }
    
    static String booleanString(String input){
        String auxBool = new String();
        int end = 0;
        int savePoint = 0;
        
        while ( (end = input.length() - 1) > 1 ){

            while ( input.charAt(end) != '(' ) end--;

            savePoint = end;

            char c = input.charAt(--end);

            while ( input.charAt(savePoint) != ')') savePoint++;
            
            auxBool = input.substring(end, ++savePoint);

            switch(c){
                case 'a':
                auxBool = auxBool.contains("0") ? "0" : "1";
                break;
                case 'o':
                auxBool = auxBool.contains("1") ? "1" : "0";
                break;
                case 'n':
                auxBool = auxBool.contains("0") ? "1" : "0";
                break;
            }

            input = input.substring(0, end) + auxBool + input.substring(savePoint);
            // System.out.println(input);
        }

        return input;
    }
}

