#include "xxsh.h"

#define MAX_LENGTH 50

int main(void)
{
	init_env_vars();
	init_list();
	check_env(FILE_NAME);
	read_env(FILE_NAME);
	main_loop();
	return 0;
}

/*Main user input loop*/
void main_loop(char *input)
{
	char buffer[MAX_LENGTH];
	char buffer2[MAX_LENGTH];
	char *token,*token2,*token3;
	char *bang_cmd;
	int check = 0;

	while ((printf("%s@%s:%s>> ",get_user(), get_host(), get_path()) > 0)
	       					&& (fgets(buffer, MAX_LENGTH, stdin) != NULL)) {
		
		/*Clearing stdin */
		if ((buffer[strlen(buffer) - 1] != '\n')&&(buffer[0]!='\0')) {
			clear_buffer();
		}

		if(buffer[0]=='!'){
			if(buffer[1]=='!'){
				if(history_empty()==1){
					continue;
				}
				else{
					strcpy(buffer,get_last());
				}
			}
			else if(buffer[1]=='\n'){
				strcpy(buffer2, buffer);
				add_history(buffer2);
				continue;
			}
			printf("This is a banger\n");
		}

		//Adds command to history
		strcpy(buffer2, buffer);
		add_history(buffer2);

		token = strtok(buffer, "  \n");
		//no input
		if (token == NULL) {
			continue;
		}
		//two or more inputs
		token2 = strtok(NULL,"=");
		if (token2 != NULL) {
			token3 = strtok(NULL, "\n");
			if(token3 != NULL){
				check = arg_cmd(token,token2,token3);
			}
		}
		//one input
		else{
			if((check = no_arg_cmd(token))==-1){
				break;
			};
		}
		if(check == 0){
			printf("%s@%s:%s>> Not a valid command\n",
			get_user(), get_host(), get_path());
		}

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

int arg_cmd(char *token,char *token2,char *token3){
	/*export needs valid key/value */
	if (strcmp(token, "export") == 0) {
		parse(token2, token3);
		return 1;
	}
	else return 0;
}

int no_arg_cmd(char *token){
	/*env needs only env as input */
	if (strcmp(token, "env") == 0) {
		print_var();
		return 1;
	}
	/*history needs only history as input */
	else if (strcmp(token, "history") == 0) {
		history();
		return 1;
	}
	/*exit need exit/quit as input */
	else if (strcmp(token, "exit") == 0 || strcmp(token, "quit") == 0) {
		write_env(FILE_NAME);
		destroy_env();
		destroy_history();
		return -1;	
	}
	return 0;
}