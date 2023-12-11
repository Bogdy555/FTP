export Configuration=Debug
export PlatformShortName=x86
export CPP_FLAGS="-c -std=c++20 -DUNICODE -D_UNICODE -m32 -DDEBUG -D_DEBUG"
export LNK_FLAGS="-m32"
export AR_FLAGS="-r -c -s"

"./Build.sh"
