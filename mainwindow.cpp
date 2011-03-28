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


MainWindow::MainWindow() {
    setupUi(this);

    #ifdef Q_WS_MAC
    QList<QWidget*> widgets = this->findChildren<QWidget*>();
    for (int i = 0; i < widgets.size(); ++i) {
        QWidget *w = widgets.at(i);
        if (w->inherits("QLabel")) {
            w->setFont(QApplication::font());
        }
    }
    #endif

    actionQuit->setShortcut(QKeySequence(Qt::Key_Escape));
    m_algorithm = algorithm->currentIndex();

    #ifdef HAVE_QUICKTIME
    m_player = 0;
    m_haveQuickTime = quicktime_init();
    m_timer =  new QTimer(this);
    m_timer->setInterval(0);
    m_timer->setSingleShot(false);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(do_play()));
    #else
    playButton->hide();
    timeSlider->hide();
    #endif

    QSettings settings; 
    m_fileName = settings.value("lastfile").toString();
    renderFullQuad->setChecked(settings.value("renderFullQuad").toBool());
}


MainWindow::~MainWindow() {
    QSettings settings;
    settings.setValue("lastFile", m_fileName);
    settings.setValue("renderFullQuad", renderFullQuad->isChecked());

    #ifdef HAVE_QUICKTIME
    if (m_haveQuickTime)
        quicktime_exit();
    #endif  
}


bool MainWindow::open(const QString& fileName) {
    #ifdef HAVE_QUICKTIME
    if (m_player) {
        delete m_player;
        m_player = 0;
    }
    #endif
    playButton->setEnabled(false);
    timeSlider->setEnabled(false);
    actionRecord->setEnabled(false);
    timeSlider->setValue(0);

    QImage image;
    if (image.load(fileName)) {
        image = image.convertToFormat(QImage::Format_ARGB32);
        glw->setPixels(image.width(), image.height(), GL_BGRA_EXT, GL_UNSIGNED_BYTE, image.bits());
        m_fileName = fileName;
        return true;
    } 
            
    #ifdef HAVE_QUICKTIME
    if (m_haveQuickTime) {
        std::string pathStd = fileName.toStdString();
        m_player = quicktime_player::open(pathStd.c_str());
        if (!m_player) {
            return false;
        }
        m_player->set_time(0);

        int nframes = m_player->get_frame_count();
        playButton->setEnabled(nframes > 1);
        actionRecord->setEnabled(nframes > 1);
        bool b = timeSlider->blockSignals(true);
        timeSlider->setEnabled(nframes > 1);
        timeSlider->setRange(0, m_player->get_duration());
        timeSlider->setValue(0);
        timeSlider->blockSignals(b);
        on_timeSlider_valueChanged(0);

        m_fileName = fileName;
        return true;
    }
    #endif

    return false;
}


void MainWindow::on_actionOpen_triggered() {
    QString filter = "Images (*.png *.bmp)";
    #ifdef HAVE_QUICKTIME
    if (m_haveQuickTime)
        filter = "Images and Videos (*.png *.bmp *.jpg *.jpeg *.mov *.avi)";
    #endif
    filter += ";;All files (*.*)";
    QString fileName = QFileDialog::getOpenFileName(this, "Open", m_fileName, filter);
    if (!fileName.isEmpty()) {
        if (!open(fileName)) {
            QMessageBox::critical(this, "Error", QString("Loading '%1' failed!").arg(fileName));
        } 
    }
}


void MainWindow::on_actionSave_triggered() {
    QFileInfo fi(m_fileName);
    QString fileName = QFileDialog::getSaveFileName(this, "Save", 
        fi.dir().filePath(fi.baseName() + "-out.png"), 
        "Image (*.png);;All files (*.*)"
    );
    if (!fileName.isEmpty()) {
        QImage img(glw->width(), glw->height(), QImage::Format_RGB32);
        glw->getPixels(img.width(), img.height(), GL_BGRA_EXT, GL_UNSIGNED_BYTE, img.bits());
        if (!img.save(fileName)) {
            QMessageBox::critical(this, "Error", QString("Saving '%1' failed!").arg(fileName));
        }
        QDesktopServices::openUrl(QUrl::fromLocalFile(fileName));
    }
}

void MainWindow::on_algorithm_currentIndexChanged(int index) {
    if ((m_algorithm == 0) && (index != 0)) {
        bool b = radius->blockSignals(true);
        radius->setValue(radius->value() * 2.0);
        radius->blockSignals(b);
    }
    if ((m_algorithm != 0) && (index == 0)) {
        bool b = radius->blockSignals(true);
        radius->setValue(radius->value() * 0.5);
        radius->blockSignals(b);
    }
    if (m_algorithm == 3) {
        bool b = N->blockSignals(true);
        N->setValue(8);
        N->blockSignals(b);
    }

    m_algorithm = index;

    sigma_t->setEnabled(index >= 2);
    alpha->setEnabled(index >= 2);
    N->setEnabled((index >= 1) && (index < 3));
    smoothing->setEnabled(index >= 1);
    q->setEnabled(index >= 1);
    kernel->setEnabled(index >= 1);

    glw->process();
}


void MainWindow::on_actionAbout_triggered() {
    QMessageBox msgBox;
    msgBox.setWindowTitle("About");
    msgBox.setIcon(QMessageBox::Information);
    msgBox.setText("<b>Anisotropic Kuwahara Filtering on the GPU</b>");
    msgBox.setInformativeText(
        "<html><body>" \
        "Copyright (C) 2009-2011 Computer Graphics Systems Group at " \
        "the Hasso-Plattner-Institut, Potsdam, Germany &lt;<a href='http://www.hpi3d.de'>www.hpi3d.de</a>&gt;" \
        "<br/><br/>" \
        "Author: Jan Eric Kyprianidis &lt;<a href='http://www.kyprianidis.com'>www.kyprianidis.com</a>&gt;<br/>" \
        "Date: " __DATE__ "<br/><br/>"
        "This program is free software: you can redistribute it and/or modify " \
        "it under the terms of the GNU General Public License as published by " \
        "the Free Software Foundation, either version 3 of the License, or " \
        "(at your option) any later version.<br/><br/>" \
        "This program is distributed in the hope that it will be useful, " \
        "but WITHOUT ANY WARRANTY; without even the implied warranty of " \
        "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the " \
        "GNU General Public License for more details."
        "<br/><br/>" \
        "Related Publications:" \
        "<ul><li>" \
        "Kyprianidis, J. E., Kang, H., &amp; D&ouml;llner, J. (2009). " \
        "Image and Video Abstraction by Anisotropic Kuwahara Filtering. " \
        "<em>Computer Graphics Forum</em> 28, 7. " \
        "(Special issue on Pacific Graphics 2009)" \
        "</li><li>" \
        "Kyprianidis, J. E., Kang, H., &amp; D&ouml;llner, J. (2010). " \
        "Anisotropic Kuwahara Filtering on the GPU. " \
        "In W. Engel (Ed.), <em>GPU Pro - Advanced Rendering Techniques</em>. " \
        "AK Peters." \
        "</li></ul>" \
        "Test image courtesy of Law Keven." \
        "</body></html>"
    );
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.exec();
}


#ifdef HAVE_QUICKTIME

void MainWindow::on_actionRecord_triggered() {
    if (!m_player) 
        return;
    
    QFileInfo fi(m_fileName);
    QString fileName = QFileDialog::getSaveFileName(this, "Record", fi.dir().filePath(fi.baseName() + "-out.mov"), 
        "QuickTime Movie (*.mov);;All files (*.*)");
    if (fileName.isEmpty())
        return;

    int w = m_player->get_width();
    int h = m_player->get_height(); 
    float fps = m_player->get_fps();
    quicktime_recorder *recorder = quicktime_recorder::create(fileName.toLatin1(), w, h, fps); 
    if (!recorder) {
        QMessageBox::critical(this, "Error", "Creation of QuickTime recorder failed!");
        return;
    }

    setEnabled(false);
    QProgressDialog progress("Recording...", "Abort", 0, m_player->get_duration(), this);
    progress.setWindowModality(Qt::WindowModal);

    void *pbuffer = m_player->get_buffer();
    void *rbuffer = recorder->get_buffer();
    int nextTime = 0;
    while (nextTime >= 0) {
        progress.setValue(nextTime);

        m_player->set_time(nextTime);
        glw->setPixels(w, h, GL_BGRA_EXT, GL_UNSIGNED_BYTE, pbuffer);
        glw->getPixels(w, h, GL_BGRA_EXT, GL_UNSIGNED_BYTE, rbuffer);

        recorder->append_frame();
        nextTime = m_player->get_next_time(nextTime);

        if (progress.wasCanceled())
            break;
    }

    recorder->finish();

    setEnabled(true);
    timeSlider->setValue(0);
    return;
}


void MainWindow::on_timeSlider_valueChanged(int value) {
    if (m_player && !m_player->is_playing()) {
        m_player->set_time(value);
        glw->setPixels(m_player->get_width(), m_player->get_height(),
                       GL_BGRA_EXT, GL_UNSIGNED_BYTE, m_player->get_buffer());
    }
}


void MainWindow::on_playButton_clicked() {
    if (m_timer->isActive()) {
        m_timer->stop();
        m_player->stop();
        playButton->setText(">");
        timeSlider->setEnabled(true);
    } else {         
        m_timer->start();
        m_player->start();
        playButton->setText("||");
        timeSlider->setEnabled(false);
    }
}


void MainWindow::do_play() {
    m_player->update();
    glw->setPixels(m_player->get_width(), m_player->get_height(),
                       GL_BGRA_EXT, GL_UNSIGNED_BYTE, m_player->get_buffer());
    timeSlider->setValue(m_player->get_time());
}

#endif

