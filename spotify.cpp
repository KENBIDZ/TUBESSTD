#include "spotify.h"

void createPlaylistList(PlaylistList &L) {
    L.firstplaylist = nullptr;
}

adrplaylist allocatePlaylist(string name) {
    adrplaylist p = new Playlist;
    p->name = name;
    p->nextplaylist = nullptr;
    p->firstsong = nullptr;
    return p;
}

adrsong allocateSong(string title, string artist, int duration) {
    adrsong s = new Song;
    s->title = title;
    s->artist = artist;
    s->duration = duration;
    s->nextsong = nullptr;
    s->prevsong = nullptr; // Inisialisasi nullptr
    return s;
}

adrplaylist findPlaylist(PlaylistList L, string playlistName) {
    adrplaylist p = L.firstplaylist;
    while (p != nullptr) {
        if (p->name == playlistName) return p;
        p = p->nextplaylist;
    }
    return nullptr;
}

void insertPlaylist(PlaylistList &L, adrplaylist p) {
    if (L.firstplaylist == nullptr)
        L.firstplaylist = p;
    else {
        adrplaylist q = L.firstplaylist;
        while (q->nextplaylist != nullptr)
            q = q->nextplaylist;
        q->nextplaylist = p;
    }
}

void insertSong(PlaylistList &L, string playlistName, adrsong s) {
    adrplaylist p = findPlaylist(L, playlistName);
    if (!p) return;

    if (p->firstsong == nullptr) {
        p->firstsong = s;
    } else {
        adrsong q = p->firstsong;
        while (q->nextsong != nullptr)
            q = q->nextsong;
        q->nextsong = s;
        s->prevsong = q; // Hubungkan ke belakang
    }
}
adrsong nextSong(PlaylistList L, adrplaylist currentP, adrsong currentS) {
    if (currentS == nullptr) return nullptr;

    // i. Jika sedang berada di playlist
    if (currentP != nullptr) {
        if (currentS->nextsong != nullptr) {
            return currentS->nextsong;
        } else {
            cout << "[End of Playlist]" << endl;
            return currentS; // Tetap di lagu terakhir
        }
    } 
    return findSimilarSong(L, currentS);
}
adrsong prevSong(PlaylistList L, adrplaylist currentP, adrsong currentS) {
    if (currentS == nullptr) return nullptr;

    if (currentP != nullptr) {
        if (currentS->prevsong != nullptr) {
            return currentS->prevsong;
        } else {
            cout << "[Start of Playlist]" << endl;
            return currentS;
        }
    }

    return findSimilarSong(L, currentS);
}

// FUNGSI MENCARI LAGU MIRIP (Berdasarkan Artis)
adrsong findSimilarSong(PlaylistList L, adrsong currentS) {
    adrplaylist p = L.firstplaylist;
    adrsong fallback = nullptr;

    while (p != nullptr) {
        adrsong s = p->firstsong;
        while (s != nullptr) {
            // Cari artis yang sama tapi bukan lagu yang sedang diputar
            if (s->artist == currentS->artist && s->title != currentS->title) {
                return s;
            }
            // Simpan lagu apa saja sebagai fallback (lagu acak/berikutnya)
            if (s != currentS && fallback == nullptr) {
                fallback = s;
            }
            s = s->nextsong;
        }
        p = p->nextplaylist;
    }

    if (fallback != nullptr) {
        cout << "[Saran lagu lain]" << endl;
        return fallback;
    }

    cout << "[Tidak ada lagu mirip]" << endl;
    return currentS;
}

void deletePlaylist(PlaylistList &L, string playlistName) {
    adrplaylist curr = L.firstplaylist;
    adrplaylist prev = nullptr;

    while (curr && curr->name != playlistName) {
        prev = curr;
        curr = curr->nextplaylist;
    }
    if (!curr) return;

    if (!prev) L.firstplaylist = curr->nextplaylist;
    else prev->nextplaylist = curr->nextplaylist;

    adrsong s = curr->firstsong;
    while (s) {
        adrsong tmp = s;
        s = s->nextsong;
        delete tmp;
    }
    delete curr;
}

void deleteSong(PlaylistList &L, string playlistName, string songTitle) {
    adrplaylist p = findPlaylist(L, playlistName);
    if (!p) return;

    adrsong curr = p->firstsong;
    adrsong prev = nullptr;

    while (curr && curr->title != songTitle) {
        prev = curr;
        curr = curr->nextsong;
    }
    if (!curr) return;

    if (!prev) p->firstsong = curr->nextsong;
    else prev->nextsong = curr->nextsong;

    delete curr;
}

void updatePlaylist(PlaylistList &L, string oldName, string newName) {
    adrplaylist p = findPlaylist(L, oldName);
    if (p) p->name = newName;
}

void updateSong(
    PlaylistList &L,
    string playlistName,
    string oldTitle,
    string newTitle,
    string newArtist,
    int newDuration
) {
    adrplaylist p = findPlaylist(L, playlistName);
    if (!p) return;

    adrsong s = p->firstsong;
    while (s) {
        if (s->title == oldTitle) {
            s->title = newTitle;
            s->artist = newArtist;
            s->duration = newDuration;
            return;
        }
        s = s->nextsong;
    }
}

void viewPlaylists(PlaylistList L) {
    adrplaylist p = L.firstplaylist;
    int i = 1;
    while (p) {
        cout << i++ << ". " << p->name << endl;
        p = p->nextplaylist;
    }
}

void viewSongsInPlaylist(PlaylistList L, string playlistName) {
    adrplaylist p = findPlaylist(L, playlistName);
    if (!p) return;

    adrsong s = p->firstsong;
    int i = 1;
    while (s) {
        cout << i++ << ". " << s->title
             << " - " << s->artist << endl;
        s = s->nextsong;
    }
}

void searchSong(PlaylistList L, string keyword) {
    adrplaylist p = L.firstplaylist;
    while (p) {
        adrsong s = p->firstsong;
        while (s) {
            if (s->title.find(keyword) != string::npos ||
                s->artist.find(keyword) != string::npos) {
                cout << s->title << " - " << s->artist
                     << " (" << p->name << ")" << endl;
            }
            s = s->nextsong;
        }
        p = p->nextplaylist;
    }
}

