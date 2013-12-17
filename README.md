debugconsole
============

A simple cocos2d-x console to run remote lua scripts

## Installation and usage
* Copy the 'console' folder to your project's source folder (e.g. Classes folder in xcode)
* Edit console/command.cpp to integrate your code with the already available commands
* Add a LuaConsole node to your cocos2d scene

```
#include "console/luaconsole.h"
...
addChild(pix2d_console::LuaConsole::create());
```

* Compile and launch your application to your device
* If your ios device is attached via usb then start the usbmuxd proxy

```
python tcprelay.py 8080
```

* Now run the concli.py script to 

## Add new commands
By now the console has only one simple but quite useful command to remolty update sprite-sheets.

```
./concli.py --plist ../path-to-your-file.plist
```
To add new commands:
* Implement the new commands in command.h and command.cpp
* Edit command.pkg to reflect the new changes
* run the tolua.py script
    python tolua.py path-to-command.pkg
* Compile and re-launch the console
* Edit concli.py to add your new commands

## Requirements

* cocos2d-x 2.0.4
* tolua++ (provided with cocos2d-x)
* python

## License

MIT License

tcprelay.py and usbmux.py are thrid-party library and are licensed under the GNU Lesser General Public
License. Please check the github repository at https://github.com/libimobiledevice/libusbmuxd.
