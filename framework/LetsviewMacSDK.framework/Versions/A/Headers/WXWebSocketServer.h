#import <Foundation/Foundation.h>
#import "WXGCDAsyncSocket.h"

@protocol WXWebSocketServerDelegate;

#ifndef htonll
#define htonll(x) __DARWIN_OSSwapInt64(x)
#endif

#ifndef ntohll
#define ntohll(x) __DARWIN_OSSwapInt64(x)
#endif

@interface NSString (WXWebSocketServer)
- (id)sha1base64;
- (id)webSocketFrameData;
@end

@interface NSData (WXWebSocketServer)
- (NSData *)webSocketFrameData;
- (NSData *)webSocketBinaryData;
@end

@interface WXWebSocketServer : NSObject

- (void)startWithPort:(NSUInteger)port delegate:(id<WXWebSocketServerDelegate>)delegate Block:(void (^)(BOOL done))block;

- (void)stop;

- (void)disDisconnectSocket:(NSData *)data;

- (BOOL)isRunning;

@property (nonatomic, readonly) NSUInteger port;
@property (nonatomic, readonly) NSUInteger clientCount;
@property (nonatomic, strong) NSArray <NSString *>*keys;
@property (nonatomic, strong) NSMutableArray *connections;

@end

@protocol WXWebSocketServerDelegate
- (void)webSocketServer:(WXWebSocketServer *)webSocketServer didAcceptSocket:(WXGCDAsyncSocket *)socket;
- (void)webSocketServer:(WXWebSocketServer *)webSocketServer didAcceptConnection:(WXGCDAsyncSocket *)connection;
- (void)webSocketServer:(WXWebSocketServer *)webSocketServer clientDisconnected:(WXGCDAsyncSocket *)connection withError:(NSError *)error;
- (void)webSocketServer:(WXWebSocketServer *)webSocketServer didReceiveData:(NSData *)data fromConnection:(WXGCDAsyncSocket *)connection;

// Data is passed to you as it was received from the socket, ie. with header & masked
// We disconnect the connection immediately after your delegate call returns.
// This always disconnect behavior sucks and should be fixed, but requires more
// intelligent error handling, so feel free to fix that.
- (void)webSocketServer:(WXWebSocketServer *)webSocketServer couldNotParseRawData:(NSData *)rawData fromConnection:(WXGCDAsyncSocket *)connection error:(NSError *)error;
@end

@interface WXGCDAsyncSocket (WXWebSocketServer)

- (void)sendWebSocketMessage:(NSString *)msg;

- (void)sendWebSocketData:(NSData *)data;

- (void)sendPONGString;
@end
