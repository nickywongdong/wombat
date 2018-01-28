testapp: dcd dld dcdltestapparatus.cpp
	g++ dcdltestapparatus.cpp -lpthread -o testapp.axolotl

dcd: dcd.cpp
	g++ dcd.cpp -o dcd.axolotl -lpthread -lboost_system -lboost_filesystem

dld: dld.cpp
	g++ dld.cpp -o dld.axolotl -lpthread

fstest: test.cpp
	g++ test.cpp -o test.prog -lboost_system -lboost_filesystem
