daemon_launcher: datad dashcamd daemon_manager.cpp
	g++ daemon_manager.cpp -o daemon_launcher -lpthread -lboost_system -lboost_filesystem -lcryptopp -std=c++11

dashcamd: dashcam_logger.cpp
	g++ dashcam_logger.cpp -o dashcamd -lpthread -lboost_system -lboost_filesystem -lcryptopp -std=c++11

datad: data_logger.cpp
	g++ data_logger.cpp -o datad -lpthread -lboost_system -lboost_filesystem -lpython -lcryptopp -std=c++11
