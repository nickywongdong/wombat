all: rp1dcd c1helper

rp1dcd: rpi1_dcd.cpp
	rm -f rpi1dcd
	g++ rpi1_dcd.cpp -o rpi1dcd -lbluetooth -std=c++11

c1helper: c1helper.cpp
	rm -f c1helper
	g++ c1helper.cpp -o c1helper -std=c++11
