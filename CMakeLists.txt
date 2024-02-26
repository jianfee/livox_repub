cmake_minimum_required(VERSION 3.8)
project(livox_repub)

# Default to C++14
if (NOT CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 14)
endif ()

if (CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    add_compile_options(-Wall -Wextra -Wpedantic)
endif ()

# Find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(pcl_ros REQUIRED)
find_package(pcl_conversions  REQUIRED)
find_package(livox_ros_driver2 REQUIRED)

# Include directories

# Declare a C++ executable
add_executable(${PROJECT_NAME} livox_repub.cpp)
ament_target_dependencies(${PROJECT_NAME}
        rclcpp
        sensor_msgs
        pcl_ros
        pcl_conversions
        livox_ros_driver2
)


# Install targets
install(TARGETS ${PROJECT_NAME}
        DESTINATION lib/${PROJECT_NAME})

install(
        DIRECTORY launch
        DESTINATION share/${PROJECT_NAME}
)

# Export dependencies
ament_export_dependencies(rclcpp sensor_msgs pcl_ros pcl_conversions livox_ros_driver2)

ament_package()
