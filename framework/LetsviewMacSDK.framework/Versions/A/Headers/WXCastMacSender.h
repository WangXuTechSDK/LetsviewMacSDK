#import <Foundation/Foundation.h>
//! Project version number for WXCastMacSender.
FOUNDATION_EXPORT double WXCastMacSenderVersionNumber;

//! Project version string for WXCastMacSender.
FOUNDATION_EXPORT const unsigned char WXCastMacSenderVersionString[];

#import "WXCastSenderVideoOptions.h"
#import "WXCastWindowItem.h"

@class WXMirrorDevice;
@class WXCastSenderVideoOptions;
@protocol WXCastMacSenderDelegate;

NS_ASSUME_NONNULL_BEGIN

/****************    Error Code    ****************/

/// 搜索服务错误码
typedef NS_ENUM(NSInteger,  WXCastMacSenderError) {
    WXCastMacSenderErrorUnknow = 1000,                       // 未知错误
    WXCastMacSenderErrorRegistFail = 1010,                   // 未完成激活
    WXCastMacSenderErrorAudioInstallCancel = 2011,           // 安装声卡，用户取消
    WXCastMacSenderErrorAudioInstallFail = 2012,             // 安装声卡失败
    WXCastMacSenderErrorCastUnusual = 3010,                  // 投屏异常
    WXCastMacSenderErrorCastTimeout = 3011,                  // 直连投屏超时
    WXCastMacSenderErrorCastRefuse = 3012,                   // 投屏被拒绝
    WXCastMacSenderErrorCastRecordPermission = 3013,         // 录屏权限未开启
    WXCastMacSenderErrorCastRegistAuthority = 3014,          // 未开通权限，联系开发商沟通
    WXCastMacSenderErrorCastVideoFail = 3021,                // 连接视频失败
    WXCastMacSenderErrorCastAudioFail = 3022,                // 连接音频失败
};

@interface WXCastMacSender : NSObject

@property (nonatomic, weak) id<WXCastMacSenderDelegate> delegate;

/// 当前投屏设备数量
@property (nonatomic, assign) int mirrorCount;

/// Activate
/// @param name 设备名称
/// @param appId 申请 SDK 的 appId
/// @param appSecret 申请 SDK 的 appSecret (格式 xxxxx-xxxxx-xxxxx-xxxxx)
+ (void)registWithDeviceName:(NSString *_Nonnull)name appId:(NSString *_Nonnull)appId appSecret:(NSString *_Nonnull)appSecret registResult:(void (^_Nullable)(BOOL success))registResultBlock;

/// 配置视频参数
- (void)configVideoOptions:(WXCastSenderVideoOptions *)options;

/// 配置音频参数
- (void)configAudioOptions:(WXCastSenderAudioOption)option;


/// 开启连接服务
/// 开启后才能进行设备间通信连接，以及投屏
/// @param port 通信端口
- (void)startMirrorService:(int)port result:(void (^_Nullable)(BOOL))block;

/// 关闭连接服务
- (void)stopMirrorService;


/// 开启server后，开始发送设备信号，连接周边设备
/// @param port 进行广播搜索时需要配置，如果不使用可以设置为0，采用其他方式搜索。需要与接收端保持一致
/// @param backport 备用端口
- (void)startSearch:(int)port backPort:(int)backport;

/// 结束发送设备信号
- (void)stopSearch;


/// 检测屏幕录制权限
/// - Parameter videoPreInit: 非沙盒应用首次开启录制会比较慢，可以设置为 true 尝试提前初始化录制模块。
- (BOOL)recordPermissionCheck:(BOOL)videoPreInit;

/// 获取当前可以投屏的窗口数据
- (NSArray <WXCastWindowItem*>*)getCurrentWindows;

/// 选择要投屏的窗口
/// 可以设置为nil，全屏投屏
- (void)selectWindowItem:(WXCastWindowItem *_Nullable)item;


/// 投屏到设备
/// @param host 目标IP地址/目标投屏码
/// @param msg 携带自定义消息
/// @return 0=发送投屏消息失败 1=发送投屏消息成功 2=直连广播发起成功
- (int)mirrorToDeivce:(NSString * _Nonnull)host withCustomMsg:(NSString *_Nullable)msg;

/// 强制刷新视频数据
- (void)reloadVideo;

/// 暂停数据传输
/// @param pause true=暂停 false=传输
- (void)pauseMedia:(BOOL)pause;

/// 断开投屏
/// 传入空值断开所有投屏
- (void)stopMirror:(NSString *_Nullable)host;


/// 发送自定义消息
/// @param msg 消息内容
/// @param host 目标设备ip
/// @param completionHandler 发送结果回调 0=success 1=fail
- (void)sendCustomMsg:(NSString *_Nonnull)msg toDevice:(NSString *_Nonnull)host completionHandler:(nullable void (^)(int status))completionHandler;


/// 启动声卡
- (BOOL)startAudioPlugin;

/// 关闭声卡
/// 建议在应用关闭时调用
+ (void)stopAudioPlugin;

/// 安装声卡
/// 非沙盒应用可使用，沙盒应用需要单独安装
- (void)installAudioPlugin;

@end

@protocol WXCastMacSenderDelegate <NSObject>

@optional
/// 连接到设备
/// @param device 设备信息
- (void)wxCastMacSender:(WXCastMacSender *)sender connectDevice:(WXMirrorDevice *_Nonnull)device;

/// 与设备断开
/// @param device 设备信息
- (void)wxCastMacSender:(WXCastMacSender *)sender disconnectDevice:(WXMirrorDevice *_Nonnull)device;

/// 回调-开启投屏连接
- (void)wxCastMacSender:(WXCastMacSender *)sender startCast:(NSString *_Nonnull)host;

/// 回调-关闭投屏连接
- (void)wxCastMacSender:(WXCastMacSender *)sender stopCast:(NSString *_Nonnull)host;

/// 回调-接收自定义消息
- (void)wxCastMacSender:(WXCastMacSender *)sender receiveMsg:(NSString *_Nonnull)message fromDevice:(NSString *_Nonnull)host;

/// 回调-收到错误提示
- (void)wxCastMacSenderOnError:(nonnull NSError *)error;

/// 回调-安装声卡结果
- (void)wxCastMacSender:(WXCastMacSender *)sender installAudioPlugin:(BOOL)result;
@end

NS_ASSUME_NONNULL_END
