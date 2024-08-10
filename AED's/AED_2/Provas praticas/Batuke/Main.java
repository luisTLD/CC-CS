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

import java.util.Scanner;

class Main {

    public static int total;
    public static int percorridas;

    public static void main(String[] args){
        Scanner sc = new Scanner(System.in);
        total = 0;
        percorridas = 0;

        int max = 0;
        int valor = 1;
        max = sc.nextInt();

        int[][] matriz = new int[max][max];

        for ( int i = 0; i < max; i++ ){
            for ( int j = 0; j < max; j++ ){
                matriz[i][j] = valor++;
            }
        }

        int[] posi = new int[2];
        posi[0] = sc.nextInt();
        posi[1] = sc.nextInt();

        int move = 1;

        // Condição Gambiarra
        while ( move < max*3 ){
            if ( move > 1 ) move++;

            dir(posi, move, matriz, max); 
            baixo(posi, move, matriz, max);    
            move++;
            
            esq(posi, move, matriz, max);      
            cima(posi, move, matriz, max);
        }
        System.out.println("\n" + percorridas);
        
        sc.close();
    }


    static void dir(int[] posi, int move, int[][] matriz, int max){
        for ( int i = 0; i < move; i++ ){
            if ( locate(posi, max) ) System.out.print(matriz[posi[0]][posi[1]] + " ");
            posi[1] = posi[1] + 1;
        }
    }

    static void baixo(int[] posi, int move, int[][] matriz, int max){
        for ( int i = 0; i < move; i++ ){
            if ( locate(posi, max) ) System.out.print(matriz[posi[0]][posi[1]] + " ");
            posi[0] = posi[0] + 1;
        }
        
    }

    static void esq(int[] posi, int move, int[][] matriz, int max){
        for ( int i = 0; i < move; i++ ){
            if ( locate(posi, max) ) System.out.print(matriz[posi[0]][posi[1]] + " ");
            posi[1] = posi[1] - 1;
        }
        
    }

    static void cima(int[] posi, int move, int[][] matriz, int max){
        for ( int i = 0; i < move; i++ ){
            if ( locate(posi, max) ) System.out.print(matriz[posi[0]][posi[1]] + " ");
            posi[0] = posi[0] - 1;
        }
        
    }
    
    static boolean locate(int[] posi, int max){
        boolean resp = ( posi[0] >= 0 && posi[0] < max ) && ( posi[1] >= 0 && posi[1] < max );
        total++;
        if ( resp ) percorridas = total;
    
        return resp;
    }

}