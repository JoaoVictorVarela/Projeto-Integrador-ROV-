import pygame
import serial 
import time 

# Inicializa o pygame
pygame.init()

# Inicializa o joystick
joystick = pygame.joystick.Joystick(0)
time.sleep(2)
joystick.init()
time.sleep(2)

#    Configura a porta serial do Arduino
arduino = serial.Serial('COM20', 9600)  # Ajuste a porta conforme necessário

# Função para enviar dados via serial para o Arduino
def send_data(x1,y1,button_state,button_state_1):
    data = f"{x1},{y1},{button_state},{button_state_1}\n"
    arduino.write(data.encode())

# Loop principal
try:
    while True:
        pygame.event.pump()  # Atualiza os eventos do joystick

        # Lê os valores dos eixos X e Y do joystick maior
        x1_axis = joystick.get_axis(0)
        y1_axis = joystick.get_axis(1)


        # Converte para o intervalo 0-255
        x1_value = int((x1_axis + 1) * 127.5)
        y1_value = int((y1_axis + 1) * 127.5)
       

        # Lê os estados dos botões 0 e 1
        button_state = joystick.get_button(0)  # Botão 0 (gatilho do joystick)
        button_state_1 = joystick.get_button(1)  # Botão 0 (gatilho do joystick)
         
        # Envia os dados para o Arduino
        send_data(x1_value,y1_value,button_state,button_state_1)

        time.sleep(0.5)
 
except KeyboardInterrupt:
    print("Programa interrompido.")
    arduino.close()

   