Ensure that the JDK is already installed.

If the installer is on a CD, Copy the EXE file for the Netbeans 6.5.1 installer onto your hard disk.

Note the location of the installer.

Open a Command Prompt running as administrator: Go to Start button > All Programs > Accessories Right click Command Prompt Select Run as administrator

In the Command Prompt use the cd command to change to the directory containing the installer.

Execute the following command to extract the contents of the installer: [Note: You might need to change the name of the installer to match the one you have.]

netbeans-6.5.1-ml-java-windows.exe --extract

Execute the following command to manually execute the installer:

java -jar bundle.jar

You will see rapid scrolling output in the Command Prompt window for a few moments, then the installer window will appear to begin the installation process.

