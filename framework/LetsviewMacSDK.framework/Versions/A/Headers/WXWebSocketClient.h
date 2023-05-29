#import <Foundation/Foundation.h>
#import <Security/SecCertificate.h>
#import "WXWebSocketInfo.h"
#import "WXWebSocketClient.h"

typedef NS_ENUM(NSInteger, WXMCReadyState) {
    WXMC_CONNECTING   = 0,
    WXMC_OPEN         = 1,
    WXMC_CLOSING      = 2,
    WXMC_CLOSED       = 3,
};

typedef enum WXMCStatusCode : NSInteger {
    WXMCStatusCodeNormal = 1000,
    WXMCStatusCodeGoingAway = 1001,
    WXMCStatusCodeProtocolError = 1002,
    WXMCStatusCodeUnhandledType = 1003,
    // 1004 reserved.
    WXMCStatusNoStatusReceived = 1005,
    // 1004-1006 reserved.
    WXMCStatusCodeInvalidUTF8 = 1007,
    WXMCStatusCodePolicyViolated = 1008,
    WXMCStatusCodeMessageTooBig = 1009,
} WXMCStatusCode;

@class WXWebSocketClient;

extern NSString *const WXWebSocketClientErrorDomain;
extern NSString *const WXMCHTTPResponseErrorKey;
extern NSString *const WXWebSocketClientConnectTimeout;

#pragma mark - WXWebSocketClientDelegate

@protocol WXWebSocketClientDelegate;

#pragma mark - WXWebSocketClient

@interface WXWebSocketClient : NSObject <NSStreamDelegate>

@property (nonatomic, strong) WXWebSocketInfo *userData;

/// ip地址
@property (nonatomic, copy) NSString *ip;

/// 端口
@property (nonatomic, assign) NSInteger port;

/// 设备名称
@property (nonatomic, copy) NSString *deviceName;

/// 设备标识id
@property (nonatomic, copy) NSString *deviceId;

/// 设备类型 pc： 0  mac ：1  ios ： 2  Android : 3    TV : 4
@property (nonatomic, assign) NSInteger deviceType;

- (NSDictionary *)deviceInfo;

/// 服务器心跳计时配置
@property (nonatomic, assign) int timeout;
@property (nonatomic, assign) int timeoutCount;
@property (nonatomic, assign) int heartbeatCount;
@property (nonatomic, assign) BOOL heartbeatOpen;
@property (nonatomic, assign) BOOL heartbeatTimeout;
@property (nonatomic, strong) dispatch_source_t heartbeatTimer;

- (void)heartbeatStart;
- (void)heartbeatStop;

@property (nonatomic, weak) id <WXWebSocketClientDelegate> delegate;

@property (nonatomic, readonly) WXMCReadyState readyState;
@property (nonatomic, readonly, retain) NSURL *url;

@property (nonatomic, readonly) CFHTTPMessageRef receivedHTTPHeaders;

// Optional array of cookies (NSHTTPCookie objects) to apply to the connections
@property (nonatomic, readwrite) NSArray * requestCookies;

// This returns the negotiated protocol.
// It will be nil until after the handshake completes.
@property (nonatomic, readonly, copy) NSString *protocol;

// Protocols should be an array of strings that turn into Sec-WebSocket-Protocol.
- (id)initWithURLRequest:(NSURLRequest *)request protocols:(NSArray *)protocols allowsUntrustedSSLCertificates:(BOOL)allowsUntrustedSSLCertificates;
- (id)initWithURLRequest:(NSURLRequest *)request protocols:(NSArray *)protocols;
- (id)initWithURLRequest:(NSURLRequest *)request;

// Some helper constructors.
- (id)initWithURL:(NSURL *)url protocols:(NSArray *)protocols allowsUntrustedSSLCertificates:(BOOL)allowsUntrustedSSLCertificates;
- (id)initWithURL:(NSURL *)url protocols:(NSArray *)protocols;
- (id)initWithURL:(NSURL *)url;

// Delegate queue will be dispatch_main_queue by default.
// You cannot set both OperationQueue and dispatch_queue.
- (void)setDelegateOperationQueue:(NSOperationQueue*) queue;
- (void)setDelegateDispatchQueue:(dispatch_queue_t) queue;

// By default, it will schedule itself on +[NSRunLoop WXMC_networkRunLoop] using defaultModes.
- (void)scheduleInRunLoop:(NSRunLoop *)aRunLoop forMode:(NSString *)mode;
- (void)unscheduleFromRunLoop:(NSRunLoop *)aRunLoop forMode:(NSString *)mode;

// WXWebSocketClients are intended for one-time-use only.  Open should be called once and only once.
- (void)open;

- (void)closeWithTimeout;
- (void)close;
- (void)closeWithCode:(NSInteger)code reason:(NSString *)reason;

// Send a UTF8 String or Data.
- (void)send:(id)data;

// Send Data (can be nil) in a ping message.
- (void)sendPing:(NSData *)data;

- (NSUInteger)writeDataStack;

@end

#pragma mark - WXWebSocketClientDelegate

@protocol WXWebSocketClientDelegate <NSObject>

// message will either be an NSString if the server is using text
// or NSData if the server is using binary.
- (void)webSocket:(WXWebSocketClient *)webSocket didReceiveMessage:(id)message;

@optional

- (void)webSocketDidOpen:(WXWebSocketClient *)webSocket;
- (void)webSocket:(WXWebSocketClient *)webSocket didFailWithError:(NSError *)error;
- (void)webSocket:(WXWebSocketClient *)webSocket didCloseWithCode:(NSInteger)code reason:(NSString *)reason wasClean:(BOOL)wasClean;
- (void)webSocket:(WXWebSocketClient *)webSocket didReceivePong:(NSData *)pongPayload;
- (void)webSocketTimeOut:(WXWebSocketClient *)webSocket;

@end

#pragma mark - NSURLRequest (WXMCCertificateAdditions)

@interface NSURLRequest (WXMCCertificateAdditions)

@property (nonatomic, retain, readonly) NSArray *WXMC_SSLPinnedCertificates;

@end

#pragma mark - NSMutableURLRequest (WXMCCertificateAdditions)

@interface NSMutableURLRequest (WXMCCertificateAdditions)

@property (nonatomic, retain) NSArray *WXMC_SSLPinnedCertificates;

@end

#pragma mark - NSRunLoop (WXWebSocketClient)

@interface NSRunLoop (WXWebSocketClient)

+ (NSRunLoop *)WXMC_networkRunLoop;

@end
