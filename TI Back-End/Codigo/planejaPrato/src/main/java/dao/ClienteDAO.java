package dao;

import java.beans.Statement;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

import model.Cliente;

public class ClienteDAO extends DAO {
    public ClienteDAO() {
        super();
        conectar();
    }

    public void finalize() {
        close();
    }

    String url = "jdbc:postgresql://localhost:5432/PlanejaPrato";
    String usuario = "postgres";
    String senha = "luissql";

    public void cadastrarCliente(Cliente cliente) {

        try (Connection connection = DriverManager.getConnection(url, usuario, senha)) {
            String sql = "INSERT INTO cliente ( email, endereco, telefone, senha, cidade, cep, nome) VALUES (?, ?, ?, ?, ? , ? , ?)";
            PreparedStatement preparedStatement = connection.prepareStatement(sql);
            preparedStatement.setString(1, cliente.getEmail());
            preparedStatement.setString(2, cliente.getEndereco());
            preparedStatement.setString(3, cliente.getNumeroTelefone());
            preparedStatement.setString(4, cliente.getSenha());
            preparedStatement.setString(5, cliente.getCidade());
            preparedStatement.setString(6, cliente.getCep());
            preparedStatement.setString(7, cliente.getNome());



            preparedStatement.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    // Nao funciona da pau em tudo
    public List<Cliente> listarClientes() {
        List<Cliente> clientes = new ArrayList<>();
        try (Connection connection = DriverManager.getConnection(url, usuario, senha)) {
            String sql = "SELECT * FROM Cliente";
            PreparedStatement preparedStatement = connection.prepareStatement(sql);
            ResultSet resultSet = preparedStatement.executeQuery();

            while (resultSet.next()) {
                Cliente cliente = new Cliente();
                cliente.setIdCliente(resultSet.getInt("idcliente"));
                cliente.setEndereco(resultSet.getString("endereco"));
                cliente.setEmail(resultSet.getString("email"));
                cliente.setNumeroTelefone(resultSet.getString("telefone"));
                cliente.setSenha(resultSet.getString("senha"));
                cliente.setCidade(resultSet.getString("cidade"));
                cliente.setCep(resultSet.getString("cep"));
                cliente.setNome(resultSet.getString("nome"));
                
                clientes.add(cliente);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return clientes;
    }
    
    
    public Cliente autenticarCliente(String email, String senhaCliente) {
    	Cliente cliente = new Cliente();
    	try (Connection connection = DriverManager.getConnection(url, usuario, senha)) {
            String sql = "SELECT * FROM Cliente WHERE email = ? AND senha = ?";
            PreparedStatement preparedStatement = connection.prepareStatement(sql);
            preparedStatement.setString(1, email);
            preparedStatement.setString(2, senhaCliente);
            

            ResultSet resultSet = preparedStatement.executeQuery();

            if(resultSet.next()) {
                cliente.setIdCliente(resultSet.getInt("idcliente"));
                cliente.setEndereco(resultSet.getString("endereco"));
                cliente.setEmail(resultSet.getString("email"));
                cliente.setNumeroTelefone(resultSet.getString("telefone"));
                cliente.setSenha(resultSet.getString("senha"));
                cliente.setCidade(resultSet.getString("cidade"));
                cliente.setCep(resultSet.getString("cep"));
                cliente.setNome(resultSet.getString("nome"));
            }
            
        } catch (SQLException e) {
            e.printStackTrace();
        }
    	
        return cliente;
    }
    
    
    /*
    // Vulneravel ao SQL injection
    public Cliente autenticarCliente(String email, String senhaCliente) {
        Cliente cliente = new Cliente();
        try (Connection connection = DriverManager.getConnection(url, usuario, senha)) {
            // Consulta SQL vulnerável a SQL Injection (apenas para fins educacionais)
            String sql = "SELECT * FROM Cliente WHERE email = '" + email + "' AND senha = '" + senhaCliente + "'";
            
            // Utilizando PreparedStatement para simular a vulnerabilidade
            PreparedStatement preparedStatement = connection.prepareStatement(sql);
            ResultSet resultSet = preparedStatement.executeQuery();

            if (resultSet.next()) {
                cliente.setIdCliente(resultSet.getInt("idcliente"));
                cliente.setEndereco(resultSet.getString("endereco"));
                cliente.setEmail(resultSet.getString("email"));
                cliente.setNumeroTelefone(resultSet.getString("telefone"));
                cliente.setSenha(resultSet.getString("senha"));
                cliente.setCidade(resultSet.getString("cidade"));
                cliente.setCep(resultSet.getString("cep"));
                cliente.setNome(resultSet.getString("nome"));
            }

        } catch (SQLException e) {
            e.printStackTrace();
        }

        return cliente;
    }
    */

    
    public Cliente retornaClientePorId(int id) {
    	Cliente cliente = new Cliente();
    	try (Connection connection = DriverManager.getConnection(url, usuario, senha)) {
            String sql = "SELECT * FROM Cliente WHERE idcliente = ?";
            PreparedStatement preparedStatement = connection.prepareStatement(sql);
            preparedStatement.setInt(1, id);
            
            ResultSet resultSet = preparedStatement.executeQuery();

            if(resultSet.next()) {
                cliente.setIdCliente(resultSet.getInt("idcliente"));
                cliente.setEndereco(resultSet.getString("endereco"));
                cliente.setEmail(resultSet.getString("email"));
                cliente.setNumeroTelefone(resultSet.getString("telefone"));
                cliente.setSenha(resultSet.getString("senha"));
                cliente.setCidade(resultSet.getString("cidade"));
                cliente.setCep(resultSet.getString("cep"));
                cliente.setNome(resultSet.getString("nome"));
            }
            
        } catch (SQLException e) {
            e.printStackTrace();
        }
    	// System.out.println("Cliente por id" + cliente.getNome());
        return cliente;
    }

    public boolean atualizarCliente(Cliente cliente) {
        boolean status = false;
        try (Connection connection = DriverManager.getConnection(url, usuario, senha)) {
            String sql = "UPDATE Cliente SET nome = ?, endereco = ?, email = ?, numero_telefone = ? WHERE id = ?";
            PreparedStatement preparedStatement = connection.prepareStatement(sql);
              preparedStatement.setString(1, cliente.getNome());
            preparedStatement.setString(2, cliente.getEndereco());
            preparedStatement.setString(3, cliente.getEmail());
            preparedStatement.setString(4, cliente.getNumeroTelefone());

            int rowsUpdated = preparedStatement.executeUpdate();
            if (rowsUpdated > 0) {
                status = true;
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return status;
    }

    public boolean deletarCliente(int id) {
        boolean status = false;
        try (Connection connection = DriverManager.getConnection(url, usuario, senha)) {
            String sql = "DELETE FROM Cliente WHERE id = ?";
            PreparedStatement preparedStatement = connection.prepareStatement(sql);
            preparedStatement.setInt(1, id);

            int rowsDeleted = preparedStatement.executeUpdate();
            if (rowsDeleted > 0) {
                status = true;
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return status;
    }

	public List<Cliente> getTodosClientes() {
		return listarClientes();
	}

}

