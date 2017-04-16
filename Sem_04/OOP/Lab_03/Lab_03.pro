#-------------------------------------------------
#
# Project created by QtCreator 2017-04-11T14:59:43
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Lab_03
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        gui/mainwindow.cpp \
    camera/base_camera.cpp \
    camera/scene_camera.cpp \
    camera/model_camera.cpp \
    model/model.cpp \
    scene/scene.cpp \
    manipulator/base_manipulator.cpp \
    manipulator/scene_manipulator.cpp \
    manipulator/model_manipulator.cpp \
    command/command.cpp \
    command/rotate_command.cpp \
    command/scale_command.cpp \
    command/move_command.cpp

HEADERS  += gui/mainwindow.hpp \
    container/vector/vector_base.hpp \
    container/vector/vector.hpp \
    container/iterator/iterator_base.hpp \
    container/matrix/matrix_base.hpp \
    container/matrix/matrix.hpp \
    container/iterator/const_iterator.hpp \
    container/iterator/iterator.hpp \
    upload/uploader.hpp \
    exceptions/base_exception.hpp \
    exceptions/container_exceptions.hpp \
    exceptions/upload_exceptions.hpp \
    primitives/point3d.hpp \
    camera/base_camera.hpp \
    camera/scene_camera.hpp \
    camera/model_camera.hpp \
    model/model.hpp \
    scene/scene.hpp \
    manipulator/base_manipulator.hpp \
    manipulator/scene_manipulator.hpp \
    manipulator/model_manipulator.hpp \
    command/command.hpp \
    container/pair/pair.hpp \
    command/rotate_command.hpp \
    command/scale_command.hpp \
    command/move_command.hpp

FORMS    += gui/mainwindow.ui
