#!/bin/sh

TEST_DIR=/home/phatalsk/Quiz1
EXEC_NAME=a.out

for base in `ls $TEST_DIR/*.ina | sed -e sX.*/XX | sed -e s/\\.ina//`; do
    echo Evaluating test case $base...
    cp -f $TEST_DIR/$base.ina $TEST_DIR/$base.outa .
    ./$EXEC_NAME < $TEST_DIR/$base.ina > my_$base.outa
    diff -b $TEST_DIR/$base.outa my_$base.outa
done
