### Check if the App bundle is signed
codesign -vv

### Get the Identities
security find-identity -v -p codesigning
