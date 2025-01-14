cmake_minimum_required(VERSION 3.16)

project(Ikm VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Находим Qt и необходимые модули
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Sql)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Sql)

# Список исходных файлов проекта
set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    database.cpp
    database.h
    userwidget.cpp
    userwidget.h
    postwidget.cpp
    postwidget.h
    commentwidget.cpp
    commentwidget.h
)

# Создание исполняемого файла
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Ikm
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        userwidget.h userwidget.cpp
        postwidget.h postwidget.cpp
        commentwidget.h commentwidget.cpp

    )
else()
    if(ANDROID)
        add_library(Ikm SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(Ikm
            ${PROJECT_SOURCES}
        )
    endif()
endif()

# Подключаем необходимые библиотеки
target_link_libraries(Ikm PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Sql)

# Настройка свойств для macOS и iOS
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.Ikm)
endif()
set_target_properties(Ikm PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

# Установка приложения
include(GNUInstallDirs)
install(TARGETS Ikm
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Финальная настройка для Qt 6
if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Ikm)
endif()
