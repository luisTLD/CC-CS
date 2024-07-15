window.onload = function () {

    // Fetch, HTML para a div com ID expecifico -> NomeDoHTML + Copy

    fetch('../createRecipeModal.html')
        .then(response => response.text())
        .then(data => {
            document.getElementById('createRecipeCopy').innerHTML = data;
        });


}