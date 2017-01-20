#include <stdlib.h>
#include <stdio.h>
#include "tinyFS.h"

#define SMALL_SIZE 50
#define TWO_BLOCK_SIZE 300
#define THREE_BLOCK_SIZE 600
#define NUM_BLOCKS 40

void simpleTestSuite() {
  fileDescriptor x;
  char small_data[SMALL_SIZE];
  char temp;
  int i, status;

  for(i = 0; i < SMALL_SIZE; i++)
    small_data[i] = i;

  tfs_mkfs("testdisk", DEFAULT_DISK_SIZE);
  tfs_mount("testdisk");

  printf("\n\n~~~Single Block File Tests~~~\n");
  printf("Test #1: Open File, Write to File, Read from File\n");
  printf("- tfs_openFile should return nonnegative ... ");
  x = tfs_openFile("abc");
  printf("%s\n", x >= 0 ? "Success" : "Failed");

  printf("- tfs_writeFile should return nonnegative ... ");
  status = tfs_writeFile(x, small_data, SMALL_SIZE);
  printf("%s\n", status >= 0 ? "Success" : "Failed");


  printf("- tfs_readByte should return original data ... ");
  for(i = 0; i < SMALL_SIZE; i++) {
    if(tfs_readByte(x, &temp) != 0) {
      printf("Failed (ReadByte had an error)\n");
      break;
    }
    if(temp != small_data[i]) {
      printf("Failed (Data does not match)\n");
      break;
    }
  }
  if( i == SMALL_SIZE)
    printf("Success\n");

  printf("- tfs_readByte should return END_OF_FILE after file ... ");
  printf("%s\n", tfs_readByte(x, &temp) == END_OF_FILE ? "Success" : "Failed");

  printf("Test #2: Seek\n");
  printf("- tfs_seek should return nonnegative status ... ");
  printf("%s\n", tfs_seek(x, 20) >= 0 ? "Success" : "Failed");

  printf("- tfs_readByte should return nonnegative when ptr within file ... ");
  printf("%s\n", tfs_readByte(x, &temp) >= 0 ? "Success" : "Failed");

  printf("- byte at seek location should be same byte that was written ... ");
  printf("%s\n", temp == small_data[20] ? "Success" : "Failed");

  printf("- tfs_seek should return nonnegative status ... ");
  printf("%s\n", tfs_seek(x, 89) >= 0 ? "Success" : "Failed");

  printf("- tfs_readByte should return END_OF_FILE if ptr is past file ... ");
  printf("%s\n", tfs_readByte(x, &temp) == END_OF_FILE ? "Success" : "Failed");

  printf("Test #3: Cleanup\n");

  printf("- tfs_closeFile should return nonnegative status ... ");
  printf("%s\n", tfs_closeFile(x) >= 0 ? "Success" : "Failed");

  printf("- tfs_unmount should return nonnegative status ... ");
  printf("%s\n", tfs_unmount() >= 0 ? "Success" : "Failed");
}

void longFileTestSuite() {
  fileDescriptor x;
  char big_data[TWO_BLOCK_SIZE];
  char temp;
  int i;

  for(i = 0; i < TWO_BLOCK_SIZE; i++)
    big_data[i] = i;

  tfs_mkfs("testdisk", DEFAULT_DISK_SIZE);
  tfs_mount("testdisk");

  printf("\n\n~~~Multi-Block File Tests~~~\n");
  printf("Test #1: Open File, Write 2 blocks of data to File, Read from File\n");

  printf("- tfs_openFile should return nonnegative ... ");
  x = tfs_openFile("def");
  printf("%s\n", x >= 0 ? "Success" : "Failed");

  printf("- tfs_writeFile should return nonnegative ... ");
  printf("%s\n", tfs_writeFile(x, big_data, TWO_BLOCK_SIZE) >= 0 ? "Success" : "Failed");

  printf("- tfs_readByte should return original data ... ");
  for(i = 0; i < TWO_BLOCK_SIZE; i++) {
    if(tfs_readByte(x, &temp) != 0) {
      printf("Failed (ReadByte had an error)\n");
      break;
    }
    if(temp != big_data[i]) {
      printf("Failed (Data does not match)\n");
      break;
    }
  }
  if( i == TWO_BLOCK_SIZE)
    printf("Success\n");

  printf("Test #2: Seek\n");
  printf("- tfs_seek should return nonnegative status ... ");
  printf("%s\n", tfs_seek(x, 20) >= 0 ? "Success" : "Failed");

  printf("- tfs_readByte should return nonnegative when ptr in first block ... ");
  printf("%s\n", tfs_readByte(x, &temp) >= 0 ? "Success" : "Failed");

  printf("- byte at seek location should be same byte that was written ... ");
  printf("%s\n", temp == big_data[20] ? "Success" : "Failed");

  printf("- tfs_seek should return nonnegative status ... ");
  printf("%s\n", tfs_seek(x, TWO_BLOCK_SIZE - 2) >= 0 ? "Success" : "Failed");

  printf("- tfs_readByte should return nonnegative when ptr in second block ... ");
  printf("%s\n", tfs_readByte(x, &temp) >= 0 ? "Success" : "Failed");

  printf("- byte at seek location should be same byte that was written ... ");
  printf("%s\n", temp == big_data[TWO_BLOCK_SIZE - 2] ? "Success" : "Failed");

  printf("- tfs_seek should return nonnegative status ... ");
  printf("%s\n", tfs_seek(x, TWO_BLOCK_SIZE) >= 0 ? "Success" : "Failed");

  printf("- tfs_readByte should return END_OF_FILE if ptr is past file ... ");
  printf("%s\n", tfs_readByte(x, &temp) == END_OF_FILE ? "Success" : "Failed");

  tfs_closeFile(x);
  tfs_unmount();
}

void openAndCloseTestSuite() {
  fileDescriptor x, y;
  char big_data[TWO_BLOCK_SIZE], small_data[SMALL_SIZE];
  char temp;
  int i;

  for(i = 0; i < TWO_BLOCK_SIZE; i++)
    big_data[i] = TWO_BLOCK_SIZE - i;
  for(i = 0; i < TWO_BLOCK_SIZE; i++)
    small_data[i] = i;

  tfs_mkfs("testdisk", DEFAULT_DISK_SIZE);
  tfs_mount("testdisk");

  printf("\n\n~~~Open and Close File Tests~~~\n");
  printf("Test #1: Two Files Open\n");
  x = tfs_openFile("oc1");
  tfs_writeFile(x, small_data, SMALL_SIZE);
  y = tfs_openFile("oc2");
  tfs_writeFile(y, big_data, TWO_BLOCK_SIZE);

  printf("- should be able to access first file ... ");
  for(i = 0; i < SMALL_SIZE; i++) {
    tfs_readByte(x, &temp);
    if(temp != small_data[i])
      break;
  }
  printf("%s\n", i == SMALL_SIZE ? "Success" : "Failed");

  printf("- should be able to access second file ... ");
  for(i = 0; i < TWO_BLOCK_SIZE; i++) {
    tfs_readByte(y, &temp);
    if(temp != big_data[i])
      break;
  }
  printf("%s\n", i == TWO_BLOCK_SIZE ? "Success" : "Failed");

  printf("Test #2: Closing and Opening Same File\n");
  tfs_closeFile(x);
  printf("- readbyte should return FILE_NOT_OPEN for closed file ... ");
  printf("%s\n", tfs_readByte(x, &temp) == FILE_NOT_OPEN ? "Success" : "Failed");

  printf("- data should be preserved when reopened ... ");
  x = tfs_openFile("oc1");
  for( i = 0; i < SMALL_SIZE; i++){
    tfs_readByte(x, &temp);
    if(temp != small_data[i])
      break;
  }
  printf("%s\n", i == SMALL_SIZE ? "Success" : "Failed");

  printf("Test #3: Bad filenames\n");
  printf("- should not create file when filename is too long ... ");
  printf("%s\n", tfs_openFile("123456789") == NAME_TOO_LONG ? "Success" : "Failed");
  printf("- should not create file with name of root folder ... ");
  printf("%s\n", tfs_openFile("\\") == INVALID_NAME ? "Success" : "Failed");

  printf("Test #4: Closing non-existant file descriptor");
  printf("- should return FILE_NOT_OPEN ... ");
  printf("%s\n", tfs_closeFile(78) == FILE_NOT_OPEN ? "Success" : "Failed");

  tfs_unmount();
}

void overwriteTestSuite() {
  fileDescriptor x;
  char big_data[THREE_BLOCK_SIZE], small_data[SMALL_SIZE], small_data2[SMALL_SIZE + SMALL_SIZE];
  char temp;
  int i;
  char *bitmap;
  bitmap = (char *)calloc(NUM_BLOCKS / 8 + 1, sizeof(char));


  for(i = 0; i < THREE_BLOCK_SIZE; i++)
    big_data[i] = THREE_BLOCK_SIZE - i;
  for(i = 0; i < SMALL_SIZE; i++)
    small_data[i] = i;
  for(i = 0; i < SMALL_SIZE + SMALL_SIZE; i++)
    small_data2[i] = SMALL_SIZE + SMALL_SIZE - i + 10;

  tfs_mkfs("testdisk", DEFAULT_DISK_SIZE);
  tfs_mount("testdisk");


  printf("\n\n~~~Overwritting~~~\n");
  x = tfs_openFile("abc");

  printf("Test #1: Overwritting One-Block File Smaller\n");
  printf("- writing one block into file should return original block ...");

  tfs_writeFile(x, small_data2, SMALL_SIZE * 2);
  for(i = 0; i < SMALL_SIZE * 2; i++) {
    if(tfs_readByte(x, &temp) != 0) {
      printf("Failed (readByte failed)\n");
      break;
    }
    if(temp != small_data2[i]) {
      printf("Failed (data was not preserved)\n");
      break;
    }
  }
  if( i == SMALL_SIZE * 2)
   printf("Success\n");
  printf("- original file should be appropriate length ... ");
  printf("%s\n", tfs_readByte(x, &temp) == END_OF_FILE ? "Success" : "Failed");

   printf("- shrinking one block file should return shrinked block ...");
   tfs_writeFile(x, small_data, SMALL_SIZE);
   for (i = 0; i < SMALL_SIZE; i++) {
    if(tfs_readByte(x, &temp) != 0) {
      printf("Failed (readByte failed)\n");
      break;
    }
    if(temp != small_data[i]) {
      printf("Failed (data was not preserved)\n");
      break;
    }
   }
   if (i == SMALL_SIZE)
      printf("Success\n");

  printf("- overwritten file should be appropriate size ... ");
  printf("%s\n", tfs_readByte(x, &temp) == END_OF_FILE ? "Success" : "Failed");

  printf("- layout of free nodes should be '1223444' ... ");
  tfs_displayFragments(bitmap);
  printf("%s\n", strncmp(bitmap, "1223444", 7) == 0 ? "Success" : "Failed");

  printf("Test #2: Overwritting One-Block File Bigger\n");
  printf("- expanding one block file should return expanded block ...");
  tfs_writeFile(x, small_data2, SMALL_SIZE * 2);
  for(i = 0; i < SMALL_SIZE * 2; i++) {
    if(tfs_readByte(x, &temp) != 0) {
      printf("Failed (readByte failed)\n");
      break;
    }
    if(temp != small_data2[i]) {
      printf("Failed (data was not preserved)\n");
      break;
    }
  }
  if(i == SMALL_SIZE * 2)
    printf("Success\n");
  printf("- overwritten file should be appropriate size ... ");
  printf("%s\n", tfs_readByte(x, &temp) == END_OF_FILE ? "Success" : "Failed");
  printf("- layout of free nodes should be '1223444' ... ");
  tfs_displayFragments(bitmap);
  printf("%s\n", strncmp(bitmap, "1223444", 7) == 0 ? "Success" : "Failed");


  printf("Test #3: Overwritting One-Block to Three-Block\n");
  printf("- expanding one-block to three-block should be three-block data ...");
  tfs_writeFile(x, big_data, THREE_BLOCK_SIZE);
  for(i = 0; i < THREE_BLOCK_SIZE; i++) {
    if(tfs_readByte(x, &temp) != 0) {
      printf("Failed (readByte failed)\n");
      break;
    }
    if(temp != big_data[i]) {
      printf("Failed (data was not preserver)\n");
      break;
    }
  }
  if(i == THREE_BLOCK_SIZE)
    printf("Success\n");
  printf("- overwritten file should be appropriate length ... ");
  printf("%s\n", tfs_readByte(x, &temp) == END_OF_FILE ? "Success" : "Failed");
  printf("- layout of free nodes should be '1223334' ... ");
  tfs_displayFragments(bitmap);
  printf("%s\n", strncmp(bitmap, "1223334", 7) == 0 ? "Success" : "Failed");


  printf("Test #4: Shrinking Three-Blocks to One-Block\n");
  printf("- shrinking three-block file to one-block file should be one-block ... ");
  tfs_writeFile(x, small_data, SMALL_SIZE);
  for(i = 0; i < SMALL_SIZE; i++) {
   if(tfs_readByte(x, &temp) != 0) {
      printf("Failed (readByte failed)\n");
      break;
    }
   if(temp != small_data[i]) {
     printf("Failed (data was not preserved)\n");
     break;
   }
  }
  if (i == SMALL_SIZE)
    printf("Success\n");
  printf("- overwritten file should be only one-block in size ... ");
  printf("%s\n", tfs_readByte(x, &temp) == END_OF_FILE ? "Success" : "Failed");
  printf("- layout of free nodes should be '1224434' ... ");
  tfs_displayFragments(bitmap);
  printf("%s\n", strncmp(bitmap, "1224434", 7) == 0 ? "Success" : "Failed");
  tfs_unmount();
}

void deleteTestSuite() {
   fileDescriptor x, y;
   char big_data[THREE_BLOCK_SIZE];
   char small_data[SMALL_SIZE];
   char *name1 = "abc";
   char temp;
   char *name2 = "def";
   char *bitmap;
   char ** filenames;
   int numfiles, i;
   bitmap = (char *)calloc(NUM_BLOCKS / 8 + 1, sizeof(char));
   filenames = (char **)calloc(1, sizeof(char **));

   for(i = 0; i < THREE_BLOCK_SIZE; i++)
    big_data[i] = THREE_BLOCK_SIZE - i;

   for(i = 0; i < SMALL_SIZE; i++)
    small_data[i] = i;

   tfs_mkfs("testdisk", DEFAULT_DISK_SIZE);
   tfs_mount("testdisk");

   printf("\n\n~~~Deleting~~~\n");

   printf("Test #1 Deleting a single file\n");
   x = tfs_openFile(name1);
   tfs_writeFile(x, big_data, THREE_BLOCK_SIZE);
   printf("- Three-Block File should be marked as free ... ");

   tfs_deleteFile(x);
   tfs_displayFragments(bitmap);
   printf("%s\n", strncmp(bitmap, "1244444", 7) == 0 ? "Success" : "Failed");

   tfs_readDir(filenames, &numfiles);
   printf("- Only root folder should exist ... ");
   printf("%s\n", numfiles == 1 ? "Success" : "Failed");


   printf("- Should not be able to write to deleted file ...");
   tfs_writeFile(x, big_data, THREE_BLOCK_SIZE);

   tfs_displayFragments(bitmap);
   printf("%s\n", strncmp(bitmap, "1244444", 7) == 0 ? "Success" : "Failed");

   printf("Test #2 Deleting second file with two open\n");
   x = tfs_openFile(name1);
   tfs_writeFile(x, big_data, THREE_BLOCK_SIZE);
   y = tfs_openFile(name2);
   tfs_writeFile(y, big_data, THREE_BLOCK_SIZE);

   printf("- Second File should be marked as free ... ");
   tfs_deleteFile(y);
   tfs_displayFragments(bitmap);
   printf("%s\n", strncmp(bitmap, "1223334444", 10) == 0 ? "Success" : "Failed");

   printf("- Should not be able to write to second file ...");
   tfs_writeFile(y, big_data, THREE_BLOCK_SIZE);
   tfs_displayFragments(bitmap);
   printf("%s\n", strncmp(bitmap, "1223334444", 10) == 0 ? "Success" : "Failed");

   tfs_readDir(filenames, &numfiles);
   printf("- One file should exist ... ");
   printf("%s\n", numfiles == 2 ? "Success" : "Failed");
   printf("- now only file abc should exist ... ");
   printf("%s\n", strncmp(*filenames+9, name1, 8) == 0 ? "Success" : "Failed");

   printf("- Should be able to shrink first file ... ");
   tfs_writeFile(x, small_data, SMALL_SIZE);
   tfs_displayFragments(bitmap);
   printf("%s\n", strncmp(bitmap, "1224434", 7) == 0 ? "Success" : "Failed");

   printf("- Should be able to expand first file ...");
   tfs_writeFile(x, big_data, THREE_BLOCK_SIZE);
   tfs_displayFragments(bitmap);
   printf("%s\n", strncmp(bitmap, "1223334444", 9) == 0 ? "Success" : "Failed");

   printf("- should be able to access expanded file ...");
   for(i = 0; i < THREE_BLOCK_SIZE; i++) {
     tfs_readByte(x, &temp);
     if(temp != big_data[i])
      break;
   }
   printf("%s\n", i == THREE_BLOCK_SIZE ? "Success" : "Failed");

   printf("- delete first file, should be only root dir ... ");
   tfs_deleteFile(x);
   tfs_readDir(filenames, &numfiles);
   printf("%s\n", numfiles == 1 ? "Success" : "Failed");
   printf("- both files should be free ... ");
   tfs_displayFragments(bitmap);
   printf("%s\n", strncmp(bitmap, "1244444", 7) == 0 ? "Success" : "Failed");

   printf("Test #3 Delete first file with two open\n");
   x = tfs_openFile(name1);
   tfs_writeFile(x, big_data, THREE_BLOCK_SIZE); /*also shrinking here*/
   y = tfs_openFile(name2);
   tfs_writeFile(y, small_data, SMALL_SIZE);
   tfs_deleteFile(x);
   printf("- First File should be marked as free ... ");
   tfs_displayFragments(bitmap);
   printf("%s\n", strncmp(bitmap, "1244442344", 10) == 0 ? "Success" : "Failed");

   printf("- One file should exist ... ");
   tfs_readDir(filenames, &numfiles);
   printf("%s\n", numfiles == 2 ? "Success" : "Failed");
   printf("- now only file def should exist ... ");
   printf("%s\n", strncmp(*filenames+9, name2, 8) == 0 ? "Success" : "Failed");

   printf("- expanding file 2 should replace free blocks...");
   tfs_writeFile(y, big_data, THREE_BLOCK_SIZE);
   for(i = 0; i < THREE_BLOCK_SIZE; i++) {
     tfs_readByte(y, &temp);
     if(temp != big_data[i])
      break;
   }
   printf("%s\n", i == THREE_BLOCK_SIZE ? "Success" : "Failed");

   printf("- Deleting second file ... ");
   tfs_deleteFile(y);
   tfs_displayFragments(bitmap);
   printf("%s\n", strncmp(bitmap, "1244444", 7) == 0 ? "Success" : "Failed");

   printf("- should be 0 open files ... ");
   tfs_readDir(filenames, &numfiles);
   printf("%s\n", numfiles == 1 ? "Success" : "Failed");
   printf("- both files should be free ... ");
   tfs_displayFragments(bitmap);
   printf("%s\n", strncmp(bitmap, "1244444", 7) == 0 ? "Success" : "Failed");

   tfs_unmount();


}

void renameTestSuite() {
  char * name1 = "abc";
  char * name2 = "lmnopq";
  char small_data[SMALL_SIZE];
  char ** filenames;
  int numfiles;
  int i, status;
  char temp;
  fileDescriptor x;

  for(i = 0; i < SMALL_SIZE; i++)
    small_data[i] = i;

  filenames = (char **)calloc(1, sizeof(char **));

  tfs_mkfs("testdisk", DEFAULT_DISK_SIZE);
  tfs_mount("testdisk");

  printf("\n\n~~~Rename and Readdir~~~\n");

  printf("Test #1: Rename a single File\n");
  x = tfs_openFile(name1);
  tfs_writeFile(x, small_data, SMALL_SIZE);
  tfs_rename(x, name2);
  tfs_closeFile(x);
  printf("- should not be able to locate file by original name ... ");
  x = tfs_openFile(name1);
  printf("%s\n", tfs_readByte(x, &temp) == END_OF_FILE ? "Success" : "Failed");
  printf("- should be able to open file with new name ... ");
  x = tfs_openFile(name2);
  printf("%s\n", tfs_readByte(x, &temp) != END_OF_FILE ? "Success" : "Failed");
  tfs_closeFile(x);

  printf("Test #2: Read directory\n");
  tfs_readDir(filenames, &numfiles);
  printf("- number of files should equal 2 ... ");
  printf("%s\n", numfiles == 3 ? "Success" : "Failed");

  printf("- filenames should be returned (lmnopq and abc) ... ");
  status = strncmp(*filenames + 9, name2, 8) == 0;
  status &= strncmp(*filenames + 18, name1, 8) == 0;
  printf("%s\n", status ? "Success" : "Failed");
  free(*filenames);

  printf("Test #3: Filenames should be gone after delete\n");
  x = tfs_openFile(name2);
  tfs_deleteFile(x);
  tfs_readDir(filenames, &numfiles);
  printf("- now only one file should exist ... ");
  printf("%s\n", numfiles == 2 ? "Success" : "Failed");
  printf("- now only file abc should exist ... ");
  printf("%s\n", strncmp(*filenames+9, name1, 8) == 0 ? "Success" : "Failed");

  x = tfs_openFile(name1);
  tfs_deleteFile(x);
  tfs_readDir(filenames, &numfiles);
  printf("- no files should exist ... ");
  printf("%s\n", numfiles == 1 ? "Success" : "Failed");

  printf("Test #4: rename should fail when file not open\n");
  printf("- rename non open file should return FILE_NOT_OPEN ... ");
  printf("%s\n", tfs_rename(89, name2) == FILE_NOT_OPEN ? "Success" : "Failed");

  //free(filenames);

  tfs_unmount();
}

void timeTestSuite() {
  char * name = "abc";
  char small_data[SMALL_SIZE];
  int i;
  char temp;
  fileDescriptor x;
  fileinfo finfo;

  for(i = 0; i < SMALL_SIZE; i++)
    small_data[i] = i;

  tfs_mkfs("testdisk", DEFAULT_DISK_SIZE);
  tfs_mount("testdisk");

  printf("\n\n~~~ Timestamps ~~~\n");
  printf("Test #1 Timestamps for new file\n");
  printf("- readFileInfo should return 0 ... ");
  x = tfs_openFile(name);
  printf("%s\n", tfs_readFileInfo(x, &finfo) >= 0 ? "Success" : "Failed");
  printf("- creation, modification, and access should be equal for new file ... ");
  printf("%s\n", (finfo.access == finfo.modification) && (finfo.modification == finfo.creation) ? "Success" : "Failed");

  printf("Test #2 Timestamps for written file\n");
  sleep(1); //Wait one second to get different timestamps
  tfs_writeFile(x, small_data, SMALL_SIZE);
  printf("- access and modification time should be updated ... ");
  tfs_readFileInfo(x, &finfo);
  printf("%s\n", finfo.creation < finfo.modification && finfo.access == finfo.modification ? "Success" : "Failed");

  printf("Test #3 Timestamps for read of file\n");
  sleep(1);
  tfs_readByte(x, &temp);
  printf("- only access time should be updated when after read ... ");
  tfs_readFileInfo(x, &finfo);
  printf("%s\n", (finfo.creation < finfo.modification) & (finfo.modification < finfo.access) ? "Success" : "Failed");
  tfs_unmount();
}

void readonlyTestSuite() {
  char * name = "abc";
  char small_data[SMALL_SIZE], small_data2[SMALL_SIZE], big_data[THREE_BLOCK_SIZE];
  int i;
  char temp;
  fileDescriptor x;
  char ** filenames;
  int numfiles;
  char samp;

  samp = 121;

  filenames = (char **)calloc(1, sizeof(char **));

  for(i = 0; i < THREE_BLOCK_SIZE; i++)
    big_data[i] = THREE_BLOCK_SIZE - i;
  for(i = 0; i < SMALL_SIZE; i++)
    small_data[i] = i;
  for(i = 0; i < SMALL_SIZE; i++)
    small_data2[i] = SMALL_SIZE - i;

  tfs_mkfs("testdisk", DEFAULT_DISK_SIZE);
  tfs_mount("testdisk");

  printf("\n\n~~~ Read/Write Status and Write Byte ~~~\n");
  x = tfs_openFile(name);
  tfs_writeFile(x, small_data, SMALL_SIZE);

  printf("Test #1 Set readonly\n");
  printf("- tfs_makeRO should return 0 ... ");
  printf("%s\n", tfs_makeRO(name) >= 0 ? "Success" : "Failed");
  printf("- tfs_makeRO should return NO_SUCH_FILE if name doesn't match ... ");
  printf("%s\n", tfs_makeRO("ajkl") == NO_SUCH_FILE ? "Success" : "Failed");
  printf("Test #2 Should not write Readonly files\n");
  printf("- attempt to write readonly file should return FILE_IS_READONLY ... ");
  printf("%s\n", tfs_writeFile(x, small_data2, SMALL_SIZE) == FILE_IS_READONLY ? "Success" : "Failed");
  printf("- no data should have been written ... ");
  tfs_readByte(x, &temp);
  printf("%s\n", temp != small_data2[0] && temp == small_data[0] ? "Success" : "Failed");

  printf("Test #3 Should not delete Readonly files\n");
  printf("- attempt to delete readonly file should return FILE_IS_READONLY ... ");
  printf("%s\n", tfs_deleteFile(x) == FILE_IS_READONLY ? "Success" : "Failed");
  printf("- file shoud still exist ... ");
  tfs_readByte(x, &temp);
  printf("%s\n", temp == small_data[1] ? "Success" : "Failed");

  printf("Test #4 Should not write byte to Readonly files\n");
  printf("- attempt to writebyte to readonly file should return FILE_IS_READONLY ... ");
  printf("%s\n", tfs_writeByte(x, samp) == FILE_IS_READONLY ? "Success" : "Failed");
  printf("- byte should have been written ... ");
  tfs_seek(x, 2);
  tfs_readByte(x, &temp);
  printf("%s\n", temp == small_data[2] ? "Success" : "Failed");

  printf("Test #5 Should be able to make file R/W\n");
  tfs_makeRW(name);
  printf("- attempt to write to read/write file should work ... ");
  printf("%s\n", tfs_writeFile(x, small_data2, SMALL_SIZE) >= 0 ? "Success" : "Failed");
  printf("- data should be written ... ");
  for(i = 0; i < SMALL_SIZE; i++) {
    if(tfs_readByte(x, &temp) != 0 || temp != small_data2[i])
      break;
  }
  printf("%s\n", i == SMALL_SIZE ? "Success" : "Failed");
  printf("- write byte should also work ... ");
  tfs_seek(x, 3);
  tfs_writeByte(x,samp);
  tfs_seek(x, 3);
  tfs_readByte(x, &temp);
  printf("%s\n", temp == samp ? "Success" : "Failed");
  printf("- delete should also work ... ");
  tfs_deleteFile(x);
  tfs_readDir(filenames, &numfiles);
  printf("%s\n", numfiles == 1 ? "Success" : "Failed");
  free(*filenames);

  printf("Test #6: writeByte should behave\n");
  x = tfs_openFile(name);
  printf("- writeByte should return END_OF_FILE when end of file... ");
  printf("%s\n", tfs_writeByte(x, samp) == END_OF_FILE ? "Success" : "Failed");
  printf("- writeByte should write to third block of file ... ");
  tfs_writeFile(x, big_data, THREE_BLOCK_SIZE);
  tfs_seek(x, THREE_BLOCK_SIZE - 2);
  tfs_writeByte(x, 34);
  tfs_seek(x, THREE_BLOCK_SIZE - 2);
  tfs_readByte(x, &temp);
  printf("%s\n", temp == 34 ? "Success" : "Failed");

  tfs_unmount();
}


void resizeTestSuite() {
  fileDescriptor x,y;
  char big_data[THREE_BLOCK_SIZE], small_data[SMALL_SIZE];
  char temp;
  int i;
  char *bitmap;
  bitmap = (char *)calloc(NUM_BLOCKS / 8 + 1, sizeof(char));


  for(i = 0; i < THREE_BLOCK_SIZE; i++)
    big_data[i] = THREE_BLOCK_SIZE - i;
  for(i = 0; i < SMALL_SIZE; i++)
    small_data[i] = i;
  //for(i = 0; i < SMALL_SIZE + SMALL_SIZE; i++)
  //  small_data2[i] = SMALL_SIZE + SMALL_SIZE - i + 10;

  tfs_mkfs("testdisk", DEFAULT_DISK_SIZE);
  tfs_mount("testdisk");


  printf("\n\n~~~Resizing~~~\n");
  x = tfs_openFile("abc");

  printf("Test #1 3 blocks to 1 block\n");
  printf("- writing 3 blocks into file should return 3 blocks ...");
  tfs_writeFile(x, big_data, THREE_BLOCK_SIZE);
  for(i = 0; i < THREE_BLOCK_SIZE; i++) {
    if(tfs_readByte(x, &temp) != 0) {
      printf("Failed (readByte failed)\n");
      break;
    }
    if(temp != big_data[i]) {
      printf("Failed (data was not preserved)\n");
      break;
    }
  }
  if( i == THREE_BLOCK_SIZE)
   printf("Success\n");
  printf("- original file should be appropriate length ... ");
  printf("%s\n", tfs_readByte(x, &temp) == END_OF_FILE ? "Success" : "Failed");

  printf("- overwrite to 1 block ...");
  tfs_writeFile(x, small_data, SMALL_SIZE);
  for(i = 0; i < SMALL_SIZE; i++) {
    if(tfs_readByte(x, &temp) != 0) {
      printf("Failed (readByte failed)\n");
      break;
    }
    if(temp != small_data[i]) {
      printf("Failed (data was not preserved)\n");
      break;
    }
  }
  if( i == SMALL_SIZE)
   printf("Success\n");
  printf("- shrinked file should be appropriate length ... ");
  printf("%s\n", tfs_readByte(x, &temp) == END_OF_FILE ? "Success" : "Failed");

  printf("Test #2 opening a second file\n");
  printf("- should only have one file extent block originally ... ");
  tfs_displayFragments(bitmap);
  printf("%s\n", strncmp(bitmap, "1224434", 7) == 0 ? "Success" : "Failed");

  y = tfs_openFile("def");
  printf("- should have four file extent blocks after big file ... ");
  tfs_writeFile(y, big_data, THREE_BLOCK_SIZE);
  tfs_displayFragments(bitmap);
  printf("%s\n", strncmp(bitmap, "122233334", 9) == 0 ? "Success" : "Failed");

  printf("- should be able to recover data from first file ... ");
  tfs_seek(x, 0);
  for(i = 0; i < SMALL_SIZE; i++) {
    if(tfs_readByte(x, &temp) != 0) {
      printf("Failed (readByte failed)\n");
      break;
    }
    if(temp != small_data[i]) {
      printf("Failed (data was not preserved)\n");
      break;
    }
  }
  if (i == SMALL_SIZE)
    printf("Success\n");

  printf("- should be able to recover data from second file ... ");
  for(i = 0; i < THREE_BLOCK_SIZE; i++) {
    if(tfs_readByte(y, &temp) != 0) {
      printf("Failed (readByte failed)\n");
      break;
    }
    if(temp != big_data[i]) {
      printf("Failed (data was not preserved)\n");
      break;
    }
  }
  if(i == THREE_BLOCK_SIZE)
    printf("Success\n");

  tfs_unmount();

}

int main(int argc, char * argv[])
{

  simpleTestSuite();
  longFileTestSuite();
  openAndCloseTestSuite();
  overwriteTestSuite();
  deleteTestSuite();
  renameTestSuite();
  timeTestSuite();
  readonlyTestSuite();
  resizeTestSuite();

  return 0;
}
