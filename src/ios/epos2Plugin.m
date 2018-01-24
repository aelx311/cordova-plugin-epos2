#import "ePOS2Plugin.h"

#import <Cordova/CDVAvailability.h>

@interface epos2Plugin()<Epos2DiscoveryDelegate, Epos2PtrReceiveDelegate>
@end

@implementation epos2Plugin

- (void)pluginInitialize {
    printerSeries = EPOS2_TM_U220;
    lang = EPOS2_MODEL_ANK;
}

- (void)startDiscover:(CDVInvokedUrlCommand *)command {
    self.discoverCallbackId = command.callbackId;

    Epos2FilterOption *filteroption_ = [[Epos2FilterOption alloc] init];
    [filteroption_ setDeviceType:EPOS2_TYPE_PRINTER];

    int result = [Epos2Discovery start:filteroption_ delegate:self];
    if (EPOS2_SUCCESS != result) {
        NSLog(@"error in startDiscover()");
        CDVPluginResult *result = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:@"Error in discovering printer."];
        [self.commandDelegate sendPluginResult:result callbackId:command.callbackId];
    }
}

- (void) onDiscovery:(Epos2DeviceInfo *)deviceInfo {
    NSLog(@"onDiscovery: %@", [deviceInfo getIpAddress]);
    NSDictionary *info = @{@"ipAddress" : [deviceInfo getIpAddress],
                           @"deviceType": [NSNumber numberWithInt:[deviceInfo getDeviceType]],
                           @"target": [deviceInfo getTarget],
                           @"deviceName": [deviceInfo getDeviceName],
                           @"macAddress": [deviceInfo getMacAddress],
                           @"bdAddress": [deviceInfo getBdAddress],
                           };
    CDVPluginResult *result = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsDictionary:info];
    [result setKeepCallbackAsBool:YES];
    [self.commandDelegate sendPluginResult:result callbackId:self.discoverCallbackId];
}

- (void)stopDiscover:(CDVInvokedUrlCommand *)command {
    NSLog(@"stopDiscover()");
    int result = EPOS2_SUCCESS;

    while (YES) {
        result = [Epos2Discovery stop];

        if (result != EPOS2_ERR_PROCESSING) {
            break;
        }
    }

    if (EPOS2_SUCCESS != result) {
        NSLog(@"error in stopDiscover()");
        CDVPluginResult *result = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:@"Error in stop discovering printer."];
        [self.commandDelegate sendPluginResult:result callbackId:command.callbackId];
    }
}

-(void)connectPrinter:(CDVInvokedUrlCommand *)command {
    NSString* target = [command.arguments objectAtIndex:0];
    NSLog(@"connectPrinter(), ip=%@", target);

    printer = [[Epos2Printer alloc] initWithPrinterSeries:printerSeries lang:lang];

    [printer setReceiveEventDelegate:self];

    int result = EPOS2_SUCCESS;

    if (printer == nil) {
        NSLog(@"error in connectPrinter(), printer object not found");
        CDVPluginResult *result = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:@"Error in connect  printer. Printer object not found"];
        [self.commandDelegate sendPluginResult:result callbackId:command.callbackId];
        return;
    }

    result = [printer connect:[NSString stringWithFormat:@"TCP:%@", target] timeout:EPOS2_PARAM_DEFAULT];
    if (result != EPOS2_SUCCESS) {
        NSLog(@"error in connectPrinter()");
        CDVPluginResult *result = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:@"Error in connect  printer."];
        [self.commandDelegate sendPluginResult:result callbackId:command.callbackId];
        return;
    }

    result = [printer beginTransaction];
    if (result != EPOS2_SUCCESS) {
        NSLog(@"error in beginTransaction()");
        CDVPluginResult *result = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:@"Error in begin transaction."];
        [self.commandDelegate sendPluginResult:result callbackId:command.callbackId];
        [printer disconnect];
        return;
    }

    CDVPluginResult *cordovaResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsBool:YES];
    [self.commandDelegate sendPluginResult:cordovaResult callbackId:command.callbackId];
}

- (void)disconnectPrinter:(CDVInvokedUrlCommand *)command {
    int result = EPOS2_SUCCESS;
    //    NSMutableDictionary *dict = [[NSMutableDictionary alloc] init];

    if (printer == nil) {
        return;
    }

    result = [printer endTransaction];
    if (result != EPOS2_SUCCESS) {
        NSLog(@"error in disconnectPrinter()");
        CDVPluginResult *result = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:@"Error in end transaction."];
        [self.commandDelegate sendPluginResult:result callbackId:command.callbackId];
        //        [dict setObject:[NSNumber numberWithInt:result] forKey:@"result"];
        //        [dict setObject:@"endTransaction" forKey:@"method"];
        //        [self performSelectorOnMainThread:@selector(showEposErrorFromThread:) withObject:dict waitUntilDone:NO];
    }

    result = [printer disconnect];
    if (result != EPOS2_SUCCESS) {
        NSLog(@"error in disconnectPrinter()");
        CDVPluginResult *result = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:@"Error in disconnect printer."];
        [self.commandDelegate sendPluginResult:result callbackId:command.callbackId];
        //        [dict setObject:[NSNumber numberWithInt:result] forKey:@"result"];
        //        [dict setObject:@"disconnect" forKey:@"method"];
        //        [self performSelectorOnMainThread:@selector(showEposErrorFromThread:) withObject:dict waitUntilDone:NO];
    }
    [self finalizeObject];

    CDVPluginResult *cordovaResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsBool:YES];
    [self.commandDelegate sendPluginResult:cordovaResult callbackId:command.callbackId];
}

- (void)finalizeObject
{
    if (printer == nil) {
        return;
    }

    [printer clearCommandBuffer];

    [printer setReceiveEventDelegate:nil];

    printer = nil;
}

- (void)onPtrReceive:(Epos2Printer *)printerObj code:(int)code status:(Epos2PrinterStatusInfo *)status printJobId:(NSString *)printJobId {
    NSLog(@"onPtrReceive");
    NSLog(@"code: %d", code);
    NSLog(@"status: %@", status);
    NSLog(@"printJobId: %@", printJobId);

    [self disconnectPrinter:nil];
}

- (void)print:(CDVInvokedUrlCommand *)command {
    self.printCallbackId = command.callbackId;

    if (printer == nil) {
        NSLog(@"error in createPrintData()");
        CDVPluginResult *result = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:@"Error in create data, printer object not dound."];
        [self.commandDelegate sendPluginResult:result callbackId:command.callbackId];
        return;
    }

    NSArray *printData = command.arguments;

    [self.commandDelegate runInBackground:^{
        int result = EPOS2_SUCCESS;

        for (NSString* data in printData) {
            NSLog(@"%@", data);
            if ([data isEqualToString:@"\n"]) {
                result = [printer addFeedLine:1];
            } else {
                result = [printer addText:data];
            }

            if (result != EPOS2_SUCCESS) {
                break;
            }
        }

        if (result != EPOS2_SUCCESS) {
            return;
        }

        [self printData];
    }];
}

- (void)printData {
    int result = EPOS2_SUCCESS;

//    Epos2PrinterStatusInfo *status = nil;

//    if (printer == nil) {
//        return;
//    }
//
//    if (![self connectPrinter]) {
//        return;
//    }

//    status = [printer getStatus];
//    [self dispPrinterWarnings:status];

//    if (![self isPrintable:status]) {
//        [ShowMsg show:[self makeErrorMessage:status]];
//        [printer disconnect];
//        return;
//    }

    result = [printer sendData:EPOS2_PARAM_DEFAULT];
    if (result != EPOS2_SUCCESS) {
        [printer disconnect];

        CDVPluginResult *result = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:@"Error in print data."];
        [self.commandDelegate sendPluginResult:result callbackId:self.printCallbackId];
        return;
    }

    CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsBool:YES];
    [self.commandDelegate sendPluginResult:pluginResult callbackId:self.printCallbackId];
    return;
}

@end
