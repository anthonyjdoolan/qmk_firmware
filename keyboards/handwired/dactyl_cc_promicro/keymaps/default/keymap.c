#include QMK_KEYBOARD_H


#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2

#define RAISE MO(_RAISE)
#define LOWER MO(_LOWER)

#define ONE_GRV LT(1,KC_GRAVE)
#define CTL_Z LCTL_T(KC_Z)
#define ALT_SHFT LALT(KC_LSFT)
#define ALT_MENU LALT_T(KC_MENU)
#define LG_QUOT LGUI_T(KC_QUOT)
#define CTL_ESC LCTL_T(KC_ESC)
#define CTL_SLS LCTL_T(KC_SLSH)
#define LT2_COL LT(_RAISE, KC_SCLN)

// Sticker Replacements
#define RHOME KC_LCTL
#define REND KC_LALT
#define RPGDN KC_RGUI

//Tap Dance Declarations
enum {
  TD_ESC_EQL = 0
};

//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  //Tap once for Esc, twice for Caps Lock
  [TD_ESC_EQL]  = ACTION_TAP_DANCE_DOUBLE(KC_ESC, KC_EQL)
// Other declarations would go here, separated by commas, if you have them
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT_6x6(
        KC_EQL , KC_1  , KC_2      , KC_3   , KC_4   , KC_5   ,                               KC_6  , KC_7   , KC_8   , KC_9   , KC_0   , KC_MINS ,
        KC_TAB , KC_Q  , KC_W      , KC_E   , KC_R   , KC_T   ,                               KC_Y  , KC_U   , KC_I   , KC_O   , KC_P   , KC_BSLS ,
        CTL_ESC, KC_A  , KC_S      , KC_D   , KC_F   , KC_G   ,                               KC_H  , KC_J   , KC_K   , KC_L   , KC_SCLN, KC_QUOT ,
        KC_LSPO, KC_Z  , KC_X      , KC_C   , KC_V   , KC_B   ,                               KC_N  , KC_M   , KC_COMM, KC_DOT , KC_SLSH, KC_RSPC ,
        _______, KC_GRV, TT(_LOWER), KC_LEFT, KC_RGHT, KC_BSPC,                               KC_SPC, KC_DOWN, KC_UP  , KC_LBRC, KC_RBRC, _______ ,
                                                KC_LALT, KC_DEL,REND,                 RPGDN ,KC_ENT,KC_RGUI,
                                                                RHOME,              KC_PGUP,
                                                               KC_LCTL,           TT(_RAISE)
    ),
    [_LOWER] = LAYOUT_6x6(
        RESET  ,KC_F1  ,KC_F2  ,KC_F3  ,KC_F4  ,KC_F5  ,                                       KC_F6  ,KC_F7  ,KC_F8  ,KC_F9  ,KC_F10 ,KC_F11 ,
        _______,KC_EXLM,KC_AT  ,KC_LBRC,KC_RBRC,KC_PIPE,                                       KC_UP  ,KC_7   ,KC_8   ,KC_9   ,KC_PAST,KC_F12 ,
        _______,KC_HASH,KC_DLR ,KC_LPRN,KC_RPRN,KC_GRV ,                                       KC_DOWN,KC_4   ,KC_5   ,KC_6   ,KC_PPLS,_______,
        _______,KC_PERC,KC_CIRC,KC_LBRC,KC_RBRC,KC_TILD,                                       KC_AMPR,KC_1   ,KC_2   ,KC_3   ,KC_ENT ,KC_PEQL,
        _______,_______,_______,_______,_______,_______,                                       KC_DOT ,_______,_______,KC_DOT ,KC_ENT ,KC_ENT ,
                                                _______,_______, KC_END,       KC_PGDN,_______,_______,
                                                                 KC_HOME,      KC_PGUP,
                                                                _______,       _______
    ),
    [_RAISE] = LAYOUT_6x6(
        _______,_______,_______,_______,_______,_______,                                       _______,_______,_______,_______,_______,_______,
        _______,_______,_______,KC_MS_U,_______,_______,                                       _______,_______,_______,_______,_______,_______,
        _______,_______,KC_MS_L,KC_MS_D,KC_MS_R,_______,                                       _______,_______,_______,_______,_______,KC_MPLY,
        _______,_______,_______,_______,_______,_______,                                       _______,_______,KC_MPRV,KC_MNXT,_______,_______,
        _______,_______,_______,KC_BTN1,KC_BTN2,_______,                                       KC_WBAK,KC_VOLU,KC_VOLD,KC_MUTE,_______,_______,
                                                _______,_______,_______,       _______,_______,_______,
                                                                _______,       _______,
                                                                _______,       _______
    )
};
