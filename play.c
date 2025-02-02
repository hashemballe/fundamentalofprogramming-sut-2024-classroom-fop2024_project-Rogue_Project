#include <ncurses.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <locale.h>
#include <ncursesw/ncurses.h>
#include <wchar.h>
#include <unistd.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#define right 0
#define left 1
#define down 2
#define up 3

#define Regular 0
#define Treasure 1
#define Enchant 2

int heart = 9;
int Floor = 0;
Mix_Music *music = NULL;

typedef struct {
    int x;
    int y;
} point;

typedef struct {
	int type;
	int door_exist[4];
	point doors[4];
	int exist;
    point left_up;
    int width;
    int height;
} room;

point character;

#include "hall.c"
#include "elements.c"
#include "character.c"

void make_doors(room *rooms);
void draw_rooms(room *rooms, int screen_height, int map[][screen_height]);
void draw_room(room r, int screen_height, int map[][screen_height]);
room make_room_in_section(int x_start, int y_start, int section_width, int section_height);
void generate_rooms(room *rooms, int screen_width, int screen_height);

void draw_room(room r, int screen_height, int map[][screen_height]) {
	
	switch(r.type) {
		case 0:
			attron(COLOR_PAIR(1));
			break;
		case 1:
			attron(COLOR_PAIR(2));
			break;
		case 2:
			attron(COLOR_PAIR(3));
			break;		
	}

    for (int i = 0; i < r.width + 2; i++) {
    	map[r.left_up.x + i][r.left_up.y] = 4;
    	map[r.left_up.x + i][r.left_up.y + r.height + 1] = 4;
        mvprintw(r.left_up.y, r.left_up.x + i, "_");
        mvprintw(r.left_up.y + r.height + 1, r.left_up.x + i, "_");
    }
    for (int i = 1; i < r.height + 2; i++) {
    	map[r.left_up.x][r.left_up.y + i] = 4;
    	map[r.left_up.x + r.width + 1][r.left_up.y + i] = 4;
        mvprintw(r.left_up.y + i, r.left_up.x, "|");
        mvprintw(r.left_up.y + i, r.left_up.x + r.width + 1, "|");
    }

	for (int i = 0; i < 4; i++) {
        if (r.door_exist[i] == 1) {
            mvprintw(r.doors[i].y, r.doors[i].x, "+");
            map[r.doors[i].x][r.doors[i].y] = 5;
        }
    }
	
    for (int i = 1; i < r.width + 1; i++) {
        for (int j = 1; j < r.height + 1; j++) {
            mvprintw(r.left_up.y + j, r.left_up.x + i, ".");
            map[r.left_up.x + i][r.left_up.y + j] = 6;
        }
    }
    
    attroff(COLOR_PAIR(3));
    attroff(COLOR_PAIR(2));
    attroff(COLOR_PAIR(1));
}

room make_room_in_section(int x_start, int y_start, int section_width, int section_height) {
    room r;
    r.width = (rand() % (section_width - 6)) + 4;
    r.height = (rand() % (section_height - 6)) + 4;
    r.left_up.x = x_start + 1 + (rand() % (section_width - r.width - 2));
    r.left_up.y = y_start + 1 + (rand() % (section_height - r.height - 2));
    return r;
}

void generate_rooms(room *rooms, int screen_width, int screen_height) {
	for(int i = 0; i < 8; i++) {
		rooms[i].exist = 0;
		for(int j = 0; j < 4; j++) {
			rooms[i].door_exist[j] = 0;
			rooms[i].doors[j].x = -1;
			rooms[i].doors[j].y = -1;
		}
	}
    int sections = 8;
    int section_width = (screen_width-20) / 4;
    int section_height = screen_height / 2;

    
    int mandatory_row = rand() % 2;
    int mandatory_rooms[4] = {1, 1, 1, 1}; 
    int other_row[4] = {rand() % 2, rand() % 2, rand() % 2, rand() % 2};
	
    
    int total_rooms = 4;
    for (int i = 0; i < 4; i++) {
        if (other_row[i]) {
            total_rooms++;
        }
    }
    while (total_rooms < 6) {
        int idx = rand() % 4;
        if (!other_row[idx]) {
            other_row[idx] = 1;
            total_rooms++;
        }
    }

    for (int i = 0; i < 8; i++) {
        int x_start = (i % 4) * section_width + 20;
        int y_start = (i < 4) ? 0 : section_height;
        int create_room;
        if(mandatory_row == 0) {
        	create_room = (i < 4) ? mandatory_rooms[i] : other_row[i - 4];
		}
		else {
			create_room = (i < 4) ? other_row[i] : mandatory_rooms[i - 4];
        }
		if (create_room) {
            rooms[i] = make_room_in_section(x_start, y_start, section_width, section_height);
            rooms[i].exist = 1;
        }
    }
}

void draw_rooms(room *rooms, int screen_height, int map[][screen_height]) {
    for (int i = 0; i < 8; i++) {
    	if(rooms[i].exist == 1)
        	draw_room(rooms[i], screen_height, map);
    }
}

void make_doors(room *rooms) {
	if(rooms[0].exist == 1 && rooms[1].exist == 1 && rooms[2].exist == 1 && rooms[1].exist == 1) {
		
		room r = rooms[0];
		rooms[0].door_exist[right] = 1;
		rooms[0].doors[right].x = r.left_up.x + r.width + 1;
       	rooms[0].doors[right].y = r.left_up.y + 1 + rand() % r.height;
       	
       	r = rooms[1];
       	rooms[1].door_exist[left] = 1;
       	rooms[1].door_exist[right] = 1;
       	rooms[1].doors[right].x = r.left_up.x + r.width + 1;
       	rooms[1].doors[right].y = r.left_up.y + 1 + rand() % r.height;
       	rooms[1].doors[left].x = r.left_up.x;
       	rooms[1].doors[left].y = r.left_up.y + 1 + rand() % r.height;
       	
       	r = rooms[2];
       	rooms[2].door_exist[left] = 1;
       	rooms[2].door_exist[right] = 1;
       	rooms[2].doors[right].x = r.left_up.x + r.width + 1;
       	rooms[2].doors[right].y = r.left_up.y + 1 + rand() % r.height;
       	rooms[2].doors[left].x = r.left_up.x;
       	rooms[2].doors[left].y = r.left_up.y + 1 + rand() % r.height;
       	
       	r = rooms[3];
       	rooms[3].door_exist[left] = 1;
       	rooms[3].doors[left].x = r.left_up.x;
       	rooms[3].doors[left].y = r.left_up.y + 1 + rand() % r.height;
       	
       	int w, q;
      	if(rooms[4].exist == 1) {
      		w = 4;
      		rooms[4].door_exist[up] = 1;
      		rooms[0].door_exist[down] = 1;
      		rooms[4].doors[up].x = rooms[4].left_up.x + 1 + rand() % rooms[4].width;
      		rooms[4].doors[up].y = rooms[4].left_up.y;
      		rooms[0].doors[down].x = rooms[0].left_up.x + 1 + rand() % rooms[0].width;
        	rooms[0].doors[down].y = rooms[0].left_up.y + rooms[0].height + 1;
		}
		else if(rooms[4].exist == 0 && rooms[5].exist == 1) {
      		w = 5;
      		rooms[5].door_exist[up] = 1;
      		rooms[1].door_exist[down] = 1;
      		rooms[5].doors[up].x = rooms[5].left_up.x + 1 + rand() % rooms[5].width;
      		rooms[5].doors[up].y = rooms[5].left_up.y;
      		rooms[1].doors[down].x = rooms[1].left_up.x + 1 + rand() % rooms[1].width;
        	rooms[1].doors[down].y = rooms[1].left_up.y + rooms[1].height + 1;
		}
		else if(rooms[4].exist == 0 && rooms[5].exist == 0 && rooms[6].exist == 1) {
      		w = 6;
      		rooms[6].door_exist[up] = 1;
      		rooms[2].door_exist[down] = 1;
      		rooms[6].doors[up].x = rooms[6].left_up.x + 1 + rand() % rooms[6].width;
      		rooms[6].doors[up].y = rooms[6].left_up.y;
      		rooms[2].doors[down].x = rooms[2].left_up.x + 1 + rand() % rooms[2].width;
        	rooms[2].doors[down].y = rooms[2].left_up.y + rooms[2].height + 1;
		}
		
		
		if(rooms[7].exist == 1) {
      		q = 7;
      		rooms[7].door_exist[up] = 1;
      		rooms[3].door_exist[down] = 1;
      		rooms[7].doors[up].x = rooms[7].left_up.x + 1 + rand() % rooms[7].width;
      		rooms[7].doors[up].y = rooms[7].left_up.y;
      		rooms[3].doors[down].x = rooms[3].left_up.x + 1 + rand() % rooms[3].width;
        	rooms[3].doors[down].y = rooms[3].left_up.y + rooms[3].height + 1;
		}
		else if(rooms[7].exist == 0 && rooms[6].exist == 1) {
      		q = 6;
      		rooms[6].door_exist[up] = 1;
      		rooms[2].door_exist[down] = 1;
      		rooms[6].doors[up].x = rooms[6].left_up.x + 1 + rand() % rooms[6].width;
      		rooms[6].doors[up].y = rooms[6].left_up.y;
      		rooms[2].doors[down].x = rooms[2].left_up.x + 1 + rand() % rooms[2].width;
        	rooms[2].doors[down].y = rooms[2].left_up.y + rooms[2].height + 1;
		}
		else if(rooms[7].exist == 0 && rooms[6].exist == 0 && rooms[5].exist == 1) {
      		q = 5;
      		rooms[5].door_exist[up] = 1;
      		rooms[1].door_exist[down] = 1;
      		rooms[5].doors[up].x = rooms[5].left_up.x + 1 + rand() % rooms[5].width;
      		rooms[5].doors[up].y = rooms[5].left_up.y;
      		rooms[1].doors[down].x = rooms[1].left_up.x + 1 + rand() % rooms[1].width;
        	rooms[1].doors[down].y = rooms[1].left_up.y + rooms[1].height + 1;
		}
		for(int i = w + 1; i <= q; i++) {
			if(rooms[i].exist == 1) {
				if(rooms[i - 1].exist == 1) {
					if(i != q) {
						rooms[i].door_exist[up] = 1;
      					rooms[i - 4].door_exist[down] = 1;
						rooms[i].doors[up].x = rooms[i].left_up.x + 1 + rand() % rooms[i].width;
      					rooms[i].doors[up].y = rooms[i].left_up.y;
      					rooms[i - 4].doors[down].x = rooms[i - 4].left_up.x + 1 + rand() % rooms[i - 4].width;
        				rooms[i - 4].doors[down].y = rooms[i - 4].left_up.y + rooms[i - 4].height + 1;
					}
					if(rand() % 2) {
						rooms[i].door_exist[left] = 1;
      					rooms[i - 1].door_exist[right] = 1;
						rooms[i - 1].doors[right].x = rooms[i - 1].left_up.x + rooms[i - 1].width + 1;
       					rooms[i - 1].doors[right].y = rooms[i - 1].left_up.y + 1 + rand() % rooms[i - 1].height;
						rooms[i].doors[left].x = rooms[i].left_up.x;
       					rooms[i].doors[left].y = rooms[i].left_up.y + 1 + rand() % rooms[i].height;
					}
				}
			}
		}
	}
			
		
	else {
		
		room r = rooms[4];
		rooms[4].door_exist[right] = 1;
		rooms[4].doors[right].x = r.left_up.x + r.width + 1;
       	rooms[4].doors[right].y = r.left_up.y + 1 + rand() % r.height;
       	
       	r = rooms[5];
       	rooms[5].door_exist[right] = 1;
      	rooms[5].door_exist[left] = 1;
       	rooms[5].doors[right].x = r.left_up.x + r.width + 1;
       	rooms[5].doors[right].y = r.left_up.y + 1 + rand() % r.height;
       	rooms[5].doors[left].x = r.left_up.x;
       	rooms[5].doors[left].y = r.left_up.y + 1 + rand() % r.height;
       	
       	r = rooms[6];
       	rooms[6].door_exist[right] = 1;
      	rooms[6].door_exist[left] = 1;
       	rooms[6].doors[right].x = r.left_up.x + r.width + 1;
       	rooms[6].doors[right].y = r.left_up.y + 1 + rand() % r.height;
       	rooms[6].doors[left].x = r.left_up.x;
       	rooms[6].doors[left].y = r.left_up.y + 1 + rand() % r.height;
       	
       	r = rooms[7];
      	rooms[7].door_exist[left] = 1;
       	rooms[7].doors[left].x = r.left_up.x;
       	rooms[7].doors[left].y = r.left_up.y + 1 + rand() % r.height;
       	
       	int w, q;
      	if(rooms[0].exist == 1) {
      		w = 0;
      		rooms[4].door_exist[up] = 1;
      	    rooms[0].door_exist[down] = 1;
      		rooms[4].doors[up].x = rooms[4].left_up.x + 1 + rand() % rooms[4].width;
      		rooms[4].doors[up].y = rooms[4].left_up.y;
      		rooms[0].doors[down].x = rooms[0].left_up.x + 1 + rand() % rooms[0].width;
        	rooms[0].doors[down].y = rooms[0].left_up.y + rooms[0].height + 1;
		}
		else if(rooms[0].exist == 0 && rooms[1].exist == 1) {
      		w = 1;
      		rooms[5].door_exist[up] = 1;
      		rooms[1].door_exist[down] = 1;
      		rooms[5].doors[up].x = rooms[5].left_up.x + 1 + rand() % rooms[5].width;
      		rooms[5].doors[up].y = rooms[5].left_up.y;
      		rooms[1].doors[down].x = rooms[1].left_up.x + 1 + rand() % rooms[1].width;
        	rooms[1].doors[down].y = rooms[1].left_up.y + rooms[1].height + 1;
		}
		else if(rooms[0].exist == 0 && rooms[1].exist == 0 && rooms[2].exist == 1) {
      		w = 2;
      		rooms[6].door_exist[up] = 1;
      		rooms[2].door_exist[down] = 1;
      		rooms[6].doors[up].x = rooms[6].left_up.x + 1 + rand() % rooms[6].width;
      		rooms[6].doors[up].y = rooms[6].left_up.y;
      		rooms[2].doors[down].x = rooms[2].left_up.x + 1 + rand() % rooms[2].width;
        	rooms[2].doors[down].y = rooms[2].left_up.y + rooms[2].height + 1;
		}
		
		
		if(rooms[3].exist == 1) {
      		q = 3;
      		rooms[7].door_exist[up] = 1;
      		rooms[3].door_exist[down] = 1;
      		rooms[7].doors[up].x = rooms[7].left_up.x + 1 + rand() % rooms[7].width;
      		rooms[7].doors[up].y = rooms[7].left_up.y;
      		rooms[3].doors[down].x = rooms[3].left_up.x + 1 + rand() % rooms[3].width;
        	rooms[3].doors[down].y = rooms[3].left_up.y + rooms[3].height + 1;
		}
		else if(rooms[3].exist == 0 && rooms[2].exist == 1) {
      		q = 2;
      		rooms[6].door_exist[up] = 1;
      		rooms[2].door_exist[down] = 1;
      		rooms[6].doors[up].x = rooms[6].left_up.x + 1 + rand() % rooms[6].width;
      		rooms[6].doors[up].y = rooms[6].left_up.y;
      		rooms[2].doors[down].x = rooms[2].left_up.x + 1 + rand() % rooms[2].width;
        	rooms[2].doors[down].y = rooms[2].left_up.y + rooms[2].height + 1;
		}
		else if(rooms[3].exist == 0 && rooms[2].exist == 0 && rooms[1].exist == 1) {
      		q = 1;
      		rooms[5].door_exist[up] = 1;
      		rooms[1].door_exist[down] = 1;
      		rooms[5].doors[up].x = rooms[5].left_up.x + 1 + rand() % rooms[5].width;
      		rooms[5].doors[up].y = rooms[5].left_up.y;
      		rooms[1].doors[down].x = rooms[1].left_up.x + 1 + rand() % rooms[1].width;
        	rooms[1].doors[down].y = rooms[1].left_up.y + rooms[1].height + 1;
		}
		for(int i = w + 1; i <= q; i++) {
			if(rooms[i].exist == 1) {
				if(rooms[i - 1].exist == 1) {
					if(i != q) {
						rooms[i + 4].door_exist[up] = 1;
      					rooms[i].door_exist[down] = 1;
						rooms[i + 4].doors[up].x = rooms[i + 4].left_up.x + 1 + rand() % rooms[i + 4].width;
      					rooms[i + 4].doors[up].y = rooms[i + 4].left_up.y;
      					rooms[i].doors[down].x = rooms[i].left_up.x + 1 + rand() % rooms[i].width;
        				rooms[i].doors[down].y = rooms[i].left_up.y + rooms[i].height + 1;
					}
					if(rand() % 2) {
						rooms[i - 1].door_exist[right] = 1;
      					rooms[i].door_exist[left] = 1;
						rooms[i - 1].doors[right].x = rooms[i - 1].left_up.x + rooms[i - 1].width + 1;
       					rooms[i - 1].doors[right].y = rooms[i - 1].left_up.y + 1 + rand() % rooms[i - 1].height;
						rooms[i].doors[left].x = rooms[i].left_up.x;
       					rooms[i].doors[left].y = rooms[i].left_up.y + 1 + rand() % rooms[i].height;
					}
				}
			}
		}
   	
	}
	
}



int play() {
	Mix_PlayMusic(music, -1);
    clear();
    cbreak();
    noecho();
    curs_set(FALSE);
    start_color();
    srand(time(NULL));
    
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_BLUE, COLOR_BLACK);
    
    int screen_width, screen_height;
    getmaxyx(stdscr, screen_height, screen_width);

    room rooms[8];
	int map[screen_width][screen_height];
	for(int i = 0; i < screen_width; i++) {
		for(int j = 0; j < screen_height; j++) {
			map[i][j] = 0;
		}
	}
	
    generate_rooms(rooms, screen_width, screen_height);
    
    make_doors(rooms);
    make_types(rooms);
    
    draw_rooms(rooms, screen_height, map);
    //refresh();
    make_hallway(rooms, screen_height, map);
    make_traps(rooms, screen_height, map);
    make_pillar(rooms, screen_height, map);
    
    spawn_food(rooms, screen_height, map);
    
    character_make(rooms, screen_height, screen_width, map);
    
    character_move(rooms, screen_height, screen_width, map);
    
    refresh();
    getch();
    endwin();

    return 0;
}
