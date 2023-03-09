mkdir build
cd build
pip3 install conan

conan install .. --build=missing  -c tools.system.package_manager:mode=install -c tools.system.package_manager:sudo=True
cmake ..
cmake --build .
cd bin
move .\r-type_server.exe ..\..\bin\windows\
move .\r-type_client.exe ..\..\bin\windows\