//
//  Macro.h
//  GCBaseFramework
//
//  Created by Geeks_Chen on 2019/1/3.
//  Copyright © 2019年 Geeks_Chen. All rights reserved.
//

#ifndef Macro_h
#define Macro_h

/* 文字 */
#define Font(name,size)  [UIFont fontWithName:name size:size]

/* 尺寸 */
#define kScreenWidth  [UIScreen mainScreen].bounds.size.width
#define kScreenHeight [UIScreen mainScreen].bounds.size.height
#define kScreenRect   [UIScreen mainScreen].bounds

///------ Ratio(Point)基于iPhone6 ------
#define kRatioX6(X) X*([UIScreen mainScreen].bounds.size.width / 375.)
#define kRatioY6(Y) Y*([UIScreen mainScreen].bounds.size.height / 667.)

/* 颜色 */
#define RGB(r, g, b) ([UIColor colorWithRed:(r)/255. green:(g)/255. blue:(b)/255. alpha:1.])
#define RGBA(r, g, b, a) ([UIColor colorWithRed:(r)/255. green:(g)/255. blue:(b)/255. alpha:a])
#define Color(hexValue)  [UIColor gc_colorWithHexString:hexValue]

/* 设备 */
#define kDevice_iPhone5 ([UIScreen instancesRespondToSelector:@selector(currentMode)] ? CGSizeEqualToSize(CGSizeMake(640, 1136), [[UIScreen mainScreen] currentMode].size) : NO)
#define kDevice_iPhone6 ([UIScreen instancesRespondToSelector:@selector(currentMode)] ? CGSizeEqualToSize(CGSizeMake(750, 1334), [[UIScreen mainScreen] currentMode].size) : NO)
#define kDevice_iPhone6P ([UIScreen instancesRespondToSelector:@selector(currentMode)] ? CGSizeEqualToSize(CGSizeMake(1242, 2208), [[UIScreen mainScreen] currentMode].size) : NO)
#define kDevice_iPhoneX ([UIScreen instancesRespondToSelector:@selector(currentMode)] ? CGSizeEqualToSize(CGSizeMake(1125, 2436), [[UIScreen mainScreen] currentMode].size) : NO)

///------ 安全边距 ------
#define kSafeArea_Top (IS_iPhoneX? 44: 20)
#define kSafeArea_Bottom (IS_iPhoneX? 34: 0)

///------ 应用程序版本号version ------
#define kAppVersion ([[[NSBundle mainBundle] infoDictionary] objectForKey:@"CFBundleShortVersionString"])

///------ iOS系统版本号 ------
#define iOS_Version ([[[UIDevice currentDevice] systemVersion] floatValue])

///------ <强烈推荐❤️>优酷大神ibireme的 Weak-Strong Dance
///省掉多处编写__weak __typeof(self) weakSelf = self; __strong __typeof(weakSelf) strongSelf = weakSelf;代码的麻烦 ------
/**
 使用说明
 Synthsize a weak or strong reference.
 
 Example:
 @weakify(self)
 [self doSomething^{
 @strongify(self)
 if (!self) return;
 ...
 }];
 
 */

#ifndef weakify
#if DEBUG
#if __has_feature(objc_arc)
#define weakify(object) autoreleasepool{} __weak __typeof__(object) weak##_##object = object;
#else
#define weakify(object) autoreleasepool{} __block __typeof__(object) block##_##object = object;
#endif
#else
#if __has_feature(objc_arc)
#define weakify(object) try{} @finally{} {} __weak __typeof__(object) weak##_##object = object;
#else
#define weakify(object) try{} @finally{} {} __block __typeof__(object) block##_##object = object;
#endif
#endif
#endif

#ifndef strongify
#if DEBUG
#if __has_feature(objc_arc)
#define strongify(object) autoreleasepool{} __typeof__(object) object = weak##_##object;
#else
#define strongify(object) autoreleasepool{} __typeof__(object) object = block##_##object;
#endif
#else
#if __has_feature(objc_arc)
#define strongify(object) try{} @finally{} __typeof__(object) object = weak##_##object;
#else
#define strongify(object) try{} @finally{} __typeof__(object) object = block##_##object;
#endif
#endif
#endif

// ---- 单例实现和定义宏
#define SingleInstance_H_(name) \
+ (instancetype)shared##name;

#define SingleInstance_M_(name) \
static id _instance = nil; \
+ (instancetype)shared##name \
{ \
static dispatch_once_t onceToken; \
dispatch_once(&onceToken, ^{ \
if (_instance == nil) \
{ \
_instance = [[self alloc] init]; \
} \
}); \
return _instance; \
} \
\
+ (instancetype)allocWithZone:(struct _NSZone *)zone \
{ \
static dispatch_once_t onceToken; \
dispatch_once(&onceToken, ^{ \
if (_instance == nil) \
{ \
_instance = [super allocWithZone:zone]; \
} \
}); \
return _instance; \
} \
\
+ (id)copyWithZone:(struct _NSZone *)zone \
{ \
return _instance; \
} \
+ (id)mutableCopyWithZone:(struct _NSZone *)zone \
{ \
return _instance; \
}

///------ other ------
#define kAppDelegate ([[UIApplication sharedApplication] delegate])
#define kAppWindow (kAppDelegate.window)
#define kAppRootViewController (kAppWindow.rootViewController)

#define kUserDefaults ([NSUserDefaults standardUserDefaults])
#define kNotificationCenter ([NSNotificationCenter defaultCenter])

#endif /* Macro_h */
