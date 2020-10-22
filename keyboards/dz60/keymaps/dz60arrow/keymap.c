#include "keymap.h"

static bool RUNFLAG = true;
static bool SFLAG = false;
static uint16_t RUNDELAY;
static uint8_t KFLAG[6] = { 1 };

uint8_t GenerateMacro(uint8_t KeyID, uint8_t mod, uint8_t StateCheck){
	if(StateCheck){
		if(mod == 0){
			register_code16(KeyID);
			unregister_code16(KeyID);
		}
		if(mod == 1){
			register_code16(KC_LALT);
			register_code16(KeyID);
			unregister_code16(KeyID);
			unregister_code16(KC_LALT);
		}
		if(mod == 2){
			register_code16(KC_LGUI);
			register_code16(KeyID);
			unregister_code16(KeyID);
			unregister_code16(KC_LGUI);
		}
		return 0;
	}
	return 1;
}

void STEXTHandler(uint16_t key){
	static int CUCount = 0;
	static int CLCount = 0;
	static bool CapState = true;

	//if(CUCount < 3 || CLCount < 3){
		if(CapState){
			if(key == (KC_A || KC_C || KC_E || KC_F || KC_N || KC_Q || KC_R || KC_S || KC_U || KC_V || KC_Y || KC_X || KC_Z)){
				CLCount = 0;
				tap_code16(KC_CAPS);
				CapState = !CapState;
			}
			if(key == (KC_B || KC_D || KC_G || KC_H || KC_I || KC_J || KC_K || KC_L || KC_M || KC_O || KC_P || KC_T || KC_W)){
				CUCount++;
			}
		}
		else{
			if(key == (KC_B || KC_D || KC_G || KC_H || KC_I || KC_J || KC_K || KC_L || KC_M || KC_O || KC_P || KC_T || KC_W)){
				CUCount = 0;
				tap_code16(KC_CAPS);
				CapState = !CapState;
			}
			if(key == (KC_A || KC_C || KC_E || KC_F || KC_N || KC_Q || KC_R || KC_S || KC_U || KC_V || KC_Y || KC_X || KC_Z)){
				CLCount++;
			}
		}
	//}
	//else{
	//	CLCount = 0;
	//	CUCount = 0;
	//	tap_code16(KC_CAPS);
	//	CapState = !CapState;
	//}
}

bool process_record_user(uint16_t keycode, keyrecord_t *record){
	if(SFLAG && record->event.pressed && keycode != KC_SPC){
		//STEXTHandler(keycode);
		tap_code16(KC_CAPS);
	}

	switch(keycode){
		case _01_MACRO:
			KFLAG[0] = GenerateMacro(KC_F7, 0, KFLAG[0]);
			break;
		case _02_MACRO:
			KFLAG[1] = GenerateMacro(KC_L, 2, KFLAG[1]);
			break;
		case _03_MACRO:
			KFLAG[2] = GenerateMacro(KC_LEFT, 1, KFLAG[2]);
			break;
		case _04_MACRO:
			KFLAG[3] = GenerateMacro(KC_UP, 1, KFLAG[3]);
			break;
		case _05_MACRO:
			KFLAG[4] = GenerateMacro(KC_DOWN, 1, KFLAG[4]);
			break;
		case _06_MACRO:
			KFLAG[5] = GenerateMacro(KC_RGHT, 1, KFLAG[5]);
			break;
		case STEXT:
			if(record->event.pressed){
				SFLAG = !SFLAG;
			}
			break;
	}
	return true;
}

uint32_t layer_state_set_user(uint32_t state){
	switch (biton32(state)){
    case _03_SPECIAL:
			rgblight_sethsv_noeeprom(MODIFIER_COLOR); //#A02C35
      break;
		case _02_MODIFIER:
			rgblight_sethsv_noeeprom(MODIFIER_COLOR); //#FC4E36
			break;
		case _01_BASE:
			rgblight_sethsv_noeeprom(HSV_ORANGE);//BASE_COLOR); //#A02C35
			break;
    default:
			rgblight_sethsv_noeeprom(HSV_ORANGE);//BASE_COLOR); //#A02C35
	}
	return state;
}

void matrix_init_user(void){
	RUNDELAY = timer_read();
}

void matrix_scan_user(void){
	if (RUNFLAG && timer_elapsed(RUNDELAY) > INIT_DELAY){
		RUNFLAG = false;

		rgblight_sethsv_noeeprom(HSV_ORANGE);//BASE_COLOR);
		rgblight_mode_noeeprom(1);
		rgblight_enable_noeeprom();
	}
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[_01_BASE] = LAYOUT_dz60arrow(
		KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_TRNS, KC_BSPC, 
		KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS, 
		_01_MACRO, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT, 
		KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_RSFT, KC_UP, KC_SLSH, 
		KC_LCTL, KC_LGUI, KC_LALT, KC_SPC, _02_MACRO, MO(1), KC_LEFT, KC_DOWN, KC_RGHT),

	[_02_MODIFIER] = LAYOUT_dz60arrow(
		KC_GRV, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_TRNS, KC_DEL, 
		RESET, STEXT  , KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_KP_1, KC_KP_2, KC_KP_3, KC_PGUP, KC_VOLD, KC_VOLU, KC_TRNS, 
		KC_CAPS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_KP_4, KC_KP_5, KC_KP_6, KC_PGDN, KC_HOME, KC_END, 
		TO(2)  , KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_KP_7, KC_KP_8, KC_KP_9, KC_KP_0, _04_MACRO, KC_INS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, _03_MACRO, _05_MACRO, _06_MACRO),

  [_03_SPECIAL] = LAYOUT_dz60arrow(
		TO(0)  , KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
    KC_TRNS, KC_TRNS, KC_UP,   KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_LEFT, KC_DOWN, KC_RIGHT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_X,    KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_A,    KC_TRNS, KC_TRNS, KC_Z,     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
};
