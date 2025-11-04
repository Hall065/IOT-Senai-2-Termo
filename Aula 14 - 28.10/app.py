from flask import Flask, jsonify
import serial, time, threading
from datetime import datetime

app = Flask(__name__)

# ===== CONFIGURAÇÕES =====
PORTA_SERIAL = "COM3"  # altere se necessário
BAUD_RATE = 9600

ser = serial.Serial(PORTA_SERIAL, BAUD_RATE, timeout=1)
time.sleep(2)

ultima_temp = 0.0
ultimo_status = "Carregando"
ultimo_servo = 0

historico = []  # armazena ultimos valores

# ===== LEITOR DA SERIAL EM THREAD =====
def ler_arduino():
    global ultima_temp, ultimo_status, ultimo_servo, historico

    while True:
        try:
            linha = ser.readline().decode().strip()

            # Espera formato: "Temperatura: 23.5 °C  |  Status: QUENTE  | Servo: 90"
            if "Temperatura" in linha and "Status" in linha and "Servo" in linha:
                partes = linha.split("|")

                temp = partes[0].split(":")[1].replace("°C", "").strip()
                status = partes[1].split(":")[1].strip()
                servo = partes[2].split(":")[1].strip()

                ultima_temp = float(temp)
                ultimo_status = status
                ultimo_servo = int(servo)

                historico.append({
                    "timestamp": datetime.now().strftime("%H:%M:%S"),
                    "temperatura": ultima_temp
                })

                # mantém só últimos 20 pontos
                if len(historico) > 20:
                    historico.pop(0)

        except:
            pass

threading.Thread(target=ler_arduino, daemon=True).start()

# ===== ROTAS WEB =====
@app.route("/status")
def status():
    return jsonify({
        "temperatura": ultima_temp,
        "status": ultimo_status,
        "servo_pos": ultimo_servo,
        "timestamp": datetime.now().strftime("%H:%M:%S"),
        "historico": historico
    })

@app.route("/comando/<cmd>")
def comando(cmd):
    try:
        if cmd == "testar_buzzer":
            ser.write(b"BUZZER_ON\n")
        elif cmd == "parar_buzzer":
            ser.write(b"BUZZER_OFF\n")

        return jsonify({"msg": f"Comando {cmd} enviado"})
    except Exception as e:
        return jsonify({"error": str(e)})

# ===== START =====
if __name__ == "__main__":
    app.run(host="0.0.0.0", port=5000, debug=True)
