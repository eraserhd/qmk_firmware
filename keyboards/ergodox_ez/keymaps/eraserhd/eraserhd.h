#ifndef keymap_h_INCLUDED
#define keymap_h_INCLUDED

#define BASE 0 // default layer
#define SYMB 1 // symbols
#define MNAV 2 // media keys
#define KNAV 3 // keyboard navigation

#define KC_SLEEP LSFT(LCTL(KC_POWER))

enum custom_keycodes {
  PLACEHOLDER = SAFE_RANGE, // can always be here
  RGB_SLD,
  META,
  X_META,
  DOT_META
};

#endif /* keymap_h_INCLUDED */
