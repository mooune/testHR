/*
 File: GraphView.h
 Abstract: Displays a graph
 Version: 2.6

 */

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
