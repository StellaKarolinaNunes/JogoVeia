#ifndef I18N_H
#define I18N_H

typedef enum {
    LANG_PT,
    LANG_EN,
    LANG_ES
} Language;

extern int current_language;

void init_i18n(void);
const char *_(const char *text);
void change_language(void);

#endif // I18N_H
