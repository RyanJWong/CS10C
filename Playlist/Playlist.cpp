#include <iostream>
#include <string>
#include "Playlist.h"

PlaylistNode::PlaylistNode() {
    uniqueID    = "none";
    songName    = "none";
    artistName  = "none";
    songLength  = 0;
    nextNodePtr = 0;
}

PlaylistNode::PlaylistNode(string uniqueID, string songName, string artistName, int songLength) : uniqueID(uniqueID), songName(songName), artistName(artistName), songLength(songLength), nextNodePtr(0) {

}

void PlaylistNode::InsertAfter(PlaylistNode* node) {
    node->SetNext(this->nextNodePtr);
    SetNext(node);
}

void PlaylistNode::SetNext(PlaylistNode* node) {
    nextNodePtr = node;
}

string PlaylistNode::GetID() {
    return uniqueID;
}

string PlaylistNode::GetSongName() {
    return songName;
}

string PlaylistNode::GetArtistName() {
    return artistName;
}

int PlaylistNode::GetSongLength() {
    return songLength;
}

PlaylistNode* PlaylistNode::GetNext() {
    return nextNodePtr;
}

void PlaylistNode::PrintPlaylistNode() {
    cout << "Unique ID: " << uniqueID << endl;
    cout << "Song Name: " << songName << endl;
    cout << "Artist Name: " << artistName << endl;
    cout << "Song Length (in seconds): " << songLength << endl; 
}
