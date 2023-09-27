#include "envVariables.h"

HashTable *initEnvVars(){
    HashTable *table = createTable();
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
    return table;
}

void printVar(HashTable *table){
    printEntrys(table);
}

char *getUser(HashTable *table){
    return getEntry(table,"EDITOR");
}

char *getHost(HashTable *table){
    return getEntry(table,"HOST");
}

char *getPath(HashTable *table){
    return getEntry(table,"PATH");
}

int checkVar(HashTable *table,char *key){
    return findEntry(table,key);
}

void setVar(HashTable *table,char *key,char *value){
    setEntry(table,key,value);
}