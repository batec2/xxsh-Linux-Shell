#include "xxsh.h"

#define MAX_LENGTH 256

int main(void)
{
	init_env_vars();
	init_list();
	main_loop();
	return 0;
}

/**
 * Prints out the prompt line
 */
void prompt()
{
	printf("\033[34m%s@%s:%s>>\033[0m ", get_user(), get_host(), get_env("PWD"));
}

/**
 * Redraws the prompt
 */
void reprompt()
{
	printf("\r\033[K");
	prompt();
}

/**
 * Gets input using raw mode from stdin
 * Using raw mode allows the shell to act on special inputs such as arrow
 * keys without having to wait for an enter.
 * @return the buffer with collected input
 */
char *get_input()
{
	static char buffer[MAX_LENGTH];
	int space= MAX_LENGTH;
	char c;
	space = MAX_LENGTH;
	// read in input and check for special characters like arrow keys
	struct termios tty;
	tcgetattr(STDIN_FILENO, &tty);
	// Put terminal into raw mode so that input gets sent to our shell
	// as soon as it is typed. This allows instant processing of arrows.
	tty.c_lflag &= ~(ECHO | ICANON);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &tty);
	while(space && (c = getchar()) != '\n' && c != EOF)	
	{
		// special characters
		if (c == '\033')
		{
			getchar();
			char *cmd = NULL;
			switch(getchar())
			{
				// up arrow
				case 'A':
					// Redraw tty input
					if(!(cmd = scroll_up()))
						continue;
					reprompt();
					printf("%s", cmd);
					// Update buffer
					strncpy(buffer, cmd, MAX_LENGTH);
					space = MAX_LENGTH - strlen(cmd);
					break;
				// down arrow
				case 'B':
					// Redraw tty input
					if(!(cmd = scroll_down()))
					{
						reprompt();
						buffer[0] = '\0';
						space = MAX_LENGTH;
						continue;
					}
					reprompt();
					printf("%s", cmd);
					// Update buffer
					strncpy(buffer, cmd, MAX_LENGTH);
					space = MAX_LENGTH - strlen(cmd);
					break;
				default:
					printf("Unknown special character entered\n");
					prompt();
			}
		}
		// backspace
		else if (c == 127)
		{
			if ((MAX_LENGTH - space) > 0)
			{
				buffer[MAX_LENGTH - space-1] = '\0';
				space++;
				// redraw updated line using ANSI escape sequences for moving 
				// the cursor backwards.
				// https://tldp.org/HOWTO/Bash-Prompt-HOWTO/x361.html
				printf("\033[1D \033[1D");
			}
		}
		else
		{
			buffer[MAX_LENGTH - space] = c;
			space--;
			printf("%c",c);
		}
	}
	buffer[MAX_LENGTH - space] = '\0';
	printf("\n");
	// TODO: Exit raw mode
	return buffer;
}

/*Main user input loop*/
void main_loop()
{
	command *cmd_args = malloc(sizeof(command));
	char *buffer;
	char buffer2[MAX_LENGTH];
	char *token;
	int check = 0;
	prompt();
	int status = 1;
	struct termios old;
	tcgetattr(STDIN_FILENO, &old);
	while (status) {
		buffer = get_input();
		//no input
		if (buffer[0] == '\0') {
			prompt();
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
					printf("Command not found\n");
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
			tcsetattr(STDIN_FILENO, TCSAFLUSH, &old);
			exit(EXIT_SUCCESS);
		};

		if (check == 0) {
			printf("Not a valid command\n");
		}
		free_command(cmd_args);

	prompt();
	}
	printf("\n");
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
 * Redirects stdin from a file
 * @param file to get stdin from.
 * @return the backed up stdin fd.
 */
int redirect_stdin(char *file)
{
	int fd = open(file, O_RDONLY);
	// back up stdin file descriptor
	int backup_fd = dup(STDIN_FILENO);
	// Closes STDIN_FILENO (0) and then creates a new file descriptor
	// with number = STDIN_FILENO 0). Since reading reads input from
	// stdin, it will now read from the duplicated file descriptor
	// which actually points to the file.
	if ((dup2(fd, STDIN_FILENO)) == -1) {
		printf("Error while opening input file descriptor\n");
		return -1;
	}
	close(fd);
	return backup_fd;
}

/**
 * Redirects stdout to a file
 * @param file to redirect output to.
 * @return the backed up stdout fd.
 */
int redirect_stdout(char *file)
{
	int fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0774);
	// back up stdout file descriptor
	int backup_fd = dup(STDOUT_FILENO);
	// Closes STDOUT_FILENO (1) and then creates a new file descriptor
	// with number = STDOUT_FILENO 1). Since printf writes output to
	// stdout, it will now write to the duplicated file descriptor
	// which actually points to the output file.
	if ((dup2(fd, STDOUT_FILENO)) == -1) {
		printf("Error while opening file descriptor\n");
		return -1;
	}
	close(fd);
	return backup_fd;
}

/**
 * Checks and sets up redirection for the command
 * Looks for redirection symbols in the arg string. Sets up any that are
 * found. Updates the command object to remove the redirection arguments.
 * @param cmd command to check
 * @return an array containing the file descriptors for stdout, stdout or
 * 0 if no redirection and NULL on error.
 */
int *check_redirects(command *cmd)
{
	static int backup_fds[2];
	// Search for output redirection in cmd string
	for (int i = 0; i < cmd->size; i++) {
		// Looks for redirection symbol and a following string
		// stdin
		if (cmd->args_list[i] &&
		    (strcmp(cmd->args_list[i], "<") == 0) &&
		    cmd->args_list[i + 1]) {
			if ((backup_fds[0] =
			     redirect_stdin(cmd->args_list[i + 1])) == -1)
				return NULL;
			// Trim off the last two command arguments
			remove_args(cmd, i, 2);
			// roll i back by one since we removed two entries
			i--;
		}
		// stdout
		if (cmd->args_list[i] &&
		    (strcmp(cmd->args_list[i], ">") == 0) &&
		    cmd->args_list[i + 1]) {
			if ((backup_fds[1] =
			     redirect_stdout(cmd->args_list[i + 1])) == -1)
				return NULL;
			// Trim off the last two command arguments
			remove_args(cmd, i, 2);
			// roll i back by one since we removed two entries
			i--;
		}
	}
	return backup_fds;
}

/**
 * Checks if stdout was redirected and reverts it
 * @param: backup_fds the backup of the stdout and stdin fds or 0 if no
 * redirection. index 0 is stdin, index 1 is stdout.
 */
void revert_redirects(int *backup_fds)
{
	// revert stdin
	if (backup_fds[0]) {
		dup2(backup_fds[0], STDIN_FILENO);
	}
	// revert stdout
	if (backup_fds[1]) {
		fflush(stdout);
		// Switch FD 1 back to stdout
		dup2(backup_fds[1], STDOUT_FILENO);
	}
}

/*gets cmd lists and runs commands*/
int arg_cmd(command *cmd)
{
	int status = 1;
	int *backup_fds = check_redirects(cmd);
	/*checks for pipe */
	if (is_pipe(cmd->args_list) != -1) {
		status = piping(cmd->args_list);
	}
	/*export needs valid key/value */
	else if (strcmp(cmd->args_list[0], "export") == 0 && cmd->size == 3) {
		parse(cmd->args_list[1]);
	}
	/*env needs only env as input */
	else if (strcmp(cmd->args_list[0], "env") == 0 && cmd->size == 2) {
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
	else if (strcmp(cmd->args_list[0], "pwd") == 0 && cmd->size == 2) {
		printf("%s\n", get_path());
	}
	else if (strcmp(cmd->args_list[0], "cd") == 0 && cmd->size == 2) {
		printf("%s\n", get_path());
	}
	/*checks if command exists in bin */
	else {
		status = run_cmd(cmd->args_list);
	}
	revert_redirects(backup_fds);
	return status;
}

/**
 * command and parses flags
*/
void read_flags(char *input, command *cmd)
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
	flag_list[counter] = NULL;	//adds null
	counter++;

	cmd->args_list = flag_list;
	cmd->size = counter;
}

/**
 * Removes the items from the list of command arguments
 * @param cmd struct holding list of command arguments
 * @param pos position to start removing 
 * @param count number of items to remove
 */
void remove_args(command *cmd, int pos, int count)
{
	// deallocate items
	for (int i = pos; i < pos + count; i++) {
		if (cmd->args_list[i]) {
			free(cmd->args_list[i]);
			cmd->args_list[i] = NULL;
		}
	}
	// shift remaining items
	while (cmd->args_list[pos + count]) {
		cmd->args_list[pos] = cmd->args_list[pos + count];
		pos++;
	}
	// nullify remaining items since they've already been copied
	while (cmd->args_list[pos]) {
		cmd->args_list[pos] = NULL;
		pos++;
	}
	// update size
	cmd->size -= count;
}

/*frees memory for the cmd struct*/
void free_command(command *cmd)
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
int is_pipe(char **args)
{
	int i = 0;
	while (args[i] != NULL) {
		//if there is a pipe and it is not the last item
		if (strcmp(args[i], "|") == 0 && (args[i + 1] != NULL)) {
			return i;
		}
		i++;
	}
	return -1;
}
