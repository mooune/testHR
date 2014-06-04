/*
 File: GraphView.m
 Abstract: A custom view for plotting history of x
 */

#import "GraphView.h"
#import "ViewController.h"
#import "scaleAndCenter.h"
#import "getPulseTemporal.h"

@implementation GraphView


- (void)addX:(double)x {

	// Add to history.
    history[nextIndex] = x;
    scaleAndCenter_initialize();
    scaleAndCenter(history, scaledDatas);
    scaleAndCenter_terminate();
	// Advance the index counter.
    nextIndex = (nextIndex + 1) % 128;
    
    // Mark itself as needing to be redrawn.
	[self setNeedsDisplay];
    
    /*
    // Compute the pulse. It Works
     u_int8_t temp = getPulseTemporal(scaledDatas,30.00);
    NSLog(@" %d", temp);
     */
    
}

- (void)drawGraphInContext:(CGContextRef)context withBounds:(CGRect)bounds {
    
    // Save any previous graphics state settings before setting the color and line width for the current draw.
    CGContextSaveGState(context);
	CGContextSetLineWidth(context, 1.0);
    
    /*
	// Draw the intermediate lines
     CGFloat temp;
 
    CGFloat value;
	CGContextSetGrayStrokeColor(context, 0.6, 1.0);
	CGContextBeginPath(context);
	for (value = -5 + 1.0; value <= 5 - 1.0; value += 1.0) {
        
		if (value == 0.0) {
			continue;
		}
		temp = 0.5 + roundf(bounds.origin.y + bounds.size.height / 2 + value / (2 * 5) * bounds.size.height);
		CGContextMoveToPoint(context, bounds.origin.x, temp);
		CGContextAddLineToPoint(context, bounds.origin.x + bounds.size.width, temp);
	}
	CGContextStrokePath(context);
	
	// Draw the center line
	CGContextSetGrayStrokeColor(context, 0.25, 1.0);
	CGContextBeginPath(context);
	temp = 0.5 + roundf(bounds.origin.y + bounds.size.height / 2);
	CGContextMoveToPoint(context, bounds.origin.x, temp);
	CGContextAddLineToPoint(context, bounds.origin.x + bounds.size.width, temp);
	CGContextStrokePath(context);
    CGContextSetRGBFillColor (context, 0, 0, 1,1);
    // Restore previous graphics state.
     */
    CGContextRestoreGState(context);
}

- (void)drawHistoryFromIndex:(NSUInteger)index inContext:(CGContextRef)context bounds:(CGRect)bounds {

    CGFloat value;

 
 CGContextBeginPath(context);
 for (NSUInteger counter = 0; counter < 128; ++counter) {
 // UIView referential has the Y axis going down, so we need to draw upside-down.

 value = scaledDatas[(index + counter) % 128] - 0.5;

 if (counter > 0) {
 CGContextAddLineToPoint(context, bounds.origin.x + (float)counter / (float)(128 - 1) * bounds.size.width, bounds.origin.y + bounds.size.height / 2 + value * bounds.size.height / 2);
 } else {
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
