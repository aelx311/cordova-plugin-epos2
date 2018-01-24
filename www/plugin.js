
var exec = require('cordova/exec');

var PLUGIN_NAME = 'epos2';

var epos2 = {
  startDiscover: function(successCallback, errorCallback) {
    exec(successCallback, errorCallback, PLUGIN_NAME, 'startDiscover', []);
  },
  stopDiscover: function(successCallback, errorCallback) {
    exec(successCallback, errorCallback, PLUGIN_NAME, 'stopDiscover', []);
  },
  connectPrinter: function(ipAddress, successCallback, errorCallback) {
    exec(successCallback, errorCallback, PLUGIN_NAME, 'connectPrinter', [ipAddress]);
  },
  disconnectPrinter: function(successCallback, errorCallback) {
    exec(successCallback, errorCallback, PLUGIN_NAME, 'disconnectPrinter', []);
  },
  print: function(data, successCallback, errorCallback) {
    exec(successCallback, errorCallback, PLUGIN_NAME, 'print', data);
  },
};

module.exports = epos2;
