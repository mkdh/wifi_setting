
package org.qtproject.example.notification;

import android.app.Notification;
import android.app.NotificationManager;
import android.content.Context;
import android.content.Intent;
import android.util.Log;

public class PopUpWiFiSettingPage  extends org.qtproject.qt5.android.bindings.QtActivity
{
    public static void notify(String s)
    {
        Log.d("PopUpWiFiSettingPage:notify", "Java constructor called.");

        //startActivity(new Intent(Settings.ACTION_WIFI_SETTINGS));
    }
}
