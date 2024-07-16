package service;

import java.sql.Date;

import dao.PedidoDAO;
import model.Pedido;

public class PedidoService {
    private PedidoDAO pedidoDAO;

    public PedidoService() {
        pedidoDAO = new PedidoDAO(); 
    }

    public void cadastrarPedido(int idCliente, Date dataPedido, float valorTotal) {
        Pedido pedido = new Pedido();
        pedido.setIdCliente(idCliente);
        pedido.setDataPedido(dataPedido);
        pedido.setValorTotal(valorTotal);
        
        pedidoDAO.cadastrarPedido(pedido);
    }
}
