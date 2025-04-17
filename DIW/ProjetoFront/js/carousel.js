document.addEventListener('DOMContentLoaded', function () {
    let lastClickedIndex = -1;

    document.querySelectorAll('.cards label').forEach((label, index) => {
        label.addEventListener('click', (e) => {
            const radios = document.querySelectorAll('input[name="slider"]');
            const currentRadio = radios[index];

            // Se já está na frente e clicou de novo => abre o modal
            if (currentRadio.checked && lastClickedIndex === index) {
                const modalId = `#modal${index + 1}`;
                const modal = new bootstrap.Modal(document.querySelector(modalId));
                modal.show();
            }

            // Armazena o último clique
            lastClickedIndex = index;
        });
    });
});
