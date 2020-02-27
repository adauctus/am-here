# am-here
Write to a file that the computer is still running

## Installation
1) Run CMake Build
2) Open System Preferences -> Security -> Full Disk Access and click the Lock
3) Drag your binary to the Full Disk Access window (allowing it full disk access)
4) Edit the plist file and change the PATH/TO to the path to the binary
5) Move the plist to ~/Library/LaunchAgents
6) run `launchctl load -w com.flattmattfanclub.am-here.plist`
