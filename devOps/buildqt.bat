:: If you start seeing this errors:
::The input line is too long.
::The syntax of the command is incorrect.
::It is because your path has become too long, vcvarsall.bat appends to the path every time it is called
::to fix this either figure out what path is being add to the path and check for it defined and if not call vcvarsall.bat or
::just restart your command prompt to start with fresh path

call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvarsall.bat" amd64

call "C:\Qt\5.15.2\msvc2019_64\bin\qtenv2.bat"

echo "start build"

:: pass in folder to recursively text replace, original string and replacement string
python "C:\projects\text_replace.py" "C:\projects\" "$$(VAR)" "C:/projects/conan/3rdpartylibs"

"C:\Qt\5.15.2\msvc2019_64\bin\qmake.exe" -set "$$(VAR)" "C:\projects\conan\3rdpartylibs"
cd "C:\projects"
"C:\Qt\5.15.2\msvc2019_64\bin\qmake.exe" "C:\projects\project.pro" -spec win32-msvc "CONFIG+=force_debug_info" "CONFIG+=separate_debug_info"
"C:\Qt\Tools\QtCreator\bin\jom.exe" -j6 release

echo "after build"

:: put the text back to original before text replacement
python "C:\projects\text_replace.py" "C:\projects" "$$(VAR)" "C:/projects/conan/3rdpartylibs"
