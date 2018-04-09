# Cordova Apple Pay Plugin

> A dependency free Cordova plugin to provide Apple Pay functionality integrated with Stripe Framework.

Updated to provide additional data access to the plugin, test calls, and compatibility
with newer versions of Cordova. Uses a Promise based interface in JavaScript.

Specifically created this version to provide methods to dynamically change the merchant id or stripe publishable key.

This plugin is integrated to Stripe, if you want an integrated-less plugin you can use
[cordova-plugin-applepay](https://www.npmjs.com/package/cordova-plugin-applepay)

## Installation
```
$ cordova plugin add --save cordova-plugin-dynamic-applepay-stripe
```

Install the plugin using Cordova 6 and above, which is based on [npm](https://www.npmjs.com/package/cordova-plugin-applepay). The plugin
exposes the `window.ApplePay` global in the browser.


## Compatibility

- iOS 9 (using newer iOS9 only APIs)
- iOS 8 (using initial Apple Pay APIs from iOS8 that are deprecated in iOS9)
- iOS 7 and older (no Apple Pay, but doesn't affect code)
- Requires Cordova 6 running at least iOS Platform 4.1.1

## Methods
The methods available all return promises, or accept success and error callbacks.
- ApplePay.setMerchantId
- ApplePay.setPublishableKey
- ApplePay.canMakePayments
- ApplePay.makePaymentRequest
- ApplePay.completeLastTransaction

## ApplePay.setMerchantId
Pass in as a string the desired merchantId for use in plugin. Will return a promise when function completes.

## ApplePay.setPublishableKey
Pass in your Stripe publishable api key for use in plugin. Will return a promise when function completes.

## ApplePay.canMakePayments
Detects if the current device supports Apple Pay and has any *capable* cards registered.

```
ApplePay.canMakePayments()
    .then((message) => {
        // Apple Pay is enabled and a supported card is setup. Expect:
        // 'This device can make payments and has a supported card'
    })
    .catch((message) => {
        // There is an issue, examine the message to see the details, will be:
        // 'This device cannot make payments.''
        // 'This device can make payments but has no supported cards'
    });
```

If in your `catch` you get the message `This device can make payments but has no supported cards` - you can decide if you want to handle this by showing the 'Setup Apple Pay' buttons instead of the
normal 'Pay with Apple Bay' buttons as per the Apple Guidelines.

## ApplePay.makePaymentRequest
Request a payment with Apple Pay, returns a Promise that once resolved, has the payment token.
In your `order`, you will set parameters like the merchant ID, country, address requirements,
order information etc. See a full example of an order at the end of this document.

```
ApplePay.makePaymentRequest(order)
    .then((paymentResponse) => {
        // User approved payment, token generated.
    })
    .catch((message) => {
        // Error or user cancelled.
    });
```

### Example Response

The `paymentResponse` is an object with the keys that contain the token itself,
this is what you'll need to pass along to your payment processor. Also, if you requested
billing or shipping addresses, this information is also included.

```
{
    "shippingAddressState": "London",
    "shippingCountry": "United Kingdom",
    "shippingISOCountryCode": "gb",
    "billingAddressCity": "London",
    "billingISOCountryCode": "gb",
    "shippingNameLast": "Name",
    "paymentData": "<BASE64 ENCODED TOKEN WILL APPEAR HERE>",
    "stripeToken": "<STRIPE TOKEN>",
    "shippingNameFirst": "First",
    "billingAddressState": "London",
    "billingAddressStreet": "Street 1\n",
    "billingNameFirst": "First",
    "billingPostalCode": "POST CODE",
    "shippingPostalCode": "POST CODE",
    "shippingAddressStreet": "Street Line 1\nStreet Line 2",
    "billingNameLast": "NAME",
    "billingSupplementarySubLocality": "",
    "billingCountry": "United Kingdom",
    "shippingAddressCity": "London",
    "shippingSupplementarySubLocality": "",
    "transactionIdentifier": "Simulated Identifier"
}
```

## ApplePay.completeLastTransaction
Once the makePaymentRequest has been resolved successfully, the device will be waiting for a completion event.
This means, that the application must proceed with the token authorisation and return a success, failure, or other validation error. Once this has been passed back, the Apple Pay sheet will be dismissed via an animation.



## License

This project is licensed under *GNU General Public License v3.0*.

It is based on the work of [Sam Kelleher](https://samkelleher.com/). It is an alteration of an older project originally started by [@jbeuckm](https://github.com/jbeuckm) and followed by David Avellaneda @davsket https://github.com/monoku/cordova-plugin-applepay-stripe/commits?author=davsket
