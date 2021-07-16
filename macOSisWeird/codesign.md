### Check if the App bundle is signed
```
codesign -vv
```

### Get the Identities
```
security find-identity -v -p codesigning
```

### Codesign Individual QT File in .app File
```
codesign --force --verify --verbose --sign "Developer ID Application: Company Name (10CHARSTRING)" MyProgram.app/Contents/Frameworks/QtCore.framework/Versions/5/QtCore

# You have to sign these extensionless Qt Files, all of them, you can write a script to get these all programmatically, but this shows how to sign just one

# Always use cp -R when copying in Qt files to be signed 

"Apple Development: Ashley Tharp (4JFQZVB37F)"

security unlock-keychain login.keychain

```
