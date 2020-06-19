#include QMK_KEYBOARD_H
#include "debug.h"
#include "action_layer.h"
#include "pointing_device.h"
#include "version.h"
#include "prompt.h"

extern uint8_t is_master;

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
int RGB_current_mode;
#endif

#ifdef OLED_DRIVER_ENABLE
static uint32_t oled_timer = 0;
#endif

enum layers
{
    _Qwerty,
    _Symbol,
    _Mouse,
    _Number,
    _Command,
    _Window
};

enum custom_keycodes
{
    FKEY_0 = SAFE_RANGE, // can always be here
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] =
{

#define _CAP_Symb_  LT(_Symbol,KC_CAPSLOCK)
#define _D_Num_     LT(_Number,KC_D)
#define _F__Symbol_ LT(_Symbol,KC_F)
#define _Z_LCtl_    LCTL_T(KC_Z)
#define _X_LAlt_    LALT_T(KC_X)
#define _Tab_Cmd    LGUI_T(KC_TAB)
#define _Qu_Symb_   LT(_Symbol,KC_QUOT)
#define Dot_RAlt    RALT_T(KC_DOT)
#define Slsh_Ctl    RCTL_T(KC_SLSH)
#define Bspc_Cmd    LGUI_T(KC_BSPC)
#define _Q_Mouse_   LT(_Mouse,KC_Q)
#define _W_Win_     LT(_Window,KC_W)

    [_Qwerty] = LAYOUT(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      KC_MINS,_Q_Mouse_,_W_Win_,  KC_E  ,  KC_R  ,  KC_T  ,                        KC_Y ,  KC_U  ,  KC_I  ,  KC_O  ,  KC_P  , KC_BSLS,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
   _CAP_Symb_,  KC_A  ,  KC_S  ,_D_Num_ ,  KC_F  ,  KC_G  ,                        KC_H ,  KC_J  ,  KC_K  ,  KC_L  , KC_SCLN ,_Qu_Symb_,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,_Z_LCtl_,_X_LAlt_,  KC_C  ,  KC_V  ,  KC_B  ,                        KC_N ,  KC_M  , KC_COMM,Dot_RAlt,Slsh_Ctl, KC_RSFT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                      TO(_Command), KC_ENT ,_Tab_Cmd,   Bspc_Cmd, KC_SPC , KC_ESC
                                      //`--------------------------'  `--------------------------'

    ),
    [_Symbol] = LAYOUT(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      _______, KC_EXLM, KC_TILD, KC_LCBR, KC_RCBR, KC_AMPR,                      KC_HOME, _______, KC_INS , KC_END , KC_PGUP, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, KC_HASH, KC_GRV , KC_LPRN, KC_RPRN, KC_DLR ,                      KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT, _______, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, KC_PERC, KC_CIRC, KC_LBRC, KC_RBRC, KC_AT  ,                      KC_DEL , KC_PGDN, KC_PGUP, _______, KC_PGDN, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, KC_EQL , _______,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'
    ),
    [_Mouse] = LAYOUT(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      _______, _______, _______, _______, _______, _______,                     _______ , KC_BTN1, KC_BTN2, KC_BTN3, KC_VOLU, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______,                     KC_MS_L , KC_MS_D, KC_MS_U, KC_MS_R, _______, KC_MPLY,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______,                     KC_WH_L , KC_WH_U, KC_WH_D, KC_WH_R, KC_VOLD, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______, _______, _______
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
    [_Command] = LAYOUT(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      _______, _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'
    ),
    [_Window] = LAYOUT(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      _______, _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'
    ),
};

void matrix_init_user(void)
{
#ifdef RGBLIGHT_ENABLE
    RGB_current_mode = rgblight_config.mode;
#endif
}

char row_and_column[8] = "  x  ";

void set_keylog(uint16_t keycode, keyrecord_t *record)
{
    snprintf(row_and_column, sizeof(row_and_column), "%2dx%d", record->event.key.row, record->event.key.col);
}

#ifdef OLED_DRIVER_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation)
{
    if (is_master)
        return OLED_ROTATION_270;
    return rotation;
}

const char *read_logo(void);

void advance_line(void)
{
    oled_write_ln_P(PSTR("     "), false);
}

void oled_task_user(void)
{
    if (timer_elapsed32(oled_timer) > 10000)
    {
        oled_off();
        return;
    }
    if (is_master)
    {
        switch (biton32(layer_state))
        {
        case _Command:
            write_prompt_to_oled();
            break;
        case _Qwerty:  oled_write_ln_P(PSTR("   A "), false); break;
        case _Symbol:  oled_write_ln_P(PSTR("   ) "), false); break;
        case _Mouse:   oled_write_ln_P(PSTR("   M "), false); break;
        case _Number:  oled_write_ln_P(PSTR("   1 "), false); break;
        case _Window:  oled_write_ln_P(PSTR("   W "), false); break;
        default:       oled_write_ln_P(PSTR("   ? "), false); break;
        }

        advance_line();
        oled_write_ln(row_and_column, false);
        advance_line();

        led_t led_state = host_keyboard_led_state();
        if (led_state.caps_lock)
            oled_write_ln_P(PSTR("CAPS"), false);
        else
            advance_line();
    }
    else
    {
        oled_write(read_logo(), false);
    }
}
#endif

bool in_window_layer = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
#ifdef OLED_DRIVER_ENABLE
    if (record->event.pressed)
        oled_timer = timer_read32();
#endif

    if (layer_state_is(_Command))
        return prompt_key(keycode, record);

    if (record->event.pressed)
        set_keylog(keycode, record);

    switch (keycode)
    {
    /* Defeat Mac OS's defeat of caps lock. */
    case KC_CAPSLOCK:
        if (!record->event.pressed)
            _delay_ms(50);
        return true;
    default:
        return true;
    }

    return true;
}

uint32_t layer_state_set_user(uint32_t state)
{
  if (layer_state_cmp(state, _Window) && !in_window_layer)
  {
      register_code(KC_LGUI);
      register_code(KC_LSHIFT);
      register_code(KC_LALT);
      register_code(KC_LCTRL);
      _delay_ms(15);
      register_code(KC_K);
      unregister_code(KC_K);
      unregister_code(KC_LGUI);
      unregister_code(KC_LSHIFT);
      unregister_code(KC_LALT);
      unregister_code(KC_LCTRL);
      in_window_layer = true;
  }
  if (!layer_state_cmp(state, _Window) && in_window_layer)
  {
      tap_code(KC_ESCAPE);
      in_window_layer = false;
  }
  return state;
}
