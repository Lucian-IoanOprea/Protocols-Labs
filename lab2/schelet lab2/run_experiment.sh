#!/bin/bash

SPEED=1
DELAY=1
LOSS=0
CORRUPT=0

{
    killall link
    killall recv
    killall send
} &> /dev/null

./link_emulator/link speed=$SPEED delay=$DELAY loss=$LOSS corrupt=$CORRUPT &> /dev/null &
sleep 1
./recv test1 test2 &
sleep 1 

./send test1 test2 

sleep 2
echo "Finished transfer, checking files"
diff test1 test1-receiver
diff test2 test2-receiver
