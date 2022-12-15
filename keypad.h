

#ifndef ECU_KEYPAD_H
#define	ECU_KEYPAD_H

/* Section : Includes */
#include "../../mcal/GPIO/hal_gpio.h"

/* Section : Macro Declarations */
#define ECU_KEYPAD_ROW  4
#define ECU_KEYPAD_COL  4
#define KEY_RELEASED    0xff

/* Section : Macro Functions Declarations */


/* Section : Data Types Declarations */


typedef struct{
    pin_config_t keypad_row_pins[ECU_KEYPAD_ROW];
    pin_config_t keypad_col_pins[ECU_KEYPAD_COL];
}keypad_t;

/* Section : Function Declarations */

Std_ReturnType keypad_initialize(const keypad_t *keypad);
Std_ReturnType keypad_get_value(const keypad_t *keypad , uint8 *value);



#endif	/* ECU_KEYPAD_H */

