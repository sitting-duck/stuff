#! /bin/bash

##
## NOTE: WE ARE COPYING INTO THE BUNDLE IN MAC_SETUP
##
APP="/Users/Shared/Jenkins/Home/workspace/Program/mac_setup/Test Program.app"
PLUGINS_DIR="$APP/Contents/PlugIns"
QTDIR="/Users/macbuild/Qt/5.6.3/clang_64"
QTIFW="/Users/Shared/Jenkins/Home/workspace/Program/mac_setup/Program/"

##
## COPY IN ALL THE PLUGINS
##
cp "$QTDIR"/plugins/audio/libqtaudio_coreaudio.dylib "$PLUGINS_DIR"/audio/

cp "$QTDIR"/plugins/bearer/libqcorewlanbearer.dylib "$PLUGINS_DIR"/bearer/
cp "$QTDIR"/plugins/bearer/libqgenericbearer.dylib "$PLUGINS_DIR"/bearer/

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

## the plugins "quick" dir apparently doesn't exist for Qt 5.6.3
# cp "$QTDIR"/plugins/quick/libdeclarative_multimedia.dylib "$PLUGINS_DIR"/quick/
# cp "$QTDIR"/plugins/quick/libdialogplugin.dylib "$PLUGINS_DIR"/quick/
# cp "$QTDIR"/plugins/quick/libdialogsprivateplugin.dylib "$PLUGINS_DIR"/quick/
# cp "$QTDIR"/plugins/quick/libmodelsplugin.dylib "$PLUGINS_DIR"/quick/
# cp "$QTDIR"/plugins/quick/libqmlfolderlistmodelplugin.dylib "$PLUGINS_DIR"/quick/
# cp "$QTDIR"/plugins/quick/libqmlsettingsplugin.dylib "$PLUGINS_DIR"/quick/
# cp "$QTDIR"/plugins/quick/libqquicklayoutsplugin.dylib "$PLUGINS_DIR"/quick/
# cp "$QTDIR"/plugins/quick/libqtgraphicaleffectsprivate.dylib "$PLUGINS_DIR"/quick/
# cp "$QTDIR"/plugins/quick/libqtquick2plugin.dylib "$PLUGINS_DIR"/quick/
# cp "$QTDIR"/plugins/quick/libqtquickcontrolsplugin.dylib "$PLUGINS_DIR"/quick/
# cp "$QTDIR"/plugins/quick/libqtquickextrasflatplugin.dylib "$PLUGINS_DIR"/quick/
# cp "$QTDIR"/plugins/quick/libqtquickextrasplugin.dylib "$PLUGINS_DIR"/quick/
# cp "$QTDIR"/plugins/quick/libwidgetsplugin.dylib "$PLUGINS_DIR"/quick/
# cp "$QTDIR"/plugins/quick/libwindowplugin.dylib "$PLUGINS_DIR"/quick/

cp "$QTDIR"/plugins/sqldrivers/libqsqlite.dylib "$PLUGINS_DIR"/sqldrivers/
cp "$QTDIR"/plugins/sqldrivers/libqsqlmysql.dylib "$PLUGINS_DIR"/sqldrivers/
cp "$QTDIR"/plugins/sqldrivers/libqsqlodbc.dylib "$PLUGINS_DIR"/sqldrivers/
cp "$QTDIR"/plugins/sqldrivers/libqsqlpsql.dylib "$PLUGINS_DIR"/sqldrivers/

cp -r "$PLUGINS_DIR" "$QTIFW/contents-beta/qt/Test Program.app/Contents/"

##
## DELETE ALL THE EXTRA GARBAGE DRAGGED IN BY MACDEPLOYQT
##
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

# DELETE THE APPLICATION OSX LIBS FROM MACOS
rm -rf "$QTIFW"/contents-beta/tlsw/Test\ Program.app/Contents/MacOs/libalgorithms.dylib
rm -rf "$QTIFW"/contents-beta/tlsw/Test\ Program.app/Contents/MacOs/libalgorithms.*.dylib
rm -rf "$QTIFW"/contents-beta/tlsw/Test\ Program.app/Contents/MacOs/libalgorithms.*.*.dylib
rm -rf "$QTIFW"/contents-beta/tlsw/Test\ Program.app/Contents/MacOs/libalgorithms.*.*.*.dylib

rm -rf "$QTIFW"/contents-beta/tlsw/Test\ Program.app/Contents/MacOs/libimpbase.dylib
rm -rf "$QTIFW"/contents-beta/tlsw/Test\ Program.app/Contents/MacOs/libimpbase.*.dylib
rm -rf "$QTIFW"/contents-beta/tlsw/Test\ Program.app/Contents/MacOs/libimpbase.*.*.dylib
rm -rf "$QTIFW"/contents-beta/tlsw/Test\ Program.app/Contents/MacOs/libimpbase.*.*.*.dylib

rm -rf "$QTIFW"/contents-beta/tlsw/Test\ Program.app/Contents/MacOs/libimprocs.dylib
rm -rf "$QTIFW"/contents-beta/tlsw/Test\ Program.app/Contents/MacOs/libimprocs.*.dylib
rm -rf "$QTIFW"/contents-beta/tlsw/Test\ Program.app/Contents/MacOs/libimprocs.*.*.dylib
rm -rf "$QTIFW"/contents-beta/tlsw/Test\ Program.app/Contents/MacOs/libimprocs.*.*.*.dylib

rm -rf "$QTIFW"/contents-beta/tlsw/Test\ Program.app/Contents/MacOs/librender.dylib
rm -rf "$QTIFW"/contents-beta/tlsw/Test\ Program.app/Contents/MacOs/librender.*.dylib
rm -rf "$QTIFW"/contents-beta/tlsw/Test\ Program.app/Contents/MacOs/librender.*.*.dylib
rm -rf "$QTIFW"/contents-beta/tlsw/Test\ Program.app/Contents/MacOs/librender.*.*.*.dylib

##
## DESTROY ALL DEBUG FILE BLOAT DRAGGED IN BY MACDEPLOYQT (why would anyone deploy debug code? Release mode only)
##
cd "$QTIFW"
find . -name "*_debug*" -print0 | xargs -0 rm -rf
#find . -name "*_debug*" -type f -print0 | xargs -0 rm -rf
find . -name "*.dSYM" -print0 | xargs -0 rm -rf
find . -name "*.*.dSYM" -print0 | xargs -0 rm -rf
find . -name "*.prl" -print0 | xargs -0 rm -rf

# DESTROY ALL HEADERS. (why would we deploy headers? Binary dependencies are deployed, but not actual code)
find . -type d -name "Headers" -print0 | xargs -0 rm -rf
find . -type f -name "Headers" -print0 | xargs -0 rm -rf


