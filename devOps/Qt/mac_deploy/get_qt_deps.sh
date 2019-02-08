#! /bin/bash

##
## NOTE: WE ARE COPYING INTO THE BUNDLE IN MAC_SETUP
##

# I write a script like this because copying all these dependencies manually with a mouse is painful. At any moment, I could be forced to create a new
# deploy environment on another machine, if, for example, a developer introduces a dependency that makes my machine no longer appropriate for deployment, 
# perhaps MacOS has released their next version, and I cannot update this machine to the next OS because Apple says my hardwarenew  will not support the new OS, 
# my machine runs out of space and I am unwilling to delete any deployment related projects, so I need to just start building new projects on a new machine, 
# this script will just fetch what we need for a QT app on the mac. 

# Every time you update which version of Qt you are using, you need to update the QTDIR 
# variable and possibly even write a new slightly modified version of this script. With every new version of Qt, some packages will be added, some deleted, 
# renamed or moved around. You can expect that your script will be able to mostly stay the same, but probably one major thing has been renamed. Keeping up a little
# bit with what is new in this Qt version may help you, but isn't necessarily required.

# Ideally you'll have a different version of this script so that at any time anyone can whip up a new deploy environment on any machine for whatever version of Qt 
# they need

APP="/Users/Shared/Jenkins/Home/workspace/Program/mac_setup/Test Program.app
PLUGINS_DIR="$APP/Contents/PlugIns"
QTDIR="/Users/macbuild/Qt/5.6.3/clang_64"
QTIFW="/Users/Shared/Jenkins/Home/workspace/Program/mac_setup/Program/"

##
## COPY IN ALL THE PLUGINS
##
cp "$QTDIR"/plugins/audio/libqtaudio_coreaudio.dylib "$PLUGINS_DIR"/audio/

cp "$QTDIR"/plugins/bearer/libqcorewlanbearer.dylib "$PLUGINS_DIR"/bearer/
cp "$QTDIR"/plugins/bearer/libqgenericbearer.dylib "$PLUGINS_DIR"/bearer/

# PLUGINS_DIR refers to Qt plugins, not your developed plugins. imageformats are a Qt plugin
# I am not sure what this dds type image is, it seems to be present in some Qt versions and not in others
#cp "$QTDIR"/plugins/imageformats/libqdds.dylib "$PLUGINS_DIR"/imageformats/
cp "$QTDIR"/plugins/imageformats/libqgif.dylib "$PLUGINS_DIR"/imageformats/
cp "$QTDIR"/plugins/imageformats/libqicns.dylib "$PLUGINS_DIR"/imageformats/
cp "$QTDIR"/plugins/imageformats/libqico.dylib "$PLUGINS_DIR"/imageformats/
cp "$QTDIR"/plugins/imageformats/libqjpeg.dylib "$PLUGINS_DIR"/imageformats/
cp "$QTDIR"/plugins/imageformats/libqsvg.dylib "$PLUGINS_DIR"/imageformats/
cp "$QTDIR"/plugins/imageformats/libqtga.dylib "$PLUGINS_DIR"/imageformats/
cp "$QTDIR"/plugins/imageformats/libqtiff.dylib "$PLUGINS_DIR"/imageformats/
cp "$QTDIR"/plugins/imageformats/libqwbmp.dylib "$PLUGINS_DIR"/imageformats/
cp "$QTDIR"/plugins/imageformats/libqwebp.dylib "$PLUGINS_DIR"/imageformats/

cp "$QTDIR"/plugins/mediaservice/libqavfcamera.dylib "$PLUGINS_DIR"/mediaservice/
cp "$QTDIR"/plugins/mediaservice/libqavfmediaplayer.dylib "$PLUGINS_DIR"/mediaservice/
cp "$QTDIR"/plugins/mediaservice/libqtmedia_audioengine.dylib "$PLUGINS_DIR"/mediaservice/

cp "$QTDIR"/plugins/platforms/libqcocoa.dylib  "$PLUGINS_DIR"/platforms/

cp "$QTDIR"/plugins/printsupport/libcocoaprintersupport.dylib  "$PLUGINS_DIR"/printsupport/

# If your application uses a database
cp "$QTDIR"/plugins/sqldrivers/libqsqlite.dylib "$PLUGINS_DIR"/sqldrivers/
cp "$QTDIR"/plugins/sqldrivers/libqsqlmysql.dylib "$PLUGINS_DIR"/sqldrivers/
cp "$QTDIR"/plugins/sqldrivers/libqsqlodbc.dylib "$PLUGINS_DIR"/sqldrivers/
cp "$QTDIR"/plugins/sqldrivers/libqsqlpsql.dylib "$PLUGINS_DIR"/sqldrivers/

cp -r "$PLUGINS_DIR" "$QTIFW/contents-beta/qt/Test Program.app/Contents/"

##
## DELETE ALL THE EXTRA GARBAGE DRAGGED IN BY MACDEPLOYQT
##
## You are probably hosting this application somewhere like aws for exapmle. You are paying per download, so storing 
## unecessary files is costing you money every time someone downloads, and with no benefit to the user. Keep your app profile
## lean and mean to save money 
rm -rf "$QTIFW"/contents-beta/qt/Test\ Program.app/Contents/Frameworks/Qt3DCore.framework
rm -rf "$QTIFW"/contents-beta/qt/Test\ Program.app/Contents/Frameworks/Qt3DInput.framework
rm -rf "$QTIFW"/contents-beta/qt/Test\ Program.app/Contents/Frameworks/Qt3DLogic.framework
rm -rf "$QTIFW"/contents-beta/qt/Test\ Program.app/Contents/Frameworks/Qt3DQuick.framework
rm -rf "$QTIFW"/contents-beta/qt/Test\ Program.app/Contents/Frameworks/Qt3DQuickScene2D.framework
rm -rf "$QTIFW"/contents-beta/qt/Test\ Program.app/Contents/Frameworks/Qt3DRender.framework
rm -rf "$QTIFW"/contents-beta/qt/Test\ Program.app/Contents/Frameworks/QtConcurrent.framework
rm -rf "$QTIFW"/contents-beta/qt/Test\ Program.app/Contents/Frameworks/QtMultimedia.framework
rm -rf "$QTIFW"/contents-beta/qt/Test\ Program.app/Contents/Frameworks/QtMultimediaQuick_p.framework
rm -rf "$QTIFW"/contents-beta/qt/Test\ Program.app/Contents/Frameworks/QtMultimediaWidgets.framework
rm -rf "$QTIFW"/contents-beta/qt/Test\ Program.app/Contents/Frameworks/QtQuickControls2.framework
rm -rf "$QTIFW"/contents-beta/qt/Test\ Program.app/Contents/Frameworks/QtQuickParticles.framework
rm -rf "$QTIFW"/contents-beta/qt/Test\ Program.app/Contents/Frameworks/QtQuickTemplates2.framework
rm -rf "$QTIFW"/contents-beta/qt/Test\ Program.app/Contents/Frameworks/QtXmlPatterns.framework

##
## DESTROY ALL DEBUG FILE BLOAT DRAGGED IN BY MACDEPLOYQT (why would anyone deploy debug code wtf?)
##
cd "$QTIFW"
find . -name "*_debug*" -print0 | xargs -0 rm -rf
#find . -name "*_debug*" -type f -print0 | xargs -0 rm -rf
find . -name "*.dSYM" -print0 | xargs -0 rm -rf
find . -name "*.*.dSYM" -print0 | xargs -0 rm -rf
find . -name "*.prl" -print0 | xargs -0 rm -rf

# DESTROY ALL HEADERS. (why would we deploy headers? Do you think users want to read code?)
find . -type d -name "Headers" -print0 | xargs -0 rm -rf
find . -type f -name "Headers" -print0 | xargs -0 rm -rf


