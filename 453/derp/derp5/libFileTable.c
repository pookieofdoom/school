#include "libFileTable.h"

descentry *table;
int table_size = 0;
int table_entries = 0;
int cur_index = 0;

int makeTableEntry(int in_loc) {
  descentry entry;
  if (table_entries == table_size) {
    if (table_size == 0) {
      table = (descentry *)calloc(5, sizeof(descentry));
      table_size = 5;
    }
    else {
      table = (descentry *)realloc(table, table_size * 2 * sizeof(descentry));
      table_size *= 2;
    }
  }
  entry.FD = cur_index;
  entry.inode_addr = in_loc;
  entry.fptr = 0;
  memcpy(table + table_entries, &entry, sizeof(descentry));
  cur_index++;
  table_entries++;
  return cur_index - 1;
}

int isFileOpen(int FD) {
  int ind;
  for(ind = 0; ind < table_entries; ind++)
    if(table[ind].FD == FD)
      return 1;
  return -1;
}

int getInodeAddress(int FD) {
  int ind;
  for(ind = 0; ind < table_entries; ind++)
    if(table[ind].FD == FD)
      return table[ind].inode_addr;
  return -1;
}

int getFileDescriptor(unsigned char inode_addr) {
  int ind;
  for(ind = 0; ind < table_entries; ind++)
    if(table[ind].inode_addr == inode_addr)
      return table[ind].FD;
  return -1;
}

int getFilePointer(int FD) {
  int ind;
  for(ind = 0; ind < table_entries; ind++)
    if(table[ind].FD == FD)
      return table[ind].fptr;
  return -1;
}

int setFilePointer(int FD, int fp) {
  int ind;
  for(ind = 0; ind < table_entries; ind++)
    if(table[ind].FD == FD) {
      table[ind].fptr = fp;
      return 0;
    }
  return -1;
}

int removeTableEntry(int FD) {
  int ind;
  for(ind = 0; ind < table_entries; ind++) {
    if(table[ind].FD == FD)
      break;
  }
  if (ind == table_entries)
    return FILE_NOT_OPEN;

  for(; ind < table_entries - 1; ind++) {
    memcpy(&table[ind], &table[ind+1], sizeof(descentry));
  }
  table_entries--;
  return 0;
}

void clearTable() {
  if(table != NULL)
    free(table);
  table = NULL;
  table_size = 0;
  table_entries = 0;
  cur_index = 0;
}
