#include "xxsh.h"

#define MAX_LENGTH 256

int main(void)
{
	init_env_vars();
	init_list();
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

	while ((printf("%s@%s:%s>> ", get_user(), get_host(), get_env("PWD")) > 0)
	       && (fgets(buffer, MAX_LENGTH, stdin) != NULL)) {

		/*Clearing stdin */
		if ((buffer[strlen(buffer) - 1] != '\n') && (buffer[0] != '\0')) {
			clear_buffer();
		} else {
			buffer[strlen(buffer) - 1] = '\0';	//removes \n
		}
		//no input
		if (buffer[0] == '\0') {
			continue;
		}

		/*bang operator !! for last command ! for last matching after the bang */
		if (buffer[0] == '!') {
			if (buffer[1] == '!') {
				if (history_empty() == 1) {
					continue;
				} else {
					strcpy(buffer, get_last());
				}
			} else if (buffer[1] == '\0') {
				strcpy(buffer2, buffer);
				add_history(buffer2);
				continue;
			} else {
				token = get_history(buffer + 1);
				//mprintf("")
				if (token == NULL) {
					continue;
				}
				strcpy(buffer, token);
			}
		}
		//Adds command to history
		strcpy(buffer2, buffer);
		add_history(buffer2);

		read_flags(buffer, cmd_args);

		if ((check = arg_cmd(cmd_args)) == -1) {
			break;
		};

		if (check == 0) {
			printf("Not a valid command\n");
		}
		free_command(cmd_args);

	}
}

/*Parses the commands for export*/
void parse(char *args)
{
	char *key, *value;
	key = strtok(args, "=");
	value = strtok(NULL, "");
	if (value == NULL) {
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

/*Clears stdin*/
void clear_buffer()
{
	char c = ' ';
	while ((c = getchar() != '\n' && c != EOF)) {
	}
}

/**
 * Checks and sets up output redirection
 * Looks for redirection symbols in the arg string. Sets up any that are
 * found. Updates the command object to remove the redirection arguments.
 * @param cmd command to check
 * @return the file descriptor for stdout, 0 if no redirection and -1 on error.
 */
int check_output_redir(command * cmd)
{
    // Search for output redirection in cmd string
    for (int i = 0; i < cmd->size; i++)
    {
        // Looks for redirection symbol and a following string
        if (cmd->args_list[i] &&
            (strcmp(cmd->args_list[i], ">") == 0) &&
            cmd->args_list[i+1])
        { 
            printf("Got a redirect!\n");
            int fd = open(cmd->args_list[i+1],
                          O_CREAT | O_WRONLY | O_TRUNC,
                          0774);
            // back up stdout file descriptor
            int stdout_backup = dup(STDOUT_FILENO);
            // Closes STDOUT_FILENO (1) and then creates a new file descriptor
            // with number = STDOUT_FILENO 1). Since printf writes output to
            // stdout, it will now write to the duplicated file descriptor
            // which actually points to the output file.
            if ((dup2(fd, STDOUT_FILENO)) == -1)
            {
                printf("Error while opening file descriptor\n");
                return -1;
            }
            close(fd);
            // Trim off the last two command arguments
            trim_command(cmd, i);
            return stdout_backup;
        }
    }
    return 0;
}

/**
 * Checks if stdout was redirected and reverts it
 * @param: stdout_backup the backup of the fd or 0 if no redirection
 */
void revert_stdout(int stdout_backup)
{
    if (!stdout_backup)
        return;
    fflush(stdout);
    // Switch FD 1 back to stdout
    dup2(stdout_backup, STDOUT_FILENO);
}

/*gets cmd lists and runs commands*/
int arg_cmd(command * cmd)
{
	/*checks for pipe*/
	if(is_pipe(cmd->args_list)!=-1){
		return piping(cmd->args_list);
	}

    // Check for redirection
    int stdout_backup = check_output_redir(cmd);
    int status = 1;
	/*export needs valid key/value */
	if (strcmp(cmd->args_list[0], "export") == 0 && cmd->size == 3) {
		parse(cmd->args_list[1]);
	}

	/*env needs only env as input */
	if (strcmp(cmd->args_list[0], "env") == 0 && cmd->size == 2) {
		print_var();
	}
	/*history needs only history as input */
	else if (strcmp(cmd->args_list[0], "history") == 0 && cmd->size == 2) {
		history();
	}
	/*exit need exit/quit as input */
	else if ((strcmp(cmd->args_list[0], "exit") == 0 ||
		  strcmp(cmd->args_list[0], "quit") == 0) && cmd->size == 2) {
		write_env(FILE_NAME);
		destroy_env();
		destroy_history();
		free_command(cmd);
		free(cmd);
		status = -1;
	}
	/*checks if command exists in bin */
	else {
		status = run_cmd(cmd->args_list);
	}
    revert_stdout(stdout_backup);
	return status;
}

/**
 * command and parses flags
*/
void read_flags(char *input, command * cmd)
{
	char **flag_list = malloc(sizeof(char *));
	char *token;
	int counter = 0;
	token = strtok(input, " ");
	do {
		if (counter != 0) {
			flag_list = (char **)realloc(flag_list,
						     (sizeof(char *) *
						      (counter + 1)));
		}
		flag_list[(counter)] = malloc(strlen(token) + 1);
		strcpy(flag_list[(counter)], token);
		counter++;
	} while ((token = strtok(NULL, " ")) != NULL);

	flag_list =
	    (char **)realloc(flag_list, (sizeof(char *) * (counter + 1)));
	flag_list[counter] = NULL;//adds null
	counter++;

	cmd->args_list = flag_list;
	cmd->size = counter;
}

/**
 * trims the list of command arguments
 * @param cmd struct holding list of command arguments
 * @param pos position to start trim from
 */
void trim_command(command * cmd, int pos)
{
    while(cmd->args_list[pos])
    {
        free(cmd->args_list[pos]);
		cmd->args_list[pos] = NULL;
        cmd->size--;
        pos++;
	}
}

/*frees memory for the cmd struct*/
void free_command(command * cmd)
{
	for (int i = 0; i < cmd->size; i++) {
		if (cmd->args_list[i] != NULL) {
			free(cmd->args_list[i]);
		}
		cmd->args_list[i] = NULL;
	}
	free(cmd->args_list);
	cmd->args_list = NULL;
}

/*checks if there is pipe operator*/
int is_pipe(char **args){
	int i =0;
	while(args[i] != NULL){
		//if there is a pipe and it is not the last item
		if(strcmp(args[i],"|")==0 && (args[i+1]!=NULL)){
			return i;
		}
		i++;
	}
	return -1;
}
