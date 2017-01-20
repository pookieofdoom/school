#!/bin/sh

TEST_DIR=/home/phatalsk/Quiz3
EXEC_NAME=a.out

for base in `ls $TEST_DIR/*.ina | sed -e sX.*/XX | sed -e s/\\.ina//`; do
    echo Evaluating test case $base...
    cp -f $TEST_DIR/$base.ina $TEST_DIR/c$base.out .
    ./$EXEC_NAME < $base.ina > my_$base.out
    diff -b c$base.out my_$base.out
done
