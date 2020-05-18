#ifndef prompt_h_INCLUDED
#define prompt_h_INCLUDED

bool prompt_key(uint16_t keycode, keyrecord_t* record);

#ifdef OLED_DRIVER_ENABLE
void write_prompt_to_oled(void);
#endif

#endif
