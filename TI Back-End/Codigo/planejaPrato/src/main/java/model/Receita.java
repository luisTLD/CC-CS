package model;

public class Receita {
		
	    public String nomeReceita;
	    public String ingredientes;
	    public String modoDePreparo;
	    public String imagem;
	    public int idReceita;
	    public int idCliente;
	    
	 // Construtor
	    public Receita(String nomeReceita, String ingredientes, String modoDePreparo, String imagem, int id) {
	        this.nomeReceita = nomeReceita;
	        this.ingredientes = ingredientes;
	        this.modoDePreparo = modoDePreparo;
	        this.imagem = imagem;
	        this.idCliente = id;
	    }
	    
	    public Receita() {}
	    
	    // Gettes e Setters
	    public void setNome(String nome) {
	    	this.nomeReceita = nome;
	    }
	    public void setImagem(String imagem) {
	    	this.imagem = imagem;
	    }

	    public void setIngredientes(String ingredientes) {
	    	this.ingredientes = ingredientes;
	    }
	    public void setModoDePreparo(String modoDePreparo) {
	    	this.modoDePreparo = modoDePreparo;
	    }

	    public void setId(int idReceita) {
	    	this.idReceita = idReceita;
	    }
	    public int getId() {
	        return idReceita;
	    }
	    public void setIdCliente(int idCliente) {
	    	this.idCliente = idCliente;
	    }
	    public int getIdCliente() {
	        return idCliente;
	    }

	    public String getNome() {
	        return nomeReceita;
	    }


	    public String getModoDePreparo() {
	        return modoDePreparo;
	    }

	    public String getIngredientes() {
	        return ingredientes;
	    }
	    public String getImagem() {
	        return imagem;
	    }


}
