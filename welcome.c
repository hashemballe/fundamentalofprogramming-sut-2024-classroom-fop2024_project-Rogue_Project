#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char logged_username[50];
int logged;
void welcome();

#include "signup.c"
#include "login.c"
#include "play.c"
#include "setting.c"


void welcome() {
	clear();
	printw("Welcome to ROGUE Game!\n");
    printw("1. signup\n");
    printw("2. login\n");
    printw("3. play\n");
    printw("4. scoreboard\n");
    printw("5. setting\n");
    printw("6. Exit\n");
    printw("Choose an option: ");
    
    int choice = getch() - '0';

    switch (choice) {
        case 1:
            create_new_user();
            break;
        case 2:
            log_in();
            break;    
        case 3:
        	if(logged == 1)
			play();
			break;
        case 4:
			//scoreboard();
			break;
		case 5:
			setting();
			break;
		case 6:
            printw("\nExiting...\n");
            break;		    
        default:
            welcome(); 
    }
}

int main() {
	SDL_Init(SDL_INIT_AUDIO);
	Mix_OpenAudio(44100, AUDIO_F32SYS, 2, 2048);
	Mix_AllocateChannels(16);
	setlocale(LC_ALL, "");
	logged = 1;
	
    initscr();
    cbreak(); 
    noecho(); 
	
	welcome();

    printw("Press any key to exit...");
    Mix_FreeMusic(music);
    Mix_CloseAudio();
    SDL_Quit();
    getch();
    endwin();

    return 0;
}