#include QMK_KEYBOARD_H
#include "prompt.h"

char prompt[40] = ">";
uint8_t prompt_offset = 1;

void clear_prompt_command(void)
{
    prompt_offset = 1;
    prompt[prompt_offset] = '\0';
}

void run_command(void)
{
    if (!strcmp_P(prompt+1, PSTR("sleep")))
        tap_code16(LSFT(LCTL(KC_POWER)));
#ifdef UNICODE_ENABLE
    else if (!strcmp_P(prompt+1, PSTR("unicode mac")))
        tap_code16(UNICODE_MODE_MAC);
    else if (!strcmp_P(prompt+1, PSTR("unicode linux")))
        tap_code16(UNICODE_MODE_LNX);
    else if (!strcmp_P(prompt+1, PSTR("unicode bsd")))
        tap_code16(UNICODE_MODE_BSD);
    else if (!strcmp_P(prompt+1, PSTR("unicode windows")))
        tap_code16(UNICODE_MODE_WIN);
    else if (!strcmp_P(prompt+1, PSTR("unicode wincompose")))
        tap_code16(UNICODE_MODE_WINC);
#endif
}

const char mapping[] PROGMEM = {
    // unshifted
      0,   0,   0,   0, 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', // 0x00
    'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '1', '2', // 0x10
    '3', '4', '5', '6', '7', '8', '9', '0',   0,   0,   0,   0, ' ', '-', '=', '[', // 0x20
    ']','\\', '#', ';','\'', '`', ',', '.', '/',   0,   0,   0,   0,   0,   0,   0, // 0x30

    // shifted
      0,   0,   0,   0, 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', // 0x00
    'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '!', '@', // 0x10
    '#', '$', '%', '^', '&', '*', '(', ')',   0,   0,   0,   0, ' ', '_', '+', '{', // 0x20
    '}', '|', '#', ':', '"', '~', '<', '>', '?',   0,   0,   0,   0,   0,   0,   0, // 0x30
};

bool prompt_key(uint16_t keycode, keyrecord_t* record)
{
    switch (keycode)
    {
    case KC_LSFT:
    case KC_RSFT:
        return true;
    }

    if (!record->event.pressed)
        return false;

    uint8_t index = keycode & 0xFF;
    if (index < sizeof(mapping)/sizeof(mapping[0]))
    {
        if (get_mods() & MOD_MASK_SHIFT)
            index += 0x40;
        char to_add = pgm_read_byte_near(mapping + index);
        if (to_add && prompt_offset < sizeof(prompt) - 1)
        {
            prompt[prompt_offset++] = to_add;
            prompt[prompt_offset] = '\0';
        }
    }

    switch (keycode & 0xFF)
    {
    case KC_BSPC:
        if (prompt_offset > 1)
            prompt[--prompt_offset] = '\0';
        break;
    case KC_ENT:
        run_command();
        /* fall through */
    case KC_ESC:
        clear_prompt_command();
        layer_move(0);
        break;
    }

    return false;
}

#ifdef OLED_DRIVER_ENABLE
void write_prompt_to_oled(void)
{
    uint8_t width = oled_max_chars();
    uint8_t prompt_display_offset = 0;
    bool seen_end = false;

    if (prompt_offset > width)
        prompt_display_offset = prompt_offset - width;

    for (uint8_t i = 0; i < width; i++)
    {
        if (!seen_end && !prompt[prompt_display_offset + i])
            seen_end = true;
        oled_write_char(seen_end ? ' ' : prompt[prompt_display_offset + i], false);
    }
}
#endif

