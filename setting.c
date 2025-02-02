void setting() {
	clear();
	printw("1. Difficulty\n2. Change music");
	int c = getch() - '0';
	switch(c) {
		case 1:
			
			break;
		case 2:
			clear();
			printw("0. OFF!\n");
			printw("1. Jostojou\n");
			printw("2. Freak\n");
			printw("3. Disease\n");
			printw("4. TaneZakhmi\n");
			printw("5. InBoodZendegi\n");
			printw("6. FourthOfJuly\n");
			c = getch() - '0';
			if (music != NULL) {
                Mix_HaltMusic();
                Mix_FreeMusic(music);
                music = NULL;
            }
			switch(c) {
			case 0:
				Mix_CloseAudio();
				break;
			case 1:
			    Mix_OpenAudio(44100, AUDIO_F32SYS, 2, 2048);
 	            music = Mix_LoadMUS("Jostojou.wav");
 	            break;
 	        case 2:
 	            Mix_OpenAudio(44100, AUDIO_F32SYS, 2, 2048);
 	            music = Mix_LoadMUS("Freak.wav");
 	            break;    
 	        case 3:
 	       	    Mix_OpenAudio(44100, AUDIO_F32SYS, 2, 2048);
				music = Mix_LoadMUS("Disease.wav");
				break;
 	        case 4:
 	        	Mix_OpenAudio(44100, AUDIO_F32SYS, 2, 2048);
				music = Mix_LoadMUS("TaneZakhmi.wav");
				break;
			case 5:
				Mix_OpenAudio(44100, AUDIO_F32SYS, 2, 2048);
				music = Mix_LoadMUS("InBoodZendegi.wav");
				break;
			case 6:
				Mix_OpenAudio(44100, AUDIO_F32SYS, 2, 2048);
 	            music = Mix_LoadMUS("FourthOfJuly.wav");
 	            break;
			}	
	}
	welcome();
}