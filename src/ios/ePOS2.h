//
//  Copyright (C) Seiko Epson Corporation 2016 - 2017. All rights reserved.
//
//  ePOS SDK Ver.2.6.0

#ifdef __OBJC__
#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#endif  /*__OBJC__*/

#define EPOS2_FALSE (0)
#define EPOS2_TRUE (1)
#define EPOS2_PARAM_UNSPECIFIED (-1)
#define EPOS2_PARAM_DEFAULT (-2)
#define EPOS2_UNKNOWN (-3)

// virtual keycode
#define EPOS2_VK_BACK         (0x08)
#define EPOS2_VK_TAB          (0x09)
#define EPOS2_VK_RETURN       (0x0D)
#define EPOS2_VK_SHIFT        (0x10)
#define EPOS2_VK_CONTROL      (0x11)
#define EPOS2_VK_MENU         (0x12)
#define EPOS2_VK_CAPITAL      (0x14)
#define EPOS2_VK_ESCAPE       (0x1B)
#define EPOS2_VK_CONVERT      (0x1C)
#define EPOS2_VK_NONCONVERT   (0x1D)
#define EPOS2_VK_SPACE        (0x20)
#define EPOS2_VK_PRIOR        (0x21)
#define EPOS2_VK_NEXT         (0x22)
#define EPOS2_VK_END          (0x23)
#define EPOS2_VK_HOME         (0x24)
#define EPOS2_VK_LEFT         (0x25)
#define EPOS2_VK_UP           (0x26)
#define EPOS2_VK_RIGHT        (0x27)
#define EPOS2_VK_DOWN         (0x28)
#define EPOS2_VK_INSERT       (0x2D)
#define EPOS2_VK_DELETE       (0x2E)
#define EPOS2_VK_0            (0x30)
#define EPOS2_VK_1            (0x31)
#define EPOS2_VK_2            (0x32)
#define EPOS2_VK_3            (0x33)
#define EPOS2_VK_4            (0x34)
#define EPOS2_VK_5            (0x35)
#define EPOS2_VK_6            (0x36)
#define EPOS2_VK_7            (0x37)
#define EPOS2_VK_8            (0x38)
#define EPOS2_VK_9            (0x39)
#define EPOS2_VK_A            (0x41)
#define EPOS2_VK_B            (0x42)
#define EPOS2_VK_C            (0x43)
#define EPOS2_VK_D            (0x44)
#define EPOS2_VK_E            (0x45)
#define EPOS2_VK_F            (0x46)
#define EPOS2_VK_G            (0x47)
#define EPOS2_VK_H            (0x48)
#define EPOS2_VK_I            (0x49)
#define EPOS2_VK_J            (0x4A)
#define EPOS2_VK_K            (0x4B)
#define EPOS2_VK_L            (0x4C)
#define EPOS2_VK_M            (0x4D)
#define EPOS2_VK_N            (0x4E)
#define EPOS2_VK_O            (0x4F)
#define EPOS2_VK_P            (0x50)
#define EPOS2_VK_Q            (0x51)
#define EPOS2_VK_R            (0x52)
#define EPOS2_VK_S            (0x53)
#define EPOS2_VK_T            (0x54)
#define EPOS2_VK_U            (0x55)
#define EPOS2_VK_V            (0x56)
#define EPOS2_VK_W            (0x57)
#define EPOS2_VK_X            (0x58)
#define EPOS2_VK_Y            (0x59)
#define EPOS2_VK_Z            (0x5A)
#define EPOS2_VK_MULTIPLY     (0x6A)
#define EPOS2_VK_ADD          (0x6B)
#define EPOS2_VK_SUBTRACT     (0x6D)
#define EPOS2_VK_F1           (0x70)
#define EPOS2_VK_F2           (0x71)
#define EPOS2_VK_F3           (0x72)
#define EPOS2_VK_F4           (0x73)
#define EPOS2_VK_F5           (0x74)
#define EPOS2_VK_F6           (0x75)
#define EPOS2_VK_F7           (0x76)
#define EPOS2_VK_F8           (0x77)
#define EPOS2_VK_F9           (0x78)
#define EPOS2_VK_F10          (0x79)
#define EPOS2_VK_F11          (0x7A)
#define EPOS2_VK_F12          (0x7B)
#define EPOS2_VK_OEM_1        (0xBA)
#define EPOS2_VK_OEM_PLUS     (0xBB)
#define EPOS2_VK_OEM_COMMA    (0xBC)
#define EPOS2_VK_OEM_MINUS    (0xBD)
#define EPOS2_VK_OEM_PERIOD   (0xBE)
#define EPOS2_VK_OEM_2        (0xBF)
#define EPOS2_VK_OEM_3        (0xC0)
#define EPOS2_VK_OEM_4        (0xDB)
#define EPOS2_VK_OEM_5        (0xDC)
#define EPOS2_VK_OEM_6        (0xDD)
#define EPOS2_VK_OEM_7        (0xDE)
#define EPOS2_VK_OEM_ATTN     (0xF0)

enum Epos2ErrorStatus : int {
    EPOS2_SUCCESS = 0,
    EPOS2_ERR_PARAM,
    EPOS2_ERR_CONNECT,
    EPOS2_ERR_TIMEOUT,
    EPOS2_ERR_MEMORY,
    EPOS2_ERR_ILLEGAL,
    EPOS2_ERR_PROCESSING,
    EPOS2_ERR_NOT_FOUND,
    EPOS2_ERR_IN_USE,
    EPOS2_ERR_TYPE_INVALID,
    EPOS2_ERR_DISCONNECT,
    EPOS2_ERR_ALREADY_OPENED,
    EPOS2_ERR_ALREADY_USED,
    EPOS2_ERR_BOX_COUNT_OVER,
    EPOS2_ERR_BOX_CLIENT_OVER,
    EPOS2_ERR_UNSUPPORTED,
    EPOS2_ERR_FAILURE = 255
};

enum Epos2CallbackCode : int {
    EPOS2_CODE_SUCCESS = 0,
    EPOS2_CODE_ERR_TIMEOUT,
    EPOS2_CODE_ERR_NOT_FOUND,
    EPOS2_CODE_ERR_AUTORECOVER,
    EPOS2_CODE_ERR_COVER_OPEN,
    EPOS2_CODE_ERR_CUTTER,
    EPOS2_CODE_ERR_MECHANICAL,
    EPOS2_CODE_ERR_EMPTY,
    EPOS2_CODE_ERR_UNRECOVERABLE,
    EPOS2_CODE_ERR_SYSTEM,
    EPOS2_CODE_ERR_PORT,
    EPOS2_CODE_ERR_INVALID_WINDOW,
    EPOS2_CODE_ERR_JOB_NOT_FOUND,
    EPOS2_CODE_PRINTING,
    EPOS2_CODE_ERR_SPOOLER,
    EPOS2_CODE_ERR_BATTERY_LOW,
    EPOS2_CODE_ERR_TOO_MANY_REQUESTS,
    EPOS2_CODE_ERR_REQUEST_ENTITY_TOO_LARGE,
    EPOS2_CODE_ERR_FAILURE = 255
};

enum Epos2PrinterSeries : int {
    EPOS2_TM_M10 = 0,
    EPOS2_TM_M30,
    EPOS2_TM_P20,
    EPOS2_TM_P60,
    EPOS2_TM_P60II,
    EPOS2_TM_P80,
    EPOS2_TM_T20,
    EPOS2_TM_T60,
    EPOS2_TM_T70,
    EPOS2_TM_T81,
    EPOS2_TM_T82,
    EPOS2_TM_T83,
    EPOS2_TM_T88,
    EPOS2_TM_T90,
    EPOS2_TM_T90KP,
    EPOS2_TM_U220,
    EPOS2_TM_U330,
    EPOS2_TM_L90,
    EPOS2_TM_H6000,
};
enum Epos2DisplayModel : int {
    EPOS2_DM_D30 = 0,
    EPOS2_DM_D110,
};

enum Epos2ModelLang : int {
    EPOS2_MODEL_ANK = 0,
    EPOS2_MODEL_JAPANESE,
    EPOS2_MODEL_CHINESE,
    EPOS2_MODEL_TAIWAN,
    EPOS2_MODEL_KOREAN,
    EPOS2_MODEL_THAI,
    EPOS2_MODEL_SOUTHASIA,
};

enum Epos2DeviceModel : int {
    EPOS2_MODEL_ALL = 0,
};

enum Epos2PortType : int {
    EPOS2_PORTTYPE_ALL = 0,
    EPOS2_PORTTYPE_TCP,
    EPOS2_PORTTYPE_BLUETOOTH,
};
enum Epos2StatusPaper : int {
    EPOS2_PAPER_OK = 0,
    EPOS2_PAPER_NEAR_END,
    EPOS2_PAPER_EMPTY,
};

enum Epos2PanelSwitch : int {
    EPOS2_SWITCH_OFF = 0,
    EPOS2_SWITCH_ON,
};

enum Epos2StatusDrawer : int {
    EPOS2_DRAWER_HIGH = 0,
    EPOS2_DRAWER_LOW,
};

enum Epos2PrinterError : int {
    EPOS2_NO_ERR = 0,
    EPOS2_MECHANICAL_ERR,
    EPOS2_AUTOCUTTER_ERR,
    EPOS2_UNRECOVER_ERR,
    EPOS2_AUTORECOVER_ERR,
};

enum Epos2AutoRecoverError : int {
    EPOS2_HEAD_OVERHEAT = 0,
    EPOS2_MOTOR_OVERHEAT,
    EPOS2_BATTERY_OVERHEAT,
    EPOS2_WRONG_PAPER,
    EPOS2_COVER_OPEN,
};

enum Epos2BatteryLevel : int {
    EPOS2_BATTERY_LEVEL_0 = 0,
    EPOS2_BATTERY_LEVEL_1,
    EPOS2_BATTERY_LEVEL_2,
    EPOS2_BATTERY_LEVEL_3,
    EPOS2_BATTERY_LEVEL_4,
    EPOS2_BATTERY_LEVEL_5,
    EPOS2_BATTERY_LEVEL_6,
};

enum Epos2StatusEvent : int {
    EPOS2_EVENT_ONLINE = 0,
    EPOS2_EVENT_OFFLINE,
    EPOS2_EVENT_POWER_OFF,
    EPOS2_EVENT_COVER_CLOSE,
    EPOS2_EVENT_COVER_OPEN,
    EPOS2_EVENT_PAPER_OK,
    EPOS2_EVENT_PAPER_NEAR_END,
    EPOS2_EVENT_PAPER_EMPTY,
    EPOS2_EVENT_DRAWER_HIGH,
    EPOS2_EVENT_DRAWER_LOW,
    EPOS2_EVENT_BATTERY_ENOUGH,
    EPOS2_EVENT_BATTERY_EMPTY,
};

enum Epos2ConnectionEvent : int {
    EPOS2_EVENT_RECONNECTING = 0,
    EPOS2_EVENT_RECONNECT,
    EPOS2_EVENT_DISCONNECT,
};

enum Epos2DeviceType : int {
    EPOS2_TYPE_ALL = 0,
    EPOS2_TYPE_PRINTER,
    EPOS2_TYPE_DISPLAY,
    EPOS2_TYPE_KEYBOARD,
    EPOS2_TYPE_SCANNER,
    EPOS2_TYPE_SERIAL,
};

enum Epos2Align : int {
    EPOS2_ALIGN_LEFT = 0,
    EPOS2_ALIGN_CENTER,
    EPOS2_ALIGN_RIGHT
};

enum Epos2Lang : int {
    EPOS2_LANG_EN = 0,
    EPOS2_LANG_JA,
    EPOS2_LANG_ZH_CN,
    EPOS2_LANG_ZH_TW,
    EPOS2_LANG_KO,
    EPOS2_LANG_TH,
    EPOS2_LANG_VI
};

enum Epos2Font : int {
    EPOS2_FONT_A = 0,
    EPOS2_FONT_B,
    EPOS2_FONT_C,
    EPOS2_FONT_D,
    EPOS2_FONT_E
};

enum Epos2Color : int {
    EPOS2_COLOR_NONE = 0,
    EPOS2_COLOR_1,
    EPOS2_COLOR_2,
    EPOS2_COLOR_3,
    EPOS2_COLOR_4
};

enum Epos2Mode : int {
    EPOS2_MODE_MONO = 0,
    EPOS2_MODE_GRAY16,
    EPOS2_MODE_MONO_HIGH_DENSITY
};

enum Epos2Halftone : int {
    EPOS2_HALFTONE_DITHER = 0,
    EPOS2_HALFTONE_ERROR_DIFFUSION,
    EPOS2_HALFTONE_THRESHOLD
};

enum Epos2Compress : int {
    EPOS2_COMPRESS_DEFLATE = 0,
    EPOS2_COMPRESS_NONE,
    EPOS2_COMPRESS_AUTO
};

enum Epos2Barcode : int {
    EPOS2_BARCODE_UPC_A = 0,
    EPOS2_BARCODE_UPC_E,
    EPOS2_BARCODE_EAN13,
    EPOS2_BARCODE_JAN13,
    EPOS2_BARCODE_EAN8,
    EPOS2_BARCODE_JAN8,
    EPOS2_BARCODE_CODE39,
    EPOS2_BARCODE_ITF,
    EPOS2_BARCODE_CODABAR,
    EPOS2_BARCODE_CODE93,
    EPOS2_BARCODE_CODE128,
    EPOS2_BARCODE_GS1_128,
    EPOS2_BARCODE_GS1_DATABAR_OMNIDIRECTIONAL,
    EPOS2_BARCODE_GS1_DATABAR_TRUNCATED,
    EPOS2_BARCODE_GS1_DATABAR_LIMITED,
    EPOS2_BARCODE_GS1_DATABAR_EXPANDED
};

enum Epos2Hri : int {
    EPOS2_HRI_NONE = 0,
    EPOS2_HRI_ABOVE,
    EPOS2_HRI_BELOW,
    EPOS2_HRI_BOTH
};

enum Epos2Symbol : int {
    EPOS2_SYMBOL_PDF417_STANDARD = 0,
    EPOS2_SYMBOL_PDF417_TRUNCATED,
    EPOS2_SYMBOL_QRCODE_MODEL_1,
    EPOS2_SYMBOL_QRCODE_MODEL_2,
    EPOS2_SYMBOL_QRCODE_MICRO,
    EPOS2_SYMBOL_MAXICODE_MODE_2,
    EPOS2_SYMBOL_MAXICODE_MODE_3,
    EPOS2_SYMBOL_MAXICODE_MODE_4,
    EPOS2_SYMBOL_MAXICODE_MODE_5,
    EPOS2_SYMBOL_MAXICODE_MODE_6,
    EPOS2_SYMBOL_GS1_DATABAR_STACKED,
    EPOS2_SYMBOL_GS1_DATABAR_STACKED_OMNIDIRECTIONAL,
    EPOS2_SYMBOL_GS1_DATABAR_EXPANDED_STACKED,
    EPOS2_SYMBOL_AZTECCODE_FULLRANGE,
    EPOS2_SYMBOL_AZTECCODE_COMPACT,
    EPOS2_SYMBOL_DATAMATRIX_SQUARE,
    EPOS2_SYMBOL_DATAMATRIX_RECTANGLE_8,
    EPOS2_SYMBOL_DATAMATRIX_RECTANGLE_12,
    EPOS2_SYMBOL_DATAMATRIX_RECTANGLE_16
};

enum Epos2Level : int {
    EPOS2_LEVEL_0 = 0,
    EPOS2_LEVEL_1,
    EPOS2_LEVEL_2,
    EPOS2_LEVEL_3,
    EPOS2_LEVEL_4,
    EPOS2_LEVEL_5,
    EPOS2_LEVEL_6,
    EPOS2_LEVEL_7,
    EPOS2_LEVEL_8,
    EPOS2_LEVEL_L,
    EPOS2_LEVEL_M,
    EPOS2_LEVEL_Q,
    EPOS2_LEVEL_H
};

enum Epos2Line : int {
    EPOS2_LINE_THIN = 0,
    EPOS2_LINE_MEDIUM,
    EPOS2_LINE_THICK,
    EPOS2_LINE_THIN_DOUBLE,
    EPOS2_LINE_MEDIUM_DOUBLE,
    EPOS2_LINE_THICK_DOUBLE
};

enum Epos2Direction : int {
    EPOS2_DIRECTION_LEFT_TO_RIGHT = 0,
    EPOS2_DIRECTION_BOTTOM_TO_TOP,
    EPOS2_DIRECTION_RIGHT_TO_LEFT,
    EPOS2_DIRECTION_TOP_TO_BOTTOM
};

enum Epos2Cut : int {
    EPOS2_CUT_FEED = 0,
    EPOS2_CUT_NO_FEED,
    EPOS2_CUT_RESERVE
};

enum Epos2Drawer : int {
    EPOS2_DRAWER_2PIN = 0,
    EPOS2_DRAWER_5PIN
};

enum Epos2Pulse  : int {
    EPOS2_PULSE_100 = 0,
    EPOS2_PULSE_200,
    EPOS2_PULSE_300,
    EPOS2_PULSE_400,
    EPOS2_PULSE_500
};

enum Epos2Pattern : int {
    EPOS2_PATTERN_NONE = 0,
    EPOS2_PATTERN_A,
    EPOS2_PATTERN_B,
    EPOS2_PATTERN_C,
    EPOS2_PATTERN_D,
    EPOS2_PATTERN_E,
    EPOS2_PATTERN_ERROR,
    EPOS2_PATTERN_PAPER_EMPTY,
    EPOS2_PATTERN_1,
    EPOS2_PATTERN_2,
    EPOS2_PATTERN_3,
    EPOS2_PATTERN_4,
    EPOS2_PATTERN_5,
    EPOS2_PATTERN_6,
    EPOS2_PATTERN_7,
    EPOS2_PATTERN_8,
    EPOS2_PATTERN_9,
    EPOS2_PATTERN_10
};

enum Epos2FeedPosition : int {
    EPOS2_FEED_PEELING = 0,
    EPOS2_FEED_CUTTING,
    EPOS2_FEED_CURRENT_TOF,
    EPOS2_FEED_NEXT_TOF
};

enum Epos2Layout : int {
    EPOS2_LAYOUT_RECEIPT = 0,
    EPOS2_LAYOUT_RECEIPT_BM,
    EPOS2_LAYOUT_LABEL,
    EPOS2_LAYOUT_LABEL_BM
};

enum Epos2Scroll : int {
    EPOS2_SCROLL_OVERWRITE = 0,
    EPOS2_SCROLL_VERTICAL,
    EPOS2_SCROLL_HORIZONTAL
};

enum Epos2Format : int {
    EPOS2_MARQUEE_WALK = 0,
    EPOS2_MARQUEE_PLACE
};

enum Epos2Brightness : int {
    EPOS2_BRIGHTNESS_20 = 0,
    EPOS2_BRIGHTNESS_40,
    EPOS2_BRIGHTNESS_60,
    EPOS2_BRIGHTNESS_100
};

enum Epos2CursorPosition : int {
    EPOS2_MOVE_TOP_LEFT = 0,
    EPOS2_MOVE_TOP_RIGHT,
    EPOS2_MOVE_BOTTOM_LEFT,
    EPOS2_MOVE_BOTTOM_RIGHT
};

enum Epos2CursorType : int {
    EPOS2_CURSOR_NONE = 0,
    EPOS2_CURSOR_UNDERLINE
};

enum Epos2LogPeriod : int {
    EPOS2_PERIOD_TEMPORARY = 0,
    EPOS2_PERIOD_PERMANENT
};

enum Epos2LogOutput : int {
    EPOS2_OUTPUT_DISABLE = 0,
    EPOS2_OUTPUT_STORAGE,
    EPOS2_OUTPUT_TCP
};

enum Epos2LogLevel : int {
    EPOS2_LOGLEVEL_LOW = 0
};

#ifdef __OBJC__

@class Epos2Printer;
@class Epos2LineDisplay;
@class Epos2Keyboard;
@class Epos2BarcodeScanner;
@class Epos2SimpleSerial;
@class Epos2CommBox;
@class Epos2DeviceInfo;

@interface Epos2PrinterStatusInfo : NSObject
@property(readonly, getter=getConnection) int connection;
@property(readonly, getter=getOnline) int online;
@property(readonly, getter=getCoverOpen) int coverOpen;
@property(readonly, getter=getPaper) int paper;
@property(readonly, getter=getPaperFeed) int paperFeed;
@property(readonly, getter=getPanelSwitch) int panelSwitch;
@property(readonly, getter=getWaitOnline) int waitOnline;
@property(readonly, getter=getDrawer) int drawer;
@property(readonly, getter=getErrorStatus) int errorStatus;
@property(readonly, getter=getAutoRecoverError) int autoRecoverError;
@property(readonly, getter=getBuzzer) int buzzer;
@property(readonly, getter=getAdapter) int adapter;
@property(readonly, getter=getBatteryLevel) int batteryLevel;
@end

@protocol Epos2ConnectionDelegate <NSObject>
@required
- (void) onConnection:(id)deviceObj eventType:(int)eventType;
@end

@protocol Epos2PtrStatusChangeDelegate <NSObject>
@required
- (void) onPtrStatusChange:(Epos2Printer *)printerObj eventType:(int)eventType;
@end

@protocol Epos2PtrReceiveDelegate <NSObject>
@required
- (void) onPtrReceive:(Epos2Printer *)printerObj code:(int)code status:(Epos2PrinterStatusInfo *)status printJobId:(NSString *)printJobId;
@end

@protocol Epos2DispReceiveDelegate <NSObject>
@required
- (void) onDispReceive:(Epos2LineDisplay *)displayObj code:(int)code;
@end

@protocol Epos2KbdKeyPressDelegate <NSObject>
@required
- (void) onKbdKeyPress:(Epos2Keyboard *)keyboardObj keyCode:(int)keyCode ascii:(NSString *)ascii;
@end

@protocol Epos2KbdReadStringDelegate <NSObject>
@required
- (void) onKbdReadString:(Epos2Keyboard *)keyboardObj readString:(NSString *)readString prefix:(int)prefix;
@end

@protocol Epos2ScanDelegate <NSObject>
@required
- (void) onScanData:(Epos2BarcodeScanner *)scannerObj scanData:(NSString *)scanData;
@end

@protocol Epos2SimpleSerialReceiveDelegate <NSObject>
@required
- (void) onSimpleSerialReceive:(Epos2SimpleSerial *)serialObj data:(NSData *)data;
@end

@protocol Epos2GetCommHistoryDelegate <NSObject>
@required
- (void) onGetCommHistory:(Epos2CommBox *)commBoxObj code:(int)code historyList:(NSArray *)historyList;
@end

@protocol Epos2CommBoxSendMessageDelegate <NSObject>
@required
- (void) onCommBoxSendMessage:(Epos2CommBox *)commBoxObj code:(int)code count:(long)count;
@end

@protocol Epos2CommBoxReceiveDelegate <NSObject>
@required
- (void) onCommBoxReceive:(Epos2CommBox *)commBoxObj senderId:(NSString *)senderId receiverId:(NSString *)receiverId message:(NSString *)message;
@end

@protocol Epos2DiscoveryDelegate <NSObject>
@required
- (void) onDiscovery:(Epos2DeviceInfo *)deviceInfo;
@end

@interface Epos2Printer : NSObject

- (id) initWithPrinterSeries:(int)printerSeries lang:(int)lang;
- (void) dealloc;

- (int) connect:(NSString *) target timeout:(long)timeout;
- (int) disconnect;
- (int) startMonitor;
- (int) stopMonitor;
- (Epos2PrinterStatusInfo *) getStatus;
- (int) sendData:(long)timeout;
- (int) beginTransaction;
- (int) endTransaction;
- (int) requestPrintJobStatus:(NSString *)printJobId;
- (int) clearCommandBuffer;
- (int) addTextAlign:(int)align;
- (int) addLineSpace:(long)linespc;
- (int) addTextRotate:(int)rotate;
- (int) addText:(NSString *)data;
- (int) addTextLang:(int)lang;
- (int) addTextFont:(int)font;
- (int) addTextSmooth:(int)smooth;
- (int) addTextSize:(long)width height:(long)height;
- (int) addTextStyle:(int)reverse ul:(int)ul em:(int)em color:(int)color;
- (int) addHPosition:(long)x;
- (int) addFeedUnit:(long)unit;
- (int) addFeedLine:(long)line;
- (int) addImage:(UIImage *)data x:(long)x y:(long)y width:(long)width height:(long)height color:(int)color mode:(int)mode halftone:(int)halftone brightness:(double)brightness compress:(int)compress;
- (int) addLogo:(long)key1 key2:(long)key2;
- (int) addBarcode:(NSString *)data type:(int)type hri:(int)hri font:(int)font width:(long)width height:(long)height;
- (int) addSymbol:(NSString *)data type:(int)type level:(int)level width:(long)width height:(long)height size:(long)size;
- (int) addHLine:(long)x1 x2:(long)x2 style:(int)style;
- (int) addVLineBegin:(long)x style:(int)style lineId:(int *)lineId;
- (int) addVLineEnd:(int)lineId;
- (int) addPageBegin;
- (int) addPageEnd;
- (int) addPageArea:(long)x y:(long)y width:(long)width height:(long)height;
- (int) addPageDirection:(int)direction;
- (int) addPagePosition:(long)x y:(long)y;
- (int) addPageLine:(long)x1 y1:(long)y1 x2:(long)x2 y2:(long)y2 style:(int)style;
- (int) addPageRectangle:(long)x1 y1:(long)y1 x2:(long)x2 y2:(long)y2 style:(int)style;
- (int) addCut:(int)type;
- (int) addPulse:(int)drawer time:(int)time;
- (int) addSound:(int)pattern repeat:(long)repeat cycle:(long)cycle;
- (int) addFeedPosition:(int)position;
- (int) addLayout:(int)type width:(long)width height:(long)height marginTop:(long)marginTop marginBottom:(long)marginBottom offsetCut:(long)offsetCut offsetLabel:(long)offsetLabel;
- (int) addCommand:(NSData *)data;
- (int) forceRecover:(long)timeout;
- (int) forcePulse:(int)drawer pulseTime:(int)time timeout:(long)timeout;
- (int) forceStopSound:(long)timeout;
- (int) forceCommand:(NSData *)data timeout:(long)timeout;
- (int) forceReset:(long)timeout;

- (void) setStatusChangeEventDelegate:(id<Epos2PtrStatusChangeDelegate>)delegate;
- (void) setReceiveEventDelegate:(id<Epos2PtrReceiveDelegate>)delegate;

- (int) setInterval:(long)interval;
- (long) getInterval;

- (void) setConnectionEventDelegate:(id<Epos2ConnectionDelegate>)delegate;
- (NSString *) getAdmin;
- (NSString *) getLocation;
@end

@interface Epos2DisplayStatusInfo : NSObject
@property(readonly, getter=getConnection) int connection;
@end

@interface Epos2LineDisplay : NSObject

- (id) initWithDisplayModel:(int)displayModel;
- (void) dealloc;

- (int) connect:(NSString *) target timeout:(long)timeout;
- (int) disconnect;

- (Epos2DisplayStatusInfo *) getStatus;
- (int) sendData;
- (int) clearCommandBuffer;
- (int) addInitialize;
- (int)	addCreateWindow:(long)number x:(long)x y:(long)y width:(long)width height:(long)height scrollMode:(int)scrollMode;
- (int) addDestroyWindow:(long)number;
- (int) addSetCurrentWindow:(long)number;
- (int) addClearCurrentWindow;
- (int) addSetCursorPosition:(long)x y:(long)y;
- (int)	addMoveCursorPosition:(int)position;
- (int) addSetCursorType:(int)type;
- (int) addText:(NSString *)data;
- (int) addText:(NSString *)data lang:(int)lang;
- (int) addText:(NSString *)data x:(long)x y:(long)y;
- (int) addText:(NSString *)data x:(long)x y:(long)y lang:(int)lang;
- (int) addReverseText:(NSString *)data;
- (int) addReverseText:(NSString *)data lang:(int)lang;
- (int) addReverseText:(NSString *)data x:(long)x y:(long)y;
- (int) addReverseText:(NSString *)data x:(long)x y:(long)y lang:(int)lang;
- (int) addMarqueeText:(NSString *)data format:(int)format unitWait:(long)unitWait repeatWait:(long)repeatWait repeatCount:(long)repeatCount lang:(int)lang;
- (int) addSetBlink:(long)interval;
- (int) addSetBrightness:(int)brightness;
- (int) addShowClock;
- (int) addCommand:(NSData *)data;

- (void) setReceiveEventDelegate:(id<Epos2DispReceiveDelegate>)delegate;

- (void) setConnectionEventDelegate:(id<Epos2ConnectionDelegate>)delegate;
- (NSString *) getAdmin;
- (NSString *) getLocation;
@end

@interface Epos2KeyboardStatusInfo : NSObject
@property(readonly, getter=getConnection) int connection;
@end

@interface Epos2Keyboard : NSObject
- (id) init;
- (void) dealloc;

- (int) connect:(NSString *) target timeout:(long)timeout;
- (int) disconnect;
- (Epos2KeyboardStatusInfo *) getStatus;

- (int) setPrefix:(NSData *)data;
- (NSData *) getPrefix;
- (void) setKeyPressEventDelegate:(id<Epos2KbdKeyPressDelegate>)delegate;
- (void) setReadStringEventDelegate:(id<Epos2KbdReadStringDelegate>)delegate;

- (void) setConnectionEventDelegate:(id<Epos2ConnectionDelegate>)delegate;
- (NSString *) getAdmin;
- (NSString *) getLocation;
@end

@interface Epos2ScannerStatusInfo : NSObject
@property(readonly, getter=getConnection) int connection;
@end

@interface Epos2BarcodeScanner : NSObject
- (id) init;
- (void) dealloc;

- (int) connect:(NSString *) target timeout:(long)timeout;
- (int) disconnect;
- (Epos2ScannerStatusInfo *) getStatus;

- (void) setScanEventDelegate:(id<Epos2ScanDelegate>)delegate;

- (void) setConnectionEventDelegate:(id<Epos2ConnectionDelegate>)delegate;
- (NSString *) getAdmin;
- (NSString *) getLocation;
@end

@interface Epos2SimpleSerialStatusInfo : NSObject
@property(readonly, getter=getConnection) int connection;
@end

@interface Epos2SimpleSerial : NSObject
- (id) init;
- (void) dealloc;
- (int) connect:(NSString *) target timeout:(long)timeout;
- (int) disconnect;
- (Epos2SimpleSerialStatusInfo *) getStatus;

- (int) sendCommand:(NSData *)data;
- (void) setReceiveEventDelegate:(id<Epos2SimpleSerialReceiveDelegate>)delegate;

- (void) setConnectionEventDelegate:(id<Epos2ConnectionDelegate>)delegate;
- (NSString *) getAdmin;
- (NSString *) getLocation;
@end

@interface Epos2CommBoxStatusInfo : NSObject
@property(readonly, getter=getConnection) int connection;
@end

@interface Epos2CommBox : NSObject
- (id) init;
- (void) dealloc;
- (int) connect:(NSString *)target timeout:(long)timeout myId:(NSString *)myId;
- (int) disconnect;
- (Epos2CommBoxStatusInfo *) getStatus;

- (int) getCommHistory:(id<Epos2GetCommHistoryDelegate>)delegate;
- (int) sendMessage:(NSString *)message targetId:(NSString *)targetId delegate:(id<Epos2CommBoxSendMessageDelegate>)delegate;
- (void) setReceiveEventDelegate:(id<Epos2CommBoxReceiveDelegate>)delegate;

- (void) setConnectionEventDelegate:(id<Epos2ConnectionDelegate>)delegate;
- (NSString *) getAdmin;
- (NSString *) getLocation;
@end

@interface Epos2FilterOption : NSObject
@property(nonatomic, getter=getPortType, setter=setPortType:) int portType;
@property(nonatomic, copy, getter=getBroadcast, setter=setBroadcast:) NSString *broadcast;
@property(nonatomic, getter=getDeviceModel, setter=setDeviceModel:) int deviceModel;
@property(nonatomic, getter=getDeviceType, setter=setDeviceType:) int deviceType;
@end

@interface Epos2DeviceInfo : NSObject
@property(nonatomic, readonly, getter=getDeviceType) int deviceType;
@property(nonatomic, copy, readonly, getter=getTarget) NSString *target;
@property(nonatomic, copy, readonly, getter=getDeviceName) NSString *deviceName;
@property(nonatomic, copy, readonly, getter=getIpAddress) NSString *ipAddress;
@property(nonatomic, copy, readonly, getter=getMacAddress) NSString *macAddress;
@property(nonatomic, copy, readonly, getter=getBdAddress) NSString *bdAddress;
@end

@interface Epos2Discovery : NSObject
+ (int) start:(Epos2FilterOption *)filterOption delegate:(id<Epos2DiscoveryDelegate>)delegate;
+ (int) stop;
@end

@interface Epos2Log : NSObject
+ (int) setLogSettings:(int)period output:(int)output ipAddress:(NSString *)ipAddress port:(int)port logSize:(int)logSize logLevel:(int)logLevel;
+(NSString *) getSdkVersion;
@end


enum Epos2BtConnection : int {
    EPOS2_BT_SUCCESS = 0,
    EPOS2_BT_ERR_PARAM,
    EPOS2_BT_ERR_UNSUPPORTED,
    EPOS2_BT_ERR_CANCEL,
    EPOS2_BT_ERR_ALREADY_CONNECT,
    EPOS2_BT_ERR_ILLEGAL_DEVICE,
    EPOS2_BT_ERR_FAILURE = 255
};

@interface Epos2BluetoothConnection : NSObject
- (id) init;
- (void) dealloc;
- (int) connectDevice : (NSMutableString *)target;
- (int) disconnectDevice : (NSString *)target;
@end

#endif  /*__OBJC__*/
