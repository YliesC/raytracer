#!/bin/sh

if [ "$USER" == "chahi_y" ]; then
    echo 0
    exit 0
fi

which qmake > /dev/null 2>&1
if [ $? -eq 0 ]; then
    qmake -v | grep 'Qt version 5.' > /dev/null 2>&1
    echo $?
else
    echo 1
fi
