package service;

import java.util.List;

import dao.IngredienteDAO;
import model.Cliente;
import model.Ingrediente;
import model.Receita;

public class IngredienteService {
    private IngredienteDAO ingredienteDAO;

    public IngredienteService() {
        ingredienteDAO = new IngredienteDAO(); 
    }

    public void cadastrarIngrediente(int id, String nome, float preco) {
        Ingrediente ingrediente = new Ingrediente();
        ingrediente.setNome(nome);
        ingrediente.setPreco(preco);
        
        ingredienteDAO.cadastrarIngrediente(ingrediente);
    }

    public void atualizarIngrediente(int id, String nome, float preco) {
        Ingrediente ingrediente = new Ingrediente();
        ingrediente.setNome(nome);
        ingrediente.setPreco(preco);
        
        ingredienteDAO.atualizarIngrediente(ingrediente);
    }

    public void deletarIngrediente(int id) {
        ingredienteDAO.deletarIngrediente(id);
    }
    public String replaceIngredientes(String html) {
    	String ingrediente = new String();
    	String novaDiv = new String();
    	List<Ingrediente> todosIngredientes = ingredienteDAO.listarIngredientes();
    	 for ( int i = 0; i < todosIngredientes.size(); i++ ) {
    		// Criar a string com a Div
             ingrediente =  "<label><input type=\"checkbox\" name=\"ingredientes\" value=oping>  oping  <input type=\"number\" name=\"quantidade\" value=\"0\" min=\"0\"></label><br>\r\n";
             //System.out.println(todosIngredientes.get(i).getNome());
 		    
             // Editar a receita
             ingrediente = ingrediente.replace("oping", todosIngredientes.get(i).getNome());             
             // Concatenar varias Divs
             novaDiv = novaDiv + ingrediente;
            }
             
             // Editar o front end com o Java
             html = html.replace("<ingredientesSub>", novaDiv);        
             
             // Retorna a string como HTML
             return html;
    }
    public String replaceIngredientesPages(String html, String aux, String nome) {
    		html = html.replace("<createModalIngredientes>", aux);
    		
    		String nomeUsuario = new String();
    		
    		 nomeUsuario = "<h3>SeuNome</h3>\r\n";
    		 
             // Editar o front end com o Java
             nomeUsuario = nomeUsuario.replace("SeuNome", nome);
             html = html.replace("<NomeUsuario>", nomeUsuario);   

             // Retorna a string como HTML
             return html;
    }


}
