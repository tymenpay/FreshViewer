cmake_minimum_required(VERSION 3.29)
project(ThreeDViewer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_PREFIX_PATH "/opt/homebrew/opt/qt@5/lib/cmake")

find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        OpenGL
        REQUIRED)

find_package(OpenGL REQUIRED)


set(SOURCES
        main.cpp
        MainWindow.cpp
        OpenGLWidget.cpp
        3DModel.cpp
)

set(HEADERS
        MainWindow.h
        OpenGLWidget.h
        3DModel.h
        3DModel.cpp
        3DModel.h
        affine_matrix.h
        coor_for_paint.h
)

add_executable(3DViewer ${SOURCES} ${HEADERS})

target_link_libraries(3DViewer
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::OpenGL
        OpenGL::GL)
