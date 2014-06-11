//
//  ViewController.h
//
//  Created by Alexandre Poisson on 1st june 2014
//  Copyright (c) 2014, Alexandre Poisson

#import <UIKit/UIKit.h>
#import "PageContentViewController.h"

@interface ViewController : UIViewController <UIPageViewControllerDataSource>
- (IBAction)startWalktrough:(id)sender;

@property (strong, nonatomic) UIPageViewController *pageViewController;
@property (strong, nonatomic) NSArray *pageTitles;
@property (strong, nonatomic) NSArray *pageImages;

@end
