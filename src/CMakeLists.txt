cmake_minimum_required(VERSION 3.0)

project(PuppetMaster)

set(AC SynaesthetiQ-audiocapture/src)
set(LED SynaesthetiQ-LED-Library/src/SynaesthetiQ)
set(EF EnvelopeFollowing/src)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -fsanitize=address -fno-omit-frame-pointer")
set(SOURCES main.cpp Visualiser/Visualiser.cpp ${LED}/synaesthetiq.cpp ${AC}/AudioCapture/PingPongBuffer.cpp ${AC}/AudioCapture/AudioCapture.cpp ${AC}/GenreClassification/GenreClassifier.cpp ${AC}/FFTProcessor.cpp ${EF}/EnvelopeFollower.cpp)
find_package( CURL REQUIRED )
find_package(iir REQUIRED)

add_executable(${PROJECT_NAME} ${SOURCES})

include_directories(/usr/local/lib ${LED} ${AC}/AudioCapture ${AC}/GenreClassification ${AC}/GenreClassification/cpp_genre_classifier)

target_link_libraries(${PROJECT_NAME} /usr/local/lib/libws2811.so asound stdc++ pthread fftw3 CURL::libcurl iir::iir)
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "${PROJECT_NAME}.exe")

set(HEADERS Visualiser/Visualiser.hpp ${LED}/synaesthetiq.hpp ${LED}/Colour.hpp ${EF}/EnvelopeFollower.hpp)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})