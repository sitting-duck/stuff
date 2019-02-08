

#!/bin/sh

APP_NAME="Test Program"
APP_NAME_NO_SPACE="TestProgram"

chmod -R a+wr "${APP_NAME}".app
#cd /Projects/mycompany/myprogram/mac_setup

# set permissions for the app so it can read, write and execute
# 755 means full permissions for the owner and read and execute permission for others
chmod -R 755 "$APP_NAME".app

# copy all the third party libs (dylib mach-o binary files) 
cp /usr/local/lib_old/*.dylib /Projects/mycompany/myprogram/mac_setup/"${APP_NAME}".app/Contents/MacOS/
cp /usr/local/lib_old/*.*.dylib /Projects/mycompany/myprogram/mac_setup/"${APP_NAME}".app/Contents/MacOS/
cp /usr/local/lib_old/*.*.*.dylib /Projects/mycompany/myprogram/mac_setup/"${APP_NAME}".app/Contents/MacOS/
cp /usr/local/lib_old/*.*.*.*.dylib /Projects/mycompany/myprogram/mac_setup/"${APP_NAME}".app/Contents/MacOS/

cp ./Contents/Info.plist ./"${APP_NAME}".app/Contents/
cp ./Contents/Resources/TestProgram.icns ./"${APP_NAME}".app/Contents/Resources/
cp ./Contents/Resources/TestProgrambeta.icns ./"${APP_NAME}".app/Contents/Resources/
cp -R ./Contents/Resources/"${APP_NAME_NO_SPACE}".plugin ./"${APP_NAME}".app/Contents/Resources/
cp ./Contents/Resources/"${APP_NAME_NO_SPACE}".lrtemplate ./"${APP_NAME}".app/Contents/Resources/

# macdeployqt uses otool to grab the list of dependencies your application has. It then searches the otool output of every dependency of every dependency
# and copies every Qt dependency from the Qt directory

cd ~/Qt/5.6/clang_64/bin/
~/Qt/5.6/clang_64/bin/macdeployqt /Projects/mycompany/myprogram/mac_setup/"${APP_NAME}".app -qmldir=/Projects/mycompany/myprogram/
~/Qt/5.6/clang_64/bin/macdeployqt /Projects/mycompany/myprogram/mac_setup/"${APP_NAME}".app -qmldir=/Projects/mycompany/myprogram/mac_setup/"${APP_NAME}".app/Contents/MacOS
cd /Projects/mycompany/myprogram/mac_setup/

mv "${APP_NAME}".app/Contents/MacOS/*.dylib "${APP_NAME}".app/Contents/Frameworks 
rm "${APP_NAME}".app/Contents/MacOS/*.a

# copy in needed qml binaries
cp -R qml_56/* "${APP_NAME}".app/Contents/MacOS

# fixing dylib dependencies in ruby
 sudo ruby ./fix_deps_lib3.rb ./"${APP_NAME}".app/Contents/Frameworks/
 sudo ruby ./fix_deps_lib3.rb ./"${APP_NAME}".app/Contents/MacOs/Test\ Program
 sudo ruby ./fix_deps.rb ./"${APP_NAME}".app
