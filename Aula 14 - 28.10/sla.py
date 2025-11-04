import serial
import time

try:
    arduino = serial.Serial('COM4', 9600, timeout=1)
    time.sleep(2)
    print("Conectado ao Arduino!")
    arduino.close()
except Exception as e:
    print("❌ Erro:", e)