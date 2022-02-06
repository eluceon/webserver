#!/bin/bash

if [ -n "$1" ]
then
    if [ $1 = 'git' ]
    then
    git add *; git commit -m "sthrace commit"; git push
    fi
else
echo "Argument not provided"
fi

test