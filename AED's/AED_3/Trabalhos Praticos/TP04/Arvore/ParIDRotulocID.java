package Arvore;


import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;

public class ParIDRotulocID implements Registro.RegistroArvoreBMais<ParIDRotulocID> {

    /* Conexão entre ID de Categorias e ID de Tarefa */
    private int id1;
    private int id2;
    private final short TAMANHO = 8;

    public ParIDRotulocID() 
    {
        this(-1, -1);
    }

    public ParIDRotulocID(int id1) 
    {
        this(id1, -1);
    }

    public ParIDRotulocID(int id1, int id2) 
    {
        try 
        {
            this.id1 = id1;
            this.id2 = id2;
        } catch (Exception e) 
        {
            e.printStackTrace();
        }
    }

    /* SET's */
    public void setId1(int id1) 
    {

        this.id1 = id1;
    }

    public void setId2(int id2) 
    {

        this.id2 = id2;
    }

    /* Fim dos Set's */

    /* GET's */
    public int getId1() 
    {

        return id1;
    }

    public int getId2() 
    {

        return id2;
    }

    /* Fim dos GET's */

    @Override

    public ParIDRotulocID clone() 
    {
        return new ParIDRotulocID(this.id1, this.id2);
    }

    public short size() 
    {
        return this.TAMANHO;
    }

    public int compareTo(ParIDRotulocID a) 
    {
        if (this.id1 != a.id1) 
        {
            return this.id1 - a.id1;
        } else 
        {
            return this.id2 == -1 ? 0 : this.id2 - a.id2;
        }
    }

    public String toString() 
    {
        return String.format("%3d", this.id1) + ";" + String.format("%-3d", this.id2);
    }

    public byte[] toByteArray() throws IOException 
    {
        ByteArrayOutputStream baos = new ByteArrayOutputStream();
        DataOutputStream dos = new DataOutputStream(baos);
        dos.writeInt(this.id1);
        dos.writeInt(this.id2);
        return baos.toByteArray();
    }

    public void fromByteArray(byte[] ba) throws IOException 
    {
        ByteArrayInputStream bais = new ByteArrayInputStream(ba);
        DataInputStream dis = new DataInputStream(bais);
        this.id1 = dis.readInt();
        this.id2 = dis.readInt();
    }

}
