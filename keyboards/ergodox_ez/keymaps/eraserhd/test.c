
#include <stdbool.h>
#include <stdint.h>

#include "../../../../tmk_core/common/keyboard.h"
#include "../../../../tmk_core/common/keycode.h"
#include "../../../../tmk_core/common/action.h"
#include "../../../../quantum/quantum_keycodes.h"
#include "eraserhd.h"

void _delay_ms(int ms) {
}

#include "soft_meta.h"

#include <assert.h>
#include <stdio.h>

int offset;
uint8_t codes[16];
bool registered[16];

void register_code(uint8_t keycode) {
    codes[offset] = keycode;
    registered[offset] = true;
    offset++;
}

void unregister_code(uint8_t keycode) {
    codes[offset] = keycode;
    registered[offset] = false;
    offset++;
}

#define END -1
#define PRESS -2
#define RELEASE -3

bool check(const int *test_case) {
    keyrecord_t record;
    bool process;
    int i;

    offset = 0;
    for (; *test_case != END; test_case += 2) {
        record.event.pressed = (test_case[0] == PRESS);
        process = process_record_user(test_case[1], &record);
        if (process) {
            if (record.event.pressed)
                register_code(test_case[1]);
            else
                unregister_code(test_case[1]);
        }
    }

    ++test_case;
    for (i = 0; *test_case != END; i++, test_case += 2) {
        if (i >= offset)
            return false;
        if ((test_case[0] == PRESS) != registered[i])
            return false;
        if (test_case[1] != codes[i])
            return false;
    }
    if (i != offset)
        return false;

    return true;
}

int x_meta_can_be_used_as_x[] = {
    PRESS, X_META, RELEASE, X_META, END,
    PRESS, KC_X, RELEASE, KC_X, END
};
int x_meta_can_be_used_as_meta[] = {
    PRESS, X_META, PRESS, KC_I, RELEASE, KC_I, RELEASE, X_META, END,
    PRESS, KC_ESC, RELEASE, KC_ESC, PRESS, KC_I, RELEASE, KC_I, END
};
int dot_meta_can_be_used_as_dot[] = {
    PRESS, DOT_META, RELEASE, DOT_META, END,
    PRESS, KC_DOT, RELEASE, KC_DOT, END
};
int dot_meta_can_be_used_as_meta[] = {
    PRESS, DOT_META, PRESS, KC_Q, RELEASE, KC_Q, RELEASE, DOT_META, END,
    PRESS, KC_ESC, RELEASE, KC_ESC, PRESS, KC_Q, RELEASE, KC_Q, END
};
int can_type_meta_dot[] = {
    PRESS, X_META, PRESS, DOT_META, RELEASE, DOT_META, RELEASE, X_META, END,
    PRESS, KC_ESC, RELEASE, KC_ESC, PRESS, KC_DOT, RELEASE, KC_DOT, END
};
int can_type_meta_x[] = {
    PRESS, DOT_META, PRESS, X_META, RELEASE, X_META, RELEASE, DOT_META, END,
    PRESS, KC_ESC, RELEASE, KC_ESC, PRESS, KC_X, RELEASE, KC_X, END
};
int x_meta_can_be_typed_fastly_as_x[] = {
    PRESS, X_META, PRESS, KC_I, RELEASE, X_META, RELEASE, KC_I, END,
    PRESS, KC_X, RELEASE, KC_X, PRESS, KC_I, RELEASE, KC_I, END
};
int dot_meta_can_be_typed_fastly_as_dot[] = {
    PRESS, DOT_META, PRESS, KC_Q, RELEASE, DOT_META, RELEASE, KC_Q, END,
    PRESS, KC_DOT, RELEASE, KC_DOT, PRESS, KC_Q, RELEASE, KC_Q, END
};

int main(void) {
    assert(check(x_meta_can_be_used_as_x));
    assert(check(x_meta_can_be_used_as_meta));
    assert(check(dot_meta_can_be_used_as_dot));
    assert(check(dot_meta_can_be_used_as_meta));
    assert(check(can_type_meta_dot));
    assert(check(can_type_meta_x));
    assert(check(x_meta_can_be_typed_fastly_as_x));
    assert(check(dot_meta_can_be_typed_fastly_as_dot));
    printf("\e[1;32mAll tests passed.\e[0m\n");
}
