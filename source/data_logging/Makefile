all: dashcamd datad datad_pyhelper daemon_manager record_helper backup_cam_helper
	cp hashkey ~/axolotl/hashkey

daemon_launcher: daemon_manager daemon_launcher.cpp
	g++ daemon_launcher.cpp -o daemon_launcher

daemon_manager: datad dashcamd daemon_manager.cpp
	rm -f daemon_manager
	g++ daemon_manager.cpp -o daemon_manager -lpthread -lboost_system -lboost_filesystem -lcryptopp -std=c++11

dashcamd: dashcam_logger.cpp
	rm -f dashcamd
	g++ dashcam_logger.cpp -o dashcamd -lpthread -lbluetooth -lboost_system -lboost_filesystem -lcryptopp -std=c++11

datad: data_logger.cpp datad_pyhelper
	rm -f datad
	g++ data_logger.cpp -o datad -lpthread -lboost_system -lboost_filesystem -lcryptopp -std=c++11

datad_pyhelper: data_logger_pyhelper.cpp
	rm -f datad_pyhelper
	g++ data_logger_pyhelper.cpp -o datad_pyhelper -lpthread -lboost_system -lboost_filesystem -lcryptopp -std=c++11

record_helper: record_helper.cpp
	rm -f record_helper
	g++ record_helper.cpp -o record_helper -std=c++11

backup_cam_helper: backup_cam_helper.cpp
	rm -f backup_cam_helper
	g++ backup_cam_helper.cpp -o backup_cam_helper -std=c++11

clean:
	rm -f daemon_launcher
	rm -f daemon_manager
	rm -f datad
	rm -f datad_pyhelper
	rm -f	dashcamd
	rm -f record_helper
	rm -f backup_cam_helper

fresh: clean all
	#rm -f um6/imu
	cd um6
	make
	cd ..
