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
    _FnKeys
};

enum custom_keycodes {
    FKEY_0 = SAFE_RANGE, // can always be here
    FKEY_1,
    FKEY_2,
    FKEY_3,
    FKEY_4,
    FKEY_5,
    FKEY_6,
    FKEY_7,
    FKEY_8,
    FKEY_9,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

#define _CAP_Symb_ LT(_Symbol,KC_CAPSLOCK)
#define _D_Num_    LT(_Number,KC_D)
#define _F__Symbol_   LT(_Symbol,KC_F)
#define _Z_LCtl_   LCTL_T(KC_Z)
#define _X_LAlt_   LALT_T(KC_X)
#define _Tab_Cmd   LGUI_T(KC_TAB)
#define _Qu_Symb_  LT(_Symbol,KC_QUOT)
#define Dot_RAlt   RALT_T(KC_DOT)
#define Slsh_Ctl   RCTL_T(KC_SLSH)
#define Bspc_Cmd   LGUI_T(KC_BSPC)
#define _Q_Mouse_   LT(_Mouse,KC_Q)

    [_Qwerty] = LAYOUT(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      KC_MINS,_Q_Mouse_,  KC_W  ,  KC_E  ,  KC_R  ,  KC_T  ,                        KC_Y ,  KC_U  ,  KC_I  ,  KC_O  ,  KC_P  , KC_BSLS,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
   _CAP_Symb_,  KC_A  ,  KC_S  ,_D_Num_ ,  KC_F  ,  KC_G  ,                        KC_H ,  KC_J  ,  KC_K  ,  KC_L  , KC_SCLN ,_Qu_Symb_,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,_Z_LCtl_,_X_LAlt_,  KC_C  ,  KC_V  ,  KC_B  ,                        KC_N ,  KC_M  , KC_COMM,Dot_RAlt,Slsh_Ctl, KC_RSFT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                      MO(_FnKeys), KC_ENT ,_Tab_Cmd,   Bspc_Cmd, KC_SPC , KC_ESC
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
    [_FnKeys] = LAYOUT(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      EEP_RST, _______, _______, _______, _______, _______,                      _______, FKEY_7 , FKEY_8 , FKEY_9 , _______, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______,                      _______, FKEY_4 , FKEY_5 , FKEY_6 , _______, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______,                      _______, FKEY_1 , FKEY_2 , FKEY_3 , _______, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______, _______, FKEY_0
                                      //`--------------------------'  `--------------------------'
    ),
};

int RGB_current_mode;

void matrix_init_user(void) {
    #ifdef RGBLIGHT_ENABLE
      RGB_current_mode = rgblight_config.mode;
    #endif
    //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
    #ifdef SSD1306OLED
        iota_gfx_init(!has_usb());   // turns on the display
    #endif
}

//SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED

// When add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);

// const char *read_mode_icon(bool swap);
// const char *read_host_led_state(void);
// void set_timelog(void);
// const char *read_timelog(void);

void matrix_scan_user(void) {
   iota_gfx_task();
}

void matrix_render_user(struct CharacterMatrix *matrix) {
  if (is_master) {
    // If you want to change the display of OLED, you need to change here
    matrix_write_ln(matrix, read_layer_state());
    matrix_write_ln(matrix, read_keylog());
    //matrix_write_ln(matrix, read_keylogs());
    //matrix_write_ln(matrix, read_mode_icon(keymap_config.swap_lalt_lgui));
    //matrix_write_ln(matrix, read_host_led_state());
    //matrix_write_ln(matrix, read_timelog());
  } else {
    matrix_write(matrix, read_logo());
  }
}

void matrix_update(struct CharacterMatrix *dest, const struct CharacterMatrix *source) {
  if (memcmp(dest->display, source->display, sizeof(dest->display))) {
    memcpy(dest->display, source->display, sizeof(dest->display));
    dest->dirty = true;
  }
}

void iota_gfx_task_user(void) {
  struct CharacterMatrix matrix;
  matrix_clear(&matrix);
  matrix_render_user(&matrix);
  matrix_update(&display, &matrix);
}
#endif//SSD1306OLED

uint8_t fkey_number = 0;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
#ifdef SSD1306OLED
    set_keylog(keycode, record);
#endif
    // set_timelog();
  }
  switch (keycode) {
  case FKEY_0: case FKEY_1: case FKEY_2: case FKEY_3: case FKEY_4: case FKEY_5: case FKEY_6: case FKEY_7: case FKEY_8: case FKEY_9:
      if (record->event.pressed)
          fkey_number = fkey_number * 10 + (keycode - FKEY_0);
      return false;
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

uint32_t layer_state_set_user(uint32_t state) {
  uint8_t layer = biton32(state);
  if (layer != _FnKeys && fkey_number > 0) {
      if (fkey_number <= 12) {
          uint16_t code = KC_F1 - 1 + fkey_number;
          register_code(code);
          unregister_code(code);
      } else if (fkey_number <= 24) {
          uint16_t code = KC_F13 - 13 + fkey_number;
          register_code(code);
          unregister_code(code);
      }
      fkey_number = 0;
  }
  return state;
}
