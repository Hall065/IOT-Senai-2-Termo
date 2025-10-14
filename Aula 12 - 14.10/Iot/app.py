from flask import Flask, render_template
import serial
import time

try:
    arduino = serial.Serial('COM3', 9600, timeout=1)
    time.sleep(2)
except serial.SerialException as e:
    print(f"Error connecting to Arduino: {e}")
    arduino = None

app = Flask(__name__)

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/control/<led_num>/<action>')
def control_led(led_num, action):
    if arduino:
        comand = ''
        if led_num == '1':
            comand = 'A' if action == 'on' else 'a'
        elif led_num == '2':
            comand = 'B' if action == 'on' else 'b'
        elif led_num == '3':
            comand = 'C' if action == 'on' else 'c'
        if comand:
            arduino.write(comand.encode())
            return f"Comando '{comand}' enviado para o LED {led_num}."
        else:
            return "Comando inválido."
    else:
        return "Arduino not connected."
if __name__ == '__main__':
    app.run(debug=True, host='0.0.0.0', port=5000, use_reloader=False)