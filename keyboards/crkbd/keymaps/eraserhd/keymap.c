#include QMK_KEYBOARD_H
#include "debug.h"
#include "action_layer.h"
#include "pointing_device.h"
#include "version.h"
#include "prompt.h"
#include "analog.h"

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
int RGB_current_mode;
#endif

enum layers
{
    _Qwerty,
    _Symbol,
    _Mouse,
    _Number,
};

enum custom_keycodes
{
    _Prompt_ = SAFE_RANGE, // can always be here
    _LMenu_,
    _MDrag_
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] =
{

#define _CAP_Symb_  LT(_Symbol,KC_CAPSLOCK)
#define _D_Num_     LT(_Number,KC_D)
#define _Z_LCtl_    LCTL_T(KC_Z)
#define _X_LAlt_    LALT_T(KC_X)
#define _Tab_Cmd    LGUI_T(KC_TAB)
#define _Qu_Symb_   LT(_Symbol,KC_QUOT)
#define Dot_RAlt    RALT_T(KC_DOT)
#define Slsh_Ctl    RCTL_T(KC_SLSH)
#define Bspc_Cmd    LGUI_T(KC_BSPC)
#define _Q_Mouse_   LT(_Mouse,KC_Q)
#define _RMenu_     LCTL(KC_F8)

    [_Qwerty] = LAYOUT(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      KC_MINS,_Q_Mouse_, KC_W  ,  KC_E  ,  KC_R  ,  KC_T  ,                        KC_Y ,  KC_U  ,  KC_I  ,  KC_O  ,  KC_P  , KC_BSLS,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
   _CAP_Symb_,  KC_A  ,  KC_S  ,_D_Num_ ,  KC_F  ,  KC_G  ,                        KC_H ,  KC_J  ,  KC_K  ,  KC_L  , KC_SCLN ,_Qu_Symb_,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,_Z_LCtl_,_X_LAlt_,  KC_C  ,  KC_V  ,  KC_B  ,                        KC_N ,  KC_M  , KC_COMM,Dot_RAlt,Slsh_Ctl, KC_RSFT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                         _Prompt_, KC_ENT ,_Tab_Cmd,   Bspc_Cmd, KC_SPC , KC_ESC
                                      //`--------------------------'  `--------------------------'

    ),
    [_Symbol] = LAYOUT(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      _______, KC_EXLM, KC_TILD, KC_LCBR, KC_RCBR, KC_AMPR,                      _LMenu_, XXXXXXX, XXXXXXX, _RMenu_, KC_PGUP, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, KC_HASH, KC_GRV , KC_LPRN, KC_RPRN, KC_DLR ,                      KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT, _______, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, KC_PERC, KC_CIRC, KC_LBRC, KC_RBRC, KC_AT  ,                      KC_DEL , KC_END , KC_HOME, KC_INS , KC_PGDN, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, XXXXXXX, _______,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'
    ),
    [_Mouse] = LAYOUT(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      _______, _______, _______, KC_BTN1, KC_BTN2, _______,                     _______ , XXXXXXX, XXXXXXX, _______, KC_VOLU, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______,                     _______ , KC_BTN1, KC_BTN3, KC_BTN2, _______, KC_MPLY,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______,                     KC_WH_L , KC_WH_D, KC_WH_U, KC_WH_R, KC_VOLD, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _MDrag_, KC_BTN1,    KC_BTN2, _______, KC_BTN3
                                      //`--------------------------'  `--------------------------'
    ),
    [_Number] = LAYOUT(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      _______, _______, _______,   KC_E , _______, _______,                      KC_MINS,  KC_7  ,  KC_8  ,  KC_9  , KC_ASTR, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______,   KC_A , _______,   KC_D ,   KC_F , _______,                      KC_PLUS,  KC_4  ,  KC_5  ,  KC_6  , KC_DOT , _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, _______, _______,   KC_C , _______,  KC_B  ,                      KC_EQL ,  KC_1  ,  KC_2  ,  KC_3  , KC_SLSH, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______, _______,  KC_0
                                      //`--------------------------'  `--------------------------'
    ),
};

int16_t xOrigin;
int16_t yOrigin;

void matrix_init_user(void)
{
#ifdef RGBLIGHT_ENABLE
    RGB_current_mode = rgblight_config.mode;
#endif
    xOrigin = analogReadPin(ANALOG_JOYSTICK_X_AXIS_PIN);
    yOrigin = analogReadPin(ANALOG_JOYSTICK_Y_AXIS_PIN);
}

char row_and_column[8] = "  x  ";

void set_keylog(uint16_t keycode, keyrecord_t *record)
{
    snprintf(row_and_column, sizeof(row_and_column), "%2dx%d", record->event.key.row, record->event.key.col);
}

#ifdef OLED_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation)
{
    if (is_keyboard_master())
        return OLED_ROTATION_270;
    return rotation;
}

const char *read_logo(void);

void advance_line(void)
{
    oled_write_ln_P(PSTR("     "), false);
}

#define X_MIN    75
#define X_MAX    793

#define Y_MIN    135
#define Y_MAX    855

int16_t joystickX;
int16_t joystickY;

bool oled_task_user(void)
{
    if (is_keyboard_master())
    {
        if (in_prompt())
            write_prompt_to_oled();
        else
        {
            switch (get_highest_layer(layer_state))
            {
            case _Qwerty:  oled_write_ln_P(PSTR("   A"), false); break;
            case _Symbol:  oled_write_ln_P(PSTR("   )"), false); break;
            case _Mouse:   oled_write_ln_P(PSTR("   M"), false); break;
            case _Number:  oled_write_ln_P(PSTR("   1"), false); break;
            default:       oled_write_ln_P(PSTR("   ?"), false); break;
            }
        }

        advance_line();
        oled_write_ln(row_and_column, false);
        advance_line();

        led_t led_state = host_keyboard_led_state();
        if (led_state.caps_lock)
            oled_write_ln_P(PSTR("CAPS"), false);
        else
            advance_line();

        char buf[7];
        snprintf(buf, 6, " %d", joystickX);
        oled_write_ln(buf, false);
        snprintf(buf, 6, " %d", joystickY);
        oled_write_ln(buf, false);
    }
    else
    {
        oled_write(read_logo(), false);
    }
    return false;
}
#endif

static _Bool set_scrolling = false;

float joystick_percent(int16_t value, int16_t min, int16_t center, int16_t max)
{
    if (value < center)
    {
        int16_t range = center - min + 1;
        int16_t distance = center - value;
        float percent = (float)distance/(float)range;
        if (percent < 0.02) percent = 0;
        if (percent > 1.0) percent = 1;
        return -percent;
    }
    else
    {
        int16_t range = max - center + 1;
        int16_t distance = value - center;
        float percent = (float)distance/(float)range;
        if (percent < 0.02) percent = 0;
        if (percent > 1.0) percent = 1;
        return +percent;
    }
}

report_mouse_t pointing_device_driver_get_report(report_mouse_t mouse_report)
{
    static uint16_t timer = 0;
    report_mouse_t report = {0};
    if (timer_elapsed(timer) <= (set_scrolling ? 50 : 10))
        return report;
    timer = timer_read();

    joystickX = analogReadPin(ANALOG_JOYSTICK_X_AXIS_PIN);
    joystickY = analogReadPin(ANALOG_JOYSTICK_Y_AXIS_PIN);

    if (set_scrolling)
    {
        report.h = -20 * joystick_percent(joystickX, X_MIN, xOrigin, X_MAX);
        report.v = 20 * joystick_percent(joystickY, Y_MIN, yOrigin, Y_MAX);
    }
    else
    {
        report.x = 35 * joystick_percent(joystickX, X_MIN, xOrigin, X_MAX);
        report.y = 35 * joystick_percent(joystickY, Y_MIN, yOrigin, Y_MAX);
    }
    return report;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
    if (record->event.pressed)
        set_keylog(keycode, record);

    switch (keycode)
    {
    /* Defeat Mac OS's defeat of caps lock. */
    case KC_CAPSLOCK:
        if (!record->event.pressed)
            _delay_ms(50);
        return true;
    case _LMenu_:
        if (record->event.pressed)
        {
            tap_code16(_RMenu_);
            tap_code16(RCTL(KC_F2));
        }
        return false;
    case _Prompt_:
        enter_prompt();
        return false;
    case _MDrag_:
        set_scrolling = record->event.pressed;
        return true;
    default:
        return true;
    }

    return true;
}
