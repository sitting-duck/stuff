#!/bin/sh

# This script is for adding files to Git LFS and then pushing them to a repo.
# It assumes you have already initalized git lfs. 
#
# Why do you need this script?
# If you need to push a loooooooot of dependencies to Git LFS. 
# If you try to push all your files at once in a single commit, any sort of 
# interruption in network connectivity could cause the push to fail and then 
# you will have to start all over again. This happened to me several times as I # tried to push 24 GB of files via git lfs to a repository. I wrote this script
# to commit and then push each file individually so I could get past that hurdle
# and move on to other things. 

# Cons: this makes the commit history rather long, but after you do it once, 
# it should be smooth sailing from there. I've never had this con cause me any
# trouble.

# global var definitions
dir=/c/Projects/path/to/local/deps
branch="my-branch"

# function definitions
function add_file_and_push_to_github() {
	branch="my-branch"

	echo "in here: $1"
	git add "$1"
	echo "after add"
	git commit -m "add $1"
	echo "after commit"
	git pull origin "${branch}"
	echo "after pull ${branch}"
	git push origin "${branch}"
	echo "after push to ${branch}"
}

rm -rf .git
rm README.md

 git init
 git remote add origin https://github.com/sitting-duck/MyDependenciesRepo.git

 git pull origin master
 git checkout -b "$branch"

 git lfs install

 git add .gitattributes
 echo "before push -u $branch"
 git push -u origin "$branch"
 echo "after push -u $branch"

 git lfs track *.lib
 git lfs track *.dll

 git pull origin "$branch"

export -f add_file_and_push_to_github
find . -type f -print0 | xargs -0 bash -c 'add_file_and_push_to_github "$@"'

