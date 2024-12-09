package Arvore;

import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.text.Normalizer;
import java.util.regex.Pattern;

public class ParRotuloId implements Registro.RegistroArvoreBMais<ParRotuloId>
{

    /* Atributos */
    private String nome;
    private int id;
    private short TAMANHO = 30;
  
    /* Construtores */
    public ParRotuloId() throws Exception 
    {
      this("", -1);
    }
  
    public ParRotuloId(String n) throws Exception 
    {
      this(n, -1);
    }
  
    public ParRotuloId(String n, int i) throws Exception 
    {
      if(n.getBytes().length>26)
        throw new Exception("Nome extenso demais. Diminua o número de caracteres.");
      this.nome = n; // ID do Usuário
      this.id = i; // ID da Pergunta
    }

    /* GET's */

    public String getNome()
    {
        return this.nome;
    }

    public int getId()
    {
        return this.id;
    }
    
    /* SET's */

    public void setNome(String nome)
    {
        this.nome = nome;
    }

    public void setId(int id)
    {
        this.id = id;
    }

    
    /* Clone */
    @Override
    public ParRotuloId clone() 
    {
      try 
      {
        return new ParRotuloId(this.nome, this.id);
      } catch (Exception e) {
        e.printStackTrace();
      }
      return null;
    }
    
    /* Retorna o Tamanho do Registro */
    public short size() 
    {
      return this.TAMANHO;
    }
    
    /* Comparação */
    public int compareTo(ParRotuloId a) 
    {
      return transforma(this.nome).compareTo(transforma(a.nome));
    }
    
    /* Formatação da String */
    public String toString() 
    {
      return this.nome + ";" + String.format("%-3d", this.id);
    }
  
    public byte[] toByteArray() throws IOException 
    {
      ByteArrayOutputStream baos = new ByteArrayOutputStream();
      DataOutputStream dos = new DataOutputStream(baos);
      byte[] vb = new byte[26];
      byte[] vbNome = this.nome.getBytes();
      int i=0;
      while(i<vbNome.length) {
        vb[i] = vbNome[i];
        i++;
      }
      while(i<26) {
        vb[i] = ' ';
        i++;
      }
      dos.write(vb);
      dos.writeInt(this.id);
      return baos.toByteArray();
    }
  
    public void fromByteArray(byte[] ba) throws IOException 
    {
      ByteArrayInputStream bais = new ByteArrayInputStream(ba);
      DataInputStream dis = new DataInputStream(bais);
      byte[] vb = new byte[26];
      dis.read(vb);
      this.nome = (new String(vb)).trim();
      this.id = dis.readInt();
    }
  
    public static String transforma(String str) 
    {
      String nfdNormalizedString = Normalizer.normalize(str, Normalizer.Form.NFD);
      Pattern pattern = Pattern.compile("\\p{InCombiningDiacriticalMarks}+");
      return pattern.matcher(nfdNormalizedString).replaceAll("").toLowerCase();
    }
}
