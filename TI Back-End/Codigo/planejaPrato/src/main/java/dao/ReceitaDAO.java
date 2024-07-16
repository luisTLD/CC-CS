package dao;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.ArrayList;
import java.util.List;

import model.Cliente;
import model.Receita;

public class ReceitaDAO extends DAO {
    private static final String DB_URL = "jdbc:postgresql://localhost:5432/PlanejaPrato";
    private static final String USER = "postgres";
    private static final String PASS = "luissql";
    
    // Conexao com bd
    public ReceitaDAO() {
        super();
        conectar();
    }
    
    @Override
    public void finalize() {
        close();
    }

    public void cadastrarReceita(String nome, String ingredientes, String modoDePreparo, String imagem, int idCliente) {
        String sql = "INSERT INTO Receita (nome, ingredientes, modoDePreparo, imagem, idCliente) VALUES (?, ?, ?, ?, ?)";
        try (Connection connection = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement preparedStatement = connection.prepareStatement(sql)) {
            
            preparedStatement.setString(1, nome);
            preparedStatement.setString(2, ingredientes);
            preparedStatement.setString(3, modoDePreparo);
            preparedStatement.setString(4, imagem);
            preparedStatement.setInt(5, idCliente);

            preparedStatement.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public boolean update(Receita receita) {
        boolean status = false;
        String sql = "UPDATE Receita SET nome = ?, ingredientes = ?, modoDePreparo = ?, imagem = ? WHERE id = ?";
        try (Connection connection = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement preparedStatement = connection.prepareStatement(sql)) {
            
            preparedStatement.setString(1, receita.getNome());
            preparedStatement.setString(2, receita.getIngredientes());
            preparedStatement.setString(3, receita.getModoDePreparo());
            preparedStatement.setString(4, receita.getImagem());
            preparedStatement.setInt(5, receita.getId());

            preparedStatement.executeUpdate();
            status = true;
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return status;
    }

    public boolean delete(int id) {
        boolean status = false;
        String sql = "DELETE FROM Receita WHERE id = ?";
        try (Connection connection = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement preparedStatement = connection.prepareStatement(sql)) {
            
            preparedStatement.setInt(1, id);

            preparedStatement.executeUpdate();
            status = true;
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return status;
    }

    public List<Receita> getTodasReceitas() {
        List<Receita> listReceitas = new ArrayList<>();
        String sql = "SELECT * FROM Receita";
        try (Connection connection = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement preparedStatement = connection.prepareStatement(sql);
             ResultSet resultSet = preparedStatement.executeQuery()) {

            while (resultSet.next()) {
                Receita receita = new Receita();
                receita.setNome(resultSet.getString("nome"));
                receita.setIngredientes(resultSet.getString("ingredientes"));
                receita.setModoDePreparo(resultSet.getString("modoDePreparo"));
                receita.setImagem(resultSet.getString("imagem"));
                receita.setIdCliente(resultSet.getInt("idcliente"));

                listReceitas.add(receita);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return listReceitas;
    }

    public List<Receita> receitasUsuario(Cliente cliente) {
        List<Receita> listReceitas = new ArrayList<>();
        String sql = "SELECT * FROM Receita WHERE idcliente = ?";
        try (Connection connection = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement preparedStatement = connection.prepareStatement(sql)) {

            preparedStatement.setInt(1, cliente.getIdCliente());
            try (ResultSet resultSet = preparedStatement.executeQuery()) {
                while (resultSet.next()) {
                    Receita receita = new Receita();
                    receita.setNome(resultSet.getString("nome"));
                    receita.setIngredientes(resultSet.getString("ingredientes"));
                    receita.setModoDePreparo(resultSet.getString("modoDePreparo"));
                    receita.setImagem(resultSet.getString("imagem"));

                    listReceitas.add(receita);
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return listReceitas;
    }
}
