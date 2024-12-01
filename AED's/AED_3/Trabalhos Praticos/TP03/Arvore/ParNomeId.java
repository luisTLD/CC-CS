package Arvore;

/*
Esta classe representa um objeto para uma entidade
que será armazenado em uma árvore B+

Neste caso em particular, este objeto é representado
por uma string e um inteiro para que possa ser usado
como índice indireto de nomes para uma entidade qualquer.

Implementado pelo Prof. Marcos Kutova
v1.0 - 2024
*/

import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.text.Normalizer;
import java.util.regex.Pattern;

public class ParNomeId implements Registro.RegistroArvoreBMais<ParNomeId>
{

  private String nome;        // Nome a ser armazenado
  private int id;             // ID associado ao nome
  private short TAMANHO = 30; // Tamanho fixo do registro em bytes

  // Construtor padrão, inicializa com valores vazios
  public ParNomeId() throws Exception
  {
    this("", -1);
  }

  // Construtor que recebe apenas um nome, ID é inicializado com -1
  public ParNomeId(String n) throws Exception
  {
    this(n, -1);
  }

  // Construtor que recebe um nome e um ID
  public ParNomeId(String n, int i) throws Exception
  {
    // Verifica se o nome excede o limite de 26 bytes
    if (n.getBytes().length > 26)
    {
      throw new Exception("Nome extenso demais. Diminua o número de caracteres.");
    }

    this.nome = n; 
    this.id = i;
  }

  // Setters e Getters
  public void setId(int id) { this.id = id; }
  public int getId() { return this.id; }
  
  public void setNome(String s) { this.nome = s; }
  public String getNome() { return this.nome; }

  @Override
  public ParNomeId clone()
  {
    try
    {
      // Retorna uma cópia do objeto atual
      return new ParNomeId(this.nome, this.id);
    }
    catch (Exception e)
    {
      e.printStackTrace();
    }
    return null;
  }

  // Retorna o tamanho fixo do registro
  public short size()
  {
    return this.TAMANHO;
  }

  // Compara dois objetos ParNomeId baseando-se no nome (ordem alfabética)
  public int compareTo(ParNomeId a)
  {
    return transforma(this.nome).compareTo(transforma(a.nome));
  }

  // Representação do objeto como string no formato "nome;id"
  public String toString()
  {
    return this.id + ") " + this.nome;
  }

  // Converte o objeto para um array de bytes para armazenamento
  public byte[] toByteArray() throws IOException
  {
    ByteArrayOutputStream baos = new ByteArrayOutputStream();
    DataOutputStream dos = new DataOutputStream(baos);

    byte[] vb = new byte[26];             // Array de bytes para o nome com tamanho fixo de 26
    byte[] vbNome = this.nome.getBytes(); // Converte o nome para bytes

    int i = 0;

    // Copia o nome para o array, byte a byte
    while (i < vbNome.length)
    {
      vb[i] = vbNome[i];
      i++;
    }

    // Preenche o restante do array com espaços, se necessário
    while (i < 26)
    {
      vb[i] = ' ';
      i++;
    }
    dos.write(vb);              // Escreve o nome no DataOutputStream
    dos.writeInt(this.id);      // Escreve o ID
    return baos.toByteArray();  // Retorna o array de bytes completo
  }

  // Constrói o objeto a partir de um array de bytes
  public void fromByteArray(byte[] ba) throws IOException
  {
    ByteArrayInputStream bais = new ByteArrayInputStream(ba);
    DataInputStream dis = new DataInputStream(bais);

    byte[] vb = new byte[26]; // Array de bytes para o nome
    dis.read(vb);             // Lê o nome do array de bytes

    this.nome = (new String(vb)).trim(); // Converte para string e remove espaços
    this.id = dis.readInt();             // Lê o ID
  }

  // Remove acentos e caracteres especiais do nome e converte para minúsculas
  public static String transforma(String str)
  {
    String nfdNormalizedString = Normalizer.normalize(str, Normalizer.Form.NFD);
    Pattern pattern = Pattern.compile("\\p{InCombiningDiacriticalMarks}+");
    return pattern.matcher(nfdNormalizedString).replaceAll("").toLowerCase();
  }
}
