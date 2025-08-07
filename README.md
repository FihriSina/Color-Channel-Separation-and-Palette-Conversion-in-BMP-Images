# Color-Channel-Separation-and-Palette-Conversion-in-BMP-Images

## 📌 Project Description

- **Input:** A 24-bit BMP image (e.g., `input.bmp`)
- **Output:**
  - `red8.bmp` → Red channel image with red-tone palette
  - `green8.bmp` → Green channel image with green-tone palette
  - `blue8.bmp` → Blue channel image with blue-tone palette

The output images are 8-bit paletted BMPs and can be opened with any standard image viewer.

---

## 🛠️ How It Works

1. The program reads a 24-bit BMP file using the provided `ImageRead()` function.
2. RGB channels are extracted pixel by pixel.
3. Each channel is saved into a separate 8-bit BMP image using `ImageWrite()` with a custom palette:
   - **Red palette:** shades from (0,0,0) to (255,0,0)
   - **Green palette:** shades from (0,0,0) to (0,255,0)
   - **Blue palette:** shades from (0,0,0) to (0,0,255)
4. The BMP headers and image data are managed manually (no external libraries used).

---

## 📁 File Structure

with output
```bash
.
├── dip.cpp          # Main source code (BMP reader/writer and channel separation)
├── input.bmp        # 24-bit input image (must be provided by the user)
├── red8.bmp         # Output: red channel (8-bit)
├── green8.bmp       # Output: green channel (8-bit)
├── blue8.bmp        # Output: blue channel (8-bit)
└── README.md        # This file


# BMP Görüntülerde Renk Kanalı Ayırma ve Palet Dönüştürme

## 📌 Proje Açıklaması

- **Girdi:** 24-bit BMP formatında bir görüntü (örneğin: `input.bmp`)
- **Çıktılar:**
  - `red8.bmp` → Sadece kırmızı kanal bilgisi, kırmızı tonlu palet ile
  - `green8.bmp` → Sadece yeşil kanal bilgisi, yeşil tonlu palet ile
  - `blue8.bmp` → Sadece mavi kanal bilgisi, mavi tonlu palet ile

Çıktı dosyaları 8-bit BMP formatındadır ve BMP görüntüleyici programlarla açılabilir.

---

## 🛠️ Nasıl Çalışır?

1. `input.bmp` adlı 24-bit BMP dosyası, `ImageRead()` fonksiyonu ile okunur.
2. Her pikselin RGB bilgisi ayrı ayrı alınır.
3. Renk kanalları için ayrı 8-bit BMP dosyaları hazırlanır.
4. Her dosyaya özel palet tanımlanır:
   - **Kırmızı paleti:** (0,0,0) → (255,0,0)
   - **Yeşil paleti:** (0,0,0) → (0,255,0)
   - **Mavi paleti:** (0,0,0) → (0,0,255)
5. BMP başlıkları ve veriler manuel olarak işlenir (kütüphane kullanılmaz).
6. Dosyalar `ImageWrite()` fonksiyonu ile kaydedilir.

---

## 📁 Klasör Yapısı

Çıktısı ile beraber
.
├── dip.cpp          # Ana kaynak kod (BMP okuma/yazma ve kanal ayırma)
├── input.bmp        # Girdi dosyası (24-bit BMP)
├── red8.bmp         # Kırmızı kanal (8-bit çıktı)
├── green8.bmp       # Yeşil kanal (8-bit çıktı)
├── blue8.bmp        # Mavi kanal (8-bit çıktı)
└── README.md        # Bu dosya
