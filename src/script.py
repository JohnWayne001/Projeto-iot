import paho.mqtt.client as mqtt

# --- Configurações ---
# Coloque aqui o MESMO IP do seu broker WSL que está na ESP32
BROKER = "192.168.0.4" # Substitua pelo IP correto
PORT = 1883
TOPIC = "esp32/status" # Escolha o tópico que a ESP32 vai usar

def on_connect(client, userdata, flags, reason_code, properties):
    if reason_code == 0:
        print(f"Conectado ao Broker {BROKER} com sucesso!")
        client.subscribe(TOPIC)
        print(f"Inscrito no tópico: {TOPIC}")
    else:
        print(f"Falha ao conectar. Código: {reason_code}")

def on_message(client, userdata, msg):
    print(f"[Mensagem Recebida] Tópico: {msg.topic} | Payload: {msg.payload.decode('utf-8')}")

# Inicializa o cliente MQTT
client = mqtt.Client(mqtt.CallbackAPIVersion.VERSION2)
client.on_connect = on_connect
client.on_message = on_message

try:
    print(f"Tentando conectar ao broker {BROKER}...")
    client.connect(BROKER, PORT, 60)
    # Fica em loop infinito escutando as mensagens
    client.loop_forever()
except KeyboardInterrupt:
    print("\nEncerrando...")
    client.disconnect()