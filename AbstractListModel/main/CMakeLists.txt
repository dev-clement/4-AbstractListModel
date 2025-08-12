find_package(Qt6 REQUIRED COMPONENTS Quick QuickControls2)

qt_standard_project_setup(REQUIRES 6.8)

qt_add_executable(appAbstractListModel
    src/main.cpp
)

qt_add_qml_module(appAbstractListModel
    URI AbstractListModel
    VERSION 1.0
    QML_FILES
        qml/Main.qml
    SOURCES
        inc/person.hpp src/person.cpp
        SOURCES inc/personmodel.hpp src/personmodel.cpp
        QML_FILES qml/InputDialog.qml
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appAbstractListModel PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appAbstractListModel
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_include_directories(appAbstractListModel PUBLIC inc/)

target_link_libraries(appAbstractListModel
    PRIVATE Qt6::Quick Qt6::QuickControls2
)

include(GNUInstallDirs)
install(TARGETS appAbstractListModel
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
