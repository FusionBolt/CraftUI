project(player)

find_package(FFmpeg REQUIRED
        COMPONENTS avformat avutil swscale swresample
        OPTIONAL_COMPONENTS avcodec)

add_library(player
        Player.h Player.cpp)

target_include_directories(player
        PUBLIC
        ${FFMPEG_INCLUDE_DIRS})

target_link_libraries(player
        ${FFMPEG_LIBRARY})