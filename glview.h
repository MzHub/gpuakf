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
#ifndef INCLUDED_GLVIEW_H
#define INCLUDED_GLVIEW_H

#include "glslmgr.h"

class GLView : public QGLWidget {
    Q_OBJECT
public:
    GLView(QWidget *parent);
    ~GLView();

	void initializeGL();
	void resizeGL(int w, int h);
	void paintGL();

    void mousePressEvent( QMouseEvent *e );
    void mouseReleaseEvent( QMouseEvent *e );
    void mouseMoveEvent( QMouseEvent *e );
    void wheelEvent(QWheelEvent *e);

    void setOrigin(const QPoint& origin);
    void setZoom(float zoom);

    int buildStatus() { return m_glslMgr->buildStatus(); }
    float zoom() const { return m_zoom; }
    QPoint origin() const { return m_origin; }
    int width() const { return m_width; }
    int height() const { return m_height; }

	void setPixels(int w, int h, GLenum format, GLenum type, void *pixels);
    void getPixels(int w, int h, GLenum format, GLenum type, void *pixels);

public slots:
    void buildLog();
    void zoomIn();
    void zoomOut();
    void reset();

	void updateKernel();
    void process();

private:
    GLSLMgr *m_glslMgr;
    int m_processN;
	int m_width;
    int m_height;
    QPoint m_origin;
    float m_zoom;
    bool m_drag;
    QPoint m_dragPos;
    QPoint m_dragOrigin;
    QImage m_jetImage;

	enum {
		TEX_KRNL = 0,
		TEX_KRNLX4,
        TEX_NOISE,
		TEX_SRC,
		TEX_DST,
        TEX_LIC,
        TEX_A,
		TEX_TFM,
		TEX_TMP0,
		TEX_TMP1,
		TEX_MAX
	};
	int m_N;
	GLuint m_tex[TEX_MAX];
	GLuint m_fbo;
    GLuint m_jet;
};

#endif
