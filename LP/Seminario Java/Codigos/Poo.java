// Exemplo de POO em Java com acoplamento usando interfaces
// 1. Herança

interface SomAnimal { void fazerSom(); }

// 2. Polimorfismo
class Animal implements SomAnimal {
    // 6. Encapsulamento
    private String nome;

    public Animal(String nome) { this.nome = nome; }
    public String getNome() { return nome; }
    
    // Implementando o método da interface
    @Override
    public void fazerSom() { System.out.println("O animal faz um som."); }
}

class Cachorro extends Animal {
    public Cachorro(String nome) { super(nome); }

    @Override
    public void fazerSom() { System.out.println(getNome() + " diz: Au Au!"); }
}

class Gato extends Animal {
    public Gato(String nome) { super(nome); }

    @Override
    public void fazerSom() { System.out.println(getNome() + " diz: Miau!"); }
}

// 3. Agregação e 4. Coesão
class Dono {
    private String nome;
    // 5. Associação
    private SomAnimal animal; 

    public Dono(String nome) { this.nome = nome; }
    public void adotarAnimal(SomAnimal animal) { this.animal = animal; }

    public void mostrarAnimal() {
        if (animal != null) {
            System.out.println(nome + " tem um animal chamado " + ((Animal) animal).getNome());
            animal.fazerSom(); // Demonstra polimorfismo
        } else {
            System.out.println(nome + " não tem um animal.");
        }
    }
}

// 8. Composição
class Zoo {
    private Dono dono;

    public Zoo(Dono dono) { this.dono = dono; }
    public void mostrarDono() { dono.mostrarAnimal(); }
}

// Classe principal para executar o código
public class Poo {
    public static void main(String[] args) {
        // Criando um dono
        Dono dono = new Dono("Carlos");

        // Criando animais
        SomAnimal cachorro = new Cachorro("Rex");
        SomAnimal gato = new Gato("Mia");

        // 7. Agregação
        dono.adotarAnimal(cachorro); // Adotando um cachorro
        dono.mostrarAnimal(); // Mostra o animal e o som que ele faz

        dono.adotarAnimal(gato); // Trocar o animal (agregação)
        dono.mostrarAnimal(); // Mostra o animal e o som que ele faz

        // Criando um zoológico
        Zoo zoo = new Zoo(dono);
        zoo.mostrarDono(); // Mostra informações do dono e do animal
    }
}
