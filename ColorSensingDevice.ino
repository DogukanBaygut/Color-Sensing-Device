/*IEE Project  2021-2022
 App No : 1
 App Name : Color Sensor Device
 Author: Dogukan
 Version: v1
 Last Update: 25.12.2021
 */

#include <LiquidCrystal.h> //LCD kütüphanesini kodumuza dahil ediyoruz

#define s0 8 //Bağladığımız pinlere göre tanımlamalarımızı yapıyoruz
#define s1 9
#define s2 10
#define s3 11
#define sensorOut 12
#define r A0    // Kırmızı(Red) led pinimizi tanımlıyoruz.
#define g A1    // Yeşil(Green) led pinimizi tanımlıyoruz.
int buzzer=A2; // Buzzerı tanımlıyoruz
LiquidCrystal lcd(7, 6, 5, 4, 3, 2); //LCD pinlerini tanımlıyoruz
int K, Y, M = 0; //3 ana renk için değişken tanımlıyoruz

void setup() {

  lcd.begin(16, 2);
  pinMode(s0, OUTPUT); //S0, S1, S2 ve S3 pinlerini OUTPUT olarak tanımlıyoruz
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);
  pinMode(g, OUTPUT);
  pinMode(r, OUTPUT);
  pinMode(buzzer,OUTPUT);
  
  pinMode(sensorOut, INPUT); //OUT pinini INPUT olarak tanımlıyoruz

  digitalWrite(s1, LOW); //Frekans ölçeğimizi %20 olarak tanımlıyoruz
  digitalWrite(s0, HIGH);
  Serial.begin(9600);

}

void loop() {

  lcd.print("K=");
  digitalWrite(s2, LOW); //Kırmızıyı filtrele
  digitalWrite(s3, LOW);
  K = pulseIn(sensorOut, LOW); //OUT pini üzerindeki LOW süresini okur
  Serial.print("Kırmızı= ");
  Serial.print(K); //Kırmızı için aldığımız değeri serial monitöre yazdır
  Serial.print("  ");
  lcd.print(K); //Kırmızı için aldığımız değeri LCD ekrana yazdır
  lcd.print("  ");
  lcd.setCursor(7, 0); //İmleci 7. sütuna al
  delay(50); //50 milisaniye bekle

  lcd.print("Y=");
  digitalWrite(s2, HIGH); //Yeşili filtrele
  digitalWrite(s3, HIGH);
  Y = pulseIn(sensorOut, LOW); //OUT pini üzerindeki LOW süresini okur
  Serial.print("Yeşil= ");
  Serial.print(Y); //Yeşil için aldığımız değeri serial monitöre yazdır
  Serial.print("   ");
  lcd.print(Y); //Yeşil için aldığımız değeri LCD ekrana yazdır
  delay(50);

  lcd.setCursor(4, 1); //İmleci 2. satır 4. sütuna taşı
  lcd.print("M=");
  digitalWrite(s2, LOW); //Maviyi filtrele
  digitalWrite(s3, HIGH);
  M = pulseIn(sensorOut, LOW); //OUT pini üzerindeki LOW süresini okur
  Serial.print("Mavi= ");
  Serial.print(M); //Mavi için aldığımız değeri serial monitöre yazdır
  Serial.println();
  lcd.print(M); //Mavi için aldığımız değeri LCD ekrana yazdır
  lcd.setCursor(0, 0);
  delay(1000); //1000 milisaniye bekle
  //Renk değerlerini 1 saniye boyunca ekranda göreceğiz

  lcd.clear(); //Ekranı temizle
  delay(150); //150 milisaniye bekle

  
  //Kalibrasyon bölümünde elde ettiğimiz değerleri bu kısımda kullanacağız
  if (K < 70 && M < 70 && Y < 70) //Eğer tüm renklerin yoğunluğu yüksekse: Beyaz
  {
    lcd.setCursor(1, 0); //İmleci 1. sütuna al
    lcd.print("Algilanan Renk");
    lcd.setCursor(2, 1); //İmleci 2. satır 2. sütuna al
    Serial.print("Renk = Beyaz   ");
    lcd.print("Beyaz"); //Ekrana Beyaz yazdırır.
    digitalWrite(buzzer,HIGH); //Buzzerı aç.
    digitalWrite(g,HIGH);    // Yeşil Ledi aç.
    delay(100);             // 0.1 saniye delay koy.
    digitalWrite(g,LOW);   // Yeşil Ledi kapa.
    digitalWrite(buzzer,LOW); // Buzzerı Kapa.
  } else if (K < 100 && Y < M && abs(K - Y) < 20)
  
  //Kırmızı yoğunluğu yüksek ve yeşille arasındaki değer 20'den azsa: Sarı
  { 
    lcd.setCursor(1, 0); //İmleci 1. sütuna al
    lcd.print("Algilanan Renk");
    lcd.setCursor(2, 1); //İmleci 2. satır 2. sütuna al
    Serial.print("Renk = Sarı   ");
    lcd.print("Sari");
    digitalWrite(buzzer,HIGH); //Buzzerı aç.
    digitalWrite(g,HIGH);  // Yeşil Ledi aç.
    delay(100);            // 0.1 saniye delay koy.
    digitalWrite(g,LOW);   // Yeşil Ledi kapa.
    digitalWrite(buzzer,LOW); // Buzzerı Kapa.
  } else if (K < 100 && M < Y && abs(M - K) < 20)
  //Kırmızı yoğunluğu yüksek ve mavi ile arasındaki değer 20'den azsa: Magenta
  {
    lcd.setCursor(1, 0); //İmleci 1. sütuna al
    lcd.print("Algilanan Renk");
    lcd.setCursor(2, 1); //İmleci 2. satır 2. sütuna al
    Serial.print("Renk = Magenta   ");
    lcd.print("Magenta"); //Ekrana Magenta yazdırır.
    digitalWrite(buzzer,HIGH); //Buzzerı aç.
    digitalWrite(g,HIGH);  // Yeşil Ledi aç.
    delay(100);          // 0.1 saniye delay koy.
    digitalWrite(g,LOW);  // Yeşil Ledi kapa.
    digitalWrite(buzzer,LOW); // Buzzerı Kapa.
  } else if (Y < 130 && Y < M && Y < K)
  //Yeşil yoğunluğu belli bir seviyenin üstünde ve kırmızı-maviden daha yoğunsa: Yeşil
  {
    lcd.setCursor(1, 0); //İmleci 1. sütuna al
    lcd.print("Algilanan Renk");
    lcd.setCursor(2, 1); //İmleci 2. satır 2. sütuna al
    Serial.print("Renk = Yeşil   ");
    lcd.print("Yesil");  // Ekrana Yeşil yazdırır.
    digitalWrite(buzzer,HIGH); //Buzzerı aç.
    digitalWrite(g,HIGH);  // Yeşil Ledi aç.
    delay(100);          // 0.1 saniye delay koy.
    digitalWrite(g,LOW);  // Yeşil Ledi kapa.
    digitalWrite(buzzer,LOW); // Buzzerı Kapa.
  } else if (M < 100 && M < Y && M < K)
  //Mavi yoğunluğu belli bir seviyenin üstünde ve yeşil-kırmızıdan daha yoğunsa: Mavi
  {
    lcd.setCursor(1, 0); //İmleci 1. sütuna al
    lcd.print("Algilanan Renk");
    lcd.setCursor(2, 1); //İmleci 2. satır 2. sütuna al
    Serial.print("Renk = Mavi   ");
    lcd.print("Mavi"); // Ekrana Mavi yazdırır.
    digitalWrite(buzzer,HIGH); //Buzzerı aç.
    digitalWrite(g,HIGH); // Yeşil Ledi aç.
    delay(100);          // 0.1 saniye delay koy.
    digitalWrite(g,LOW); // Yeşil Ledi kapa.
    digitalWrite(buzzer,LOW); // Buzzerı Kapa.
  } else if (K < 100 && K < Y && K < M)
  //Kırmızı yoğunluğu belli bir seviyenin üstünde ve yeşil-maviden daha yoğunsa: Kırmızı
  {
    lcd.setCursor(1, 0); //İmleci 1. sütuna al
    lcd.print("Algilanan Renk");
    lcd.setCursor(2, 1); //İmleci 2. satır 2. sütuna al
    Serial.print("Renk = Kırmızı   ");
    lcd.print("Kirmizi"); // Ekrana Kirmizi yazdırır.
    digitalWrite(buzzer,HIGH); //Buzzerı aç.
    digitalWrite(g,HIGH); // Yeşil Ledi aç.
    delay(100);         // 0.1 saniye delay koy.
    digitalWrite(g,LOW); // Yeşil Ledi kapa.
    digitalWrite(buzzer,LOW); // Buzzerı Kapa.
  } else {
    
    lcd.setCursor(1,0); //İmleci 1. sütuna al
    lcd.print("ERROR !");
    lcd.setCursor(2, 1); //İmleci 2. satır 2. sütuna al
    Serial.print("Renk algılanamadı   "); //Belirlediğimiz kıstaslara uymayan diğer renkler
    lcd.print("Tekrar deneyin"); // Ekrana Tekrar deneyin yazdırır.
    
  
    
    digitalWrite(buzzer,HIGH);  //Buzzerı aç.
    digitalWrite(r,HIGH); //Kırmızı Ledi aç.
    delay(2000); // 2 saniye delay koy.
    digitalWrite(r,LOW); // Kırmızı Ledi kapa.
    digitalWrite(buzzer,LOW); // Buzzerı Kapa.
    delay(1000); // 1 saniye delay koy.
    digitalWrite(buzzer,HIGH);  //Buzzerı aç.
    digitalWrite(r,HIGH); //Kırmızı Ledi aç.
    delay(2000); // 2 saniye delay koy.
    digitalWrite(r,LOW); // Kırmızı Ledi kapa.
    digitalWrite(buzzer,LOW); // Buzzerı Kapa.
    
  }

  Serial.println(); //Serial monitörde bir satır aşağı geç
  delay(1000); //1000 milisaniye bekle
  lcd.clear(); //LCD ekranı temizle
  delay(150);

}
