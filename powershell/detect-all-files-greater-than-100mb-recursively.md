Enter your own path instead of the one in this example, the root folder of the C:\drive.

 ```
 Get-ChildItem C:\ -recurse | where-object {$_.length -gt 100000000} | Sort-Object length | ft fullname, length -auto
 ```
 
 gt 1000000 basically means size greater than 1 million bytes which is 100MB (the file size limit for Git LFS)
 
 use lt to find files smaller than. 
 
 change 10000000 to a different number to customize size. 
