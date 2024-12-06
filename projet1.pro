QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    view/dashboard.cpp \
    view/kitchen.cpp \
    view/view.cpp \
    view/DisplayInterfacesClass.cpp \
    main/main.cpp \
    controller/classDefinition/MainController.cpp \
    controller/classDeclaration/MotionlessElementController.h \
    model/classDefinition/Butler.cpp \
    model/classDefinition/DirtyDishesStorage.cpp \
    model/classDefinition/Human.cpp \
    model/classDefinition/Recipe.cpp \
    model/classDefinition/WashingMachine.cpp

HEADERS += \
    view/dashboard.h \
    view/kitchen.h \
    view/view.h \
    view/DisplayInterfacesClass.h \
    controller/classDeclaration/MainController.h \
    controller/classDeclaration/MotionlessElementController.h \
    model/classDeclaration/Butler.h \
    model/classDeclaration/DirtyDishesStorage.h \
    model/classDeclaration/Human.h \
    model/classDeclaration/Recipe.h \
    model/classDeclaration/WashingMachine.h
FORMS += \
    view/dashboard.ui \
    view/kitchen.ui \
    view/view.ui

RESOURCES += \
    view/resources.qrc


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
