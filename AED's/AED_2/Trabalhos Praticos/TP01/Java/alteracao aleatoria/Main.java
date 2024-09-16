/*
Crie um método ITERATIVO que recebe uma string, 
sorteia duas letras minúsculas aleatórias (código ASCII <= 'a' e >= 'z'), 
substitui todas as ocorrências da primeira letra na string pela segunda 
e retorna a string com as alterações efetuadas. Na saída padrão,
para cada linha de entrada, execute o método desenvolvido nesta questão e 
mostre a string retornada como uma linha de saída. 
Abaixo, observamos um exemplo de entrada supondo que 
para a primeira linha as letras sorteados foram o 'a' e o 'q'. Para a segunda linha, foram o 'e' e o 'k'.

EXEMPLO DE ENTRADA:                                     EXEMPLO DE SAÍDA:

o rato roeu a roupa do rei de roma             o rqto roeu q roupq do rei de romq

e qwe qwe qwe ewq ewq ewq                     k qwk qwk qwk kwq kwq kwq

FIM

A classe Random do Java gera números (ou letras)
aleatórios e o exemplo abaixo mostra uma letra minúscula na tela. Em especial, destacamos que:

i) \textit{seed} é a semente para geração de números aleatórios;
ii) nesta questão, por causa da correção automática, a *seed* será quatro;
iii) a disciplina de Estatística e Probabilidade faz uma discussão sobre ``aleatório''.

Random gerador = new Random();
gerador.setSeed(4);
System.out.println((char)('a' + (Math.abs(gerador.nextInt()) % 26)));
*/

import java.util.*;

class Main{

    public static void main(String[] args){
        Random rand = new Random();
        rand.setSeed(4);

        char randChar;
        char newChar;
        
        String input = new String();
        
        Scanner sc = new Scanner(System.in);
        
        while( !(input = sc.nextLine()).equals("FIM")){
            randChar = (char)('a' + Math.abs(rand.nextInt() % 26));
            newChar = (char)('a' + Math.abs(rand.nextInt() % 26));
            
            System.out.println(randString(input, randChar, newChar));
        }
        
        sc.close();
    }
    
    static String randString(String input, char randChar, char newChar){

        char[] array = input.toCharArray();

        for ( int i = 0; i < input.length(); i++ ){
            if ( array[i] == randChar )  array[i] = newChar;
        }

        return new String(array);
    }
}