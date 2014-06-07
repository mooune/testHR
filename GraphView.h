/*
 File: GraphView.h
 Abstract: Displays a graph
 Version: 2.6

 */

#import <UIKit/UIKit.h>
#import <QuartzCore/QuartzCore.h>

@interface GraphView : UIView {
	NSUInteger nextIndex;
	double history[128];
    double scaledDatas[128];
}

- (void)addX:(double)x;
- (void)displayRythm:(double [128]) x;
@end
