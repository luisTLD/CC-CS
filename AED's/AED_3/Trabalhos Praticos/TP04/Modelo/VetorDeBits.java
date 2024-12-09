package Modelo;

import java.util.BitSet;

public class VetorDeBits
{
    private BitSet vetor;

    // Construtor padrão
    public VetorDeBits()
    {
        vetor = new BitSet();
        vetor.set(0);
    }

    // Construtor com tamanho inicial
    public VetorDeBits(int n)
    {
        vetor = new BitSet(n);
        vetor.set(n);
    }

    // Construtor com array de bytes
    public VetorDeBits(byte[] v) { vetor = BitSet.valueOf(v); }

    // Converter para array de bytes
    public byte[] toByteArray()
    {
        return vetor.toByteArray();
    }

    // Definir bit no índice especificado
    public void set(int i)
    {
        ajustarTamanhoSeNecessario(i);
        vetor.set(i);
    }

    // Limpar bit no índice especificado
    public void clear(int i)
    {
        ajustarTamanhoSeNecessario(i);
        vetor.clear(i);
    }

    // Obter valor do bit no índice especificado
    public boolean get(int i) { return vetor.get(i); }

    // Retornar comprimento lógico do vetor
    public int length() { return vetor.length() - 1; }

    // Retornar tamanho interno do vetor
    public int size() { return vetor.size(); }

    // Converter o vetor para String (representação binária)
    @Override
    public String toString()
    {
        StringBuilder sb = new StringBuilder();

        for (int i = 0; i < vetor.length() - 1; i++)
        {
            sb.append(vetor.get(i) ? '1' : '0');
        }
        
        return sb.toString();
    }

    // Ajustar tamanho se necessário
    private void ajustarTamanhoSeNecessario(int i)
    {
        if (i >= vetor.length() - 1)
        {
            vetor.clear(vetor.length() - 1);
            vetor.set(i + 1);
        }
    }
}
