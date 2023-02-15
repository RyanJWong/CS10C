#ifndef __PLAYLIST_NODE__
#define __PLAYLIST_NODE__
#include <iostream>
#include <string>
using std::string;
using std::endl;
using std::cout;
class PlaylistNode {
    private:
        string uniqueID;
        string songName;
        string artistName;
        int songLength;
        PlaylistNode* nextNodePtr;

    public:
        PlaylistNode();
        PlaylistNode(string uniqueID, string songName, string artistName, int songLength);
        void InsertAfter(PlaylistNode* node);
        void SetNext(PlaylistNode* node);
        string GetID();
        string GetSongName();
        string GetArtistName();
        int GetSongLength();
        PlaylistNode* GetNext();
        void PrintPlaylistNode();

};

#endif