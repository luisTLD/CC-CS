package Arquivo;

import java.util.ArrayList;
import Arvore.*;
import Modelo.*;

public class ArquivoCategoria extends Arquivo<Categoria>
{
    Arquivo<Categoria> arq_categoria; // Arquivo de categorias
    ArvoreBMais<ParNomeId> indice_indireto_nome; // Índice indireto para armazenar pares (nome_categoria, id_categoria)

    // Construtor que inicializa o arquivo de categorias e o índice indireto
    public ArquivoCategoria() throws Exception
    {
        super("categorias", Categoria.class.getConstructor());
        indice_indireto_nome = new ArvoreBMais<>(
            ParNomeId.class.getConstructor(),
            5,
            "./dados/indice_indireto_nome.btree.db"
        );
    }

    // Cria uma nova categoria e atualiza o índice indireto
    @Override
    public int create(Categoria c) throws Exception
    {
        int id = super.create(c); // Cria a categoria e obtém o ID
        indice_indireto_nome.create(new ParNomeId(c.getNome(), id)); // Adiciona ao índice indireto
        return id;
    }

    // Lê uma categoria com base no nome
    public Categoria read(String n) throws Exception
    {
        ArrayList<ParNomeId> p = indice_indireto_nome.read(new ParNomeId(n, -1)); // Busca no índice indireto
        return super.read(p.get(0).getId()); // Lê a categoria usando o ID encontrado
    }

    // Deleta uma categoria com base no nome
    public boolean delete(String n) throws Exception
    {
        return delete(read(n).getId()); // Lê o ID da categoria e a deleta
    }

    // Deleta uma categoria com base no ID
    public boolean delete(int id) throws Exception
    {
        boolean result = false;
        Categoria obj = super.read(id); // Lê a categoria
        if (obj != null)
        {
            if (indice_indireto_nome.delete(new ParNomeId(obj.getNome(), obj.getId()))) // Remove do índice indireto
            {
                result = super.delete(obj.getId()); // Deleta a categoria
            }
        }
        return result;
    }

    // Listar todas categorias
    public void list() 
    {
        try
        {
            System.out.println();
            indice_indireto_nome.show();
        }
        catch (Exception e)
        {
            System.err.println("Erro no sistema");
        }
    }

    // Atualiza uma categoria e ajusta o índice indireto se necessário
    @Override
    public boolean update(Categoria novaCategoria) throws Exception
    {
        Categoria categoriaVelha = read(novaCategoria.getId()); // Lê a categoria atual
        if (super.update(novaCategoria)) // Atualiza a categoria
        {
            if (novaCategoria.getId() == categoriaVelha.getId()) // Se o ID não mudou
            {
                indice_indireto_nome.delete(new ParNomeId(categoriaVelha.getNome(), categoriaVelha.getId())); // Remove entrada antiga
                indice_indireto_nome.create(new ParNomeId(novaCategoria.getNome(), novaCategoria.getId())); // Cria entrada nova
            }
            return true;
        }
        return false;
    }
}
