@echo off
cls
if not exist build mkdir build
cd build
cmake -G "MinGW Makefiles" ..

make 
cd ..
.\Server.exe "config/config.json"