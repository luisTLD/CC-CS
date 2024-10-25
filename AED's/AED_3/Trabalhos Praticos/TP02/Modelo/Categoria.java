package Modelo;

import java.io.IOException;
import java.io.ByteArrayOutputStream;
import java.io.DataOutputStream;
import java.io.ByteArrayInputStream;
import java.io.DataInputStream;

import Registro.*;

public class Categoria implements Registro
{

    public int id;      // ID da categoria
    public String nome; // Nome da categoria

    // Construtor padrão, inicializa com ID -1 e nome vazio
    public Categoria()
    {
        this(-1, "");
    }
    
    // Construtor que inicializa apenas com o nome, ID é -1
    public Categoria(String n)
    {
        this(-1, n);
    }

    // Construtor que inicializa com ID e nome fornecidos
    public Categoria(int i, String n)
    {
        this.id = i;
        this.nome = n;
    }

    // Getters e Setters
    public void setId(int id) { this.id = id; }
    public int getId() { return id; }

    public String getNome() { return nome; }
    public void setNome(String nome) { this.nome = nome; }

    // Retorna uma representação da categoria como string
    public String toString()
    {
        return "\nID..: " + this.id +
               "\nNome: " + this.nome;
    }

    // Converte o objeto Categoria para um array de bytes para armazenamento
    public byte[] toByteArray() throws IOException
    {
        ByteArrayOutputStream baos = new ByteArrayOutputStream();
        DataOutputStream dos = new DataOutputStream(baos);

        dos.writeInt(this.id);   // Escreve o ID no array de bytes
        dos.writeUTF(this.nome); // Escreve o nome no array de bytes

        return baos.toByteArray(); // Retorna o array de bytes completo
    }

    // Constrói o objeto Categoria a partir de um array de bytes
    public void fromByteArray(byte[] b) throws IOException
    {
        ByteArrayInputStream bais = new ByteArrayInputStream(b);
        DataInputStream dis = new DataInputStream(bais);

        this.id = dis.readInt();   // Lê o ID do array de bytes
        this.nome = dis.readUTF(); // Lê o nome do array de bytes
    }
}
