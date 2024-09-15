/*
Como de costume, neste ano Noel recebeu muitos pedidos de presentes.
Só que em função de alguns imprevistos, não terá como entregar todos os presentes pessoalmente neste ano.
Daí então decidiu utilizar o velho e bom correio tradicional, para alguns pedidos que podem ser entregues por carta.

Para esta tarefa, pediu ajuda ao elfo Evergreen Xadada,para que ele imprimisse etiquetas a todos os envelopes
que serão destinados a algumas destas crianças, cujo pedidopode ser entregue por carta. Cada uma destas etiquetas deverá
conter apenas o nome da criança e a saudação "Feliz Natal" no respectivo idioma desta criança.
Para auxiliar nesta tarefa, Noel disponibilizou uma tabelacom vários idiomas e o nome e o país de cada uma das crianças selecionadas,
de acordo com o exemplo abaixo. Você deve ajudar Evergreen fazendo um programa que imprima estas etiquetas.
Entrada

A entrada é composta por um único caso de teste. A primeira linha de entrada contém um inteiro N (1 < N < 100)
que indica a quantidade de traduções da palavra "Feliz Natal" existentes na entrada.
As próximas N * 2 linhas contém respectivamente o nome de uma língua seguido da tradução de "Feliz Natal" para esta língua.
Segue um inteiro M (1 < M < 100) que indica a quantidade de crianças que receberão as cartas.
As próximas M * 2 linhas conterão, respectivamente, o nome da criança e a língua nativa desta criança.

Obs.: É garantido que nenhuma tradução apareça repetida ou duplicada e os países de todas as crianças estejam presentes na relação dos países.
Saída

Seu programa deverá imprimir todas as etiquetas de acordo com a entrada,
conforme o exemplo abaixo, sempre com uma linha em branco após a impressão de cada uma das etiquetas, inclusive após a última etiqueta.
*/

import java.util.Scanner;

public class Main {

    public static void main(String[] args)
    {
        Scanner sc = new Scanner(System.in);

        // Ler a quantidade com nextLine e dar ParseInt, pois apenas com nextInt teria que usar um nextLine para limpar o '\n' do buffer
        int qtd_felizNatal = Integer.parseInt(sc.nextLine());

        // Array com lingua e sua respectiva traducao
        FelizNatal[] array_natal = new FelizNatal[qtd_felizNatal];
        for (int i = 0; i < qtd_felizNatal; i++) {
            String lingua = sc.nextLine();
            String traducao = sc.nextLine();
            FelizNatal aux = new FelizNatal(lingua, traducao);
            array_natal[i] = aux;
        }

        int qtd_pessoa = Integer.parseInt(sc.nextLine());
        for (int i = 0; i < qtd_pessoa; i++)
        {
            String nome = sc.nextLine();
            String lingua = sc.nextLine();

            // Apos ler a lingua, procurar ela no Array de lingua / traducao, e printar o nome e sua traducao
            for (int j = 0; j < qtd_felizNatal; j++)
            {
                if (lingua.equals(array_natal[j].lingua))
                {
                    System.out.println(nome);
                    System.out.println(array_natal[j].traducao);
                    System.out.println();
                }
            }
        }

        sc.close();
    }
}

class FelizNatal {
    public String lingua;
    public String traducao;

    FelizNatal() {
        this.lingua = "";
        this.traducao = "";
    }

    FelizNatal(String l, String t) {
        this.lingua = l;
        this.traducao = t;
    }
}