package dao;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

import model.Pedido;

public class PedidoDAO extends DAO {
    public PedidoDAO() {
        super();
        conectar();
    }

    public void finalize() {
        close();
    }

    String url = "jdbc:postgresql://localhost:5432/PlanejaPrato";
    String usuario = "postgres";
    String senha = "luissql";

    public void cadastrarPedido(Pedido pedido) {
        try (Connection connection = DriverManager.getConnection(url, usuario, senha)) {
            String sql = "INSERT INTO Pedido (idPedido, idCliente, dataPedido, valorTotal) VALUES (?, ?, ?, ?)";
            PreparedStatement preparedStatement = connection.prepareStatement(sql);
            preparedStatement.setInt(1, pedido.getIdPedido());
            preparedStatement.setInt(2, pedido.getIdCliente());
            preparedStatement.setDate(3, pedido.getDataPedido());
            preparedStatement.setFloat(4, pedido.getValorTotal());

            preparedStatement.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public List<Pedido> listarPedidos() {
        List<Pedido> pedidos = new ArrayList<>();
        try (Connection connection = DriverManager.getConnection(url, usuario, senha)) {
            String sql = "SELECT * FROM Pedido";
            PreparedStatement preparedStatement = connection.prepareStatement(sql);
            ResultSet resultSet = preparedStatement.executeQuery();

            while (resultSet.next()) {
                Pedido pedido = new Pedido();
                pedido.setIdPedido(resultSet.getInt("idPedido"));
                pedido.setIdCliente(resultSet.getInt("idCliente"));
                pedido.setDataPedido(resultSet.getDate("dataPedido"));
                pedido.setValorTotal(resultSet.getFloat("valorTotal"));
                pedidos.add(pedido);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return pedidos;
    }

    public boolean atualizarPedido(Pedido pedido) {
        boolean status = false;
        try (Connection connection = DriverManager.getConnection(url, usuario, senha)) {
            String sql = "UPDATE Pedido SET idCliente = ?, dataPedido = ?, valorTotal = ? WHERE idPedido = ?";
            PreparedStatement preparedStatement = connection.prepareStatement(sql);
            preparedStatement.setInt(1, pedido.getIdCliente());
            preparedStatement.setDate(2, new java.sql.Date(pedido.getDataPedido().getTime()));
            preparedStatement.setFloat(3, pedido.getValorTotal());
            preparedStatement.setInt(4, pedido.getIdPedido());

            int rowsUpdated = preparedStatement.executeUpdate();
            if (rowsUpdated > 0) {
                status = true;
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return status;
    }
    public boolean deletarPedido(int id) {
        boolean status = false;
        try (Connection connection = DriverManager.getConnection(url, usuario, senha)) {
            String sql = "DELETE FROM Pedido WHERE id = ?";
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
