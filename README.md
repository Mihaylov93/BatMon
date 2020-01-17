# Battery monitoring widget

[![Codacy Badge](https://api.codacy.com/project/badge/Grade/c949b506abc74ec2a49d462053e77fe8)](https://www.codacy.com/manual/Mihaylov93/BatMon?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=Mihaylov93/BatMon&amp;utm_campaign=Badge_Grade)
[![Build Status](https://travis-ci.org/Mihaylov93/BatMon.svg?branch=master)](https://travis-ci.org/Mihaylov93/BatMon)

![freedoom](https://cdn.discordapp.com/attachments/459401282743173120/476116122622754858/capture_01.png "freedoom")

## BatMon

A widget for Clockwork Pi that displays the battery percentage as a overlay on top of the current window. Clockwork Pi Gameshell has a battery widget on the UI but not while playing games. This is an attempt to solve this.

### Features

Initially it read **/sys/class/power_supply/axp20x-battery/uevent** file and computed a percentage from the data extracted. 
Currently **upower** is used to get the percentage from **/org/freedesktop/UPower/devices/battery_axp20x_battery**

Although old way is still present as a fallback option, if the device doesn´t have upower or running it doesnt give a proper result,
percentage display will be built from **/sys/class/power_supply/axp20x-battery/uevent** like below.

#### $ cat /sys/class/power_supply/axp20x-battery/uevent

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

- twm does not appear to implement extended window manager hints [(EWMH)](https://en.wikipedia.org/wiki/Extended_Window_Manager_Hints).
Some flags like **Qt::WA_X11NetWmWindowTypeDock** might not work for that reason.

- For the same reason, the hint **Qt::WindowStaysOnTopHint** also doesn´t work, widget doesn´t stay always on top (*It does on other window manager*), a new opened window re-paints on top of it and it gets hidden. A workaround to this is having a timer to hide the widget, update it and repaint it on top of the current active window.

## Building and installation

This project was made with c++ and Qt5 in order to compile it from source you need to have Qt5 and QMake.

### Building from source

```sh
qmake BatMon.pro
make
```

### Downloading binary

You can get a precompiled package from [releases.](https://github.com/Mihaylov93/BatMon/releases "releases")

It has Qt5 dependencies that should be preinstalled in the latest OS, if for some reason it doesn´t run
because of a library missing you can check with **readelf -f** the required libraries.

```sh
$ readelf -d BatMon

Dynamic section at offset 0x5ed0 contains 34 entries:
  Tag        Type                         Name/Value
 0x00000001 (NEEDED)                     Shared library: [libQt5Widgets.so.5]
 0x00000001 (NEEDED)                     Shared library: [libQt5Gui.so.5]
 0x00000001 (NEEDED)                     Shared library: [libQt5Core.so.5]
 0x00000001 (NEEDED)                     Shared library: [libGLESv2.so.2]
 0x00000001 (NEEDED)                     Shared library: [libpthread.so.0]
 0x00000001 (NEEDED)                     Shared library: [libstdc++.so.6]
 0x00000001 (NEEDED)                     Shared library: [libm.so.6]
 0x00000001 (NEEDED)                     Shared library: [libgcc_s.so.1]
 0x00000001 (NEEDED)                     Shared library: [libc.so.6]

```

```sh
sudo apt-get install libqtcore5 libqtgui5 
```

#### Installation

To add it to the launcher:

```sh
tar -zxvf BatMon-0.5.tar.gz -C /home/cpi/apps/Menu/
```
