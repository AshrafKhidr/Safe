#include "ecu_keypad.h"



static const uint8 button_values[ECU_KEYPAD_ROW][ECU_KEYPAD_COL] = {
    {'7' , '8' , '9' , '/' },
    {'4' , '5' , '6' , '*' },
    {'1' , '2' , '3' , '-' },
    {'A' , '0' , '=' , '+' }
};

Std_ReturnType keypad_initialize(const keypad_t *keypad){
    Std_ReturnType ret = E_OK;
    uint8 rows_counter = INIT,cols_counter = INIT;
    if(NULL == keypad){
        ret = E_NOT_OK;
    }
    else{
        for(rows_counter = INIT ; rows_counter < ECU_KEYPAD_ROW ; rows_counter++){
            ret = gpio_pin_direction_initialize(&(keypad->keypad_row_pins[rows_counter]));
        }
        for(cols_counter = INIT ; cols_counter < ECU_KEYPAD_COL ; cols_counter++){
            ret = gpio_pin_direction_initialize(&(keypad->keypad_col_pins[cols_counter]));
        }
        
        
    }
    return ret;
}
Std_ReturnType keypad_get_value(const keypad_t *keypad , uint8 *value){
    Std_ReturnType ret = E_OK;
    uint8 rows_counter = 0,cols_counter = 0,counter=0;
    logic_t col_logic = 0;
    *value = KEY_RELEASED;
    if((NULL == keypad) || (NULL == value)){
        ret = E_NOT_OK;
    }
    else{
        for(rows_counter =0 ; rows_counter < ECU_KEYPAD_ROW ; rows_counter++){
            for(counter = 0 ; counter < ECU_KEYPAD_ROW ; counter++){
                ret = gpio_pin_write_logic(&(keypad->keypad_row_pins[counter]) , GPIO_LOW);
            }
            ret = gpio_pin_write_logic(&(keypad->keypad_row_pins[rows_counter]) , GPIO_HIGH);
            for(cols_counter = 0 ; cols_counter < ECU_KEYPAD_COL ; cols_counter++){
            ret = gpio_pin_read_logic(&(keypad->keypad_col_pins[cols_counter]) , &col_logic);
            if(col_logic == GPIO_HIGH){
                *value = button_values[rows_counter][cols_counter];
            }
        }
            __delay_ms(50);
        }
    }
    return ret;
}

