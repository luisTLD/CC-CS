package dao;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

import model.Ingrediente;

public class IngredienteDAO extends DAO {
    public IngredienteDAO() {
        super();
        conectar();
    }

    public void finalize() {
        close();
    }

    String url = "jdbc:postgresql://localhost:5432/PlanejaPrato";
    String usuario = "postgres";
    String senha = "luissql";

    public void cadastrarIngrediente(Ingrediente ingrediente) {
        try (Connection connection = DriverManager.getConnection(url, usuario, senha)) {
            String sql = "INSERT INTO ingrediente (idIngrediente, nome, preco) VALUES (?, ?, ?)";
            PreparedStatement preparedStatement = connection.prepareStatement(sql);
            preparedStatement.setInt(1, ingrediente.getIdIngrediente());
            preparedStatement.setString(2, ingrediente.getNome());
            preparedStatement.setFloat(3, ingrediente.getPreco());

            preparedStatement.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public List<Ingrediente> listarIngredientes() {
        List<Ingrediente> ingredientes = new ArrayList<>();
        try (Connection connection = DriverManager.getConnection(url, usuario, senha)) {
            String sql = "SELECT * FROM ingrediente";
            PreparedStatement preparedStatement = connection.prepareStatement(sql);
            ResultSet resultSet = preparedStatement.executeQuery();

            while (resultSet.next()) {
                Ingrediente ingrediente = new Ingrediente();
                ingrediente.setIdIngrediente(resultSet.getInt("idIngrediente"));
                ingrediente.setNome(resultSet.getString("nome"));
                ingrediente.setPreco(resultSet.getFloat("preco"));
                ingredientes.add(ingrediente);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return ingredientes;
    }

    public boolean atualizarIngrediente(Ingrediente ingrediente) {
        boolean status = false;
        try (Connection connection = DriverManager.getConnection(url, usuario, senha)) {
            String sql = "UPDATE ingrediente SET nome = ?, preco = ? WHERE idIngrediente = ?";
            PreparedStatement preparedStatement = connection.prepareStatement(sql);
            preparedStatement.setString(1, ingrediente.getNome());
            preparedStatement.setFloat(2, ingrediente.getPreco());
            preparedStatement.setInt(3, ingrediente.getIdIngrediente());

            int rowsUpdated = preparedStatement.executeUpdate();
            if (rowsUpdated > 0) {
                status = true;
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return status;
    }
    public boolean deletarIngrediente(int id) {
        boolean status = false;
        try (Connection connection = DriverManager.getConnection(url, usuario, senha)) {
            String sql = "DELETE FROM ingrediente WHERE id = ?";
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

}
