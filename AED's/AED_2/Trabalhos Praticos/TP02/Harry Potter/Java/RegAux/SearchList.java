package RegAux;

import java.util.List;

public class SearchList {
        // Função para retornar o index do personagem com ID, ou -1 caso não exista
    static int linearIdSearch(final List<Personagem> personagens, String id){
        int index = -1;
        int length = personagens.size();

        for ( int i = 0; i < length; i++ ){
   
            if ((personagens.get(i).getId()).equals(id)){
                MyLog.countComp(i + 1);

                index = i;
                i = length;
            }
        }

        if ( index == -1 ) MyLog.countComp(length);

        return index;
    }
    
    // Função para retornar o index do personagem com NAME, ou -1 caso não exista
    static int linearNameSearch(final List<Personagem> personagens, String name){
        int index = -1;
        int length = personagens.size();

        for ( int i = 0; i < length; i++ ){

            if ((personagens.get(i).getName()).equals(name)){
                MyLog.countComp(i + 1);

                index = i;
                i = length;
            }
        }

        if ( index == -1 ) MyLog.countComp(length);

        return index;
    }
}
