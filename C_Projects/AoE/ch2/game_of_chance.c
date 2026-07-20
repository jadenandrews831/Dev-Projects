#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>

#include "hacking.h"

#define DATAFILE "/var/chance.data"			// File to store user data

// Custom user struct to store information about users
struct user {
	int uid;
	int credits;
	int highscore;
	char name[100];
	int (*currentgame) ();
};

// Function prototypes
int get_player_data();
void register_new_player();
void update_player_data();
void show_highscore();
void jackpot();
void input_name();
void print_cards(char *, char *, int);
int take_wager(int, int);
void play_the_game();
int pick_a_number();
int dealer_no_match();
int find_the_ace();
void fatal(char *);

// Global variables
struct user player;					// Player struct

int main(){
	int choice, last_game;
	srand(time(0));					// Seed the randomizer with the current time
	if(get_player_data() == -1)
		register_new_player();			// Try to read player data from file. If there is no data, register a new player.

	while(choice != 7){
		printf("-=[ Game of Chance Menu ]=-\n");
		printf("1 - Play the Pick a Number game\n");
		printf("2 - Play the No Match Dealer game\n");
		printf("3 - Play the Find the Ace game\n");
		printf("4 - View current high score\n");
		printf("5 - Change your user name\n");
		printf("6 - Reset your account at 100 credits\n");
		printf("7 - Quit\n");
		printf("[Name: %s]\n", player.name);
		printf("[You have %u credits] -> ", player.credits);
		scanf("%d", &choice);
	}
}
