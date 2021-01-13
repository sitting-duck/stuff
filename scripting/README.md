
### Vim Commands I Like: 
:%s/foo/bar/gc # search and replace entire doc with confirmation

:tabf . # open a file viewer for opening another doc in a new tab

:set number # show line numbers 


### Installing Stuff Windows
```
wget https://www.python.org/ftp/python/3.6.8/python-3.6.8-amd64.exe
wget https://sourceforge.net/projects/qttabbar/files/latest/download 
wget https://www.qt.io/download-thank-you?hsLang=en

python -m pip install --upgrade pip
pip install conan
```

### Looping Windows
```
set veai=C:/Program Files/derp.exe
set videos=C:\Users\me\Documents\stuff
set model=a b c d e f g
set sizen=1 2 4
set device=0 10
set block=1x2 2x3 3x4
(for %%m in (%model%) do (
	echo model: %%m
	(for %%s in (%sizen%) do (
		echo size: %%s

		(for %%d in (%device%) do (
			echo device: %%d

			(for %%b in (%block%) do (
				echo block: %%b
				"%veai%" -i "%videos%\input\school_%%b_10f.mp4" -o "%videos%\output\school_%%b_10f_%%sx_%%m_d%%d_out.mp4" -s %%s --output-format mp4 -m %%m -c %%d
			))
			
		))
		
	))
	
))
```

### Grab Stuff from Qt dir Windows
set qt=C:\Qt\5.15.2\msvc2019_64
set dll=Q5Core Qt5Gui Qt5Network Qt5Qml Qt5Quick Qt5QuickControls2 Qt5Sql Qt5Svg Qt5Xml Qt5Widgets
set dest=C:\Users\ashley\projects\image\build-Desktop_Qt_5_15_2_MSVC2019_64bit-Release\

(for %%d in (%dll%) do (
        XCOPY %qt%\bin\%%.dll %dest% /E /H /C /I
))

set qml=Qt QtQml QtQuick QtQuick.2
(for %%q in (%qml%) do (
        XCOPY %qt%\qml\%%q %dest% /E /H /C /I
))

set plugins=platforms imageformats
(for %%p in (%plugins%) do (
        XCOPY %qt%\plugins\%%p %dest% /E /H /C /I
))

