🎵 Music Management System - Aplikasi Manajemen Data Lagu Berbasis C++
Aplikasi console sederhana untuk mengelola koleksi musik dengan fitur CRUD, pencarian, dan pengurutan data lagu. Dibangun menggunakan bahasa C++ sebagai implementasi struktur data dan algoritma dasar.

✨ Fitur Utama
📥 Input Data - Tambah data lagu baru (maksimal 30 lagu) dengan informasi nama, genre, artis, dan durasi

📋 Tampilkan Data - Menampilkan seluruh daftar lagu dalam format tabel yang rapi

🔍 Pencarian (Sequential Search) - Cari lagu berdasarkan:

Nama Lagu

Genre

Artis

📊 Pengurutan (Quick Sort) - Urutkan lagu berdasarkan durasi dari terpendek ke terpanjang

🗑️ Hapus Data - Hapus lagu yang tidak diinginkan dari daftar

💾 Penyimpanan Eksternal - Data otomatis tersimpan ke file music.txt dan dimuat saat program dijalankan

🛠️ Teknologi & Konsep yang Digunakan
C++ Standard Library (iostream, fstream, iomanip, string)

Sequential Search Algorithm - Pencarian berurutan

Quick Sort Algorithm - Pengurutan rekursif dengan metode partisi

File I/O - Penyimpanan dan pembacaan data dari file teks

Struct - Struktur data untuk merepresentasikan lagu

🚀 Cara Menjalankan
Clone repository ini

Kompilasi menggunakan compiler C++ (GCC, MinGW, atau MSVC):

bash
g++ Music.new.cpp -o music_manager.exe
Jalankan program:

bash
./music_manager.exe
📁 Struktur Data
cpp
struct musik {
    string namaLagu;
    string genre;
    string artis;
    int durasi;  // disimpan dalam satuan detik
};
📄 Format File Penyimpanan (music.txt)
text
[jumlah_data]
[nama_lagu_1]
[genre_1]
[artis_1]
[durasi_detik_1]
[nama_lagu_2]
...
🧠 Algoritma yang Diimplementasikan
Algoritma	Kegunaan
Sequential Search	Mencari lagu berdasarkan nama, genre, atau artis
Quick Sort	Mengurutkan lagu berdasarkan durasi (Divide and Conquer)
🔄 Alur Program
Program membaca data dari music.txt saat startup

Menampilkan menu utama dengan total lagu yang tersimpan

User memilih fitur (input, tampil, cari, urut, hapus, keluar)

Setiap perubahan data otomatis disimpan ke file

Program berakhir dengan menyimpan data terakhir

📌 Catatan
Maksimal penyimpanan: 30 lagu

Validasi input untuk durasi (menit dan detik 0-59)

Pencarian bersifat case-sensitive

Tabel tampilan otomatis terpotong jika teks terlalu panjang

👨‍💻 Author
Dibangun sebagai tugas implementasi algoritma searching dan sorting menggunakan C++.

