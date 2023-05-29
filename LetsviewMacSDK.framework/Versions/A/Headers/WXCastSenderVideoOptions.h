//
//  WXCastSenderVideoConfiguration.h
//  WXCastiOSSender
//
//  Created by fbs on 2022/7/7.
//

#import <AVFoundation/AVFoundation.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(int, WXCastSenderVideoFps) {
    WXCastSenderVideoFps20 = 20,
    WXCastSenderVideoFps30 = 30, // 默认
};

typedef NS_ENUM(int, WXCastSenderVideoResolution) {
    WXCastSenderVideoResolution540 = 540,
    WXCastSenderVideoResolution720 = 720, // 默认
    WXCastSenderVideoResolution1080 = 1080,
    WXCastSenderVideoResolution2k = 1440 // 需要高清设备
};

typedef NS_ENUM(int, WXCastSenderVideoBitrate) {
    WXCastSenderVideoBitrateLow = 1,
    WXCastSenderVideoBitrateMedium = 2,
    WXCastSenderVideoBitrateHigh = 3, // 默认
    WXCastSenderVideoBitrateUltra = 4
};

typedef NS_ENUM(int, WXCastSenderVideoEncodeMode) {
    WXCastSenderVideoEncodeModeHardware = 0,
    WXCastSenderVideoEncodeModeSoftware = 1
};

typedef NS_ENUM(int, WXCastSenderAudioOption) {
    WXCastSenderAudioOptionNone = 0,
    WXCastSenderAudioOptionSystem = 1
};

@interface WXCastSenderVideoOptions : NSObject

+ (instancetype)defaultOptions;

/// 编码模式
/// 默认使用硬编码，部分 imac 设备上编码会有异常，需要切换软编码
@property (nonatomic, assign) WXCastSenderVideoEncodeMode encodeMode;

/// 分辨率
@property (nonatomic, assign) WXCastSenderVideoResolution resolution;

/// 帧率
@property (nonatomic, assign) WXCastSenderVideoFps fps;

/// 码率。越高，则画面越清晰，但占用的数据量更大，会收到网络情况和内存影响
@property (nonatomic, assign) WXCastSenderVideoBitrate bitrate;


- (CGSize)videoSize;

- (CGSize)aspectRatioVideoSize:(CGSize)bufferSize;

- (int)caculateVideoBitrate;


+ (void)sampleBufferFromPixelBuffer:(CMSampleBufferRef)inputSampleBuffer  withCGImage:(CGImageRef)imageRef;
+ (CMSampleBufferRef)adjustTime:(CMSampleBufferRef)sample by:(CMTime)offset;

@end

NS_ASSUME_NONNULL_END
