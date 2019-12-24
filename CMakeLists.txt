cmake_minimum_required(VERSION 3.0)

project(usernameandpasswordvalidator)

add_executable(usernameandpasswordvalidator main.cpp User.cpp)

install(TARGETS usernameandpasswordvalidator RUNTIME DESTINATION bin)
