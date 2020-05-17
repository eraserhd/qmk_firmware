#include QMK_KEYBOARD_H
#include "debug.h"
#include "action_layer.h"
#include "pointing_device.h"
#include "version.h"

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

enum layers {
    _Qwerty,
    _Symbol,
    _Mouse,
    _Number,
    _Command,
    _Window
};

enum custom_keycodes {
    FKEY_0 = SAFE_RANGE, // can always be here
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

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

int RGB_current_mode;

void matrix_init_user(void)
{
    #ifdef RGBLIGHT_ENABLE
      RGB_current_mode = rgblight_config.mode;
    #endif
    //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
    #ifdef SSD1306OLED
        iota_gfx_init(!has_usb());   // turns on the display
    #endif
}

char prompt[40] = ":";
uint8_t prompt_offset = 1;

#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation)
{
    if (is_master)
        return OLED_ROTATION_270;
    return rotation;
}

const char *read_logo(void);
const char *read_keylog(void);
const char *read_layer_state(void);

void oled_task_user(void)
{
    if (is_master)
    {
        switch (biton32(layer_state))
        {
        case _Qwerty:  oled_write_ln_P(PSTR("QWRTY"), false); break;
        case _Symbol:  oled_write_ln_P(PSTR("SYMBL"), false); break;
        case _Mouse:   oled_write_ln_P(PSTR("MOUSE"), false); break;
        case _Number:  oled_write_ln_P(PSTR("NUMBR"), false); break;
        case _Command: oled_write_ln_P(PSTR("COMMD"), false); break;
        case _Window:  oled_write_ln_P(PSTR("WINDW"), false); break;
        default:       oled_write_ln_P(PSTR(" ??? "), false); break;
        }
    }
    else
    {
        oled_write(read_logo(), false);
    }
}
#endif

//SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED

// When add source files to SRC in rules.mk, you can use functions.
const char *read_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylogs(void);

// const char *read_mode_icon(bool swap);
// const char *read_host_led_state(void);
// void set_timelog(void);
// const char *read_timelog(void);

void matrix_scan_user(void)
{
   iota_gfx_task();
}

void matrix_render_user(struct CharacterMatrix *matrix)
{
    if (is_master)
    {
        if (layer_state_is(_Command))
        {
            matrix_write_ln(matrix, prompt);
        }
        else
        {
            // If you want to change the display of OLED, you need to change here
            matrix_write_ln(matrix, read_layer_state());
            matrix_write_ln(matrix, read_keylog());
            //matrix_write_ln(matrix, read_keylogs());
            //matrix_write_ln(matrix, read_mode_icon(keymap_config.swap_lalt_lgui));
            //matrix_write_ln(matrix, read_host_led_state());
            //matrix_write_ln(matrix, read_timelog());
        }
    }
    else
    {
        matrix_write(matrix, read_logo());
    }
}

void matrix_update(struct CharacterMatrix *dest, const struct CharacterMatrix *source)
{
    if (memcmp(dest->display, source->display, sizeof(dest->display)))
    {
        memcpy(dest->display, source->display, sizeof(dest->display));
        dest->dirty = true;
    }
}

void iota_gfx_task_user(void)
{
  struct CharacterMatrix matrix;
  matrix_clear(&matrix);
  matrix_render_user(&matrix);
  matrix_update(&display, &matrix);
}
#endif//SSD1306OLED

bool in_window_layer = false;

void run_command(void)
{
    if (!strcmp(prompt, ":sleep"))
    {
        tap_code16(LSFT(LCTL(KC_POWER)));
    }
}

void clear_command(void)
{
    prompt_offset = 1;
    prompt[prompt_offset] = '\0';
}

bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
    if (layer_state_is(_Command))
    {
        if (record->event.pressed)
        {
            char to_add = 0;
            switch (keycode)
            {
            case KC_A ... KC_Z:
                to_add = 'a' + (keycode - KC_A);
                break;
            case KC_ENT:
                run_command();
                /* fall through */
            case KC_ESC:
                clear_command();
                layer_move(_Qwerty);
                break;
            }

            if (to_add && prompt_offset < sizeof(prompt) - 1)
            {
                prompt[prompt_offset++] = to_add;
                prompt[prompt_offset] = '\0';
            }
        }
        return false;
    }

    if (record->event.pressed)
    {
#ifdef SSD1306OLED
        set_keylog(keycode, record);
#endif
        // set_timelog();
      }

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
      register_code(KC_F13);
      unregister_code(KC_F13);
      in_window_layer = true;
  }
  if (!layer_state_cmp(state, _Window) && in_window_layer)
  {
      register_code(KC_F14);
      unregister_code(KC_F14);
      in_window_layer = false;
  }
  return state;
}
