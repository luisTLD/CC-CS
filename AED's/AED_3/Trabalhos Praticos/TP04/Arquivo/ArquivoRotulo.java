package Arquivo;

import Arvore.*;
import Modelo.*;
import java.util.ArrayList;

public class ArquivoRotulo extends Arquivo<Rotulo> {
    ArvoreBMais<ParRotuloId> arvoreB;

    // Criando o arquivo de rótulo
    public ArquivoRotulo()throws Exception
    {
        super("ArquivoRotulo", Rotulo.class.getConstructor());
        try
        {
            arvoreB = new ArvoreBMais<>(ParRotuloId.class.getConstructor(), 5, "./dados/ArvoresRotulos");
        }catch(Exception e)
        {
            System.out.println(e.getMessage());
            throw new Exception();
        }
    }

    // Método público para a criação de rótulo. Retorna o ID do rótulo criado
    public int create(String nome_rotulo)throws Exception
    {
        Rotulo rotulo = new Rotulo(nome_rotulo);
        return this.create1(rotulo);
    }
    
    // Método privado para a criação de rótulo. Retorna o ID do rótulo criado
    private int create1(Rotulo rotulo) throws Exception
    {
        int id = super.create(rotulo); // Cria o rótulo no arquivo base e obtém o ID
        rotulo.setId(id); // Define o ID no objeto rótulo
        try
        {
            arvoreB.create(new ParRotuloId(rotulo.getNome(),rotulo.getId())); // Adiciona o rótulo ao índice
        }catch(Exception e)
        {
            System.out.println("Erro na criação de um novo rótulo");
            System.out.println(e.getMessage());
        }
        return id;
    } 
    
    // Método para leitura de tarefas associadas a um rótulo. Retorna as tarefas encontradas
    public ArrayList<Tarefa> read(String nome_rotulo)throws Exception
    {
        ArrayList<Tarefa> t = new ArrayList<>();
        ArquivoTarefa tarefas = new ArquivoTarefa();
        try
        {
            ArrayList<ParRotuloId> rotulo = arvoreB.read(new ParRotuloId(nome_rotulo));
        
            // Verifica se o rótulo existe
            if(rotulo.isEmpty())
            {
                throw new Exception("Rótulo inexistente");
            }
            t = tarefas.read(rotulo.get(0)); // Lê as tarefas associadas ao rótulo
        }catch(Exception e)
        {
            System.out.println("Erro na leitura do arquivo");
            System.out.println(e.getMessage());
        }
        return t;
    }

    // Método de atualização do nome de um rótulo. Retorna true se a atualização for bem-sucedida
    public boolean update(String nome_rotulo, String novo_rotulo)throws Exception
    {
        Rotulo rt = new Rotulo(novo_rotulo); // Cria um novo objeto rótulo com o nome atualizado
        
        try
        {
            ArrayList<ParRotuloId> rotulo = arvoreB.read(new ParRotuloId(nome_rotulo));
            
            // Verifica se o rótulo existe
            if(rotulo.isEmpty())
            {
                throw new Exception("Rótulo inexistente");
            }
            rt.setId(rotulo.get(0).getId()); // Atualiza o ID do rótulo
            
            if(super.update(rt))
            { // Atualiza o rótulo no arquivo base
                System.out.println("Atualização realizada");
            }

            // Remove o rótulo antigo do índice e adiciona o novo
            arvoreB.delete(rotulo.get(0));
            arvoreB.create(new ParRotuloId(rt.getNome(), rt.getId()));
        }
        catch (Exception e)
        {
            System.out.println("Erro na atualização do arquivo");
            System.out.println(e.getMessage());
        }
        
        return true;
    }

    // Método para deletar um rótulo. Retorna true se a exclusão for bem-sucedida
    public boolean delete(String nome_rotulo) throws Exception
    {
        try
        {
            ArrayList<ParRotuloId> rotulo = arvoreB.read(new ParRotuloId(nome_rotulo));

            // Verifica se o rótulo existe
            if(rotulo.isEmpty())
            {
                throw new Exception("Rótulo inexistente");
            }

            // Verifica se existem tarefas associadas ao rótulo
            ArquivoTarefa tarefas = new ArquivoTarefa();
            ArrayList<Tarefa> t = tarefas.read(rotulo.get(0));
    
            if(!t.isEmpty())
                throw new Exception("Existem tarefas associadas a este rótulo");
            
            // Remove o rótulo do arquivo base e do índice
            return super.delete(rotulo.get(0).getId()) ? arvoreB.delete(rotulo.get(0)) : false;
        }catch(Exception e)
        {
            System.out.println("Erro ao deletar");
            System.out.println(e.getMessage());
        }
        return false;
    }

    // Lista todos os rótulos. Retorna um ArrayList com os rótulos encontrados
    public ArrayList<Rotulo> listar() throws Exception
    {
        ArrayList<Rotulo> rotulos = new ArrayList<>();
        try
        {
            rotulos = super.readAll(); // Lê todos os rótulos do arquivo base

            // Verifica se existem rótulos
            if(rotulos.isEmpty())
                throw new Exception("Nenhum rótulo foi criado");
            
            // Exibe os rótulos encontrados
            for(int i = 0; i<rotulos.size(); i++)
            {
                System.out.println("Índice: " + rotulos.get(i).getId() + " Nome do rótulo: " + rotulos.get(i).getNome());
            }
        }catch(Exception e)
        {
            System.out.println(e.getMessage());
        }
        return rotulos;
    }

}
