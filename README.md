# Battery monitoring widget

![CaveStory](https://cdn.discordapp.com/attachments/459401282743173120/475803474832130097/w.png)

It reads the **/sys/class/power_supply/axp20x-battery/uevent** file.

``` cat /sys/class/power_supply/axp20x-battery/uevent
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

###It gets the percentage as follows:

```(voltage_now-voltage_min)/(voltage_max-voltage_min)) * 100```

## Issues:

twm does not appear to implement extended window manager hints [(EWMH)](https://en.wikipedia.org/wiki/Extended_Window_Manager_Hints).
Some flags like **WA_X11NetWmWindowTypeDock** might not work for that reason.


#### It glitches:

![Fredoom](https://cdn.discordapp.com/attachments/459401282743173120/475803629039910942/capture_01.png)




