# Noktadan Noktaya Kablosuz Telemetri ve FSM Tabanlı Aktüatör Kontrol Sistemi

Bu proje; bir Verici Yer İstasyonu (Arduino Uno + HC-05) ile bir Alıcı/İşleyici Düğüm (ESP32-WROOM-32U) arasında RF (Radyo Frekansı) tabanlı kablosuz iletişim kurarak mekanik sistemleri asenkron olarak kontrol eden uçtan uca bir gömülü sistem prototipidir.

## Öne Çıkan Mühendislik Özellikleri
* **Sonlu Durum Makinesi (FSM):** Parazitli RF ortamlarında veri kaybını önleyen, işlemciyi kilitlemeyen (non-blocking) `<data>` paket ayrıştırma algoritması.
* **Master/Slave Bluetooth Mimarisi:** ESP32 (Master) ve HC-05 (Slave) arasında MAC adresine güdümlü otomatik bağlantı.
* **Aktüatör Karakterizasyonu:** Sürekli dönen (360° Continuous) servo motorun PWM sinyalleriyle yön ve hassas hız kontrolü.
* **Donanımsal Eşik Koruması:** Telemetri verisi kritik sınıra (>900) ulaştığında otomatik devre kesici/alarm görevini üstlenen JQC3F Röle entegrasyonu.

## Donanım Bağlantı Şeması (Alıcı Düğüm - ESP32)
| Bileşen | Pin/Bağlantı Noktası | ESP32 GPIO | Görev |
| :--- | :--- | :--- | :--- |
| **Servo Motor** | Sinyal (Sarı) | `GPIO 13` | PWM Hız ve Yön Kontrolü |
| **Röle Modülü** | Sinyal (IN) | `GPIO 12` | Dijital Eşik Tetikleme |
| **Sistem Gücü** | VCC / DC+ | `VIN (5V)` | Aktüatör Beslemesi |
| **Sistem Gücü** | GND / DC- | `GND` | Ortak Toprak Hattı |

## Karşılaşılan Problemler ve Çözümler
1. **USB Enumeration:** CP2102 sürücüleri kurularak donanım sisteme tanıtıldı.
2. **Port Çakışması:** COM9 çakışması, Bluetooth eşleşmesi kesilerek giderildi.
3. **Kütüphane İmza Değişimi:** `SerialBT.setPin("1234", 4);` revizyonu ile güncel SDK uyumluluğu sağlandı.

## Teknik Makale
Projenin detaylı donanım blok diyagramı ve akademik analizleri için yüklenen PDF raporunu inceleyebilirsiniz.

---
*Proje Geliştiricisi: Halil Özbağcı*
