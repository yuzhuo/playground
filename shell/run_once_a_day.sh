#!/bin/bash

stampfile="test.ts"
today=`date +%Y%m%d`

if [ -f $stampfile ]; then
    stamp=`cat $stampfile`
    if [ "$today" == "$stamp" ]; then
        echo "has run today"
    else
        echo -e $today > $stampfile
        echo "not run today"
    fi
else
    touch $stampfile
    echo -e $today > $stampfile
    echo "never run"
fi
