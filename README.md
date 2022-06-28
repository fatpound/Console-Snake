# Snake [WinCMD]

	ÖZELLİKLER
	----------
	
	WASD ile Oynanış
	Duvara Çarpınca Oyun Biter
	Geldiği Yöne Gitme Koruması
	Yemi Yerse Yılanın Boyu Uzar
	ESC'ye Basılırsa Oyun Sonlandırılır
	Yılan Sürekli Hareket Etmez Kullanıcıdan Bir Karakter Beklenir
	Yemin Oluşturulabileceği Yer Kalmazsa (Yılan Tüm Tahtayı Kaplarsa) Oyun Kazanılır
	
	EKLEMELER
	---------
	
	CAPS-Lock Açıkken Oynama Eklendi
	Yön Tuşlarına Basılmazsa Oyun Tahtasını Ekrana Tekrar Çizdirme İptal Edildi
	Oyuncu Tahtayı 15x15'den Büyük Yapmak İsterse Kullanıcı Uyarıldı ve Tahta 50x50'ye Ayarlandı
	Oyunu Kazanmayı Tespit Eden Kod Değiştirildi (int AreaLeft() Yerine "hitapple" içine (Score == Tahta Alanı - 2) Sorgusu Eklendi)
