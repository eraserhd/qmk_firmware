#include QMK_KEYBOARD_H
#include "debug.h"
#include "action_layer.h"
#include "pointing_device.h"
#include "version.h"

#define TRACKBALL_ADDRESS  0x0A
#define TRACKBALL_WRITE    ((TRACKBALL_ADDRESS<<1)|I2C_WRITE)
#define TRACKBALL_READ     ((TRACKBALL_ADDRESS<<1)|I2C_READ)

#define BASE 0 // default layer
#define SYMB 1 // symbols & keyboard navigation
#define MNAV 2 // media keys
#define NUMB 3 // numbers

#define KC_SLEEP LSFT(LCTL(KC_POWER))

enum custom_keycodes {
    PLACEHOLDER = SAFE_RANGE, // can always be here
    RGB_SLD,

    // Symbols when shifted, but dead when used as numerals
    NOT_1,
    NOT_2,
    NOT_3,
    NOT_4,
    NOT_5,
    NOT_6,
    NOT_7,
    NOT_8,
    NOT_9,
    NOT_0
};

enum {
    TD_RESET = 0,
    TD_SLEEP,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

#define _RESET_    TD(TD_RESET)
#define _CAP_SYMB_ LT(SYMB,KC_CAPSLOCK)
#define _D_MNAV_   LT(MNAV,KC_D)
#define _F_SYMB_   LT(SYMB,KC_F)
#define _Z_LCtl_   LCTL_T(KC_Z)
#define _X_LAlt_   LALT_T(KC_X)
#define _Tab_Cmd   LGUI_T(KC_TAB)
#define _Sleep_    TD(TD_SLEEP)
#define _Qu_SYMB_  LT(SYMB,KC_QUOT)
#define Dot_RAlt   RALT_T(KC_DOT)
#define Slsh_Ctl   RCTL_T(KC_SLSH)
#define Bspc_Cmd   LGUI_T(KC_BSPC)
#define _Q_Num_    LT(NUMB,KC_Q)

[BASE] = LAYOUT_ergodox_pretty(
// ,----------------------------------------------------------------------.       ,----------------------------------------------------------------.
      KC_EQL  ,  NOT_1  ,  NOT_2  ,  NOT_3  ,  NOT_4  ,  NOT_5  , _RESET_ ,         XXXXXXX,  NOT_6 ,  NOT_7 ,  NOT_8 ,  NOT_9 ,  NOT_0 ,  KC_MINS ,
// |----------+---------+---------+---------+---------+---------+---------|       |--------+--------+--------+--------+--------+--------+----------|
     TT(NUMB) , _Q_Num_ ,  KC_W   ,  KC_E   ,  KC_R   ,  KC_T   ,  KC_MEH ,         KC_MEH ,  KC_Y  ,  KC_U  ,  KC_I  ,  KC_O  ,  KC_P  ,  KC_BSLS ,
// |----------+---------+---------+---------+---------+---------|         |       |        |--------+--------+--------+--------+--------+----------|
    _CAP_SYMB_,  KC_A   ,  KC_S   ,_D_MNAV_ , _F_SYMB_,  KC_G  ,/*--------|       |-------*/  KC_H  ,  KC_J  ,  KC_K  ,  KC_L  , KC_SCLN, _Qu_SYMB_,
// |----------+---------+---------+---------+---------+---------|         |       |        |--------+--------+--------+--------+--------+----------|
     KC_LSPO  ,_Z_LCtl_ ,_X_LAlt_ ,  KC_C   ,  KC_V   ,   KC_B  , KC_HYPR ,         KC_HYPR,  KC_N  ,  KC_M  , KC_COMM,Dot_RAlt,Slsh_Ctl,  KC_RSPC ,
// `----------+---------+---------+---------+---------+-------------------'       `-----------------+--------+--------+--------+--------+----------'
      KC_LALT , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,                                               XXXXXXX, XXXXXXX, KC_LBRC, KC_RBRC, KC_RALT,
//   `------------------------------------------------'                                             `--------------------------------------------'
//                                                        ,-----------------.   ,-----------------.
                                                            XXXXXXX, XXXXXXX,     KC_LALT, KC_ESC ,
//                                               ,--------|--------|--------|   |--------+--------+--------.
                                                                     XXXXXXX,     KC_PGUP,
//                                               |        |        |--------|   |--------|        |        |
                                                   KC_ENT ,_Tab_Cmd, _Sleep_,    KC_PGDN ,Bspc_Cmd, KC_SPC
//                                               `--------------------------'   `--------------------------'
),

[SYMB] = LAYOUT_ergodox_pretty(
// ,----------------------------------------------------------------------.       ,----------------------------------------------------------------.
     _______  ,  KC_F1  ,  KC_F2  ,  KC_F3  ,  KC_F4  ,  KC_F5  , _______ ,        _______ ,  KC_F6 ,  KC_F7 ,  KC_F8 ,  KC_F9 , KC_F10 ,  KC_F11  ,
// |----------+---------+---------+---------+---------+---------+---------|       |--------+--------+--------+--------+--------+--------+----------|
     _______  , KC_EXLM , KC_TILD , KC_LCBR , KC_RCBR , KC_PIPE , _______ ,        _______ , KC_HOME, _______, KC_INS , KC_END , _______,  KC_F12  ,
// |----------+---------+---------+---------+---------+---------|         |       |        |--------+--------+--------+--------+--------+----------|
     _______  , KC_HASH , KC_GRV  , _______ , _______ , KC_DLR ,/*--------|       |-------*/ KC_LEFT, KC_DOWN,  KC_UP , KC_RGHT, _______,  _______ ,
// |----------+---------+---------+---------+---------+---------|         |       |        |--------+--------+--------+--------+--------+----------|
     _______  , KC_PERC , KC_CIRC , KC_LBRC , KC_RBRC , KC_AT   , _______ ,         _______,  KC_DEL, KC_PGDN, KC_PGUP, _______, _______,  _______ ,
// `----------+---------+---------+---------+---------+-------------------'       `-----------------+--------+--------+--------+--------+----------'
      _______ , _______ , _______ , _______ , _______ ,                                              _______ , _______, _______, _______, _______,
//   `------------------------------------------------'                                             `--------------------------------------------'
//                                                        ,-----------------.   ,-----------------.
                                                           RGB_MOD , _______,    RGB_TOG , RGB_SLD,
//                                               ,--------|--------|--------|   |--------+--------+--------.
                                                                     _______,    _______ ,
//                                               |        |        |--------|   |--------|        |        |
                                                  RGB_VAD , RGB_VAI, _______,    _______ , RGB_HUD, RGB_HUI
//                                               `--------------------------'   `--------------------------'
),
// MEDIA AND MOUSE
[MNAV] = LAYOUT_ergodox_pretty(
// ,----------------------------------------------------------------------.       ,----------------------------------------------------------------.
      _______ , _______ , _______ , _______ , _______ , _______ , _______ ,        _______ , _______, _______, _______, _______, _______,  _______ ,
// |----------+---------+---------+---------+---------+---------+---------|       |--------+--------+--------+--------+--------+--------+----------|
      _______ , _______ , _______ , _______ , _______ , _______ , _______ ,        _______ , _______, KC_BTN1, KC_BTN2, KC_BTN3, KC_ACL0,  _______ ,
// |----------+---------+---------+---------+---------+---------|         |       |        |--------+--------+--------+--------+--------+----------|
      _______ , _______ , _______ , _______ , _______ , _______,/*--------|       |-------*/ KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_ACL1,  KC_MPLY ,
// |----------+---------+---------+---------+---------+---------|         |       |        |--------+--------+--------+--------+--------+----------|
      _______ , _______ , _______ , _______ , _______ , _______ , _______ ,        _______ , KC_WH_L, KC_WH_U, KC_WH_D, KC_WH_R, KC_ACL2,  _______ ,
// `----------+---------+---------+---------+---------+-------------------'       `-----------------+--------+--------+--------+--------+----------'
      _______ , _______ , _______ , _______ , _______ ,                                               _______, KC_VOLD, KC_MUTE, _______, _______,
//   `------------------------------------------------'                                             `--------------------------------------------'
//                                                        ,-----------------.   ,-----------------.
                                                           _______ , _______,    _______ , _______,
//                                               ,--------|--------|--------|   |--------+--------+--------.
                                                                    _______ ,    _______ ,
//                                               |        |        |--------|   |--------|        |        |
                                                  _______ , _______, _______,    _______ , _______, KC_WBAK
//                                               `--------------------------'   `--------------------------'
),
// NUMBERS
[NUMB] = LAYOUT_ergodox_pretty(
// ,----------------------------------------------------------------------.       ,----------------------------------------------------------------.
      _______ , XXXXXXX , XXXXXXX ,  XXXXXXX, XXXXXXX , XXXXXXX , _______ ,        _______ , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  _______ ,
// |----------+---------+---------+---------+---------+---------+---------|       |--------+--------+--------+--------+--------+--------+----------|
      _______ , _______ , _______ ,   KC_E  , _______ , _______ , _______ ,        _______ , KC_PMNS,  KC_7  ,  KC_8  ,  KC_9  , KC_PAST,  _______ ,
// |----------+---------+---------+---------+---------+---------|         |       |        |--------+--------+--------+--------+--------+----------|
      _______ ,   KC_A  , _______ ,   KC_D  ,   KC_F  , _______,/*--------|       |-------*/ KC_PPLS,  KC_4  ,  KC_5  ,  KC_6  , KC_DOT ,  _______ ,
// |----------+---------+---------+---------+---------+---------|         |       |        |--------+--------+--------+--------+--------+----------|
      _______ , _______ , _______ ,   KC_C  , _______ ,  KC_B   , _______ ,        _______ , KC_PEQL,  KC_1  ,  KC_2  ,  KC_3  , KC_PSLS,  _______ ,
// `----------+---------+---------+---------+---------+-------------------'       `-----------------+--------+--------+--------+--------+----------'
      _______ , _______ , _______ , _______ , _______ ,                                              _______ ,  KC_0  , KC_DOT , _______, _______,
//   `------------------------------------------------'                                             `--------------------------------------------'
//                                                        ,-----------------.   ,-----------------.
                                                           _______ , _______,    _______ , _______,
//                                               ,--------|--------|--------|   |--------+--------+--------.
                                                                     _______,    _______ ,
//                                               |        |        |--------|   |--------|        |        |
                                                  _______ , _______, _______,    _______ , _______,  KC_0
//                                               `--------------------------'   `--------------------------'
),
};

uint16_t not_keycodes[10] = { KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0 };

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case RGB_SLD:
        if (record->event.pressed) {
          #ifdef RGBLIGHT_ENABLE
            rgblight_mode(1);
          #endif
        }
        return false;
    case NOT_1:
    case NOT_2:
    case NOT_3:
    case NOT_4:
    case NOT_5:
    case NOT_6:
    case NOT_7:
    case NOT_8:
    case NOT_9:
    case NOT_0:
        if ((keyboard_report->mods & MOD_BIT(KC_LSFT)) || (keyboard_report->mods & MOD_BIT(KC_RSFT))) {
            if (record->event.pressed)
                register_code(not_keycodes[keycode-NOT_1]);
            else
                unregister_code(not_keycodes[keycode-NOT_1]);
        }
        return true;
    case KC_CAPSLOCK:
        if (!record->event.pressed)
            _delay_ms(50);
        return true;
    default:
        return true;
    }
}

void trackball_set_rgbw(uint8_t red, uint8_t green, uint8_t blue, uint8_t white)
{
    i2c_status_t result = i2c_start(TRACKBALL_WRITE, ERGODOX_EZ_I2C_TIMEOUT);
    if (result == I2C_STATUS_SUCCESS) {
        i2c_write(0x00, ERGODOX_EZ_I2C_TIMEOUT);
        i2c_write(red, ERGODOX_EZ_I2C_TIMEOUT);
        i2c_write(green, ERGODOX_EZ_I2C_TIMEOUT);
        i2c_write(blue, ERGODOX_EZ_I2C_TIMEOUT);
        i2c_write(white, ERGODOX_EZ_I2C_TIMEOUT);
    }
    i2c_stop();
}

int16_t mouse_offset(uint8_t positive, uint8_t negative, int16_t scale)
{
    int16_t offset = (int16_t)positive - (int16_t)negative;
    int16_t magnitude = scale*offset*offset;
    return offset < 0 ? -magnitude : magnitude;
}

static uint8_t scrolling = 0;
static int16_t x_offset = 0;
static int16_t y_offset = 0;
static int16_t h_offset = 0;
static int16_t v_offset = 0;

void update_member(int8_t* member, int16_t* offset)
{
    if (*offset > 127) {
        *member = 127;
        *offset -= 127;
    } else if (*offset < -127) {
        *member = -127;
        *offset += 127;
    } else {
        *member = *offset;
        *offset = 0;
    }
}

void trackball_check_mouse(void)
{
    uint8_t state[5] = {};
    i2c_status_t result = i2c_readReg(TRACKBALL_WRITE, 0x04, state, 5, ERGODOX_EZ_I2C_TIMEOUT);
    if (result != I2C_STATUS_SUCCESS) {
        ergodox_right_led_1_on();
    } else {
        if (scrolling) {
            h_offset += mouse_offset(state[2], state[3], 1);
            v_offset -= mouse_offset(state[1], state[0], 1);
        } else {
            x_offset += mouse_offset(state[2], state[3], 5);
            y_offset += mouse_offset(state[1], state[0], 5);
        }
    }

    report_mouse_t mouse = pointing_device_get_report();
    if (state[4] & (1<<7)) {
        mouse.buttons |= MOUSE_BTN1;
    } else {
        mouse.buttons &= ~MOUSE_BTN1;
    }
    update_member(&mouse.x, &x_offset);
    update_member(&mouse.y, &y_offset);
    update_member(&mouse.v, &v_offset);
    update_member(&mouse.h, &h_offset);
    pointing_device_set_report(mouse);
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
    trackball_set_rgbw(0x0,0x0,0x0,0x0);
#ifdef RGBLIGHT_COLOR_LAYER_0
    rgblight_setrgb(RGBLIGHT_COLOR_LAYER_0);
#endif
}

void matrix_scan_user(void) {
    trackball_check_mouse();
}

// Runs whenever there is a layer state change.
uint32_t layer_state_set_user(uint32_t state) {
  ergodox_board_led_off();
  ergodox_right_led_1_off();
  ergodox_right_led_2_off();
  ergodox_right_led_3_off();

  uint8_t layer = biton32(state);
  if (layer == MNAV)
      scrolling = 1;
  else
      scrolling = 0;
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
}
