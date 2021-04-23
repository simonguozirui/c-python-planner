cmake_minimum_required(VERSION 3.10)
project(FrenetOptimalTrajectory)


set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_FLAGS "-march=native -I -Ofast -pthread -Wall -DQT_NO_VERSION_TAGGING")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -O0")

find_package(Qt5Widgets REQUIRED)
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Eigen3)

if(Eigen3_FOUND)
    set(CUSTOM_EIGEN ${EIGEN3_INCLUDE_DIR})
else()
    find_package(Eigen)
    set(CUSTOM_EIGEN ${EIGEN_INCLUDE_DIR})
endif()

include_directories(.)
include_directories(
        ${CUSTOM_EIGEN}
)

# include_directories("/usr/include/python3.8") # for /usr/include/python3.8/structmember.h

add_library(FrenetOptimalTrajectory STATIC
            AnytimeFrenetPlanner.cpp
            AnytimeFrenetPlanner.h)

add_executable(FrenetOptimalTrajectoryTest
            main.cpp
            AnytimeFrenetPlanner.cpp
            AnytimeFrenetPlanner.h
)

# target_link_libraries(FrenetOptimalTrajectory Eigen3::Eigen Qt5::Widgets Qt5::Gui)
target_link_libraries(FrenetOptimalTrajectory Eigen3::Eigen Qt5::Core Qt5::Gui Qt5::Widgets)
target_link_libraries(FrenetOptimalTrajectoryTest Eigen3::Eigen Qt5::Widgets Qt5::Gui)


