cmake_minimum_required(VERSION 3.10.2)

project(sign_up_car CXX)

  
# set(Boost_USE_MULTITHREADED ON)
   
# find_package(Threads REQUIRED)
# find_package(OpenSSL REQUIRED)
# find_package(Boost COMPONENTS system REQUIRED)
# find_package(CURL)
# include_directories(${OPENSSL_INCLUDE_DIR} ${Boost_INCLUDE_DIR})
# if (CURL_FOUND)
# include_directories(${CURL_INCLUDE_DIRS})
# add_definitions(-DHAVE_CURL)
# endif()
    
add_executable(sign_up_car sign_up_car.cpp main.cpp db.cpp)

add_executable(lunch_db lunch_db.cpp db.cpp)
    
# add_executable(tests test.cpp db.cpp)
    
# find_package(GTest CONFIG REQUIRED)
# target_link_libraries(tests PRIVATE GTest::gmock GTest::gtest GTest::gmock_main GTest::gtest_main)


find_package(unofficial-sqlite3 CONFIG REQUIRED)
target_link_libraries(sign_up_car PRIVATE unofficial::sqlite3::sqlite3)
target_link_libraries(lunch_db PRIVATE unofficial::sqlite3::sqlite3)

set_target_properties(
sign_up_car
PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)

set_target_properties(
lunch_db
PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)

if (MSVC)
    add_compile_options(/W4 /WX)
    else()
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()