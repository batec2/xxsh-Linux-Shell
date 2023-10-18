#include "envVariables.h"

PRIVATE HashTable *table = NULL;
//initiates the table
void init_env_vars()
{
	table = create_table();
	add_entry(table, "CC", "Default");
	add_entry(table, "EDITOR", "Default");
	add_entry(table, "HOME", "Default");
	add_entry(table, "OLDPWD", "Default");
	add_entry(table, "HOST", "Default");
	add_entry(table, "PATH", "Default");
	add_entry(table, "PWD", "Default");
	add_entry(table, "SHELL", "Default");
	add_entry(table, "HISTSIZE", "5");
	add_entry(table, "USER", "Default");
	check_env(FILE_N);
	read_env(FILE_N);
}

//prints all values in the table
void print_var()
{
	print_entrys(table,NULL);
}

void write_var(FILE *file)
{
	print_entrys(table,file);
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

//frees all memory associated with the table
void destroy_env()
{
	destroy_table(table);
}

//writes env vars to file
void write_env(char *file_name){
	FILE *out_file = open_file(file_name,"w");
	print_entrys(table,out_file);
	fclose(out_file);
}

/**
 * Checks if file exists, if it doesnt, creates the file if and writes default
 * environment variables
*/
void check_env(char *file_name){
    FILE *file = open_file(file_name,"r");
    if(file==NULL){
        write_env(file_name);
    }
    else{
        fclose(file);
    }
}

/**
 * Takes env variables from file and sets them in hashmap
*/
void read_env(char *file_name){
	char buffer[MAX_COUNT];
	char *token,*token2;
	FILE *file = open_file(file_name,"r");
	while(fgets(buffer,MAX_COUNT,file)!=NULL){
		token = strtok(buffer,",\n");
		token2 = strtok(NULL,"\n");
		set_var(token,token2);
	}
	fclose(file);
}

