mkdir "./Binaries/"

mkdir "./Binaries/FTP_API/"
mkdir "./Binaries/FTP_Server/"
mkdir "./Binaries/FTP_Client/"

mkdir "./Binaries/FTP_API/$Configuration/"
mkdir "./Binaries/FTP_Server/$Configuration/"
mkdir "./Binaries/FTP_Client/$Configuration/"

mkdir "./Binaries/FTP_API/$Configuration/$PlatformShortName/"
mkdir "./Binaries/FTP_Server/$Configuration/$PlatformShortName/"
mkdir "./Binaries/FTP_Client/$Configuration/$PlatformShortName/"

mkdir "./Objects/"

mkdir "./Objects/FTP_API/"
mkdir "./Objects/FTP_Server/"
mkdir "./Objects/FTP_Client/"

mkdir "./Objects/FTP_API/$Configuration/"
mkdir "./Objects/FTP_Server/$Configuration/"
mkdir "./Objects/FTP_Client/$Configuration/"

mkdir "./Objects/FTP_API/$Configuration/$PlatformShortName/"
mkdir "./Objects/FTP_Server/$Configuration/$PlatformShortName/"
mkdir "./Objects/FTP_Client/$Configuration/$PlatformShortName/"



g++ $CPP_FLAGS "./FTP_API/Sources/FTP_API_Networking.cpp" -o "./Objects/FTP_API/$Configuration/$PlatformShortName/FTP_API_Networking.o"
g++ $CPP_FLAGS "./FTP_API/Sources/FTP_API_Multithreading.cpp" -o "./Objects/FTP_API/$Configuration/$PlatformShortName/FTP_API_Multithreading.o"

pushd "./Objects/FTP_API/$Configuration/$PlatformShortName/"

ar $AR_FLAGS "../../../../Binaries/FTP_API/$Configuration/$PlatformShortName/FTP_API.a" "./FTP_API_Networking.o"
ar $AR_FLAGS "../../../../Binaries/FTP_API/$Configuration/$PlatformShortName/FTP_API.a" "./FTP_API_Multithreading.o"

popd



g++ $CPP_FLAGS "./FTP_Server/Sources/FTP_Server_EntryPoint.cpp" -I "$PWD/FTP_API/Headers/" -o "./Objects/FTP_Server/$Configuration/$PlatformShortName/FTP_Server_EntryPoint.o"

pushd "./Objects/FTP_Server/$Configuration/$PlatformShortName/"

g++ $LNK_FLAGS "./FTP_Server_EntryPoint.o" "../../../../Binaries/FTP_API/$Configuration/$PlatformShortName/FTP_API.a" -o "../../../../Binaries/FTP_Server/$Configuration/$PlatformShortName/FTP_Server.out"

popd



g++ $CPP_FLAGS "./FTP_Client/Sources/FTP_Client_EntryPoint.cpp" -I "$PWD/FTP_API/Headers/" -o "./Objects/FTP_Client/$Configuration/$PlatformShortName/FTP_Client_EntryPoint.o"

pushd "./Objects/FTP_Client/$Configuration/$PlatformShortName/"

g++ $LNK_FLAGS "./FTP_Client_EntryPoint.o" "../../../../Binaries/FTP_API/$Configuration/$PlatformShortName/FTP_API.a" -o "../../../../Binaries/FTP_Client/$Configuration/$PlatformShortName/FTP_Client.out"

popd
