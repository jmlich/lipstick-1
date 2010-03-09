/***************************************************************************
**
** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (directui@nokia.com)
**
** This file is part of duihome.
**
** If you have questions regarding the use of this file, please contact
** Nokia at directui@nokia.com.
**
** This library is free software; you can redistribute it and/or
** modify it under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation
** and appearing in the file LICENSE.LGPL included in the packaging
** of this file.
**
****************************************************************************/

#include "home.h"
#include "desktop.h"
#include "notificationarea.h"
#include "mainwindow.h"
#include "statusareawindow.h"
#include "statusarea.h"
#include "homenotificationsink.h"

#include <DuiApplicationPage>
#include <DuiModalSceneWindow>
#include <DuiOverlay>
#include <DuiPannableViewport>
#include <DuiButton>
#include <DuiSceneManager>
#include <DuiApplication>
#include <QGraphicsLinearLayout>
#include "homeapplication.h"

// TODO: make this stylable
static const int NOTIFICATIONAREA_TRANSITION_DURATION = 400;

Home::Home(QGraphicsItem *parent) :
    DuiSceneWindow(parent),
    notificationAreaState(Closed),
    desktop(new Desktop(this)),
    statusAreaWindow(new StatusAreaWindow),
    notificationAreaViewportOverlay(new DuiOverlay),
    notificationAreaViewport(new DuiPannableViewport(notificationAreaViewportOverlay)),
    notificationAreaVisible(false),
    eventCaptureWidget(0),
    desktopSourceY(0),
    desktopDestY(0)
{
    setObjectName("Home");
    statusAreaWindow->show();

    // Use the desktop as the central widget
    QGraphicsLinearLayout *layout = new QGraphicsLinearLayout(Qt::Vertical);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addItem(desktop);
    setLayout(layout);

    // Create notification area
    notificationArea = new NotificationArea(this);
    notificationAreaViewport->setObjectName("NotificationAreaViewport");
    notificationAreaViewport->setWidget(notificationArea);
    notificationAreaViewport->setZValue(1);
    notificationAreaViewport->hide();
    connect(notificationArea, SIGNAL(notificationCountChanged(int)), this, SLOT(notificationCountChanged(int)));
    connect(statusAreaWindow->statusArea(), SIGNAL(toggleNotificationArea()), this, SLOT(toggleNotificationArea()));
    notificationAreaViewportOverlay->setObjectName("NotificationAreaViewportOverlay");
    MainWindow::instance()->sceneManager()->hideWindowNow(notificationAreaViewportOverlay);

    // Configure the notification area timeline
    notificationAreaTimeLine.setDuration(NOTIFICATIONAREA_TRANSITION_DURATION);
    connect(&notificationAreaTimeLine, SIGNAL(valueChanged(qreal)), this, SLOT(notificationAreaTimeLineValueChanged(qreal)));
    connect(&notificationAreaTimeLine, SIGNAL(finished()), this, SLOT(notificationAreaTimeLineFinished()));
}

Home::~Home()
{
    delete statusAreaWindow;
    delete notificationAreaViewportOverlay;
    delete eventCaptureWidget;
}

void Home::notificationCountChanged(int count)
{
    if (notificationAreaVisible) {
        if (count == 0) {
            setNotificationAreaVisible(false);
        } else {
            updateNotificationAreaGeometry();
            updateGeometry();
        }
    }
}

void Home::notificationAreaTimeLineValueChanged(qreal value)
{
    // Calculate the desktop position
    qreal delta = desktopDestY - desktopSourceY;
    qreal y = desktopSourceY + delta * value;
    setPos(0, y);

    // Calculate the notification area position and size.
    // When the state is opening or closing, the notification area slides down/up.
    // When the state is open, the size is animated according to changes in notification count.
    switch (notificationAreaState) {
    case Opening:
    case Closing:
        notificationAreaViewport->setPos(0, y - notificationAreaViewport->size().height());
        if (!notificationAreaViewport->isVisible()) {
            notificationAreaViewport->setVisible(true);
        }
        break;
    case Open:
        notificationAreaViewport->setGeometry(QRectF(0, 0, notificationAreaViewport->size().width(), y));
        break;
    default:
        break;
    }
}

void Home::notificationAreaTimeLineFinished()
{
    switch (notificationAreaState) {
    case Opening:
        notificationAreaState = Open;
        break;
    case Closing:
        notificationAreaState = Closed;
        notificationAreaViewport->setVisible(false);
        desktop->setNotificationAreaOpen(false);
        MainWindow::instance()->sceneManager()->hideWindowNow(notificationAreaViewportOverlay);
        break;
    default:
        break;
    }
}

void Home::setNotificationAreaVisible(bool visible)
{
    if (visible == notificationAreaVisible) {
        return;
    }
    notificationAreaVisible = visible;

    HomeApplication *application = dynamic_cast<HomeApplication *>(qApp);
    if (application != NULL) {
        application->homeNotificationSink().setNotificationAreaVisible(visible);
    }

    if (visible) {
        desktop->setNotificationAreaOpen(true, "");
        eventCaptureWidget = new MouseEventCaptureWidget(desktop);
        connect(eventCaptureWidget, SIGNAL(eventReceived(QGraphicsSceneMouseEvent *)), this, SLOT(mouseEventReceived()));
        notificationAreaState = Opening;
        MainWindow::instance()->sceneManager()->showWindowNow(notificationAreaViewportOverlay);
    } else {
        delete eventCaptureWidget;
        eventCaptureWidget = 0;
        notificationAreaState = Closing;
    }

    updateNotificationAreaGeometry();
    updateGeometry();
}

void Home::updateNotificationAreaGeometry()
{
    // Set the notificationarea viewport width, so that the preferred height of
    // notification area will become valid
    notificationAreaViewport->setGeometry(QRectF(notificationAreaViewport->pos(), QSizeF(size().width(), notificationAreaViewport->size().height())));

    // Set the geometry of the notification viewport according to the size of the notification area
    qreal maxNotificationAreaHeight = size().height() - statusAreaWindow->statusArea()->boundingRect().height();
    qreal notificationAreaHeight = notificationArea->preferredHeight();
    qreal notificationAreaVPHeight = qMin(maxNotificationAreaHeight, notificationAreaHeight);
    notificationAreaViewport->setGeometry(
        QRectF(QPointF(0, notificationAreaVisible ? notificationAreaViewport->pos().y() : -notificationAreaVPHeight),
               QSizeF(size().width(), notificationAreaVPHeight)));

    // Enable or disable panning of notificationarea viewport depending on the height of the area
    bool needNotificationPanning = notificationAreaHeight > maxNotificationAreaHeight;
    if (needNotificationPanning != notificationAreaViewport->isEnabled()) {
        notificationAreaViewport->setEnabled(needNotificationPanning);
    }

    // Store the current desktop position for animation
    desktopSourceY = pos().y();

    // Move the desktop to give space to the notification area, if it's visible
    desktopDestY = notificationAreaVisible ? notificationAreaVPHeight : 0;

    if (desktopSourceY != desktopDestY) {
        if (notificationAreaTimeLine.state() == QTimeLine::Running) {
            notificationAreaTimeLine.stop();
            notificationAreaTimeLine.setCurrentTime(0);
        }
        notificationAreaTimeLine.start();
    }

    if (notificationAreaVisible) {
        // The notification area shows recent notifications at the bottom, make it visible
        panNotificationAreaToBottom();
    }
}

void Home::mouseEventReceived()
{
    toggleNotificationArea();
}

void Home::toggleNotificationArea()
{
    setNotificationAreaVisible(!notificationAreaVisible);
}

void Home::panNotificationAreaToBottom()
{
    // The notification area shows recent notifications at the bottom, make it visible
    notificationAreaViewport->setPosition(QPointF(0, notificationArea->preferredHeight() - notificationAreaViewport->size().height()));
}

void Home::setGeometry(const QRectF &rect)
{
    DuiSceneWindow::setGeometry(rect);

    if (rect.size() != previousSize) {
        // The size of the page has changed
        previousSize = rect.size();

        if (notificationAreaVisible) {
            // Close the notification area if it was open
            setNotificationAreaVisible(false);
        }
    }
}

QRectF Home::boundingRect() const
{
    return desktop->boundingRect();
}

MouseEventCaptureWidget::MouseEventCaptureWidget(QGraphicsItem *parent) :
    DuiWidget(parent)
{
}

MouseEventCaptureWidget::~MouseEventCaptureWidget()
{
}

QRectF MouseEventCaptureWidget::boundingRect() const
{
    return QRectF(QPointF(), parentWidget()->size());
}

void MouseEventCaptureWidget::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit eventReceived(event);
}

void MouseEventCaptureWidget::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    emit eventReceived(event);
}

void MouseEventCaptureWidget::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    emit eventReceived(event);
}