TEMPLATE = aux

CONFIG -= debug_and_release

INSTALLER = installer

INPUT = $$PWD/config/config.xml $$PWD/packages
example.input = INPUT
example.output = $$INSTALLER
example.commands = /home/lieroz/Qt/QtIFW-3.0.2/bin/binarycreator -c $$PWD/config/config.xml -p $$PWD/packages ${QMAKE_FILE_OUT}
example.CONFIG += target_predeps no_link combine

QMAKE_EXTRA_COMPILERS += example

OTHER_FILES += \
    packages/package1/meta/package.xml \
    packages/examples/meta/package.xml

