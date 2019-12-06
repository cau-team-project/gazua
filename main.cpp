#include <QtGui/QGuiApplication>
#include <QtCore/QDir>
#include <QtQuick/QQuickView>
#include <QtQml/QQmlEngine>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QTreeView>
#include <QTimer>
#include <QApplication>
#include "API.h"
#include "CoinInfoModel.h"
#include "CoinTreeModel.h"
#include "CoinTreeItem.h"
#include "UserInfo.h"

int main(int argc, char *argv[])
{
    //QGuiApplication app(argc, argv);
    QApplication app(argc, argv);

    QFile apiKeyFile("apikey.txt");
    if(!apiKeyFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "API KEY NOT FOUND!";
        return 1;
    }

    QString key;
    QString secret;

    QTextStream apiKeyStream(&apiKeyFile);

    if(!apiKeyStream.atEnd())
        key = std::move(apiKeyStream.readLine());
    if(!apiKeyStream.atEnd())
        secret = std::move(apiKeyStream.readLine());

    Gazua::API api{std::move(key), std::move(secret)};
    api.access();
    auto userInfo = std::make_shared<Gazua::UserInfo>();

    QStringList coinInfoModelHeader;
    coinInfoModelHeader << "1" << "2" << "3";
    auto coinTreeModel = std::make_shared<Gazua::CoinTreeModel>(coinInfoModelHeader, QString(), nullptr);
/*
    QQmlApplicationEngine engine;
    auto context = engine.rootContext();
    context->setContextProperty("userInfo", userInfo.get());
    context->setContextProperty("coinTreeModel", coinTreeModel.get());
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
*/

    QTreeView view;
    view.setModel(userInfo.get());
    view.setWindowTitle(QObject::tr("UserInfo"));
    view.expandAll();
    view.resize(500, 1000);
    view.show();

    QTreeView view2;
    view2.setModel(coinTreeModel.get());
    view2.setWindowTitle(QObject::tr("CoinTree"));
    view2.expandAll();
    //view2.setRootIndex(coinTreeModel->index(coinTreeModel->getRootItem()->childCount() - 1, 0, coinTreeModel->index(0, 0, QModelIndex())));
    view2.show();

    QTimer timer{};
    api.connect(&timer, &QTimer::timeout, &api, [&api, coinTreeModel, userInfo, &view, &view2] () {
        api.refreshCoinInfo(coinTreeModel);
        api.refreshUserInfo(userInfo);
        view.expandAll();
        //view2.expandAll();
    });
    timer.start(4000);

    return app.exec();
}
