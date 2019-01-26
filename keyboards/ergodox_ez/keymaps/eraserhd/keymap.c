#include QMK_KEYBOARD_H
#include "debug.h"
#include "action_layer.h"
#include "version.h"

#define BASE 0 // default layer
#define SYMB 1 // symbols & keyboard navigation
#define MNAV 2 // media keys

#define KC_SLEEP LSFT(LCTL(KC_POWER))

enum custom_keycodes {
  PLACEHOLDER = SAFE_RANGE, // can always be here
  RGB_SLD,
};

enum {
    TD_RESET = 0,
    TD_SLEEP
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |   =    |   1  |   2  |   3  |   4  |   5  | RESET|           |      |   6  |   7  |   8  |   9  |   0  |   -    |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | SYMB   |   Q  |   W  |   E  |   R  |   T  | Meh  |           | Meh  |   Y  |   U  |   I  |   O  |   P  |   \    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |CAP/SYMB|   A  |   S  |D/MNAV|F/SYMB|   G  |------|           |------|   H  |   J  |   K  |   L  |   ;  |' / SYMB|
 * |--------+------+------+------+------+------| Hyper|           |Hyper |------+------+------+------+------+--------|
 * | LShift |Z/LCtl|X/LAlt|   C  |   V  |   B  |      |           |      |   N  |   M  |   ,  |./RAlt|//RCtl| RShift |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | LAlt |  '"  |AltShf| Left |      |                                       |      | Down |   [  |   ]  | RAlt |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | App  | LGui |       | Alt  |  Esc |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       | PgUp |      |      |
 *                                 | Enter| Tab/ |------|       |------| Bksp |Space |
 *                                 |      | Cmd  | Sleep|       | PgDn | /Cmd |      |
 *                                 `--------------------'       `--------------------'
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[BASE] = LAYOUT_ergodox(  // layer 0 : default
        // left hand
        KC_EQL,      KC_1,         KC_2,   KC_3,   KC_4,   KC_5,   TD(TD_RESET),
        MO(SYMB),    KC_Q,         KC_W,   KC_E,   KC_R,   KC_T,   MEH_T(KC_NO),
        LT(SYMB,KC_CAPSLOCK), KC_A,KC_S,   LT(MNAV,KC_D),  LT(SYMB,KC_F),   KC_G,
        KC_LSFT,     LCTL_T(KC_Z), LALT_T(KC_X), KC_C,   KC_V,   KC_B,   ALL_T(KC_NO),
        KC_LALT,     KC_QUOT,      LALT(KC_LSFT),  KC_LEFT,KC_NO,
                                              ALT_T(KC_APP),  KC_LGUI,
                                                              KC_NO,
                                        KC_ENT,LGUI_T(KC_TAB),TD(TD_SLEEP),
        // right hand
             KC_NO,       KC_6,  KC_7,   KC_8,   KC_9,   KC_0,           KC_MINS,
             MEH_T(KC_NO),KC_Y,  KC_U,   KC_I,   KC_O,   KC_P,           KC_BSLS,
                          KC_H,  KC_J,   KC_K,   KC_L,   KC_SCLN,        LT(SYMB,KC_QUOT),
             ALL_T(KC_NO),KC_N,  KC_M,   KC_COMM,RALT_T(KC_DOT),RCTL_T(KC_SLSH),KC_RSFT,
                                 KC_NO,  KC_DOWN,KC_LBRC,KC_RBRC,        KC_RALT,
             KC_LALT,        KC_ESC,
             KC_PGUP,
             KC_PGDN, LGUI_T(KC_BSPC), KC_SPC
    ),
/* Keymap 1: Symbol Layer
 *
 * ,---------------------------------------------------.          ,--------------------------------------------------.
 * |         |  F1  |  F2  |  F3  |  F4  |  F5  |      |          |      |  F6  |  F7  |  F8  |  F9  |  F10 |   F11  |
 * |---------+------+------+------+------+------+------|          |------+------+------+------+------+------+--------|
 * |         |   !  |   ~  |   {  |   }  |   |  |      |          |      | Home |      | Ins  | End  |      |   F12  |
 * |---------+------+------+------+------+------|      |          |      |------+------+------+------+------+--------|
 * |         |   #  |   `  |      |      |   $  |------|          |------| Left | Down |  Up  |Right |      |        |
 * |---------+------+------+------+------+------|      |          |      |------+------+------+------+------+--------|
 * |         |   %  |   ^  |   [  |   ]  |   @  |      |          |      | DEL  | PgDn | PgUp |      |      |        |
 * `---------+------+------+------+------+-------------'          `-------------+------+------+------+------+--------'
 *   |       |      |      |      |      |                                      |      |    . |   0  |   =  |      |
 *   `-----------------------------------'                                      `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |Animat|      |       |Toggle|Solid |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |Bright|Bright|      |       |      |Hue-  |Hue+  |
 *                                 |ness- |ness+ |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// SYMBOLS
[SYMB] = LAYOUT_ergodox(
       // left hand
       KC_TRNS,KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_TRNS,
       KC_TRNS,KC_EXLM,KC_TILD,KC_LCBR,KC_RCBR,KC_PIPE,KC_TRNS,
       KC_TRNS,KC_HASH,KC_GRV, KC_TRNS,KC_TRNS,KC_DLR,
       KC_TRNS,KC_PERC,KC_CIRC,KC_LBRC,KC_RBRC,KC_AT,KC_TRNS,
       KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
                                       RGB_MOD,KC_TRNS,
                                               KC_TRNS,
                               RGB_VAD,RGB_VAI,KC_TRNS,
       // right hand
       KC_TRNS,  KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
       KC_TRNS,  KC_HOME, KC_TRNS, KC_INS,  KC_END,  KC_TRNS, KC_F12,
                 KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_TRNS, KC_TRNS,
       KC_TRNS,  KC_DEL,  KC_PGDN, KC_PGUP, KC_TRNS, KC_TRNS, KC_TRNS,
                          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       RGB_TOG, RGB_SLD,
       KC_TRNS,
       KC_TRNS, RGB_HUD, RGB_HUI
),
/* Keymap 2: Media and mouse keys
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      | Lclk | Rclk | Btn3 | Acc0 |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |------|           |------|MsLeft|MsDown| MsUp |MsRigt| Acc1 |  Play  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |WhLeft|WhDown| WhUp |WhRigt| Acc2 |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |VolUp |VolDn | Mute |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |Brwser|
 *                                 |      |      |------|       |------|      |Back  |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// MEDIA AND MOUSE
[MNAV] = LAYOUT_ergodox(
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                           KC_TRNS, KC_TRNS,
                                                    KC_TRNS,
                                  KC_TRNS, KC_TRNS, KC_TRNS,
    // right hand
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS,  KC_TRNS, KC_BTN1, KC_BTN2, KC_BTN3, KC_ACL0, KC_TRNS,
                 KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_ACL1, KC_MPLY,
       KC_TRNS,  KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R, KC_ACL2, KC_TRNS,
                          KC_VOLU, KC_VOLD, KC_MUTE, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_WBAK
),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case RGB_SLD:
        if (record->event.pressed) {
          #ifdef RGBLIGHT_ENABLE
            rgblight_mode(1);
          #endif
        }
        return false;
    case KC_CAPSLOCK:
        if (!record->event.pressed)
            _delay_ms(50);
        return true;
    default:
        return true;
    }
}

void dance_reset_reset(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count >= 3) {
        reset_keyboard();
    }
}

void dance_sleep_reset(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count >= 3) {
        register_code(KC_LSFT);
        register_code(KC_LCTL);
        register_code(KC_POWER);
        unregister_code(KC_POWER);
        unregister_code(KC_LCTL);
        unregister_code(KC_LSFT);
    }
}

qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_RESET] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, NULL, dance_reset_reset),
    [TD_SLEEP] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, NULL, dance_sleep_reset),
};

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
#ifdef RGBLIGHT_COLOR_LAYER_0
  rgblight_setrgb(RGBLIGHT_COLOR_LAYER_0);
#endif
};

// Runs whenever there is a layer state change.
uint32_t layer_state_set_user(uint32_t state) {
  ergodox_board_led_off();
  ergodox_right_led_1_off();
  ergodox_right_led_2_off();
  ergodox_right_led_3_off();

  uint8_t layer = biton32(state);
  switch (layer) {
      case 0:
        #ifdef RGBLIGHT_COLOR_LAYER_0
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_0);
        #else
        #ifdef RGBLIGHT_ENABLE
          rgblight_init();
        #endif
        #endif
        break;
      case 1:
        ergodox_right_led_1_on();
        #ifdef RGBLIGHT_COLOR_LAYER_1
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_1);
        #endif
        break;
      case 2:
        ergodox_right_led_2_on();
        #ifdef RGBLIGHT_COLOR_LAYER_2
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_2);
        #endif
        break;
      case 3:
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_3
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_3);
        #endif
        break;
      case 4:
        ergodox_right_led_1_on();
        ergodox_right_led_2_on();
        #ifdef RGBLIGHT_COLOR_LAYER_4
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_4);
        #endif
        break;
      case 5:
        ergodox_right_led_1_on();
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_5
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_5);
        #endif
        break;
      case 6:
        ergodox_right_led_2_on();
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_6
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_6);
        #endif
        break;
      case 7:
        ergodox_right_led_1_on();
        ergodox_right_led_2_on();
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_7
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_6);
        #endif
        break;
      default:
        break;
    }

  return state;
};
