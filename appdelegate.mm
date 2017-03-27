#import "UIKit/UIKit.h"
#include <QtCore>
#include "qisystemdispatcher.h"

@interface QIOSApplicationDelegate
@end

@interface QIOSApplicationDelegate(AppDelegate)
@end

@implementation QIOSApplicationDelegate (AppDelegate)

// It just demonstrate how to override QIOSApplicationDelegate to get
// launch options via didFinishLaunchingWithOptions.
// QuickIOS do not bundle this code since it may conflict with
// other framework whose need this piece of information

- (BOOL)application:(UIApplication *)application
didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    Q_UNUSED(application);

    NSLog(@"didFinishLaunchingWithOptions: %@", [launchOptions description]);
    QISystemDispatcher* dispatcher = QISystemDispatcher::instance();
    dispatcher->addListener("activityIndicatorStartAnimation",activityIndicatorStartAniamtion);

    return YES;
}
static bool activityIndicatorStartAniamtion(QVariantMap& data) {
    Q_UNUSED(data);
    if ([[UIApplication sharedApplication] canOpenURL:[NSURL URLWithString:@"prefs:root=WIFI"]]) {
        [[UIApplication sharedApplication] openURL:[NSURL URLWithString:@"prefs:root=WIFI"]];
    } else {
        [[UIApplication sharedApplication] openURL:[NSURL URLWithString:@"App-Prefs:root=WIFI"]];
    }
    return true;
}
@end



