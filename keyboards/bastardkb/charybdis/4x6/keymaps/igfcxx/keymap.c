/**
 * Copyright 2021 Charly Delay <charly@codesink.dev> (@0xcharly)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

#ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
#    include "timer.h"
#endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE

enum charybdis_keymap_layers {
    LAYER_QWERTY = 0,
    LAYER_FUNC1 = 1,
    LAYER_FUNC2 = 2,
    LAYER_MOUSE = 3,
};

// Mod-Tap Keys
#define TO_BASE TO(LAYER_QWERTY)
#define MO_FUN1 MO(LAYER_FUNC1)
#define MO_FUN2 MO(LAYER_FUNC2)
#define TO_MOUS TO(LAYER_MOUSE)
#define CT_CAP  CTL_T(KC_CAPS)

#ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
static uint16_t auto_pointer_layer_timer = 0;

#   ifndef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS
#       define CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS 500
#   endif

#   ifndef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD
#       define CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD 8
#   endif
#endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE

#ifndef POINTING_DEVICE_ENABLE
#   define DPI_MOD KC_NO
#   define S_D_MOD KC_NO
#   define SNIPING KC_NO
#   define DRGSCRL KC_NO
#endif // !POINTING_DEVICE_ENABLE

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // 0. 基础布局
  [LAYER_QWERTY] = LAYOUT(
  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
       QK_GESC,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,       KC_6,    KC_7,    KC_8,    KC_9,    KC_0,  KC_DEL,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
        KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,       KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_BSLS,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
        CT_CAP,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,       KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,       KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_RSFT,
  // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                  KC_BSPC,  KC_SPC,  MO_FUN1,   MO_FUN2,  KC_ENT,
  //                            ├───────────────────────────┤ ├──────────────────┤
                                           KC_LGUI, KC_LALT,     KC_APP
  //                            ╰───────────────────────────╯ ╰──────────────────╯

  /*
     ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
          Esc        1        2        3        4        5           6        7        8        9        0      Del
     ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
          Tab        Q        W        E        R        T           Y        U        I        O        P       \\
     ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
         Caps        A        S        D        F        G           H        J        K        L        ;        '
     ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
        Shift        Z        X        C        V        B           N        M        ,        .        /    Shift
     ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                  BackSp    Space                         Enter
                                ├───────────────────────────┤ ├──────────────────┤
                                              Win      Alt        Menu
                                ╰───────────────────────────╯ ╰──────────────────╯
  */
  ),

  // 1. 方向键
  [LAYER_FUNC1] = LAYOUT(
  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
        KC_F12,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,      KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX,   KC_UP, XXXXXXX, KC_MINS,  KC_EQL,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       XXXXXXX, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, XXXXXXX,    XXXXXXX, KC_LEFT, KC_DOWN, KC_RGHT, KC_LBRC, KC_RBRC,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                  _______, _______, _______,    TO_MOUS, _______,
  //                            ├───────────────────────────┤ ├──────────────────┤
                                           _______, _______,    _______
  //                            ╰───────────────────────────╯ ╰──────────────────╯

  /*
     ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
          F12       F1       F2       F3       F4       F5          F6       F7       F8       F9      F10      F11
     ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
                                                                                       ↑                 -        =
     ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
                   Win      Alt     Ctrl    Shift                             ←        ↓        →        [        ]
     ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
                                                                                                                   
     ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                  BackSp    Space                         Enter
                                ├───────────────────────────┤ ├──────────────────┤
                                              Win      Alt        Menu
                               ╰───────────────────────────╯ ╰──────────────────╯
  */
  ),

  // 2. 功能区
  [LAYER_FUNC2] = LAYOUT(
  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
        KC_F12,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,      KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       UG_NEXT, UG_SATU, UG_HUEU, UG_VALU, KC_BRIU, KC_VOLU,    XXXXXXX,  KC_INS, KC_HOME, KC_PGUP, KC_UNDS, KC_PLUS,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       UG_TOGG, RGB_M_P, KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE,    XXXXXXX,  KC_DEL,  KC_END, KC_PGDN, KC_LCBR, KC_RCBR,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       UG_PREV, UG_SATD, UG_HUED, UG_VALD, KC_BRID, KC_VOLD,    XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                  _______, _______, TO_MOUS,    _______, _______,
  //                            ├───────────────────────────┤ ├──────────────────┤
                                           _______, _______,    _______
  //                            ╰───────────────────────────╯ ╰──────────────────╯

  /*
     ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
          F12       F1       F2       F3       F4       F5          F6       F7       F8       F9      F10      F11
     ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
         Anm+     Sat+     Hue+     Val+     Bri+     Vol+                  Ins     Home     PgUp        _        +
     ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
         RGB+     RGB=     Prev     Play     Next     Mute                  Del      End     PgDw        {        }
     ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
         Anm-     Sat-     Hue-     Val-     Bri-     Vol-                                                         
     ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                  BackSp    Space                         Enter
                                ├───────────────────────────┤ ├──────────────────┤
                                              Win      Alt        Menu
                               ╰───────────────────────────╯ ╰──────────────────╯
  */
  ),


  // 3. Mouse
  [LAYER_MOUSE] = LAYOUT(
  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
        KC_ESC,  KC_NUM, KC_PSLS, KC_PAST, KC_PMNS, KC_PPLS,    XXXXXXX, DPI_MOD, S_D_MOD, XXXXXXX, QK_BOOT,  EE_CLR,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
        KC_TAB,  KC_DLR,   KC_P7,   KC_P8,   KC_P9, KC_PERC,    XXXXXXX,DPI_RMOD,S_D_RMOD, XXXXXXX, XXXXXXX, XXXXXXX,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
        CT_CAP,   KC_AT,   KC_P4,   KC_P5,   KC_P6, KC_PEQL,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       KC_LSFT,   KC_P0,   KC_P1,   KC_P2,   KC_P3, KC_PDOT,    XXXXXXX, MS_BTN1, MS_BTN2, SNIPING, DRGSCRL, XXXXXXX,
  // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                  _______, _______, TO_BASE,    TO_BASE, _______,
  //                            ├───────────────────────────┤ ├──────────────────┤
                                           _______, _______,    _______
  //                            ╰───────────────────────────╯ ╰──────────────────╯

  /*
     ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
          Esc      Num        /        *        -        +                 DPI+    SDPI+          QK_BOOT    EE_CLR
     ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
          Tab        Q        7        8        9        %                 DPI-    SDPI-                           
     ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
         Caps        A        4        5        6        =                                                         
     ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
        Shift        0        1        2        3        .                 MS_L     MS_R  SNIPING  DRGSCRL         
     ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                  BackSp    Space                         Enter
                                ├───────────────────────────┤ ├──────────────────┤
                                              Win      Alt        Menu
                               ╰───────────────────────────╯ ╰──────────────────╯
  */
  )
  
};
// clang-format on

#ifdef POINTING_DEVICE_ENABLE
#   ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    if (abs(mouse_report.x) > CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD || abs(mouse_report.y) > CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD) {
        if (auto_pointer_layer_timer == 0) {
            layer_on(LAYER_POINTER);
#       ifdef RGB_MATRIX_ENABLE
            rgb_matrix_mode_noeeprom(RGB_MATRIX_NONE);
            rgb_matrix_sethsv_noeeprom(HSV_GREEN);
#       endif
        }
        auto_pointer_layer_timer = timer_read();
    }
    return mouse_report;
}

void matrix_scan_user(void) {
    if (auto_pointer_layer_timer != 0 && TIMER_DIFF_16(timer_read(), auto_pointer_layer_timer) >= CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS) {
        auto_pointer_layer_timer = 0;
        layer_off(LAYER_POINTER);
#       ifdef RGB_MATRIX_ENABLE
        rgb_matrix_mode_noeeprom(RGB_MATRIX_DEFAULT_MODE);
#       endif
    }
}
#   endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
#endif // POINTING_DEVICE_ENABLE

#ifdef RGB_MATRIX_ENABLE
// Forward-declare this helper function since it is defined in rgb_matrix.c.
void rgb_matrix_update_pwm_buffers(void);
#endif

#define CHARYBDIS_DRAGSCROLL_REVERSE_Y

// Combos
enum combos {
    RT_LPRN,
    YU_RPRN,
    FG_LBRC,
    HJ_RBRC,
    VB_LCBR,
    NM_RCBR,
    FB_BSLS,
    NJ_SLSH,
    DF_BSPC,
    JK_ENT,
};

const uint16_t PROGMEM rt_combo[] = {KC_R, KC_T, COMBO_END};
const uint16_t PROGMEM yu_combo[] = {KC_Y, KC_U, COMBO_END};
const uint16_t PROGMEM fg_combo[] = {KC_F, KC_G, COMBO_END};
const uint16_t PROGMEM hj_combo[] = {KC_H, KC_J, COMBO_END};
const uint16_t PROGMEM vb_combo[] = {KC_V, KC_B, COMBO_END};
const uint16_t PROGMEM nm_combo[] = {KC_N, KC_M, COMBO_END};
const uint16_t PROGMEM fb_combo[] = {KC_F, KC_B, COMBO_END};
const uint16_t PROGMEM nj_combo[] = {KC_N, KC_J, COMBO_END};
const uint16_t PROGMEM df_combo[] = {KC_D, KC_F, COMBO_END};
const uint16_t PROGMEM jk_combo[] = {KC_J, KC_K, COMBO_END};

combo_t key_combos[] = {
    [RT_LPRN] = COMBO(rt_combo, KC_LPRN),  // R + T   -> '('
    [YU_RPRN] = COMBO(yu_combo, KC_RPRN),  // Y + U   -> ')'
    [FG_LBRC] = COMBO(fg_combo, KC_LBRC),  // F + G   -> '['
    [HJ_RBRC] = COMBO(hj_combo, KC_RBRC),  // H + J   -> ']'
    [VB_LCBR] = COMBO(vb_combo, KC_LCBR),  // V + B   -> '{'
    [NM_RCBR] = COMBO(nm_combo, KC_RCBR),  // N + M   -> '}'
    [FB_BSLS] = COMBO(fb_combo, KC_BSLS),  // F + B   -> '\'
    [NJ_SLSH] = COMBO(nj_combo, KC_SLSH),  // N + J   -> '/'
    [DF_BSPC] = COMBO(df_combo, KC_BSPC),  // D + F   -> Bsp
    [JK_ENT]  = COMBO(jk_combo, KC_ENT),   // J + K   -> Ent
};
