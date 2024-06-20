let count = 0;
let timer = null;
let startTime = null;
let btn = document.getElementById('btn');
let resetBtn = document.getElementById('resetBtn');

btn.addEventListener('click', function() {
  if (timer === null) {
    startTime = Date.now();
    timer = setInterval(function() {
      const elapsedSeconds = Math.floor((Date.now() - startTime) / 1000);
      document.getElementById('time').innerText = 'Time: ' + elapsedSeconds;
      if (elapsedSeconds >= 5) {
        clearInterval(timer);
        timer = null;
        document.getElementById('cpsResult').innerText = 'Média CPS: ' + (count / 5).toFixed(2) + ' Total de cliques: ' + count;
        btn.disabled = true;
      }
    }, 1000);
  }
  count++;
});

resetBtn.addEventListener('click', function() {
  count = 0;
  if (timer !== null) {
    clearInterval(timer);
    timer = null;
  }
  startTime = null;
  document.getElementById('time').innerText = 'Time: 0';
  document.getElementById('cpsResult').innerText = 'Click';
  btn.disabled = false;
});