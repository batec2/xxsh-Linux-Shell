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
	command *cmd_args = malloc(sizeof(command));
	char buffer[MAX_LENGTH];
	char buffer2[MAX_LENGTH];
	char *token;
	int check = 0;

	while ((printf("%s@%s:%s>> ",get_user(), get_host(), get_path()) > 0)
	       					&& (fgets(buffer, MAX_LENGTH, stdin) != NULL)) {
	
		/*Clearing stdin */
		if ((buffer[strlen(buffer) - 1] != '\n')&&(buffer[0]!='\0')) {
			clear_buffer();
		}
		else{
			buffer[strlen(buffer) - 1] = '\0';//removes \n
		}
		//no input
		if (buffer[0] == '\0') {
			continue;
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
			else if(buffer[1]=='\0'){
				strcpy(buffer2, buffer);
				add_history(buffer2);
				continue;
			}
			token = get_history(strtok(buffer+1,"\0"));
			if(token==NULL){
				continue;
			}
			strcpy(buffer,token);
		}
		
		

		//Adds command to history
		strcpy(buffer2, buffer);
		add_history(buffer2);

		read_flags(buffer,cmd_args);

		if((check = arg_cmd(cmd_args))==-1){
			break;
		};
		
		if(check == 0){
			printf("%s@%s:%s>> Not a valid command\n",
			get_user(), get_host(), get_path());
		}
		free_command(cmd_args);

	}
}


void parse(char *args)
{
	char *key,*value;
	key = strtok(args,"=");
	value = strtok(NULL,"");
	if(value ==NULL){
		return;
	}
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

int arg_cmd(command *cmd){
	/*export needs valid key/value */
	if (strcmp(cmd->args_list[0], "export") == 0 &&
			cmd->size==2) {
		parse(cmd->args_list[1]);
		return 1;
	}

	/*env needs only env as input */
	if (strcmp(cmd->args_list[0], "env") == 0 &&
			cmd->size==1) {
		print_var();
		return 1;
	}
	/*history needs only history as input */
	else if (strcmp(cmd->args_list[0], "history") == 0 &&
			cmd->size==1) {
		history();
		return 1;
	}
	/*exit need exit/quit as input */
	else if ((strcmp(cmd->args_list[0], "exit") == 0 || 
			strcmp(cmd->args_list[0], "quit") == 0) && cmd->size==1) {
		write_env(FILE_NAME);
		destroy_env();
		destroy_history();
		free_command(cmd);
		free(cmd);
		return -1;	
	}
	else{
		/*PUT BINARY HERE*/
	}
	return 0;
}

/**
 * command and parses flags
*/
void read_flags(char *input,command *cmd){
	char **flag_list = malloc(sizeof(char *));
	char *token;
	int counter = 0;
	token = strtok(input, " ");
	do {
		if(counter != 0){
			flag_list = (char **)realloc(flag_list,
						(sizeof(char *)*(counter+1)));
		}
		flag_list[(counter)] = malloc(strlen(token)+1);
		strcpy(flag_list[(counter)],token);
		counter++;
	} while ((token = strtok(NULL, " "))!=NULL);
	cmd->args_list = flag_list;
	cmd->size = counter;
}

void free_command(command *cmd){
	for(int i = 0;i<cmd->size;i++){
		free(cmd->args_list[i]);
		cmd->args_list[i]=NULL;
	}
	free(cmd->args_list);
	cmd->args_list = NULL;
}