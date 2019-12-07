#!/bin/sh


# global var definitions
dir=/d/Projects/myFolder/ # set this to the folder you want pushed to your github repo
branch="newbranch6" # set this to the name of the new branch you want to create (needs to be set again below)


# function definitions
function add_file_and_push_to_github() {
	branch="newbranch6" # set this to the name of the new branch you want to create (until I can look up how to make global var in bash)

	git add "$1"
	git commit -m "add $1"
	git pull origin "${branch}"
	git push origin "${branch}"
}

rm -rf .git
rm README.md

 git init
 git remote add origin https://github.com/sitting-duck/stuff.git

 git pull origin master
 git checkout -b "$branch"

 git lfs install

 git add .gitattributes
 git push -u origin "$branch"

 git lfs track *.lib
 git lfs track *.dll

 git pull origin "$branch"

export -f add_file_and_push_to_github
find . -type f -print0 | xargs -0 bash -c 'add_file_and_push_to_github "$@"'

