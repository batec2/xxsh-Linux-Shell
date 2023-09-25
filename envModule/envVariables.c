#include "envVariables.h"

int main(void){
    return 0;
}
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
    addEntry(table,"HISTSIZE","Default");
    return table;
}


