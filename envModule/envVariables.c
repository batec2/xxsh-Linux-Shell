#include "envVariables.h"

PRIVATE HashTable *table = NULL;
//initiates the table
void init_env_vars()
{
	table = create_table();
	// Get the user information
	if (!get_user_info(getuid(), table))
		printf("WARNING: Failed to look up user information.\n");
	// Only set defaults if env variable isn't set
	check_set_var("CC", "Default");
	check_set_var("EDITOR", "Default");
	check_set_var("HOME", "Default");
	check_set_var("OLDPWD", "Default");
	check_set_var("HOST", "Default");
	check_set_var("PATH", "Default");
	check_set_var("PWD", "Default");
	check_set_var("SHELL", "Default");
	check_set_var("HISTSIZE", "5");
	check_set_var("USER", "Default");

	check_env(FILE_N);
	read_env(FILE_N);
}

//prints all values in the table
void print_var()
{
	print_entrys(table, NULL);
}

void write_var(FILE *file)
{
	print_entrys(table, file);
}

//gets the current value of USER
char *get_user()
{
	return get_entry(table, "USER");
}

//gets the current value of HOST
char *get_host()
{
	return get_entry(table, "HOST");
}

//gets the current value of PATH
char *get_path()
{
	return get_entry(table, "PATH");
}

//gets the value of the key from the table
char *get_env(char *key)
{
	return get_entry(table, key);
}

//checks if key exists in the tables
int check_var(char *key)
{
	return find_entry(table, key);
}

//Sets the value of a env variable
void set_var(char *key, char *value)
{
	set_entry(table, key, value);
}

/** 
 * Only sets the environment variable if it isn't already set.
 * @param String name of environment variable
 * @param String value of environment variable
 */
void check_set_var(char *key, char *value)
{
	if(!get_entry(table, key))
		add_entry(table, key, value);
}

//frees all memory associated with the table
void destroy_env()
{
	destroy_table(table);
}

//writes env vars to file
void write_env(char *file_name)
{
	FILE *out_file = open_file(file_name, "w");
	print_entrys(table, out_file);
	fclose(out_file);
}

/**
 * Checks if file exists, if it doesnt, creates the file if and writes default
 * environment variables
*/
void check_env(char *file_name)
{
	FILE *file = open_file(file_name, "r");
	if (file == NULL) {
		write_env(file_name);
	} else {
		fclose(file);
	}
}

/**
 * Takes env variables from file and sets them in hashmap
*/
void read_env(char *file_name)
{
	char buffer[MAX_COUNT];
	char *token, *token2;
	FILE *file = open_file(file_name, "r");
	while (fgets(buffer, MAX_COUNT, file) != NULL) {
		token = strtok(buffer, ",\n");
		token2 = strtok(NULL, "\n");
		set_var(token, token2);
	}
	fclose(file);
}

/**
 * Finds a user entry in etc/passwd
 * @param: id the user ID
 * @returns: 1 on success, 0 on failure
 */
int get_user_info(int uid, HashTable *table)
{
	char user_id[20];
	snprintf(user_id, 20, "%d", uid);
	char data[255];
	FILE *file = open_file("/etc/passwd", "r");
	int found = 0;
	while (fgets(data, sizeof(data), file) != NULL)
	{
		if (strstr(data, user_id) != NULL)
		{
			found = 1;
			break;
		}
	}
	fclose(file);
	if (!found)
	{
		printf("Unable to find the current user in the /etc/password file.\n");
		return 0;
	}
	// Extract information
	char *substring = strtok(data, ":");
	int count = 0;
	while (substring != NULL && ++count)
	{
		switch(count)
		{
			case 1:
				add_entry(table, "USER", substring);
				break;
			case 6:
				add_entry(table, "HOME", substring);
				add_entry(table, "PWD", substring);
				break;
			case 7:
				strtok(substring, "\n");
				add_entry(table, "SHELL", substring);
				break;
		}
		substring = strtok(NULL, ":");
	}
	return 1;
}
