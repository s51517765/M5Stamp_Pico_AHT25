# M5Stamp Pico with AHT25

## 概要 (Overview)

M5Stamp Pico のチュートリアルとしてAHT25とLine notifyを試してみた。

M5Stamp Picoでローカルサーバーを立ち上げ、そのIPアドレスにアクセスすると、AHT25による環境値が見れる。

M5Stamp Picoを起動時にLineでIPアドレスを送信することでスマホから容易にアクセスできる。

## 動作要件 (Requirements)

M5Stamp Pico / Arduino IDE / AHT25 / Line notify

## 回路図 (Circuit diagram)

|M5Stamp|AHT25|
|---|---|
|3.3V|VCC|
|SDA 21|SDA|
|GND|GND|
|SCL 22|SCL|

M5Stamp PicoにはUSBポートがないので書き込みにはUSB Serial を使う。

接続は以下のようにし、この状態でM5Stamp Picoを再起動する。

|USB Serial|M5Stamp|
|---|---|
|VCC (5V)|5V|
|RX|TX|
|TX|RX|
|GND|GND|
|GND|G0|

## 技術的解説 (Technical explanation)

https://s51517765.hatenadiary.jp/entry/2023/01/23/073000

## 引用 (Reference)
https://github.com/middle-river/weather_station

Arduino IDEを使う場合は、上記weather_stationリポジトリのAHT25.hをArudino/libraries/AHT25/にコピーする。

https://sin1n24.hatenablog.com/entry/2022/09/10/233653

https://github.com/s51517765/ESP32_AHT25

PlatformIOを使う場合は上記ESP32_AHT25リポジトリを参考にしてください。

## ライセンス (License)

This software is released under the MIT License, see LICENSE.
