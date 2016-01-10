// Importando as bibliotecas necessárias
#include "ESP8266WiFi.h"
#include "DHT.h"

// Definições da rede wireless 
const char* ssid = "SSID";
const char* password = "password";

// Setando o endereço estico do Arduino na rede
IPAddress ip(192, 168, 0, 11); //Node static IP
IPAddress gateway(192, 168, 0, 1);
IPAddress subnet(255, 255, 255, 0);

// Pin
#define DHTPIN D12

// Use DHT11 sensor
#define DHTTYPE DHT22

// Initialize DHT sensor
DHT dht(DHTPIN, DHTTYPE, 15);

String inputString      = "";
boolean stringComplete  = false;

// Host
const char* host = "192.168.0.7";

void setup() {

  // Start Serial
  Serial.begin(115200);
  delay(10);

  // Init DHT
  dht.begin();

  // We start by connecting to a WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  WiFi.config(ip, gateway, subnet);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  pinMode(buzzer, OUTPUT);
}

void loop() {

  Serial.print("Estabelecendo conexão...");
  Serial.println(host);

  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 1337;

  if (!client.connect(host, httpPort)) {
    Serial.println("Sem conexão com o servidor...");
    return;
  } else {
    Serial.println();
    Serial.println("Conectado ao servidor...");
    Serial.println(host);
  }

  // Reading temperature and humidity
  int h = dht.readHumidity();
  // Read temperature as Celsius
  int t = dht.readTemperature();

  // form a JSON-formatted string:
  String jsonString = "{\"temperatura\":\"";
  jsonString += t;
  jsonString += "\",\"umidade\":\"";
  jsonString += h;
  jsonString += "\"}";

  // print it:
  client.print(jsonString);




  // Read all the lines of the reply from server and print them to Serial
  while (client.available()) {
    char inChar = (char)client.read();
    inputString += inChar;
    if (inChar == '\r') {
      stringComplete = true;
    }
  }


  Serial.println("Dados enviados com sucesso");

  // Repeat every 3 seconds
  delay(3000);

}
