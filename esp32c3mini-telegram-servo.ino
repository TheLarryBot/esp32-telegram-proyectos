#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>
#include <ESP32Servo.h>

const char* ssid     = "hola";
const char* password = "88888888";
#define TOKEN   "TOKEN
#define CHAT_ID "ID"

#define PIN_SERVO 5

WiFiClientSecure cliente;
UniversalTelegramBot bot(TOKEN, cliente);
Servo servo;

void setup() {
  Serial.begin(115200);
  delay(1000);

  servo.attach(PIN_SERVO);
  servo.write(0);
  Serial.println("Servo listo en 0 grados");

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Conectando WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConectado! IP: " + WiFi.localIP().toString());

  cliente.setInsecure();
  bot.sendMessage(CHAT_ID, "Servo listo! Escribe /mover_90", "");
  Serial.println("Bot conectado!");
}

void loop() {
  int mensajes = bot.getUpdates(bot.last_message_received + 1);

  for (int i = 0; i < mensajes; i++) {
    String texto = bot.messages[i].text;
    Serial.println("Llego: " + texto);

    if (texto.startsWith("/mover_")) {
      int grados = texto.substring(7).toInt();
      grados = constrain(grados, 0, 180);
      servo.write(grados);
      Serial.println("Moviendo a: " + String(grados));
      bot.sendMessage(CHAT_ID, "Servo en: " + String(grados) + " grados", "");
    }

    if (texto == "/ayuda" || texto == "/start") {
      String menu = "Comandos:\n\n";
      menu += "/mover_0   - Va a 0 grados\n";
      menu += "/mover_90  - Va a 90 grados\n";
      menu += "/mover_180 - Va a 180 grados\n";
      menu += "/mover_N   - Va a N grados (0-180)";
      bot.sendMessage(CHAT_ID, menu, "");
    }
  }

  delay(2000);
}
