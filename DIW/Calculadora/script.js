document.addEventListener("DOMContentLoaded", function (){
    let espelho = document.getElementById("espelho");
    let del = document.getElementById("del");
    let numero = document.getElementsByTagName("button");
    let excluir = document.getElementById("excluir");
    let historico = document.getElementById("historico");
    let principal = document.getElementById("retornar");
    let tela1 = document.getElementById("tela1");
    let tela2 = document.getElementById("tela2");
    let salvar = document.getElementById("salvar");
    let historicoTela2 = document.getElementById("historicoTela2");
    let limpar = document.getElementById("zerar");
    var elementosRemover = historicoTela2.getElementsByTagName("p");
    let usado = true;
    let resposta = 0;
    let respostaString = "";
    let novaString = "";
    let expressao = "";
    let primeiro = true;
    let idaVolta = true;
    let trocar = true;
    let especialInicial = true;
    let especialFinal = true;
    let t = 0;
    let nenhum = true;

    function carEspecial() {
        const ultimoCaractere = espelho.innerHTML[espelho.innerHTML.length - 1];
        if (
            ultimoCaractere === "%" ||
            ultimoCaractere === "+" ||
            ultimoCaractere === "-" ||
            ultimoCaractere === "*" ||
            ultimoCaractere === "/" ||
            ultimoCaractere === "."
        ) {
            especialInicial = false;
            return especialInicial;
        } else {
            return especialInicial;
        }
    }
    

    function ultimoEspecial() {
        const ultimoCaractere = event.target.textContent;
        if (
            ultimoCaractere === "%" ||
            ultimoCaractere === "+" ||
            ultimoCaractere === "-" ||
            ultimoCaractere === "*" ||
            ultimoCaractere === "/" ||
            ultimoCaractere === "."
        ) {
            especialFinal = false;
            return especialFinal;
        } else {
            return especialFinal;
        }
    }
    
    function carNormal() {
        const ultimoCaractere = espelho.innerHTML[espelho.innerHTML.length - 1];
        if (
            ultimoCaractere === "1" ||
            ultimoCaractere === "2" ||
            ultimoCaractere === "3" ||
            ultimoCaractere === "4" ||
            ultimoCaractere === "5" ||
            ultimoCaractere === "6" ||
            ultimoCaractere === "7" ||
            ultimoCaractere === "8" ||
            ultimoCaractere === "9" ||
            ultimoCaractere === "0" 
        ) {
            normalInicial = false;
            return normalInicial;
        } else {
            return normalInicial;
        }
    }
    
    
    function ultimoNormal() {
        const ultimoCaractere = event.target.textContent;
        if (
            ultimoCaractere === "1" ||
            ultimoCaractere === "2" ||
            ultimoCaractere === "3" ||
            ultimoCaractere === "4" ||
            ultimoCaractere === "5" ||
            ultimoCaractere === "6" ||
            ultimoCaractere === "7" ||
            ultimoCaractere === "8" ||
            ultimoCaractere === "9" ||
            ultimoCaractere === "0" 
        ) {
            normalFinal = false;
            return normalFinal;
        } else {
            return normalFinal;
        }
    }



    function mudar (){
        if ( trocar === true ){
            tela1.style.display = "none";
            tela2.style.display = "block";
            trocar = false;
        }
        else if ( trocar === false ){
            tela1.style.display = "block";
            tela2.style.display = "none";
            trocar = true;
        }
    }

    function parenteses (){
        if ( espelho.innerHTML.length > 24 ){
            for ( let z = 0; z < numero.length; z++ ){
                numero[z].removeEventListener("click", mostrar);
            }
        }
        else if ( espelho.innerHTML[espelho.innerHTML.length - 1] === "."){
            return;
        }
        else if ( event.target === numero[1] ){
            if ( idaVolta === true ){
                if ( espelho.innerHTML[0] ==  0 ){
                    espelho.innerHTML = "(";
                    idaVolta = false;
                    primeiro = false;
                }
                else{
                    if ( carEspecial() || espelho.innerHTML[espelho.innerHTML.length - 1] === ")" ){
                        espelho.innerHTML += "*(";
                        idaVolta = false;
                    }
                    else {
                        espelho.innerHTML += "(";
                        idaVolta = false;
                    }
                }
            }
            else if ( idaVolta === false && !carNormal() && espelho.innerHTML[espelho.innerHTML.length - 1] != "(" && carEspecial() ){
                espelho.innerHTML += ")";
                idaVolta = true;
            }
        }
    }

    function trocarSinal (){
        if (event.target === numero[18] && espelho.innerHTML[0] === "0") {
            return;
        }
        else{
            if ( espelho.innerHTML.length > 24 ){
                return;
            }
                else{
                novaString = "-(";
                for ( t = 0; t < espelho.innerHTML.length ; t++ ){
                    novaString += espelho.innerHTML[t];
                }
                novaString += ")";
                espelho.innerHTML = novaString;
            }
        }
    }

    function verificarPrimeiroNumero (){
        if ( espelho.innerHTML[0] == 0 ){
            primeiro = true;
        } 
    }

    function atribuirFuncao (){
        for ( let  i = 2; i < numero.length; i++ ){
            if ( i === 18 || i === 19 ){
             continue;
            }
             numero[i].addEventListener("click", mostrar)
         }
    }
    
    function retomarFuncao  (){
        if ( espelho.innerHTML.length <= 25 ){
            for ( let  i = 2; i < numero.length; i++ ){
                if ( i === 18 || i === 19 ){
                continue;
                }
                numero[i].addEventListener("click", mostrar)
            }
        }
    }

    function mostrar (){
        normalInicial = true;
        normalFinal = true;
        especialFinal = true;
        especialInicial = true;
        if ( espelho.innerHTML.length > 24 ){
            for ( let z = 0; z < numero.length; z++ ){
                numero[z].removeEventListener("click", mostrar);
            }
        }
        else if (event.target === numero[17] && espelho.innerHTML[0] === "0") {
            return;
        }
        else if (ultimoEspecial() === false && carEspecial() === false ) {
            return;
        }
        else if ( 
            ( !especialFinal && espelho.innerHTML === "0" && espelho.innerHTML.length === 1 ) || 
            !especialFinal && espelho.innerHTML[espelho.innerHTML.length - 1] === "(" 
        ) {
            return;
        }
        else if ( event.target.textContent === "." && espelho.innerHTML[espelho.innerHTML.length - 1] === ")"){
            return;
        }
        else if ( espelho.innerHTML[espelho.innerHTML.length - 1] === ")" && !ultimoNormal() ){
            espelho.innerHTML = espelho.innerHTML + "*" + event.target.textContent;
            return;
        }
        else if ( primeiro === true ){
            espelho.innerHTML = "";
            primeiro = false;
        }
        espelho.innerHTML += event.target.textContent;
    }

    function zerar (){
        espelho.innerHTML = "0";
        primeiro = true;
        idaVolta = true;
        retomarFuncao ();
    }

    function remover (){
        if ( espelho.innerHTML.length === 1 ){
            espelho.innerHTML = "0";
            primeiro = true;
            idaVolta = true;
        }
        else {
            if ( espelho.innerHTML[espelho.innerHTML.length - 1] == ")"){
                idaVolta = false;
            }
            else if ( espelho.innerHTML[espelho.innerHTML.length - 1] == "("){
                idaVolta = true;
            }
            novaString = "";
            for ( let r = 0; r < espelho.innerHTML.length - 1; r++ ){
                novaString += espelho.innerHTML[r];
            }
            espelho.innerHTML = "";
            espelho.innerHTML = novaString;
            novaString = "";
            retomarFuncao ();
        }
    }

    function resultado() {
        if ( usado === true ){
            salvar.innerHTML = "";
            usado = false;
        }
        else {
            salvar.innerHTML = "Nenhuma operação feita";
        }
        expressao = espelho.innerHTML;
        resposta = eval(expressao);
        if ( nenhum === true ){
            elementosRemover[0].remove();
        }
        if (verificarDecimal() === true) {
            espelho.innerHTML = resposta.toFixed(2);
            var salvar2 = document.createElement("p");
            salvar2.textContent = expressao + " = " + resposta.toFixed(2);
            historicoTela2.appendChild(salvar2);
            nenhum = false;
            verificarPrimeiroNumero();
        }
        else {
            espelho.innerHTML = resposta;
            var salvar2 = document.createElement("p");
            salvar2.textContent = expressao + " = " + resposta;
            historicoTela2.appendChild(salvar2);
            nenhum = false;
            verificarPrimeiroNumero();
        }
      }

    function verificarDecimal (){
        respostaString = resposta.toString();
        for ( let v = 0; v < respostaString.length; v++ ){
            if ( respostaString[v] === "." ){
                return true;
            }
        }
        return false;
    }

    function reset() {
        while (elementosRemover.length > 0) {
            elementosRemover[0].remove();
        }
        var inicio = document.createElement("p");
        inicio.textContent = "Nenhuma operação feita";
        historicoTela2.appendChild(inicio);
        nenhum = true;
    }

    del.addEventListener("click", zerar);

    numero[1].addEventListener("click", parenteses);

    numero[19].addEventListener("click", resultado);

    numero[18].addEventListener("click", trocarSinal);

    excluir.addEventListener("click", remover);

    historico.addEventListener("click", mudar);

    principal.addEventListener("click", mudar);

    limpar.addEventListener("click", reset);

    atribuirFuncao ();


    function teste (){
        console.log(espelho.innerHTML.length);
        console.log(espelho.innerHTML);
        console.log(event.target.textContent);
    }

});
