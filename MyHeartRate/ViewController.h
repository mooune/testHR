//
//  ViewController.h
//  Shooter
//
//  Created by Geppy Parziale on 2/24/12.
//  Copyright (c) 2012 iNVASIVECODE, Inc. All rights reserved.
//
#import "AppDelegate.h"
#import <UIKit/UIKit.h>
#import <AVFoundation/AVFoundation.h>
#import <QuartzCore/QuartzCore.h>
#import <CoreMedia/CoreMedia.h>
#import <Accelerate/Accelerate.h>
#import <CoreLocation/CoreLocation.h>
#import "ViewController.h"
#import "GraphView.h"


@interface ViewController : UIViewController {
    
    //   UILabel *pulseLabel;
    //   GraphView *graphView;
    //   UILabel *sumYLabel;
    double buffer[128];
}


@property (weak, nonatomic) IBOutlet UIButton *startButton;

@property (weak, nonatomic) IBOutlet UIButton *stopButton;

@property (strong, nonatomic) IBOutlet UILabel *pulseLabel;

@property (nonatomic, retain) IBOutlet GraphView *graphView;

- (IBAction)startRecording:(id)sender;
- (IBAction)stopRecording:(id)sender;

@end
