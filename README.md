Tabii! Aşağıda hem İngilizce hem Türkçe içerikleri düzgün biçimde hizalanmış, bölümleri ayrı ayrı ama aynı başlık yapısına sadık kalarak düzenlenmiş `README.md` örneğini bulabilirsin. Formatlama hataları giderildi, açıklamalar sadeleştirildi ve klasör yapısı kutu içinde gösterildi. Hazırsan doğrudan GitHub’a koyabilirsin. 👇

---

````markdown
# Color Channel Separation and Palette Conversion in BMP Images  
# BMP Görüntülerde Renk Kanalı Ayırma ve Palet Dönüştürme

---

## 📌 Project Description / Proje Açıklaması

- **Input / Girdi:** A 24-bit BMP image (e.g., `input.bmp`)
- **Output / Çıktılar:**
  - `red8.bmp` → Red channel image with red-tone palette  
    `→` Kırmızı kanal bilgisi, kırmızı tonlu palet ile
  - `green8.bmp` → Green channel image with green-tone palette  
    `→` Yeşil kanal bilgisi, yeşil tonlu palet ile
  - `blue8.bmp` → Blue channel image with blue-tone palette  
    `→` Mavi kanal bilgisi, mavi tonlu palet ile

The output images are 8-bit paletted BMPs and can be opened with any standard image viewer.  
Çıktı dosyaları 8-bit BMP formatındadır ve standart BMP görüntüleyicilerle açılabilir.

---

## 🛠️ How It Works / Nasıl Çalışır

1. The program reads a 24-bit BMP file using the `ImageRead()` function.  
   `→` Program, `ImageRead()` fonksiyonu ile 24-bit BMP dosyasını okur.
2. RGB channels are extracted pixel by pixel.  
   `→` RGB renk kanalları piksel piksel ayrılır.
3. Each channel is saved into a separate 8-bit BMP using `ImageWrite()` with a custom palette:  
   `→` Her kanal, özel bir paletle birlikte ayrı bir 8-bit BMP dosyasına yazılır:
   - Red palette → (0,0,0) → (255,0,0)
   - Green palette → (0,0,0) → (0,255,0)
   - Blue palette → (0,0,0) → (0,0,255)
4. BMP headers and image data are managed manually (no external libraries used).  
   `→` BMP başlıkları ve görüntü verileri elle işlenir (kütüphane kullanılmaz).

---

## 📁 File Structure / Klasör Yapısı

<details>
<summary>With Output / Çıktılar Dahil</summary>

```bash
.
├── dip.cpp          # Main source code / Ana kaynak kod
├── input.bmp        # 24-bit input image / Girdi resmi
├── red8.bmp         # Red channel output / Kırmızı kanal çıktısı
├── green8.bmp       # Green channel output / Yeşil kanal çıktısı
├── blue8.bmp        # Blue channel output / Mavi kanal çıktısı
└── README.md        # This file / Bu dosya
````

</details>

---

## 📜 License / Lisans

This project is intended for educational use only.
Bu proje yalnızca eğitim amaçlıdır.

```
