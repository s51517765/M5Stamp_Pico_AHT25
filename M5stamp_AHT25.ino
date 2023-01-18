
//https://sin1n24.hatenablog.com/entry/2022/09/10/233653
//https://github.com/middle-river/weather_station

#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <WebServer.h>
#include "HTTPClient.h"
#include "auth.h"
#include "AHT25.h"

const char* host = "notify-api.line.me";

WiFiClientSecure client;

WebServer server(80); // ポート80番
#define PIN_SDA 21
#define PIN_SCL 22
String HTML_text = "";
unsigned long t = 0;
//  HTMLを組み立てる
String html1 = "<!DOCTYPE html><html><head><meta charset=\"utf-8\"><title>環境情報</title></head><body><p><h1>";
String html2 = "</h1></p><p><a href=\"/\"><h1>Reload</h1></a></p></body></html>";

void sendLine(String message)
{
  client.setInsecure();
  Serial.printf( "[%lu] LINE Notify Connection \n", millis() );
  if ( !client.connect(host, 443) ) {
    Serial.printf("[%lu] Connection NG \n", millis() );
  }

  String query = String("message=") + message;
  String request = String("") +
                   "POST /api/notify HTTP/1.1\r\n" +
                   "Host: " + host + "\r\n" +
                   "Authorization: Bearer " + token + "\r\n" +
                   "Content-Length: " + String(query.length()) +  "\r\n" +
                   "Content-Type: application/x-www-form-urlencoded\r\n\r\n" +
                   query + "\r\n";
  client.print(request);
}

// HTMLを構成
void handleHTML()
{
  String html = html1 + HTML_text + html2;
  server.send(200, "text/html", html);
}

// 存在しないアドレスが指定された時の処理
void handleNotFound(void)
{
  server.send(404, "text/plain", "Not Found.");
}

String getTemp()
{
  AHT25 sensor(PIN_SDA, PIN_SCL);
  // Seosor Out
  float t = 22;
  float h = 51;
  float p = 1000; // Not Used
  sensor.begin();
  sensor.get(t, h, p);
  String text = "Temperature: " + String(t) + " C <br>" + "Humidity: " + String(h) + " %Rh";
  Serial.println("Temperature: " + String(t) + " C");
  Serial.println("Humidity: " + String(h) + " %");

  return text;
}

void setup() {
  pinMode(25,OUTPUT);
  digitalWrite(25,HIGH);
  // シリアルポートの初期化
  Serial.begin(115200);

  // WiFiのアクセスポイントに接続
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  // ESP32のIPアドレスを出力
  Serial.println("\nWiFi Connected.");
  Serial.print("IP = ");
  String address = WiFi.localIP().toString();
  Serial.println(address);

  // このアドレスにアクセスしたときに処理される関数を指定
  server.on("/", handleHTML);

  server.onNotFound(handleNotFound);
  // Webサーバーを起動
  server.begin();
  //LineでIPアドレスを送信
  sendLine(address);
}

void loop() {
  server.handleClient();

  if (millis() - t > 3000)
  {
    Serial.print("IP = ");
    Serial.println(WiFi.localIP());
    HTML_text = getTemp();
    t = millis();
  }
}
