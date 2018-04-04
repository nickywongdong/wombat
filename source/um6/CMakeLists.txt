# @author Isaac Jesus da Silva - ROBOFEI-HT - FEI
# @version V0.0.1
# @created 24/08/2015
# @Modified 24/08/2015 
#
# 
# Para Help acesse http://www.cmake.org/cmake/help/v2.8.0/cmake.html#command:link_directories

find_package( Boost REQUIRED )

include_directories(
  include
  ${Boost_INCLUDE_DIRS}
  ./include/um6
  ./serial/include

)

include_directories(include)
add_library(comms SHARED src/comms.cpp)
install(TARGETS comms DESTINATION ./lib)
add_library(registers SHARED src/registers.cpp)
install(TARGETS registers DESTINATION ./lib)

add_executable(imu src/imu.cpp)
add_dependencies(imu serial comms registers ${Boost_LIBRARIES})

target_link_libraries(imu serial comms registers rt pthread ${Boost_LIBRARIES})

install(TARGETS imu DESTINATION ./)


