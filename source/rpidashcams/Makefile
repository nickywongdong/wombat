all: rp1dcd c1helper rp2dcd c2helper bchelper

rp1dcd: rpi1_dcd.cpp
	rm -f rpi1dcd
	g++ rpi1_dcd.cpp -o rpi1dcd -lbluetooth -std=c++11

c1helper: c1helper.cpp
	rm -f c1helper
	g++ c1helper.cpp -o c1helper -std=c++11

rp2dcd: rpi2_dcd.cpp
	rm -f rpi2dcd
	g++ rpi2_dcd.cpp -o rpi2dcd -lbluetooth -std=c++11

c2helper: c2helper.cpp
	rm -f c2helper
	g++ c2helper.cpp -o c2helper -std=c++11

bchelper: bchelper.cpp
	rm -f bchelper
	g++ bchelper.cpp -o bchelper -std=c++11
