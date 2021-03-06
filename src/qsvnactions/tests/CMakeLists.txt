FIND_PACKAGE(Qt4)
SET(QT_USE_QTTEST 1)
INCLUDE(${QT_USE_FILE})

IF (WIN32)
  SET ( EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin )
ELSE (WIN32)
  SET ( EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR}/bin )
ENDIF (WIN32)

INCLUDE_DIRECTORIES( ${CMAKE_CURRENT_SOURCE_DIR}
                     ${CMAKE_CURRENT_BINARY_DIR} )

set ( qsvn_sources
        ../qsvnaction.cpp
        ../qsvnclientaction.cpp
        ../qsvnclientcheckoutaction.cpp
        ../qsvnrepositoryaction.cpp
        ../qsvnrepositorycreateaction.cpp
        ../../helper.cpp
        ../../listener.cpp
        ../../login.cpp
        ../../statustext.cpp
        ../../sslservertrust.cpp )

set ( testcases
        qsvnclientcheckoutactiontests
        qsvnrepositorycreateactiontests )

foreach( testcase ${testcases} )
  QT4_GENERATE_MOC( ${CMAKE_CURRENT_SOURCE_DIR}/${testcase}.cpp ${CMAKE_CURRENT_BINARY_DIR}/${testcase}.moc )
  ADD_EXECUTABLE( ${testcase} ${testcase}.cpp ${qsvn_sources} ${CMAKE_CURRENT_BINARY_DIR}/${testcase}.moc)
  ADD_TEST( ${testcase} ${EXECUTABLE_OUTPUT_PATH}/${testcase} )
  TARGET_LINK_LIBRARIES( ${testcase} svnqt ${QT_LIBRARIES} )
endforeach( testcase ${testcases} )
