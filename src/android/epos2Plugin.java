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

public class epos2Plugin extends CordovaPlugin {
    private static final String TAG = "epos2";
    private CallbackContext callbackContext = null;
    private Printer printer = null;

    public void initialize(CordovaInterface cordova, CordovaWebView webView) {
        super.initialize(cordova, webView);
    }

    public boolean execute(final String action, final JSONArray args, final CallbackContext callbackContext) throws JSONException {
        this.callbackContext = callbackContext;

        if (action.equals("startDiscover")) {
            startDiscovery(callbackContext);
        } else if (action.equals("stopDiscover")) {
            stopDiscovery(callbackContext);
        } else if (action.equals("connectPrinter")) {
            connectPrinter(args, callbackContext);
        } else if (action.equals("disconnectPrinter")) {
            disconnectPrinter();
        } else if (action.equals("print")) {
            print(args, callbackContext);
        }

        return true;
    }

    private void startDiscovery(final CallbackContext callbackContext) {
        FilterOption mFilterOption = new FilterOption();
        mFilterOption.setDeviceType(Discovery.TYPE_PRINTER);
        mFilterOption.setEpsonFilter(Discovery.FILTER_NAME);
        try {
            Discovery.start(webView.getContext(), mFilterOption, discoveryListener);
        } catch (Epos2Exception e) {
            Log.e(TAG, "Error discovering printer: " + e.getErrorStatus(), e);
            callbackContext.error("Error discovering printer: " + e.getErrorStatus());
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
                    return;
                }
            }
        }
    }

    private void connectPrinter(final JSONArray args, final CallbackContext callbackContext) {
        Log.d(TAG, "Connecting Printer");

        try {
            printer = new Printer(Printer.TM_U220, Printer.MODEL_ANK, webView.getContext());
            printer.setReceiveEventListener(receiveListener);
        }
        catch (Epos2Exception e) {
            callbackContext.error("Error creating printer: " + e.getErrorStatus());
            Log.e(TAG, "Error creating printer: " + e.getErrorStatus(), e);
            return;
        }

        try {
            String target = args.getString(0);
            printer.connect("TCP:" + target , Printer.PARAM_DEFAULT);
        } catch (Epos2Exception e) {
            callbackContext.error("Error connecting printer: " + e.getErrorStatus());
            Log.e(TAG, "Error connecting printer: " + e.getErrorStatus(), e);
            return;
        } catch (JSONException e) {
            callbackContext.error("Error getting target: " + e.getCause());
            Log.e(TAG, "Error connecting printer", e);
            return;
        }

        try {
            printer.beginTransaction();
        } catch (Epos2Exception e) {
            callbackContext.error("Error beginning transaction");
            Log.e(TAG, "Error beginning transaction", e);
            return;
        }

        PluginResult result = new PluginResult(Status.OK, "Done connecting");
        callbackContext.sendPluginResult(result);
    }

    private void disconnectPrinter() {
        if (printer == null) {
            return;
        }

        try {
            printer.endTransaction();
        }
        catch (Epos2Exception e) {
            callbackContext.error("Error ending transaction: " + e.getErrorStatus());
            Log.e(TAG, "Error ending transaction: " + e.getErrorStatus(), e);
            return;
        }

        try {
            printer.disconnect();
        }
        catch (Epos2Exception e) {
            callbackContext.error("Error disconnecting printer: " + e.getErrorStatus());
            Log.e(TAG, "Error disconnecting printer: " + e.getErrorStatus(), e);
            return;
        }

        printer.clearCommandBuffer();
        printer.setReceiveEventListener(null);
        printer = null;

        PluginResult result = new PluginResult(Status.OK, true);
        callbackContext.sendPluginResult(result);
    }

    private void print(final JSONArray array, final CallbackContext callbackContext) {
        if (printer == null) {
            callbackContext.error("printer not found");
            return;
        }

        try {
            for (int i = 0; i < array.length(); i++) {
                String data = array.getString(i);
                if ("\n".equals(data)) {
                    printer.addFeedLine(1);
                } else {
                    printer.addText(data);
                }
            }

            printer.addCut(Printer.CUT_FEED);

            PrinterStatusInfo status = printer.getStatus();

            if (!isPrintable(status)) {
                callbackContext.error("Error printing: printer is not printable");
                Log.e(TAG, "Error printing: printer is not printable");

                try {
                    printer.disconnect();
                }
                catch (Epos2Exception ex) {
                    callbackContext.error("Error disconnecting");
                    Log.e(TAG, "Error disconnecting", ex);
                }
                return;
            }

            printer.sendData(Printer.PARAM_DEFAULT);
        } catch (Epos2Exception e) {
            callbackContext.error("Error printing");
            Log.e(TAG, "Error printing", e);
            try {
                printer.disconnect();
            }
            catch (Epos2Exception ex) {
                callbackContext.error("Error disconnecting");
                Log.e(TAG, "Error disconnecting", ex);
            }
        } catch (JSONException e) {
            callbackContext.error("Error getting data");
            Log.e(TAG, "Error getting data", e);
        }
    }

    private DiscoveryListener discoveryListener = new DiscoveryListener() {
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

    private ReceiveListener receiveListener = new ReceiveListener() {
        @Override
        public void onPtrReceive(final Printer printer, final int code, final PrinterStatusInfo status, final String printJobId) {
            Log.d(TAG, "print success. status: " + status.getErrorStatus());

            new Thread(new Runnable() {
                @Override
                public void run() {
                    disconnectPrinter();
                }
            }).start();
        }
    };

    private boolean isPrintable(PrinterStatusInfo status) {
        if (status == null) {
            return false;
        }

        if (status.getConnection() == Printer.FALSE) {
            return false;
        }
        else if (status.getOnline() == Printer.FALSE) {
            return false;
        }

        return true;
    }
}
