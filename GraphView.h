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
}

- (void)displayRythm:(double [128]) x;
@end
