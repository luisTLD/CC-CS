package Modelo;
import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.DataInputStream;
import java.io.DataOutputStream;

public class Rotulo implements Registro.Registro{

/* Used to store recorded Tasks from the Arquivo database
 * Contains:
 *   id: Attribute given only by Arquivo to indicate its position
 *   nome: 
*/
    private int id;
    
    //Atributos da classe Categoria
    private String nome;

    // Métodos Getters e Setters para os campos da classe
    public void setId(int id) { this.id = id; }
    public int getId() { return this.id; }

    public void setNome(String nome) { this.nome = nome; }
    public String getNome() { return this.nome; }

    //Método toByteArray
    public byte[] toByteArray()
    {
        ByteArrayOutputStream baos = new ByteArrayOutputStream();
        DataOutputStream dos = new DataOutputStream(baos);
        try
        {
            dos.writeInt(this.id);
            dos.writeUTF(this.nome);
        } 
        catch(Exception e)
        {
            System.out.println("Erro ao converter Tarefa para array de byte");
            System.out.println(e.getMessage());
        }

        return baos.toByteArray();
    }
    
    //Método fromByteArray
    public void fromByteArray(byte [] array)
    {
        ByteArrayInputStream bais = new ByteArrayInputStream(array);
        DataInputStream dis = new DataInputStream(bais);
        try
        {
            this.id = dis.readInt();
            this.nome = dis.readUTF();
        }
        catch(Exception e)
        {
            System.out.println("Erro converter vetor de byte pra objeto tarefa");
            e.printStackTrace();
        }
    }

    //Construtores
    public Rotulo(String nome)
    {
        this.nome = nome;
        this.id = -1;
    }

    public Rotulo(){}

    @Override
    public String toString() { return getArgumentList(); }


    private String getArgumentList()
    {
        StringBuilder sb = new StringBuilder();
        sb.append("{");
        sb.append("id: ").append(Integer.toString(this.id)).append(", ");
        sb.append("nome: ").append(nome).append(", ");

        return sb.toString();
    }

}
