# Install script for directory: /home/nvidia/axolotl/navit/navit

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "RelWithDebInfo")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/navit" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/navit")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/navit"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE FILES "/home/nvidia/axolotl/navit-build/navit/navit")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/navit" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/navit")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/navit")
    endif()
  endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/navit" TYPE FILE PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ FILES "/home/nvidia/axolotl/navit-build/navit/navit.xml")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/nvidia/axolotl/navit-build/navit/support/shapefile/cmake_install.cmake")
  include("/home/nvidia/axolotl/navit-build/navit/font/freetype/cmake_install.cmake")
  include("/home/nvidia/axolotl/navit-build/navit/graphics/gtk_drawing_area/cmake_install.cmake")
  include("/home/nvidia/axolotl/navit-build/navit/graphics/opengl/cmake_install.cmake")
  include("/home/nvidia/axolotl/navit-build/navit/gui/gtk/cmake_install.cmake")
  include("/home/nvidia/axolotl/navit-build/navit/vehicle/gpsd/cmake_install.cmake")
  include("/home/nvidia/axolotl/navit-build/navit/speech/cmdline/cmake_install.cmake")
  include("/home/nvidia/axolotl/navit-build/navit/graphics/null/cmake_install.cmake")
  include("/home/nvidia/axolotl/navit-build/navit/osd/core/cmake_install.cmake")
  include("/home/nvidia/axolotl/navit-build/navit/vehicle/demo/cmake_install.cmake")
  include("/home/nvidia/axolotl/navit-build/navit/vehicle/file/cmake_install.cmake")
  include("/home/nvidia/axolotl/navit-build/navit/gui/internal/cmake_install.cmake")
  include("/home/nvidia/axolotl/navit-build/navit/map/binfile/cmake_install.cmake")
  include("/home/nvidia/axolotl/navit-build/navit/map/filter/cmake_install.cmake")
  include("/home/nvidia/axolotl/navit-build/navit/map/mg/cmake_install.cmake")
  include("/home/nvidia/axolotl/navit-build/navit/map/shapefile/cmake_install.cmake")
  include("/home/nvidia/axolotl/navit-build/navit/map/textfile/cmake_install.cmake")
  include("/home/nvidia/axolotl/navit-build/navit/map/csv/cmake_install.cmake")
  include("/home/nvidia/axolotl/navit-build/navit/fib-1.1/cmake_install.cmake")
  include("/home/nvidia/axolotl/navit-build/navit/maptool/cmake_install.cmake")
  include("/home/nvidia/axolotl/navit-build/navit/icons/cmake_install.cmake")
  include("/home/nvidia/axolotl/navit-build/navit/maps/cmake_install.cmake")

endif()

