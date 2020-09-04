#!/bin/bash

# First convert the files
bash scripts/convert.sh

# CREATING FIRST CODEBOOK

BASEDIR="codebook-1"
CONTENTS="scripts/contents.txt"

rm -rf "$BASEDIR"
[[ -d "$BASEDIR" ]] || mkdir "$BASEDIR"

DIRNAME=""
DIRCOUNTER=1
FILECOUNTER=1

while read -r line
do
    if [[ $line == "["*"]" ]]; then
        DIRNAME=${line#"["}
        DIRNAME=${DIRNAME%"]"}
        DIRNAME="${DIRCOUNTER}. ${DIRNAME}"
        DIRCOUNTER=$((DIRCOUNTER+1))
        FILECOUNTER=1
        mkdir $BASEDIR/"$DIRNAME"
    elif [[ $line == *"|"* ]]; then
        filename=`echo "${line%|*}" | sed 's/ *$//g'`
        newfilename=`echo "${line#*|}" | sed 's/^ *//g'`

        FILECOUNTER_WITHZERO=`printf "%02d" $FILECOUNTER`
        cp "cpp-codes"/$filename "$BASEDIR"/"$DIRNAME"/"${newfilename}.cpp"
        FILECOUNTER=$((FILECOUNTER+1))
    fi
done < "$CONTENTS"

# Convert to pdf
codes2pdf $BASEDIR
mv notebook.pdf "${BASEDIR}"/"${BASEDIR}.pdf"

# CREATING SECOND CODEBOOK

BASEDIR2="codebook-2"
rm -rf "$BASEDIR2"
[[ -d "$BASEDIR2" ]] || mkdir "$BASEDIR2"

cp scripts/generator.py $BASEDIR2
cp scripts/notebook.tex $BASEDIR2
cd $BASEDIR2
python2 generator.py

mv "notebook.pdf" "${BASEDIR2}.pdf"