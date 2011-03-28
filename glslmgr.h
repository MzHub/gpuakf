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
#ifndef INCLUDED_GLSLMGR_H
#define INCLUDED_GLSLMGR_H

#include "ui_glslmgr.h"

class GLSLMgr : public QDialog, public Ui_GLSLMgr {
    Q_OBJECT
public:
    GLSLMgr(QGLWidget *parent);
    ~GLSLMgr();

    QGLWidget* parent() { return (QGLWidget*)QDialog::parent(); }
    GLuint pid(const char* name) { return m_prog[name]->programId(); }
    int buildStatus() const { return m_buildStatus; }

    bool initialize();
    void replaceInSource(const QString& pattern, const QString& text);

public slots:
    void build();
    void enableEdit();
    void sourceChanged(bool change);
    void copyToClipboard();

private:
    QShortcut *m_enableEdit;
    int m_buildStatus;
    QString m_log;
    QPlainTextEdit *m_logText;
    QList<QPlainTextEdit*> m_srcText;
    QPushButton *m_build;
    QMap<QString, QGLShaderProgram*> m_prog;
};

#endif
