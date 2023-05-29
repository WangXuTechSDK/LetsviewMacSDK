#ifdef __OBJC__
#import <Cocoa/Cocoa.h>
#else
#ifndef FOUNDATION_EXPORT
#if defined(__cplusplus)
#define FOUNDATION_EXPORT extern "C"
#else
#define FOUNDATION_EXPORT extern
#endif
#endif
#endif

#import "WXCastMacSender.h"
#import "WXCastWindowItem.h"
#import "WXCastSenderVideoOptions.h"
#import "WXMirrorLogger.h"
#import "WXMirrorDevice.h"
#import "WXMirrorCore.h"
#import "WXMirrorCode.h"
#import "WXGCDAsyncSocket.h"
#import "WXGCDAsyncUdpSocket.h"
#import "WXCastDeviceTool.h"
#import "WXWebSocketServer.h"
#import "WXWebSocketClient.h"
#import "WXWebSocketInfo.h"
#import "WXBGMManager.h"

FOUNDATION_EXPORT double LetsviewMacSDKVersionNumber;
FOUNDATION_EXPORT const unsigned char LetsviewMacSDKVersionString[];

