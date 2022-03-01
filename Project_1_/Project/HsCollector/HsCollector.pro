TEMPLATE = subdirs

QT  +=network

SUBDIRS += \
    HscUI \
    #HscClient \
    #thirdparty

CONFIG(debug, debug|release) {
    DESTDIR =  $$OUT_PWD/../debug
} else {
    DESTDIR =  $$OUT_PWD/../release
}
