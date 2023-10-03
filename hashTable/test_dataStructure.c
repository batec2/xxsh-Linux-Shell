#include "dataStructure.h"

int main()
{
	HashTable *table = create_table();
	add_entry(table, "EntryKey1", "EntryValue1");
	add_entry(table, "EntryKey1", "EntryValue110");
	add_entry(table, "EntryKey2", "EntryValue2");
	add_entry(table, "EntryKey3", "EntryValue3");
	print_entrys(table);
	printf("---Current Load:%.2f---%i\n",
	       ((float)(table->items + table->tombstones) / table->size),
	       (table->items / table->size));
	add_entry(table, "EntryKey4", "EntryValue4");
	add_entry(table, "EntryKey5", "EntryValue5");
	print_entrys(table);
	printf("---Current Load:%.2f---%i\n",
	       ((float)(table->items + table->tombstones) / table->size),
	       (table->items / table->size));
	printf("REMOVE EntryKey1\n");
	remove_entry(table, "EntryKey1");
	remove_entry(table, "EntryKey1");
	printf("Get EntryKey1: %s\n", get_entry(table, "EntryKey1"));
	printf("Set EntryKey2, value to CHANGED\n");
	set_entry(table, "EntryKey2", "CHANGED");
	printf("Get EntryKey2: %s\n", get_entry(table, "EntryKey2"));
	print_entry(table, "EntryKey2");
	print_entrys(table);
	destroy_table(table);
	return 0;
}
