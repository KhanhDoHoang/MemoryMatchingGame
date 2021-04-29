# CMakeList.txt : CMake project for TestNana, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.0)

project ("TestNana")


add_definitions(-D_SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING)
# Add source to this project's executable.
add_executable (TestNana "Sample nana code/TestNana.cpp" "Sample nana code/TestNana.h" "Sample nana code/Label.cpp" "Sample nana code/Cal.cpp" "Sample nana code/Dragme.cpp" "Main.cpp" "Sample nana code/Clicl.cpp" "Game.h" "Game.cpp" "Card.cpp" "Card.h" "Image.h")

#This line fixes the /MDd problem on slide #9
#set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS_DEBUG} NANA_ENABLE_AUDIO")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS_DEBUG} NANA_ENABLE_AUDIO")
#C:\Users\katie\source\repos\TestNana\nana_1.7.4\nana\include
target_include_directories(TestNana PUBLIC "C:\\Users\\katie\\source\\repos\\TestNana\\nana_1.7.4\\nana\\include")
target_link_directories(TestNana PUBLIC "C:\\Users\\katie\\source\\repos\\TestNana\\nana_1.7.4\\nana\\build\\bin")
target_link_libraries(TestNana "nana_v142_Debug_x64")
add_definitions(-DNANA_ENABLE_AUDIO)