QT += charts
QT += sql
QT += core gui sql
QT += network
requires(qtConfig(combobox))

HEADERS += \
    tool/templateSingle.hpp\
    task/getMessage.h \
    dataTransfer/tcpServer.h \
    manager/controlCenter.h \
    database/sqlServe.h \
    dataDecoding/readDat.h \
    dataDecoding/oneMachinePara.h \
    dataDecoding/writeToJson.h \
    dataDecoding/writeToDb.h \
    dataDecoding/fileManager.h \
    dataDecoding/FileSystemWatcher.h \
    manager/receiveOperator.h \
    dataDecoding/stabilityCal.h \
    ui/singleMachine.h \
    ui/allmachineWindow.h \
    tool/SafeQueue.h \
    tool/ThreadPool.h

SOURCES += \
    main.cpp \
    task/getMessage.cpp \
    dataTransfer/tcpServer.cpp \
    manager/controlCenter.cpp \
    database/sqlServe.cpp \
    dataDecoding/readDat.cpp \
    dataDecoding/oneMachinePara.cpp \
    dataDecoding/writeToJson.cpp \
    dataDecoding/writeToDb.cpp \
    dataDecoding/fileManager.cpp \
    dataDecoding/FileSystemWatcher.cpp \
    manager/receiveOperator.cpp \
    dataDecoding/stabilityCal.cpp \
    ui/singleMachine.cpp \
    ui/allmachineWindow.cpp

target.path = $$[QT_INSTALL_EXAMPLES]/charts/chartthemes
INSTALLS += target

FORMS += \
    ui/singleMachine.ui \
    ui/allmachineWindow.ui

DISTFILES += \
    report.dat \
    em63/report_1.job \
    em63/SESS0000.REQ

RESOURCES += \
    ui/source/green.qrc
