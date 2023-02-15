#include "Playlist.h"
#include <iostream>
#include <string>
// Usings
using std::string;
using std::endl;
using std::cout;
using std::cin;
using std::getline;

// Function stubs


PlaylistNode * GetTail(PlaylistNode * head);


PlaylistNode * AddSong();

void PrintMenu(string title);

void OutputFullPlaylist(PlaylistNode * head);

void RemoveSong(PlaylistNode * head);

void ChangePosition(PlaylistNode * head);

void OutputSongsByArtist(PlaylistNode * head);

void OutputByTotalTime(PlaylistNode * head);


int main() {
    bool running        = true;

    string title;
    char option;

    PlaylistNode * head = new PlaylistNode(); // dummy
    PlaylistNode * tail = head; 

    cout << "Enter playlist's title:" << endl;
    // Use getline to not chop words
    getline(cin, title);

    cout << endl;

    // Display menu
    PrintMenu(title);

    // Make sure file input oes not end
    while (running and not cin.eof()) {

        try {   
            cin >> option;
            // cases for each opt
            switch (option)
            {
                case 'a':
                    cout << "ADD SONG" << endl;

                    // append song to the end of the list and reflect changes in tail
                    tail->SetNext(AddSong());


                    PrintMenu(title);

                    break;

                case 'd':
                    cout << "REMOVE SONG" << endl;

                    RemoveSong(head);
                
                    PrintMenu(title);
                    break;
                case 'c':
                    cout << "CHANGE POSITION OF SONG" << endl;

                    ChangePosition(head);

                    PrintMenu(title);

                    break;
                    
                case 's':
                    cout << "OUTPUT SONGS BY SPECIFIC ARTIST" << endl;

                    OutputSongsByArtist(head);
                    PrintMenu(title);

                    break;    
                case 't': 
                    cout << "OUTPUT TOTAL TIME OF PLAYLIST (IN SECONDS)" << endl;

                    OutputByTotalTime(head);
                    PrintMenu(title);

                    break;
                case 'o':
                    cout << title << " - OUTPUT FULL PLAYLIST" << endl;

                    OutputFullPlaylist(head);
                    PrintMenu(title);

                    break;

                case 'q':
                    // exit loop
                    running = false;

                    break;

                default:
                    cout << "Invalid option." << endl;
                    // wrong character entered
                    break;

            }
            // Make sure to update tail
            tail = GetTail(head);

        }
        catch (string input) {
            // non char was entered
            cout << input << " is not a valid character!" << endl;
        }
        
        
    }

    return 0;
}

// JAMZ PLAYLIST MENU
// a - Add song
// d - Remove song
// c - Change position of song
// s - Output songs by specific artist
// t - Output total time of playlist (in seconds)
// o - Output full playlist
// q - Quit

// Choose an option:
void PrintMenu (string title) {
    cout << title << " PLAYLIST MENU" << endl;
    cout << "a - Add song" << endl;
    cout << "d - Remove song" << endl;
    cout << "c - Change position of song" << endl;
    cout << "s - Output songs by specific artist" << endl;
    cout << "t - Output total time of playlist (in seconds)" << endl;
    cout << "o - Output full playlist" << endl;
    cout << "q - Quit" << endl << endl;
    cout << "Choose an option:" << endl;
}

void OutputFullPlaylist(PlaylistNode * head) {
    // set count variable to display numbers
    int num = 1;
    if (head->GetNext() != nullptr) {
        // loop thru list until end is reached, call print on each node and increment num
        for (PlaylistNode * curr = head->GetNext(); curr != nullptr; curr = curr->GetNext()) {
            cout << num << '.' << endl;
            curr->PrintPlaylistNode();
            ++num;
            cout << endl;
        }
    }
    else {     // special case if the list is empty
        cout << "Playlist is empty" << endl << endl;
    }
}

PlaylistNode * GetTail(PlaylistNode * head) {
    // helper function to grab tail from the head after any updates
    PlaylistNode * tail;

    for (PlaylistNode * curr = head; curr != nullptr; curr = curr->GetNext()) {
        if (curr->GetNext() == nullptr) { // if the next node is null, set current to tail
            tail = curr;
            break;
        }
    }

    return tail;
} 

PlaylistNode * AddSong() { 
    // Enter song's unique ID:
    // SD123
    // Enter song's name:
    // Peg
    // Enter artist's name:
    // Steely Dan
    // Enter song's length (in seconds):
    // 237
    // var initialization
    string id, name, artist;
    int length;

    cout << "Enter song's unique ID:" << endl;
    cin >> id;

    cout << "Enter song's name:" << endl;
    cin.ignore(); // clear buffer
    getline(cin, name); // grab full name
    
    cout << "Enter artist's name:" << endl;
    getline(cin, artist); // grab full name

    cout << "Enter song's length (in seconds):" << endl;
    cin >> length;
    cout << endl;

    return new PlaylistNode(id, name, artist, length); // return new node
}

void RemoveSong(PlaylistNode * head) {
//     REMOVE SONG
// Enter song's unique ID:
// JJ234
// "All For You" removed
    // var declarations
    string id;
    PlaylistNode * curr = head->GetNext();
    PlaylistNode * prev = head; // keep prev as dummy node

    cout << "Enter song's unique ID:" << endl;
    cin >> id; // get id

    while (curr != nullptr) {
        if (curr->GetID() == id) { // remove node if the id matches
            prev->SetNext(curr->GetNext()); // set prev nodes next to the found node's next
            cout << "\"" <<  curr->GetSongName() << "\" removed." << endl << endl;
            delete curr; // delete and exit loop
            return;
        }
        prev = curr; // update prev to the current node
        curr = curr->GetNext(); // increment next
    }

    // if we are at this point the song w/id does not exist
    cout << "Song with ID: " << id << " not found." << endl;
}

// helper function to get list depth
int GetSize(PlaylistNode * head) {
    int size = 0;

    for (PlaylistNode * temp = head->GetNext(); temp != nullptr; temp = temp->GetNext()) {
        size++;
    }
    // basically loop until the end and return the depth
    return size;
}

void ChangePosition(PlaylistNode * head) {
    // declarations
    int current, desired, i;

    //input
    cout << "Enter song's current position:" << endl;
    cin >> current;
    cout << "Enter new position for song:" << endl;
    cin >> desired;

    // create two pointers, one to the current node being looked for and for the previous node to it
    PlaylistNode * currNode,  * prevNode;
    prevNode = head;

    // grab node to move and node before it
    i = 1;
    for (currNode = head->GetNext(); currNode != nullptr; currNode = currNode->GetNext()) {
        if (i == current) {
            break;
        }
        ++i;
        prevNode = currNode;
    }

    // set the previous nodes next to the node being moved's next
    prevNode->SetNext(currNode->GetNext());

    if (desired <= 1) { // If the user enters a new position that is less than 1, move the node to the position 1 (the head)
        currNode->SetNext(head->GetNext());
        head->SetNext(currNode);
    }
    else if (desired > GetSize(head)) { // If the user enters a new position greater than n, move the node to position n (the tail)
        PlaylistNode * tail = GetTail(head);
        tail->SetNext(currNode);
        currNode->SetNext(0); // set next to null
    }

    else { // otherwise move the ndode to the specified location
        PlaylistNode * desiredNode, * prevToDesired;
        i = 1;
        // grab the desired location and the node before it
        for (desiredNode = head->GetNext(); desiredNode != nullptr; desiredNode = desiredNode->GetNext()) {
            if (i == desired) { // once i find it exit the loop
                break;
            }
            ++i;
            prevToDesired = desiredNode;
        }

        prevToDesired->SetNext(currNode); // Insert the current node at the desired node's position, set the current's next to desired
        currNode->SetNext(desiredNode);
        cout << "\"" <<currNode->GetSongName() << "\" moved to position " << desired << endl << endl;
    }
}

void OutputSongsByArtist(PlaylistNode * head) {
    string name;
    int num = 1;

    cout << "Enter artist's name:" << endl;

    cin.ignore(); // clear buffer
    getline(cin, name);

    cout << endl;
    
    // loop and only print the ones w/ matching artists
    for (PlaylistNode * curr = head->GetNext(); curr != nullptr; curr = curr->GetNext()) {
        if (curr->GetArtistName() == name) {
            cout << num << '.' << endl;
            curr->PrintPlaylistNode();
            cout << endl;
        }
        ++num;  
    }
}

// Add up the time from all the songs and display
void OutputByTotalTime(PlaylistNode * head) {
    int total = 0;
    for (PlaylistNode * curr = head->GetNext(); curr != nullptr; curr = curr->GetNext()) {
        total+=curr->GetSongLength(); 
    }
    cout << "Total time: " << total << " seconds" << endl << endl;
}