TAP_DANCE_ENABLE = yes

TEST_CODE = keyboards/ergodox_ez/keymaps/eraserhd/test.c

%: 
	clang -o /tmp/test.out $(TEST_CODE) && /tmp/test.out
