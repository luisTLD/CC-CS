package RegAux;

import java.io.BufferedReader;
import java.io.FileReader;
import java.util.ArrayList;
import java.util.List;

public class ReadCsv{
    public static List<Personagem> readAllFile(final String fileToRead){
        List<Personagem> personagens = new ArrayList<>();
        
        try {
            BufferedReader br = new BufferedReader(new FileReader(fileToRead));
            br.readLine();

            String csvLine = new String();

            while( (csvLine = br.readLine()) != null ){
                String[] csvArray = lineArrayFormat(csvLine, ";");
                Personagem pessoa = new Personagem(csvArray);
                personagens.add(pessoa);
            }

            br.close();
        }
        catch (Exception e){
            e.printStackTrace();
            personagens = null;
        }

        return personagens;
    }

    // Função para splitar uma String pelo char 'c'
    static String[] lineArrayFormat(String aux, final String c){
        String[] auxArray = aux.split(c);
        return auxArray;
    }
    
}
