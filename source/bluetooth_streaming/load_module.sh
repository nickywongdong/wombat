#!/bin/bash

pactl unload-module module-loopback
pactl load-module module-loopback
