from flask import Flask, render_template, jsonify
import serial
import time
import serial.tools.list_ports

# === CONFIGURAÇÃO ARDUINO UNO ===
def encontrar_arduino_uno():
    """Tenta encontrar automaticamente o Arduino Uno"""
    ports = list(serial.tools.list_ports.comports())
    for p in ports:
        # Procura por Arduino Uno nas descrições
        if 'arduino' in p.description.lower() or 'uno' in p.description.lower():
            print(f"✅ Arduino Uno encontrado em: {p.device}")
            return p.device
        # Ou por CH340 (clone comum do Uno)
        elif 'CH340' in p.description:
            print(f"✅ Arduino (CH340) encontrado em: {p.device}")
            return p.device
    
    # Se não encontrou, lista todas as portas
    print("❌ Arduino Uno não encontrado automaticamente.")
    print("📋 Portas disponíveis:")
    for p in ports:
        print(f"   - {p.device}: {p.description}")
    
    return None

# Tenta encontrar automaticamente OU use uma porta fixa
SERIAL_PORT = 'COM5'  # ⚠️ AJUSTE SE PRECISAR!
BAUDRATE = 9600

print(f"🎯 Tentando conectar na porta: {SERIAL_PORT}")

try:
    arduino = serial.Serial(SERIAL_PORT, BAUDRATE, timeout=1)
    time.sleep(2)  # Dar tempo para o Uno inicializar
    print(f"✅ Conectado ao Arduino Uno em {SERIAL_PORT}")
    print("📊 Aguardando dados...")
except Exception as e:
    print(f"❌ Falha na conexão: {e}")
    print("\n🔧 SOLUÇÕES:")
    print("1. Verifique se o cabo USB está conectado")
    print("2. Feche o Arduino IDE (pode estar usando a porta)")
    print("3. Tente outras portas: COM2, COM3, COM4...")

app = Flask(__name__)

historico_temperatura = []

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/status')
def status():
    if not arduino:
        return jsonify({"error": "Arduino Uno não conectado"}), 500

    try:
        # Lê TODAS as linhas disponíveis para evitar atraso
        while arduino.in_waiting > 10:
            arduino.readline()  # Limpa buffer antigo
        
        if arduino.in_waiting > 0:
            raw = arduino.readline().decode('utf-8', errors='ignore').strip()
            
            if raw and "Temperatura:" in raw and "Status:" in raw:
                print(f"📨 Dados Uno: {raw}")
                
                # Processa o formato do seu código
                try:
                    temp_str = raw.split("Temperatura: ")[1].split(" °C")[0]
                    status_str = raw.split("Status: ")[1].split("  |")[0]
                    servo_str = raw.split("Servo: ")[1]
                    
                    temperatura = float(temp_str)
                    servo_pos = int(servo_str)
                    
                    # Adiciona ao histórico
                    timestamp = time.strftime("%H:%M:%S")
                    historico_temperatura.append({
                        "temperatura": temperatura,
                        "timestamp": timestamp,
                        "status": status_str
                    })
                    
                    if len(historico_temperatura) > 20:
                        historico_temperatura.pop(0)
                    
                    return jsonify({
                        "temperatura": temperatura,
                        "status": status_str,
                        "servo_pos": servo_pos,
                        "timestamp": timestamp,
                        "historico": historico_temperatura[-10:],
                        "error": None
                    })
                    
                except Exception as e:
                    print(f"⚠️ Erro ao processar: {e}")
                    return jsonify({"error": f"Formato inválido: {raw}"}), 502
        
        return jsonify({"error": "Aguardando dados do Uno..."}), 502
        
    except Exception as e:
        print(f"❌ Erro na comunicação: {e}")
        return jsonify({"error": str(e)}), 500

@app.route('/comando/<cmd>')
def comando(cmd):
    if not arduino:
        return jsonify({"error": "Arduino não conectado"}), 500

    try:
        if cmd == 'testar_buzzer':
            arduino.write(b'T')  # Comando de teste
            return jsonify({"status": "comando enviado"})
        elif cmd == 'parar_buzzer':
            arduino.write(b'S')  # Comando de stop
            return jsonify({"status": "comando enviado"})
        else:
            return jsonify({"error": "Comando desconhecido"}), 400
    except Exception as e:
        return jsonify({"error": str(e)}), 500

if __name__ == '__main__':
    print("\n🚀 Iniciando servidor para Arduino Uno...")
    print("🌐 Acesse: http://localhost:5000")
    app.run(debug=True, host='0.0.0.0', port=5000)