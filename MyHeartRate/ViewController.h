//
//  ViewController.h
//
//  Created by Alexandre Poisson on 1st june 2014
//  Edited on 28/02/2015
//  Copyright (c) 2015, Alexandre Poisson
//
//
//  This ViewController is the tutorial appearing at the begining
//
#import <UIKit/UIKit.h>
#import "PageContentViewController.h"

@interface ViewController : UIViewController <UIPageViewControllerDataSource>
- (IBAction)startWalktrough:(id)sender;

@property (strong, nonatomic) UIPageViewController *pageViewController;
@property (strong, nonatomic) NSArray *pageTitles;
@property (strong, nonatomic) NSArray *pageImages;

@end
