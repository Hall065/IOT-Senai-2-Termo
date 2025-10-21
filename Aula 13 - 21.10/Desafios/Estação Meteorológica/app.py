import serial
import threading
import time
import json
from flask import Flask, jsonify, render_template

app = Flask(__name__)

# Variáveis globais
temperatura_atual = None
umidade_atual = None
estado_leds = {1: False, 2: False}

# 🔹 Tenta conectar ao Arduino
try:
    ser = serial.Serial('COM3', 9600, timeout=1)
    print("✅ Porta serial aberta com sucesso.")
    time.sleep(2)  # espera o Arduino reiniciar
except serial.SerialException:
    print("⚠️ Erro: Porta serial não encontrada. Verifique a conexão e a porta.")
    ser = None


# 🔹 Thread que lê os dados do Arduino continuamente
def ler_serial():
    global temperatura_atual, umidade_atual
    while True:
        if ser is None:
            time.sleep(1)
            continue
        try:
            linha = ser.readline().decode('utf-8').strip()
            if linha:
                print(f"📩 Recebido da serial: {linha}")
                dados = json.loads(linha)  # tenta converter o JSON
                temperatura_atual = dados.get("temperatura")
                umidade_atual = dados.get("umidade")
                print(f"🌡️ Temp: {temperatura_atual} °C | 💧 Umid: {umidade_atual} %")
        except json.JSONDecodeError:
            # se o Arduino mandou algo estranho, só ignora
            pass
        except Exception as e:
            print(f"⚠️ Erro ao ler Serial: {e}")
        time.sleep(0.1)


# 🔹 Página principal
@app.route('/')
def index():
    return render_template('index.html')


# 🔹 Retorna os dados lidos do sensor
@app.route('/get_data')
def get_data():
    global temperatura_atual, umidade_atual
    if temperatura_atual is None or umidade_atual is None:
        # agora em vez de "erro", devolve 0 pra não travar o site
        return jsonify({"temperatura": 0, "umidade": 0})
    return jsonify({
        "temperatura": temperatura_atual,
        "umidade": umidade_atual
    })


# 🔹 Controle dos LEDs (envia comando via Serial)
@app.route('/controlar/<int:led_num>/<string:acao>')
def controlar_led(led_num, acao):
    global estado_leds

    if led_num not in estado_leds:
        return jsonify({"status": "erro", "mensagem": "LED inválido"}), 400
    if acao not in ['on', 'off']:
        return jsonify({"status": "erro", "mensagem": "Ação inválida"}), 400

    estado_leds[led_num] = (acao == 'on')

    if ser and ser.is_open:
        comando = f"LED{led_num}_{acao.upper()}\n"
        ser.write(comando.encode())
        print(f"🚀 Enviado para Arduino: {comando.strip()}")

    print(f"💡 LED {led_num} {'ligado' if estado_leds[led_num] else 'desligado'}")
    return jsonify({"status": "sucesso", "led": led_num, "acao": acao})


# 🔹 Inicialização do servidor Flask
if __name__ == '__main__':
    # inicia a thread da serial antes do servidor
    thread_serial = threading.Thread(target=ler_serial)
    thread_serial.daemon = True
    thread_serial.start()

    print("⌛ Aguardando primeira leitura do Arduino...")
    time.sleep(3)  # garante que o Arduino já enviou algo

    app.run(debug=True, use_reloader=False)
