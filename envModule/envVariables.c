#include "envVariables.h"

PRIVATE HashTable *table = NULL;
//initiates the table
void initEnvVars(){
    table = createTable();
    addEntry(table,"CC","Default");
    addEntry(table,"EDITOR","Default");
    addEntry(table,"HOME","Default");
    addEntry(table,"OLDPWD","Default");
    addEntry(table,"HOST","Default");
    addEntry(table,"PATH","Default");
    addEntry(table,"PWD","Default");
    addEntry(table,"SHELL","Default");
    addEntry(table,"HISTSIZE","5");
    addEntry(table,"USER","Default");
}
//prints all values in the table
void printVar(){
    printEntrys(table);
}
//gets the current value of USER
char *getUser(){
    return getEntry(table,"USER");
}
//gets the current value of HOST
char *getHost(){
    return getEntry(table,"HOST");
}
//gets the current value of PATH
char *getPath(){
    return getEntry(table,"PATH");
}
//gets the value of the key from the table
char *getEnv(char *key){
    return getEntry(table,key);
}
//checks if key exists in the tables
int checkVar(char *key){
    return findEntry(table,key);
}
//Sets the value of a env variable
void setVar(char *key,char *value){
    setEntry(table,key,value);
}
//frees all memory associated with the table
void destroyEnv(){
    destroyTable(table);
}