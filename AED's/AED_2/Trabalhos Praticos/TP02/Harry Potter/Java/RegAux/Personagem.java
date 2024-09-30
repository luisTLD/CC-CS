package RegAux;

import java.time.LocalDate;
import java.time.format.DateTimeFormatter;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Scanner;

public class Personagem{
    private String id;
    private String name;
    private List<String> alternateNames;
    private String house;
    private String ancestry;
    private String species;
    private String patronus;
    private boolean hogwartsStaff; 
    private boolean hogwartsStudent;
    private String actorName;
    private boolean alive;
    private List<String> alternateActors;
    private LocalDate dateOfBirth;
    private int yearOfBirth;
    private String eyeColor;
    private String gender;
    private String hairColor;
    private boolean wizard;

    public Personagem(String[] aux) {
        this.id = aux[0];
        this.name = aux[1];
        this.alternateNames = new ArrayList<>();
        alternateNames.addAll(Arrays.asList(stringArrayFormat(aux[2])));
        this.house = aux[3];
        this.ancestry = aux[4];
        this.species = aux[5];
        this.patronus = aux[6];
        this.hogwartsStaff = stringBooleanFormat(aux[7]);
        this.hogwartsStudent = stringBooleanFormat(aux[8]);
        this.actorName = aux[9];
        this.alive = stringBooleanFormat(aux[10]);
        this.alternateActors = new ArrayList<>();
        alternateActors.addAll(Arrays.asList(stringArrayFormat(aux[11])));
        this.dateOfBirth = stringLocalDateFormat(aux[12]);
        this.yearOfBirth = Integer.parseInt(aux[13]);
        this.eyeColor = aux[14];
        this.gender = aux[15];
        this.hairColor = aux[16];
        this.wizard = stringBooleanFormat(aux[17]);
    }

    public Personagem(){}

    // Set's
    public void setId(String id) {this.id = id;}
    public void setName(String name) {this.name = name;}
    public void setAlternateNames(List<String> alternateNames) {this.alternateNames = alternateNames;}
    public void setHouse(String house) {this.house = house;}
    public void setAncestry(String ancestry) {this.ancestry = ancestry;}
    public void setSpecies(String species) {this.species = species;}
    public void setPatronus(String patronus) {this.patronus = patronus;}
    public void setHogwartsStaff(boolean hogwartsStaff) {this.hogwartsStaff = hogwartsStaff;}
    public void setHogwartsStudent(boolean hogwartsStudent) {this.hogwartsStudent = hogwartsStudent;}
    public void setActorName(String actorName) {this.actorName = actorName;}
    public void setAlive(boolean alive) {this.alive = alive;}
    public void setAlternateActors(List<String> alternateActors) {this.alternateActors = alternateActors;}
    public void setDateOfBirth(LocalDate dateOfBirth) {this.dateOfBirth = dateOfBirth;}
    public void setYearOfBirth(int yearOfBirth) {this.yearOfBirth = yearOfBirth;}
    public void setEyeColor(String eyeColor) {this.eyeColor = eyeColor;}
    public void setGender(String gender) {this.gender = gender;}
    public void setHairColor(String hairColor) {this.hairColor = hairColor;}
    public void setWizard(boolean wizard) {this.wizard = wizard;}

    // Get's
    public String getId() {return id;}
    public String getName() {return name;}
    public List<String> getAlternateNames() {return alternateNames;}
    public String getHouse() {return house;}
    public String getAncestry() {return ancestry;}
    public String getSpecies() {return species;}
    public String getPatronus() {return patronus;}
    public boolean isHogwartsStaff() {return hogwartsStaff;}
    public boolean getHogwartsStudent() {return hogwartsStudent;}
    public String getActorName() {return actorName;}
    public boolean isAlive() {return alive;}
    public List<String> getAlternateActors() {return alternateActors;}
    public LocalDate getDateOfBirth() {return dateOfBirth;}
    public int getYearOfBirth() {return yearOfBirth;}
    public String getEyeColor() {return eyeColor;}
    public String getGender() {return gender;}
    public String getHairColor() {return hairColor;}
    public boolean isWizard() {return wizard;}

    // Retornar um clone
    public Personagem clone() {
        Personagem clone = new Personagem();

        clone.id = this.id;
        clone.name = this.name;
        clone.alternateNames = new ArrayList<>(this.alternateNames);
        clone.house = this.house;
        clone.ancestry = this.ancestry;
        clone.species = this.species;
        clone.patronus = this.patronus;
        clone.hogwartsStaff = this.hogwartsStaff;
        clone.hogwartsStudent = this.hogwartsStudent;
        clone.actorName = this.actorName;
        clone.alive = this.alive;
        clone.alternateActors = new ArrayList<>(this.alternateActors);
        clone.dateOfBirth = this.dateOfBirth;
        clone.yearOfBirth = this.yearOfBirth;
        clone.eyeColor = this.eyeColor;
        clone.gender = this.gender;
        clone.hairColor = this.hairColor;
        clone.wizard = this.wizard;

        return clone;
    }
    
    // Função para printar todos os atributos 
    public void printPessoa() {
        DateTimeFormatter formatter = DateTimeFormatter.ofPattern("dd-MM-yyyy");
        String dateOfBirthFormat = dateOfBirth.format(formatter);

        System.out.println("[" + id + " ## "  + name + " ## " + arrayToStringFormat(alternateNames) + " ## "
        + house + " ## " + ancestry + " ## " + species + " ## " + patronus + " ## " + hogwartsStaff + " ## " 
        + hogwartsStudent + " ## " + actorName + " ## " + alive + " ## " + dateOfBirthFormat + " ## " 
        + yearOfBirth + " ## " + eyeColor + " ## " + gender + " ## " + hairColor + " ## " + wizard + "]");
    }

    // Função auxiliar para printar todos os atributos de todas os personagens de uma lista
    public static void printAll(final List<Personagem> personagens){
        for ( Personagem pessoa : personagens ) pessoa.printPessoa();
    }
    
    // Função auxiliar para o exercico, que retorna uma Lista expecifica por ID's necessarios
    public static List<Personagem> mySubList(final List<Personagem> personagens, Scanner sc){
        String input = new String();
        List<Personagem> aux = new ArrayList<>(); 

        while (!(input = sc.nextLine()).equals("FIM")){
            int i = SearchList.linearIdSearch(personagens, input);

            if (i != -1) aux.add(personagens.get(i));
            else System.out.print("ID " + input + " não encontrado");
        }

        return aux;
    }
 
    // Função para converter um Array em uma string com dentre de { }
    private String arrayToStringFormat(List<String> aux){
        String[] array = aux.toArray(new String[aux.size()]);
        String str = Arrays.toString(array);

        str = str.replace("[", "{");
        str = str.replace("]", "}");

        return str;
    }
    
    // Função para converter uma String em um Array, delimitado por ','
    private String[] stringArrayFormat(String aux){
        aux = aux.replace("[", "");
        aux = aux.replace("]", "");
        aux = aux.replace("'","");

        String[] auxArray = aux.split(",");

        for ( int i = 0; i < auxArray.length; i++ ){
            auxArray[i] = auxArray[i].trim();
        }

        return auxArray;
    }

    // Função para converter uma String em Boolean
    private boolean stringBooleanFormat(final String aux){
        return aux.equals("VERDADEIRO") ? true : false;
    }

    // Função para converter uma String em um LocalDate
    private LocalDate stringLocalDateFormat(final String aux){
        try {
            DateTimeFormatter formatter = DateTimeFormatter.ofPattern("d-M-yyyy");
            LocalDate data = LocalDate.parse(aux, formatter);
            return data;
        } catch (Exception e) {
            e.printStackTrace();
            return null;
        }
    }
}
