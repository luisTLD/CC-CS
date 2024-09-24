import RegAux.*;

import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class Main{
    public static void main(String[] args){
        // Iniciar o cronometro
        MyLog.startTimer();

        Scanner sc = new Scanner(System.in);
        // String input = new String();

        // Ler o CSV, e passar tudo para uma List
        List<Personagem> personagens = ReadCsv.readAllFile("/tmp/characters.csv");
        
        // Criar uma List secundaria, apenas com os Personagens que serao utilizados no exercicio
        List<Personagem> using = new ArrayList<>();
        using = Personagem.mySubList(personagens, sc);

        // Realizar a questao expecifica e printar a saida
        using = SortList.quickSortHouse(using, 10);
        Personagem.printAll(using);       

        // Encerrar o cronometro e criar o log de saida
        MyLog.endTimer();
        MyLog.createLog("000000");
        sc.close();
    }

}

