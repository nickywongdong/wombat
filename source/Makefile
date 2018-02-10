rundaemons: dcd dld dcdl_manager.cpp
	g++ dcdl_manager.cpp -o daemon_manager -lpthread -lboost_system -lboost_filesystem -lcryptopp

dcd: dcd.cpp
	g++ dcd.cpp -o dcd -lpthread -lboost_system -lboost_filesystem -lcryptopp

dld: dld.cpp
	g++ dld.cpp -o dld -lpthread -lboost_system -lboost_filesystem -lpython -lcryptopp
