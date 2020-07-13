#include QMK_KEYBOARD_H
#include "host.h"
#include "prompt.h"
#include "report.h"

static host_driver_t* original_driver = NULL;
static report_keyboard_t last_report = {};
static char prompt[40] = ">";
static uint8_t prompt_offset = 1;

static void clear_prompt_command(void)
{
    prompt_offset = 1;
    prompt[prompt_offset] = '\0';
}

static uint16_t look_up_symbol(const char* name)
{
    // f1 through f24
    if (name[0] == 'f')
    {
        if (name[1] >= '1' && name[1] <= '9' && name[2] == '\0')
            return KC_F1 + (name[1] - '1');
        if (name[1] == '1' && name[2] >= '0' && name[2] <= '9' && name[3] == '\0')
            return KC_F10 + (name[1] - '0');
        if (name[1] == '2' && name[2] >= '0' && name[2] <= '4' && name[3] == '\0')
            return KC_F20 + (name[1] - '0');
    }

    if (!strcmp_P(name, PSTR("left")))  return MAGIC_EE_HANDS_LEFT;
    if (!strcmp_P(name, PSTR("right"))) return MAGIC_EE_HANDS_RIGHT;
    if (!strcmp_P(name, PSTR("sleep"))) return LSFT(LCTL(KC_POWER));
    return KC_NO;
}

static void run_command(void)
{
    uint16_t value = look_up_symbol(prompt+1);
    if (value != KC_NO)
        tap_code16(value);
#ifdef RGBLIGHT_ENABLE
    else if (!strcmp_P(prompt+1, PSTR("led off")))
        rgblight_disable();
    else if (!strcmp_P(prompt+1, PSTR("led plain")))
    {
        rgblight_enable();
        rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
    }
    else if (!strcmp_P(prompt+1, PSTR("led breathe")))
    {
        rgblight_enable();
        rgblight_mode_noeeprom(RGBLIGHT_MODE_BREATHING);
    }
    else if (!strcmp_P(prompt+1, PSTR("led rainbow")))
    {
        rgblight_enable();
        rgblight_mode_noeeprom(RGBLIGHT_MODE_RAINBOW_MOOD);
    }
    else if (!strcmp_P(prompt+1, PSTR("led swirl")))
    {
        rgblight_enable();
        rgblight_mode_noeeprom(RGBLIGHT_MODE_RAINBOW_SWIRL);
    }
    else if (!strcmp_P(prompt+1, PSTR("led snake")))
    {
        rgblight_enable();
        rgblight_mode_noeeprom(RGBLIGHT_MODE_SNAKE);
    }
    else if (!strcmp_P(prompt+1, PSTR("led knight")))
    {
        rgblight_enable();
        rgblight_mode_noeeprom(RGBLIGHT_MODE_KNIGHT);
    }
    else if (!strcmp_P(prompt+1, PSTR("led xmas")))
    {
        rgblight_enable();
        rgblight_mode_noeeprom(RGBLIGHT_MODE_CHRISTMAS);
    }
    else if (!strcmp_P(prompt+1, PSTR("led gradient")))
    {
        rgblight_enable();
        rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_GRADIENT);
    }
    else if (!strcmp_P(prompt+1, PSTR("led test")))
    {
        rgblight_enable();
        rgblight_mode(RGBLIGHT_MODE_RGB_TEST);
    }
#endif
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

static const char mapping[] PROGMEM =
{
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

static uint8_t keyboard_leds(void)
{
    return original_driver->keyboard_leds();
}

static bool in_last_report(uint8_t key)
{
    for (uint8_t i = 0; i < KEYBOARD_REPORT_KEYS; i++)
        if (last_report.keys[i] == key)
            return true;
    return false;
}

static void send_keyboard(report_keyboard_t *report)
{
    for (uint8_t i = 0; i < KEYBOARD_REPORT_KEYS; i++)
    {
        if (in_last_report(report->keys[i]))
            continue;
        switch (report->keys[i])
        {
        case KC_LSHIFT:
        case KC_RSHIFT:
            continue;
        default:
            break;
        }

        uint8_t index = report->keys[i];
        if (report->mods & ((1<<1)|(1<<5)))
            index += 0x40;
        if (index >= sizeof(mapping)/sizeof(mapping[0]))
            continue;

        char to_add = pgm_read_byte_near(mapping + index);
        if (to_add && prompt_offset < sizeof(prompt) - 1)
        {
            prompt[prompt_offset++] = to_add;
            prompt[prompt_offset] = '\0';
            continue;
        }

        switch (report->keys[i])
        {
        case KC_BSPC:
            if (prompt_offset > 1)
                prompt[--prompt_offset] = '\0';
            break;
        case KC_ENT:
            leave_prompt();
            run_command();
            clear_prompt_command();
            break;
            /* fall through */
        case KC_ESC:
            leave_prompt();
            clear_prompt_command();
            break;
        }
    }

    memcpy(&last_report, report, sizeof(report_keyboard_t));
}

static void send_mouse(report_mouse_t *mouse)
{
}

static void send_system(uint16_t code)
{
}

static void send_consumer(uint16_t code)
{
}

static host_driver_t prompt_driver =
{
    .keyboard_leds = keyboard_leds,
    .send_keyboard = send_keyboard,
    .send_mouse    = send_mouse,
    .send_system   = send_system,
    .send_consumer = send_consumer,
};


void enter_prompt(void)
{
    if (original_driver)
        return;
    original_driver = host_get_driver();
    host_set_driver(&prompt_driver);
}

void leave_prompt(void)
{
    if (!original_driver)
        return;
    host_set_driver(original_driver);
    original_driver = NULL;
    memset(&last_report, 0, sizeof(report_keyboard_t));
}

bool in_prompt(void)
{
    return original_driver != NULL;
}
