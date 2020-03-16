QT       += core gui network xml androidextras

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    data/allaction.cpp \
    data/globaldata.cpp \
    main.cpp \
    dynerandroid.cpp \
    server/serversocket.cpp \
    widget/Cart/cart.cpp \
    widget/CloseWindow/closewindow.cpp \
    widget/menu/addorderitem.cpp \
    widget/menu/customWidget/orderitemdata.cpp \
    widget/serverConnection/serverconnection.cpp \
    widget/tableList/TableCustomButtons/tablecustombuttons.cpp \
    widget/tableList/tablelist.cpp

HEADERS += \
    data/allaction.h \
    data/globaldata.h \
    dynerandroid.h \
    server/serversocket.h \
    widget/Cart/cart.h \
    widget/CloseWindow/closewindow.h \
    widget/menu/addorderitem.h \
    widget/menu/customWidget/orderitemdata.h \
    widget/serverConnection/serverconnection.h \
    widget/tableList/TableCustomButtons/tablecustombuttons.h \
    widget/tableList/tablelist.h

FORMS += \
    dynerandroid.ui \
    widget/Cart/cart.ui \
    widget/CloseWindow/closewindow.ui \
    widget/menu/addorderitem.ui \
    widget/menu/customWidget/orderitemdata.ui \
    widget/serverConnection/serverconnection.ui \
    widget/tableList/TableCustomButtons/tablecustombuttons.ui \
    widget/tableList/tablelist.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
