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

#ifndef UT_SWITCHERVIEW_H
#define UT_SWITCHERVIEW_H

#include <QtTest/QtTest>
#include <QObject>
#include <DuiApplication>

class DuiWindow;
class TestSwitcherView;
class Switcher;
class SwitcherButton;
class DuiSceneManager;

class Ut_SwitcherView : public QObject
{
    Q_OBJECT

private slots:
    // Called before the first testfunction is executed
    void initTestCase();
    // Called after the last testfunction was executed
    void cleanupTestCase();
    // Called before each testfunction is executed
    void init();
    // Called after every testfunction
    void cleanup();

    // Test cases for detail view
    void testAutoPanningInDetailView();
    void testSnapIndexChangedInDetailView();
    void testPanningStoppedInDetailView();

    // Test cases for over view
    void testAutoPanningInOverView();
    void testButtonModesInOverviewMode();
    void testPanningStoppedInOverView();

private:
    void verifyButtonModesInOverviewMode(Dui::Orientation orientation);
    void verifyButtonModesInOverviewMode(QList< QSharedPointer<SwitcherButton> > &buttonList);

    QList< QSharedPointer<SwitcherButton> > createButtonList(int buttons);
    void appendMoreButtonsToList(int newButtons, QList< QSharedPointer<SwitcherButton> > &buttonList);

signals:
    void snapIndexChanged(int newPosition);
    void panningStopped();

private:
    DuiApplication *app;
    DuiSceneManager *duiSceneManager;
    Switcher *switcher;
    // The object being tested
    TestSwitcherView *m_subject;
};

#endif