cmake_minimum_required(VERSION 3.15)

project(httpserver LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

SET(CMAKE_INSTALL_PREFIX $<TARGET_FILE_DIR:${PROJECT_NAME}> CACHE PATH "Initial cahe" FORCE)

set(CMAKE_AUTOMOC ON)

find_package(Qt5 COMPONENTS Core Network REQUIRED)

set(project_headers 
myServer.h)

set(project_sources 
main.cpp 
myServer.cpp)

add_executable(${PROJECT_NAME} WIN32
	${project_headers} 
	${project_sources})

target_link_libraries(${PROJECT_NAME} 
PUBLIC
Qt5::Core
Qt5::Network)

install(FILES $<TARGET_FILE:Qt5::Core> DESTINATION $<TARGET_FILE_DIR:${PROJECT_NAME}>)
install(FILES $<TARGET_FILE:Qt5::Network> DESTINATION $<TARGET_FILE_DIR:${PROJECT_NAME}>)