all:
	rm -f datad
	make datad
	rm -f dashcamd
	make dashcamd
	rm -f daemon_launcher
	make daemon_launcher
	rm -f datad_pyhelper
	make datad_pyhelper

daemon_launcher: datad dashcamd daemon_manager.cpp
	g++ daemon_manager.cpp -o daemon_launcher -lpthread -lboost_system -lboost_filesystem -lcryptopp -std=c++11

dashcamd: dashcam_logger.cpp
	g++ dashcam_logger.cpp -o dashcamd -lpthread -lboost_system -lboost_filesystem -lcryptopp -std=c++11

datad: data_logger.cpp datad_pyhelper
	g++ data_logger.cpp -o datad -lpthread -lboost_system -lboost_filesystem -lcryptopp -std=c++11

datad_pyhelper: data_logger_pyhelper.cpp
	g++ data_logger_pyhelper.cpp -o datad_pyhelper -lpthread -lboost_system -lboost_filesystem -lcryptopp -std=c++11
