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
#import "ViewController.h"
#import "GraphView.h"


@interface ViewController : UIViewController {
    
    double buffer[128];
}


@property (weak, nonatomic) IBOutlet UIButton *startButton;

@property (weak, nonatomic) IBOutlet UIButton *stopButton;

@property (strong, nonatomic) IBOutlet UILabel *pulseLabel;

@property (nonatomic, retain) IBOutlet GraphView *graphView;

- (IBAction)startRecording:(id)sender;
- (IBAction)stopRecording:(id)sender;

@end
