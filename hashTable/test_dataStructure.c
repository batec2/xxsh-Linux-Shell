#include "dataStructure.h"

int main()
{
	HashTable *table = createTable();
	addEntry(table, "EntryKey1", "EntryValue1");
	addEntry(table, "EntryKey1", "EntryValue110");
	addEntry(table, "EntryKey2", "EntryValue2");
	addEntry(table, "EntryKey3", "EntryValue3");
	printEntrys(table);
	printf("---Current Load:%.2f---%i\n",
	       ((float)(table->items + table->tombstones) / table->size),
	       (table->items / table->size));
	addEntry(table, "EntryKey4", "EntryValue4");
	addEntry(table, "EntryKey5", "EntryValue5");
	printEntrys(table);
	printf("---Current Load:%.2f---%i\n",
	       ((float)(table->items + table->tombstones) / table->size),
	       (table->items / table->size));
	printf("REMOVE EntryKey1\n");
	removeEntry(table, "EntryKey1");
	removeEntry(table, "EntryKey1");
	printf("Get EntryKey1: %s\n", getEntry(table, "EntryKey1"));
	printf("Set EntryKey2, value to CHANGED\n");
	setEntry(table, "EntryKey2", "CHANGED");
	printf("Get EntryKey2: %s\n", getEntry(table, "EntryKey2"));
	printEntry(table, "EntryKey2");
	printEntrys(table);
	destroyTable(table);
	return 0;
}