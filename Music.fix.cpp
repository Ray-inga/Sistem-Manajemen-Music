#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <limits> // Diperlukan untuk error handling cin
using namespace std;

struct musik {
    string namaLagu;
    string genre;
    string artis;
    int durasi;
};

musik daftar[30];

//  Helper: Error handling input angka (mencegah crash & infinite loop)
int inputAngkaValid(int minVal, int maxVal) {
    int val;
    while (true) {
        cin >> val;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << " Input tidak valid. Harap masukkan angka: ";
        } else if (val < minVal || val > maxVal) {
            cout << " Nilai harus antara " << minVal << " dan " << maxVal << ". Coba lagi: ";
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return val;
        }
    }
}

void menuUtama() {
    cout << "\n";
    cout << string(40,'=') << endl;
    cout << "       SISTEM MANAJEMEN MUSIK\n";
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

void tampilkanData(musik daftar[], int jumlahdata) {
    if(jumlahdata > 0){
        cout << "\n";
        cout << string(80,'=') << endl;
        cout << "No  | Nama Lagu                  | Genre        | Artis             | Durasi\n";
        cout << string(80,'=') << endl;
        for(int i = 0; i < jumlahdata; i++){
            int menit = daftar[i].durasi / 60;
            int detik = daftar[i].durasi % 60;
            cout << left << setw(3) << i+1 << " | ";
            cout << left << setw(26) << daftar[i].namaLagu.substr(0, 26) << " | ";
            cout << left << setw(12) << daftar[i].genre.substr(0, 12) << " | ";
            cout << left << setw(17) << daftar[i].artis.substr(0, 17) << " | ";
            cout << menit << ":" << (detik < 10 ? "0" : "") << detik << endl;
        }
        cout << string(80,'=') << endl;
    }else{
        cout << "\n.....No Data music.txt!\n";
    }
}

void sequentialSearch(musik daftar[], int jumlahdata, int pilihan) {
    if(jumlahdata == 0) {
        cout << "\nDATA MASIH KOSONG!\n";
        return;
    }
    string cari;
    bool ketemu = false;
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
                break;
            }
        }
    }
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
                ketemu = true;
            }
        }
    }
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

int partitionDurasi(int low, int high, musik daftar[]) {
    int pivot = daftar[high].durasi;
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (daftar[j].durasi <= pivot) {
            i++;
            swap(daftar[i], daftar[j]);
        }
    }
    swap(daftar[i + 1], daftar[high]);
    return i + 1;
}

void quickSortDurasi(int low, int high, musik daftar[]) {
    if (low < high) {
        int pi = partitionDurasi(low, high, daftar);
        quickSortDurasi(low, pi - 1, daftar);
        quickSortDurasi(pi + 1, high, daftar);
    }
}

void hapusData(musik daftar[], int &jumlahdata) {
    if(jumlahdata == 0) {
        cout << "\nTIDAK ADA DATA YANG BISA DIHAPUS\n";
        return;
    }
    tampilkanData(daftar, jumlahdata);
    cout << "\nMasukkan nomor lagu yang akan dihapus (1-" << jumlahdata << ") : ";
    int nomor = inputAngkaValid(1, jumlahdata); //  VALIDASI
    if(nomor >= 1 && nomor <= jumlahdata) {
        for(int i = nomor - 1; i < jumlahdata - 1; i++) {
            daftar[i] = daftar[i + 1];
        }
        jumlahdata--;
        cout << "\nLagu nomor " << nomor << " berhasil dihapus!\n";
        cout << "Sisa lagu : " << jumlahdata << " lagu\n";
    } else {
        cout << "\nNomor tidak valid!\n";
    }
}

void SimpanData(musik daftar[], int jumlahData) {
    ofstream file("music.txt");
    if(file.is_open()) {
        file << jumlahData << "\n";
        for(int i = 0; i < jumlahData; i++) {
            file << daftar[i].namaLagu << "\n";
            file << daftar[i].genre << "\n";
            file << daftar[i].artis << "\n";
            file << daftar[i].durasi << "\n";
        }
        file.close();
        cout << "\nData berhasil disimpan ke music.txt (" << jumlahData << " lagu)\n";
    } else {
        cout << "\nGagal menyimpan data!\n";
    }
}

void BacaData(musik daftar[], int &jumlahData) {
    ifstream file("music.txt");
    if(file.is_open()) {
        file >> jumlahData;
        //  VALIDASI: Cek jika file korup atau jumlah melebihi array
        if (cin.fail() || jumlahData < 0 || jumlahData > 30) {
            jumlahData = 0;
            cout << "\nFile music.txt rusak/kosong. Data direset.\n";
        } else {
            file.ignore(numeric_limits<streamsize>::max(), '\n');
            for(int i = 0; i < jumlahData; i++) {
                getline(file, daftar[i].namaLagu);
                getline(file, daftar[i].genre);
                getline(file, daftar[i].artis);
                file >> daftar[i].durasi;
                file.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            cout << "\nData berhasil dimuat dari music.txt (" << jumlahData << " lagu)\n";
        }
        file.close();
    } else {
        cout << "\nBelum ada isi\n";
        jumlahData = 0;
    }
}

int main() {
    int jumlahdata = 0;
    int pilihan;
    bool running = true;
    cout << "\n";
    cout << "========================================\n";
    cout << "  JUMLAH MUSIC YANG DISIMPAN\n";
    cout << "========================================\n";
    BacaData(daftar, jumlahdata);

    do {
        menuUtama();
        cout << jumlahdata << " lagu" << endl;
        cout << "Pilihan Anda : ";
        pilihan = inputAngkaValid(1, 6); //  VALIDASI MENU

        switch(pilihan) {
        case 1: {
            cout << "\n================== INPUT DATA LAGU ==================\n";
            cout << "Jumlah lagu yang akan diinput (max 30) : ";
            int newData = inputAngkaValid(1, 30); //  VALIDASI JUMLAH INPUT

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
                    while(true) { //  VALIDASI DURASI
                        cin >> menit >> detik;
                        if(cin.fail() || detik < 0 || detik > 59) {
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            cout << "Format salah! Detik harus 0-59. Coba lagi: ";
                        } else { break; }
                    }
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    daftar[jumlahdata + i].durasi = (menit * 60) + detik;
                }
                jumlahdata += newData;
                cout << "\nBerhasil menambahkan " << newData << " lagu!\n";
                SimpanData(daftar, jumlahdata);
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
            pilihSearch = inputAngkaValid(1, 3); //  VALIDASI SEARCH

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
            quickSortDurasi(0, jumlahdata - 1, daftar);
            cout << "\nSORTING SELESAI!\n";
            cout << "\nHasil sorting berdasarkan durasi:\n";
            tampilkanData(daftar, jumlahdata);
            break;
        }
        case 5: {
            cout << "\n================== HAPUS DATA LAGU ==================\n";
            hapusData(daftar, jumlahdata);
            if(jumlahdata > 0) {
                SimpanData(daftar, jumlahdata);
            }
            break;
        }
        case 6: {
            cout << "\n================== KELUAR ==================\n";
            SimpanData(daftar, jumlahdata);
            cout << "Terima kasih telah menggunakan program ini!\n";
            running = false;
            break;
        }
        default:
            cout << "\nPilihan tidak valid! Silahkan pilih 1-6.\n";
            break;
        }
        if(running && pilihan != 6) {
            cout << "\nTekan Enter untuk kembali ke menu utama...";
            cin.get();
        }
    } while(running == true);
    return 0;
}
