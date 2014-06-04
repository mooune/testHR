//
//  ViewController.m
//
//  Created by Alexandre Poisson on 30/06/14.
//
#import "ViewController.h"
#import "GraphView.h"
#import "getPulseTemporal.h"

@interface ViewController () <AVCaptureVideoDataOutputSampleBufferDelegate>

@property (nonatomic, strong) AVCaptureSession *captureSession;
@property (nonatomic, strong) AVCaptureVideoDataOutput *dataOutput;
@property (nonatomic) AVCaptureDeviceInput *videoDeviceInput;
@property (nonatomic) int nFramesW;
@property double sumY;

@property double sumForChart;
@property int pulseComp;


- (void)setupCameraSession;

@end


@implementation ViewController


@synthesize pulseComp;
@synthesize captureSession;
@synthesize dataOutput;
@synthesize nFramesW;
@synthesize pulseLabel;
@synthesize sumY;
@synthesize graphView;


- (void)viewDidLoad
{
    [super viewDidLoad];
    
    nFramesW=128;
    
    [self setupCameraSession];

    [captureSession startRunning];
    
    [graphView setIsAccessibilityElement:YES];
    
}


- (void)setupCameraSession
{
    
    // Session
    captureSession = [AVCaptureSession new];
    [captureSession setSessionPreset:AVCaptureSessionPreset352x288];
    
    // Capture device
    AVCaptureDevice *inputDevice = [AVCaptureDevice defaultDeviceWithMediaType:AVMediaTypeVideo];
    NSError *error;
    // Device input
    AVCaptureDeviceInput *deviceInput = [AVCaptureDeviceInput deviceInputWithDevice:inputDevice error:&error];
    [ViewController setTorchMode:AVCaptureTorchModeOn forDevice:inputDevice];
    [ViewController setFocusMode:AVCaptureFocusModeLocked forDevice:inputDevice];
    [ViewController setExposureMode:AVCaptureExposureModeLocked forDevice:inputDevice];
    [ViewController setFrameRate:30.0 forDevice:inputDevice];
    // [ViewController setWhiteBalanceMode:AVCaptureWhiteBalanceModeAutoWhiteBalance forDevice:inputDevice];
    
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
}


- (void)captureOutput:(AVCaptureOutput *)captureOutput didOutputSampleBuffer:(CMSampleBufferRef)sampleBuffer fromConnection:(AVCaptureConnection *)connection
{
    // NSLog(@" I am in CaptureOuput");
    CVImageBufferRef imageBuffer = CMSampleBufferGetImageBuffer(sampleBuffer);
    CVPixelBufferLockBaseAddress(imageBuffer, 0);
    
    size_t width = CVPixelBufferGetWidthOfPlane(imageBuffer, 0);
    size_t height = CVPixelBufferGetHeightOfPlane(imageBuffer, 0);

    uint8_t *baseAddress = CVPixelBufferGetBaseAddressOfPlane(imageBuffer, 0);
    
    
    sumY = 0;
    
    for (uint y = round( height*1/3); y < round(height*2/3); y += 1)
    {
        
        for (uint x = round(width*1/3); x < round(width*2/3); x += 1)
        {
            // NSLog(@"color at %dx %d: %u", x, y, *baseAddress);
            sumY += *baseAddress;
            //NSLog(@" val %hhu",*baseAddress);
            baseAddress += 1;
            
        }
    }
    
   // sumForChart = sumY;
    //  NSLog(@" sumY %f",sumY);

    
    for (int count=0;count<nFramesW-1;count++)
    {
        buffer[count] = buffer[count+1];
        // NSLog(@"windows [%d]  %f",count,window[count]);
    }
    
    buffer[nFramesW-1] = sumY;
    // NSLog(@" windows [nFrames-1] %f",window[nFramesW-1]);
    //  NSLog(@" \n ");
    

    // release
    CVPixelBufferUnlockBaseAddress(imageBuffer, 0);
    
    dispatch_async(dispatch_get_main_queue(), ^{
        [graphView addX:sumY];
        pulseLabel.text=[NSString stringWithFormat:@"%d",pulseComp];
    });

    
    pulseComp=0.0;
    getPulseTemporal_initialize();
    pulseComp = getPulseTemporal(buffer,30.00);
    getPulseTemporal_terminate();

}

- (void) viewDidUnload {
    self.pulseLabel= nil;
    self.graphView = nil;
    [captureSession stopRunning];
    
}

- (void)dealloc {
    
}

// La methode du dessous a été ajoutée par A.Poisson pour forcer la torche afin d eclairer le doigt
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

// La methode du dessous a été ajoutée par A.Poisson pour forcer le focus
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

// La methode du dessous a été ajoutée par A.Poisson pour forcer le focus
+ (void)setExposureMode:(AVCaptureExposureMode)exposureMode forDevice:(AVCaptureDevice *)device
{
    NSError *error = nil;
    if ([device lockForConfiguration:&error])
    {
        [device setExposureMode:exposureMode];
        [device unlockForConfiguration];
    }
    else
    {
        NSLog(@"%@", error);
    }
}

+ (void)setWhiteBalanceMode:(AVCaptureWhiteBalanceMode)whiteBalanceMode forDevice:(AVCaptureDevice *)device
{
    NSError *error = nil;
    if ([device lockForConfiguration:&error])
    {
        [device setWhiteBalanceMode:whiteBalanceMode];
        [device unlockForConfiguration];
    }
    else
    {
        NSLog(@"%@", error);
    }
}



- (IBAction)startRecording:(id)sender {

    /*
  captureSession=nil;
    dataOutput=nil;

    [self viewDidLoad]; 
  */
  }

- (IBAction)stopRecording:(id)sender {
    self.pulseLabel= nil;
     self.graphView = nil;
    [captureSession stopRunning];
    
}
@end
