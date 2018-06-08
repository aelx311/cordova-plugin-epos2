cordova-plugin-epos2
======
Cordova plugin for Epson ePOS SDK(v2.6.0) for iOS and Android.

Check supported device and requirement from official SDK by Epson. 
[iOS](https://download.epson-biz.com/modules/pos/index.php?page=single_soft&cid=5670&scat=58&pcat=52)
[Android](https://download.epson-biz.com/modules/pos/index.php?page=single_soft&cid=5669&scat=61&pcat=52)

API
===

### Printer Discovery
#### .startDiscover(successCallback, errorCallback)
This will only search for supported printers in local area network(LAN)
```
window.epos2.startDiscover(function(deviceInfo) => {
    // success callback with deviceInfo
}, function(error) => {
    // error callback
})
```
#### .stopDiscover(successCallback, errorCallback)
```
window.epos2.stopDiscover(function() => {
    // success callback
}, function(error) => {
    // error callback
})
```

### Printer Connection
#### .connectPrinter(ipAddress, successCallback, errorCallback)
```
window.epos2.connectPrinter(ipAddress, function() => {
    // success callback
}, function(error) => {
    // error callback
})
```
#### .disconnectPrinter(successCallback, errorCallback)
```
window.epos2.disconnectPrinter(function() => {
    // success callback
}, function(error) => {
    // error callback
})
```

### Printing
#### .print(stringData, successCallback, errorCallback)
Use '\n' in string data in order to move to next line.

Cut feed is added automatically.
```
window.epos2.print(stringData, function() => {
    // success callback
}, function(error) => {
    // error callback
})
```