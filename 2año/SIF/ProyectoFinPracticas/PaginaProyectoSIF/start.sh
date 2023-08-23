#/bin/bash

php -S localhost:8000 &

sleep 5

/usr/bin/firefox -new-window localhost:8000

pid=$(pidof php)

kill $pid
