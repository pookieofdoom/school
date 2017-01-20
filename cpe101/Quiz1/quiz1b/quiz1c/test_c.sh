#!/bin/sh

TEST_DIR=/home/phatalsk/Quiz1
EXEC_NAME=a.out

for base in `ls $TEST_DIR/*.inc | sed -e sX.*/XX | sed -e s/\\.inc//`; do
    echo Evaluating test case $base...
    cp -f $TEST_DIR/$base.inc $TEST_DIR/$base.outc .
    ./$EXEC_NAME < $TEST_DIR/$base.inc > my_$base.outc
    diff -wb $TEST_DIR/$base.outc my_$base.outc
done
