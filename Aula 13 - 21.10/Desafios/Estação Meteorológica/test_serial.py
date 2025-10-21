import serial
import json

try:
    ser = serial.Serial('COM3', 9600, timeout=1)  # Altere para sua porta
    print("Porta serial aberta")
except Exception as e:
    print("Erro ao abrir porta serial:", e)
    exit()

while True:
    linha = ser.readline().decode('utf-8').strip()
    if linha:
        print("Recebido:", linha)
        try:
            dados = json.loads(linha)
            print(f"Temperatura: {dados.get('temperatura')}, Umidade: {dados.get('umidade')}")
        except json.JSONDecodeError:
            print("JSON inválido")
