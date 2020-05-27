QT       += core gui sql charts network printsupport
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
QT += multimedia
include( $$PWD/../SMTPClient/SMTPClient.pri )

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
QMAKE_CXXFLAGS_WARN_OFF -= -Wunused-parameter
# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    animal.cpp \
    avis_fournisseur.cpp \
    chartview.cpp \
    chat.cpp \
    connexion.cpp \
    equipement.cpp \
    fournisseur.cpp \
    login.cpp \
    main.cpp \
    mainwindow.cpp \
    nourriture.cpp \
    ouvrier.cpp \
    plante.cpp \
    produit.cpp \
    produitv.cpp \
    profil.cpp \
    tableprinter.cpp \
    vehicule.cpp \

HEADERS += \
    animal.h \
    avis_fournisseur.h \
    chartview.h \
    chat.h \
    connexion.h \
    equipement.h \
    fournisseur.h \
    login.h \
    mainwindow.h \
    nourriture.h \
    ouvrier.h \
    plante.h \
    produit.h \
    produitv.h \
    profil.h \
    tableprinter.h \
    vehicule.h \


FORMS += \
    mainwindow.ui

RC_ICONS = myappico.ico
QMAKE_CXXFLAGS += -std=gnu++14

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

DISTFILES += \
    SMTPClient/SMTPClient.pri \
    style.qss
