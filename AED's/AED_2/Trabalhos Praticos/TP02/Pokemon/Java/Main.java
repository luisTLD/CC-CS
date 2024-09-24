import java.util.Date;
import java.util.ArrayList;
import java.util.List;
import java.io.BufferedReader;
import java.io.FileReader;
import java.text.SimpleDateFormat;
import java.util.Scanner;

/*
            Logica do codigo

    Abrimos o arquivo para leitura, lemos linha por linha, para cada linha temos 
que formata-la manualmente para conseguir dar split em todos os atributos, apos 
formata-la, iremos dar split onde teremos um array de string e em cada posicao sera
uma coluna a ser setada, mandamos este array para o construtor e setamos manualmente
atributo por atributo, apos isso adicionamos esta nova instancia a nossa List de pokemons
e o retornamos, apos isso fazemos uma pesquisa, adicionamos a nossa nova List, e apenas
trabalhamos com ela apartir de agora
*/

public class Main
{
    public static void main(String[] args)
    {
        Scanner sc = new Scanner(System.in);

        String input_string = new String();
        int input_int = 0;

        // Ler o CSV, e passar tudo para uma List
        List<Pokemon> pokemons = ReadCsv.readAllFile("pokemon.csv");

        // List que iremos adicionar apenas os selecionados da entrada, para trabalhar so com eles
        List<Pokemon> using = new ArrayList<>();

        // Ler ate FIM, e procurar por ID, e adicionar na List
        while (!(input_string = sc.nextLine()).equals("FIM")) {
            input_int = Integer.parseInt(input_string);
            using.add(PokemonSearch.searchPokemonId(pokemons, input_int));
        }

        // Printar instancia por instancia da List
        for (Pokemon p : using) System.out.println(p);

        sc.close();
    }
}



class Pokemon
{
    // Atributos privados
    private int id;
    private int generation;
    private String name;
    private String description;
    private ArrayList<String> types;
    private ArrayList<String> abilities;
    private double weight;
    private double height;
    private int captureRate;
    private boolean isLegendary;
    private Date captureDate;

    // Construtores
    public Pokemon()
    {
        this.id = 0;
        this.generation = 0;
        this.name = "";
        this.description = "";
        this.types = new ArrayList<>();
        this.abilities = new ArrayList<>();
        this.weight = 0.0;
        this.height = 0.0;
        this.captureRate = 0;
        this.isLegendary = false;
        this.captureDate = new Date();
    }

    public Pokemon(int id, int generation, String name, String description, ArrayList<String> types, 
                   ArrayList<String> abilities, double weight, double height, int captureRate, 
                   boolean isLegendary, Date captureDate){
        this.id = id;
        this.generation = generation;
        this.name = name;
        this.description = description;
        this.types = types;
        this.abilities = abilities;
        this.weight = weight;
        this.height = height;
        this.captureRate = captureRate;
        this.isLegendary = isLegendary;
        this.captureDate = captureDate;
    }

    // Recebe um array com cada coluna, e vai setando
    public Pokemon(String[] aux) throws Exception
    {
        // Por ter atributos vazios, setar tudo com 0 para nao ocorrer problemas de Parse
        for (int i = 0; i < aux.length; i++) if (aux[i].isEmpty()) aux[i] = "0";


            // Setar atributo por atributo
        this.id = Integer.parseInt(aux[0]);
        this.generation = Integer.parseInt(aux[1]);
        
        this.name = aux[2];
        this.description = aux[3];

        // Verificacao, pois existem pokemons com 2 tipos e pokemons com apenas 1 tipo
        this.types = new ArrayList<>();
        aux[4] = "'" + aux[4] + "'";
        this.types.add(aux[4]);
        if (aux[5] != "0") {
            aux[5] = "'" + aux[5].trim() + "'";
            this.types.add(aux[5]);  
        }
        
        // Formatar a string para ficar correto na hora de printar
        aux[6] = aux[6].replace("\"", "");
        aux[6] = aux[6].replace("[", "");
        aux[6] = aux[6].replace("]", "");
        String[] tmp = aux[6].split(",");
        this.abilities = new ArrayList<>();
        for (String s : tmp) abilities.add(s.trim());
        
        this.weight = Double.parseDouble(aux[7]);
        this.height = Double.parseDouble(aux[8]);

        this.captureRate = Integer.parseInt(aux[9]);

        this.isLegendary = (aux[10].equals("1") ? true : false);

        if (aux[11].isEmpty())
        {
            this.captureDate = null;
        } else
        {
            SimpleDateFormat inputDateFormat = new SimpleDateFormat("dd/MM/yyyy");
            this.captureDate = inputDateFormat.parse(aux[11]);
        }
    }

    // Métodos Getters e Setters
    public int getId() { return id; }
    public void setId(int id) { this.id = id; }

    public int getGeneration() { return generation; }
    public void setGeneration(int generation) { this.generation = generation; }

    public String getName() { return name; }
    public void setName(String name) { this.name = name; }

    public String getDescription() { return description; }
    public void setDescription(String description) { this.description = description; }

    public ArrayList<String> getTypes() { return types; }
    public void setTypes(ArrayList<String> types) { this.types = types; }

    public ArrayList<String> getAbilities() { return abilities; }
    public void setAbilities(ArrayList<String> abilities) { this.abilities = abilities; }

    public double getWeight() { return weight; }
    public void setWeight(double weight) { this.weight = weight; }

    public double getHeight() { return height; }
    public void setHeight(double height) { this.height = height; }

    public int getCaptureRate() { return captureRate; }
    public void setCaptureRate(int captureRate) { this.captureRate = captureRate; }

    public boolean getIsLegendary() { return isLegendary; }
    public void setIsLegendary(boolean isLegendary) { this.isLegendary = isLegendary; }

    public Date getCaptureDate() { return captureDate; }
    public void setCaptureDate(Date captureDate) { this.captureDate = captureDate; }

    // Método clone
    public Pokemon clone()
    {
        try {
            return (Pokemon) super.clone();
        } catch (CloneNotSupportedException e)
        {
            System.out.println("Cloning not supported.");
            return null;
        }
    }

    // Método para imprimir todos atributos da instancia apenas chamando ela no SOP
    public String toString()
    {
        SimpleDateFormat outputDateFormat = new SimpleDateFormat("dd/MM/yyyy");
        String formattedDate = (captureDate != null) ? outputDateFormat.format(captureDate) : "Data não disponível";

        return "[#" + id + " -> " + name + ": " + description +
            " - " + types + " - " + abilities + 
            " - " + weight + "kg - " + height + "m - " +
            captureRate + "% - " + isLegendary + 
            " - " + generation + " gen] - " + formattedDate;
    }
}



class PokemonSearch {
    // Função estática que busca um Pokémon pelo ID
    public static Pokemon searchPokemonId(List<Pokemon> pokemons, int id)
    {
        for (Pokemon pokemon : pokemons)
        {
            if (pokemon.getId() == id)
            {
                return pokemon;
            }
        }
        return null;
    }
}


class ReadCsv{
    public static List<Pokemon> readAllFile(final String fileToRead)
    {
        List<Pokemon> personagens = new ArrayList<>();
        
        try
        {
            BufferedReader br = new BufferedReader(new FileReader(fileToRead));

            // Pular o cabecalho
            br.readLine();

            // Ler linha por linha
            String csvLine = new String();
            while((csvLine = br.readLine()) != null)
            {
                // Tratar a linha, para conseguir fazer o plit em ; sem atrapalhar a lista
                csvLine = lineFormat(csvLine);

                // Para cada linha, damos split e jogamos para o construtor, e adicionamos a instancia toda preenchida no nosso array
                Pokemon pessoa = new Pokemon(csvLine.split(";"));
                personagens.add(pessoa);
            }

            br.close();
        }
        catch (Exception e)
        {
            e.printStackTrace();
            personagens = null;
        }

        // Retornar array com todos os pokemons
        return personagens;
    }

    // Subistituir todas as , por ; para dar split (menos as , dentro de [])
    private static String lineFormat(String line)
    {
        char[] array_aux = line.toCharArray();
        boolean in_list = false;
        for (int i = 0; i < array_aux.length; i++)
        {
            if (!in_list && array_aux[i] == ',') array_aux[i] = ';'; 
            else if (array_aux[i] == '"') in_list = !in_list;
        }

        return new String(array_aux);
    }

}