


document.addEventListener('DOMContentLoaded', () => {
    // Seu código JavaScript aqui
    let cartNew = document.querySelector("#cart-icon");
    let cart = document.querySelector(".cart");
    let closeCart = document.querySelector("#close-cart");
    // close cart
    closeCart.onclick = () => {
        cart.classList.remove("active");
        overlay.style.display = "none";
    
    };
    
    // open cart
    cartNew.onclick = () => {
        if (cart.classList.contains("active")) {
            cart.classList.remove("active"); // Se o carrinho estiver aberto, fecha


        } else {
            cart.classList.add("active"); // Se o carrinho estiver fechado, abre
            overlay.style.display = "block";
        };
    }
    overlay.onclick = (event) => {
        if (event.target === overlay) {
            cart.classList.remove("active");
            overlay.style.display = "none";
        }
    };
});
