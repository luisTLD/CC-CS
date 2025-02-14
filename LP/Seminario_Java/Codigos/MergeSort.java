import java.util.Random;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.TimeUnit;

class MergeSort {
    private int[] array;
    private int[] tempMergeArray;
    private ExecutorService executor;

    public MergeSort(int[] array) {
        this.array = array;
        this.tempMergeArray = new int[array.length];
        this.executor = Executors.newFixedThreadPool(Runtime.getRuntime().availableProcessors()); // Número de threads igual ao número de núcleos do processador
    }

    // Método principal para ordenar o array
    public void mergeSort(int left, int right) {
        if (left < right) {
            int middle = (left + right) / 2;

            // Criar duas threads para ordenar as duas metades
            executor.submit(() -> mergeSort(left, middle));
            executor.submit(() -> mergeSort(middle + 1, right));

            // Mesclar as duas metades
            merge(left, middle, right);
        }
    }

    // Método para mesclar duas subpartes do array
    private void merge(int left, int middle, int right) {
        for (int i = left; i <= right; i++) {
            tempMergeArray[i] = array[i];
        }

        int i = left;
        int j = middle + 1;
        int k = left;

        while (i <= middle && j <= right) {
            if (tempMergeArray[i] <= tempMergeArray[j]) {
                array[k] = tempMergeArray[i];
                i++;
            } else {
                array[k] = tempMergeArray[j];
                j++;
            }
            k++;
        }

        // Copiar os elementos restantes da metade esquerda, se houver
        while (i <= middle) {
            array[k] = tempMergeArray[i];
            k++;
            i++;
        }
    }

    public void shutdown() {
        executor.shutdown();
        try {
            // Esperar até que todas as tarefas sejam concluídas
            if (!executor.awaitTermination(60, TimeUnit.SECONDS)) {
                executor.shutdownNow();
            }
        } catch (InterruptedException e) {
            executor.shutdownNow();
        }
    }

    // Método estático para iniciar o merge sort
    public static void sort(int[] array, boolean useThreads) {
        MergeSort mergeSort = new MergeSort(array);
        if (useThreads) {
            mergeSort.mergeSort(0, array.length - 1);
            mergeSort.shutdown();
        } else {
            mergeSort.mergeSortNoThreads(0, array.length - 1);
        }
    }

    // Método para ordenar sem threads
    public void mergeSortNoThreads(int left, int right) {
        if (left < right) {
            int middle = (left + right) / 2;
            mergeSortNoThreads(left, middle);
            mergeSortNoThreads(middle + 1, right);
            merge(left, middle, right);
        }
    }

    // Método principal para teste
    public static void main(String[] args) {
        Random rand = new Random();
        int size = 1000000; // Tamanho do array para teste (1 milhão de elementos)
        int[] arrayWithThreads = new int[size];
        int[] arrayWithoutThreads = new int[size];

        // Preencher os arrays com valores aleatórios
        for (int i = 0; i < size; i++) {
            int value = rand.nextInt(1000); // Valores aleatórios entre 0 e 999
            arrayWithThreads[i] = value;
            arrayWithoutThreads[i] = value;
        }

        // Testar o Merge Sort com threads
        long startTimeWithThreads = System.nanoTime();
        sort(arrayWithThreads, true);
        long endTimeWithThreads = System.nanoTime();
        long durationWithThreads = endTimeWithThreads - startTimeWithThreads;

        // Testar o Merge Sort sem threads
        long startTimeWithoutThreads = System.nanoTime();
        sort(arrayWithoutThreads, false);
        long endTimeWithoutThreads = System.nanoTime();
        long durationWithoutThreads = endTimeWithoutThreads - startTimeWithoutThreads;

        // Mostrar resultados
        System.out.println("Tempo de execução com threads: " + durationWithThreads + " nanosegundos");
        System.out.println("Tempo de execução sem threads: " + durationWithoutThreads + " nanosegundos");
    }
}
