typedef struct {
    point place;
    int health_value;
} Food;

int GOLD = 0;
int DARK_GOLD = 0;

point gold;
int gold_count = 0;
point dark_gold;
int dark_gold_count = 0;

point golds[10];
point dark_golds[5];

Food food_items[10];
int food_menu[5];
int foods_number = 0;
int food_count = 0;
int player_hunger = 9;


point mace = {0};
point dagger = {0};
point wand = {0};
point arrow = {0};
point sword = {0};
int backpack[5] = {0};
int weapon;

int spells[3] = {0};
point health;
point speed;
point damage;

void spawn_food(room * rooms, int screen_height, int map[][screen_height]) {
	for(int i = 0; i < 5; i++) {
		food_menu[i] = 0;
	}
	for(int i = 0; i < 8; i++) {
		if(rooms[i].exist == 1 && rand() % 2 == 0 && food_count < 10) {
			int x = rooms[i].left_up.x + 2 + rand() % (rooms[i].width - 3);
			int y = rooms[i].left_up.y + 2 + rand() % (rooms[i].height - 3);
			if(map[x + 1][y] == 6) {
			map[x][y] = 7;
			food_items[food_count].place.x = x;
			food_items[food_count].place.y = y;
			food_items[food_count].health_value = 2;
			//phase 2
			food_count ++;
			mvaddwstr(y, x, L"\U0001F372");
			}
		}
		
		if(rooms[i].exist == 1 && rand() % 3 == 0) {
			int x = rooms[i].left_up.x + 2 + rand() % (rooms[i].width - 3);
			int y = rooms[i].left_up.y + 2 + rand() % (rooms[i].height - 3);
			if(map[x + 1][y] == 6) {
			map[x][y] = 8;
			golds[gold_count].y = y;
			golds[gold_count++].x = x;
			//phase 2
			mvaddwstr(y, x, L"\U0001F4b0");
			}
		}
		
		if(rooms[i].exist == 1 && rand() % 5 == 0) {
			int x = rooms[i].left_up.x + 2 + rand() % (rooms[i].width - 3);
			int y = rooms[i].left_up.y + 2 + rand() % (rooms[i].height - 3);
			if(map[x + 1][y] == 6) {
			map[x][y] = 9;
			dark_golds[dark_gold_count].y = y;
			dark_golds[dark_gold_count++].x = x;
			//phase 2
			mvaddwstr(y, x, L"\U0001F6e2");
			}
		}
		
		if(rooms[i].exist == 1 && rand() % 5 == 0) {
			int x = rooms[i].left_up.x + 2 + rand() % (rooms[i].width - 3);
			int y = rooms[i].left_up.y + 2 + rand() % (rooms[i].height - 3);
			if(map[x + 1][y] == 6) {
			map[x][y] = 10;
			mace.y = y;
			mace.x = x;
			//phase 2
			mvaddwstr(y, x, L"\U00002692");
			}
		}
		
		if(rooms[i].exist == 1 && rand() % 5 == 0) {
			int x = rooms[i].left_up.x + 2 + rand() % (rooms[i].width - 3);
			int y = rooms[i].left_up.y + 2 + rand() % (rooms[i].height - 3);
			if(map[x + 1][y] == 6) {
			map[x][y] = 11;
			dagger.y = y;
			dagger.x = x;
			//phase 2
			mvaddwstr(y, x, L"\U0001F5E1");
			}
		}
		
		if(rooms[i].exist == 1 && rand() % 5 == 0) {
			int x = rooms[i].left_up.x + 2 + rand() % (rooms[i].width - 3);
			int y = rooms[i].left_up.y + 2 + rand() % (rooms[i].height - 3);
			if(map[x + 1][y] == 6) {
			map[x][y] = 12;
			wand.y = y;
			wand.x = x;
			//phase 2
			mvaddwstr(y, x, L"\U0001FA84");
			}
		}
		
		if(rooms[i].exist == 1 && rand() % 5 == 0) {
			int x = rooms[i].left_up.x + 2 + rand() % (rooms[i].width - 3);
			int y = rooms[i].left_up.y + 2 + rand() % (rooms[i].height - 3);
			if(map[x + 1][y] == 6) {
			map[x][y] = 13;
			arrow.y = y;
			arrow.x = x;
			//phase 2
			mvaddwstr(y, x, L"\U000027b3");
			}
		}
		
		if(rooms[i].exist == 1 && rand() % 5 == 0) {
			int x = rooms[i].left_up.x + 2 + rand() % (rooms[i].width - 3);
			int y = rooms[i].left_up.y + 2 + rand() % (rooms[i].height - 3);
			if(map[x + 1][y] == 6) {
			map[x][y] = 14;
			sword.y = y;
			sword.x = x;
			//phase 2
			mvaddwstr(y, x, L"\U00002694");
			}
		}
		if(rooms[i].exist == 1 && rand() % 5 == 0) {
			int x = rooms[i].left_up.x + 2 + rand() % (rooms[i].width - 3);
			int y = rooms[i].left_up.y + 2 + rand() % (rooms[i].height - 3);
			if(map[x + 1][y] == 6) {
			map[x][y] = 15;
			health.y = y;
			health.x = x;
			//phase 2
			mvaddwstr(y, x, L"\U0001f375");
			}
		}
		if(rooms[i].exist == 1 && rand() % 5 == 0) {
			int x = rooms[i].left_up.x + 2 + rand() % (rooms[i].width - 3);
			int y = rooms[i].left_up.y + 2 + rand() % (rooms[i].height - 3);
			if(map[x + 1][y] == 6) {
			map[x][y] = 16;
			speed.y = y;
			speed.x = x;
			//phase 2
			mvaddwstr(y, x, L"\U0001f37b");
			}
		}
		if(rooms[i].exist == 1 && rand() % 5 == 0) {
			int x = rooms[i].left_up.x + 2 + rand() % (rooms[i].width - 3);
			int y = rooms[i].left_up.y + 2 + rand() % (rooms[i].height - 3);
			if(map[x + 1][y] == 6) {
			map[x][y] = 17;
			damage.y = y;
			damage.x = x;
			//phase 2
			mvaddwstr(y, x, L"\U0001f6b1");
			}
		}
		if(rooms[i].exist == 1 && rooms[i].type == 1) {
			int x = rooms[i].left_up.x + 2 + rand() % (rooms[i].width - 3);
			int y = rooms[i].left_up.y + 2 + rand() % (rooms[i].height - 3);
			if(map[x + 1][y] == 6) {
			map[x][y] = 17;
			damage.y = y;
			damage.x = x;
			//phase 2
			mvaddwstr(y, x, L"\U0001f6b1");
			}
			x = rooms[i].left_up.x + 2 + rand() % (rooms[i].width - 3);
			y = rooms[i].left_up.y + 2 + rand() % (rooms[i].height - 3);
			if(map[x + 1][y] == 6) {
			map[x][y] = 16;
			speed.y = y;
			speed.x = x;
			//phase 2
			mvaddwstr(y, x, L"\U0001f37b");
			}
			x = rooms[i].left_up.x + 2 + rand() % (rooms[i].width - 3);
			y = rooms[i].left_up.y + 2 + rand() % (rooms[i].height - 3);
			if(map[x + 1][y] == 6) {
			map[x][y] = 15;
			health.y = y;
			health.x = x;
			//phase 2
			mvaddwstr(y, x, L"\U0001f375");
			}
		}
	}
}

void update_hunger() {
    player_hunger++;
    if (player_hunger > 10) {
        heart --;
        if (heart < 0) heart = 0;
    }
}

void add_food_to_menu(int x, int y, int screen_height, int map[][screen_height]) {
    Food food = {0};
    for(int i = 0; i < food_count; i++) {
        if(food_items[i].place.x == x && food_items[i].place.y == y) {
            food = food_items[i];
            food_items[i].place.x = 0;
            food_items[i].place.y = 0;
            if(foods_number < 5) {
        		food_menu[foods_number] = food.health_value;
        		foods_number++;
    		} 		
			else {
        		for(int i = 0; i < 4; i++) {
        	    	food_menu[i] = food_menu[i + 1];
        		}
        		food_menu[4] = food.health_value;
    		}
		break;
        }
    }
    
}

void consume_food() {
    mvprintw(18, 2, "FOOD MENU");
    for(int i = 0; i < foods_number; i++) {
        mvprintw(20 + 2 * i, 2, "%d       %d   ", i, food_menu[i]);
    }
    int c = getch() - '0';
    if(c >= 0 && c < foods_number) {
    	heart += food_menu[c];
        for(int i = c; i < foods_number - 1; i++) {
            food_menu[i] = food_menu[i + 1];
        }
        foods_number--;
    }
    for(int i = 0; i < 10; i++) {
		mvprintw(18 +i, 2, "              ");
	}
}

void wear_weopon() {
	mvprintw(18, 2, "WEAPON MENU");
    int j = 0;
    for(int i = 0; i < 5; i++) {
    	if(backpack[i] == 1) {
    		switch(i) {
    			case 0: 
    				mvprintw(20 + 2 * j++, 2, "%d      MACE", i);
    				break;
    			case 1:
					mvprintw(20 + 2 * j++, 2, "%d      DAGGER", i);
    				break;
				case 2:
					mvprintw(20 + 2 * j++, 2, "%d      WAND", i);
    				break;	
				case 3:
					mvprintw(20 + 2 * j++, 2, "%d      ARROW", i);
    				break;	
				case 4:
					mvprintw(20 + 2 * j++, 2, "%d      SWORD", i);
    				break;					
			}
		}
	}
    int c = getch() - '0';
    if(c >= 0 && c < 5 && backpack[c] == 1) {
		weapon = c;
    }
    for(int i = 0; i < 10; i++) {
		mvprintw(18 + i, 2, "              ");
	}
}

void drink_spell() {
	mvprintw(18, 2, "SPELL MENU");
    int j = 0;
    for(int i = 0; i < 3; i++) {
    	if(spells[i] == 1) {
    		switch(i) {
    			case 0: 
    				mvprintw(20 + 2 * j++, 2, "%d      HEALTH", i);
    				break;
    			case 1:
					mvprintw(20 + 2 * j++, 2, "%d      SPEED", i);
    				break;
				case 2:
					mvprintw(20 + 2 * j++, 2, "%d      DAMAGE", i);
    				break;					
			}
		}
	}
    int c = getch() - '0';
    for(int i = 0; i < 10; i++) {
		mvprintw(18 + i, 2, "              ");
	}
    //phase 2
}
