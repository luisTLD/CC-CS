// Dados de exemplo das receitas (substitua isso pelos seus dados reais)
const todasReceitas = [
    { id: 1, nome: 'Bolo de Chocolate', ingredientes: 'Farinha, Ovo, Chocolate', modoDePreparo: 'Passo a passo...' },
    { id: 2, nome: 'Lasanha de Frango', ingredientes: 'Massa de lasanha, Frango, Queijo', modoDePreparo: 'Passo a passo...' },
    // Adicione mais receitas conforme necessário
];

// Função para preencher a tabela com as receitas
function preencherTabelaReceitas() {
    const tableBody = document.getElementById('receitasBody');

    // Limpa o conteúdo atual da tabela
    tableBody.innerHTML = '';

    // Itera sobre todas as receitas e cria uma nova linha na tabela para cada uma
    todasReceitas.forEach((receita, index) => {
        const newRow = tableBody.insertRow();
        newRow.innerHTML = `
            <th scope="row">${index + 1}</th>
            <td>${receita.nome}</td>
            <td>${receita.ingredientes}</td>
            <td>${receita.modoDePreparo}</td>
        `;
    });
}

// Evento que é disparado quando o modal é aberto (Bootstrap)
const modalElement = document.getElementById('recipeModal');
modalElement.addEventListener('shown.bs.modal', function () {
    // Chama a função para preencher a tabela com as receitas ao abrir o modal
    preencherTabelaReceitas();
});
