version=${1}

if [ -z ${version} ]; then
        echo "Usage: update_win.sh <version (x.x.x)>"
        exit 1
else
        echo "uploading version '${version}'"
fi

rm ./conan/lib/*
cp ../build/*.lib ./conan/lib/

rm ./conan/bin/*
cp ../build/*.dll ./conan/bin/
rm ./conan/bin/Qt*.dll

rm -r ./conan/include/**
cp ./include/*.h ./conan/include/

conan export-pkg ./conan_win/conanfile.py project/${version}@ashley/testing -pf . -f
conan upload project/${version}@ashley/testing -r artifactory --all --force
