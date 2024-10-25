package Arvore;

/*
Esta classe representa um objeto para uma entidade
que será armazenado em uma árvore B+

Neste caso em particular, este objeto é representado
por dois números inteiros para que possa conter
relacionamentos entre dois IDs de entidades quaisquer
 
Implementado pelo Prof. Marcos Kutova
v1.0 - 2021
*/

import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;

public class ParIdId implements Registro.RegistroArvoreBMais<ParIdId> {

  private int id1; // Primeiro ID (identificador de uma entidade)
  private int id2; // Segundo ID (identificador de outra entidade)
  private short TAMANHO = 8; // Tamanho fixo do registro em bytes (2 inteiros)

  // Construtor padrão, inicializa com IDs -1
  public ParIdId()
  {
    this(-1, -1);
  }

  // Construtor que recebe apenas um ID, inicializa o segundo com -1
  public ParIdId(int n1)
  {
    this(n1, -1);
  }

  // Construtor que recebe dois IDs
  public ParIdId(int n1, int n2)
  {
    try
    {
      this.id1 = n1; // ID da entidade agregadora ( Categoria )
      this.id2 = n2; // ID da outra entidade ( Tarefa )
    }
    catch (Exception ec)
    {
      ec.printStackTrace();
    }
  }

  // Setters e Getters
  public void setId1(int id) { this.id1 = id; }
  public int getId1() { return this.id1; }

  public void setId2(int id) { this.id2 = id; }
  public int getId2() { return this.id2; }

  @Override
  public ParIdId clone()
  {
    // Retorna uma cópia do objeto atual
    return new ParIdId(this.id1, this.id2);
  }

  // Retorna o tamanho fixo do registro
  public short size()
  {
    return this.TAMANHO;
  }

  // Compara dois objetos ParIdId, baseando-se primeiro em id1 e depois em id2
  public int compareTo(ParIdId a)
  {
    if (this.id1 != a.id1)
    {
      return this.id1 - a.id1; // Compara id1
    }
    else
    {
      // Compara id2 apenas se o id2 da busca for diferente de -1
      // Permite busca de listas com base no id1
      return this.id2 == -1 ? 0 : this.id2 - a.id2;
    }
  }

  // Representação do objeto como string no formato "id1;id2"
  public String toString()
  {
    return String.format("%3d", this.id1) + ";" + String.format("%-3d", this.id2);
  }

  // Converte o objeto para um array de bytes para armazenamento
  public byte[] toByteArray() throws IOException
  {
    ByteArrayOutputStream baos = new ByteArrayOutputStream();
    DataOutputStream dos = new DataOutputStream(baos);

    dos.writeInt(this.id1); // Escreve id1 no array de bytes
    dos.writeInt(this.id2); // Escreve id2 no array de bytes

    return baos.toByteArray(); // Retorna o array de bytes completo
  }

  // Constrói o objeto a partir de um array de bytes
  public void fromByteArray(byte[] ba) throws IOException
  {
    ByteArrayInputStream bais = new ByteArrayInputStream(ba);
    DataInputStream dis = new DataInputStream(bais);
    
    this.id1 = dis.readInt(); // Lê o primeiro inteiro do array de bytes (id1)
    this.id2 = dis.readInt(); // Lê o segundo inteiro do array de bytes (id2)
  }

}
