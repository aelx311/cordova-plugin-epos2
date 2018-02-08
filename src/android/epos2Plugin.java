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

import android.content.Context;
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

public class epos2Plugin extends CordovaPlugin implements ReceiveListener {
    private static final String TAG = "epos2";
    private CallbackContext callbackContext = null;
    private Printer printer = null;

    public void initialize(CordovaInterface cordova, CordovaWebView webView) {
        super.initialize(cordova, webView);
    }

    public boolean execute(final String action, final JSONArray args, final CallbackContext callbackContext) throws JSONException {
        this.callbackContext = callbackContext;

//        cordova.getActivity().runOnUiThread(new Runnable() {
//            public void run() {
//                if (action.equals("startDiscover")) {
//                    startDiscovery();
//                } else if (action.equals("stopDiscover")) {
//                    stopDiscovery(callbackContext);
//                } else if (action.equals("connectPrinter")) {
//                    connectPrinter(args, callbackContext);
//                } else if (action.equals("disconnectPrinter")) {
//                    disconnectPrinter(callbackContext);
//                } else if (action.equals("print")) {
//                    print(args, callbackContext);
//                }
//            }
//        });

//        cordova.getThreadPool().execute(new Runnable() {
//            public void run() {
//                if (action.equals("startDiscover")) {
//                    startDiscovery();
//                } else if (action.equals("stopDiscover")) {
//                    stopDiscovery(callbackContext);
//                } else if (action.equals("connectPrinter")) {
//                    connectPrinter(args, callbackContext);
//                } else if (action.equals("disconnectPrinter")) {
//                    disconnectPrinter(callbackContext);
//                } else if (action.equals("print")) {
//                    print(args, callbackContext);
//                }
//            }
//        });

        if (action.equals("startDiscover")) {
            cordova.getThreadPool().execute(new Runnable() {
                @Override
                public void run() {
                    startDiscovery();
                }
            });
            return true;
        }

        if (action.equals("stopDiscover")) {
            cordova.getThreadPool().execute(new Runnable() {
                @Override
                public void run() {
                    stopDiscovery(callbackContext);
                }
            });
            return true;
        }

        if (action.equals("connectPrinter")) {
            cordova.getThreadPool().execute(new Runnable() {
                @Override
                public void run() {
                    connectPrinter(args, callbackContext);
                }
            });

//            PluginResult pluginResult = new  PluginResult(PluginResult.Status.NO_RESULT);
//            pluginResult.setKeepCallback(true);
//            callbackContext.sendPluginResult(pluginResult);
            return true;
        }

        if (action.equals("disconnectPrinter")) {
            disconnectPrinter(callbackContext);
            return true;
        }

        if (action.equals("print")) {
            print(args, callbackContext);
            return true;
        }

        return false;
    }

    private void startDiscovery() {
        FilterOption mFilterOption = new FilterOption();
        mFilterOption.setDeviceType(Discovery.TYPE_PRINTER);
        mFilterOption.setEpsonFilter(Discovery.FILTER_NAME);
        try {
            Discovery.start(webView.getContext(), mFilterOption, mDiscoveryListener);
        } catch (Epos2Exception e) {
            Log.e(TAG, "Error discovering printer: " + e.getErrorStatus(), e);
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
        if (printer == null) {
            try {
                printer = new Printer(Printer.TM_U220, Printer.MODEL_ANK, cordova.getActivity());
                printer.setReceiveEventListener(this);
            }
            catch (Epos2Exception e) {
                PluginResult result = new PluginResult(Status.ERROR, "Error creating printer");
                callbackContext.sendPluginResult(result);
                Log.e(TAG, "Error creating printer: " + e.getErrorStatus(), e);
                return;
            }

            try {
                String target = args.getString(0);
                printer.connect("TCP:" + target , Printer.PARAM_DEFAULT);
            } catch (Epos2Exception e) {
                PluginResult result = new PluginResult(Status.ERROR, "Error connecting printer: " + e.getErrorStatus());
                callbackContext.sendPluginResult(result);
                Log.e(TAG, "Error connecting printer: " + e.getErrorStatus(), e);
            } catch (JSONException e) {
                PluginResult result = new PluginResult(Status.ERROR, "Error getting target: " + e.getCause());
                callbackContext.sendPluginResult(result);
                Log.e(TAG, "Error connecting printer", e);
            }
        }

        PluginResult result = new PluginResult(Status.OK, "Done printing");
        callbackContext.sendPluginResult(result);
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

        printer.clearCommandBuffer();

        printer.setReceiveEventListener(null);

        printer = null;
    }

    private void print(final JSONArray array, final CallbackContext callbackContext) {
        if (printer == null) {
            callbackContext.error("printer not found");
            return;
        }

        StringBuilder textData = new StringBuilder();
        try {
            JSONArray dataArray = array.getJSONArray(0);
            for (int i = 0; i < dataArray.length(); i++) {
                String data = dataArray.getString(i);
                Log.d(TAG, data);
                if ("\n".equals(data)) {
                    printer.addFeedLine(1);
                } else {
                    printer.addText(data);
                }
            }

//            printer.addCut(Printer.CUT_FEED);

            PrinterStatusInfo status = printer.getStatus();

//            if (!isPrintable(status)) {
//                ShowMsg.showMsg(makeErrorMessage(status), mContext);
//                try {
//                    mPrinter.disconnect();
//                }
//                catch (Exception ex) {
//                    // Do nothing
//                }
//                return false;
//            }

//                printer.sendData(Printer.PARAM_DEFAULT);
        }
        catch (Exception e) {
            Log.e(TAG, "Error printing");
            try {
                printer.disconnect();
            }
            catch (Exception ex) {
                Log.e(TAG, "Error disconnecting");
            }
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

//    private ReceiveListener mPtrReceive = new ReceiveListener() {
//        @Override
//        public void onPtrReceive(final Printer printer, final int code, final PrinterStatusInfo status, final String printJobId) {
//            Log.d(TAG, "status: " + status);
//            disconnectPrinter(null);
//        }
//    };

    @Override
    public void onPtrReceive(Printer printer, int code, PrinterStatusInfo status, String printJobId) {
        Log.d(TAG, "status: " + status);
        this.callbackContext.success("onPtrReceive");
        disconnectPrinter(null);
    }
}
