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

void displayMenu(bool isAdmin) {
    cout << "\n--- Manajer Playlist Spotify ---\n";
    cout << "1. Tampilkan Semua Playlist\n";
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
    cout << "P. Play Lagu\n";
    cout << "S. Stop Lagu\n";
    cout << "N. Next Lagu\n";
    cout << "B. Previous Lagu\n";

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

    // ===== DATA AWAL =====
    insertPlaylist(L, allocatePlaylist("SZA - SOS Collection"));
    insertSong(L, "SZA - SOS Collection", allocateSong("Kill Bill", "SZA", 153));
    insertSong(L, "SZA - SOS Collection", allocateSong("Snooze", "SZA", 192));
    insertSong(L, "SZA - SOS Collection", allocateSong("Nobody Gets Me", "SZA", 180));

    insertPlaylist(L, allocatePlaylist("SZA - CTRL"));
    insertSong(L, "SZA - CTRL", allocateSong("Love Galore", "SZA", 210));
    insertSong(L, "SZA - CTRL", allocateSong("The Weekend", "SZA", 202));

    string input;
    do {
        displayMenu(isAdmin);
        getline(cin, input);

        // ===== PLAYER =====
        if (input == "P" || input == "p") {
            string pname;
            cout << "Nama Playlist: ";
            getline(cin, pname);

            currentPlaylist = findPlaylist(L, pname);
            if (!currentPlaylist || !currentPlaylist->firstsong) {
                cout << "Playlist kosong / tidak ditemukan\n";
            } else {
                currentSong = currentPlaylist->firstsong;
                isPlaying = true;
                cout << "▶ Playing: " << currentSong->title
                     << " - " << currentSong->artist << endl;
            }
        }
        else if (input == "S" || input == "s") {
            if (isPlaying) {
                cout << "⏹ Stopped: " << currentSong->title << endl;
                isPlaying = false;
            } else {
                cout << "Tidak ada lagu yang diputar\n";
            }
        }
        else if (input == "N" || input == "n") {
            if (isPlaying && currentSong->nextsong) {
                currentSong = currentSong->nextsong;
                cout << "▶ Next: " << currentSong->title << endl;
            } else {
                cout << "Tidak ada lagu berikutnya\n";
            }
        }
        else if (input == "B" || input == "b") {
            if (!isPlaying || !currentPlaylist) {
                cout << "Tidak ada lagu diputar\n";
            } else {
                adrsong prev = nullptr;
                adrsong temp = currentPlaylist->firstsong;

                while (temp && temp != currentSong) {
                    prev = temp;
                    temp = temp->nextsong;
                }

                if (prev) {
                    currentSong = prev;
                    cout << "▶ Previous: " << currentSong->title << endl;
                } else {
                    cout << "Sudah di lagu pertama\n";
                }
            }
        }

        // ===== MENU PUBLIK =====
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
            cout << "Keyword: ";
            getline(cin, k);
            searchSong(L, k);
        }

        // ===== ADMIN =====
        else if (input == "A" || input == "a") {
            isAdmin = adminLoginCheck();
        }

    } while (input != "0");

    cout << "Program selesai.\n";
    return 0;
}
