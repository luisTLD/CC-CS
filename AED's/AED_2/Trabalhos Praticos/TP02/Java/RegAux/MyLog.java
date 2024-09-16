package RegAux;

import java.io.FileWriter;

public class MyLog {
    
    // Variaveis "globais"
    private static long startTime = 0;
    private static long endTime = 0;
    private static int totalComp = 0;
    private static int totalMove = 0;

    // Função para regular comparações
    static void countComp(int x){
        totalComp += x;
    }

     // Função para regular movimentações
    static void countMove(int x){
        totalMove += x;
    }

    // Função para começar o cronometro
    public static void startTimer() {
        startTime = System.currentTimeMillis();
    }

    // Função para encerrar o cronometro
    public static void endTimer() {
        endTime = System.currentTimeMillis();
    }

    // Função para calcular o tempo gasto
    static long getTime() {
        return endTime - startTime;
    }

    // Função para criar o txt contendo as informações de comparações e tempo
    public static void createLog(final String matricula) {
        try {
            FileWriter logArq = new FileWriter(matricula + "_quicksort.txt");
            logArq.write(matricula + "\t" + (endTime - startTime) + "\t" + totalComp + "\t" + totalMove + "\n");
            logArq.close();
        } 
        catch (Exception e) {
            e.printStackTrace();
            System.out.println("Erro ao criar txt");
        }
    }
}
