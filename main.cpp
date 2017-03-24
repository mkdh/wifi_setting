#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtAndroid>
#include <QtAndroidExtras/QAndroidJniObject>
#include <QtDebug>
int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));
    QtAndroid::hideSplashScreen();


    qDebug() << __func__;
    /*
method 1
    QAndroidJniObject javaNotification = QAndroidJniObject::fromString("QQQ");
    QAndroidJniObject::callStaticMethod<void>("PopUpWiFiSettingPage",
                                       "notify",
                                       "(Ljava/lang/String;)V",
                                       javaNotification.object<jstring>());
    */



    /*
method 2
    //startActivity(new Intent(Settings.ACTION_WIFI_SETTINGS));
    //http://stackoverflow.com/questions/25024615/open-android-settings-from-qt-appcom-android-settings

    //crash code
    // It will make my app crash at "activity.callObjectMethod....." line
    QAndroidJniObject activity = QAndroidJniObject::callStaticObjectMethod("org/qtproject/qt5/android/QtNative", "activity", "()Landroid/app/Activity;");   //activity is valid
    if ( activity.isValid() )
    {
        // Equivalent to Jave code: 'Intent intent = new Intent();'
        QAndroidJniObject intent("android/content/Intent","()V");
        if ( intent.isValid() )
        {
            //http://stackoverflow.com/questions/11429090/how-to-open-wifi-settings-on-nook-nookcolor
            QAndroidJniObject param1 = QAndroidJniObject::fromString("com.android.settings");
            QAndroidJniObject param2 = QAndroidJniObject::fromString("com.android.se‌​ttings.wifi.Settings‌​_Wifi_Settings");

            if ( param1.isValid() && param2.isValid() )
            {
                // Equivalent to Jave code: 'intent.setClassName("com.android.phone", "com.android.phone.NetworkSetting");'
                intent.callObjectMethod("setClassName","(Ljava/lang/String;Ljava/lang/String;)Landroid/content/Intent;",param1.object<jobject>(),param2.object<jobject>());

                // Equivalent to Jave code: 'startActivity(intent);'
                activity.callObjectMethod("startActivity","(Landroid/content/Intent;)V",intent.object<jobject>());
            }
        }
    }
    */
    //method 3

    //startActivity(new Intent(Settings.ACTION_WIFI_SETTINGS));
    //http://stackoverflow.com/questions/25024615/open-android-settings-from-qt-appcom-android-settings
    QAndroidJniObject activity = QAndroidJniObject::callStaticObjectMethod("org/qtproject/qt5/android/QtNative", "activity", "()Landroid/app/Activity;");   //activity is valid
    if ( activity.isValid() )
    {
        // Equivalent to Jave code: 'Intent intent = new Intent();'
        //http://doc.qt.io/qt-5/qandroidjniobject.html#QAndroidJniObject-4
        QAndroidJniObject intent("android/content/Intent","(I)V", "Settings.ACTION_WIFI_SETTINGS");
        if ( intent.isValid() )
        {
            activity.callObjectMethod("startActivity","(Landroid/content/Intent;)V",intent.object<jobject>());
        }
    }

    qDebug() << "=======================";

    return app.exec();
}
