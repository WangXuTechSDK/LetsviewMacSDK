//
//  WXWebsocketInfo.h
//  WXMirrorCore
//
//  Created by fbs on 2023/4/5.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface WXWebSocketInfo : NSObject

@property (nonatomic, copy) NSString *key;
@property (nonatomic, copy) NSString *uuid;
@property (nonatomic, copy) NSString *host;
@property (nonatomic, assign) int port;

@property (nonatomic, copy) NSString *name;
/// pc： 0  mac ：1  ios ： 2  Android : 3    TV : 4
@property (nonatomic, assign) int type;
@property (nonatomic, assign) int version;

@end

NS_ASSUME_NONNULL_END
