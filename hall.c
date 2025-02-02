void make_hallway(room *rooms, int screen_height, int map[][screen_height]);
void make_hall(point a, point b, int w, int screen_height, int map[][screen_height]);
void make_traps(room *rooms, int screen_height, int map[][screen_height]);
void make_pillar(room *rooms, int screen_height, int map[][screen_height]);
void make_types(room *rooms);

void make_hallway(room * rooms, int screen_height, int map[][screen_height]) {
  for(int i = 0; i < 8; i++) {
    if(rooms[i].exist == 1 && rooms[i].door_exist[right] == 1) {
      make_hall(rooms[i].doors[right], rooms[i + 1].doors[left], 1, screen_height, map);
      //printw("%d- %d %d ",i, rooms[i].doors[right].x, rooms[i + 1].doors[left].x);
    }
    if(rooms[i].exist == 1 && rooms[i].door_exist[down] == 1) {
      make_hall(rooms[i].doors[down], rooms[i + 4].doors[up], 2, screen_height, map);
      //printw("%d- %d %d ",i, rooms[i].doors[down].x, rooms[i + 4].doors[up]. x, 2);
    }
  }
}


void make_hall(point a, point b, int w, int screen_height, int map[][screen_height]) {
  point hall = a;
  if(w == 1) {
  	hall.x++;
  }
  else {
  	hall.y++;
  }
  mvprintw(hall.y, hall.x, "#");
  map[hall.x][hall.y] = 1;
  while(hall.x != b.x || hall.y != b.y) {
  	
    if(rand() % 2 == 0) {
      if(hall.x < b.x) {
        if(!(hall.y != b.y && hall.x + 1 == b.x) || w != 1) {
          hall.x++;
        }
      }
      else if(hall.x > b.x) {
        if(!(hall.y != b.y && hall.x - 1 == b.x) || w != 1) {
          hall.x--;
        }
      }
    }
    else {
      if(hall.y < b.y) {
        if(!(hall.x != b.x && hall.y + 1 == b.y) || w != 2) {
          hall.y++;
        }
      }
      else if(hall.y > b.y) {
        if(!(hall.x != b.x && hall.y - 1 == b.y) || w != 2) {
          hall.y--;
        }
      }
    }
    if((hall.y != b.y || hall.x != b.x) && (hall.y != a.y || hall.x != a.x)) {
      map[hall.x][hall.y] = 1;
	  mvprintw(hall.y, hall.x, "#");
    }  	
  }
}

void make_traps(room *rooms, int screen_height, int map[][screen_height]) {
	for(int i = 0; i < 8; i++) {
		if(rooms[i].exist == 1 && rand() % 4 == 0) {
			int x = rooms[i].left_up.x + 1 + rand() % rooms[i].width;
			int y = rooms[i].left_up.y + 1 + rand() % rooms[i].height;
			map[x][y] = 2;
			mvprintw(y, x, "^");
		}
		if(rooms[i].exist == 1 && rooms[i].type == 2) {
			int x = rooms[i].left_up.x + 1 + rand() % rooms[i].width;
			int y = rooms[i].left_up.y + 1 + rand() % rooms[i].height;
			map[x][y] = 2;
			mvprintw(y, x, "^");
			 x = rooms[i].left_up.x + 1 + rand() % rooms[i].width;
			 y = rooms[i].left_up.y + 1 + rand() % rooms[i].height;
			map[x][y] = 2;
			mvprintw(y, x, "^");
			 x = rooms[i].left_up.x + 1 + rand() % rooms[i].width;
			 y = rooms[i].left_up.y + 1 + rand() % rooms[i].height;
			map[x][y] = 2;
			mvprintw(y, x, "^");
			 x = rooms[i].left_up.x + 1 + rand() % rooms[i].width;
			 y = rooms[i].left_up.y + 1 + rand() % rooms[i].height;
			map[x][y] = 2;
			mvprintw(y, x, "^");
		}
	}
}

void make_pillar(room *rooms, int screen_height, int map[][screen_height]) {
	for(int i = 0; i < 8; i++) {
		if(rooms[i].exist == 1 && rand() % 2 == 0) {
			int x = rooms[i].left_up.x + 2 + rand() % (rooms[i].width - 2);
			int y = rooms[i].left_up.y + 2 + rand() % (rooms[i].height - 2);
			map[x][y] = 3;
			mvprintw(y, x, "O");
		}
	}
}

void make_types(room *rooms) {
	for(int i = 0; i < 8; i++) {
		rooms[i].type = 0;
		if(rand() % 3 == 0) {
			rooms[i].type = 1;
		}
	}
	if(Floor == 0) {
		while(1) {
			int x = rand() % 8;
			if(rooms[x].exist == 1) {
				rooms[x].type = 2;
				break;
			}
		}
	}
}