#!/usr/bin/expect -f
set prompt "#"
spawn bluetoothctl
sleep 1
expect -re $prompt
sleep 1
send "agent NoInputNoOutput\r"
sleep 2
expect "Agent registered"
send "default-agent\r"
expect -re $prompt
sleep 20
#interact

#set prompt "Authorize service
#o):"
expect -re $prompt
send "yes\r"
sleep 1
expect -re $prompt
send "yes\r"

#set prompt "#"
expect -re $prompt
send "exit\r"
expect eof
