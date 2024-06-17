/*
O Imperador Júlio César foi um dos principais nomes do Império Romano. 
Entre suas contribuições, temos um algoritmo de criptografia chamado Ciframento de César. 
Segundo os historiadores, César utilizava esse algoritmo para criptografar as mensagens que enviava aos seus generais durante as batalhas. 
A ideia básica é um simples deslocamento de caracteres.

Assim, por exemplo, se a chave utilizada para criptografar as mensagens for 3, 
todas as ocorrências do caractere a são substituídas pelo caractere d, as do b por e, e assim sucessivamente.

Crie um método ITERATIVO que recebe uma string como parâmetro e retorna outra contendo a entrada de forma cifrada. 
Neste exercício, suponha a chave de ciframento três. Na saída padrão, para cada linha de entrada, escreva uma linha com a mensagem criptografada.
*/

import java.util.*;

class Main{

   public static void main(String[] args){
    Scanner sc = new Scanner(System.in);
    String input= new String();

    while( !(input = sc.nextLine()).equals("FIM") ){
        System.out.println(cifra(input));
    }

    sc.close();
   }
   
   public static String cifra(String input){
    char[] array = input.toCharArray();

    for ( int i = 0; i < input.length(); i++ ) {
        if (array[i] <= 128 ) array[i] += 3;
    }

    return new String(array);
   }

}