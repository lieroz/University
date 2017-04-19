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
    3dparty/jsmn.c \
    upload/uploader.cpp \
    objects/model.cpp \
    objects/camera.cpp \
    managers/upload_manager.cpp \
    managers/camera_manager.cpp \
    managers/model_manager.cpp \
    managers/draw_manager.cpp \
    controller/controller.cpp \
    facade/facade.cpp \
    scene/scene.cpp \
    transformations/model_transformations.cpp \
    transformations/camera_transformations.cpp \
    commands/move_model.cpp \
    commands/rotate_model.cpp \
    commands/scale_model.cpp \
    commands/manage_camera.cpp \
    commands/move_scene.cpp \
    commands/rotate_scene.cpp \
    commands/manage_scene_camera.cpp

HEADERS  += gui/mainwindow.hpp \
    containers/vector/vector_base.hpp \
    containers/vector/vector.hpp \
    containers/iterator/iterator_base.hpp \
    containers/matrix/matrix_base.hpp \
    containers/matrix/matrix.hpp \
    containers/iterator/const_iterator.hpp \
    containers/iterator/iterator.hpp \
    upload/uploader.hpp \
    exceptions/base_exception.hpp \
    exceptions/container_exceptions.hpp \
    exceptions/upload_exceptions.hpp \
    primitives/point3d.hpp \
    manipulator/base_manipulator.hpp \
    containers/pair/pair.hpp \
    3dparty/jsmn.h \
    objects/visible_object.hpp \
    objects/invisible_object.hpp \
    objects/scene_object.hpp \
    objects/model.hpp \
    objects/camera.hpp \
    transformations/abstract_transformations.hpp \
    managers/abstract_manager.hpp \
    managers/upload_manager.hpp \
    managers/camera_manager.hpp \
    managers/model_manager.hpp \
    managers/draw_manager.hpp \
    controller/controller.hpp \
    facade/facade.hpp \
    scene/scene.hpp \
    transformations/model_transformations.hpp \
    transformations/camera_transformations.hpp \
    commands/command.hpp \
    commands/move_model.hpp \
    commands/rotate_model.hpp \
    commands/scale_model.hpp \
    commands/move_scene.hpp \
    commands/rotate_scene.hpp \
    commands/manage_scene_camera.hpp \
    commands/manage_model_camera.hpp

FORMS    += gui/mainwindow.ui
