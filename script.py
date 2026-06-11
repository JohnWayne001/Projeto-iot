import paho.mqtt.publish as publish

BROKER = "192.168.0.4"  # IP do computador onde o Mosquitto está rodando
TOPICO = "Aula"

while True:

    comando = input("Digite ON ou OFF: ").upper()

    if comando in ["ON", "OFF"]:

        publish.single(
            TOPICO,
            comando,
            hostname=BROKER,
            port=1883
        )

        print(f"Mensagem enviada: {comando}")

    else:

        print("Digite apenas ON ou OFF")