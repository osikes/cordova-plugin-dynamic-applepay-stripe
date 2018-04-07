#import <UIKit/UIKit.h>
#import <Cordova/CDVPlugin.h>

#import <PassKit/PassKit.h>

typedef void (^ARAuthorizationBlock)(PKPaymentAuthorizationStatus);

@interface CDVApplePay : CDVPlugin <PKPaymentAuthorizationViewControllerDelegate>
{
    PKMerchantCapability merchantCapabilities;
    NSArray<NSString *>* supportedPaymentNetworks;
}

@property (nonatomic, strong) ARAuthorizationBlock paymentAuthorizationBlock;

@property (nonatomic, strong) NSString* paymentCallbackId;

- (void)setPublishableKey:(CDVInvokedUrlCommand*)command;
- (void)setMerchantId:(CDVInvokedUrlCommand*)command;
- (void)makePaymentRequest:(CDVInvokedUrlCommand*)command;
- (void)canMakePayments:(CDVInvokedUrlCommand*)command;
- (void)completeLastTransaction:(CDVInvokedUrlCommand*)command;


@end
