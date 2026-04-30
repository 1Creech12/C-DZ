cmake_minimum_required(VERSION 3.16)

project(JournalTest VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Ищем Qt6 с модулем Network
find_package(Qt6 REQUIRED COMPONENTS Core Widgets Network)

# Все исходники в одной папке
set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    loginwindow.cpp
    loginwindow.h
    loginwindow.ui
    apiclient.cpp
    apiclient.h
    authmanager.cpp
    authmanager.h
    AuthModels.h
)

# Основное приложение
qt_add_executable(JournalTest
    MANUAL_FINALIZATION
    ${PROJECT_SOURCES}
    ${PROJECT_RESOURCES}
)

# Линкуем все модули Qt
target_link_libraries(JournalTest PRIVATE
    Qt6::Core
    Qt6::Widgets
    Qt6::Network
)

# Тест авторизации
add_executable(test_auth
    test_auth.cpp
    apiclient.cpp
    authmanager.cpp
)

target_link_libraries(test_auth PRIVATE
    Qt6::Core
    Qt6::Network
)

# Свойства для macOS
set_target_properties(JournalTest PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER com.topacademy.journaltest
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

# Финализация Qt6
qt_finalize_executable(JournalTest)

# Установка
include(GNUInstallDirs)
install(TARGETS JournalTest
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)