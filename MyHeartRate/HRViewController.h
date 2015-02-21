//
//  ViewController.h
//
//  Created by Alexandre Poisson on 1st june 2014
//  Copyright (c) 2014, Alexandre Poisson
//
#import "AppDelegate.h"
#import <UIKit/UIKit.h>
#import <AVFoundation/AVFoundation.h>
#import <QuartzCore/QuartzCore.h>
#import <CoreMedia/CoreMedia.h>
#import <Accelerate/Accelerate.h>
#import "HRViewController.h"
#import "GraphView.h"


@interface HRViewController : UIViewController {
    
    double buffer[160]; //buffer contains more element to have a good signal after low pass filter
    double scaledBuffer[128];  // buffer to store the value
    double detrendBuffer[128]; // buffer to store the values after the removal of the polynomial trend
    int indexB;
    int bufferCompPulse[200];
    int nCompPulse;
}
@property (weak, nonatomic) IBOutlet UIProgressView *progressView;

@property (weak, nonatomic) IBOutlet UIButton *startButton;

@property (weak, nonatomic) IBOutlet UIButton *stopButton;

@property (strong, nonatomic) IBOutlet UILabel *pulseLabel;

@property (weak, nonatomic) IBOutlet UILabel *progressLabel;

@property (nonatomic) float progressValue;

@property (nonatomic, retain) IBOutlet GraphView *graphView;

- (IBAction)startRecording:(id)sender;
- (IBAction)stopRecording:(id)sender;
-(void)increaseProgressValue;
-(void)addToCompPulseBuffer:(int)x :(int)indexBuffer;
@end
