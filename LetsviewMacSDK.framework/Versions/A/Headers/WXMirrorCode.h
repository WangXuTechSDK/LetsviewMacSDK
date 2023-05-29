//
//  WXMirrorCode.h
//  WXMirrorCore
//
//  Created by fbs on 2023/1/17.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface WXMirrorCode : NSObject

+ (NSString *)generate;

+ (NSString *)decode:(NSString *)code;

+ (NSString *)decode:(NSString *)prefix code:(NSString *)code;
@end

NS_ASSUME_NONNULL_END
