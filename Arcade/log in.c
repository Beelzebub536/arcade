#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int  user_exists(FILE *, const char *);
static int  user_authen(FILE *, const char *, const char *);
static void get_creds(char *, char *);
static void sign_in(FILE *);
static void sign_up(FILE *);

static int  main_loop(FILE *);

static void clrscr()
{
    system("@cls||clear");
}

static void splash_log(void)
{
    strdly("            ________________________________________ \n");
    strdly("           |  ____________________________________  | \n");
    strdly("           | |    PLEASE SIGN IN BEFORE ENTERING  | | \n");
    strdly("           | |     1. SIGN IN                     | | \n");
    strdly("           | |     2. SIGN UP                     | | \n");
    strdly("           | |     3. EXIT                        | | \n");
    strdly("           | |____________________________________| | \n");
    strdly("           |________________________________________|\n");
}

char * getstr(char *s, int size, FILE *in)
{
	fgets(s, size, in);
	s[strcspn(s, "\r\n")] = 0;
	return s;
}

void main_log(void)
{
	FILE * ptr = fopen("archive.txt","a+");
	main_loop(ptr);
	fclose(ptr);
}

static void sign_in(FILE * ptr)
{
	clrscr();
	char user[255], pass[255];
	get_creds(user, pass);

	if(user_authen(ptr, user, pass))
		printf("Hi %s\n", user);
	else
		printf("Incorrect credentials\n");
}

static void sign_up(FILE * ptr)
{
	clrscr();
	char user[255], pass[255];
	get_creds(user, pass);
	printf("%s\t%s\n", user, pass);

	if(user_exists(ptr, user)) {
		printf("User exists, choose another username.\n");
	} else {
		fseek(ptr, 0L, SEEK_END);
		fprintf(ptr, "%s\t%s\n", user, pass);
		printf("Sign up successful.\n");
		rewind(ptr);
	}
}

static int user_exists(FILE * ptr, const char * user)
{
	char line[1024], *state, *data;
	int ret = -1;
	while(!feof(ptr)) {
		getstr(line, 1024, ptr);
		data = strtok_r(line, "\t", &state);
		ret = strncmp(user, data, 1024);
		if(ret == 0) break;
	}
	rewind(ptr);
	return ret == 0;
}

static int user_authen(FILE * ptr, const char * user, const char * pass)
{
	char line[1024], *state, *data;
	int ret1 = -1, ret2 = -1;
	while(!feof(ptr)) {
		getstr(line, 1024, ptr);
		data = strtok_r(line, "\t", &state);
		ret1 = strncmp(user, data, 255);
		if(ret1 == 0) {
			data = strtok_r(NULL, "\t", &state);
			ret2 = strncmp(pass, data, 255);
			if(ret2 == 0) break;
		}
	}
	rewind(ptr);
	return ret1 == 0 && ret2 == 0;
}

static int main_loop(FILE * ptr)
{
        splash_log();
        int choice;
            top:
		scanf("%d",&choice);
		switch(choice) {
		case 1:
			sign_up(ptr);
			break;
		case 2:
			sign_in(ptr);
			break;
		case 3:
		    printf("EXITED!\n");
			main();
        default:
            clrscn();
            splash_log();
            printf("INVALID INPUT.\nTRY AGAIN>");
            goto top;

		}
}

static void get_creds(char * user, char * pass)
{
	printf("username> ");
	scanf("%s", user);
	printf("password> ");
	scanf("%s", pass);
}

