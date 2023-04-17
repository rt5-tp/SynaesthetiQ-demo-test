cmake_minimum_required(VERSION 3.0)

project(Demo-test)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

set(AC SynaesthetiQ-audiocapture/src)
set(LED SynaesthetiQ-LED-Library/src/SynaesthetiQ)
set(EF EnvelopeFollowing/src)

set(SOURCES main.cpp Visualiser/Visualiser.cpp ${LED}/synaesthetiq.cpp ${AC}/AudioCapture/PingPongBuffer.cpp ${AC}/AudioCapture/AudioCapture.cpp ${AC}/GenreClassification/GenreClassifier.cpp ${AC}/FFTProcessor.cpp ${CMAKE_CURRENT_SOURCE_DIR}/${EF}/EnvelopeFollower.cpp)
find_package(CURL REQUIRED)
find_package(iir REQUIRED)

add_executable(${PROJECT_NAME} ${SOURCES})

include_directories(/usr/local/lib ${LED} ${AC}/AudioCapture ${AC}/GenreClassification ${AC}/GenreClassification/cpp_genre_classifier)

target_link_libraries(${PROJECT_NAME} /usr/local/lib/libws2811.so asound stdc++ pthread fftw3 CURL::libcurl iir::iir)
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "${PROJECT_NAME}.exe")

set(HEADERS Visualiser/Visualiser.hpp ${LED}/synaesthetiq.hpp ${LED}/Colour.hpp ${EF}/EnvelopeFollower.hpp)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Find Doxygen and configure it
find_package(Doxygen)
if(DOXYGEN_FOUND)
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
    message("Doxygen build started")

    add_custom_target(doc_doxygen ALL
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM)
else(DOXYGEN_FOUND)
    message("Doxygen needs to be installed to generate the documentation")
endif(DOXYGEN_FOUND)
