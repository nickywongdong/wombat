#!/bin/bash


#pacmd <<'END'
#    list-sinks
#    list-sources
#
#    load_module module-loopback source=
#END

pacmd list-sources
pacmd list-sinks

pacmd load-module module-loopback source=bluez_source.xxxx sink=alsa_output.pci-xxxx
