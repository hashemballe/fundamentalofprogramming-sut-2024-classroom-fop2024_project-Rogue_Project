void log_in();
int validate_login(const char *username, const char *password);
void loop1();
void log_in() {
	char username[50], password[50];
	
	
	clear();
    printw("--- FIRST LOG IN ! ---\n");
	
    printw("Enter username: ");
    echo();
    getstr(username);
    
    noecho();
	printw("Enter password: ");
	echo();
	getstr(password);
	
	noecho();
	
	if(validate_login(username, password)) {
	printw("\nUser logged in successfully!\n Press any button...");
	getch();
	logged = 1;
	strcpy(logged_username, username);
	welcome();
	}
}
int validate_login(const char *username, const char *password) {
    FILE *file = fopen("users.txt", "r");
    if (!file) {
	printw("\nusername doesn't exist!\n Press any key to retry...");
    getch();
	return 0; 
	}
    char line[250];
    while (fgets(line, sizeof(line), file)) {
        char stored_username[50];
        char stored_password[50];
        sscanf(line, "%s", stored_username);
        sscanf(line + strlen(stored_username) + 1, "%s", stored_password);
        if (strcmp(username, stored_username) == 0) {
        	if(strcmp(password, stored_password) == 0) {
				fclose(file);
            	return 1;
			}
			
			else {
				noecho();
				printw("\nWRONG password!\n");
				printw("try again?(y/n) ");
				loop1(); 
				fclose(file);
				return 0;
			}
            
        }
    	
    }
		printw("\nusername doesn't exist!\n Press any key to retry...");
        printw("try again?(y/n) ");
        noecho();
		loop1(); 
		fclose(file);
		return 0;
}
void loop1() {
	char ch = getch();
	while(1) {
		if(ch == 'y') {
			log_in();
			return;
		}
		else if(ch == 'n') {
			welcome();
			return;
		}
		else {
			ch = getch();
		}
	}
}