cmake_minimum_required(VERSION 3.14)
project(GWUI)

set(VERSION 1.0)
set(DESCRIPTION "GWUI 1.0 version")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMake/Modules" ${CMAKE_MODULE_PATH})

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})
find_package(SDL2IMAGE REQUIRED)
include_directories(${SDL2_TTF_INCLUDE_DIR})
find_package(SDL2MIXER REQUIRED)
include_directories(${SDL2_IMAGE_INCLUDE_DIR})
find_package(SDL2TTF REQUIRED)
include_directories(${SDL2_MIXER_INCLUDE_DIR})

# add_subdirectory(Player)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

set(PUGIXML_DIR pugixml)
include_directories(${PUGIXML_DIR})

set(SOURCE_FILES ${PUGIXML_DIR}/pugixml.hpp ${PUGIXML_DIR}/pugixml.cpp Demo.cpp widget/Window.cpp widget/Window.h units/Text.cpp units/Text.h units/Font.cpp units/Font.h utils/Timer.cpp utils/Timer.h widget/Button.cpp widget/Button.h units/Rectangle.h widget/TextArea.cpp widget/TextArea.h widget/ComboBox.cpp widget/ComboBox.h core/System.h units/Renderer.h widget/Widget.cpp widget/Widget.h core/Object.h widget/Label.cpp widget/Label.h units/Image.cpp units/Image.h widget/HorizontalSlider.cpp widget/HorizontalSlider.h widget/LineEdit.cpp widget/LineEdit.h core/Control.cpp core/Control.h core/Event.cpp core/Event.h widget/AbstractButton.cpp widget/AbstractButton.h widget/CheckBox.cpp widget/CheckBox.h widget/ButtonGroup.cpp widget/ButtonGroup.h Layout/VerticalLayout.cpp Layout/VerticalLayout.h utils/XMLLoad.cpp utils/XMLLoad.h utils/DefaultLoadNodeFunction.h units/MessageBox.cpp units/MessageBox.h units/Dialog.cpp units/Dialog.h Player/LockFreeQueue.h units/Renderer.cpp units/Cursor.cpp units/Cursor.h units/SelectArea.cpp units/SelectArea.h units/Rectangle.cpp core/System.cpp common.hpp units/MouseCursor.cpp units/MouseCursor.h units/ClipBoard.cpp units/ClipBoard.h Layout/HorizontalLayout.cpp Layout/HorizontalLayout.h Layout/WidgetLayout.cpp Layout/WidgetLayout.h Layout/GridLayout.cpp Layout/GridLayout.h core/Object.cpp core/MetaInfo.h core/MetaInfo.cpp)
add_executable(GWUI ${SOURCE_FILES})

target_link_libraries(GWUI ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARY} ${SDL2_MIXER_LIBRARY} ${SDL2_TTF_LIBRARY})