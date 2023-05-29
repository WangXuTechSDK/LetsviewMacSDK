//
//  WXCastWindowItem.h
//  WXCastMacSender
//
//  Created by fbs on 2023/5/8.
//

#import <Foundation/Foundation.h>
#import <Cocoa/Cocoa.h>

NS_ASSUME_NONNULL_BEGIN

@interface WXCastWindowItem : NSObject

@property (nonatomic, copy) NSString *uuid;

@property (nonatomic, copy) NSString *name;

@property (nonatomic, copy) NSString *status;

@property (nonatomic, assign) CGRect bounds;

@property (nonatomic, assign) int pid;

@property (nonatomic, assign) int number;

@end

NS_ASSUME_NONNULL_END
