
#include "application.h"

#define  EEPROM_STATUS_LOCATION 0x20
#define  EEPROM_PASSWORD_LOCATION1 0x21
#define  EEPROM_PASSWORD_LOCATION2 0x22
#define  EEPROM_PASSWORD_LOCATION3 0x23
#define  EEPROM_PASSWORD_LOCATION4 0x24
#define MAX_TRIES 3

char arr[4];

int main() {
   Std_ReturnType ret = E_NOT_OK;
    uint8 value=KEY_RELEASED;
	uint8 flag=0,i;
	uint8 tries=MAX_TRIES;
    uint8 temp_data[5];
   
   chr_lcd_8bit_t lcd_user = {
      .lcd_en.direction = GPIO_DIRECTION_OUTPUT ,
      .lcd_en.logic = GPIO_LOW , 
      .lcd_en.port = PORTB_INDEX , 
      .lcd_en.pin = GPIO_PIN0,
      
      .lcd_rs.direction = GPIO_DIRECTION_OUTPUT , 
      .lcd_rs.logic = GPIO_LOW , 
      .lcd_rs.port = PORTB_INDEX , 
      .lcd_rs.pin = GPIO_PIN1,
      
      .lcd_data[0].direction = GPIO_DIRECTION_OUTPUT , .lcd_data[0].logic = GPIO_LOW , .lcd_data[0].port = PORTA_INDEX , .lcd_data[0].pin = GPIO_PIN0,
      .lcd_data[1].direction = GPIO_DIRECTION_OUTPUT , .lcd_data[1].logic = GPIO_LOW , .lcd_data[1].port = PORTA_INDEX , .lcd_data[1].pin = GPIO_PIN1,
      .lcd_data[2].direction = GPIO_DIRECTION_OUTPUT , .lcd_data[2].logic = GPIO_LOW , .lcd_data[2].port = PORTA_INDEX , .lcd_data[2].pin = GPIO_PIN2,
      .lcd_data[3].direction = GPIO_DIRECTION_OUTPUT , .lcd_data[3].logic = GPIO_LOW , .lcd_data[3].port = PORTA_INDEX , .lcd_data[3].pin = GPIO_PIN3,
      .lcd_data[4].direction = GPIO_DIRECTION_OUTPUT , .lcd_data[4].logic = GPIO_LOW , .lcd_data[4].port = PORTC_INDEX , .lcd_data[4].pin = GPIO_PIN7,
      .lcd_data[5].direction = GPIO_DIRECTION_OUTPUT , .lcd_data[5].logic = GPIO_LOW , .lcd_data[5].port = PORTA_INDEX , .lcd_data[5].pin = GPIO_PIN5,
      .lcd_data[6].direction = GPIO_DIRECTION_OUTPUT , .lcd_data[6].logic = GPIO_LOW , .lcd_data[6].port = PORTB_INDEX , .lcd_data[6].pin = GPIO_PIN2,
      .lcd_data[7].direction = GPIO_DIRECTION_OUTPUT , .lcd_data[7].logic = GPIO_LOW , .lcd_data[7].port = PORTB_INDEX , .lcd_data[7].pin = GPIO_PIN3,
    };
   keypad_t keypad_user = {
    .keypad_row_pins[0].direction=GPIO_DIRECTION_OUTPUT,
    .keypad_row_pins[0].logic=GPIO_LOW,
    .keypad_row_pins[0].port=PORTD_INDEX,
    .keypad_row_pins[0].pin = GPIO_PIN0,
    .keypad_row_pins[1].direction=GPIO_DIRECTION_OUTPUT,
    .keypad_row_pins[1].logic=GPIO_LOW,
    .keypad_row_pins[1].port=PORTD_INDEX,
    .keypad_row_pins[1].pin = GPIO_PIN1,
    .keypad_row_pins[2].direction=GPIO_DIRECTION_OUTPUT,
    .keypad_row_pins[2].logic=GPIO_LOW,
    .keypad_row_pins[2].port=PORTD_INDEX,
    .keypad_row_pins[2].pin = GPIO_PIN2,
    .keypad_row_pins[3].direction=GPIO_DIRECTION_OUTPUT,
    .keypad_row_pins[3].logic=GPIO_LOW,
    .keypad_row_pins[3].port=PORTD_INDEX,
    .keypad_row_pins[3].pin = GPIO_PIN3,

    .keypad_col_pins[0].direction = GPIO_DIRECTION_INPUT,
    .keypad_col_pins[0].logic=GPIO_LOW,
    .keypad_col_pins[0].port=PORTD_INDEX,
    .keypad_col_pins[0].pin = GPIO_PIN4,
    .keypad_col_pins[1].direction = GPIO_DIRECTION_INPUT,
    .keypad_col_pins[1].logic=GPIO_LOW,
    .keypad_col_pins[1].port=PORTD_INDEX,
    .keypad_col_pins[1].pin = GPIO_PIN5,
    .keypad_col_pins[2].direction = GPIO_DIRECTION_INPUT,
    .keypad_col_pins[2].logic=GPIO_LOW,
    .keypad_col_pins[2].port=PORTD_INDEX,
    .keypad_col_pins[2].pin = GPIO_PIN6,
    .keypad_col_pins[3].direction = GPIO_DIRECTION_INPUT,
    .keypad_col_pins[3].logic=GPIO_LOW,
    .keypad_col_pins[3].port=PORTD_INDEX,
    .keypad_col_pins[3].pin = GPIO_PIN7,
    };
   
    lcd_8bit_initialize(&lcd_user);
    keypad_initialize(&keypad_user);
    
    ret = Data_EEPROM_ReadByte(EEPROM_STATUS_LOCATION , &temp_data[0]);
    if (temp_data[0]==KEY_RELEASED){
        ret = lcd_8bit_send_string(&lcd_user , "set pass:");
		for(i=0;i<=3;i++){
			do {
                ret = keypad_get_value(&keypad_user , &value);
			}while(value==KEY_RELEASED);
            ret = lcd_8bit_send_char_data(&lcd_user , value);
			__delay_ms(500);
            ret = lcd_8bit_send_char_data_pos(&lcd_user ,1 , 10+i, '*');
			__delay_ms(500);
            ret = Data_EEPROM_WriteByte(EEPROM_PASSWORD_LOCATION1+i,value);
		}
        ret = Data_EEPROM_WriteByte(EEPROM_STATUS_LOCATION , 0x00);
	}				
    while(flag==0){
		arr[0]=KEY_RELEASED;
        arr[1]=KEY_RELEASED;
        arr[2]=KEY_RELEASED;
        arr[3]=KEY_RELEASED;
        ret = lcd_8bit_send_command(&lcd_user , LCD_CLEAR);
        ret = lcd_8bit_send_string(&lcd_user , "check pass:");
		for(i=0;i<=3;i++){
			do{
                ret = keypad_get_value(&keypad_user , &arr[i]);
			}while (arr[i]==KEY_RELEASED);
            ret = lcd_8bit_send_char_data(&lcd_user , arr[i]);
			__delay_ms(500);
            ret = lcd_8bit_send_char_data_pos(&lcd_user ,1 , 12+i, '*');
			__delay_ms(500);
		}		
		ret = Data_EEPROM_ReadByte(EEPROM_PASSWORD_LOCATION1 , &temp_data[1]);
        ret = Data_EEPROM_ReadByte(EEPROM_PASSWORD_LOCATION2 , &temp_data[2]);
        ret = Data_EEPROM_ReadByte(EEPROM_PASSWORD_LOCATION3 , &temp_data[3]);
        ret = Data_EEPROM_ReadByte(EEPROM_PASSWORD_LOCATION4 , &temp_data[4]);
        if(temp_data[1]==arr[0] &&  temp_data[2]==arr[1] && temp_data[3]==arr[2] && temp_data[4]==arr[3]){
            ret = lcd_8bit_send_command(&lcd_user , LCD_CLEAR);
            ret = lcd_8bit_send_string(&lcd_user , "right password");
            ret = lcd_8bit_send_char_str_pos(&lcd_user , 2 ,1 ,"safe opened" );
            flag=1;
        }	
        else{
            tries--;
            if (tries>0){
                ret = lcd_8bit_send_command(&lcd_user , LCD_CLEAR);
                ret = lcd_8bit_send_string(&lcd_user , "wrong password");
                __delay_ms(1000);
                ret = lcd_8bit_send_command(&lcd_user , LCD_CLEAR);
                ret = lcd_8bit_send_string(&lcd_user , "tries left:");
                ret = lcd_8bit_send_char_data(&lcd_user , tries+48);
                __delay_ms(1000);
            }
            else{
                ret = lcd_8bit_send_command(&lcd_user , LCD_CLEAR);
                ret = lcd_8bit_send_string(&lcd_user , "wrong password");
                ret = lcd_8bit_send_char_str_pos(&lcd_user , 2 ,1 ,"safe closed" );
                flag=1;
            }
        }
	}

//   while(1){
//       
//   }

    return (EXIT_SUCCESS);
}
