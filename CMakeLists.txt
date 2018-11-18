cmake_minimum_required(VERSION 3.12)
project(CompMath)

set(CMAKE_CXX_STANDARD 14)

# Указывает CMake запускать MOC когда это необходимо
set(CMAKE_AUTOMOC ON)
# По скольку MOC файлы генерируются в дирекотрии bin, необходимо
# указать CMake включать эти файлы (из этой директории)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# include other modules above
find_package(Qt5 REQUIRED COMPONENTS Core Gui Widgets Charts)
include_directories(${Qt5Widgets_INCLUDES})
# Добавляет -DQT_WIDGETS_LIB при использовании QtWidgets в Qt 5.
add_definitions(${Qt5Widgets_DEFINITIONS})

# Добавление флагов компиляции для Qt проекта
set(CMAKE_CXX_FLAGS "${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")

add_executable(CompMath main.cpp gui/LAbsTabs.cpp gui/LAbsTabs.h gui/LinearSystemTab.cpp gui/LinearSystemTab.h gui/IntegrationTab.cpp gui/IntegrationTab.h algos/LinearSystemSolver.cpp algos/LinearSystemSolver.h algos/IntegrationSolver.cpp algos/IntegrationSolver.h helpers/Function.cpp helpers/Function.h gui/InterpolationTab.cpp gui/InterpolationTab.h gui/ODETab.cpp gui/ODETab.h algos/InterpolationSolver.cpp algos/InterpolationSolver.h algos/ODESolver.cpp algos/ODESolver.h)

target_link_libraries(${PROJECT_NAME} Qt5::Core)
target_link_libraries(${PROJECT_NAME} Qt5::Gui)
target_link_libraries(${PROJECT_NAME} Qt5::Widgets)
    target_link_libraries(${PROJECT_NAME} Qt5::Charts)

# Если в проекте есть UI формы, то необходимо испоользовать эту директиву и перечислить пути к файлам UI форм.
# qt5_wrap_ui(UIS_HDRS views/mainwindow.ui)
# Указывает какие модули использовать в проекте
qt5_use_modules(CompMath Widgets Charts)
