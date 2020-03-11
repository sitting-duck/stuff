Environment.plist files are apparently an easy way to set environment variables on the Mac. 

I have been broken hearted before in the past when trying to debug others peoples code on the MACOS and was unable to access my environment variables I had set on the command line. 

You keep it in the home directory.

To activate the environment.plist (assuming you named it environment.plist), run

launchctl load ~/environment.plist
launchctl start ~/environment.plist

If it is already loaded and you have modified the plist file, see your updates by running:

launchctl stop ~/environment.plist
launchctl unload ~/environment.plist
launchctl load ~/environment.plist
launchctl start ~/environment.plist

