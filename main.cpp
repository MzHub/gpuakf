//
// by Jan Eric Kyprianidis <www.kyprianidis.com>
// Copyright (C) 2009-2011 Computer Graphics Systems Group at the
// Hasso-Plattner-Institut, Potsdam, Germany <www.hpi3d.de>
// 
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
#include "mainwindow.h"


MainWindow *mainWindow = NULL;


int main(int argc, char **argv) {
    QApplication::setOrganizationDomain("jkyprian.hpi3d.de");
    QApplication::setOrganizationName("jkyprian");
    QApplication::setApplicationName("gpuakf");
    QApplication app(argc, argv);
    QApplication::setStyle(new QPlastiqueStyle);
    QApplication::setPalette(QApplication::style()->standardPalette());

    QSettings settings;
    #ifdef Q_WS_WIN
    if (QSysInfo::windowsVersion() >= QSysInfo::WV_VISTA) {
        if (settings.value("wddmCheck", true).toBool()) {
            int result = QMessageBox::warning(NULL, "Warning",
                "You are running Windows Vista or later. This program performs extensive "
                "processing on the GPU. You may have to adjust your "
                "<a href='http://www.microsoft.com/whdc/device/display/wddm_timeout.mspx'>WDDM timeout</a> "
                "settings. Do you want to continue?",
                QMessageBox::Yes | QMessageBox::No
            );
            if (result != QMessageBox::Yes) 
                exit(1);
        }
        settings.setValue("wddmCheck", false);
    }
    #endif

    #ifdef Q_WS_MAC
    QFont font = QApplication::font();
    font.setPointSize(11);
    QApplication::setFont(font);
    #endif

    QString defaultFile = settings.value("lastFile").toString();
    if (defaultFile.isEmpty()) {
        QFileInfo fi(":/test_512x512.png");
        defaultFile = fi.absoluteFilePath();
    }

    mainWindow = new MainWindow;
    mainWindow->restoreGeometry(settings.value("mw").toByteArray());
    mainWindow->showNormal();

    int buildStatus = mainWindow->glw->buildStatus();
    if (buildStatus < 2) {
        if ((buildStatus != 1) || settings.value("showWarnings", true).toBool()) {
            mainWindow->glw->buildLog();
        }
        if (buildStatus == 0) exit(1);
    }

    if (QFile::exists(defaultFile)) mainWindow->open(defaultFile);

    app.connect(&app, SIGNAL(lastWindowClosed()), &app, SLOT(quit()));
    int result = app.exec();

    settings.setValue("mw", mainWindow->saveGeometry());
    delete mainWindow;
    mainWindow = NULL;
    
    return result;
}
