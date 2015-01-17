/*
 File: GraphView.m
 Abstract: A custom view for plotting a vector given in argument of displayRythm
 */

#import "GraphView.h"
#import "HRViewController.h"
#import "scaleAndCenter.h"
#import "getPulseTemporal.h"

@implementation GraphView

- (void)displayRythm:(double [128]) x {
    for (int j=0;j<128;j++)
        {
            scaledDatas[j] = x[j];
        }
	[self setNeedsDisplay];

}

- (void)drawGraphInContext:(CGContextRef)context withBounds:(CGRect)bounds {
    
    // Save any previous graphics state settings before setting the color and line width for the current draw.
    CGContextSaveGState(context);
	CGContextSetLineWidth(context, 1.0);
    CGContextRestoreGState(context);
}

- (void)drawHistoryFromIndex:(NSUInteger)index inContext:(CGContextRef)context bounds:(CGRect)bounds {

    CGFloat value;
 CGContextBeginPath(context);
 for (NSUInteger counter = 0; counter < 128; ++counter) {
 // UIView referential has the Y axis going down, so we need to draw upside-down.

 value = scaledDatas[(index + counter) % 128] /2;
     
 if (counter > 0) {
 CGContextAddLineToPoint(context, bounds.origin.x + (float)counter / (float)(128 - 1) * bounds.size.width, bounds.origin.y + bounds.size.height / 2 + value * bounds.size.height / 2);
 }
 else {
 CGContextMoveToPoint(context, bounds.origin.x + (float)counter / (float)(128 - 1) * bounds.size.width, bounds.origin.y + bounds.size.height / 2 + value * bounds.size.height / 2);
 }
 }
    // Save any previous graphics state settings before setting the color and line width for the current draw.
    CGContextSaveGState(context);
    CGContextSetLineWidth(context, 2.0);

    CGContextSetRGBStrokeColor(context,1,0,0,1);
    CGContextSetRGBFillColor (context, 0, 0, 1,1);
	CGContextSetLineWidth(context, 2.0);
    CGContextStrokePath(context);
    // Restore previous graphics state.
    CGContextRestoreGState(context);
}


- (void)drawRect:(CGRect)clip {
    NSUInteger index = nextIndex;
    
	CGContextRef context = UIGraphicsGetCurrentContext();
	CGRect bounds = CGRectMake(0, 0, [self bounds].size.width, [self bounds].size.height);
	
	// create the graph
	[self drawGraphInContext:context withBounds:bounds];
	
    // plot x,y,z with anti-aliasing turned off
    CGContextSetAllowsAntialiasing(context, false);
    [self drawHistoryFromIndex:index inContext:context bounds:bounds];
    
    CGContextSetAllowsAntialiasing(context, true);
}


@end
