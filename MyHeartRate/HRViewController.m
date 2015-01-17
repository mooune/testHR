//
//  HRViewController.m
//
//  Created by Alexandre Poisson on 1st june 2014
//  Copyright (c) 2014, Alexandre Poisson
#import "HRViewController.h"
#import "GraphView.h"
#import "getPulseTemporal.h"
#import "scaleAndCenter.h"

@interface HRViewController () <AVCaptureVideoDataOutputSampleBufferDelegate>

@property (nonatomic, strong) AVCaptureSession *captureSession;
@property (nonatomic, strong) AVCaptureVideoDataOutput *dataOutput;
@property (nonatomic) AVCaptureDeviceInput *videoDeviceInput;
@property (nonatomic) int nFramesW;
//@property int pulseComp;
@property int pulseDisplayed;

@end


@implementation HRViewController


//@synthesize pulseComp;
@synthesize pulseDisplayed;
@synthesize captureSession;
@synthesize dataOutput;
@synthesize nFramesW;
@synthesize pulseLabel;

@synthesize graphView;


- (void)viewDidLoad
{
    [super viewDidLoad];
}

-(void) viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
    
    nFramesW = 128;
    pulseDisplayed = 0;
    pulseLabel.text=[NSString stringWithFormat:@"--"];
    
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


- (void)captureOutput:(AVCaptureOutput *)captureOutput didOutputSampleBuffer:(CMSampleBufferRef)sampleBuffer fromConnection:(AVCaptureConnection *)connection
{
    // NSLog(@" I am in CaptureOuput");
    CVImageBufferRef imageBuffer = CMSampleBufferGetImageBuffer(sampleBuffer);
    CVPixelBufferLockBaseAddress(imageBuffer, 0);
    
    size_t width = CVPixelBufferGetWidthOfPlane(imageBuffer, 0);
    size_t height = CVPixelBufferGetHeightOfPlane(imageBuffer, 0);

    uint8_t *baseAddress = CVPixelBufferGetBaseAddressOfPlane(imageBuffer, 0);
    
    double sumY = 0 ;
  //  int pulseComp;
    
    
    // we only capture a section of the Buffer to save time
    
    for (uint y = round( height*1/3); y < round(height*2/3); y += 2)
    {
        for (uint x = round(width*1/3); x < round(width*2/3); x += 2)
        {
            sumY += *baseAddress;
            baseAddress += 1;
            
        }
    }
      NSLog(@" sumY %f",sumY);  // NSLog output that is usefull to print sumY values in the console
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
        scaleAndCenter_initialize();
        scaleAndCenter(buffer, scaledBuffer);
 
        scaleAndCenter_terminate();
       [graphView displayRythm:scaledBuffer];
   // switch  if the camera is obturated with the finger
        if (sumY < 50000)  // this value is strongely correlated to the boundaries and increments in the for loops. Todo: find a better alternative
        {
        pulseLabel.text=[NSString stringWithFormat:@"Put Finger"];        }
        
        else {
            
            getPulseTemporal_initialize();
            int pulseComp = getPulseTemporal(scaledBuffer,30.00);
            getPulseTemporal_terminate();
            if (pulseComp > 30 && pulseComp < 200)      // getPulse return 0 when the pulse is not computed
                                {
                                pulseDisplayed = pulseComp ;

                                }
            pulseLabel.text=[NSString stringWithFormat:@"%d",pulseDisplayed];
            
        }
        

    });

    
   // pulseComp=0.0;
    


}

- (void) viewDidUnload {
    [super viewDidUnload];
    self.pulseLabel= nil;
    self.graphView = nil;
    [captureSession stopRunning];
    self.dataOutput=nil;
    self.captureSession=nil;
 //   [captureSession release];
    
}

-(void) viewWillDisappear:(BOOL)animated {
    [super viewWillDisappear:animated];
    self.pulseLabel= nil;
    self.graphView = nil;
    [captureSession stopRunning];
    self.dataOutput=nil;
    self.captureSession=nil;
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
    
    [self viewWillAppear:NO];

  }

- (IBAction)stopRecording:(id)sender {

    self.dataOutput=nil;
    self.captureSession=nil;
    
}
@end
