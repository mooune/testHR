//
//  HRViewController.h
//
//
//  Created by Alexandre Poisson on 1st june 2014
//  Edited on 10/10/2015
//  Copyright (c) 2015, Alexandre Poisson
//
//
//  This ViewController is the tutorial appearing at the begining
//



#import "AppDelegate.h"
#import <UIKit/UIKit.h>
#import <AVFoundation/AVFoundation.h>
#import <QuartzCore/QuartzCore.h>
#import <CoreMedia/CoreMedia.h>
#import <Accelerate/Accelerate.h>
#import "HRViewController.h"
#import "GraphView.h"
#import <iAd/iAd.h>

#define BUFFERCOMPPULSE 100

@interface HRViewController : UIViewController <ADBannerViewDelegate, AVCaptureVideoDataOutputSampleBufferDelegate> {
    
    double buffer[160]; //buffer contains more element to have a good signal after low pass filter
    double scaledBuffer[128];  // buffer to store the value
    double detrendBuffer[128]; // buffer to store the values after the removal of the polynomial trend
    int indexB;
    int bufferCompPulse[BUFFERCOMPPULSE];
    int nCompPulse;
    
}
@property int pulseDisplayed;
@property (nonatomic, strong) AVCaptureSession *captureSession;
@property (nonatomic, strong) AVCaptureVideoDataOutput *dataOutput;
@property (nonatomic) AVCaptureDeviceInput *videoDeviceInput;
@property (nonatomic) int nFramesW;
@property (weak, nonatomic) IBOutlet ADBannerView *adBanner;
@property (weak, nonatomic) IBOutlet UIProgressView *progressView;
@property (weak, nonatomic) IBOutlet UIButton *startButton;
@property (weak, nonatomic) IBOutlet UIButton *stopButton;
@property (strong, nonatomic) IBOutlet UILabel *pulseLabel;
@property (weak, nonatomic) IBOutlet UILabel *progressLabel;
@property (nonatomic) float progressValue;
@property (nonatomic, retain) IBOutlet GraphView *graphView;
@property (weak, nonatomic) IBOutlet UITextField *LiveInstruction;

- (IBAction)startRecording:(id)sender;
- (IBAction)stopRecording:(id)sender;
-(void)increaseProgressValue;
-(void)addToCompPulseBuffer:(int)x :(int)indexBuffer;

@end
