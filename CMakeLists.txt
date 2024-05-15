cmake_minimum_required(VERSION 3.16)
project(eigen_ipopt)

find_package(Eigen3 REQUIRED)
include_directories(${EIGEN3_INCLUDE_DIR})

# find_package(Ipopt REQUIRED)

find_package(PythonLibs 3 REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})

set(SRC_PATH ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(HEAD_PATH ${CMAKE_CURRENT_SOURCE_DIR}/include)

# 使用通配符匹配源文件
# file(GLOB SOURCES "${SRC_PATH}/*.cc")

include_directories(${HEAD_PATH})

add_executable(eigen_demo ${SRC_PATH}/hello_eigen.cc)
target_link_libraries(eigen_demo ${PYTHON_LIBRARIES})

add_executable(ipopt_demo ${SRC_PATH}/hello_ipopt.cc)
target_link_libraries(ipopt_demo ipopt)
