#!/bin/sh

# global var definitions
dir=/Projects/path/to/dependencies/
branch="my-branch"

rm -rf .git
rm README.md

 git init
 git remote add origin https://github.com/sitting-duck/myRepo.git

 git pull origin master
 git checkout -b "$branch"

 git lfs install

 git add .gitattributes
 echo "before push -u $branch"
 git push -u origin "$branch"
 echo "after push -u $branch"

 git lfs track *.dylib

 git pull origin "$branch"

while IFS="" read -r p || [ -n "$p" ]
do
  printf '%s\n' "$p"

  if [[ p != *".git"* ]]; then
  	branch="my-branch"

	echo "in here: $p"
	git add "$p"
	echo "after add"
	git commit -m "add $p"
	echo "after commit"
	git pull origin "${branch}"
	echo "after pull ${branch}"
	git push origin "${branch}"
	echo "after push to ${branch}"
  fi

done < files.txt
