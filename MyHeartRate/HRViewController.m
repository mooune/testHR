//
//  HRViewController.m
//
//  Created by Alexandre Poisson on 1st june 2014
//  Edited on 28/02/2015
//  Copyright (c) 2015, Alexandre Poisson
//
//  This view controller can be considered as the main controller
//  It creates the capture session
//  send buffer to being displayed
//  ...



#import "HRViewController.h"
#import "GraphView.h"
#import "getPulseTemporal.h"
#import "scaledCenteredFiltered.h"
#import "myPolyDetrend.h"
#import "scaledCenteredFiltered_initialize.h"
#import "scaledCenteredFiltered_terminate.h"
#import "myPolyDetrend_initialize.h"
#import "myPolyDetrend_terminate.h"
#import "getPulseTemporal_initialize.h"
#import "getPulseTemporal_terminate.h"
#import <iAd/iAd.h>


//@interface HRViewController () <AVCaptureVideoDataOutputSampleBufferDelegate, ADBannerViewDelegate>
//@end


@implementation HRViewController


@synthesize pulseDisplayed;
@synthesize captureSession;
@synthesize dataOutput;
@synthesize nFramesW;
@synthesize pulseLabel;
@synthesize graphView;
@synthesize progressView;
//@synthesize progressLabel;
//@synthesize progressValue;


-(void)bannerViewWillLoadAd:(ADBannerView *)banner{
    NSLog(@"Ad Banner will load ad.");
}

-(void)bannerViewDidLoadAd:(ADBannerView *)banner{
    NSLog(@"Ad Banner did load ad.");
    // Show the ad banner.
    [UIView animateWithDuration:0.5 animations:^{
        self.adBanner.alpha = 1.0;
    }];
}

-(BOOL)bannerViewActionShouldBegin:(ADBannerView *)banner willLeaveApplication:(BOOL)willLeave{
    NSLog(@"Ad Banner action is about to begin.");
    
    return YES;
}

-(void)bannerViewActionDidFinish:(ADBannerView *)banner{
    NSLog(@"Ad Banner action did finish");
    [self newEstimationSession];

}


-(void)bannerView:(ADBannerView *)banner didFailToReceiveAdWithError:(NSError *)error{
    NSLog(@"Unable to show ads. Error: %@", [error localizedDescription]);
}


- (void)viewDidLoad
{
    NSLog(@" Hr View did Load");

    [super viewDidLoad];
    [self.progressView setTransform:CGAffineTransformMakeScale(1.0, 8.0)];
    self.progressLabel.text=[NSString stringWithFormat:@"0 %%"];
    self.pulseLabel.text=[NSString stringWithFormat:@""];
    [self.pulseLabel setOpaque:NO];
    self.pulseLabel.backgroundColor = [UIColor colorWithPatternImage:[UIImage imageNamed:@"coeurCropS.png"]];


    // Make self the delegate of the ad banner.
    self.adBanner.delegate = self;
    
    // Initially hide the ad banner.
    self.adBanner.alpha = 0.0;
    
}

-(void)newEstimationSession
{
    
    indexB = 0;
    nFramesW = 160;
    pulseDisplayed = 0;
    nCompPulse =0;
    self.progressValue = 0.0f;
    pulseLabel.text=[NSString stringWithFormat:@"--"];
    [pulseLabel setOpaque:NO];
    
    pulseLabel.backgroundColor = [UIColor colorWithPatternImage:[UIImage imageNamed:@"coeurCropS.png"]];
    // Session
    captureSession = [AVCaptureSession new];
    [captureSession setSessionPreset:AVCaptureSessionPreset352x288];
    
    // Capture device
    AVCaptureDevice *inputDevice = [AVCaptureDevice defaultDeviceWithMediaType:AVMediaTypeVideo];
    NSError *error;
    
    // Device input
    AVCaptureDeviceInput *deviceInput = [AVCaptureDeviceInput deviceInputWithDevice:inputDevice error:&error];
    [HRViewController setTorchMode:AVCaptureTorchModeOn forDevice:inputDevice];
    [HRViewController setFocusMode:AVCaptureFocusModeLocked forDevice:inputDevice];
    [HRViewController setExposureMode:AVCaptureExposureModeLocked forDevice:inputDevice];
    [HRViewController setFrameRate:30.0 forDevice:inputDevice]; // iphone 5 supports up to 30 frames per seconds
    [HRViewController setWhiteBalanceMode:AVCaptureWhiteBalanceModeLocked forDevice:inputDevice];
    
    if ( [captureSession canAddInput:deviceInput] )
        [captureSession addInput:deviceInput];
    
    dataOutput = [AVCaptureVideoDataOutput new];
    dataOutput.videoSettings = [NSDictionary dictionaryWithObject:[NSNumber numberWithUnsignedInt:kCVPixelFormatType_420YpCbCr8BiPlanarFullRange]
                                                           forKey:(NSString *)kCVPixelBufferPixelFormatTypeKey];
    [dataOutput setAlwaysDiscardsLateVideoFrames:NO];
    
    if ( [captureSession canAddOutput:dataOutput] )
        [captureSession addOutput:dataOutput];
    
    [captureSession commitConfiguration];
    
    dispatch_queue_t queue = dispatch_queue_create("VideoQueue", DISPATCH_QUEUE_SERIAL);
    
    [dataOutput setSampleBufferDelegate:self queue:queue];
    
    [captureSession startRunning];

    
}


-(void) viewWillAppear:(BOOL)animated {
    NSLog(@" Hr View will appear");

    
    [super viewWillAppear:animated];
    [self newEstimationSession];
}


- (void)captureOutput:(AVCaptureOutput *)captureOutput didOutputSampleBuffer:(CMSampleBufferRef)sampleBuffer fromConnection:(AVCaptureConnection *)connection
{
    CVImageBufferRef imageBuffer = CMSampleBufferGetImageBuffer(sampleBuffer);
    CVPixelBufferLockBaseAddress(imageBuffer, 0);
    
    size_t width = CVPixelBufferGetWidthOfPlane(imageBuffer, 0);
    size_t height = CVPixelBufferGetHeightOfPlane(imageBuffer, 0);
    
    uint8_t *baseAddress = CVPixelBufferGetBaseAddressOfPlane(imageBuffer, 0);
    
    double sumY = 0 ;
    
    // we only capture a section of the Buffer to save time
    
    for (uint y = round( height*1/3); y < round(height*2/3); y += 2)
    {
        for (uint x = round(width*1/3); x < round(width*2/3); x += 2)
        {
            sumY += *baseAddress;
            baseAddress += 1;
            
        }
    }
    // NSLog(@" sumY %f",sumY);  // NSLog output that is usefull to print sumY values in the console
    // values can then be imported in MATLAB to test the algorithm
    
    
    for (int count=0;count<nFramesW-1;count++)
    {
        buffer[count] = buffer[count+1];
    }
    
    buffer[nFramesW-1] = sumY;
    
    
    // release
    CVPixelBufferUnlockBaseAddress(imageBuffer, 0);
    
    dispatch_async(dispatch_get_main_queue(), ^{
        //   [graphView addX:sumY];
        //   pulseDisplayed = 0;
        
        
        scaledCenteredFiltered_initialize();
        scaledCenteredFiltered(buffer, scaledBuffer);
        scaledCenteredFiltered_terminate();
        
        myPolyDetrend_initialize();
        myPolyDetrend(scaledBuffer, detrendBuffer);
        scaledCenteredFiltered_terminate();
        
        [graphView displayRythm:scaledBuffer]; // the detrend buffer gives a strange result when displayed in the graphView
        
        // check  if the camera is obturated with the finger. if not, put a warning
        // it is done by analysing the luminance value.
        //this value is strongely correlated to the boundaries and increments in the for loops.
        //Todo: find a better alternative
        if (sumY < 50000)
        {
            pulseLabel.text = NSLocalizedString(@"Put Finger", nil);
        }
        
        else {
            pulseLabel.text = NSLocalizedString(@"Don't move your Finger", nil);

            getPulseTemporal_initialize();
            int pulseComp = getPulseTemporal(detrendBuffer,30.00);
            getPulseTemporal_terminate();
            
            if (pulseComp > 30 && pulseComp < 200 && self.progressValue < 1)      // getPulse return 0 when the pulse is not computed
            {
                
                pulseDisplayed = pulseComp ;
                [graphView addToPulseBuffer:pulseComp :graphView.indexB];
                
                graphView.indexB = graphView.indexB +1;
                // pulseLabel.text=[NSString stringWithFormat:@"%i",pulseComp];
                // NSLog(@" pulseDisplayed %i",pulseComp);
                [self addToCompPulseBuffer:pulseComp :nCompPulse];
                nCompPulse = nCompPulse + 1;
                [self increaseProgressValue];
            }
            else
            {
                // pulseDisplayed = 0;
            }
            
            
        }
        
        // NSLog(@" pulseDisplayed %i",pulseDisplayed);
        //
        
    });
}

-(void)addToCompPulseBuffer:(int)x :(int)indexBuffer
{
    bufferCompPulse[indexBuffer] =x;
    // NSLog(@" this is a new entry to pulse Buffer %i at index %i",pulseBuffer[indexBuffer],indexBuffer);
}


- (void) increaseProgressValue
{
    
    self.progressValue = self.progressValue + 0.005;
    self.progressView.progress = self.progressValue;
    self.progressLabel.text=[NSString stringWithFormat:@"%.f %%",100*self.progressValue];
    if (self.progressValue >= 1.0)
        
    {
        int somme;
        somme = 0;
        for (int count = 0; count<199; count++)
        {
            somme = somme + bufferCompPulse[count];
            
        }
        somme = somme / 200;
        pulseLabel.text=[NSString stringWithFormat:@"%i bpm",somme];
        [captureSession stopRunning];
        
        //   pulseLabel.text=[NSString stringWithFormat:@"Finish"];
    }
    //   [self performSelector:@selector(increaseProgressValue) withObject:self afterDelay:0.2];
    
    
}

- (void) viewDidUnload {
    NSLog(@" Hr View Did Unload");

    [super viewDidUnload];
    self.pulseLabel= nil;
    self.graphView = nil;
    [captureSession stopRunning];
    self.dataOutput = nil;
    self.captureSession = nil;
    //   [captureSession release];
    
}

-(void) viewWillDisappear:(BOOL)animated {
    NSLog(@" Hr View will disappear");

    [super viewWillDisappear:animated];
/*
    self.pulseLabel= nil;
    self.graphView = nil;
    [captureSession stopRunning];
    self.dataOutput = nil;
    self.captureSession = nil;
   */
}

- (void)dealloc {
    
}

// force torch
+ (void)setTorchMode:(AVCaptureTorchMode)torchMode forDevice:(AVCaptureDevice *)device
{
    if ([device hasFlash] && [device isTorchModeSupported:torchMode])
    {
        NSError *error = nil;
        if ([device lockForConfiguration:&error])
        {
            [device setTorchMode:torchMode];
            [device unlockForConfiguration];
        }
        else
        {
            NSLog(@"%@", error);
        }
    }
}
// force a fixed framerate
+ (void)setFrameRate:(double)frameRate forDevice:(AVCaptureDevice *)device
{
    NSError *error = nil;
    if ([device lockForConfiguration:&error])
    {
        // with activeFormat.videoSupportedFrameRateRanges
        [device setActiveVideoMaxFrameDuration:CMTimeMake(1, frameRate)];
        [device setActiveVideoMinFrameDuration:CMTimeMake(1, frameRate)];
        [device unlockForConfiguration];
    }
    else
    {
        NSLog(@"%@", error);
    }
    
}

// force focus
+ (void)setFocusMode:(AVCaptureFocusMode)focusMode forDevice:(AVCaptureDevice *)device
{
    NSError *error = nil;
    if ([device lockForConfiguration:&error])
    {
        [device setFocusMode:focusMode];
        [device unlockForConfiguration];
    }
    else
    {
        NSLog(@"%@", error);
    }
}

// force exposure
+ (void)setExposureMode:(AVCaptureExposureMode)exposureMode forDevice:(AVCaptureDevice *)device
{
    NSError *error = nil;
    if ([device lockForConfiguration:&error])
    {
        [ device setExposureModeCustomWithDuration:CMTimeMake(1,30) ISO:92 completionHandler:nil]; // it seems iso can be set from 46 to 736
        [device unlockForConfiguration];
    }
    else
    {
        NSLog(@"%@", error);
    }
}

// force white balance
+ (void)setWhiteBalanceMode:(AVCaptureWhiteBalanceMode)whiteBalanceMode forDevice:(AVCaptureDevice *)device
{
    NSError *error = nil;
    if ([device lockForConfiguration:&error])
    {
        if ([device isWhiteBalanceModeSupported:whiteBalanceMode])
        {
            [device setWhiteBalanceMode:whiteBalanceMode];
        }
        
        else
        {
            NSLog(@"White balance mode is not supported");
        }
        
        [device unlockForConfiguration];
    }
    else
    {
        NSLog(@"%@", error);
    }
}




- (IBAction)startRecording:(id)sender {
    
    [self viewWillAppear : NO];
    
}

- (IBAction)stopRecording:(id)sender {
    
    self.dataOutput = nil;
    self.captureSession = nil;
    
    
}
@end
