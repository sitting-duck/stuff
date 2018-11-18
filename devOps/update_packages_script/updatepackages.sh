#!/bin/bash

while read p; do
  echo "$p"

  if [[ $p == *"<Description>"* ]]; then
  	echo "found a line with <Description> tag"
  fi

done </d/Projects/project/win_setup/program/packages/packages.conf

# packages=($(grep -oP '(?<=Package>)[^<]+' "/d/Projects/fStudio/win_setup/program/packages/packages.conf"))
# -o, --only-matching       show only the part of a line matching PATTERN
# -P, --perl-regexp         PATTERN is a Perl regular expression

# Perl meta characters: {}[]()^$.|*+?-\
# () - grouping metacharacter
# ^ - anchor metacharacter to match at the beginning of the string
# $ - anchor metacharacter to match at the end of the string or before a newline at the end of the string
# [] - denotes a character class. (the special characters for a character class are: -]\^$)

# [^<] - neglected character class. Match everything that is not <, and there must be a < or else the match fails

# Select each entire package: <Package>(.*)<\/Package>


# packages=($(grep -oP "Package" "/d/Projects/fStudio/win_setup/program/packages/packages.conf"))
# putting the entire expression in parens means that we are in list context, so the matches are returned in a list
# 


# packages=($(grep -oP '(?<Package>)[^<Package>].[^</Package>]+' "/d/Projects/fStudio/win_setup/program/packages/packages.conf"))
# packages=($(grep -oP '<[^>]*>[^<]*<[^>]*>' "/d/Projects/fStudio/win_setup/program/packages/packages.conf"))
# packages=($(grep -oP '(<Package>([\w\W]*)<\/Package>)' "/d/Projects/fStudio/win_setup/program/packages/packages.conf"))
# any=($(grep -oP '(<DisplayName>.*<\/DisplayName>)' "/d/Projects/fStudio/win_setup/program/packages/packages.conf"))

# packages=($(grep -oP '(<Package>/[\S\s\w\W]*<\/Package>)' "/d/Projects/fStudio/win_setup/program/packages/packages.conf"))
# versions=($(grep -oP '(<Version>[\s\S]*<\/Version>)' "/d/Projects/fStudio/win_setup/program/packages/packages.conf"))
# directories=($(grep -oP '(<Directory>[\s\S]*<\/Directory>)' "/d/Projects/fStudio/win_setup/program/packages/packages.conf"))

# dates=($(grep -oP '(<Date>[\w\W]*<\/Date>)' "/d/Projects/fStudio/win_setup/program/packages/packages.conf"))

# displayNames=($(grep -oP '(<DisplayName>(?s).+<\/DisplayName>)' "/d/Projects/fStudio/win_setup/program/packages/packages.conf"))


# echo $(grep -oP '(<DisplayName>(?s).+<\/DisplayName>)' "/d/Projects/fStudio/win_setup/program/packages/packages.conf")
# echo $(grep -oP 's/(<Description>[\s\S]*<\/Description>)/' "/d/Projects/fStudio/win_setup/program/packages/packages.conf")

# displayNameTokens=($(grep -oP '(<DisplayName>[\s\S]*<\/DisplayName>)' "/d/Projects/fStudio/win_setup/program/packages/packages.conf"))
# descriptionTokens=($(grep -oP 's/(<Description>[\s\S]*<\/Description>)/' "/d/Projects/fStudio/win_setup/program/packages/packages.conf"))

# grep -E, --extended-regexp     PATTERN is an extended regular expression
# fuckingDescrips=($(grep -E "<Description>([[:digit:]]|[^[:digit:]])+<\/Description>" "/d/Projects/fStudio/win_setup/program/packages/packages.conf"))
# echo $(grep -oE "<Description>([[:digit:]]|[^[:digit:]])+<\/Description>"  "/d/Projects/fStudio/win_setup/program/packages/packages.conf"))
# printf '%s\n' "${fuckingDescrips[@]}"

# echo "ANY"

#  for i in ${!any[*]}
#  do
#  	# $1 is equivalent to the first match, $2 is equivalent to the second match and so on. 
#  	echo "$i" "${any[$i]}"
#  done


# echo "PACKAGES"

#  for i in ${!packages[*]}
#  do
#  	# $1 is equivalent to the first match, $2 is equivalent to the second match and so on. 
#  	echo "$i" "${packages[$i]}"
#  done

# echo "VERSIONS"

# for i in ${!versions[*]}
#  do
#  	# $1 is equivalent to the first match, $2 is equivalent to the second match and so on. 
#  	echo "$i" "${versions[$i]}"
#  done

# echo "DIRECTORIES"

# for i in ${!directories[*]}
#  do
#  	# $1 is equivalent to the first match, $2 is equivalent to the second match and so on. 
#  	echo "$i" "${directories[$i]}"
#  done

# echo "display names"

# for i in ${!displayNames[*]}
#  do
#  	# $1 is equivalent to the first match, $2 is equivalent to the second match and so on. 
#  	echo "$i" "${displayNames[$i]}"
#  done

#  echo "DATES"

# for i in ${!dates[*]}
#  do
#  	# $1 is equivalent to the first match, $2 is equivalent to the second match and so on. 
#  	echo "$i" "${dates[$i]}"
#  done

#  echo "DISPLAY NAMES"
# declare -a displayNames
# currentDisplayNameIndex=0
# for i in ${!displayNameTokens[*]}
#  do
#  	# $1 is equivalent to the first match, $2 is equivalent to the second match and so on. 
#  	if [[ ${displayNameTokens[$i]} == *"<DisplayName>"* ]]; then
#  		while [ true ]; do
#  			if [[ ${displayNameTokens[$i]} != *"</DisplayName>"* ]]; then
#  				tempString="$tempString ${displayNameTokens[$i]}"
#  				i=$i+1
#  			fi

#  			if [[ ${displayNameTokens[$i]} == *"</DisplayName>"* ]]; then
#  				tempString="$tempString ${displayNameTokens[$i]}"
#  				break
#  			fi 			
#  		done
#  	fi

#  	displayNames[$currentDisplayNameIndex]=$tempString
#  	currentDisplayNameIndex=$((currentDisplayNameIndex+1)) 	
#  	tempString=""
#  done

#   printf '%s\n' "${displayNames[@]}"

# echo "DESCRIPTIONS"
# printf '%s\n' "${descriptionTokens[@]}"

# declare -a descriptions
# currentDescriptionIndex=0
# for i in ${!descriptionTokens[*]}
#  do
#  	# $1 is equivalent to the first match, $2 is equivalent to the second match and so on. 
#  	if [[ ${descriptionTokens[$i]} == *"<Description>"* ]]; then
#  		while [ true ]; do
#  			if [[ ${descriptionTokens[$i]} != *"</Description>"* ]]; then
#  				tempString="$tempString ${descriptionTokens[$i]}"
#  				echo "new temp: $tempString"
#  				i=$i+1
#  			fi

#  			if [[ ${descriptionTokens[$i]} == *"</Description>"* ]]; then
#  				tempString="$tempString ${descriptionTokens[$i]}"
#  				break
#  			fi 			
#  		done
#  	fi

#  	descriptions[$currentDescriptionIndex]=$tempString
#  	currentDescriptionIndex=$((currentDescriptionIndex+1)) 	
#  	tempString=""
#  done

#   printf '%s\n' "${descriptions[@]}"






