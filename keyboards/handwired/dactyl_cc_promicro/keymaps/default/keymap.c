#include QMK_KEYBOARD_H

void maybe_activate_alt_tab(void);
void maybe_activate_alt_grv(void);

#define _QWERTY  0
#define _LOWER   1
#define _RAISE   2
#define _SPECIAL 3
#define _NUM     4
#define _NAV     5
#define _FUNCTION 6


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
#define QWERTY TO(_QWERTY)

// ALIASES
#define SCRL_UP KC_MS_WH_UP
#define SCRL_DN KC_MS_WH_DOWN
#define SCRL_LT KC_MS_WH_LEFT
#define SCRL_RT KC_MS_WH_RIGHT

// SETTINGS
#define MOUSEKEY_WHEEL_INTERVAL 50

// Initialize variable holding the binary
// representation of active modifiers.
uint8_t mod_state;

//Tap Dance Declarations
enum {
  TD_ESC_EQL = 0,
  NUM
};

//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_ESC_EQL]  = ACTION_TAP_DANCE_DOUBLE(KC_ESC, KC_EQL),
  [NUM]  = ACTION_TAP_DANCE_LAYER_MOVE(KC_F7, _NUM)
};

bool is_alt_tab_active = false;    // ADD this near the begining of keymap.c
uint16_t alt_tab_timer = 0;        // we will be using them soon.
bool is_alt_grv_active = false;    // ADD this near the begining of keymap.c
uint16_t alt_grv_timer = 0;        // we will be using them soon.

enum custom_keycodes {             // Make sure have the awesome keycode ready
  ALT_TAB = SAFE_RANGE,
  SHA_TAB,
  ALT_GRV,
  SHA_GRV,
};

void maybe_activate_alt_tab() {
    if (!is_alt_tab_active) {
      is_alt_tab_active = true;
      register_code(KC_LALT);
    }
    alt_tab_timer = timer_read();
}

void maybe_activate_alt_grv() {
    if (!is_alt_grv_active) {
      is_alt_grv_active = true;
      register_code(KC_LALT);
    }
    alt_grv_timer = timer_read();
}


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {               // This will do most of the grunt work with the keycodes.
    case ALT_TAB:
      if (record->event.pressed) {
        maybe_activate_alt_tab();
        register_code(KC_TAB);
      } else {
        unregister_code(KC_TAB);
      }
      break;
    case SHA_TAB:
      if (record->event.pressed) {
        maybe_activate_alt_tab();
        register_code(KC_RSFT);
	register_code(KC_TAB);
      } else {
        unregister_code(KC_RSFT);
	unregister_code(KC_TAB);
      } 
      break;      
    case ALT_GRV:
      if (record->event.pressed) {
        maybe_activate_alt_grv();
        register_code(KC_GRV);
      } else {
        unregister_code(KC_GRV);
      }
      break;
    case SHA_GRV:
      if (record->event.pressed) {
        maybe_activate_alt_grv();
        register_code(KC_RSFT);
	register_code(KC_GRV);
      } else {
        unregister_code(KC_RSFT);
	unregister_code(KC_GRV);
      } 
      break;      
  }
  return true;
}

void matrix_scan_user(void) {     // The very important timer.
  if (is_alt_tab_active) {
    if (timer_elapsed(alt_tab_timer) > 750) {
      unregister_code(KC_LALT);
      is_alt_tab_active = false;
    }
  }
  if (is_alt_grv_active) {
    if (timer_elapsed(alt_grv_timer) > 750) {
      unregister_code(KC_LALT);
      is_alt_grv_active = false;
    }
  }
}


enum combo_events {
  ER_PRN,
  UI_PRN,
  DF_CBR,
  JK_CBR,
  CV_BRC,
  MCOM_BRC,
};

const uint16_t PROGMEM E_R_COMBO[] = {KC_E, KC_R, COMBO_END};
const uint16_t PROGMEM U_I_COMBO[] = {KC_U, KC_I, COMBO_END};
const uint16_t PROGMEM D_F_COMBO[] = {KC_D, KC_F, COMBO_END};
const uint16_t PROGMEM J_K_COMBO[] = {KC_J, KC_K, COMBO_END};
const uint16_t PROGMEM C_V_COMBO[] = {KC_C, KC_V, COMBO_END};
const uint16_t PROGMEM M_COM_COMBO[] = {KC_M, KC_COMM, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
  [ER_PRN] = COMBO_ACTION(E_R_COMBO),
  [UI_PRN] = COMBO_ACTION(U_I_COMBO),
  [DF_CBR] = COMBO_ACTION(D_F_COMBO),
  [JK_CBR] = COMBO_ACTION(J_K_COMBO),
  [CV_BRC] = COMBO_ACTION(C_V_COMBO),
  [MCOM_BRC] = COMBO_ACTION(M_COM_COMBO),
};

void process_combo_event(uint8_t combo_index, bool pressed) {
    mod_state = get_mods();
    switch(combo_index) {
        case ER_PRN:
          if (pressed) {
            tap_code16(KC_LPRN);  
          }
          break;

        case UI_PRN:
          if (pressed) {
            tap_code16(KC_RPRN);  
          }
          break;

        case DF_CBR:
          if (pressed) {
            tap_code16(KC_LCBR);  
          }
          break;

        case JK_CBR:
          if (pressed) {
            tap_code16(KC_RCBR);  
          }
          break;

        case CV_BRC:
          if (pressed) {
            tap_code16(KC_LBRC);  
          }
          break;

        case MCOM_BRC:
          if (pressed) {
            tap_code16(KC_RBRC);  
          }
          break;
    }
}

/*
 * Per key tapping term settings
 */
//uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
//    switch (keycode) {
//        case HOME_I:
//            // My ring finger tends to linger on the key 
//            // This tapping term allows me to type "ion" effortlessly.
//            return TAPPING_TERM + 200;
//        case HOME_O:
//            return TAPPING_TERM + 10;
//        case SYM_ENT:
//            // Very low tapping term to make sure I don't hit Enter accidentally.
//            return TAPPING_TERM - 65;
//        // These next mod taps are used very frequently during typing.
//        // As such, the lower the tapping term, the faster the typing.
//        case HOME_S:
//            return TAPPING_TERM - 28;
//        case HOME_E:
//            return TAPPING_TERM - 26;
//        case HOME_D:
//            return TAPPING_TERM - 16;
//        case HOME_H:
//            return TAPPING_TERM - 16;
//        default:
//            return TAPPING_TERM;
//    }
//}

// Sticker Replacements
#define RHOME LGUI_T(KC_HOME)
#define REND  LALT_T(KC_END)
#define RPGDN RGUI_T(KC_PGDN)
#define RPGUP RALT_T(KC_PGUP)
#define LDEL  LCTL_T(KC_ESC)
#define RRALT ALT_TAB
#define RLCTL SHA_TAB 
#define BSPC  TT(_RAISE)
#define RGRV  SHA_GRV
#define RRBRC ALT_GRV
#define RBSLS KC_ENT

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT_6x6(
           KC_EQL , KC_1  , KC_2      , KC_3   , KC_4   , KC_5 ,                        KC_6  , KC_7   , KC_8   , KC_9   , KC_0   , KC_MINS ,
           KC_TAB , KC_Q  , KC_W      , KC_E   , KC_R   , KC_T ,                        KC_Y  , KC_U   , KC_I   , KC_O   , KC_P   , RBSLS   ,
           CTL_ESC, KC_A  , KC_S      , KC_D   , KC_F   , KC_G ,                        KC_H  , KC_J   , KC_K   , KC_L   , KC_SCLN, KC_QUOT ,
   LSFT_T(KC_CAPS), KC_Z  , KC_X      , KC_C   , KC_V   , KC_B ,                        KC_N  , KC_M   , KC_COMM, KC_DOT , KC_SLSH, RSFT_T(KC_ENT),
          _______, RGRV  ,TT(_SPECIAL), KC_LEFT, KC_RGHT, BSPC ,                        KC_SPC, KC_DOWN, KC_UP  , KC_LBRC, RRBRC  , _______ ,
                                                    KC_LALT, LDEL, REND,       RPGDN,KC_ENT,TG(_NAV),
					                          RHOME,       RPGUP,
                                                                  RLCTL,       RRALT
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
        _______,KC_GRV ,KC_TILD,KC_BSLS,KC_PIPE,KC_LPRN,                                       KC_RPRN,KC_7   ,KC_8   ,KC_9   ,KC_MINS,_______,
        _______,KC_EXLM,KC_AT  ,KC_HASH,KC_DLR ,KC_LCBR,                                       KC_RCBR,KC_4   ,KC_5   ,KC_6   ,KC_PLUS,_______,
        _______,KC_PERC,KC_CIRC,KC_AMPR,KC_ASTR,KC_LBRC,                                       KC_RBRC,KC_1   ,KC_2   ,KC_3   ,KC_ENT ,_______,
        _______,_______,_______,KC_QUOT,KC_DQT ,_______,                                       KC_UNDS,KC_BSPC,KC_0   ,KC_EQL ,_______,_______,
                                                _______,_______,_______,       _______,_______,_______,
                                                                _______,       _______,
                                                                _______,       _______
    ),
    [_SPECIAL] = LAYOUT_6x6(
        RESET  ,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,                                      XXXXXXX,TO(_NUM),XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,
        XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,                                       XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,
        QWERTY ,XXXXXXX,XXXXXXX,XXXXXXX,TO(_FUNCTION),XXXXXXX,                                 KC_HELP,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,
        KC_CAPS,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,                                       XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,
        XXXXXXX,XXXXXXX,XXXXXXX,_______,_______,XXXXXXX,                                       KC_UNDS,_______,_______,XXXXXXX,XXXXXXX,XXXXXXX,
                                                XXXXXXX,XXXXXXX,XXXXXXX,       XXXXXXX,KC_DLR ,XXXXXXX,
                                                                XXXXXXX,       XXXXXXX,
                                                                KC_MINS,       KC_PLUS
    ),
    [_NUM] = LAYOUT_6x6(
        QWERTY ,QWERTY ,QWERTY ,QWERTY ,QWERTY ,QWERTY ,                                       XXXXXXX,XXXXXXX,KC_EQL ,KC_SLSH,KC_ASTR,XXXXXXX,
        QWERTY ,QWERTY ,QWERTY ,QWERTY ,QWERTY ,QWERTY ,                                       XXXXXXX,KC_7   ,KC_8   ,KC_9   ,KC_MINS,XXXXXXX,
        QWERTY ,QWERTY ,QWERTY ,QWERTY ,QWERTY ,QWERTY ,                                       XXXXXXX,KC_4   ,KC_5   ,KC_6   ,KC_PPLS,XXXXXXX,
        QWERTY ,QWERTY ,QWERTY ,QWERTY ,QWERTY ,QWERTY ,                                       XXXXXXX,KC_1   ,KC_2   ,KC_3   ,KC_COMM,XXXXXXX,
        QWERTY ,QWERTY ,QWERTY ,_______,_______,QWERTY ,                                       KC_0   ,_______,_______,KC_DOT ,KC_ENT ,XXXXXXX,
                                                QWERTY ,QWERTY ,QWERTY ,       QWERTY ,QWERTY ,QWERTY ,
                                                                QWERTY ,       QWERTY ,
                                                                QWERTY ,       QWERTY  
    ),
    [_NAV] = LAYOUT_6x6(
        QWERTY ,QWERTY ,QWERTY ,QWERTY ,QWERTY ,QWERTY ,                                       QWERTY ,QWERTY ,QWERTY ,QWERTY ,QWERTY ,QWERTY ,
        QWERTY ,QWERTY ,KC_BTN1,KC_MS_U,KC_BTN2,QWERTY ,                                       QWERTY ,QWERTY ,QWERTY ,QWERTY ,QWERTY ,QWERTY ,
        QWERTY ,QWERTY ,KC_MS_L,KC_MS_D,KC_MS_R,QWERTY ,                                       KC_LEFT,KC_DOWN,KC_UP  ,KC_RGHT,QWERTY ,QWERTY ,
        QWERTY ,QWERTY ,SCRL_LT,SCRL_DN,SCRL_UP,SCRL_RT,                                       KC_HOME,KC_PGDN,KC_PGUP,KC_END ,QWERTY ,QWERTY ,
        QWERTY ,QWERTY ,QWERTY ,_______,_______,QWERTY ,                                       QWERTY ,_______,_______,QWERTY ,QWERTY ,QWERTY ,
                                                QWERTY ,QWERTY ,QWERTY ,       QWERTY ,QWERTY ,QWERTY ,
                                                                QWERTY ,       QWERTY ,
                                                                QWERTY ,       QWERTY 
    ),
    [_FUNCTION] = LAYOUT_6x6(
        QWERTY ,QWERTY ,QWERTY ,QWERTY ,QWERTY ,QWERTY ,                                       QWERTY ,KC_F10 ,KC_F11 ,KC_F12 ,QWERTY ,QWERTY ,
        QWERTY ,QWERTY ,QWERTY ,QWERTY ,QWERTY ,QWERTY ,                                       QWERTY ,KC_F7  ,KC_F8  ,KC_F9  ,QWERTY ,QWERTY ,
        QWERTY ,QWERTY ,QWERTY ,QWERTY ,QWERTY ,QWERTY ,                                       QWERTY ,KC_F4  ,KC_F5  ,KC_F6  ,QWERTY ,QWERTY ,
        QWERTY ,QWERTY ,QWERTY ,QWERTY ,QWERTY ,QWERTY ,                                       QWERTY ,KC_F1  ,KC_F2  ,KC_F3  ,QWERTY ,QWERTY ,
        QWERTY ,QWERTY ,QWERTY ,_______,_______,QWERTY ,                                       QWERTY ,_______,_______,QWERTY ,QWERTY ,QWERTY ,
                                                QWERTY ,QWERTY ,QWERTY ,       QWERTY ,QWERTY ,QWERTY ,
                                                                QWERTY ,       QWERTY ,
                                                                QWERTY ,       QWERTY 
    )
};
