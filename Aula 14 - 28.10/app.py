import serial
import threading
import time
import json
import os
from flask import Flask, jsonify, send_from_directory

app = Flask(__name__)

# Variáveis globais
temperatura_atual = None
status_atual = None
servo_pos = None
historico = []

# Porta serial
PORTA = "COM3"
BAUD = 9600

try:
    ser = serial.Serial(PORTA, BAUD, timeout=1, write_timeout=1)
    print("✅ Porta serial conectada.")
    time.sleep(2)
except:
    print("⚠️ Não foi possível abrir a porta serial.")
    ser = None


# Thread leitura Serial
def ler_serial():
    global temperatura_atual, status_atual, servo_pos, historico

    while True:
        if ser is None:
            time.sleep(1)
            continue

        try:
            linha = ser.readline().decode().strip()
            if not linha:
                continue

            print("📩 Recebido:", linha)

            dados = json.loads(linha)

            temperatura_atual = dados.get("temperatura")
            status_atual = dados.get("status")
            servo_pos = dados.get("servo_pos")

            timestamp = time.strftime("%H:%M:%S")

            historico.append({"temperatura": temperatura_atual, "timestamp": timestamp})

            # Mantém apenas últimos 30 pontos
            historico = historico[-30:]

        except json.JSONDecodeError:
            pass
        except Exception as e:
            print("Erro:", e)

        time.sleep(0.2)


# Página (se quiser usar arquivos locais)
@app.route("/")
def index():
    return send_from_directory(".", "index.html")


# Rota para frontend buscar dados
@app.route("/status")
def status():
    if temperatura_atual is None:
        return jsonify({"error": "Sem dados ainda"})

    return jsonify({
        "temperatura": temperatura_atual,
        "status": status_atual,
        "servo_pos": servo_pos,
        "timestamp": time.strftime("%H:%M:%S"),
        "historico": historico
    })


# Enviar comando pro Arduino
@app.route("/comando/<cmd>")
def comando(cmd):
    if ser and ser.is_open:
        ser.write((cmd + "\n").encode())
        print(f"🚀 Enviado comando: {cmd}")
        return jsonify({"status": "ok", "cmd": cmd})
    return jsonify({"status": "erro"})


# Fecha serial ao sair
import atexit
@atexit.register
def fechar():
    if ser and ser.is_open:
        ser.close()


# Iniciar thread e servidor
if __name__ == "__main__":
    t = threading.Thread(target=ler_serial, daemon=True)
    t.start()

    app.run(debug=True, use_reloader=False)
