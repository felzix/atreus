#ifndef BUILD_INFORMATION
#define BUILD_INFORMATION "locally built"
#endif

#include "Kaleidoscope.h"
#include "Kaleidoscope-EEPROM-Settings.h"
#include "Kaleidoscope-EEPROM-Keymap.h"
#include "Kaleidoscope-FocusSerial.h"
#include "Kaleidoscope-Macros.h"
#include "Kaleidoscope-MouseKeys.h"
#include "Kaleidoscope-OneShot.h"
#include "Kaleidoscope-Qukeys.h"
#include "Kaleidoscope-SpaceCadet.h"

#define MO(n) ShiftToLayer(n)
#define TG(n) LockLayer(n)

#define Key_Exclamation LSHIFT(Key_1)
#define Key_Question LSHIFT(Key_Slash)
#define Key_At LSHIFT(Key_2)
#define Key_Hash LSHIFT(Key_3)
#define Key_Dollar LSHIFT(Key_4)
#define Key_Percent LSHIFT(Key_5)
#define Key_Caret LSHIFT(Key_6)
#define Key_And LSHIFT(Key_7)
#define Key_Star LSHIFT(Key_8)
#define Key_LeftParen LSHIFT(Key_9)
#define Key_RightParen LSHIFT(Key_0)
#define Key_Plus LSHIFT(Key_Equals)
#define Key_Underscore LSHIFT(Key_Minus)
#define Key_Colon LSHIFT(Key_Semicolon)
#define Key_GreaterThan LSHIFT(Key_Period)
#define Key_LessThan LSHIFT(Key_Comma)
#define Key_LeftCurlyBrace LSHIFT(Key_LeftBracket)
#define Key_RightCurlyBrace LSHIFT(Key_RightBracket)

enum {
  MACRO_CANCEL,
  MACRO_VERSION_INFO
};

enum {
  QWERTY,
  FUN,
  UPPER,
  BOTH
};

/* *INDENT-OFF* */
KEYMAPS(
  [QWERTY] = KEYMAP_STACKED
  (
       Key_Q            ,Key_W                ,Key_E           ,Key_R             ,Key_T
      ,Key_A            ,Key_S                ,Key_D           ,Key_F             ,Key_G
      ,Key_Z            ,Key_X                ,Key_C           ,Key_Comma         ,Key_LeftParen      ,Key_Period
      ,Key_Esc          ,OSL(UPPER)           ,OSL(FUN)        ,Key_Space         ,OSM(LeftShift)     ,OSM(LeftGui)

                        ,Key_Y                ,Key_U           ,Key_I             ,Key_O              ,Key_P
                        ,Key_H                ,Key_J           ,Key_K             ,Key_L              ,Key_M
      ,Key_Quote        ,Key_RightParen       ,Key_Semicolon   ,Key_V             ,Key_B              ,Key_N
      ,OSM(LeftControl) ,OSM(LeftAlt)         ,Key_Backspace   ,OSM(RightAlt)     ,OSL(BOTH)          ,Key_Enter
  ),

  [FUN] = KEYMAP_STACKED
  (
       XXX              ,Key_UpArrow         ,XXX              ,Key_Colon         ,Key_Star
      ,Key_LeftArrow    ,Key_DownArrow       ,Key_RightArrow   ,Key_And           ,Key_At
      ,Key_Hash         ,Key_Plus            ,Key_Caret        ,Key_Slash         ,Key_LeftBracket    ,Key_Question
      ,M(MACRO_CANCEL)  ,___                 ,___              ,Key_Tab           ,___                ,___

                        ,Key_Dollar          ,Key_7            ,Key_8             ,Key_9              ,Key_Period
                        ,Key_Percent         ,Key_4            ,Key_5             ,Key_6              ,Key_Comma
      ,Key_Minus        ,Key_RightBracket    ,Key_1            ,Key_2             ,Key_3              ,Key_Equals
      ,___              ,___                 ,Key_Delete       ,Key_0             ,___                ,___
  ),

  [UPPER] = KEYMAP_STACKED
  (
       XXX              ,Key_Home            ,XXX              ,XXX               ,XXX
      ,Key_PageUp       ,Key_End             ,Key_PageDown     ,XXX               ,XXX
      ,Key_Dollar       ,Key_Star            ,Key_Percent      ,Key_Backslash     ,Key_LessThan       ,Key_Exclamation
      ,M(MACRO_CANCEL)  ,___                 ,___              ,Key_Tab           ,___                ,___

                        ,XXX                 ,Key_F7           ,Key_F8            ,Key_F9             ,Key_F11
                        ,XXX                 ,Key_F4           ,Key_F5            ,Key_F6             ,Key_F12
      ,Key_Backtick     ,Key_GreaterThan     ,Key_F1           ,Key_F2            ,Key_F3             ,Key_Exclamation
      ,___              ,___                 ,Key_Insert       ,Key_F10           ,___                ,___
  ),

  [BOTH] = KEYMAP_STACKED
  (
       Key_mouseBtnL    ,Key_mouseUp         ,Key_mouseBtnR    ,Key_mouseScrollUp ,XXX
      ,Key_mouseL       ,Key_mouseDn         ,Key_mouseR       ,Key_mouseScrollDn ,XXX
      ,Key_mouseScrollL ,Key_mouseBtnM       ,Key_mouseScrollR ,XXX               ,XXX                ,XXX
      ,M(MACRO_CANCEL)  ,___                 ,___              ,XXX               ,___                ,___

                        ,XXX                 ,Key_mouseWarpNW  ,Key_mouseWarpN    ,Key_mouseWarpNE    ,Key_VolumeUp
                        ,XXX                 ,Key_mouseWarpW   ,Key_mouseWarpIn   ,Key_mouseWarpE     ,Key_Mute
      ,XXX              ,XXX                 ,Key_mouseWarpSW  ,Key_mouseWarpS    ,Key_mouseWarpSE    ,Key_VolumeDown
      ,___              ,___                 ,XXX              ,OSM(RightAlt)     ,___                ,Key_mouseWarpEnd
  )
)
/* *INDENT-ON* */

KALEIDOSCOPE_INIT_PLUGINS(
  EEPROMSettings,
  EEPROMKeymap,
  Focus,
  FocusEEPROMCommand,
  FocusSettingsCommand,
  Qukeys,
  SpaceCadet,
  OneShot,
  Macros,
  MouseKeys
);

const macro_t *macroAction(uint8_t macroIndex, uint8_t keyState) {
  switch (macroIndex) {
    case MACRO_CANCEL:
      Layer.move(QWERTY);
      OneShot.cancel(true);
      break;
    case MACRO_VERSION_INFO:
      if (keyToggledOn(keyState)) {
        Macros.type(PSTR("Keyboardio Atreus - Kaleidoscope "));
        Macros.type(PSTR(BUILD_INFORMATION));
      }
      break;
    default:
      break;
  }

  return MACRO_NONE;
}

void setup() {
  Kaleidoscope.setup();
  SpaceCadet.disable();
  MouseKeys.setWarpGridSize(MOUSE_WARP_GRID_3X3);
  MouseKeys.speed = 2;
  MouseKeys.accelSpeed = 4;
  MouseKeys.setSpeedLimit(32);
  // EEPROMKeymap.setup(10);
}

void loop() {
  Kaleidoscope.loop();
}
