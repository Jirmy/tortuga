//
//  PoloI.h
//  PoloTouch
//
//  Created by Lady 3Jane Marie-France Tessier-Ashpool on 4/4/09.
//  Copyright 2009 TRX Systems. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <marcopolo.h>

@class OscilloscopeViewController;

@interface PoloI : rammarcopoloPolo <rammarcopoloPolo> {
    IBOutlet OscilloscopeViewController* mOscilloscopeViewController;
}
@end
