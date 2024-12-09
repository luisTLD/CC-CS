package Arquivo;

import Modelo.LZW;
import java.io.*;
import java.util.ArrayList;

public class Backup
{
    // Diretório para armazenar backups
    private static final String BACKUP = ".\\backups";
    // Diretório para armazenar dados originais
    private static final String DATA = ".\\dados";

    public Backup()
    {
        // Garantir que os diretórios de backup e dados existem
        createDirectory(BACKUP);
        createDirectory(DATA);
    }

    private void createDirectory(String path)
    {
        // Cria o diretório especificado caso ele não exista
        File dir = new File(path);
        if (!dir.exists())
        {
            dir.mkdirs();
        }
    }

    private byte[] serializeFiles(File[] files)
    {
        // Serializa os arquivos em um array de bytes
        try (ByteArrayOutputStream baos = new ByteArrayOutputStream();
             DataOutputStream dos = new DataOutputStream(baos))
        {
            for (File file : files)
            {
                if (file.isFile())
                {
                    // Escreve o nome do arquivo
                    dos.writeUTF(file.getName());
                    // Lê o conteúdo do arquivo
                    byte[] file_bytes = readFile(file);
                    // Escreve o tamanho e o conteúdo do arquivo
                    dos.writeInt(file_bytes.length);
                    dos.write(file_bytes);
                }
            }
            return baos.toByteArray();
        }
        catch (IOException e)
        {
            System.err.println("Erro" + e.getMessage());
            return null;
        }
    }

    private byte[] readFile(File file) throws IOException
    {
        // Lê o conteúdo de um arquivo como array de bytes
        try (FileInputStream fis = new FileInputStream(file))
        {
            return fis.readAllBytes();
        }
    }

    private void writeFile(String filepath, byte[] data)
    {
        // Escreve um array de bytes em um arquivo especificado
        try (FileOutputStream fos = new FileOutputStream(filepath))
        {
            fos.write(data);
        }
        catch (IOException e)
        {
            System.err.println("Erro " + e.getMessage());
        }
    }

    public double calculateCompressRatio(byte[] data_o, byte[] data_c)
    {
        // Calcula a taxa de compressão entre os dados originais e comprimidos
        int tamanho_o = data_o.length;
        int tamanho_c = data_c.length;
        return (1 - ((double) tamanho_c / tamanho_o)) * 100;
    }

    public void createBackup(String backup_file)
    {
        try
        {
            // Garante que o diretório de backup existe
            createDirectory(BACKUP);
            File data = new File(DATA);

            // Cria subdiretório para o backup atual
            String sub_dir_path = BACKUP + "\\" + backup_file.replace(".db", "");
            createDirectory(sub_dir_path);

            if (data.exists())
            {
                File[] files = data.listFiles();
                if (files != null)
                {
                    // Serializa e comprime os arquivos
                    byte[] data_orig = serializeFiles(files);
                    byte[] data_c = LZW.codifica(data_orig);

                    // Calcula e exibe a taxa de compressão
                    double compressRatio = calculateCompressRatio(data_orig, data_c);
                    System.out.printf("Taxa: %.2f%%\n", compressRatio);

                    // Salva os dados comprimidos no subdiretório do backup
                    writeFile(sub_dir_path + "\\" + backup_file, data_c);
                }
            }
        }
        catch (Exception e)
        {
            System.out.println("Erro: " + e.getMessage());
        }
    }

    public void restoreBackup(String backup_file)
    {
        // Localiza o arquivo de backup no diretório de backups
        File backup = new File(BACKUP + "\\" + backup_file);

        if (!backup.exists())
        {
            File sub_dir = new File(BACKUP + "\\" + backup_file.replace(".db", ""));
            backup = new File(sub_dir, backup_file);
        }

        if (backup.exists()) {
            try
            {
                // Lê e decodifica os dados do backup
                byte[] backup_data = readFile(backup);
                backup_data = LZW.decodifica(backup_data);

                try (ByteArrayInputStream bais = new ByteArrayInputStream(backup_data);
                     DataInputStream dis = new DataInputStream(bais))
                {
                    // Limpa o diretório de dados antes da restauração
                    clearDirectory(DATA);

                    while (dis.available() > 0)
                    {
                        // Lê e recria cada arquivo do backup
                        String file_n = dis.readUTF();
                        int file_t = dis.readInt();
                        byte[] file_bytes = new byte[file_t];
                        dis.readFully(file_bytes);
                        writeFile(DATA + "\\" + file_n, file_bytes);
                    }
                }
            }
            catch (Exception e)
            {
                System.err.println("Erro ao recuperar o backup: " + e.getMessage());
            }
        }
    }

    private void clearDirectory(String dir_path)
    {
        // Remove todos os arquivos e subdiretórios do diretório especificado
        File dir = new File(dir_path);
        if (dir.exists())
        {
            File[] files = dir.listFiles();
            if (files != null)
            {
                for (File file : files)
                {
                    if (file.isFile())
                    {
                        file.delete();
                    }
                    else if (file.isDirectory())
                    {
                        clearDirectory(file.getPath());
                        file.delete();
                    }
                }
            }
        }
    }

    public ArrayList<String> listBackups()
    {
        // Lista os nomes dos subdiretórios no diretório de backups
        ArrayList<String> backups = new ArrayList<>();

        File backup = new File(BACKUP);
        File[] sub_dirs = backup.listFiles(File::isDirectory);

        if (sub_dirs != null)
        {
            for (File sub_dir : sub_dirs)
            {
                backups.add(sub_dir.getName());
            }
        }
        return backups;
    }
}
