package service;

import java.util.List;
import java.util.Collections;

import dao.ClienteDAO;
import dao.IngredienteDAO;
import dao.ReceitaDAO;
import model.Cliente;
import model.Ingrediente;
import model.Receita;

public class ReceitaService {
    public ReceitaDAO receitaDAO;
    public ClienteDAO clienteDAO;
    public static IngredienteDAO ingredienteDAO = new IngredienteDAO();
    public static ClienteService clienteService = new ClienteService();

    public ReceitaService() {
        // Inicializa a instância de ReceitaDAO
        receitaDAO = new ReceitaDAO(); 
        clienteDAO = new ClienteDAO();
    }

    public void cadastraReceita(String nome, String modoDePreparo, String ingredientes,String img_url,Cliente cliente) {
        	// Cria um novo objeto Receita e seta os valores no construtor
    		System.out.println(cliente.getIdCliente());
            Receita receita = new Receita();
            receita.setNome(nome);
            receita.setIngredientes(ingredientes);
            receita.setModoDePreparo(modoDePreparo);
            receita.setImagem(img_url);
            receita.setIdCliente(cliente.getIdCliente());
            
  
            receitaDAO.cadastrarReceita(receita.getNome(),receita.getIngredientes(),receita.getModoDePreparo(),receita.getImagem(),receita.getIdCliente());
    }
    
    // Apenas chamar a função que esta na DAO, para retornar a lista e acessar na Aplicação
    public List<Receita> retornarTodasReceitas(){
    	return receitaDAO.getTodasReceitas();
    }
    
    public List<Receita> retornarReceitasDoCliente(Cliente cliente){
    	return receitaDAO.receitasUsuario(cliente);
    }
    
    public List<Cliente> retornarTodosClientes(){
    	return clienteDAO.getTodosClientes();
    }
 
    
    // Função para printar no Console todas as receitas do SQL, chamar apos chamar listarReceitas
    public void printarReceitas(List<Receita> receitas) {
    	for (Receita receita : receitas) {
            System.out.println("Nome da receita: " + receita.getNome());
            System.out.println("Ingredientes: " + receita.getIngredientes());
            System.out.println("Modo de preparo: " + receita.getModoDePreparo());
            System.out.println("Url da imagem: " + receita.getImagem());

            System.out.println("--------------------------");
        }
    }
    
    //adiciona receitas do bd para o front end yourRecipes
    public String replaceYourRecipes(String html, Cliente cliente) {
    	String receita = new String();
    	String novaDiv = new String();
    	List<Receita> todasReceitas = retornarReceitasDoCliente(cliente);
    	
    	// Printar o nome do usuario
    	String nomeUsuario = new String();
		nomeUsuario = "<h3>SeuNome</h3>\r\n";		 
        // Editar o front end com o Java
        nomeUsuario = nomeUsuario.replace("SeuNome", cliente.getNome());
        html = html.replace("<NomeUsuario>", nomeUsuario);
    	
    	 for ( int i = 0; i < todasReceitas.size(); i++ ) {
    		// Criar a string com a Div
             receita = "<div class=\"card\" style=\"width: 18rem; margin: 10px;\">\r\n"
 		    		+ "<img src=\"img/"+ todasReceitas.get(i).imagem +"\" class=\"card-img-top\" alt=\"..\" style=\"height: 16rem; width: 100%;\">\r\n" + "<div class=\"card-body\">\r\n"
             		+ "<h5 class=\"card-title\">Nome da receita</h5>\r\n"
             		+ "<p class=\"card-text\">cliente</p>\r\n" 
             		//<!-- Formulário que envia o nome da receita -->
             		+ "<form action=\"/ver-receita\" method=\"post\" id=\"viewRecipeForm\">"
                    + "<input type=\"hidden\" name=\"recipeName\" value=\"Nome da receita\">"
             		+ "<button type=\"submit\" class=\"btn btn-primary\" data-bs-toggle=\"modal\" data-bs-target=\"#recipeModal\">Ver Receita</button>\r\n"
             		+ "</form>"
             		+ "</div>\r\n"
             		+ "</div>";            
    		    
             // Editar a receita
             receita = receita.replace("Nome da receita", todasReceitas.get(i).getNome());
             // receita = receita.replace("Seu modo de preparo", todasReceitas.get(i).getModoDePreparo());
             receita = receita.replace("cliente", cliente.getNome());
             
             // Concatenar varias Divs
             novaDiv = novaDiv + receita;
             }
             
             // Editar o front end com o Java
             html = html.replace("<CaixaSuasReceitas>", novaDiv);
             
             // Retorna a string como HTML
             return html;
    }
    
    // alterar features pelas receitas do bd
    public String replaceFeatures(String html,Cliente cliente) {
    	String receita = new String();
    	String novaDiv = new String();
    	List<Receita> todasReceitas = retornarTodasReceitas();
    	
    	// Printar o nome do usuario
    	String nomeUsuario = new String();
		nomeUsuario = "<h3>SeuNome</h3>\r\n";		 
        // Editar o front end com o Java
        nomeUsuario = nomeUsuario.replace("SeuNome", cliente.getNome());
        html = html.replace("<NomeUsuario>", nomeUsuario);
    	
    	int loop = todasReceitas.size();
    	loop = loop > 4 ? 4 : loop;
    	loop--;
    	// loop para retornar as 10 ultimas receitas
    	int pos = todasReceitas.size() - 1;
    	while ( loop >= 0 ) {
    		// codigo
    		receita = "<div class=\"card\" style=\"width: 18rem; margin: 10px;\">\r\n"
		    		+ "<img src=\"img/"+ todasReceitas.get(pos).imagem +"\" class=\"card-img-top\" alt=\"..\" style=\"height: 16rem; width: 100%;\">\r\n" + "<div class=\"card-body\">\r\n"
             		+ "<h5 class=\"card-title\">Nome da receita</h5>\r\n"
             		+ "<p class=\"card-text\">cliente</p>\r\n" 
             		//<!-- Formulário que envia o nome da receita -->
             		+ "<form action=\"/ver-receita\" method=\"post\" id=\"viewRecipeForm\">"
                    + "<input type=\"hidden\" name=\"recipeName\" value=\"Nome da receita\">"
             		+ "<button type=\"submit\" class=\"btn btn-primary\" data-bs-toggle=\"modal\" data-bs-target=\"#recipeModal\">Ver Receita</button>\r\n"
             		+ "</div>\r\n"
             		+ "</form>"
             		+ "</div>";		
    		
    		Cliente aux = clienteService.clientePorId(todasReceitas.get(pos).getIdCliente());
    		
    		// Editar a receita
    		receita = receita.replace("Nome da receita", todasReceitas.get(pos).getNome());
    		receita = receita.replace("cliente", aux.getNome());
    		
    		// Concatenar varias Divs
    		novaDiv = novaDiv + receita;
    	  		
    		loop--;
    		pos--;
    	}
            
             // Editar o front end com o Java
             html = html.replace("<CaixaSuasReceitas>", novaDiv);
             
             // Retorna a string com o HTML
             return html;
    }

  
    // Pesquisar receita
    public String pesquisaReceita(String html, String nome) {
		// String auxiliares para criar a nova div
    	String receita = new String();
    	String novaDiv = new String();
    	
    	// Lista com todas as receitas do BD para pesquisa
    	List<Receita> todasReceitas = retornarTodasReceitas();
    	
    	// Printar o nome do usuario
    	String nomeUsuario = new String();
		nomeUsuario = "<h3>SeuNome</h3>\r\n";		 
        // Editar o front end com o Java
        nomeUsuario = nomeUsuario.replace("SeuNome", nome);
        html = html.replace("<NomeUsuario>", nomeUsuario);

	 // Loop por todas as receitas para encontrar a procurada
   	 for ( int i = 0; i < todasReceitas.size(); i++ ) {
			// codigo
         receita = "<div class=\"card\" style=\"width: 18rem; margin: 10px;\">\r\n"
		    		+ "<img src=\"img/"+ todasReceitas.get(i).imagem +"\" class=\"card-img-top\" alt=\"..\" style=\"height: 16rem; width: 100%;\">\r\n"	+ "<div class=\"card-body\">\r\n"
          		+ "<h5 class=\"card-title\">Nome da receita</h5>\r\n"
          		+ "<p class=\"card-text\">cliente</p>\r\n" 
          		//<!-- Formulário que envia o nome da receita -->
          		+ "<form action=\"/ver-receita\" method=\"post\" id=\"viewRecipeForm\">"
                 + "<input type=\"hidden\" name=\"recipeName\" value=\"Nome da receita\">"
                 + "</form>"
          		+ "<button type=\"submit\" class=\"btn btn-primary\" data-bs-toggle=\"modal\" data-bs-target=\"#recipeModal\">Ver Receita</button>\r\n"
          		+ "</div>\r\n"
          		+ "</div>";

			// Editar a receita
			if(nome == todasReceitas.get(i).getNome()) {
				Cliente aux = clienteService.clientePorId(todasReceitas.get(i).getId());
				// Encontrou a receita procurada, e adiciou na div
				receita = receita.replace("Nome da receita", todasReceitas.get(i).getNome());
				receita = receita.replace("cliente", aux.getNome());
				//receita = receita.replace("Seu modo de preparo", todasReceitas.get(i).getModoDePreparo());
			
				// Sair do loop
				i = todasReceitas.size();			
			}

			// Concatenar varias Divs
			novaDiv = novaDiv + receita;
		}

		// Editar o front end com o Java
		html = html.replace("<CaixaSuasReceitas>", novaDiv);

		// Retorna a string como HTML
		return html;
	}

	
	// Adicionar os ingredientes do BD
	public String replaceIngredientes(String html, Receita receita, String nome) {
		// Replace para editar os textos
		html = html.replace("Nome da receita", receita.getNome());
		html = html.replace("Nome dos ingredientes",  receita.getIngredientes());
		html = html.replace("Seu modo de preparo", receita.getModoDePreparo());	
		//html = html.replace("imgReceitaEscolhida", receita.getImagem());
		
		// Printar o nome do usuario
    	String nomeUsuario = new String();
		nomeUsuario = "<h3>SeuNome</h3>\r\n";		 
        // Editar o front end com o Java
        nomeUsuario = nomeUsuario.replace("SeuNome", nome);
        html = html.replace("<NomeUsuario>", nomeUsuario);
        
        String[] array = receita.getIngredientes().split(", ");
        float total = 0;
        
        List<Ingrediente> listaIngrediente = ingredienteDAO.listarIngredientes();
        
        // Percorrer a lista de todos os ingredientes
        for ( Ingrediente aux : listaIngrediente ) {

        	// Percorrer lista de ingredientes desejados
        	for ( String ver : array ) {
        		
        		String[] teste = (ver.toLowerCase()).split("_");
        		
        		if ( (aux.getNome().toLowerCase()).compareTo(teste[0]) == 0 ) {
        			total = total + aux.getPreco()*Integer.parseInt(teste[1]);
        		}
        	}
        }
        
        html = html.replace("totalPreco", Float.toString(total));
		// Retorna a string com o HTML
        
		return html;
	}
	
	
	
    // Retornar a Receita em formato de instancia
    public Receita procurarReceita(String nome) {
    	List<Receita> receitas = retornarTodasReceitas();
    	Receita resp = new Receita();
    	
    	// Procurar a receita
    	for (Receita receita : receitas) {
            if ( receita.getNome().equals(nome) ) {
            	resp = receita;
            	break;
            }
        }
    	
    	return resp;
    }

    //Pesquisar receitas pelo input e adicionar ao front
    public String replacePesquisaFeatureRecipes(String html, String input, String nome){    	
    	// String auxiliares para criar a nova div
    	String receita = new String();
    	String novaDiv = new String();
    	
    	// Printar o nome do usuario
    	String nomeUsuario = new String();
		nomeUsuario = "<h3>SeuNome</h3>\r\n";		 
        // Editar o front end com o Java
        nomeUsuario = nomeUsuario.replace("SeuNome", nome);
        html = html.replace("<NomeUsuario>", nomeUsuario);
    	
    	// Lista com todas as receitas do BD para pesquisa
    	List<Receita> todasReceitas = retornarTodasReceitas();
    	
    	for ( int i = 0; i < todasReceitas.size(); i++ ) {
    		// Verificar se o nome da receita começa com o input de pesquisa do usuario
    		if ( todasReceitas.get(i).getNome().contains(input)) {
    			// Criar a string com a Div
                receita = "<div class=\"card\" style=\"width: 18rem; margin: 10px;\">\r\n"
    		    		+ "<img src=\"img/"+ todasReceitas.get(i).imagem +"\" class=\"card-img-top\" alt=\"..\" style=\"height: 16rem; width: 100%;\">\r\n" + "<div class=\"card-body\">\r\n"
                		+ "<h5 class=\"card-title\">Nome da receita</h5>\r\n"
                		+ "<p class=\"card-text\">cliente</p>\r\n" 
                		//<!-- Formulário que envia o nome da receita -->
                		+ "<form action=\"/ver-receita\" method=\"post\" id=\"viewRecipeForm\">"
                       + "<input type=\"hidden\" name=\"recipeName\" value=\"Nome da receita\">"
                		+ "<button type=\"submit\" class=\"btn btn-primary\" data-bs-toggle=\"modal\" data-bs-target=\"#recipeModal\">Ver Receita</button>\r\n"
                		+ "</form>"
                		+ "</div>\r\n"
                		+ "</div>";
                
                Cliente aux = new Cliente();
                aux = clienteService.clientePorId(todasReceitas.get(i).getIdCliente());
                
                // Editar a receita
                receita = receita.replace("Nome da receita", todasReceitas.get(i).getNome());
                receita = receita.replace("cliente", aux.getNome());
                //receita = receita.replace("Seu modo de preparo", todasReceitas.get(i).getModoDePreparo());
                
                // Concatenar varias Divs
                novaDiv = novaDiv + receita;
               }
    	}
    	
    	// Editar o front end com o Java
        html = html.replace("<DestaquesReceitas>", novaDiv);
        html = html.replace("Receitas em Destaque!", "Pesquisa por: " + input);
    	
        // Chamar funcao para editar o resto da pagina features como os NewRecipes e retornar tudo pronto
    	return replaceNewRecipes(html, 0, nome);
    }

 // alterar features pelas receitas do bd
    public String replaceNewRecipes(String html, int teste, String nome) {
    	// String auxiliares para criar a nova div
    	String receita = new String();
    	String novaDiv = new String();
    	
    	// Printar o nome do usuario
    	String nomeUsuario = new String();
		nomeUsuario = "<h3>SeuNome</h3>\r\n";		 
        // Editar o front end com o Java
        nomeUsuario = nomeUsuario.replace("SeuNome", nome);
        html = html.replace("<NomeUsuario>", nomeUsuario);
    	
    	// Lista com todas as receitas do BD para pesquisa
    	List<Receita> todasReceitas = retornarTodasReceitas();
    	
    	// verificar se tem menos de 4 
    	int loop = todasReceitas.size();
    	loop = loop > 4 ? 4 : loop;
    	loop--;
    	// loop para retornar as 4 ultimas receitas
    	int pos = todasReceitas.size() - 1;
    	
    	// Editar as receitas recentes
    	while ( loop >= 0 ) {
    		
    		// codigo
            receita = "<div class=\"card\" style=\"width: 18rem; margin: 10px;\">\r\n"
		    		+ "<img src=\"img/"+ todasReceitas.get(pos).imagem +"\" class=\"card-img-top\" alt=\"..\" style=\"height: 16rem; width: 100%;\">\r\n" + "<div class=\"card-body\">\r\n"
             		+ "<h5 class=\"card-title\">Nome da receita</h5>\r\n"
             		+ "<p class=\"card-text\">cliente</p>\r\n" 
             		//<!-- Formulário que envia o nome da receita -->
             		+ "<form action=\"/ver-receita\" method=\"post\" id=\"viewRecipeForm\">"
                    + "<input type=\"hidden\" name=\"recipeName\" value=\"Nome da receita\">"
             		+ "<button type=\"submit\" class=\"btn btn-primary\" data-bs-toggle=\"modal\" data-bs-target=\"#recipeModal\">Ver Receita</button>\r\n"
             		+ "</div>\r\n"
             		+ "</form>"
             		+ "</div>";
            
    		Cliente aux = new Cliente();
            aux = clienteService.clientePorId(todasReceitas.get(pos).getIdCliente());
            
    		// Editar a receita
    		receita = receita.replace("Nome da receita", todasReceitas.get(pos).getNome());
    		receita = receita.replace("cliente", aux.getNome());
    		//receita = receita.replace("Seu modo de preparo", todasReceitas.get(pos).getModoDePreparo());
    		
    		// Concatenar varias Divs
    		novaDiv = novaDiv + receita;
    	  		
    		loop--;
    		pos--;
    	}
    	// Editar o front end com o Java
        html = html.replace("<CaixaNovasReceitas>", novaDiv);
        
        if ( teste != 0 ) {
	        // Resetar Strings
	        receita = new String();
	        novaDiv = new String();
	        
	        // sortear para os destaques
	    	Collections.shuffle(todasReceitas);
	    	
	    	// verificar se tem menos de 4 
	    	loop = todasReceitas.size();
	    	loop = loop > 4 ? 4 : loop;
	    	loop--;
	    	// loop para retornar as 4 ultimas receitas
	    	pos = 0;
	    	
	    	// Editar as receitas destaques
	    	while ( loop >= 0 ) {
	    		// codigo
	            receita = "<div class=\"card\" style=\"width: 18rem; margin: 10px;\">\r\n"
    		    		+ "<img src=\"img/"+ todasReceitas.get(pos).imagem +"\" class=\"card-img-top\" alt=\"..\" style=\"height: 16rem; width: 100%;\">\r\n" + "<div class=\"card-body\">\r\n"
	             		+ "<h5 class=\"card-title\">Nome da receita</h5>\r\n"
	             		+ "<p class=\"card-text\">cliente</p>\r\n" 
	             		//<!-- Formulário que envia o nome da receita -->
	             		+ "<form action=\"/ver-receita\" method=\"post\" id=\"viewRecipeForm\">"
	                    + "<input type=\"hidden\" name=\"recipeName\" value=\"Nome da receita\">"
	             		+ "<button type=\"submit\" class=\"btn btn-primary\" data-bs-toggle=\"modal\" data-bs-target=\"#recipeModal\">Ver Receita</button>\r\n"
	             		+ "</div>\r\n"
	             		+ "</form>"
	             		+ "</div>";
	            
	            Cliente aux = new Cliente();
	            aux = clienteService.clientePorId(todasReceitas.get(pos).getIdCliente());
	    		
	    		// Editar a receita
	    		receita = receita.replace("Nome da receita", todasReceitas.get(pos).getNome());
	    		receita = receita.replace("cliente", aux.getNome());
	    		//receita = receita.replace("Seu modo de preparo", todasReceitas.get(pos).getModoDePreparo());
	    		
	    		// Concatenar varias Divs
	    		novaDiv = novaDiv + receita;
	    	  		
	    		loop--;
	    		pos++;
	    	}
	    	
	            
	        // Editar o front end com o Java
	        html = html.replace("<DestaquesReceitas>", novaDiv);
    	}
             
        // Retorna a string com o HTML
        return html;
    }

	public String replaceRecipesHome(String html) {
		
			String receita = new String();
			String novaDiv = new String();
	        
			// Lista com todas as receitas do BD para pesquisa
	    	List<Receita> todasReceitas = retornarTodasReceitas();
			
	        // sortear para os destaques
	    	Collections.shuffle(todasReceitas);
	    	
	    	// verificar se tem menos de 4 
	    	int loop = todasReceitas.size();
	    	loop = loop > 4 ? 4 : loop;
	    	loop--;
	    	
	    	// loop para retornar as 4 ultimas receitas
	    	int pos = 0;
	    	
	    	// Editar as receitas destaques
	    	while ( loop >= 0 ) {
	    		
	    		// codigo
	            receita = "<div class=\"card\" style=\"width: 18rem; margin: 10px;\">\r\n"
 		    		+ "<img src=\"img/"+ todasReceitas.get(pos).imagem +"\" class=\"card-img-top\" alt=\"..\" style=\"height: 16rem; width: 100%;\">\r\n" + "<div class=\"card-body\">\r\n"
	             		+ "<h5 class=\"card-title\">Nome da receita</h5>\r\n"
	             		+ "<p class=\"card-text\">cliente</p>\r\n" 
	             		//<!-- Formulário que envia o nome da receita -->
	             		+ "<form action=\"/ver-receita\" method=\"post\" id=\"viewRecipeForm\">"
	                    + "<input type=\"hidden\" name=\"recipeName\" value=\"Nome da receita\">"
	             		+ "<button type=\"submit\" class=\"btn btn-primary\" data-bs-toggle=\"modal\" data-bs-target=\"#recipeModal\">Ver Receita</button>\r\n"
	             		+ "</div>\r\n"
	             		+ "</form>"
	             		+ "</div>";
	            
	            Cliente aux = new Cliente();
	            aux = clienteService.clientePorId(todasReceitas.get(pos).getIdCliente());
	    		
	    		// Editar a receita
	    		receita = receita.replace("Nome da receita", todasReceitas.get(pos).getNome());
	    		receita = receita.replace("cliente", aux.getNome());
	    		//receita = receita.replace("Seu modo de preparo", todasReceitas.get(pos).getModoDePreparo());
	    		
	    		// Concatenar varias Divs
	    		novaDiv = novaDiv + receita;
	    	  		
	    		loop--;
	    		pos++;
	    	}
	    	
	        // Editar o front end com o Java
	        html = html.replace("<DestaquesReceitas>", novaDiv);
	        
		return html;
	}

}  