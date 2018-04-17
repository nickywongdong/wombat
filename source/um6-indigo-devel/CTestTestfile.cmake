# CMake generated Testfile for 
# Source directory: /home/nvidia/wombat/source/um6-indigo-devel
# Build directory: /home/nvidia/wombat/source/um6-indigo-devel
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(_ctest_um6_gtest_um6_test_registers "/home/nvidia/wombat/source/um6-indigo-devel/catkin_generated/env_cached.sh" "/usr/bin/python" "/opt/ros/kinetic/share/catkin/cmake/test/run_tests.py" "/home/nvidia/wombat/source/um6-indigo-devel/test_results/um6/gtest-um6_test_registers.xml" "--return-code" "/home/nvidia/wombat/source/um6-indigo-devel/devel/lib/um6/um6_test_registers --gtest_output=xml:/home/nvidia/wombat/source/um6-indigo-devel/test_results/um6/gtest-um6_test_registers.xml")
add_test(_ctest_um6_gtest_um6_test_comms "/home/nvidia/wombat/source/um6-indigo-devel/catkin_generated/env_cached.sh" "/usr/bin/python" "/opt/ros/kinetic/share/catkin/cmake/test/run_tests.py" "/home/nvidia/wombat/source/um6-indigo-devel/test_results/um6/gtest-um6_test_comms.xml" "--return-code" "/home/nvidia/wombat/source/um6-indigo-devel/devel/lib/um6/um6_test_comms --gtest_output=xml:/home/nvidia/wombat/source/um6-indigo-devel/test_results/um6/gtest-um6_test_comms.xml")
add_test(_ctest_um6_roslint_package "/home/nvidia/wombat/source/um6-indigo-devel/catkin_generated/env_cached.sh" "/usr/bin/python" "/opt/ros/kinetic/share/catkin/cmake/test/run_tests.py" "/home/nvidia/wombat/source/um6-indigo-devel/test_results/um6/roslint-um6.xml" "--working-dir" "/home/nvidia/wombat/source/um6-indigo-devel" "--return-code" "/opt/ros/kinetic/share/roslint/cmake/../../../lib/roslint/test_wrapper /home/nvidia/wombat/source/um6-indigo-devel/test_results/um6/roslint-um6.xml make roslint_um6")
subdirs(gtest)
