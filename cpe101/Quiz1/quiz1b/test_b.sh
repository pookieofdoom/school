#!/bin/sh

TEST_DIR=/home/phatalsk/Quiz1
EXEC_NAME=a.out

for base in `ls $TEST_DIR/*.inb | sed -e sX.*/XX | sed -e s/\\.inb//`; do
    echo Evaluating test case $base...
    cp -f $TEST_DIR/$base.inb $TEST_DIR/$base.outb .
    ./$EXEC_NAME < $TEST_DIR/$base.inb > my_$base.outb
    diff -wb $TEST_DIR/$base.outb my_$base.outb
done
