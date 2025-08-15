#include <iostream>
#include <limits> // std::numeric_limits için
#include <cmath> // pow() fonksiyonu icin

// Gelecekte eklenecek hesaplama fonksiyonlarýnýn prototipleri
void bilesikFaizHesapla();
void krediOdemePlaniHesapla();
void enflasyonHesapla();

void clearScreen() {
    // Platforma göre ekraný temizleme
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

int main() {
    int secim = 0; // Hata veren kýsým düzeltildi

    do {
        clearScreen();
        std::cout << "------------------------------------------\n";
        std::cout << "|         Finans Hesaplayici             |\n";
        std::cout << "------------------------------------------\n";
        std::cout << "| 1. Bilesik Faiz Hesaplama              |\n";
        std::cout << "| 2. Kredi Odeme Plani Hesaplama         |\n";
        std::cout << "| 3. Enflasyonun Etkisini Hesaplama      |\n";
        std::cout << "| 4. Cikis                               |\n";
        std::cout << "------------------------------------------\n";
        std::cout << "Lutfen bir secim yapin: ";

        std::cin >> secim;

        // Geçersiz girdiyi (harf gibi) temizle
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            secim = 0; // Hatalý girdi için 0 atayalým, menü tekrar dönsün
        }

        // Bu satýr, girdi alýndýktan sonra kalan yeni satýr karakterini temizler.
        // Bu, alt modüllere geçildiðinde programýn donmasýný engeller.
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');


        switch (secim) {
        case 1:
            bilesikFaizHesapla();
            break;
        case 2:
            krediOdemePlaniHesapla();
            break;
        case 3:
            enflasyonHesapla();
            break;
        case 4:
            std::cout << "Programdan cikiliyor...\n";
            break;
        default:
            std::cout << "Gecersiz secim. Lutfen tekrar deneyin.\n";
            std::cout << "Devam etmek icin bir tusa basin...\n";
            std::cin.get();
            break;
        }

    } while (secim != 4);

    return 0;
}

// BilesikFaizHesapla fonksiyonu, girdi alma ve hesaplama kýsmý eklendi
void bilesikFaizHesapla() {
    clearScreen();
    std::cout << "------------------------------------------\n";
    std::cout << "|      Bilesik Faiz Hesaplama            |\n";
    std::cout << "------------------------------------------\n";

    double anaPara;
    double faizOrani;
    int vade;
    int bilesiklenmeSikligi;

    std::cout << "Ana parayi giriniz (TL): ";
    std::cin >> anaPara;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Girdi sonrasý temizlik

    std::cout << "Yillik faiz oranini giriniz (orn: %5 icin 5): ";
    std::cin >> faizOrani;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Girdi sonrasý temizlik

    std::cout << "Vadeyi yillik olarak giriniz: ";
    std::cin >> vade;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Girdi sonrasý temizlik

    std::cout << "Faizlerin yilda kac kez bilesiklendigini giriniz (aylik icin 12, yillik icin 1): ";
    std::cin >> bilesiklenmeSikligi;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Girdi sonrasý temizlik

    // Faiz oranini ondalikli degere cevir
    faizOrani /= 100.0;

    double gelecektekiDeger;
    double toplamFaiz;

    gelecektekiDeger = anaPara * pow((1 + faizOrani / bilesiklenmeSikligi), vade * bilesiklenmeSikligi);
    toplamFaiz = gelecektekiDeger - anaPara;

    std::cout << "\n------------------------------------------\n";
    std::cout.precision(2); // Ondalik kisim 2 basamakli olsun
    std::cout << std::fixed; // Normal ondalik gosterimi icin

    std::cout << "Ana Para: " << anaPara << " TL" << std::endl;
    std::cout << "Toplam Geri Odeme: " << gelecektekiDeger << " TL" << std::endl;
    std::cout << "Toplam Faiz Getirisi: " << toplamFaiz << " TL" << std::endl;
    std::cout << "------------------------------------------\n";

    std::cout << "\nAna menuye donmek icin bir tusa basin...\n";
    std::cin.get();
}

// Boþ fonksiyon gövdeleri
void krediOdemePlaniHesapla() {
    clearScreen();
    std::cout << "------------------------------------------\n";
    std::cout << "|    Kredi Odeme Plani Hesaplama         |\n";
    std::cout << "------------------------------------------\n";

    double anaPara;
    double faizOrani;
    int vadeYil;

    std::cout << "Kredi ana parasini giriniz (TL): ";
    std::cin >> anaPara;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Yillik faiz oranini giriniz (orn: %5 icin 5): ";
    std::cin >> faizOrani;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Vadeyi yillik olarak giriniz: ";
    std::cin >> vadeYil;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // Girdileri aylýk deðerlere dönüþtür
    double aylikFaizOrani = (faizOrani / 100.0) / 12.0;
    int toplamTaksitSayisi = vadeYil * 12;

    double aylikTaksit;
    double toplamOdeme;
    double toplamFaiz;

    // Formülü uygula
    // Payda sýfýr olabileceði için kontrol eklemek iyi bir pratik
    if (aylikFaizOrani > 0) {
        aylikTaksit = anaPara * (aylikFaizOrani * pow(1 + aylikFaizOrani, toplamTaksitSayisi)) / (pow(1 + aylikFaizOrani, toplamTaksitSayisi) - 1);
    }
    else {
        // Faiz oraný sýfýrsa aylýk taksit ana para/toplam taksit sayýsýdýr
        aylikTaksit = anaPara / toplamTaksitSayisi;
    }

    toplamOdeme = aylikTaksit * toplamTaksitSayisi;
    toplamFaiz = toplamOdeme - anaPara;

    // Sonuçlarý ekrana yazdýrma
    std::cout << "\n------------------------------------------\n";
    std::cout.precision(2);
    std::cout << std::fixed;

    std::cout << "Kredi Tutari: " << anaPara << " TL" << std::endl;
    std::cout << "Aylik Taksit: " << aylikTaksit << " TL" << std::endl;
    std::cout << "Toplam Odeme: " << toplamOdeme << " TL" << std::endl;
    std::cout << "Toplam Faiz Maliyeti: " << toplamFaiz << " TL" << std::endl;
    std::cout << "------------------------------------------\n";

    std::cout << "\nAna menuye donmek icin bir tusa basin...\n";
    std::cin.get();

}

void enflasyonHesapla() {
    clearScreen();
    std::cout << "------------------------------------------\n";
    std::cout << "|    Enflasyonun Etkisini Hesaplama      |\n";
    std::cout << "------------------------------------------\n";

    double bugunkuDeger;
    double enflasyonOrani;
    int vadeYil;

    std::cout << "Bugunku para miktarini giriniz (TL): ";
    std::cin >> bugunkuDeger;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Yillik ortalama enflasyon oranini giriniz (orn: %10 icin 10): ";
    std::cin >> enflasyonOrani;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Gelecek icin vadeyi yillik olarak giriniz: ";
    std::cin >> vadeYil;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // Faiz oranýný ondalýklý deðere çevir
    enflasyonOrani /= 100.0;

    double gelecektekiSatinalmaGucu;

    // Formülü uygula
    gelecektekiSatinalmaGucu = bugunkuDeger / pow(1 + enflasyonOrani, vadeYil);

    std::cout << "\n------------------------------------------\n";
    std::cout.precision(2);
    std::cout << std::fixed;

    std::cout << "Bugunku " << bugunkuDeger << " TL'nin " << vadeYil << " yil sonraki satinalma gucu:\n";
    std::cout << gelecektekiSatinalmaGucu << " TL'dir" << std::endl;
    std::cout << "------------------------------------------\n";

    std::cout << "\nAna menuye donmek icin bir tusa basin...\n";
    std::cin.get();
}