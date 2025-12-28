#ifndef SPOTIFY_H_INCLUDED
#define SPOTIFY_H_INCLUDED

#include <iostream>
#include <string>

using namespace std;

struct User {
    string username;
    string password;
};

struct Playlist;
struct Song;

typedef Playlist* adrplaylist;
typedef Song* adrsong;

struct Song {
    string title;
    string artist;
    int duration;
    adrsong nextsong;
    adrsong prevsong; // Tambahan untuk fitur prev
};

struct Playlist {
    string name;
    adrplaylist nextplaylist;
    adrsong firstsong;
};

struct PlaylistList {
    adrplaylist firstplaylist;
};

void createPlaylistList(PlaylistList &L);

adrplaylist allocatePlaylist(string name);
adrsong allocateSong(string title, string artist, int duration);

adrplaylist findPlaylist(PlaylistList L, string playlistName);

void insertPlaylist(PlaylistList &L, adrplaylist p);
void insertSong(PlaylistList &L, string playlistName, adrsong s);

void deletePlaylist(PlaylistList &L, string playlistName);
void deleteSong(PlaylistList &L, string playlistName, string songTitle);

void updatePlaylist(PlaylistList &L, string oldName, string newName);
void updateSong(PlaylistList &L,string playlistName,string oldTitle,string newTitle,string newArtist,int newDuration);

void viewPlaylists(PlaylistList L);
void viewSongsInPlaylist(PlaylistList L, string playlistName);
void searchSong(PlaylistList L, string keyword);

adrsong nextSong(PlaylistList L, adrplaylist currentP, adrsong currentS);
adrsong prevSong(PlaylistList L, adrplaylist currentP, adrsong currentS);
adrsong findSimilarSong(PlaylistList L, adrsong currentS);

#endif // SPOTIFY_H_INCLUDED

