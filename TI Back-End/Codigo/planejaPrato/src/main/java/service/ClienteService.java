package service;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

import dao.ClienteDAO;
import model.Cliente;
import model.Receita;

public class ClienteService {
    private ClienteDAO clienteDAO;

    public ClienteService() {
        clienteDAO = new ClienteDAO(); 
    }

    public void cadastrarCliente(String nome, String senha, String endereco, String email,String telefone, String cidade,String cep) {
        Cliente cliente = new Cliente(nome, senha, endereco, email, telefone, cidade, cep);        
        clienteDAO.cadastrarCliente(cliente);
    }
    public List<Cliente> retornarTodosClientes(){
    	return clienteDAO.listarClientes();
    }

    public void printarClientes(List<Cliente> clientes) {
        for (Cliente cliente : clientes) {
            System.out.println("ID do Cliente: " + cliente.getIdCliente());
            System.out.println("Nome: " + cliente.getNome());
            System.out.println("Endereço: " + cliente.getEndereco());
            System.out.println("Email: " + cliente.getEmail());
            System.out.println("Telefone: " + cliente.getNumeroTelefone());
            System.out.println("Cidade: " + cliente.getCidade());
            System.out.println("CEP: " + cliente.getCep());
            System.out.println("--------------------------");
        }
    }
    public Cliente autenticarCliente(String email, String senha){
    	return clienteDAO.autenticarCliente(email,senha);
    }

    public Cliente clientePorId(int id) {
    	return clienteDAO.retornaClientePorId(id);
    }


} 
