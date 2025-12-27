@echo off
g++ copyable_array.cpp -o copyable_array.exe -std=c++11
g++ movable_array.cpp -o movable_array.exe -std=c++11
g++ perfect_forwarding.cpp -o perfect_forwarding.exe -std=c++11
echo [SHELL] Running CopyableArray Demo...
copyable_array.exe
echo.
echo [SHELL] Running MovableArray Demo...
movable_array.exe
echo.
echo [SHELL] Running Perfect Forwarding Demo...
perfect_forwarding.exe
echo.
echo [SHELL] All programs executed.