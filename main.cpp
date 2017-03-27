#include <QGuiApplication>
#include <QQmlApplicationEngine>
#if __linux__
#include <QtAndroid>
#include <QtAndroidExtras/QAndroidJniObject>
#endif

#include "qisystemdispatcher.h"

#include <QtDebug>
int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));

#if __APPLE__
#if defined(Q_OS_IOS)
    QVariantMap map;
    map["style"] = 2;

    QISystemDispatcher::instance()->dispatch("activityIndicatorStartAnimation",map);
#else//OS
    qDebug()<<"OS";
#endif
    //startActivity(new Intent(Settings.ACTION_WIFI_SETTINGS));
    //http://stackoverflow.com/questions/25024615/open-android-settings-from-qt-appcom-android-settings
#elif __linux__//for android system
    QtAndroid::hideSplashScreen();

    //startActivity(new Intent(Settings.ACTION_WIFI_SETTINGS));
    //http://stackoverflow.com/questions/25024615/open-android-settings-from-qt-appcom-android-settings


    QAndroidJniObject wifiSettings = QAndroidJniObject::fromString("android.settings.WIFI_SETTINGS");
    QAndroidJniObject intent("android/content/Intent","(Ljava/lang/String;)V",
                             wifiSettings.object<jstring>());
    if ( intent.isValid() )
        QtAndroid::startActivity(intent, 0);
#else
    qDebug()<<"Unknown compiler";
#endif

    return app.exec();
}
