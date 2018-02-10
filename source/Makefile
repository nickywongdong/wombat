rundaemons: dcd dld dcdl_manager.cpp
	g++ dcdl_manager.cpp -o rundaemons.axolotl -lpthread -lboost_system -lboost_filesystem -lcryptopp

dcd: dcd.cpp
	g++ dcd.cpp -o dcd.axolotl -lpthread -lboost_system -lboost_filesystem -lcryptopp

dld: dld.cpp
	g++ dld.cpp -o dld.axolotl -lpthread -lboost_system -lboost_filesystem -lpython -lcryptopp

fstest: test.cpp
	g++ test.cpp -o test.prog -lboost_system -lboost_filesystem -lcryptopp
