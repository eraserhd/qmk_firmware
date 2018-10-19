#ifndef keymap_h_INCLUDED
#define keymap_h_INCLUDED

#define BASE 0 // default layer
#define SYMB 1 // symbols & keyboard navigation
#define MNAV 2 // media keys

#define KC_SLEEP LSFT(LCTL(KC_POWER))

enum custom_keycodes {
  PLACEHOLDER = SAFE_RANGE, // can always be here
  RGB_SLD,
  X_META,
  DOT_META
};

enum {
    TD_RESET = 0,
    TD_SLEEP
};

#endif /* keymap_h_INCLUDED */
