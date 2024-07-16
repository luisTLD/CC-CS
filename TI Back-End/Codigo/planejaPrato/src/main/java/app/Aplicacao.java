/* Responsavel por rodar a WEB, e criar uma instancia de ReceitaService */

package app;

import static spark.Spark.*;

import service.ClienteService;
import service.IngredienteService;
import service.ReceitaService;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

import model.Cliente;
import model.Receita;
import java.net.URI;
import java.net.http.*;
import org.json.JSONObject;

public class Aplicacao {
	// Instancias
    public static OpenAIClient client = new OpenAIClient();
    public static ReceitaService receitaService = new ReceitaService();
    public static ClienteService clienteService = new ClienteService();
    public static IngredienteService ingredienteService = new IngredienteService();


    // Criar uma String auxiliar para futuras implementações e usos
    public static String html = new String();
    public static String receita = new String();
    
    // Cliente Logado
    public static String email = new String();
    public static String senha = new String();
    
    public static void main(String[] args) {
    	
        // Configura a porta do servidor web
        port(5402);

        // Configura o diretório para arquivos estáticos (HTML, CSS, JS)
        staticFiles.externalLocation("src/main/resources/public");
        
        // Clicar em Ver Receita
        post("/ver-receita", (request, response) -> {
        	
        	// Codigo para verificar se o cliente ta logado e retornar uma instancia com os dados deste cliente
        	Cliente clienteLogado =  request.session().attribute("usuarioLogado");
        	if (clienteLogado == null) {
                response.redirect("/login.html");
                return null;
            }
        	// Printar o nome do cliente q esta logado
        	System.out.println(clienteLogado.getNome());
        	
            // Receber o nome da receita enviado pela solicitação POST
            String nome = request.queryParams("recipeName");
            
            // Buscar a receita pelo nome
            Receita receita = receitaService.procurarReceita(nome);

            // Html para a pagina a ser redirecionado
            html = htmlText("receita.html");
            
        	// Atualizar o HTML com o bd necessario
            html = receitaService.replaceIngredientes(html, receita, clienteLogado.getNome());
            
            return html;
        });  
        
        get("/home", (request, response) -> {
        	String html = htmlText("home.html");
        	Cliente clienteLogado =  request.session().attribute("usuarioLogado");
        	if (clienteLogado == null) {
                response.redirect("/login.html");
                return null;
            }
        	System.out.println(clienteLogado.getNome());

        	String aux = new String();
        	aux = htmlText("createRecipeModal.html");
        	aux = ingredienteService.replaceIngredientes(aux);
        	html = ingredienteService.replaceIngredientesPages(html, aux, clienteLogado.getNome());
        	html = receitaService.replaceRecipesHome(html);
        	
        	return html;
        });
        

        // Rota para cadastrar uma receita via POST
        post("/cadastra-receita", (request, response) -> {
        	
        	// Codigo para verificar se o cliente ta logado e retornar uma instancia com os dados deste cliente
        	Cliente clienteLogado =  request.session().attribute("usuarioLogado");
        	
        	if (clienteLogado == null) {
                response.redirect("/login.html");
                return null;
            }
        	
        	// Printar o nome do cliente q esta logado
        	System.out.println(clienteLogado.getNome());        	

            // Obtém os parâmetros da requisição
            String nome = request.queryParams("nome");
            String[] ingredientesChegada = request.queryParamsValues("ingredientes");
            String[] quantidade = request.queryParamsValues("quantidade");
            
            int j = 0;
            for ( int i = 0; i < ingredientesChegada.length; i++ ) {
            	while (quantidade[j].equals("0")) j++;
	            	System.out.println(quantidade[j]);
	            	ingredientesChegada[i] += "_" + quantidade[j];
	            	System.out.println(ingredientesChegada[i]);
            }
            
            String ingredientes = String.join(", ", ingredientesChegada);         
            
            String modoDePreparo = request.queryParams("modoDePreparo");  
            String nomeImg = client.createImages(nome + " receita culinaria");
            
            // Converte os valores para minúsculas
            nome = nome.toLowerCase();
            ingredientes = ingredientes.toLowerCase();
            modoDePreparo = modoDePreparo.toLowerCase();
            
            // Imprime os valores recebidos no console
            System.out.println("Nome: " + nome);
            System.out.println("Ingredientes: " + ingredientes);
            System.out.println("Modo de Preparo: " + modoDePreparo);
            System.out.println("Url Imagem: " + nomeImg);      

            
            // Chama o serviço de cadastro de receita
            // Manda os parametros para a função cadastrarReceita de receitaService
            receitaService.cadastraReceita(nome, modoDePreparo, ingredientes, nomeImg, clienteLogado);          
            
            // Printar todas as receitar do BD no console
            receitaService.printarReceitas(receitaService.retornarReceitasDoCliente(clienteLogado));
            
            // Preencher a string aux com o conteudo do HTML
            html = htmlText("yourRecipes.html");
            html = receitaService.replaceYourRecipes(html, clienteLogado);
            
            return html;       
        });
        
        post("/cadastra-cliente", (request, response) -> {       	
        	        	
            // Obtém os parâmetros da requisição
            String nome = request.queryParams("nome");
            String cep = request.queryParams("cep");
            String email = request.queryParams("email");
            String senha = request.queryParams("senha");
            String endereco = request.queryParams("endereco");  
            String telefone = request.queryParams("telefone");  
            String cidade = request.queryParams("cidade"); 
            
            
            // Converte os valores para minúsculas
            nome = nome.toLowerCase();
            //email = email.toLowerCase();
            //senha = senha.toLowerCase();
            endereco = endereco.toLowerCase();
            telefone = telefone.toLowerCase();
            cidade = cidade.toLowerCase();
            cep = cep.toLowerCase();
            
            // printar os dados do cliente
            System.out.println("Nome: "+ nome +"\nEmail: " +email + "\nSenha: " + senha + "Endereco: "+endereco + "\nTelefone: "+ telefone + "\nCidade: "+cidade + "\nCep: "+cep);
            // Chama o serviço de cadastro de receita
            // Manda os parametros para a função cadastrarReceita de receitaService
            
            // Criptografia
            char[] crip = senha.toCharArray();
            for ( int i = 0; i < senha.length(); i++ ) crip[i] += i;
            senha = new String(crip);
            
            clienteService.cadastrarCliente(nome, senha, endereco, email, telefone, cidade, cep);          
            
            // Printar todas os usuarios do BD no console
            clienteService.printarClientes(clienteService.retornarTodosClientes());
            
            // Preencher a string aux com o conteudo do HTML
            html = htmlText("index.html");
            return html;
        });
        
        post("/login", (request, response) -> {
            // Receber o nome da receita enviado pela solicitação POST
            email = request.queryParams("email");
            senha = request.queryParams("senha");
            
            System.out.println("Email: "+ email+ "\nSenha: "+ senha);
            
            // Criptografia tambem proteje contra o SQL injection
            char[] crip = senha.toCharArray();
            for ( int i = 0; i < senha.length(); i++ ) crip[i] += i;
            senha = new String(crip);
            
            System.out.println("Email: "+ email+ "\nSenha: "+ senha);
            
            Cliente clienteLogado = clienteService.autenticarCliente(email, senha);
            
            // mandar para o index apos cadastrado
            html = htmlText("home.html");
            String aux = htmlText("createRecipeModal.html");
            aux = ingredienteService.replaceIngredientes(aux);
            html = ingredienteService.replaceIngredientesPages(html, aux, clienteLogado.getNome());
            
            if(clienteLogado!=null) {
            	// printar o email do usuario logado
            	System.out.println("Nome: " + clienteLogado.getEmail());
            	
            	// manter logado
            	request.session().attribute("usuarioLogado", clienteLogado);
            }
            else {
            	// caso nao logar, redirecionar para o login novamente
            	html = htmlText("login.html");
            }
            
            // redirecionar para pagina certa
            return html; 
        });  

        
     // Pesquisar receita
        post("/pesquisar-receita", (request, response) -> {
        	
        	// Codigo para verificar se o cliente ta logado e retornar uma instancia com os dados deste cliente
        	Cliente clienteLogado =  request.session().attribute("usuarioLogado");
        	if (clienteLogado == null) {
                response.redirect("/login.html");
                return null;
            }
        	// Printar o nome do cliente q esta logado
        	System.out.println(clienteLogado.getNome());
        	
        	// Receber o input do usuario
        	String input = request.queryParams("pesquisa");
        	input = input.toLowerCase();
        	
        	// Html para a pagina a ser redirecionado
        	html = htmlText("featureRecipes.html");
        	
        	// Atualizar o HTML com o bd necessario
            html = receitaService.replacePesquisaFeatureRecipes(html, input, clienteLogado.getNome());
            
            // Retonar html com a pesquisa 
        	return html;
        });

        
        // Rota para atualizar html yourRecipes com receitas do bd via GET 
        get("/yourRecipes", (request, response) -> {
        	
        	// Codigo para verificar se o cliente ta logado e retornar uma instancia com os dados deste cliente
        	Cliente clienteLogado =  request.session().attribute("usuarioLogado");
        	if (clienteLogado == null) {
                response.redirect("/login.html");
                return null;
            }
        	
        	String aux = new String();
        	aux = htmlText("createRecipeModal.html");
        	html = htmlText("yourRecipes.html");        	
        	aux = ingredienteService.replaceIngredientes(aux);
        	
        	html = ingredienteService.replaceIngredientesPages(html, aux, clienteLogado.getNome());

        	// Printar o nome do cliente q esta logado
        	System.out.println(clienteLogado.getNome());
        	        	
        	html = receitaService.replaceYourRecipes(html, clienteLogado);
        	
        	return html;
        });
        
     // Ir para a pagina features, e atualizando as receitas novas
        get("/features", (request, response) -> {
        	
        	// Codigo para verificar se o cliente ta logado e retornar uma instancia com os dados deste cliente
        	Cliente clienteLogado =  request.session().attribute("usuarioLogado");
        	if (clienteLogado == null) {
                response.redirect("/login.html");
                return null;
            }
        	// Printar o nome do cliente q esta logado
        	System.out.println(clienteLogado.getNome());
        	
        	// Ler o html
            html = htmlText("featureRecipes.html");
            
            // Atualizar o HTML com o bd necessario
            html = receitaService.replaceNewRecipes(html, 1, clienteLogado.getNome());
            
            // Retornar o HTML editado
            return html;
        });
        
       
    }

    
    // Função para ler um HTML e retornar uma String contendo todo o conteudo
    public static String htmlText(String link){
    	
    	// Criar uma String formatada para redirecionar ao local que deseja ler
    	String caminhoArq = "./src/main/resources/public/" + link;
    	
    	// Criar a string de saida com todo o HTML
    	StringBuilder conteudo = new StringBuilder();
    	
    	// Tentar abrir o Scanner para ler o HTML
    	try {
            File arquivo = new File(caminhoArq);
            Scanner sc = new Scanner(arquivo);

            // Concatencar na String todo o HTML, construindo a String de saida
            while (sc.hasNextLine()) {
                conteudo.append(sc.nextLine());
            }
            
            sc.close();
    	}
    	catch (FileNotFoundException e) {
    		e.printStackTrace();
    	}
    	
    	// Retonar a String contendo todo o HTML
    	return conteudo.toString();
    }
    
}
