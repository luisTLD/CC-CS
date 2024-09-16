/*
Crie um método iterativo que recebe uma string e retorna true se a mesma é composta somente por vogais.
Crie outro método iterativo que recebe uma string e retorna true se a mesma é composta somente por consoantes. 
Crie um terceiro método iterativo que recebe uma string e retorna true se a mesma corresponde a um número inteiro. 
Crie um quarto método iterativo que recebe uma string e retorna true se a mesma corresponde a um número real. 
Na saída padrão, para cada linha de entrada, escreva outra de saída da seguinte forma X1 X2 X3 X4 onde cada Xi é um booleano indicando 
se a é entrada é: composta somente por vogais (X1); composta somente somente por consoantes (X2); 
um número inteiro (X3); um número real (X4). Se Xi for verdadeiro, seu valor será SIM, caso contrário, NÃO.
*/

import java.util.*;

class Main{

    public static void main(String[] args){
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
        

        while( !(input = sc.nextLine()).equals("FIM")){
            if ( line == 1 ){
                System.out.println();
            }
            line = 1;

            tam = input.length();

            System.out.print(verVog(input, tam) + " ");
            System.out.print(verCons(input, tam, allCons) + " ");
            System.out.print(verInt(input, tam) + " ");
            System.out.print(verReal(input, tam));

        }

        sc.close();
    }

    static String verVog(String input, int tam){
        for ( int i = 0; i < tam; i++ ){
            if( input.charAt(i) != 'a' &&
                input.charAt(i) != 'e' && 
                input.charAt(i) != 'i' && 
                input.charAt(i) != 'o' && 
                input.charAt(i) != 'u' ){

                return "NAO";
            }
        }
        return "SIM";
    }

    static String verCons(String input, int tam, char[] allCons){
        boolean ver;
        for ( int i = 0; i < tam; i++ ){
            ver = false;
            for ( int j = 0; j < allCons.length; j++ ){
                if ( input.charAt(i) == allCons[j] ) ver = true;
            }
            if ( ver == false ) return "NAO";
        }
        return "SIM";
    }

    static String verInt(String input, int tam){
        for ( int i = 0; i < tam; i++ ){
            if( input.charAt(i) < '0' || input.charAt(i) > '9' ) return "NAO";
        }
        return "SIM";
    }

    static String verReal(String input, int tam){
        int dot = 0;
        for ( int i = 0; i < tam; i++ ){
            if ( input.charAt(i) == '.' || input.charAt(i) == ',') { 
                dot++;
                if ( dot > 1 ) return "NAO";
            }
            else if( input.charAt(i) < '0' || input.charAt(i) > '9' ) return "NAO";
        }
        return "SIM";
    }

}