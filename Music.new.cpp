#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <limits>
#include <cstdlib> 
using namespace std;

struct musik {
    string namaLagu;
    string genre;
    string artis;
    int durasi; 
};

musik daftar[30];

void clearScreen() {
    system("cls");
}

int inputAngkaValid(int minVal, int maxVal) {
    int val;
    while (true) {
        cin >> val;
        if (cin.fail()) {
            cin.clear(); // benerin fungsi input yang macet
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // buang ketikan yang salah tadi
            cout << " Input tidak valid. Harap masukkan angka: ";
        } else if (val < minVal || val > maxVal) {
            // Kalau angkanya ngawur (misal menu cuma 1-6 tapi diinput 9)
            cout << " Nilai harus antara " << minVal << " dan " << maxVal << ". Coba lagi: ";
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // bersihin sisa enter
            return val; // balikin angka yang udah bener
        }
    }
}

// Fungsi nampilin daftar menu pilihan
void menuUtama() {
    clearScreen(); // Sesuai request, layar dibersihin pas menu utama muncul biar ga numpuk teks lama
    cout << "\n";
    cout << string(40,'=') << endl;
    cout << "        SISTEM MANAJEMEN MUSIK\n";
    cout << string(40,'=') << endl;
    cout << "1. INPUT DATA LAGU\n";
    cout << "2. TAMPIL DATA LAGU\n";
    cout << "3. SEARCHING LAGU\n";
    cout << "4. SORTING LAGU\n";
    cout << "5. HAPUS DATA LAGU\n";
    cout << "6. EXIT\n";
    cout << string(40,'=') << endl;
    cout << "Total lagu : ";
}

// Fungsi buat nampilin semua lagu yang tersimpan dalam bentuk tabel
void tampilkanData(musik daftar[], int jumlahdata) {
    if(jumlahdata > 0){
        cout << "\n";
        cout << string(80,'=') << endl;
        cout << "No  | Nama Lagu                  | Genre        | Artis             | Durasi\n";
        cout << string(80,'=') << endl;
        for(int i = 0; i < jumlahdata; i++){
            // Balikin total detik ke format menit dan detik buat ditampilkan
            int menit = daftar[i].durasi / 60;
            int detik = daftar[i].durasi % 60;
            
            // left dan setw() ini bawaan iomanip biar jarak spasi tabelnya lurus otomatis
            cout << left << setw(3) << i+1 << " | ";
            cout << left << setw(26) << daftar[i].namaLagu.substr(0, 26) << " | ";
            cout << left << setw(12) << daftar[i].genre.substr(0, 12) << " | ";
            cout << left << setw(17) << daftar[i].artis.substr(0, 17) << " | ";
            // Kalau detiknya di bawah 10 (misal 5), ditambahin angka 0 di depannya jadi 05
            cout << menit << ":" << (detik < 10 ? "0" : "") << detik << endl;
        }
        cout << string(80,'=') << endl;
    }else{
        cout << "\n.....No Data music.txt!\n";
    }
}

// Algoritma Pencarian Berurutan (Sequential Search / Linear Search)
void sequentialSearch(musik daftar[], int jumlahdata, int pilihan) {
    if(jumlahdata == 0) {
        cout << "\nDATA MASIH KOSONG!\n";
        return;
    }
    string cari;
    bool ketemu = false;
    
    // Pilihan 1: Nyari pake nama lagu
    if(pilihan == 1) {
        cout << "\nCari berdasarkan NAMA LAGU\n";
        cout << "Masukkan nama lagu : ";
        getline(cin, cari);
        cout << "\nHASIL PENCARIAN:\n";
        for (int i = 0; i < jumlahdata; i++) {
            if (daftar[i].namaLagu == cari) {
                int menit = daftar[i].durasi / 60;
                int detik = daftar[i].durasi % 60;
                cout << "\nData ditemukan!\n";
                cout << "Nama Lagu : " << daftar[i].namaLagu << endl;
                cout << "Genre     : " << daftar[i].genre << endl;
                cout << "Artis     : " << daftar[i].artis << endl;
                cout << "Durasi    : " << menit << ":" << (detik < 10 ? "0" : "") << detik << endl;
                ketemu = true;
                break; // Langsung stop perulangan karena nama lagu kan unik biasanya cuma satu
            }
        }
    }
    // Pilihan 2: Nyari pake genre lagu (bisa nampilin banyak data sekaligus)
    else if(pilihan == 2) {
        cout << "\nCari berdasarkan GENRE LAGU\n";
        cout << "Masukkan genre : ";
        getline(cin, cari);
        cout << "\nHASIL PENCARIAN (Genre: " << cari << "):\n";
        for (int i = 0; i < jumlahdata; i++) {
            if (daftar[i].genre == cari) {
                int menit = daftar[i].durasi / 60;
                int detik = daftar[i].durasi % 60;
                cout << "\nNama Lagu : " << daftar[i].namaLagu << endl;
                cout << "Artis     : " << daftar[i].artis << endl;
                cout << "Durasi    : " << menit << ":" << (detik < 10 ? "0" : "") << detik << endl;
                ketemu = true; // Jangan di-break biar data genre lain yang sama ikut muncul
            }
        }
    }
    // Pilihan 3: Nyari pake nama artis
    else if(pilihan == 3) {
        cout << "\nCari berdasarkan ARTIS\n";
        cout << "Masukkan nama artis : ";
        getline(cin, cari);
        cout << "\nHASIL PENCARIAN (Artis: " << cari << "):\n";
        for (int i = 0; i < jumlahdata; i++) {
            if (daftar[i].artis == cari) {
                int menit = daftar[i].durasi / 60;
                int detik = daftar[i].durasi % 60;
                cout << "\nNama Lagu : " << daftar[i].namaLagu << endl;
                cout << "Genre     : " << daftar[i].genre << endl;
                cout << "Durasi    : " << menit << ":" << (detik < 10 ? "0" : "") << detik << endl;
                ketemu = true;
            }
        }
    }
    if (!ketemu) {
        cout << "\nTidak ada ini didalam data\n";
    }
}

// Fungsi pembagi kelompok data (Partisi) buat Quick Sort
int partitionDurasi(int low, int high, musik daftar[]) {
    int pivot = daftar[high].durasi; // Kita ambil patokan (pivot) dari elemen paling belakang
    int i = low - 1; // Penanda batas untuk elemen yang lebih kecil dari pivot
    
    for (int j = low; j < high; j++) {
        // Kalau durasi data lebih pendek/sama dengan pivot, geser ke bagian kiri
        if (daftar[j].durasi <= pivot) {
            i++;
            swap(daftar[i], daftar[j]); // Tukar posisinya
        }
    }
    swap(daftar[i + 1], daftar[high]); // Taruh pivot di tengah-tengah kelompok data
    return i + 1; // Balikin posisi indeks pivot yang baru
}

// Algoritma Pengurutan Cepat Rekursif (Quick Sort)
void quickSortDurasi(int low, int high, musik daftar[]) {
    if (low < high) {
        // Pi itu posisi pivot yang udah bener letaknya setelah dibagi
        int pi = partitionDurasi(low, high, daftar);
        
        // Panggil fungsi ini lagi secara rekursif buat ngurutin data sebelah kiri dan kanan pivot
        quickSortDurasi(low, pi - 1, daftar); // urutkan kelompok kiri
        quickSortDurasi(pi + 1, high, daftar); // urutkan kelompok kanan
    }
}

// Fungsi buat hapus data lagu pilihan user
void hapusData(musik daftar[], int &jumlahdata) {
    if(jumlahdata == 0) {
        cout << "\nTIDAK ADA DATA YANG BISA DIHAPUS\n";
        return;
    }
    tampilkanData(daftar, jumlahdata); // tampilin dulu listnya biar user ga tebak-tebakan nomor
    cout << "\nMasukkan nomor lagu yang akan dihapus (1-" << jumlahdata << ") : ";
    int nomor = inputAngkaValid(1, jumlahdata);
    
    if(nomor >= 1 && nomor <= jumlahdata) {
        // Logika hapusnya: timpa data lama dengan cara menggeser data di depannya maju ke belakang
        for(int i = nomor - 1; i < jumlahdata - 1; i++) {
            daftar[i] = daftar[i + 1];
        }
        jumlahdata--; // total jumlah data dikurang 1 karena ada yang kehapus
        cout << "\nLagu nomor " << nomor << " berhasil dihapus!\n";
        cout << "Sisa lagu : " << jumlahdata << " lagu\n";
    } else {
        cout << "\nNomor tidak valid!\n";
    }
}

// Fungsi mindahin isi array komputer ke file penyimpanan eksternal (TXT)
void SimpanData(musik daftar[], int jumlahData) {
    ofstream file("music.txt"); // buka/bikin file baru namanya music.txt
    if(file.is_open()) {
        file << jumlahData << "\n"; // baris pertama diisi total jumlah data
        for(int i = 0; i < jumlahData; i++) {
            file << daftar[i].namaLagu << "\n";
            file << daftar[i].genre << "\n";
            file << daftar[i].artis << "\n";
            file << daftar[i].durasi << "\n";
        }
        file.close(); // wajib ditutup biar filenya ga korup
        cout << "\nData berhasil disimpan ke music.txt (" << jumlahData << " lagu)\n";
    } else {
        cout << "\nGagal menyimpan data!\n";
    }
}

// Fungsi buat ngambil data dari file TXT dimasukkan lagi ke program pas pertama dibuka
void BacaData(musik daftar[], int &jumlahData) {
    ifstream file("music.txt");
    if(file.is_open()) {
        file >> jumlahData; // baca angka jumlah data di baris pertama
        if (file.fail() || jumlahData < 0 || jumlahData > 30) {
            jumlahData = 0;
            cout << "\nFile music.txt rusak/kosong. Data direset.\n";
        } else {
            file.ignore(numeric_limits<streamsize>::max(), '\n'); // skip baris enter awal
            for(int i = 0; i < jumlahData; i++) {
                getline(file, daftar[i].namaLagu);
                getline(file, daftar[i].genre);
                getline(file, daftar[i].artis);
                file >> daftar[i].durasi;
                file.ignore(numeric_limits<streamsize>::max(), '\n'); // skip enter setelah angka durasi
            }
            cout << "\nData berhasil dimuat dari music.txt (" << jumlahData << " lagu)\n";
        }
        file.close();
    } else {
        cout << "\nBelum ada isi\n"; // Kondisi kalau file music.txt emang belum pernah dibikin
        jumlahData = 0;
    }
}

// Alur kontrol utama jalannya program aplikasi
int main() {
    int jumlahdata = 0;
    int pilihan;
    bool running = true;
    
    cout << "\n";
    cout << "========================================\n";
    cout << "  JUMLAH MUSIC YANG DISIMPAN\n";
    cout << "========================================\n";
    BacaData(daftar, jumlahdata); // Pas aplikasi dibuka, otomatis langsung loading data lama dari TXT

    do {
        menuUtama(); // Panggil tampilan menu utama
        cout << jumlahdata << " lagu" << endl;
        cout << "Pilihan Anda : ";
        pilihan = inputAngkaValid(1, 6); // Ambil input pilihan menu yang valid (1 sampai 6)

        switch(pilihan) {
        case 1: {
            cout << "\n================== INPUT DATA LAGU ==================\n";
            cout << "Jumlah lagu yang akan diinput (max 30) : ";
            int newData = inputAngkaValid(1, 30);

            if(jumlahdata + newData > 30) {
                cout << "\nMelebihi batas maksimal (30 lagu)!\n";
                cout << "Sisa kapasitas: " << 30 - jumlahdata << " lagu\n";
            } else if(newData < 1) {
                cout << "\nJumlah data minimal 1!\n";
            } else {
                for(int i = 0; i < newData; i++) {
                    cout << "\nLagu ke-" << jumlahdata + i + 1 << "\n";
                    cout << "Nama Lagu : ";
                    getline(cin, daftar[jumlahdata + i].namaLagu);
                    cout << "Genre      : ";
                    getline(cin, daftar[jumlahdata + i].genre);
                    cout << "Artis      : ";
                    getline(cin, daftar[jumlahdata + i].artis);

                    int menit, detik;
                    cout << "Durasi (format: menit(space bar)detik) : ";
                    while(true) {
                        cin >> menit >> detik;
                        if(cin.fail() || detik < 0 || detik > 59) {
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            cout << "Format salah! Detik harus 0-59. Coba lagi: ";
                        } else { break; }
                    }
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    // Konversi menit ke detik lalu ditambah sisa detiknya biar datanya jadi satu angka bulat tunggal
                    daftar[jumlahdata + i].durasi = (menit * 60) + detik;
                }
                jumlahdata += newData;
                cout << "\nBerhasil menambahkan " << newData << " lagu!\n";
                SimpanData(daftar, jumlahdata); // Tiap abis input data baru, otomatis langsung backup ke TXT
            }
            break;
        }
        case 2: {
            cout << "\n================== DAFTAR LAGU ==================\n";
            tampilkanData(daftar, jumlahdata);
            break;
        }
        case 3: {
            if(jumlahdata == 0) {
                cout << "\nISI DULU DATANYA\n";
                break;
            }
            int pilihSearch;
            cout << "\n================== MENU SEARCHING ==================\n";
            cout << "1. Cari berdasarkan NAMA LAGU\n";
            cout << "2. Cari berdasarkan GENRE LAGU\n";
            cout << "3. Cari berdasarkan ARTIS\n";
            cout << "Pilihan : ";
            pilihSearch = inputAngkaValid(1, 3);

            if(pilihSearch >= 1 && pilihSearch <= 3) {
                sequentialSearch(daftar, jumlahdata, pilihSearch);
            } else {
                cout << "\nPilihan tidak valid\n";
            }
            break;
        }
        case 4: {
            if(jumlahdata == 0) {
                cout << "\nASTAGFIRULLAH, data belum ada\n";
                break;
            }
            cout << "\n================== SORTING LAGU ==================\n";
            cout << "Mengurutkan lagu berdasarkan DURASI (Dari terpendek ke terpanjang)\n";
            quickSortDurasi(0, jumlahdata - 1, daftar); // Lempar indeks awal (0) dan indeks akhir array (jumlahdata-1)
            cout << "\nSORTING SELESAI!\n";
            cout << "\nHasil sorting berdasarkan durasi:\n";
            tampilkanData(daftar, jumlahdata);
            break;
        }
        case 5: {
            cout << "\n================== HAPUS DATA LAGU ==================\n";
            hapusData(daftar, jumlahdata);
            if(jumlahdata > 0) {
                SimpanData(daftar, jumlahdata); // Otomatis simpan perubahan setelah data dihapus
            }
            break;
        }
        case 6: {
            cout << "\n================== KELUAR ==================\n";
            SimpanData(daftar, jumlahdata); // Pastikan data tersimpan aman sebelum aplikasi ditutup total
            cout << "Terima kasih telah menggunakan program ini!\n";
            running = false; // Ubah ke false biar perulangan do-while berhenti
            break;
        }
        default:
            cout << "\nPilihan tidak valid! Silahkan pilih 1-6.\n";
            break;
        }
        
        // Jeda penahan biar user bisa baca teks hasil menu dulu sebelum layarnya dibersihin lagi sama menuUtama()
        if(running && pilihan != 6) {
            cout << "\nTekan Enter untuk kembali ke menu utama...";
            cin.get();
        }
    } while(running == true);
    
    return 0;
}
