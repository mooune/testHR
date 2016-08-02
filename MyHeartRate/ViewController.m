//
//  ViewController.m
//
//  Created by Alexandre Poisson on 1st june 2014
//  Edited on 10/10/2015
//  Copyright (c) 2015, Alexandre Poisson
//
//
//  This ViewController is the tutorial appearing at the begining
//
#import "ViewController.h"

@interface ViewController ()


@end

@implementation ViewController
@synthesize TipTextView;

- (void)viewDidLoad
{
    [super viewDidLoad];
    TipTextView.text = NSLocalizedString(@"TipTextViewText", nil);
 
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    
    // Dispose of any resources that can be recreated.
}
@end
