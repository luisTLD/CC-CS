package service;

import dao.CarrinhoDAO;
import model.Carrinho;

public class CarrinhoService {
    private CarrinhoDAO carrinhoDAO;

    public CarrinhoService() {
        carrinhoDAO = new CarrinhoDAO(); 
    }

    public void cadastrarCarrinho(int idPedido, int idIngrediente, int quantidade, float valorTotal) {
        Carrinho carrinho = new Carrinho();
        carrinho.setIdPedido(idPedido);
        carrinho.setIdIngrediente(idIngrediente);
        carrinho.setQuantidade(quantidade);
        carrinho.setValorTotal(valorTotal);
        
        carrinhoDAO.adicionarItem(carrinho);
    }
}
