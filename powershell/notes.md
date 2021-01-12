it won't do anything by default because security first. 
First, reopen the powershell as an administrator.

so do this:
```
Get-ExecutionPolicy
```
it's probably going to say Restricted
```
Set-ExecutionPolicy Unrestricted
```
to open it up


