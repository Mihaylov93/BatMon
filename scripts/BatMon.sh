#!/bin/bash
APP_ID=$(ps -C BatMon --no-header --format 'pid')
if [ -n "${APP_ID}" ]; then
  echo "Stopping instance $APP_ID"
  kill "${APP_ID}"
else
# You can change the refresh time in seconds 
./BatMon 30 &
fi
exit