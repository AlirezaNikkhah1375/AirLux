#!/bin/bash
while true
do
    # Generate a random integer between 1 and 100
    random_int=$((1 + $RANDOM % 10000))

    # Send the integer to localhost:3000
    curl -X POST -d 'data=$random_int' http://localhost:3000

    echo "Sleep for 3 seconds . . ."
    # Pause for 3 seconds
    sleep 3
done
