//
//  WXSoftwareVideoEncoder.h
//  WXCastMacSender
//
//  Created by fbs on 2022/10/18.
//

#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>

NS_ASSUME_NONNULL_BEGIN

@protocol WXSoftwareVideoEncoderDelegate;
@interface WXSoftwareVideoEncoder : NSObject

/// 编码后的画面宽度
@property (nonatomic, assign) int videoWidth;
/// 编码后的画面高度
@property (nonatomic, assign) int videoHeight;

/// 视频编码的帧率（fps）
/// 默认值为 20。用户可以自行设置帧率，建议不要超过 30 帧。
/// 帧率越大，画面越流畅
@property (nonatomic, assign) int videoFps;

/// 视频码率，均值，单位是（Mbps）
/// 码率越高，则画面越清晰，但占用的数据量更大，不利于传输
@property (nonatomic, assign) int videoBitrate;

/// 是否要输出 sps 信息
@property (nonatomic, assign) int spsMark;

/// type=0 sps+pps  type=1 frame  type=-1 fail
@property (nonatomic, copy) void (^output)(NSData *data, int type);

@property (nonatomic, weak) id<WXSoftwareVideoEncoderDelegate> delegate;

- (void)startRunning;

- (void)encodeH264SampleBuffer:(CMSampleBufferRef)sampleBuffer;

- (void)reset;

- (void)stopRunning;
@end

@protocol WXSoftwareVideoEncoderDelegate <NSObject>

- (void)softWareEncodedVideoInfo:(WXSoftwareVideoEncoder *)encoder;

- (void)softWareEncodedVideoFrame:(NSData *)data;

@end

NS_ASSUME_NONNULL_END
