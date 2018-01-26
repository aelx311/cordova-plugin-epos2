/**
 */
package com.cordova.plugin;

import org.apache.cordova.CallbackContext;
import org.apache.cordova.CordovaInterface;
import org.apache.cordova.CordovaPlugin;
import org.apache.cordova.CordovaWebView;
import org.apache.cordova.PluginResult;
import org.apache.cordova.PluginResult.Status;
import org.json.JSONObject;
import org.json.JSONArray;
import org.json.JSONException;

import android.util.Log;

import java.util.Date;

public class epos2Plugin extends CordovaPlugin {
  private static final String TAG = "epos2";

  public void initialize(CordovaInterface cordova, CordovaWebView webView) {
    super.initialize(cordova, webView);

    Log.d(TAG, "Initializing epos2Plugin");
  }

  public boolean execute(final String action, final JSONArray args, final CallbackContext callbackContext) throws JSONException {
    cordova.getThreadPool().execute(new Runnable() {
            public void run() {
                if (action.equals("startDiscovery")) {
                    startDiscovery();
                }
            }
        });
    return true;
  }

  private void startDiscovery() {
    Log.d(TAG, "startDicvoery() called");
  }
}
