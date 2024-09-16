/*
A Cuca está com um baita problema. Todas as N > 0 crianças que ela raptou
estão acordadas e chorando. As crianças estão cada uma em um quarto, e
os quartos são numerados de 1 a N, sendo 1 o quarto mais próximo da Cuca. A Cuca vai
visitar cada quarto, um por vez, na ordem de 1 a N, e ela leva exatamente um minuto
para entrar em um quarto, enfeitiçar a criança para que volte a dormir,
e sair do quarto. Portanto, a Cuca precisará de exatos N minutos para que todas as crianças
estejam dormindo novamente.

Todas as crianças raptadas têm idades diferentes. Quando mais de uma
criança está chorando ao mesmo tempo, o choro que mais irrita a Cuca é
sempre o da criança mais nova. Assim, a cada minuto desde que a Cuca
começa sua tarefa, há uma única criança, dentre todas as que estão
acordadas, que é a que mais está irritando a Cuca, até que a Cuca
consiga concluir a tarefa de pôr todas as crianças para dormir.

Por exemplo, considere que N = 3, que as crianças nos quartos
1, 2,
e 3 são, respectivamente, Alice, Bob, e
Clara, e que Alice é a mais nova e Bob é o mais velho. Assim, as
crianças que mais estão irritando a Cuca nos minutos 1, 2, e
3 são, respectivamente, Alice, Clara, e
Clara novamente. Note que no minuto 2,
Bob e Clara estão acordados, mas Clara é mais nova que Bob, por isso
irrita mais a Cuca. No minuto 3,
somente Clara está acordada e, portanto, continua sendo a criança que
mais está irritando a Cuca.

Entrada

A primeira linha da entrada consiste unicamente no inteiro N (1 ≤ N ≤ 5 ⋅ 104), o
número de crianças raptadas pela Cuca.

A segunda linha consiste nos nomes das N crianças, de modo que o I-ésimo (1 ≤ I ≤ N) nome é o nome da
criança no quarto I. Todos os
nomes são formados apenas por no mínimo 1 e no máximo 8 letras do alfabeto latino, sem caracteres
especiais ou diacríticos, sendo a primeira letra sempre maiúscula, e as
demais minúsculas. Nomes consecutivos são separados entre si por um
espaço em branco. É garantido que os nomes das N crianças são todos distintos.

A terceira linha consiste nos mesmos N nomes da segunda linha, mas agora
fornecidos em ordem crescente das idades das crianças a que
correspondem.

Imprima uma linha consistindo em N nomes de crianças, de modo que o
I-ésimo nome (1 ≤ I ≤ N) corresponda à
criança que mais irrita a Cuca no minuto I desde que se inicia a tarefa de
pôr todas as crianças para dormir. Nomes consecutivos devem vir
separados por um espaço em branco, sem que haja um espaço em branco ao
final da linha.


Samples Input	

5
Alice Bob Clara Dora Eve
Bob Clara Eve Dora Alice

Samples Output

Bob Bob Clara Eve Eve

Tempo limite base: 1 segundos | Limite de memória: 250 MB 
*/

import java.io.IOException;
import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;
 

public class Main {
 
    public static void main(String[] args) throws IOException {
        Scanner sc = new Scanner(System.in);

        int total = sc.nextInt();
        sc.nextLine();

        String[] dormir = sc.nextLine().split(" ");
        String[] irritando = sc.nextLine().split(" ");

        Map<String, Integer> mapa = new HashMap<>();

        for (int i = 0; i < total; i++)  mapa.put(irritando[i], i);

        int index = 0;
        StringBuilder saida = new StringBuilder();
        saida.append(irritando[index]);

        irritando[mapa.get(dormir[0])] = "0";
        for ( int i = 1; i < total; i++ ){
            while ( irritando[index] == "0" ) index++;
            saida.append(" ").append(irritando[index]);

            irritando[mapa.get(dormir[i])] = "0";
        }

        System.out.println(saida);
 
        sc.close();
    }
}