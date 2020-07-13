#ifndef prompt_h_INCLUDED
#define prompt_h_INCLUDED

void enter_prompt(void);
void leave_prompt(void);
bool in_prompt(void);

#ifdef OLED_DRIVER_ENABLE
void write_prompt_to_oled(void);
#endif

#endif
