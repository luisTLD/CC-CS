package Registro;

import java.io.IOException;

// Interface que forca a classe ter estas funcoes, para poder ser utilizada 
public interface Registro
{
    public void setId(int i);

    public int getId();

    public byte[] toByteArray() throws IOException;
    
    public void fromByteArray(byte[] b) throws IOException;
}


