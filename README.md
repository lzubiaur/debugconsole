debugconsole
============

A simple cocos2d-x console to run remote lua scripts

## Description

debugconsole is a simple network server-client implementation which allows remote access to a cocos2dx application for development/debugging purpose. The goal is to be able to remotely run lua scripts at runtime and to avoid  compiling/packaging/launchimg the application when it's not neceserry (e.g. updating a resource like spritesheet, sounds...).

The server part is a cocos2dx CCNode listenning for lua script requests on a network socket. The client part is a simple python script which will construct the lua script and send it to the console.

## Requirements

* cocos2d-x 2.0.4
* lua api (provided with cocos2d-x)
* tolua++ (provided with cocos2d-x)
* python

## Installation and usage
* Copy the 'console' folder to your project's source folder (e.g. Classes folder in xcode)
* Edit console/command.cpp to integrate your code with the already available commands
* Add a LuaConsole node to your cocos2d scene

```
#include "console/luaconsole.h"
...
addChild(pix2d_console::LuaConsole::create());
```
* Compile and launch your application
* Now you can execute client/concli.py to access your game remotly

# iOS devices

If your iPad/iPhone is attached to your computer via usb then start the usbmuxd proxy before running the client script.

```
python tcprelay.py 8080
```
## Adding new commands
By now the console has only one simple but quite useful command to remolty update sprite-sheets.

```
./concli.py --plist ../path-to-your-file.plist
```
To add new commands:
* Implement the new commands in command.h and command.cpp
* Edit command.pkg to reflect the new changes
* run the tolua.py script

```
    python tolua.py path-to-command.pkg
```
* Compile and re-launch the console
* Edit concli.py to add your new commands

## Configuration
Both console and client's ip and port can be configured. By default the port 8080 is used.
The python script can be configured by editing the concly.conf file. 
* Edit concly.conf to configure the client's network parameters
* Create the 

## License

MIT License

tcprelay.py and usbmux.py are thrid-party library and are licensed under the GNU Lesser General Public
License. Please check the github repository at https://github.com/libimobiledevice/libusbmuxd.
