cmake_minimum_required(VERSION 3.5)

project(Account_Management VERSION 1.0 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    resources.qrc
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Account_Management
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        libs/database.h libs/database.cpp
        libs/account.h libs/account.cpp
        libs/transaction.h libs/transaction.cpp
        libs/labels.h libs/labels.cpp
    )
else()
    add_executable(Account_Management
        ${PROJECT_SOURCES}
    )
endif()

target_link_libraries(Account_Management PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
)

set_target_properties(Account_Management PROPERTIES
    WIN32_EXECUTABLE TRUE
)

install(TARGETS Account_Management
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Account_Management)
endif()
