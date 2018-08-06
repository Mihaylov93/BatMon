BASENAME=$(dirname $0)
while true; do
    $BASENAME/BatMon & APP_PID=$!
    sleep 29s
    kill $APP_PID
    sleep 1s
done
