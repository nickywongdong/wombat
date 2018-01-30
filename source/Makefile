testapp: dcd dld dcdl_tester.cpp
	g++ dcdl_tester.cpp -o testapp.axolotl -lpthread -lboost_system -lboost_filesystem
	mv *.axolotl runnable

dcd: dcd.cpp
	g++ dcd.cpp -o dcd.axolotl -lpthread -lboost_system -lboost_filesystem

dld: dld.cpp
	g++ dld.cpp -o dld.axolotl -lpthread -lboost_system -lboost_filesystem

fstest: test.cpp
	g++ test.cpp -o test.prog -lboost_system -lboost_filesystem
