#!/bin/sh

BASEDIR=$(dirname "$0") # path to the directory of this script

RED="\033[0;31m"
GREEN="\033[0;32m"
BOLD=$(tput bold)
NORMAL=$(tput sgr0)

declare -a submission_files=(
    "src/pa1.cpp" # PA1
    "src/pa2.cpp src/tree.cpp include/tree.h src/heap.cpp include/heap.h" # PA2
    "src/pa3.cpp src/closed_hash_function.cpp src/closed_hash_table.cpp src/open_hash_function.cpp src/open_hash_table.cpp src/sort.cpp src/tree.cpp src/bst.cpp src/avl.cpp include/closed_hash_function.h include/closed_hash_table.h include/open_hash_function.h include/open_hash_table.h include/sort.h include/tree.h include/bst.h include/avl.h" # PA3
    "src/pa4.cpp src/graph.cpp include/graph.h" # PA4
)

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
    if [ $i -gt ${#submission_files[@]} ] ; then
        break
    fi

    echo " ${RED}${BOLD}===== PA$i Processing =====${NORMAL}${GREEN} "
    
    pa_name=pa$i
    pa_dir_path="$BASEDIR/../$pa_name"
    pa_submission_dir_path="$BASEDIR/$pa_name"

    if ! [ -d $pa_submission_dir_path ] ; then
        echo "Creating a directory for $pa_name at $pa_submission_dir_path"
        mkdir -p $pa_submission_dir_path
    fi

    pa_file_relative_paths=(${submission_files[$i-1]})
    for file_path in "${pa_file_relative_paths[@]}"
    do
        file_name=$(basename $file_path)
        sed '/.*\/\/[ ]SUBMIT:.*/d' "$pa_dir_path/$file_path" > "$pa_submission_dir_path/$file_name"
    done

    echo "Processing done for $pa_name"
done
