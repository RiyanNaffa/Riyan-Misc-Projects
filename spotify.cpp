#include<iostream>
#include<chrono>
#include<string>

// CIRCULAR LIST

struct Song{
    std::string title;
    std::string artist;
    int year;
//    int length;
    bool favorite = false;
    struct Song* next;
    struct Song* prev;
};

struct Song *rear = NULL;

void add_song_to_playlist(std::string, std::string, int);
void remove_song_from_playlist(std::string);
void play_in_order();
//void play_shuffle();
void add_to_favorite(std::string);
void play_favorites();
//void play_next_song();
//void play_prev_song();
int playlist_size();

int main(){
    std::cout << "============================================================\n========== PLAY YOUR SONGS, SING YOUR HEARTS OUT! ==========\n============================================================\n\n";
    add_song_to_playlist("Neo-Aspect", "Roselia", 2020);
    add_song_to_playlist("Never forget", "kessoku band", 2022);
    add_song_to_playlist("If I could be a constellation", "kessoku band", 2022);
    add_song_to_playlist("Borderline", "Tame Impala", 2020);
    add_song_to_playlist("The Less I Know The Better", "Tame Impala", 2015);
    add_song_to_playlist("Bibbidiba", "Hoshimachi Suisei", 2024);
    add_song_to_playlist("What is wrong with", "kessoku band", 2022);
    add_song_to_playlist("Black Shout", "Roselia", 2020);

    std::cout << "Playlist (" << playlist_size() << " songs)\n";
    play_in_order();

    return 0;
}

void add_song_to_playlist(std::string title = "Untitled", std::string artist = "No artist", int year = 0){
    struct Song *new_song = new Song;
    // SET THE APPROPRIATE POINTERS
    if(rear == NULL) {                  // Empty playlist
        rear = new_song;
        new_song->next = new_song;
        new_song->prev = new_song;
    }
    else{
        new_song->prev = rear;
        new_song->next = rear->next;
        new_song->next->prev = new_song;
        rear->next = new_song;
        rear = new_song;
    }
    // SET THE VALUES
    new_song->title = title;
    new_song->artist = artist;
    new_song->year = year;
//    new_song->length = length;

    std::cout << "\"" << new_song->title << "\"" << " is added to the playlist.\n";
}

void remove_song_from_playlist(std::string title = "_NO_TITLE_"){
    struct Song *walker_node = rear;
    do{
        walker_node = walker_node->next;
        if (walker_node->title == title){
            if(walker_node == rear) rear = rear->prev;
            walker_node->prev->next = walker_node->next;
            walker_node->next->prev = walker_node->prev;
            delete walker_node;
            return;
        }
    } while (walker_node != rear);
    std::cout << "Song not found.\n";
}

void play_in_order(){
    struct Song *walker_node = rear;
    do{
        walker_node = walker_node->next;
        std::cout << "Now playing: " << walker_node->title << " by " << walker_node->artist << " (" << walker_node->year << ")\n";
    } while (walker_node != rear);
}

void add_to_favorite(std::string title){
    struct Song *walker_node = rear;
    do{
        walker_node = walker_node->next;
        if(walker_node->title == title) walker_node->favorite = true;
    } while (walker_node != rear);
}

void play_favorites(){
    struct Song *walker_node = rear;
    do{
        walker_node = walker_node->next;
        if(walker_node->favorite) std::cout << "Now playing: " << walker_node->title << " by " << walker_node->artist << " (" << walker_node->year << ")\n";
    } while (walker_node != rear);
}

int playlist_size(){
    struct Song *walker_node = rear;
    int ctr = 0;
    do{
        walker_node = walker_node->next;
        ctr++;
    } while(walker_node != rear);
    return ctr;
}