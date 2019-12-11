[![Codacy Badge](https://api.codacy.com/project/badge/Grade/c949b506abc74ec2a49d462053e77fe8)](https://www.codacy.com/manual/Mihaylov93/BatMon?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=Mihaylov93/BatMon&amp;utm_campaign=Badge_Grade)
[![Build Status](https://travis-ci.org/Mihaylov93/BatMon.svg?branch=master)](https://travis-ci.org/Mihaylov93/BatMon)
# Battery monitoring widget 

![freedoom](https://cdn.discordapp.com/attachments/459401282743173120/476116122622754858/capture_01.png "freedoom")

## BatMon
A widget for Clockwork Pi that displays the battery percentage as a overlay on top of the current window. Clockwork Pi Gameshell has a battery widget on the UI but not while playing games. This is an attempt to solve this.

### Features

It reads the **/sys/class/power_supply/axp20x-battery/uevent** file.

**$ cat /sys/class/power_supply/axp20x-battery/uevent**
```sh
      POWER_SUPPLY_NAME=axp20x-battery
      POWER_SUPPLY_PRESENT=1
      POWER_SUPPLY_ONLINE=1
      POWER_SUPPLY_STATUS=Charging
      POWER_SUPPLY_VOLTAGE_NOW=4186000
      POWER_SUPPLY_CURRENT_NOW=1000
      POWER_SUPPLY_CONSTANT_CHARGE_CURRENT=1200000
      POWER_SUPPLY_CONSTANT_CHARGE_CURRENT_MAX=1200000
      POWER_SUPPLY_HEALTH=Good
      POWER_SUPPLY_VOLTAGE_MAX_DESIGN=4200000
      POWER_SUPPLY_VOLTAGE_MIN_DESIGN=2900000
      POWER_SUPPLY_CAPACITY=100
```

 **It gets the percentage as follows:**

```(voltage_now-voltage_min)/(voltage_max-voltage_min)) * 100```

## Issues

-  twm does not appear to implement extended window manager hints [(EWMH)](https://en.wikipedia.org/wiki/Extended_Window_Manager_Hints).
Some flags like **Qt::WA_X11NetWmWindowTypeDock** might not work for that reason.

-  For the same reason, the hint **Qt::WindowStaysOnTopHint** also doesn´t work, widget doesn´t stay always on top (*It does on other window manager*), a new opened window re-paints on top of it and it gets hidden. A workaround to this is having a timer to hide the widget, update it and repaint it on top of the current active window.

## Building and installation

This project was made with c++ and Qt4 in order to compile it from source you need to install qt4-dev-tools

### Building from source
```sh
 sudo apt-get install qt4-dev-tools
 ```

```sh
qmake BatMon.pro
make
```
### Downloading binary

You can get a precompiled package from [releases.](https://github.com/Mihaylov93/BatMon/releases "releases")

It has Qt4 dependencies we need to solve by installing the libs.

```sh
 $ readelf -d BatMon

Dynamic section at offset 0x3ee0 contains 32 entries:
  Tag        Type                         Name/Value
 0x00000001 (NEEDED)                     Shared library: [libQtGui.so.4]
 0x00000001 (NEEDED)                     Shared library: [libQtCore.so.4]
 0x00000001 (NEEDED)                     Shared library: [libpthread.so.0]
 0x00000001 (NEEDED)                     Shared library: [libstdc++.so.6]
 0x00000001 (NEEDED)                     Shared library: [libm.so.6]
 0x00000001 (NEEDED)                     Shared library: [libgcc_s.so.1]
 0x00000001 (NEEDED)                     Shared library: [libc.so.6]

```

```sh
sudo apt-get install libqtcore4 
sudo apt-get install libqtgui4 
```
Note: If we have the qt4-dev-tools we already have the libs.

#### Installation

To add it to the launcher:

```sh
sudo apt-get install libqtcore4
sudo apt-get install libqtgui4
tar -zxvf BatMon.tar.gz -C /home/cpi/apps/Menu/
```
