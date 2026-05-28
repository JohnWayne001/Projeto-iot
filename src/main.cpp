#include <WiFi.h>
#include <Arduino.h>
#include <PubSubClient.h>

// ===== WIFI =====
const char* ssid = "iot";
const char* password = "iotsenai502";

// ===== MQTT =====
const char* mqtt_server = "192.168.0.4";
const int mqtt_port = 1883;

// ===== LED =====
#define LED 27

WiFiClient espClient;
PubSubClient client(espClient);

// ===== FUNÇÃO QUANDO CHEGAR MENSAGEM =====
void callback(char* topic, byte* payload, unsigned int length) {

  Serial.print("Mensagem recebida no tópico: ");
  Serial.println(topic);

  String mensagem = "";

  for (int i = 0; i < length; i++) {
    mensagem += (char)payload[i];
  }

  Serial.print("Mensagem: ");
  Serial.println(mensagem);

  // ===== CONTROLE DO LED =====

  if (mensagem == "ON") {

    digitalWrite(LED, HIGH);

    Serial.println("LED LIGADO");
  }

  if (mensagem == "OFF") {

    digitalWrite(LED, LOW);

    Serial.println("LED DESLIGADO");
  }
}

// ===== CONECTAR WIFI =====
void setup_wifi() {

  delay(10);

  Serial.println();
  Serial.print("Conectando no WiFi: ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {

    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi conectado!");

  Serial.print("IP da ESP32: ");
  Serial.println(WiFi.localIP());
}

// ===== RECONECTAR MQTT =====
void reconnect() {

  while (!client.connected()) {

    Serial.print("Conectando ao MQTT...");

    String clientId = "ESP32Client-";
    clientId += String(random(0xffff), HEX);

    if (client.connect(clientId.c_str())) {

      Serial.println(" conectado!");

      // ===== TÓPICO =====
      client.subscribe("Aula");

    } else {

      Serial.print(" falhou, rc=");
      Serial.print(client.state());

      Serial.println(" tentando novamente em 5 segundos");

      delay(5000);
    }
  }
}

// ===== SETUP =====
void setup() {

  Serial.begin(115200);

  pinMode(LED, OUTPUT);

  setup_wifi();

  client.setServer(mqtt_server, mqtt_port);

  client.setCallback(callback);
}

// ===== LOOP =====
void loop() {

  if (!client.connected()) {

    reconnect();
  }

  client.loop();
}