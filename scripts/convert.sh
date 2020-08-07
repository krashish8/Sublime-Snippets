#!/bin/bash

# Convert all sublime-snippet files in current directory to cpp files, removing extra lines from sublime-snippet

rm -rf cpp-codes
[[ -d cpp-codes ]] || mkdir cpp-codes

for f in *.sublime-snippet;
do
	filename="${f%.*}";
	sed '1,2d' "${filename}.sublime-snippet" | sed '$d' | sed '$d' | sed '$d' | sed '$d'| sed '$d' | sed '$d' > "cpp-codes/${filename}.cpp";
	# DON'T DELETE THE SNIPPETS FILE
	# rm -rf "${filename}.sublime-snippet";
done
