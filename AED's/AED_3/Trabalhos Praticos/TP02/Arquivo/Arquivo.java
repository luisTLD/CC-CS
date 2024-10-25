package Arquivo;

import java.io.File;
import java.io.RandomAccessFile;
import java.lang.reflect.Constructor;

import Registro.*;
import Hash.*;

public class Arquivo<T extends Registro>
{
    final int TAM_CABECALHO = 4;        // Tamanho do cabeçalho do arquivo (4 bytes para guardar o ID para proximo registro)
    RandomAccessFile arquivo;           // Manipulador para o arquivo de dados
    String nome_arquivo;                // Nome do arquivo de dados
    Constructor<T> construtor;          // Construtor da classe T
    HashExtensivel<ParIDEndereco> indice_direto; // indice direto para acesso rapido aos registros

    // Construtor da classe Arquivo (na = Nome para o arquivo)
    public Arquivo(String na, Constructor<T> c) throws Exception
    {
        // Cria o diretorio de dados se nao existir
        File d = new File(".\\dados");
        if(!d.exists()) d.mkdir();

        // Define o nome do arquivo e abre o RandomAccessFile para leitura e escrita
        this.nome_arquivo = ".\\dados\\" + na + ".db";
        this.construtor = c;
        arquivo = new RandomAccessFile(this.nome_arquivo, "rw");

        // Inicializa o cabecalho do arquivo se ele nao existir (Setar ID como 0)
        if (arquivo.length() < TAM_CABECALHO) arquivo.writeInt(0);

        // Inicializa o indice direto com os arquivos de indice
        indice_direto = new HashExtensivel<>(
            ParIDEndereco.class.getConstructor(), 
            4, 
            ".\\dados\\" + na + ".hash_d.db", 
            ".\\dados\\" + na + ".hash_c.db"
        );
    }

    // Cria um novo registro no arquivo
    public int create(T obj) throws Exception
    {
        // Atualiza o ID do próximo registro
        arquivo.seek(0);
        int proximo_id = arquivo.readInt() + 1;
        arquivo.seek(0);
        arquivo.writeInt(proximo_id);
        obj.setId(proximo_id);

        // Move o ponteiro para o final do arquivo e escreve o novo registro
        arquivo.seek(arquivo.length());
        long endereco = arquivo.getFilePointer();

        byte[] b = obj.toByteArray();
        arquivo.writeByte(' ');       // Marca o registro como válido
        arquivo.writeShort(b.length);   // Escreve o tamanho do registro
        arquivo.write(b);               // Escreve o conteúdo do registro

        // Adiciona a entrada no indice direto
        indice_direto.create(new ParIDEndereco(proximo_id, endereco));

        return obj.getId();
    }

    // Le um registro do arquivo baseado no ID
    public T read(int id) throws Exception
    {
        T obj;
        short tamanho;
        byte[] array_registro;
        byte lapide;

        // Recupera o endereco do registro a partir do indice direto
        ParIDEndereco pid = indice_direto.read(id);
        if(pid != null)
        {
            // Move o cursor do arquivo para onde deve comecar a ler 
            arquivo.seek(pid.getEndereco());
            obj = construtor.newInstance();
            lapide = arquivo.readByte();
            // Se tiver marcado como valido, ler sequencialmente a quantidade de bytes que esta marcado como tamanho do registro
            if (lapide == ' ')
            {
                tamanho = arquivo.readShort();
                array_registro = new byte[tamanho];
                arquivo.read(array_registro);
                obj.fromByteArray(array_registro);
                if (obj.getId() == id) return obj; // Verifica se o ID corresponde
            }
        }

        return null; // Retorna null se o registro nao for encontrado
    }

    // Remove um registro do arquivo baseado no ID
    public boolean delete(int id) throws Exception
    {
        T obj;
        short tamanho;
        byte[] array_registro;
        byte lapide;

        // Recupera o endereço do registro a partir do indice direto
        ParIDEndereco pie = indice_direto.read(id);
        if (pie != null)
        {
            arquivo.seek(pie.getEndereco());
            obj = construtor.newInstance();
            lapide = arquivo.readByte();
            // Se tiver marcado como valido, ler sequencialmente a quantidade de bytes que esta marcado como tamanho do registro
            if(lapide == ' ') 
            {
                tamanho = arquivo.readShort();
                array_registro = new byte[tamanho];
                arquivo.read(array_registro);
                obj.fromByteArray(array_registro);
                if(obj.getId() == id)
                {
                    // Marca o registro como excluído
                    if(indice_direto.delete(id))
                    {
                        arquivo.seek(pie.getEndereco());
                        arquivo.write('*');
                        return true;
                    }
                }
            }
        }

        return false; // Retorna false se o registro nao for encontrado ou nao puder ser excluido
    }

    // Atualiza um registro existente com novos dados
    public boolean update(T novo_obj) throws Exception
    {
        T obj;
        short tamanho;
        byte[] array_registro;
        byte lapide;

        // Recupera o endereço do registro a partir do indice direto
        ParIDEndereco pie = indice_direto.read(novo_obj.getId());
        if (pie != null)
        {
            arquivo.seek(pie.getEndereco());
            obj = construtor.newInstance();
            lapide = arquivo.readByte();
            // Se tiver marcado como valido, ler sequencialmente a quantidade de bytes que esta marcado como tamanho do registro
            if (lapide == ' ')
            {
                tamanho = arquivo.readShort();
                array_registro = new byte[tamanho];
                arquivo.read(array_registro);
                obj.fromByteArray(array_registro);
                if (obj.getId() == novo_obj.getId())
                {
                    byte[] novo_array_registro = novo_obj.toByteArray();
                    short novo_tamanho = (short) novo_array_registro.length;

                    // Atualiza o registro se o novo tamanho for menor ou igual ao tamanho antigo
                    if (novo_tamanho <= tamanho)
                    {
                        arquivo.seek(pie.getEndereco() + 3);
                        arquivo.write(novo_array_registro);
                    }
                    // Move o novo registro para o fim do arquivo se o novo tamanho for maior
                    else
                    {
                        arquivo.seek(pie.getEndereco());
                        arquivo.write('*');             // Marcar registro antigo como excluido
                        arquivo.seek(arquivo.length());   // Ir para o final para escrever o registro atualizado
                        long novo_endereco = arquivo.getFilePointer();

                        arquivo.writeByte(' ');             // Marca o registro como válido
                        arquivo.writeShort(novo_tamanho);     // Escreve o tamanho do registro
                        arquivo.write(novo_array_registro);   // Escreve o conteúdo do registro
                        indice_direto.update(new ParIDEndereco(novo_obj.getId(), novo_endereco)); // Atualiza o indice na hash
                    }

                    return true;
                }
            }
        }

        return false; // Retorna false se o registro não for encontrado ou não puder ser atualizado
    }

    // Fecha o arquivo e o indice direto
    public void close() throws Exception
    {
        arquivo.close();
        indice_direto.close();
    }
}
