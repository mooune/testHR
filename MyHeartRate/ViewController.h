//
//  ViewController.h
//
//  Created by Alexandre Poisson on 1st june 2014
//  Updated on 17 January 2015
//  This ViewController is the tutorial appearing at the begining
//  Copyright (c) 2015, Alexandre Poisson

#import <UIKit/UIKit.h>
#import "PageContentViewController.h"

@interface ViewController : UIViewController <UIPageViewControllerDataSource>
- (IBAction)startWalktrough:(id)sender;

@property (strong, nonatomic) UIPageViewController *pageViewController;
@property (strong, nonatomic) NSArray *pageTitles;
@property (strong, nonatomic) NSArray *pageImages;

@end
