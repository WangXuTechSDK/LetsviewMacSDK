//
//  WXBGMManager.h
//  WXScreenRecordLib
//
//  Created by q f h on 2022/3/18.
//  Copyright © 2022 CocoaPods. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface WXBGMManager : NSObject

+ (BOOL)initBGM;

+ (void)closeBGM;

+ (instancetype)shared;

- (void) requestAccess;
@end

NS_ASSUME_NONNULL_END
