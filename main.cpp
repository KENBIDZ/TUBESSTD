#include "spotify.h"

const string ADMINPASSWORD = "admin";

bool adminLoginCheck() {
    string pass;
    cout << "Password Admin: ";
    getline(cin, pass);

    if (pass == ADMINPASSWORD) {
        cout << "Login Admin Berhasil\n";
        return true;
    }
    cout << "Password Salah\n";
    return false;
}

void displayMenu(bool isAdmin, bool isPlaying, adrsong currentS) {
    cout << "\n--- Manajer Playlist Spotify ---\n";
    if (isPlaying && currentS != nullptr) {
        cout << ">> NOW PLAYING: " << currentS->title << " - " << currentS->artist << " <<" << endl;
    } else {
        cout << ">> Status: Stopped <<" << endl;
    }
    
    cout << "\n1. Tampilkan Semua Playlist\n";
    cout << "2. Tampilkan Lagu dalam Playlist\n";
    cout << "3. Cari Lagu\n";

    if (isAdmin) {
        cout << "4. Tambah Playlist\n";
        cout << "5. Tambah Lagu ke Playlist\n";
        cout << "6. Update Playlist\n";
        cout << "7. Update Lagu\n";
        cout << "8. Hapus Lagu\n";
        cout << "9. Hapus Playlist\n";
    }

    cout << "\n--- Player ---\n";
    cout << "P. Play dari Playlist\n";
    cout << "S. Stop Lagu\n";
    cout << "N. Next Lagu\n";
    cout << "B. Previous Lagu (Back)\n";

    cout << "\nA. Login Admin\n";
    cout << "0. Keluar\n";
    cout << "Pilih: ";
}

int main() {
    PlaylistList L;
    createPlaylistList(L);

    bool isAdmin = false;
    bool isPlaying = false;

    adrplaylist currentPlaylist = nullptr;
    adrsong currentSong = nullptr;

    User user;
    cout << "Masukkan nama user: ";
    getline(cin, user.username);

    // ===== DATA AWAL (40 LAGU) =====
    // (Data awal yang sudah kamu buat sebelumnya tetap dimasukkan di sini)
    insertPlaylist(L, allocatePlaylist("Midnight Drive"));
    insertSong(L, "Midnight Drive", allocateSong("Saturn", "SZA", 186));
    insertSong(L, "Midnight Drive", allocateSong("After Hours", "Kehlani", 202));
    insertSong(L, "Midnight Drive", allocateSong("Best Part", "Daniel Caesar", 209));
    
    insertPlaylist(L, allocatePlaylist("SZA Essentials"));
    insertSong(L, "SZA Essentials", allocateSong("Kill Bill", "SZA", 153));
    insertSong(L, "SZA Essentials", allocateSong("Snooze", "SZA", 192));

    string input;
    do {
        displayMenu(isAdmin, isPlaying, currentSong);
        getline(cin, input);

        // ===== PLAYER LOGIC (SESUAI GAMBAR) =====
        
        if (input == "P" || input == "p") {
            string pname;
            cout << "Masukkan Nama Playlist untuk diputar: ";
            getline(cin, pname);

            currentPlaylist = findPlaylist(L, pname);
            if (!currentPlaylist || !currentPlaylist->firstsong) {
                cout << "[Error] Playlist tidak ditemukan atau kosong.\n";
            } else {
                currentSong = currentPlaylist->firstsong;
                isPlaying = true;
                playSong(currentSong);
            }
        }
        else if (input == "S" || input == "s") {
            stopSong(currentSong);
            isPlaying = false;
            currentPlaylist = nullptr; // Keluar dari mode playlist saat stop
        }
        else if (input == "N" || input == "n") {
            if (currentSong != nullptr) {
                // Jika currentPlaylist NULL, fungsi nextSong otomatis cari lagu mirip (Artis Sama)
                currentSong = nextSong(L, currentPlaylist, currentSong);
                playSong(currentSong);
                isPlaying = true;
            } else {
                cout << "Gunakan menu Play (P) terlebih dahulu.\n";
            }
        }
        else if (input == "B" || input == "b") {
            if (currentSong != nullptr) {
                // Menggunakan pointer prevsong yang sudah di-update di spotify.cpp
                currentSong = prevSong(L, currentPlaylist, currentSong);
                playSong(currentSong);
                isPlaying = true;
            } else {
                cout << "Gunakan menu Play (P) terlebih dahulu.\n";
            }
        }

        // ===== MENU MANAGEMENT =====
        else if (input == "1") {
            viewPlaylists(L);
        }
        else if (input == "2") {
            string p;
            cout << "Nama Playlist: ";
            getline(cin, p);
            viewSongsInPlaylist(L, p);
        }
        else if (input == "3") {
            string k;
            cout << "Keyword (Judul/Artis): ";
            getline(cin, k);
            searchSong(L, k);
        }
        else if (input == "A" || input == "a") {
            isAdmin = adminLoginCheck();
        }
        // Tambahkan handling untuk case 4-9 jika Admin...

    } while (input != "0");

    cout << "Program selesai. Sampai jumpa, " << user.username << "!\n";
    return 0;
}
