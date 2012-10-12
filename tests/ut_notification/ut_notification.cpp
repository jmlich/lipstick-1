/***************************************************************************
**
** Copyright (C) 2012 Jolla Ltd.
** Contact: Robin Burchell <robin.burchell@jollamobile.com>
**
** This file is part of lipstick.
**
** This library is free software; you can redistribute it and/or
** modify it under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation
** and appearing in the file LICENSE.LGPL included in the packaging
** of this file.
**
****************************************************************************/

#include <QtTest/QtTest>
#include "ut_notification.h"
#include "notification.h"
#include "notificationmanager_stub.h"

void Ut_Notification::testGettersAndSetters()
{
    QString appName = "appName1";
    QString appIcon = "appIcon1";
    QString summary = "summary1";
    QString body = "body1";
    QStringList actions = QStringList() << "action1a" << "action1b";
    QString icon = "icon1";
    QDateTime timestamp = QDateTime::currentDateTime();
    QVariantHash hints;
    hints.insert(NotificationManager::HINT_ICON, icon);
    hints.insert(NotificationManager::HINT_TIMESTAMP, timestamp);
    int expireTimeout = 1;

    // Ensure that the constructor puts things in place
    Notification notification(appName, appIcon, summary, body, actions, hints, expireTimeout);
    QCOMPARE(notification.appName(), appName);
    QCOMPARE(notification.appIcon(), appIcon);
    QCOMPARE(notification.summary(), summary);
    QCOMPARE(notification.body(), body);
    QCOMPARE(notification.actions(), actions);
    QCOMPARE(notification.expireTimeout(), expireTimeout);
    QCOMPARE(notification.icon(), icon);
    QCOMPARE(notification.timestamp(), timestamp);
    QCOMPARE(notification.localizedTimestamp(), timestamp.toString("hh:mm:ss"));

    appName = "appName2";
    appIcon = "appIcon2";
    summary = "summary2";
    body = "body2";
    actions = QStringList() << "action2a" << "action2b" << "action2c";
    icon = "icon2";
    timestamp = QDateTime::currentDateTime();
    hints.insert(NotificationManager::HINT_ICON, icon);
    hints.insert(NotificationManager::HINT_TIMESTAMP, timestamp);
    expireTimeout = 2;
    notification.setAppName(appName);
    notification.setAppIcon(appIcon);
    notification.setSummary(summary);
    notification.setBody(body);
    notification.setActions(actions);
    notification.setHints(hints);
    notification.setExpireTimeout(expireTimeout);
    QCOMPARE(notification.appName(), appName);
    QCOMPARE(notification.appIcon(), appIcon);
    QCOMPARE(notification.summary(), summary);
    QCOMPARE(notification.body(), body);
    QCOMPARE(notification.actions(), actions);
    QCOMPARE(notification.expireTimeout(), expireTimeout);
    QCOMPARE(notification.icon(), icon);
    QCOMPARE(notification.timestamp(), timestamp);
    QCOMPARE(notification.localizedTimestamp(), timestamp.toString("hh:mm:ss"));
}

void Ut_Notification::testSignals()
{
    QVariantHash hints;
    Notification notification(QString(), QString(), QString(), QString(), QStringList(), hints, 0);
    QSignalSpy summarySpy(&notification, SIGNAL(summaryChanged()));
    QSignalSpy bodySpy(&notification, SIGNAL(bodyChanged()));
    QSignalSpy iconSpy(&notification, SIGNAL(iconChanged()));
    QSignalSpy timestampSpy(&notification, SIGNAL(localizedTimestampChanged()));

    notification.setSummary("summary");
    QCOMPARE(summarySpy.count(), 1);
    notification.setSummary("summary");
    QCOMPARE(summarySpy.count(), 1);

    notification.setBody("body");
    QCOMPARE(bodySpy.count(), 1);
    notification.setBody("body");
    QCOMPARE(bodySpy.count(), 1);

    hints.insert(NotificationManager::HINT_ICON, "icon");
    hints.insert(NotificationManager::HINT_TIMESTAMP, "2012-10-01 18:04:19");
    notification.setHints(hints);
    QCOMPARE(iconSpy.count(), 1);
    QCOMPARE(timestampSpy.count(), 1);
    notification.setHints(hints);
    QCOMPARE(iconSpy.count(), 1);
    QCOMPARE(timestampSpy.count(), 1);
}

QTEST_MAIN(Ut_Notification)