package dao;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

import model.Carrinho;

public class CarrinhoDAO extends DAO {
    public CarrinhoDAO() {
        super();
        conectar();
    }

    public void finalize() {
        close();
    }

    String url = "jdbc:postgresql://localhost:5432/PlanejaPrato";
    String usuario = "postgres";
    String senha = "luissql";

    public void adicionarItem(Carrinho carrinho) {
        try (Connection connection = DriverManager.getConnection(url, usuario, senha)) {
            String sql = "INSERT INTO Carrinho (idPedido, idIngrediente, quantidade, valorTotal) VALUES (?, ?, ?, ?)";
            PreparedStatement preparedStatement = connection.prepareStatement(sql);
            preparedStatement.setInt(1, carrinho.getIdPedido());
            preparedStatement.setInt(2, carrinho.getIdIngrediente());
            preparedStatement.setInt(3, carrinho.getQuantidade());
            preparedStatement.setFloat(4, carrinho.getValorTotal());

            preparedStatement.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public List<Carrinho> listarItensCarrinho(int idPedido) {
        List<Carrinho> itensCarrinho = new ArrayList<>();
        try (Connection connection = DriverManager.getConnection(url, usuario, senha)) {
            String sql = "SELECT * FROM Carrinho WHERE idPedido = ?";
            PreparedStatement preparedStatement = connection.prepareStatement(sql);
            preparedStatement.setInt(1, idPedido);
            ResultSet resultSet = preparedStatement.executeQuery();

            while (resultSet.next()) {
                Carrinho item = new Carrinho();
                item.setIdPedido(resultSet.getInt("idPedido"));
                item.setIdIngrediente(resultSet.getInt("idIngrediente"));
                item.setQuantidade(resultSet.getInt("quantidade"));
                item.setValorTotal(resultSet.getFloat("valorTotal"));
                itensCarrinho.add(item);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return itensCarrinho;
    }

    public boolean atualizarItemCarrinho(Carrinho item) {
        boolean status = false;
        try (Connection connection = DriverManager.getConnection(url, usuario, senha)) {
            String sql = "UPDATE Carrinho SET quantidade = ?, valorTotal = ? WHERE idPedido = ? AND idIngrediente = ?";
            PreparedStatement preparedStatement = connection.prepareStatement(sql);
            preparedStatement.setInt(1, item.getQuantidade());
            preparedStatement.setFloat(2, item.getValorTotal());
            preparedStatement.setInt(3, item.getIdPedido());
            preparedStatement.setInt(4, item.getIdIngrediente());

            int rowsUpdated = preparedStatement.executeUpdate();
            if (rowsUpdated > 0) {
                status = true;
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return status;
    }

    public boolean removerItemCarrinho(int idPedido, int idIngrediente) {
        boolean status = false;
        try (Connection connection = DriverManager.getConnection(url, usuario, senha)) {
            String sql = "DELETE FROM Carrinho WHERE idPedido = ? AND idIngrediente = ?";
            PreparedStatement preparedStatement = connection.prepareStatement(sql);
            preparedStatement.setInt(1, idPedido);
            preparedStatement.setInt(2, idIngrediente);

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
