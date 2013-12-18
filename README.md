debugconsole
============

A simple cocos2d-x console for running remote lua scripts

## Description

debugconsole is a simple server-client implementation which allows remote access to a cocos2dx application for development/debugging purpose. The goal is to be able to remotely run lua scripts at runtime and to avoid  compiling/packaging/launching the application when it's not neceserry (e.g. updating a resource like spritesheet, sounds...).

The server part is a cocos2dx CCNode listenning on a network socket for lua script requests. The client part is a simple python script which will construct the lua script and send it to the console.

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
* Now you can execute client/concli.py to access your game remotely

# iOS devices

If your iPad/iPhone is attached to your computer via usb then start the usbmuxd proxy before running the client script.

```
python tcprelay.py 8080
```
## Adding new commands
By now the console has only one simple but quite useful command to remotely update sprite-sheets.

```
./concli.py --plist ../path-to-your-file.plist
```
To add new commands:
* Add new command methods in command.h and command.cpp
* Edit command.pkg to reflect the changes (see [tolua++ doc](http://www.codenix.com/~tolua/tolua++.html))
* run the tolua.py script

```
    python tolua.py path-to-command.pkg
```
* Compile and re-launch the console
* Edit concli.py to add your new commands

## Configuration
Both console and client's ip and port can be configured. By default the port 8080 is used.
* Edit concly.conf to configure the client's network parameters
* The lua console's ip and port can be provided to the create method

```
LuaConsole::create("0.0.0.0",8080);
```
## License

MIT License

tcprelay.py and usbmux.py are part of the awesome libusbmuxd library and are licensed under the GNU Lesser General Public
License. Please have a look at the [libusbmuxd's github repository](https://github.com/libimobiledevice/libusbmuxd).
