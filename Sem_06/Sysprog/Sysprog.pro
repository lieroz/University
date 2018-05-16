TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += daemon/daemon.c \
    tree/tree.c \
    kernel_modules/md1.c \
    kernel_modules/md2.c \
    kernel_modules/md3.c \
    vfs/vfs.c \
    fortune_cookies/fortune_cookies.c \
    sockets/af_unix/server.c \
    sockets/af_unix/client.c \
    sockets/af_inet_multiplex/server.c \
    sockets/af_inet_multiplex/client.c \
    tasklet/tasklet.c \
    work_queue/work_queue.c

INCLUDEPATH += /usr/src/linux-headers-$$system(uname -r)/include
INCLUDEPATH += /usr/src/linux-headers-$$system(uname -r)/arch/x86/include
