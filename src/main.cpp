#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>

// WIFI
const char* ssid = "iot";
const char* password = "iotsenai502";

// MQTT
const char* mqtt_server = "192.168.0.4";
const int mqtt_port = 1883;

// LED
#define LED_PIN 4

WiFiClient espClient;
PubSubClient client(espClient);

void callback(char* topic, byte* payload, unsigned int length)
{
    String mensagem = "";

    for (unsigned int i = 0; i < length; i++)
    {
        mensagem += (char)payload[i];
    }

    Serial.print("Mensagem recebida: ");
    Serial.println(mensagem);

    if (mensagem == "ON")
    {
        digitalWrite(LED_PIN, HIGH);
    }

    if (mensagem == "OFF")
    {
        digitalWrite(LED_PIN, LOW);
    }
}

void conectarWifi()
{
    Serial.print("Conectando ao WiFi");

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }

    Serial.println();
    Serial.println("WiFi conectado");

    Serial.print("IP: ");
    Serial.println(WiFi.localIP());
}

void conectarMQTT()
{
    while (!client.connected())
    {
        Serial.println("Conectando MQTT...");

        String clientId = "ESP32-";
        clientId += String(random(0xffff), HEX);

        if (client.connect(clientId.c_str()))
        {
            Serial.println("MQTT conectado");

            client.subscribe("Aula");
        }
        else
        {
            Serial.print("Erro MQTT: ");
            Serial.println(client.state());

            delay(3000);
        }
    }
}

void setup()
{
    Serial.begin(115200);

    pinMode(LED_PIN, OUTPUT);

    conectarWifi();

    client.setServer(mqtt_server, mqtt_port);
    client.setCallback(callback);
}

void loop()
{
    if (!client.connected())
    {
        conectarMQTT();
    }

    client.loop();
}