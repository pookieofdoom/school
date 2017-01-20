CC = gcc
CFLAGS= -g -Wall

SOURCES = libDisk.c libTinyFS.c libDisk.h tinyFS.h tinyFsDemo.c libFileTable.c libFileTable.h libFreeBlocks.c libFreeBlocks.h featDirList.c featTimeStamps.c featReadWrite.c

all: tinyFsDemo

tinyFsDemo: $(SOURCES)
	gcc -o tinyFsDemo $(SOURCES) $(CFLAGS)

clean:
	rm tinyFsDemo
