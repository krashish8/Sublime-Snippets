#!/bin/bash

# Convert all sublime-snippet files in current directory to cpp files, removing extra lines from sublime-snippet
for f in *.sublime-snippet;
do
	filename="${f%.*}";
	sed '1,2d' "${filename}.sublime-snippet" | sed '$d' | sed '$d' | sed '$d' | sed '$d'| sed '$d' | sed '$d' > "${filename}.cpp";
	rm -rf "${filename}.sublime-snippet";
done