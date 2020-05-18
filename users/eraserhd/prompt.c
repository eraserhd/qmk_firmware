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
    if (!strcmp(prompt+1, "sleep"))
    {
        tap_code16(LSFT(LCTL(KC_POWER)));
    }
}

bool prompt_key(uint16_t keycode, keyrecord_t* record)
{
    if (!record->event.pressed)
        return false;

    char to_add = 0;
    switch (keycode & 0xFF)
    {
    case KC_A ... KC_Z:
        to_add = 'a' + (keycode - KC_A);
        break;
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

    if (to_add && prompt_offset < sizeof(prompt) - 1)
    {
        prompt[prompt_offset++] = to_add;
        prompt[prompt_offset] = '\0';
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

