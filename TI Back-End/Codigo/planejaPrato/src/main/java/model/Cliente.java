package model;

public class Cliente {
    private int idCliente;
    private String nome;
    private String senha;
    private String endereco;
    private String email;
    private String numeroTelefone;
    private String cidade;
    private String cep;

    // Construtor que inicializa todos os campos
    public Cliente() {}
    public Cliente(String nome, String senha, String endereco, String email, String numeroTelefone, String cidade, String cep) {
        this.nome = nome;
        this.senha = senha;
        this.endereco = endereco;
        this.email = email;
        this.numeroTelefone = numeroTelefone;
        this.cidade = cidade;
        this.cep = cep;
    }

    public void setSenha(String senha) {
        this.senha = senha;
    }
    public String getSenha() {
        return senha;
    }

    public void setCidade(String cidade) {
        this.cidade = cidade;
    }

    public String getCidade() {
        return cidade;
    }

    // Setter para cep
    public void setCep(String cep) {
        this.cep = cep;
    }

    // Getter para cep
    public String getCep() {
        return cep;
    }


    // Getters e Setters
    public int getIdCliente() {
        return idCliente;
    }

    public void setIdCliente(int idCliente) {
        this.idCliente = idCliente;
    }

    public String getNome() {
        return nome;
    }

    public void setNome(String nome) {
        this.nome = nome;
    }

    public String getEndereco() {
        return endereco;
    }

    public void setEndereco(String endereco) {
        this.endereco = endereco;
    }

    public String getEmail() {
        return email;
    }

    public void setEmail(String email) {
        this.email = email;
    }

    public String getNumeroTelefone() {
        return numeroTelefone;
    }

    public void setNumeroTelefone(String numeroTelefone) {
        this.numeroTelefone = numeroTelefone;
    }
}