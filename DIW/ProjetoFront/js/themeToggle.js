document.addEventListener("DOMContentLoaded", function () {
    const btn = document.getElementById('toggle-theme');
    const icon = document.getElementById('theme-icon');
    const body = document.body;

    // Garante modo escuro ao iniciar
    body.setAttribute('data-bs-theme', 'dark');

    // Garante ícone correto ao iniciar
    if (icon) {
        icon.className = 'bi bi-moon-fill';
    }

    btn.addEventListener('click', () => {
        const atual = body.getAttribute('data-bs-theme') || 'light';
        const novo = atual === 'dark' ? 'light' : 'dark';
        body.setAttribute('data-bs-theme', novo);

        if (icon) {
            icon.className = novo === 'dark' ? 'bi bi-moon-fill' : 'bi bi-sun-fill';
        }
    });
});
