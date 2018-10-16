
static struct {
    bool x_held : 1;
    bool dot_held : 1;
    bool sent : 1;
} meta_state = { 0 };

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case RGB_SLD:
      if (record->event.pressed) {
        #ifdef RGBLIGHT_ENABLE
          rgblight_mode(1);
        #endif
      }
      return false;
    case X_META:
      if (record->event.pressed) {
          meta_state.x_held = true;
          meta_state.sent = false;
      } else {
          meta_state.x_held = false;
          if (!meta_state.sent) {
              if (meta_state.dot_held) {
                  meta_state.sent = true;
                  register_code(KC_ESC);
                  unregister_code(KC_ESC);
              }
              register_code(KC_X);
              unregister_code(KC_X);
          }
      }
      return false;
    case DOT_META:
      if (record->event.pressed) {
          meta_state.dot_held = true;
          meta_state.sent = false;
      } else {
          meta_state.dot_held = false;
          if (!meta_state.sent) {
              if (meta_state.x_held) {
                  meta_state.sent = true;
                  register_code(KC_ESC);
                  unregister_code(KC_ESC);
              }
              register_code(KC_DOT);
              unregister_code(KC_DOT);
          }
      }
      return false;
    default:
      if (meta_state.x_held || meta_state.dot_held) {
        switch (keycode) {
        case KC_CAPSLOCK:
        case KC_SCROLLLOCK:
        case KC_NUMLOCK:
        case KC_LOCKING_CAPS:
        case KC_LOCKING_NUM:
        case KC_LOCKING_SCROLL:
        case KC_LCTRL:
        case KC_LSHIFT:
        case KC_LALT:
        case KC_LGUI:
        case KC_RCTRL:
        case KC_RSHIFT:
        case KC_RALT:
        case KC_RGUI:
        case KC_NO:
        case KC_TRNS:
          break;
        default:
          if (record->event.pressed) {
            return false;
          } else {
            meta_state.sent = true;
            register_code(KC_ESC);
            unregister_code(KC_ESC);
            register_code(keycode);
          }
        }
      }
      return true;
  }
}
