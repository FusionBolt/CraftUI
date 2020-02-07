cmake_minimum_required(VERSION 3.14)
project(GWUI)

set(CMAKE_CXX_STANDARD 17)

set(SDL_DIR /usr/local/Cellar/sdl2/2.0.10)
include_directories(${SDL_DIR}/include/SDL2/)
link_directories(${SDL_DIR}/lib/)

set(SDL_IMG_DIR /usr/local/Cellar/sdl2_image/2.0.5)
include_directories(${SDL_IMG_DIR}/include/SDL2/)
link_directories(${SDL_IMG_DIR}/lib/)

set(SDL_TTF_DIR /usr/local/Cellar/sdl2_ttf/2.0.15)
include_directories(${SDL_TTF_DIR}/include/SDL2/)
link_directories(${SDL_TTF_DIR}/lib/)

set(SDL_MIXER_DIR /usr/local/Cellar/sdl2_mixer/2.0.4)
include_directories(${SDL_MIXER_DIR}/include/SDL2/)
link_directories(${SDL_MIXER_DIR}/lib/)

set(PUGIXML_DIR pugixml)
include_directories(${PUGIXML_DIR})
link_directories(${PUGIXML_DIR})
set(SOURCE_FILES ${PUGIXML_DIR}/pugixml.hpp ${PUGIXML_DIR}/pugixml.cpp main.cpp widget/Window.cpp widget/Window.h units/Text.cpp units/Text.h units/Font.cpp units/Font.h utils/Util.hpp utils/Timer.cpp utils/Timer.h widget/Button.cpp widget/Button.h units/Rectangle.hpp widget/TextArea.cpp widget/TextArea.h widget/ComboBox.cpp widget/ComboBox.h core/System.hpp units/Renderer.hpp widget/Widget.cpp widget/Widget.h core/Object.hpp widget/Label.cpp widget/Label.h units/Image.cpp units/Image.h widget/HorizontalSlider.cpp widget/HorizontalSlider.h widget/LineEdit.cpp widget/LineEdit.h core/Control.cpp core/Control.h core/Event.cpp core/Event.h widget/AbstractButton.cpp widget/AbstractButton.h widget/CheckBox.cpp widget/CheckBox.h widget/ButtonGroup.cpp widget/ButtonGroup.h widget/VerticalLayout.cpp widget/VerticalLayout.h utils/XMLLoad.cpp utils/XMLLoad.h utils/DefaultLoadNodeFunction.h)
add_executable(GWUI ${SOURCE_FILES})

target_link_libraries(GWUI SDL2 SDL2_image SDL2_ttf SDL2_mixer)