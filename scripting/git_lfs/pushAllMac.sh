# this script is for pushing all files individually to git lfs instead of adding them all at once and then
# trying to push a huge commit to git lfs.
# When GitLFS was newer this could fail about 20 minutes into an uplaod and then have to be restarted
# this sript was a surefire way to get around that limitation but a setback with this approach 
# is that now there are as many commits in the commit history as there are files that you pushed, which
# could be undesirable and create clutter in the history

#!/bin/sh

# global var definitions
dir=/Projects/maccontents/
branch="newbranch5"

rm -rf .git
rm README.md

 git init
 git remote add origin https://github.com/sitting-duck/stuff.git

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
  	branch="newbranch5"

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
