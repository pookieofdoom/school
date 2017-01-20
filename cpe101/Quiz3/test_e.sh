#!/bin/sh

TEST_DIR=/home/phatalsk/Quiz3
EXEC_NAME=a.out

for base in `ls $TEST_DIR/*.ind | sed -e sX.*/XX | sed -e s/\\.ind//`; do
    echo Evaluating test case $base...
    cp -f $TEST_DIR/$base.ind $TEST_DIR/e$base.out .
    ./$EXEC_NAME < $base.ind > my_$base.out
    diff -b e$base.out my_$base.out
done
