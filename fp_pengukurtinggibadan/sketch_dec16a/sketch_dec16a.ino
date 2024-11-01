// ID, Nama Template, dan Token Authentikasi Blynk
#define BLYNK_TEMPLATE_ID "TMPL6wS4966Ij"
#define BLYNK_TEMPLATE_NAME "Quickstart Template"
#define BLYNK_AUTH_TOKEN "4oi5YVKU3D0HQ9mBdXdOD6i1IvjG38m_"  

// Library yang diperlukan
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <BlynkSimpleEsp8266.h>  

// Pin untuk sensor ultrasonik
#define trigPin D7
#define echoPin D6

// Inisialisasi objek LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Variabel untuk perhitungan tinggi
int jarak = 200;
int tinggi;

// Informasi jaringan Wi-Fi
char ssid[] = "Redmi Note 8";
char pass[] = "makanbang";
char auth[] = "4oi5YVKU3D0HQ9mBdXdOD6i1IvjG38m_";

void setup() {
  // Inisialisasi komunikasi serial dan konfigurasi pin
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Konfigurasi dan inisialisasi LCD
  lcd.init();
  lcd.backlight();
  lcd.setCursor(2, 0);
  lcd.print("ALAT PENGUKUR");
  delay(1000);
  lcd.setCursor(2, 1);
  lcd.print("TINGGI BADAN");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("TINGGIMU: ");

  // Memulai koneksi Blynk
  Blynk.begin(auth, ssid, pass);
}

void loop() {
  // Menjalankan fungsi-fungsi Blynk
  Blynk.run();

  // Membaca data dari sensor ultrasonik
  long duration, gape;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  gape = (duration / 2) / 29.1;
  tinggi = jarak - gape;

  // Menampilkan hasil pengukuran di LCD
  lcd.setCursor(10, 0);
  lcd.print(tinggi);
  lcd.print(" ");
  lcd.print("CM");
  lcd.print(" ");

  // Mengirim data ke pin virtual di Blynk
  Blynk.virtualWrite(V6, "TINGGIMU: " + String(tinggi) + " CM");
  Blynk.virtualWrite(V7, tinggi);
  
  // Menunggu sebentar sebelum melakukan pengukuran berikutnya
  delay(100);
}
