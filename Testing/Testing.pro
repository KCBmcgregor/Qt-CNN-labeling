TEMPLATE = app
CONFIG -= qt
CONFIG -= app_bundle
CONFIG += console

isEmpty(BOOST_INCLUDE_DIR): BOOST_INCLUDE_DIR=$$(BOOST_INCLUDE_DIR)
# set by Qt Creator wizard
isEmpty(BOOST_INCLUDE_DIR): BOOST_INCLUDE_DIR="C:/Users/Roshni/Documents/boost_1_72_0"
!isEmpty(BOOST_INCLUDE_DIR): INCLUDEPATH *= $${BOOST_INCLUDE_DIR}

isEmpty(BOOST_INCLUDE_DIR): {
    message("BOOST_INCLUDE_DIR is not set, assuming Boost can be found automatically in your system")
}

SOURCES += \
    main.cpp \
    control.cpp \
    image.cpp \
    model.cpp \
    point.cpp \
    polygonitem.cpp \
    savetimer.cpp \
    view.cpp

HEADERS += \
    control.h \
    image.h\
    model.h \
    point.h \
    polygonitem.h\
    savetimer.h \
    view.h

FORMS += \
    view.ui

