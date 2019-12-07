### My Git Tips

When using git on Windows and you are using a machine for both work related coding and personal related coding, you may find yourself in the situation where you are using two git accounts on the same machine. <br/>
I often find that using git config user.name myUserName, and even git config --global user.name myUserName, DOES NOT WORK :(. What you need to do is hit Windows key and search for "Credential Manager." <br/>
You'll see an option for "Web Credentials" and for "Windows Credentials". <br/>
Select "Windows Credentials" <br/>
Delete the Github token under "Generic Credentials" <br/>
Next time you try to use git from the command line it will prompt you for a new username and password. <br/>

