project(kapman)

cmake_minimum_required (VERSION 2.8.12 FATAL_ERROR)
set (QT_MIN_VERSION "5.3.0")
set (KF5_MIN_VERSION "5.15.0")

find_package(ECM 1.7.0 REQUIRED CONFIG)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${ECM_MODULE_PATH} ${ECM_KDE_MODULE_DIR})

find_package(Qt5 ${QT_MIN_VERSION} REQUIRED NO_MODULE COMPONENTS Widgets Svg)
find_package(KF5 ${KF5_MIN_VERSION} REQUIRED COMPONENTS
    CoreAddons
    Config
    Crash
    DBusAddons
    DocTools
    Config
    I18n
    ConfigWidgets
    XmlGui
    )

find_package(KF5KDEGames 4.9.0 REQUIRED)

include(FeatureSummary)
include(ECMInstallIcons)
include(KDEInstallDirs)
include(KDECompilerSettings NO_POLICY_SCOPE)
include(KDECMakeSettings)
include(ECMAddAppIcon)

add_definitions(
    -DQT_USE_FAST_CONCATENATION
    -DQT_USE_FAST_OPERATOR_PLUS
    -DQT_NO_CAST_FROM_ASCII
    -DQT_NO_CAST_TO_ASCII
    -DQT_NO_CAST_FROM_BYTEARRAY
    -DQT_NO_URL_CAST_FROM_STRING
    -DQT_USE_QSTRINGBUILDER
)

add_subdirectory(doc)

set(kapman_SRCS
	bonus.cpp
	cell.cpp
	character.cpp
	characteritem.cpp
	element.cpp
	elementitem.cpp
	energizer.cpp
	game.cpp
	gamescene.cpp
	gameview.cpp
	ghost.cpp
	ghostitem.cpp
	kapman.cpp
	kapmanitem.cpp
	kapmanmainwindow.cpp
	kapmanparser.cpp
	main.cpp
	maze.cpp
	mazeitem.cpp
	pill.cpp
)
file(GLOB themes
	"themes/*.svgz"
	"themes/*.desktop"
	"themes/*.copyright"
	"themes/*.png"
)
file(GLOB sounds_ogg "sounds/*.ogg")

kconfig_add_kcfg_files(kapman_SRCS settings.kcfgc)

ecm_install_icons(ICONS 128-apps-kapman.png  16-apps-kapman.png  22-apps-kapman.png  32-apps-kapman.png  48-apps-kapman.png  64-apps-kapman.png DESTINATION ${KDE_INSTALL_ICONDIR} THEME hicolor)

file(GLOB ICONS_SRCS "${CMAKE_CURRENT_SOURCE_DIR}/*-apps-kapman.png")
ecm_add_app_icon(kapman_SRCS ICONS ${ICONS_SRCS})
add_executable(kapman ${kapman_SRCS})

target_link_libraries(kapman 
   KF5KDEGames
   KF5KDEGamesPrivate
   Qt5::Svg
   Qt5::Xml
   KF5::Crash
   KF5::DBusAddons
   KF5::XmlGui
)

install(TARGETS kapman ${KDE_INSTALL_TARGETS_DEFAULT_ARGS})
install(PROGRAMS org.kde.kapman.desktop DESTINATION ${KDE_INSTALL_APPDIR})
install(FILES org.kde.kapman.appdata.xml DESTINATION ${KDE_INSTALL_METAINFODIR})
install(FILES kapmanui.rc DESTINATION ${KDE_INSTALL_KXMLGUI5DIR}/kapman)
install(FILES defaultmaze.xml DESTINATION ${KDE_INSTALL_DATADIR}/kapman)
install(FILES ${themes} DESTINATION ${KDE_INSTALL_DATADIR}/kapman/themes)
install(FILES ${sounds_ogg} DESTINATION ${KDE_INSTALL_SOUNDDIR}/kapman)

feature_summary(WHAT ALL INCLUDE_QUIET_PACKAGES FATAL_ON_MISSING_REQUIRED_PACKAGES)
