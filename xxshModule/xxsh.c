#include "xxsh.h"

#define MAX_LENGTH 50

int main(void)
{
	init_env_vars();
	main_loop();
	return 0;
}

/*Main user input loop*/
void main_loop()
{
	char buffer[MAX_LENGTH];
	char buffer2[MAX_LENGTH];
	char *token;
	char *token2;
	char *token3;
	FILE *env_file;

	if()


	while ((printf("%s@%s:%s>> ", get_user(), get_host(), get_path()) > 0)
	       && (fgets(buffer, MAX_LENGTH, stdin) != NULL)) {
		/*Clearing stdin */
		if (buffer[strlen(buffer) - 1] != '\n') {
			clear_buffer();
		}
		strcpy(buffer2, buffer);	//creates copy of command for insert into history
		token = strtok(buffer, "  \n");
		if (token == NULL) {
			continue;
		}
		/*export needs valid key/value */
		if (strcmp(token, "export") == 0) {
			token2 = strtok(NULL, "=");
			//Input needs in form of ENVAR=VALUE
			if (token2 != NULL) {
				token3 = strtok(NULL, "\n");
			}
			if ((token2 != NULL) && (token3 != NULL)) {
				parse(token2, token3);
			}
		}
		/*env needs only env as input */
		else if (strcmp(token, "env") == 0) {
			token2 = strtok(NULL, "\n");
			if (token2 == NULL) {
				print_var();
			}
		}
		/*history needs only history as input */
		else if (strcmp(token, "history") == 0) {
			token2 = strtok(NULL, "\n");
			if (token2 == NULL) {
				history();
			}
		}
		/*quit needs only quit as input */
		else if (strcmp(token, "quit") == 0) {
			token2 = strtok(NULL, "\n");
			if (token2 == NULL) {
				write_env(FILE_NAME);
				destroy_env();
				destroy_history();
				break;
			}

		}
		/*exit need exit as input */
		else if (strcmp(token, "exit") == 0) {
			token2 = strtok(NULL, "\n");
			if (token2 == NULL) {
				write_env(FILE_NAME);
				destroy_env();
				destroy_history();
				break;
			}
		} else {
			printf("%s@%s:%s>> Not a valid command\n",
			       get_user(), get_host(), get_path());
		}
		add_history(buffer2);
	}
}

void parse(char *key, char *value)
{
	if (strcmp(key, "HISTSIZE") == 0) {
		if (atoi(value) <= 0) {
			return;
		}
		set_var(key, value);
	}
	/*any env other than history */
	else {
		set_var(key, value);
	}
}

void clear_buffer()
{
	char c =' ';
	while ((c = getchar() != '\n' && c != EOF)) {
	}
}
