//
//  Graphview.h
//
//  Created by Alexandre Poisson on 1st june 2014
//  Edited on 28/02/2015
//  Copyright (c) 2015, Alexandre Poisson
//
//
// A custom view for plotting a vector given in argument of displayRythm

#import <UIKit/UIKit.h>
#import <QuartzCore/QuartzCore.h>

@interface GraphView : UIView {
	NSUInteger nextIndex;
    double scaledDatas[128];
    int pulseBuffer[100];
   // int indexB;

}
@property int indexB;
- (void)displayRythm:(double [128]) x;
- (void)addToPulseBuffer:(int)x :(int)indexBuffer;

@end
