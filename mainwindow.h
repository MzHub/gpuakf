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
#ifndef INCLUDED_MAINWINDOW_H
#define INCLUDED_MAINWINDOW_H

#include "ui_mainwindow.h"
#ifdef HAVE_QUICKTIME
#include "quicktime.h"
#endif

class MainWindow : public QMainWindow, public Ui_MainWindow {
    Q_OBJECT
public:
    MainWindow();
    ~MainWindow();

	bool open(const QString& fileName);

public slots:
    void on_actionOpen_triggered();
    void on_actionSave_triggered();
    void on_actionAbout_triggered();
    void on_algorithm_currentIndexChanged(int index);

    #ifdef HAVE_QUICKTIME
    void on_actionRecord_triggered();
    void on_timeSlider_valueChanged(int value);
    void on_playButton_clicked();
    void do_play();
    #endif

private:
    QString m_fileName;
    int m_algorithm;

    #ifdef HAVE_QUICKTIME
    QTimer *m_timer;
    bool m_haveQuickTime;
    quicktime_player *m_player;
    #endif
};

extern MainWindow *mainWindow;

#endif
