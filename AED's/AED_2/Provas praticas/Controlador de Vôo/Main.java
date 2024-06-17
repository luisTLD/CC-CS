/*
O aeroporto de Congonhas recebe todos os dias uma média de 600 pousos e decolagens, 
ou cerca de 36 por hora. No último ano, foram exatamente 223.989 movimentos aéreos. 
Para organizar todo o fluxo de aviões que chegam a Congonhas e saem de lá, a torre de controle funciona o tempo inteiro com nível máximo de atenção. 
Para descartar qualquer possibilidade de erro humano o chefe do controle de tráfego aéreo de Congonhas contratou você 
para desenvolver um programa que organize automaticamente o fluxo de aviões no campo de pouso.

Para isso, basta seguir o seguinte protocolo, os aviões que veem do lado Oeste da pista têm maior prioridade de serem colocados na fila, 
pois são aqueles que estão mais próximo do localizador (início da pista). Já os aviões que estão se aproximando pelo lado Norte e Sul, 
devem ser inseridos na fila 1 por vez, ou seja, insere-se 1 avião do lado Norte e em seguida 1 avião do lado Sul. Por último, 
insere-se o próximo avião que esteja se aproximando ao lado leste da pista.

Entrada
A entrada é composta por um número inteiro P, representando o ponto cardeal do avião que entrou no campo da pista (-4 <= P <= -1), 
onde (-4 representa o lado leste, -3 o lado norte, -2 lado sul e -1 lado oeste) . Em seguida é realizada a entrada dos respectivos aviões, 
compostos de um identificador começando com a letra “A” seguida de um número inteiro I (1 <= I <= 1000). 
A qualquer momento é permitido trocar o ponto cardeal, e inserir novas aeronaves, repetidamente até que o controlador finalize a sessão com o dígito 0.

Saída
A saída é composta de uma linha contendo as aeronaves enfileiradas pela ordem do protocolo estabelecido pelo aeroporto.
*/

import java.util.*;
import java.io.*;

class Main{
    public static void main(String[] args){
        Scanner sc = new Scanner(System.in);

        List<String> oeste = new ArrayList<>();
        List<String> sul = new ArrayList<>();
        List<String> norte = new ArrayList<>();
        List<String> leste = new ArrayList<>();

        int[] posi = new int[4];
        // 0 -> oeste; 1 -> sul; 2 -> norte; 3 -> leste
        String aux = new String();
        String caso = new String();
        

        // Adicionar o Voo em seu respectivo Array
        aux = sc.nextLine();
        caso = aux;
        while ( aux.equals("0") == false ){
            aux = sc.nextLine();
            if ( aux.equals("0") == true ) break;
            if ( aux.charAt(0) == '-' ){
               caso = aux; 
            } else  {
                switch (caso){
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
        for ( int i = 0; i < bigger; i++ ){
            if ( existe(i, oeste) ) merge.add(oeste.get(i));
            if ( existe(i, norte) ) merge.add(norte.get(i));
            if ( existe(i, sul) ) merge.add(sul.get(i));
            if ( existe(i, leste) ) merge.add(leste.get(i));
        }

        // Printar a Saida
        for ( int i = 0; i < merge.size(); i++ ){
            System.out.print(merge.get(i) + " ");
        }

        sc.close();
    }

    // Verificar se o Indice existe no array
    public static boolean existe(int index, List<String> aux){
        boolean resp = true;

        if ( aux.size() <= index ) resp = false;

        return resp;
    }

    // Obter maior lista para controlar o tamanho do loop de merge
    public static int maiorLista(List<String> lista1, List<String> lista2, List<String> lista3, List<String> lista4){
        int maior = lista1.size();

        if ( maior < lista2.size() ) maior = lista2.size();
        if ( maior < lista3.size() ) maior = lista3.size();
        if ( maior < lista4.size() ) maior = lista4.size();

        return maior;
    }

}

// -4 representa o lado leste, -3 o lado norte, -2 lado sul e -1 lado oeste