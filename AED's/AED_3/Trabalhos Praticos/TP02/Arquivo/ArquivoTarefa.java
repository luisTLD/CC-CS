package Arquivo;

import java.util.ArrayList;
import Arvore.*;
import Modelo.*;

public class ArquivoTarefa extends Arquivo<Tarefa>
{
    Arquivo<Tarefa> arq_tarefa; // Arquivo de tarefas
    ArvoreBMais<ParIdId> indice_indireto_id; // Índice indireto para armazenar pares (id_categoria, id_tarefa)

    // Construtor que inicializa o arquivo de tarefas e o índice indireto
    public ArquivoTarefa() throws Exception
    {
        super("tarefas", Tarefa.class.getConstructor());
        indice_indireto_id = new ArvoreBMais<>(
            ParIdId.class.getConstructor(), 
            5, 
            "./dados/indice_indireto_id.btree.db"
        );
    }

    // Cria uma nova tarefa e atualiza o índice indireto
    @Override
    public int create(Tarefa c) throws Exception
    {
        int id = super.create(c); // Cria a tarefa e obtém o ID
        indice_indireto_id.create(new ParIdId(c.getIdCategoria(), id)); // Adiciona ao índice indireto
        return id;
    }

    // Lê todas as tarefas com base no id_categoria pela Hash
    public ArrayList<Tarefa> readAll(int id) throws Exception
    {
        ArrayList<ParIdId> p = indice_indireto_id.read(new ParIdId(id, -1)); // Busca no índice indireto
        ArrayList<Tarefa> t = new ArrayList<>(); // ArrayList com as tarefas que forem achadas pela hash
        Arquivo<Tarefa> arq = new Arquivo<>("tarefas", Tarefa.class.getConstructor());

        if (p != null && !p.isEmpty())
        {
            for (ParIdId p_aux : p)
            {
                Tarefa tarefa = (Tarefa) arq.read(p_aux.getId2()); // id2 == id_tarefa, buscando por ParIDEndereco
                if (tarefa != null)
                {
                    t.add(tarefa); 
                }
            }
        }
        return t;
    }
    
    // Deleta uma tarefa e remove do índice indireto
    public boolean delete(int id) throws Exception
    {
        boolean result = false;
        Tarefa obj = super.read(id); // Lê a tarefa
        if(obj != null)
        {
            if(indice_indireto_id.delete(new ParIdId(obj.getIdCategoria(), obj.getId())))
            {
                result = super.delete(obj.getId()); // Deleta a tarefa
            } 
        } 
        return result;
    }

    // Atualiza uma tarefa e ajusta o índice indireto se necessário
    @Override
    public boolean update(Tarefa novaTarefa) throws Exception
    {
        Tarefa TarefaVelho = read(novaTarefa.getId()); // Lê a tarefa atual
        if(super.update(novaTarefa)) // Atualiza a tarefa
        {
            if(novaTarefa.getId() == TarefaVelho.getId()) // Se o ID não mudou
            {
                indice_indireto_id.delete(new ParIdId(TarefaVelho.getIdCategoria(), TarefaVelho.getId())); // Remove entrada antiga
                indice_indireto_id.create(new ParIdId(novaTarefa.getIdCategoria(), novaTarefa.getId())); // Cria entrada nova
            }
            return true;
        }
        return false;
    } 
}
