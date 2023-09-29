#!/bin/sh

BASEDIR=$(dirname "$0") # path to the directory of this script

# declare a function that prints a message
usage_exit() {
    echo "Usage: ./submit.sh OR ./submit.sh clear"
    exit 1
}

if [ $# -ge 2 ]; then
    usage_exit
fi

if [ $# -eq 1 ]; then
    if [ $1 = "clear" ]; then
        rm -f "$BASEDIR/pa1.cpp"
        rm -f "$BASEDIR/pa2.cpp"
        rm -f "$BASEDIR/pa3.cpp"
        rm -f "$BASEDIR/pa4.cpp"
        echo "Cleared all cpp files."
        exit 0
    else
        usage_exit
    fi
fi

for i in 1 2 3 4
do
    pa_name=pa$i
    pa_path="$BASEDIR/../$pa_name/src/$pa_name.cpp"
    if test -f "$pa_path"; then
        echo "PA$i Processing..."
        sed 's,.*//[ ]SUBMIT:.*,,g' $pa_path > "$BASEDIR/$pa_name.cpp"
    fi
done
