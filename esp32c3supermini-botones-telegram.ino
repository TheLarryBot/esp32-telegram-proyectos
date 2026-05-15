#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>

const char* ssid     = "hola";
const char* password = "88888888";
#define TOKEN   "8203910516:AAEqMl2IhO12NvBbcrdpq-vK0i3682uaoWk"
#define CHAT_ID "1249279984"

#define TOUCH1  4
#define TOUCH2  5

WiFiClientSecure cliente;
UniversalTelegramBot bot(TOKEN, cliente);

void setup() {
  Serial.begin(115200);

  pinMode(TOUCH1, INPUT);
  pinMode(TOUCH2, INPUT);

  WiFi.begin(ssid, password);
  Serial.print("Conectando");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500); Serial.print(".");
  }
  Serial.println("\nConectado!");

  cliente.setInsecure();
  bot.sendMessage(CHAT_ID, "Listo! Toca un boton", "");
}

void loop() {
  if (digitalRead(TOUCH1) == HIGH) {
    bot.sendMessage(CHAT_ID, "Tocaron el Boton 1!", "");
    delay(2000);
  }

  if (digitalRead(TOUCH2) == HIGH) {
    bot.sendMessage(CHAT_ID, "Tocaron el Boton 2!", "");
    delay(2000);
  }
}
