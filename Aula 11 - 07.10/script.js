    // comportamento simples de UI + exemplo de integração
    document.querySelectorAll('.btn').forEach(btn => {
      btn.addEventListener('click', async (e) => {
        const led = btn.dataset.led;
        const action = btn.dataset.action; // 'on' ou 'off'

        // atualizar a UI localmente
        const statusEl = document.getElementById('status-' + led);
        if(action === 'on'){
          statusEl.textContent = 'ON';
          statusEl.classList.remove('off');
          statusEl.classList.add('on');
        } else {
          statusEl.textContent = 'OFF';
          statusEl.classList.remove('on');
          statusEl.classList.add('off');
        }

        // envie o comando ao Arduino. Exemplo comentado:
        // await sendCommand(led, action);
      });
    });

    // Exemplo genérico de função para integrar com Arduino via HTTP
    // Ajuste a URL e payload conforme seu servidor/ESP.
    async function sendCommand(led, action){
      try{
        const resp = await fetch('http://IP_DO_SEU_ARDUINO/led', {
          method:'POST',
          headers:{'Content-Type':'application/json'},
          body: JSON.stringify({led: Number(led), state: action})
        });
        const j = await resp.json();
        console.log('Resposta do Arduino:', j);
      }catch(err){
        console.error('Erro ao conectar com Arduino:', err);
      }
    }