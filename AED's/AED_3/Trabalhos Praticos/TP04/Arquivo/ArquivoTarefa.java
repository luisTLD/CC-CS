package Arquivo;

import Arvore.*;
import ListaInvertida.ElementoLista;
import ListaInvertida.StopWords;
import Modelo.*;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;

public class ArquivoTarefa extends Arquivo<Tarefa>
{
    Arquivo<Tarefa> arq_tarefa; // Arquivo de tarefas
    ArvoreBMais<ParIdId> indice_indireto_id; // Índice indireto para armazenar pares (id_categoria, id_tarefa)
    ArvoreBMais<ParIDRotulocID> arvore; // Árvore B+ para associação de rótulos com tarefas
    StopWords stopWords; // Gerenciador de stopwords

    // Construtor que inicializa o arquivo de tarefas e os índices
    public ArquivoTarefa() throws Exception
    {
        super("tarefas", Tarefa.class.getConstructor());
        indice_indireto_id = new ArvoreBMais<>(ParIdId.class.getConstructor(),5, "./dados/indice_indireto_id.btree.db");
        arvore = new ArvoreBMais<>(ParIDRotulocID.class.getConstructor(), 5, "./dados/ArvoreTarefasRotulos.btree.db");        
        stopWords = new StopWords(); // Inicializa a estrutura para lidar com stopwords
    }

    // Cria uma nova tarefa, atualiza os índices e insere as stopwords associadas
    @Override
    public int create(Tarefa c) throws Exception
    {
        int id = super.create(c); // Cria a tarefa e obtém o ID gerado
        indice_indireto_id.create(new ParIdId(c.getIdCategoria(), id)); // Adiciona ao índice indireto
        ArrayList<Integer> id_rotulos = c.getIDRotulo(); // Obtém os IDs dos rótulos
        for(int i = 0; i < id_rotulos.size(); i++) 
        {
            arvore.create(new ParIDRotulocID(id_rotulos.get(i), id)); // Associa rótulos às tarefas
        }
        stopWords.inserir(c.getNome(), id); // Insere palavras associadas à tarefa no gerenciador de stopwords
        return id;
    }
    
    // Lê todas as tarefas de uma categoria específica usando o índice indireto
    public ArrayList<Tarefa> readAll(int id) throws Exception
    {
        ArrayList<ParIdId> p = indice_indireto_id.read(new ParIdId(id, -1)); // Busca no índice indireto
        ArrayList<Tarefa> t = new ArrayList<>(); // Lista para armazenar as tarefas encontradas
        Arquivo<Tarefa> arq = new Arquivo<>("tarefas", Tarefa.class.getConstructor());
        
        if (p != null && !p.isEmpty())
        {
            for (ParIdId p_aux : p)
            {
                Tarefa tarefa = (Tarefa) arq.read(p_aux.getId2()); // Obtém a tarefa pelo ID
                if (tarefa != null)
                {
                    t.add(tarefa); // Adiciona à lista de tarefas
                }
            }
        }
        return t;
    }
    
    // Lê tarefas associadas a um rótulo específico
    public ArrayList<Tarefa> read(ParRotuloId parRotuloId) throws Exception 
    {
        ArrayList<Tarefa> t = new ArrayList<>();
        ArrayList<ParIDRotulocID> id = arvore.read(new ParIDRotulocID(parRotuloId.getId())); // Busca associações de rótulos
        for(int i = 0; i < id.size(); i++) 
        {
            t.add(super.read(id.get(i).getId2())); // Adiciona as tarefas à lista
        }
        return t;
    }

    // Deleta uma tarefa, removendo-a dos índices e stopwords
    public boolean delete(Tarefa tarefa) 
    {
        boolean result = false;
        try 
        {
            result = super.delete(tarefa.getId()) ? indice_indireto_id.delete(new ParIdId(tarefa.getIdCategoria(), tarefa.getId())) : false;
            String[] chaves = stopWords.stopWordsCheck(tarefa.getNome()); // Obtém palavras associadas à tarefa
            ArrayList<Integer> id_rotulos = tarefa.getIDRotulo(); // Obtém os IDs dos rótulos
            for(int i = 0; i < id_rotulos.size(); i++) 
            {
                arvore.delete(new ParIDRotulocID(id_rotulos.get(i), tarefa.getId())); // Remove as associações de rótulos
            }
            for(int i = 0; i < chaves.length; i++) {
                chaves[i] = chaves[i].toLowerCase();
                stopWords.lista.delete(chaves[i], tarefa.getId()); // Remove palavras associadas
            }
            stopWords.lista.decrementaEntidades(); // Atualiza contadores no gerenciador de stopwords
        } catch(Exception e) {
            System.out.println(e.getMessage()); // Tratamento de erro
        }
        return result;
    }

    // Atualiza uma tarefa e ajusta as associações no gerenciador de stopwords
    public boolean update(Tarefa tarefa, Tarefa update) 
    {
        boolean result = false;
        update.setId(tarefa.getId()); // Mantém o ID original da tarefa

        try 
        {
            String[] chaves = stopWords.stopWordsCheck(tarefa.getNome()); // Obtém palavras da tarefa antiga
            for(int i = 0; i < chaves.length; i++) 
            {
                chaves[i] = chaves[i].toLowerCase();
                stopWords.lista.delete(chaves[i], tarefa.getId()); // Remove palavras da tarefa antiga
            }
            stopWords.inserir(update.getNome(), update.getId()); // Insere palavras da nova tarefa
            result = super.update(update); // Atualiza a tarefa no arquivo
        } catch(Exception e) 
        {
            System.out.println(e.getMessage()); // Tratamento de erro
        }
        return result;
    }

    // Lista tarefas baseadas em palavras-chave, utilizando stopwords
    public ArrayList<Tarefa> listar(String titulo) throws Exception 
    {
        ArrayList<ElementoLista> elementos = new ArrayList<>();
        String[] chaves = stopWords.stopWordsCheck(titulo); // Divide o título em palavras-chave
        for(int i = 0; i < chaves.length; i++) 
        {
            if(!chaves[i].isEmpty()) 
            {
                try 
                {
                    ElementoLista[] elementos_listas = stopWords.lista.read(chaves[i]); // Busca elementos na lista invertida
                    if(elementos_listas != null) {
                        for(ElementoLista elemento : elementos_listas) 
                        {
                            float frequencia = elemento.getFrequencia(); // Calcula a relevância da tarefa
                            float idf = stopWords.lista.numeroEntidades() / (float) elementos_listas.length;
                            ElementoLista elementoAux = new ElementoLista(elemento.getId(), frequencia * idf);
                            boolean existe = false;
                            for(ElementoLista e : elementos) 
                            {
                                if(e.getId() == elementoAux.getId()) 
                                {
                                    e.setFrequencia(e.getFrequencia() + elementoAux.getFrequencia());
                                    existe = true;
                                    break;
                                }
                            }
                            if(!existe) 
                            {
                                elementos.add(elementoAux);
                            }
                        }
                    }
                } catch(Exception e) 
                {
                    System.out.println(e.getMessage());
                }
            }
        }

        // Ordena os elementos pela relevância em ordem decrescente
        Collections.sort(elementos, new Comparator<ElementoLista>() 
        {
            @Override
            public int compare(ElementoLista e1, ElementoLista e2) 
            {
                return Float.compare(e2.getFrequencia(), e1.getFrequencia());
            }
        });

        ArrayList<Tarefa> tarefas = new ArrayList<>();
        for(ElementoLista elemento : elementos) 
        {
            tarefas.add(super.read(elemento.getId())); // Adiciona as tarefas à lista
        }

        return tarefas;
    }

    // Atualiza os rótulos associados a uma tarefa
    public boolean updateRotulos(Tarefa tarefa, ArrayList<Integer> removed, ArrayList<Integer> added) 
    {
        boolean result = false;
        try 
        {
            ArrayList<Integer> idRotulo = tarefa.getIDRotulo(); // Obtém os rótulos atuais da tarefa
            for(Integer removeId : removed) 
            {
                if(idRotulo.contains(removeId)) 
                {
                    arvore.delete(new ParIDRotulocID(removeId, tarefa.getId())); // Remove rótulo do índice
                    idRotulo.remove(removeId);
                } else 
                {
                    System.out.println("Rótulo não encontrado");
                }
            }
            for(Integer addId : added) 
            {
                if(!idRotulo.contains(addId)) 
                {
                    idRotulo.add(addId); // Adiciona o novo rótulo
                    arvore.create(new ParIDRotulocID(addId, tarefa.getId())); // Atualiza o índice
                } else 
                {
                    System.out.println("Rótulo já existente");
                }
            }
            tarefa.setIdRotulos(idRotulo); // Atualiza os rótulos da tarefa
            result = super.update(tarefa); // Persiste as alterações no arquivo
        } catch(Exception e) 
        {
            System.out.println(e.getMessage());
        }
        return result;
    }
}
