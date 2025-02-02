int validate_username(const char *username);
int validate_password(const char *password);
int validate_email(const char *email);
int save_user(const char *username, const char *password, const char *email);
void create_new_user();
void loop();

void create_new_user() {
    char username[50], password[50], email[50];

    clear();
    printw("--- Create New User ---\n");

    printw("Enter username: ");
    echo();
    getstr(username);


	noecho();
    printw("Enter password: ");
    echo();
    getstr(password);
	printw("Enter email: ");
    echo();
	getstr(email);
	if (!validate_username(username) || strcmp(username, "\0") == 0) {
        printw("\nError: Username already exists or invalid!\n");
        printw("try again?(y/n) ");
        noecho();
		loop();
		return;               
    }
    else if (!validate_password(password)) {
        printw("\nError: Password must be at least 7 characters, contain a number, an uppercase, and a lowercase letter!\n");
    	printw("try again?(y/n) ");
    	noecho();
    	loop();
    	return;
    }
    else if (!validate_email(email)) {
    	printw("\nerror: Invalid email format!\n");
        printw("try again?(y/n) ");
        noecho();
        loop();
        return;
	}

	
	save_user(username, password, email);
    printw("\nUser created successfully!\n Press any button...");
    getch();
    welcome();
}

int validate_username(const char *username) {
    FILE *file = fopen("users.txt", "r");
    if (!file) return 1; 

    char line[250];
    while (fgets(line, sizeof(line), file)) {
        char stored_username[50];
        sscanf(line, "%s", stored_username);
        if (strcmp(username, stored_username) == 0) {
            fclose(file);
            return 0;
        }
    }

    fclose(file);
    return 1;
}

int validate_password(const char *password) {
    if (strlen(password) < 7) return 0;

    int has_upper = 0, has_lower = 0, has_digit = 0;
    for (int i = 0; password[i]; i++) {
        if (isupper(password[i])) has_upper = 1;
        if (islower(password[i])) has_lower = 1;
        if (isdigit(password[i])) has_digit = 1;
    }

    return has_upper && has_lower && has_digit;
}

int validate_email(const char *email) {
    const char *at = strchr(email, '@');
    if (!at || at == email || !strchr(at + 2, '.') || strchr(at + 2, '.') == &email[strlen(email) - 1]) return 0;
    return 1;
}

int save_user(const char *username, const char *password, const char *email) {
    FILE *file = fopen("users.txt", "a");
    if (!file) return 0;

    fprintf(file, "%s %s %s\n", username, password, email);
    fclose(file);
    return 1;
}

void loop() {
	char ch = getch();
	while(1) {
		if(ch == 'y') {
			create_new_user();
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