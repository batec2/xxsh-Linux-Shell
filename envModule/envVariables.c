#include "envVariables.h"

PRIVATE HashTable *table = NULL;
PRIVATE char source_dir[255];
//initiates the table
void init_env_vars()
{
	// Get the current path when the program is started.
	// This is used for reading in system and user variables. Also
	// used on program exit for writing user variables.
	getcwd(source_dir, 253);
	strncat(source_dir, "/", 2);
	table = create_table();

	read_env();
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
 * Set the current working directory and PWD and OLDPWD env variables
 * @param path string representing the path to set as the current working
 * directory.
 * @return 0 if successful, else -1
 */
int change_directory(char *path)
{
	if (chdir(path))
	{
		printf("Unable to change directory to: %s\n", path);
		return -1;
	}
	char *pwd = get_env("PWD");
	if (pwd != NULL)
		set_var("OLDPWD", pwd);
	else
		set_var("OLDPWD", path);
	set_var("PWD", path);
	return 0;
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
void write_env()
{
	char *config = malloc(sizeof(source_dir) + sizeof(USER_CONFIG_FILE));
	strcpy(config, source_dir);
	strcat(config, USER_CONFIG_FILE);
	FILE *out_file = open_file(config, "w");
	free(config);
	print_entrys(table, out_file);
	fclose(out_file);
}

/**
 * Takes env variables from file and sets them in hashmap
 *
 * Order of reading:
 * 1) Variables are loaded in from the system default configuration file
 * 2) User specific information is retrieved from the /etc/passwd entry
 * 3) The user config file is read if it exists.
 * 4) System specific environment variables such as the hostname are
 * retrieved from the system if they aren't found in the user config file.
*/
void read_env()
{
	// Load in system config file
	char *sys_config = malloc(sizeof(source_dir) + sizeof(SYS_CONFIG_FILE));
	strcpy(sys_config, source_dir);
	strcat(sys_config, SYS_CONFIG_FILE);
	read_in_config(sys_config);
	free(sys_config);

	// Get the user passwd entry information
	if (!get_user_info(getuid(), table))
		printf("WARNING: Failed to look up user information.\n");

	// Load in user config file
	char *user_config = malloc(sizeof(source_dir) + sizeof(USER_CONFIG_FILE));
	strcpy(user_config, source_dir);
	strcat(user_config, USER_CONFIG_FILE);
	read_in_config(user_config);
	free(user_config);
	
	// Check for any missing system-specific env variables and attempt to 
	// read them in
	if (get_env("HOST") == NULL)
	{
		get_hostname();
	}
	
}

/**
 * Reads in the hostname for the system and stores it in the HOST env var
 */
void get_hostname()
{
	FILE *hostname = open_file("/proc/sys/kernel/hostname", "r");
	char data[255];
	fgets(data, sizeof(data), hostname);
	strtok(data, "\n");
	set_var("HOST", data);
}

/**
 * Reads in environment variables from a config file
 *
 * @param config the path to the config file
 */
void read_in_config(char *config)
{
	char buffer[MAX_COUNT];
	char *token, *token2;
	FILE *file = open_file(config, "r");
	if (file != NULL)
	{
		while (fgets(buffer, MAX_COUNT, file) != NULL) {
			token = strtok(buffer, ",\n");
			token2 = strtok(NULL, "\n");
			set_var(token, token2);
		}
		fclose(file);
	}
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
				set_entry(table, "USER", substring);
				break;
			case 6:
				set_entry(table, "HOME", substring);
				// Update current working directory
				change_directory(substring);
				break;
			case 7:
				strtok(substring, "\n");
				set_entry(table, "SHELL", substring);
				break;
		}
		substring = strtok(NULL, ":");
	}
	return 1;
}
