#!/bin/sh

TEST_DIR=/home/jworkman/SampleQuiz1
EXEC_NAME=a.out

for base in `ls $TEST_DIR/*.in | sed -e sX.*/XX | sed -e s/\\.in//`; do
    echo Evaluating test case $base...
    cp -f $TEST_DIR/$base.in $TEST_DIR/$base.out .
    ./$EXEC_NAME < $TEST_DIR/$base.in > my_$base.out
    diff $TEST_DIR/$base.out my_$base.out
done
