/*
Jogando Cartas Fora

Dada uma pilha de n cartas enumeradas de 1 até n com a carta 1 no topo e a carta n na base.  
A seguinte operação é ralizada enquanto tiver 2 ou mais cartas na pilha.

Jogue fora a carta do topo e mova a próxima carta (a que ficou no topo) para a base da pilha.

Sua tarefa é encontrar a sequência de cartas descartadas e a última carta remanescente.

Cada linha de entrada (com exceção da última) contém um número n ≤ 50. 
A última linha contém 0 e não deve ser processada. Cada número de entrada produz duas linhas de saída. 
A primeira linha apresenta a sequência de cartas descartadas e a segunda linha apresenta a carta remanescente.
Entrada

A entrada consiste em um número indeterminado de linhas contendo cada uma um valor de 1 até 50. 
A última linha contém o valor 0.
Saída

Para cada caso de teste, imprima duas linhas. 
A primeira linha apresenta a sequência de cartas descartadas, 
cada uma delas separadas por uma vírgula e um espaço. 
A segunda linha apresenta o número da carta que restou. 
Nenhuma linha tem espaços extras no início ou no final. 
Veja exemplo para conferir o formato esperado.

Exemplo de Entrada 	

7
19
10
6
0

Exemplo de Saída
Discarded cards: 1, 3, 5, 7, 4, 2
Remaining card: 6
Discarded cards: 1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 4, 8, 12, 16, 2, 10, 18, 14
Remaining card: 6
Discarded cards: 1, 3, 5, 7, 9, 2, 6, 10, 8
Remaining card: 4
Discarded cards: 1, 3, 5, 2, 6
Remaining card: 4  
*/


import java.io.IOException;
import java.util.Scanner;

class Celula{
    public int valor;
    public Celula prox;
    public Celula ant;
    
    public Celula(){
        this.prox = null;
        this.ant = null;
        this.valor = 0;
    }
    
    public Celula(int x){
        this.prox = null;
        this.ant = null;
        this.valor = x;
    }
}

class Lista{
    public Celula primeiro;
    public Celula ultimo;
    
    public Lista(){
        Celula aux = new Celula();
        primeiro = aux;
        ultimo = aux;
    }
    
    public void inserir(int x){
        Celula aux = new Celula(x);
        aux.ant = ultimo;
        ultimo.prox = aux;
        ultimo = aux;
    }
    
    public int remover(){
        int x = primeiro.prox.valor;
        primeiro = primeiro.prox;
        return x;
    }
}
    
public class Main {
 
    public static void main(String[] args) throws IOException {
        Lista cartas = new Lista();
       
        Scanner sc = new Scanner(System.in);
        
        int max = 0;
        
        while ( (max = sc.nextInt()) != 0 ){
        
            for ( int i = 1; i <= max; i++ ) cartas.inserir(i);
            
            System.out.print("Discarded cards: ");
            
            while ( cartas.primeiro.prox != cartas.ultimo ){
                System.out.print(cartas.remover() + " ");
                cartas.inserir(cartas.remover());
            }
            
            System.out.println("\nRemaining card: " + cartas.remover());
        }

        sc.close();
    }
}