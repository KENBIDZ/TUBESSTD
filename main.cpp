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
    cout << "3. Cari Lagu (Global)\n";

    if (isAdmin) {
        cout << "\n--- MENU ADMIN ---\n";
        cout << "4. Tambah Playlist Baru\n";
        cout << "5. Tambah Lagu ke Playlist\n";
        cout << "6. Update Nama Playlist\n";
        cout << "7. Update Detail Lagu\n";
        cout << "8. Hapus Lagu dari Playlist\n";
        cout << "9. Hapus Playlist\n";
    }

    cout << "\n--- PLAYER ---\n";
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

    // ============================================================
    // DATA AWAL (40 LAGU - 5 PLAYLIST)
    // ============================================================
    
    // PLAYLIST 1: Midnight Drive
    insertPlaylist(L, allocatePlaylist("Midnight Drive"));
    insertSong(L, "Midnight Drive", allocateSong("Made For Me", "Muni Long", 188));
    insertSong(L, "Midnight Drive", allocateSong("Saturn", "SZA", 186));
    insertSong(L, "Midnight Drive", allocateSong("After Hours", "Kehlani", 202));
    insertSong(L, "Midnight Drive", allocateSong("Pink + White", "Frank Ocean", 184));
    insertSong(L, "Midnight Drive", allocateSong("Coffee", "Miguel", 286));
    insertSong(L, "Midnight Drive", allocateSong("Location", "Khalid", 219));
    insertSong(L, "Midnight Drive", allocateSong("Best Part", "Daniel Caesar", 209));
    insertSong(L, "Midnight Drive", allocateSong("On My Mama", "Victoria Monét", 184));

    // PLAYLIST 2: Top Charts 2025
    insertPlaylist(L, allocatePlaylist("Top Charts 2025"));
    insertSong(L, "Top Charts 2025", allocateSong("Birds of a Feather", "Billie Eilish", 210));
    insertSong(L, "Top Charts 2025", allocateSong("Espresso", "Sabrina Carpenter", 175));
    insertSong(L, "Top Charts 2025", allocateSong("As It Was", "Harry Styles", 167));
    insertSong(L, "Top Charts 2025", allocateSong("Greedy", "Tate McRae", 131));
    insertSong(L, "Top Charts 2025", allocateSong("Flowers", "Miley Cyrus", 200));
    insertSong(L, "Top Charts 2025", allocateSong("Too Sweet", "Hozier", 251));
    insertSong(L, "Top Charts 2025", allocateSong("Single Soon", "Selena Gomez", 171));
    insertSong(L, "Top Charts 2025", allocateSong("Runaway", "AURORA", 248));

    // PLAYLIST 3: Rap Caviar
    insertPlaylist(L, allocatePlaylist("Rap Caviar"));
    insertSong(L, "Rap Caviar", allocateSong("Squabble Up", "Kendrick Lamar", 157));
    insertSong(L, "Rap Caviar", allocateSong("Million Dollar Baby", "Tommy Richman", 155));
    insertSong(L, "Rap Caviar", allocateSong("Fe!n", "Travis Scott", 191));
    insertSong(L, "Rap Caviar", allocateSong("First Class", "Jack Harlow", 173));
    insertSong(L, "Rap Caviar", allocateSong("Like That", "Future & Metro Boomin", 267));
    insertSong(L, "Rap Caviar", allocateSong("Sticky", "Drake", 243));
    insertSong(L, "Rap Caviar", allocateSong("Pushin P", "Gunna", 136));
    insertSong(L, "Rap Caviar", allocateSong("Dark Thoughts", "Lil Tecca", 164));

    // PLAYLIST 4: Indie Soul & Local
    insertPlaylist(L, allocatePlaylist("Indie Soul & Local"));
    insertSong(L, "Indie Soul & Local", allocateSong("Midnight Sun", "Thee Marloes", 215));
    insertSong(L, "Indie Soul & Local", allocateSong("Telepatía", "Kali Uchis", 160));
    insertSong(L, "Indie Soul & Local", allocateSong("My Love Mine All Mine", "Mitski", 138));
    insertSong(L, "Indie Soul & Local", allocateSong("Self Control", "Frank Ocean", 249));
    insertSong(L, "Indie Soul & Local", allocateSong("Messy", "Lola Young", 192));
    insertSong(L, "Indie Soul & Local", allocateSong("Here With Me", "d4vd", 242));
    insertSong(L, "Indie Soul & Local", allocateSong("Belong Together", "Mark Ambor", 148));
    insertSong(L, "Indie Soul & Local", allocateSong("Supalonely", "BENEE", 223));

    // PLAYLIST 5: SZA Essentials
    insertPlaylist(L, allocatePlaylist("SZA Essentials"));
    insertSong(L, "SZA Essentials", allocateSong("Kill Bill", "SZA", 153));
    insertSong(L, "SZA Essentials", allocateSong("Snooze", "SZA", 192));
    insertSong(L, "SZA Essentials", allocateSong("Nobody Gets Me", "SZA", 180));
    insertSong(L, "SZA Essentials", allocateSong("Love Galore", "SZA", 210));
    insertSong(L, "SZA Essentials", allocateSong("The Weekend", "SZA", 202));
    insertSong(L, "SZA Essentials", allocateSong("Shirt", "SZA", 181));
    insertSong(L, "SZA Essentials", allocateSong("Broken Clocks", "SZA", 231));
    insertSong(L, "SZA Essentials", allocateSong("Drew Barrymore", "SZA", 231));

    string input;
    do {
        displayMenu(isAdmin, isPlaying, currentSong);
        getline(cin, input);

        // --- MENU PUBLIK & ADMIN (1-9) ---
        if (input == "1") {
            viewPlaylists(L);
        }
        else if (input == "2") {
            string p;
            cout << "Nama Playlist: "; getline(cin, p);
            viewSongsInPlaylist(L, p);
        }
        else if (input == "3") {
            string k;
            cout << "Keyword (Judul/Artis): "; getline(cin, k);
            searchSong(L, k);
        }
        else if (isAdmin && input == "4") {
            string name;
            cout << "Nama Playlist Baru: "; getline(cin, name);
            insertPlaylist(L, allocatePlaylist(name));
        }
        else if (isAdmin && input == "5") {
            string pname, title, artist; int dur;
            cout << "Ke Playlist: "; getline(cin, pname);
            cout << "Judul: "; getline(cin, title);
            cout << "Artis: "; getline(cin, artist);
            cout << "Durasi: "; cin >> dur; cin.ignore();
            insertSong(L, pname, allocateSong(title, artist, dur));
        }
        else if (isAdmin && input == "6") {
            string oldN, newN;
            cout << "Nama Playlist Lama: "; getline(cin, oldN);
            cout << "Nama Baru: "; getline(cin, newN);
            updatePlaylist(L, oldN, newN);
        }
        else if (isAdmin && input == "7") {
            string pname, oldT, newT, newA; int newD;
            cout << "Playlist: "; getline(cin, pname);
            cout << "Judul Lama: "; getline(cin, oldT);
            cout << "Judul Baru: "; getline(cin, newT);
            cout << "Artis Baru: "; getline(cin, newA);
            cout << "Durasi Baru: "; cin >> newD; cin.ignore();
            updateSong(L, pname, oldT, newT, newA, newD);
        }
        else if (isAdmin && input == "8") {
            string pname, title;
            cout << "Playlist: "; getline(cin, pname);
            cout << "Judul Lagu: "; getline(cin, title);
            deleteSong(L, pname, title);
        }
        else if (isAdmin && input == "9") {
            string pname;
            cout << "Nama Playlist: "; getline(cin, pname);
            deletePlaylist(L, pname);
        }

        // --- PLAYER LOGIC ---
        else if (input == "P" || input == "p") {
            string pname;
            cout << "Masukkan Nama Playlist untuk diputar: ";
            getline(cin, pname);
            currentPlaylist = findPlaylist(L, pname);
            if (currentPlaylist && currentPlaylist->firstsong) {
                currentSong = currentPlaylist->firstsong;
                isPlaying = true;
                playSong(currentSong);
            } else {
                cout << "[Error] Playlist tidak ditemukan/kosong.\n";
            }
        }
        else if (input == "S" || input == "s") {
            stopSong(currentSong);
            isPlaying = false;
            currentPlaylist = nullptr; 
        }
        else if (input == "N" || input == "n") {
            if (currentSong) {
                currentSong = nextSong(L, currentPlaylist, currentSong);
                playSong(currentSong);
                isPlaying = true;
            } else { cout << "Putar lagu dulu (P).\n"; }
        }
        else if (input == "B" || input == "b") {
            if (currentSong) {
                currentSong = prevSong(L, currentPlaylist, currentSong);
                playSong(currentSong);
                isPlaying = true;
            } else { cout << "Putar lagu dulu (P).\n"; }
        }
        else if (input == "A" || input == "a") {
            isAdmin = adminLoginCheck();
        }

    } while (input != "0");

    cout << "Program selesai. Sampai jumpa, " << user.username << "!\n";
    return 0;
}
