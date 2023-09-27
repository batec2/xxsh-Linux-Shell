#include "envVariables.h"

PRIVATE HashTable *table = NULL;

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

void printVar(){
    printEntrys(table);
}

char *getUser(){
    return getEntry(table,"USER");
}

char *getHost(){
    return getEntry(table,"HOST");
}

char *getPath(){
    return getEntry(table,"PATH");
}

char *getEnv(char *key){
    return getEntry(table,key);
}

int checkVar(char *key){
    return findEntry(table,key);
}

void setVar(char *key,char *value){
    setEntry(table,key,value);
}