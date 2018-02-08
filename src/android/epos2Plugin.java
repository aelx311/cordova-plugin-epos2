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

import com.epson.epos2.Epos2Exception;
import com.epson.epos2.discovery.DeviceInfo;
import com.epson.epos2.discovery.Discovery;
import com.epson.epos2.discovery.DiscoveryListener;
import com.epson.epos2.discovery.FilterOption;
import com.epson.epos2.printer.Printer;
import com.epson.epos2.printer.PrinterStatusInfo;
import com.epson.epos2.printer.ReceiveListener;

import java.util.Date;
import java.util.HashMap;

public class epos2Plugin extends CordovaPlugin {
    private static final String TAG = "epos2";
    private CordovaWebView webView = null;
    private CallbackContext callbackContext = null;
    private Printer printer = null;

    public void initialize(CordovaInterface cordova, CordovaWebView webView) {
        super.initialize(cordova, webView);
        this.webView = webView;
        Log.d(TAG, "Initializing epos2Plugin");
    }

    public boolean execute(final String action, final JSONArray args, final CallbackContext callbackContext) throws JSONException {
        this.callbackContext = callbackContext;

        cordova.getThreadPool().execute(new Runnable() {
            public void run() {
                if (action.equals("startDiscover")) {
                    startDiscovery();
                } else if (action.equals("stopDiscover")) {
                    stopDiscovery(callbackContext);
                } else if (action.equals("connectPrinter")) {
                    connectPrinter(args, callbackContext);
                } else if (action.equals("disconnectPrinter")) {
                    disconnectPrinter(callbackContext);
                } else if (action.equals("print")) {
                    print(args, callbackContext);
                }
            }
        });
        return true;
    }

    private void startDiscovery() {
        FilterOption mFilterOption = new FilterOption();
        mFilterOption.setDeviceType(Discovery.TYPE_PRINTER);
        mFilterOption.setEpsonFilter(Discovery.FILTER_NAME);
        try {
            Discovery.start(webView.getContext(), mFilterOption, mDiscoveryListener);
        } catch (Epos2Exception e) {
            e.printStackTrace();
        }
    }

    private void stopDiscovery(final CallbackContext callbackContext) {
        while (true) {
            try {
                Discovery.stop();
                PluginResult result = new PluginResult(Status.OK, true);
                callbackContext.sendPluginResult(result);
                break;
            }
            catch (Epos2Exception e) {
                if (e.getErrorStatus() != Epos2Exception.ERR_PROCESSING) {
                    PluginResult result = new PluginResult(Status.ERROR, false);
                    callbackContext.sendPluginResult(result);
                    break;
                }
            }
        }
    }

    private void connectPrinter(final JSONArray args, final CallbackContext callbackContext) {
        try {
            printer = new Printer(Printer.TM_U220, Printer.MODEL_ANK, webView.getContext());
        }
        catch (Exception e) {
            callbackContext.error("Error creating printer");
            Log.e(TAG, "Error creating printer");
        }

        boolean isBeginTransaction = false;

        if (printer == null) {
            Log.e(TAG, "printer is null");
        }

        try {
            printer.connect("TCP:64:EB:8C:FB:10:4D", Printer.PARAM_DEFAULT);
        }
        catch (Exception e) {
            Log.e(TAG, "Error connecting printer");
        }

        try {
            printer.beginTransaction();
            isBeginTransaction = true;
        }
        catch (Exception e) {
            Log.e(TAG, "Error beginning transaction");
        }

        if (isBeginTransaction == false) {
            try {
                printer.disconnect();
            }
            catch (Epos2Exception e) {

            }
        }

        printer.setReceiveEventListener(mPtrReceive);

    }

    private void disconnectPrinter(final CallbackContext callbackContext) {
        if (printer == null) {
            return;
        }

        try {
            printer.endTransaction();
        }
        catch (final Exception e) {
            Log.d(TAG, "Error ending transaction");
        }

        try {
            printer.disconnect();
        }
        catch (final Exception e) {
            Log.d(TAG, "Error disconnecting printer");
        }

        if (printer == null) {
            return;
        }

        printer.clearCommandBuffer();

        printer.setReceiveEventListener(null);

        printer = null;
    }

    private void print(final JSONArray array, final CallbackContext callbackContext) {
        if (printer == null) {
            return;
        }

        StringBuilder textData = new StringBuilder();
        try {
//            printer.addTextAlign(Printer.ALIGN_CENTER);

            printer.addFeedLine(1);
            textData.append("THE STORE 123 (555) 555 – 5555\n");
            textData.append("STORE DIRECTOR – John Smith\n");
            textData.append("\n");
            textData.append("7/01/07 16:58 6153 05 0191 134\n");
            textData.append("ST# 21 OP# 001 TE# 01 TR# 747\n");
            textData.append("------------------------------\n");
            printer.addText(textData.toString());
            textData.delete(0, textData.length());

            printer.addCut(Printer.CUT_FEED);
        }
        catch (Exception e) {
            Log.e(TAG, "Error printing");
        }
    }

    private DiscoveryListener mDiscoveryListener = new DiscoveryListener() {
        @Override
        public void onDiscovery(final DeviceInfo deviceInfo) {
            JSONObject item = new JSONObject();

            try {
                item.put("deviceName", deviceInfo.getDeviceName());
                item.put("target", deviceInfo.getTarget());
                item.put("ipAddress", deviceInfo.getIpAddress());
                item.put("macAddress", deviceInfo.getMacAddress());
                item.put("deviceType", deviceInfo.getDeviceType());
                item.put("bdAddress", deviceInfo.getBdAddress());
            } catch (JSONException e) {
                callbackContext.error("Error building device info");
            }

            callbackContext.success(item);
        }
    };

    private ReceiveListener mPtrReceive = new ReceiveListener() {
        @Override
        public void onPtrReceive(final Printer printer, final int code, final PrinterStatusInfo status, final String printJobId) {
            Log.d(TAG, "status: " + status);
            disconnectPrinter(null);
        }
    };
}
