package RegAux;

import java.util.ArrayList;
import java.util.List;

public class SortList {
    // Função para ordenar a lista por nome, utilizando metodo SelectionSort, int totalSort = N elementos ordenados
    static List<Personagem> selectionSortName(final List<Personagem> personagens, int totalSort){
        List<Personagem> auxCopy = new ArrayList<>(personagens);
        int max = auxCopy.size();

        for ( int i = 0; i < totalSort; i++ ){
            int lower = i;

            for ( int j = i + 1; j < max; j++ ){
                if (compareName(auxCopy.get(lower), auxCopy.get(j)) > 0 ) lower = j;
            }

            swap(auxCopy, i, lower);
        }

        return auxCopy.subList(0, totalSort);
    }


    // Função para ordenar a lista por DateOfBirth, utilizando InsertionSort
    static List<Personagem> insertionSortDateOfBirth(final List<Personagem> personagens, int totalSort){
        List<Personagem> auxCopy = new ArrayList<>(personagens);
        Personagem temp = new Personagem();
        int max = auxCopy.size();
        int j = 0;
        int move = 0;

        for ( int i = 1; i < max; i++ ){
            temp = auxCopy.get(i);
            if ( i > totalSort ) j = totalSort;
            else j = i - 1;
            
            while ( (j >= 0) && (compareDateOfBirth(auxCopy.get(j), temp) > 0)){
                auxCopy.set(j + 1, auxCopy.get(j));
                move++;
                j--;
            }

            auxCopy.set(j + 1, temp);
        }
        MyLog.countMove(max - 1 + move);
        MyLog.countComp(max - 1);

        return auxCopy.subList(0, totalSort);
    }

    // Função para ordenar a lista por House, utilizando QuickSort
    public static List<Personagem> quickSortHouse(List<Personagem> personagens, int totalSort) {
        List<Personagem> auxCopy = new ArrayList<>(personagens);

        quickSortCall(auxCopy, 0, personagens.size() - 1, totalSort);

        return auxCopy.subList(0, totalSort);
    }

    static void quickSortCall(List<Personagem> personagens, int left, int right, int totalSort) {
        int i = left;
        int j = right;
        Personagem piv = personagens.get((left + right) / 2);

        while (j >= i) {
            while (compareHouse(personagens.get(i), piv) < 0) i++;
            while (compareHouse(piv, personagens.get(j)) < 0) j--; 

            if (j >= i) {
                swap(personagens, i, j);
                i++;
                j--;
            }

            if (left < j) quickSortCall(personagens, left, j, totalSort);
            if (totalSort > i) quickSortCall(personagens, i, right, totalSort);
        }
    }


    // Função para ordenar a listar por YearOfBirth, utilizandou CountingSort
    static List<Personagem> countingSortYearOfBirth(final List<Personagem> personagens){
        int length = personagens.size();

        // Maior elemento da List
        int maxYear = 0;
        for ( Personagem pessoa : personagens ){
            if ( pessoa.getYearOfBirth() > maxYear ) maxYear = pessoa.getYearOfBirth();
        }
        
        // Inicializar o array de contagem
        int[] count = new int[maxYear + 1];

        // Contar as ocorrências de cada ano de nascimento
        for (Personagem pessoa : personagens){
            count[pessoa.getYearOfBirth()]++;
        }
      
        // Atualizar o array de contagem para conter o número de elementos menores ou iguais a i
        for (int i = 1; i <= maxYear; i++){
            count[i] += count[i - 1];
        }

        // Construir a lista ordenada
        List<Personagem> auxCopy = new ArrayList<>(personagens);
        for (int i = length - 1; i >= 0; i--) {
            int yearOfBirth = personagens.get(i).getYearOfBirth();
            auxCopy.set(count[yearOfBirth] - 1, personagens.get(i));

            count[yearOfBirth]--;
        }

        // Passar pela Lista novamente para desempatar por nome onde o Year estava igual
        List<Personagem> newSortSubList = new ArrayList<>();
        int index = 0;
        int atualYear = auxCopy.get(0).getYearOfBirth();
        boolean reSort = false;

        // Procurar intervalos com Year repetido, reordendar esses intervalos e voltar para Lista Principal
        for (int i = 1; i < length; i++) {           
            if ( auxCopy.get(i).getYearOfBirth() == atualYear ) {
                if ( !reSort ) {
                    index = i - 1; 
                    reSort = true;
                }
            }
            
            // Pegar o intervalo, reordenar e adicionar
            
            if ( reSort && (auxCopy.get(i).getYearOfBirth() != atualYear)) {
                newSortSubList = auxCopy.subList(index, i);
                newSortSubList = selectionSortName(newSortSubList, newSortSubList.size());
                
                for (int j = index; j < i; j++) {
                    auxCopy.set(j, newSortSubList.get(j - index));
                }

                reSort = false;
            }

            atualYear = auxCopy.get(i).getYearOfBirth();
        }

        // Tratar caso tenha uma sequencia repetida ate o ultimo elemento
        
        if ( reSort ){
            newSortSubList = auxCopy.subList(index, length);
            newSortSubList = selectionSortName(newSortSubList, newSortSubList.size());
        
            for (int j = index; j < length; j++) {
                auxCopy.set(j, newSortSubList.get(j - index));
            }
        }

        return auxCopy;
    }


    // Função para ordenar a lista por HairColor, utilizando HeapSort
    static List<Personagem> heapSortHairColor(final List<Personagem> personagens){
        List<Personagem> auxCopy = new ArrayList<>(personagens);
        int length = auxCopy.size();

        for ( int max = 1; max < length; max++ ){

            // Construir Heap, se o filho for maior que o pai, troca e continua verificando com o proximo pai
            for ( int i = max; max > 0 && compareHairColor(auxCopy.get(i), auxCopy.get((i - 1) / 2)) > 0; i = (i - 1) / 2){
                swap(auxCopy, i, (i - 1) / 2);
            }
        }

        // Ordenação, taca o primiero pro final, e constroi o Heap novamente, ate ordenar
        int endIndex = length - 1;
        while ( endIndex > 0 ){
            swap(auxCopy, 0, endIndex);
            endIndex--;

            // Reconstruir o Heap
            int aux = 0; 

            // Entrar em Loop enquando aux tiver filho
            while((aux * 2) + 1 <= endIndex){
                // Obter o maior filho de aux
                int son = 0;

                // Ver se so tem um filho, ou, comparar os 2 para retornar o maior
                if ( (2 * aux) + 1 == endIndex ) son = endIndex;
                else if ( compareHairColor(auxCopy.get((2 * aux) + 1), auxCopy.get((2 * aux) + 2)) > 0 ) son = ((2 * aux) + 1);
                else son = ((2 * aux) + 2);

                // Verificar se o filho é maior que o novo pai, para fazer a troca
                if ( compareHairColor(auxCopy.get(son), auxCopy.get(aux)) > 0 ){
                    swap(auxCopy, son, aux);

                    // aux ser igual a son, para que verifique se agora ele é filho de algum novo pai menor que ele
                    aux = son;
                } else aux = endIndex; // Sair do loop
            }
        }

        return auxCopy;
    }


    // Função para chamar o MergeSort
    static List<Personagem> mergeSortActorName(List<Personagem> personagens){
        List<Personagem> auxCopy = new ArrayList<>(personagens);
    
        mergeSortActorNameCall(auxCopy, 0, auxCopy.size() - 1);
    
        return auxCopy;
    }

    // Função para ordenar ActorName utilizando MergeSort
    static private void mergeSortActorNameCall(final List<Personagem> personagens, int left, int right){
        if ( left < right ){
            int middle = (left + right) / 2;

            mergeSortActorNameCall(personagens, left, middle);
            mergeSortActorNameCall(personagens, middle + 1, right);
            mergeSortActorNameAction(personagens, left, middle, right);
        }
    }

    // Fazer o merge entre os arrays
    static private void mergeSortActorNameAction(List<Personagem> personagens, int left, int middle, int right) {
        int nLeft = (middle - left) + 1;
        int nRight = right - middle;

        Personagem[] arrayLeft = new Personagem[nLeft + 1];
        Personagem[] arrayRight = new Personagem[nRight + 1];

        for (int i = 0; i < nLeft; i++) {
            arrayLeft[i] = personagens.get(left + i);
        }
        MyLog.countMove(nLeft);

        for (int j = 0; j < nRight; j++) {
            arrayRight[j] = personagens.get(middle + j + 1);
        }
        MyLog.countMove(nRight);

        // Sentinela
        arrayLeft[nLeft] = new Personagem();
        arrayRight[nRight] = new Personagem();

        int i = 0;
        int j = 0;

        for (int k = left; k <= right; k++) {
            if ((arrayRight[j].getActorName() == null || (arrayLeft[i].getActorName() != null) && compareActorName(arrayRight[j], arrayLeft[i]) >= 0)) {
                personagens.set(k, arrayLeft[i]);

                i++;
            } else {
                personagens.set(k, arrayRight[j]);
                
                j++;
            }
        }
        MyLog.countMove(j + i);
    }



    // Função para inverter 2 posições
    static private void swap(List<Personagem> list, int i, int j) {
        Personagem aux = list.get(i);
        list.set(i, list.get(j));
        list.set(j, aux);

        MyLog.countMove(3);
    }


// ------------------------------------------------------------------------------------------------------------------------------------

                            // Funções para comparação e desempatar em Name


    // Função que compara nome de Personagem x e y, retorna positivo se a x for "maior"...
    static private int compareName(Personagem x, Personagem y){
        MyLog.countComp(1);

        return x.getName().compareTo(y.getName());
    }

    // Função que compara DateOfBirth de Personagem x e y, retorna positivo se a x for "maior"... e desempatar pelo nome
    static private int compareDateOfBirth(Personagem x, Personagem y){
        MyLog.countComp(1);

        int aux = x.getDateOfBirth().compareTo(y.getDateOfBirth());

        if ( aux == 0 ) aux = compareName(x, y);

        return aux;
    }

    // Função que compara HairColor, retorna positivo se x for "maior", e desempata em name
    static private int compareHairColor(Personagem x, Personagem y){
        MyLog.countComp(1);

        int aux = x.getHairColor().compareTo(y.getHairColor());

        if ( aux == 0 ) aux = compareName(x, y);

        return aux;
    }

    // Função que compara ActorName, desempata em Name
    static private int compareActorName(Personagem x, Personagem y){
        MyLog.countComp(1);

        int aux = x.getActorName().compareTo(y.getActorName());

        if ( aux == 0 ) aux = compareName(x, y);

        return aux;
    }

    // Função que compara House e desempata em Name
    static int compareHouse(Personagem x, Personagem y) {
        MyLog.countComp(1);

        int aux = x.getHouse().compareTo(y.getHouse());

        if ( aux == 0 ) aux = compareName(x, y);

        return aux;
    }

}
