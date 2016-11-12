#include <AccelStepper.h>
#include <LiquidCrystal.h>
#include <EEPROMex.h>
//#include <Wire.h>
//#include <stdio.h>
#include <avr/pgmspace.h>
#include <phi_interfaces.h>
#include <phi_prompt.h>
#include <MemoryFree.h>

#define DEBUG true // flag to turn on/off debugging
#define Serial if(DEBUG)Serial


#define ELEM_CNT(x)  (sizeof(x) / sizeof(x[0]))
#define GET_VAR_NAME(varName,holder) sprintf(holder, "%s", #varName)

// Definition EEPROM
#define EEPROM_MIN_ADDR 0
#define EEPROM_MAX_ADDR 511

// Definition LCD
#define LCD_number_of_columns 16
#define LCD_number_of_rows 2
#define LCD_RS 8
#define LCD_EN 9
#define LCD_D4 4
#define LCD_D5 5
#define LCD_D6 6
#define LCD_D7 7

// Paramètres du moteur et de la vis
// adresses EEPROM : Ne pas toucher ce bloc
// pas de la vis en mm (valeur par défaut 2mm)
static const unsigned short int EEPROM_screw_pitch = EEPROM.getAddress(sizeof(float));
static float screw_pitch;
static float _default_screw_pitch  = 2.0f;
// nombre de pas par tour de rotation du moteur
static const unsigned short int EEPROM_motor_no_steps = EEPROM.getAddress(sizeof(int));
static int motor_no_steps ;
static int _default_motor_no_steps = 400;
// Vitesse maxi moteur
static const unsigned short int EEPROM_stepper_max_speed = EEPROM.getAddress(sizeof(int));
static int stepper_max_speed;
//static int _default_stepper_max_speed = 1200;
// Acceleration moteur
static const unsigned short int EEPROM_stepper_acceleration = EEPROM.getAddress(sizeof(int));
static int stepper_acceleration;
//static int _default_stepper_acceleration = 400;
// fin valeurs EEPROM
// position stepper moteur
static const unsigned short int EEPROM_stepper_last_known_position = EEPROM.getAddress(sizeof(long));
static long stepper_last_known_position;
//static long _default_stepper_last_known_position  = 0;
// position borne haute moteur
static const unsigned short int EEPROM_stepper_high_bound = EEPROM.getAddress(sizeof(long));
static long stepper_high_bound;
//static long _default_stepper_high_bound = 18000;
// position borne basse moteur
static const unsigned short int EEPROM_stepper_low_bound = EEPROM.getAddress(sizeof(long));
static long stepper_low_bound;
//static long _default_stepper_low_bound = 0;
// fin valeurs EEPROM
static const unsigned short int EEPROM_memorybank = EEPROM.getAddress(sizeof(float[26]));
static char memorybank_mapping[]={'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
static const float EMPTY_BANK=-9999;
static float memorybank[]={EMPTY_BANK,EMPTY_BANK,EMPTY_BANK,EMPTY_BANK,EMPTY_BANK,EMPTY_BANK,EMPTY_BANK,EMPTY_BANK,EMPTY_BANK,EMPTY_BANK,EMPTY_BANK,EMPTY_BANK,EMPTY_BANK,EMPTY_BANK,EMPTY_BANK,EMPTY_BANK,EMPTY_BANK,EMPTY_BANK,EMPTY_BANK,EMPTY_BANK,EMPTY_BANK,EMPTY_BANK,EMPTY_BANK,EMPTY_BANK,EMPTY_BANK,EMPTY_BANK};
static const float default_memorybank[]={EMPTY_BANK,EMPTY_BANK,EMPTY_BANK,EMPTY_BANK,EMPTY_BANK,EMPTY_BANK,EMPTY_BANK,EMPTY_BANK,EMPTY_BANK,EMPTY_BANK,EMPTY_BANK,EMPTY_BANK,EMPTY_BANK,EMPTY_BANK,EMPTY_BANK,EMPTY_BANK,EMPTY_BANK,EMPTY_BANK,EMPTY_BANK,EMPTY_BANK,EMPTY_BANK,EMPTY_BANK,EMPTY_BANK,EMPTY_BANK,EMPTY_BANK,EMPTY_BANK};
static unsigned short int mem_index=0;

// lecture des valeurs en mémoire
static void init_from_eeprom_memorybank(){
	Serial.println("Lecture memory bank");
	if(EEPROM.readBlock(EEPROM_memorybank,memorybank) > 0) {
		Serial.println("Lecture memory bank ok");
	}
	char buff[50];
	for (unsigned short int i=0;i<ELEM_CNT(memorybank);i++){
		sprintf(buff,"%c : %f",memorybank_mapping[i],memorybank[i]);
		Serial.println(buff);
	}
}

// format memory bank
static void format_memory_bank (){
	Serial.println("format memory bank");
		if(EEPROM.updateBlock(EEPROM_memorybank,default_memorybank) > 0) {
			Serial.println("format memory bank ok");
		}
		Serial.println("Lecture memory bank");
			if(EEPROM.readBlock(EEPROM_memorybank,memorybank) > 0) {
				Serial.println("Lecture memory bank ok");
			}
		char buff[50];
		for (short unsigned int i=0;i<ELEM_CNT(memorybank);i++){
			sprintf(buff,"%c : %f",memorybank_mapping[i],memorybank[i]);
			Serial.println(buff);
		}
}

// update memory bank
static void update_memory_bank (){
	Serial.println("Update memory bank");
		if(EEPROM.updateBlock(EEPROM_memorybank,memorybank) > 0) {
			Serial.println("Update memory bank ok");
		}
}


static char analog_mapping1[]={'C','Z','N','F','M','G','T'}; // Les codes qui seront nécessaires pour phi_prompt
static byte analog_pins1[]={2}; // Les entrées analogiques utilisées
static int button_resistor_values1[]={142,287,431,504,575,722,871}; // Les résistances mesurées en fonction du bouton sélectionné.
static phi_analog_keypads analog_keypad1(analog_mapping1, analog_pins1, button_resistor_values1, 1, 7);

static char analog_mapping2[]={'U','D','L','R','B','A','S','C'}; // Les codes qui seront nécessaires pour phi_prompt
static byte analog_pins2[]={3}; // Les entrées analogiques utilisées
static int button_resistor_values2[]={125,251,377,504,631,760,890}; // Les résistances mesurées en fonction du bouton sélectionné.

static phi_analog_keypads analog_keypad2(analog_mapping2, analog_pins2, button_resistor_values2, 1, 7);

static multiple_button_input * keypads[]={&analog_keypad1, &analog_keypad2, 0};

// The following sets up function keys for phi_prompt library
static char up_keys[]={"U"}; ///< All keys that act as the up key are listed here.
static char down_keys[]={"D"}; ///< All keys that act as the down key are listed here.
static char left_keys[]={"L"}; ///< All keys that act as the left key are listed here.
static char right_keys[]={"R"}; ///< All keys that act as the right key are listed here.
static char enter_keys[]={"B"}; ///< All keys that act as the enter key are listed here.
static char escape_keys[]={"A"}; ///< All keys that act as the escape key are listed here.
static char stop_keys[]={"S"};
static char zero_keys[]={"Z"};
static char change_bit_keys[]={"C"};
static char mem_down_keys[]={"M"};
static char mem_up_keys[]={"N"};
static char format_mem[]={"F"};
static char go_store_keys[]={"G"};
static char auto_split_keys[]={"T"};

static char * function_keys[]={up_keys,down_keys,left_keys,right_keys,enter_keys,escape_keys,stop_keys,zero_keys,change_bit_keys,mem_down_keys,mem_up_keys,format_mem,go_store_keys,auto_split_keys}; /// pas de bouton echap pour l'instant


// configuration du clavier analogique
static void configure_analogkeyboard(){
//	analog_keypad.set_debounce(100);
//	analog_keypad.set_dash(50);
//	analog_keypad.set_hold(500);
//	analog_keypad.set_repeat(100);
	analog_keypad1.set_debounce(100);
	analog_keypad1.set_dash(50);
	analog_keypad1.set_hold(500);
	analog_keypad1.set_repeat(100);
	analog_keypad2.set_debounce(100);
	analog_keypad2.set_dash(50);
	analog_keypad2.set_hold(500);
	analog_keypad2.set_repeat(100);
}



/*
 * LCD R/W pin to ground
 * 10K POT :
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)
*/
static LiquidCrystal lcd(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

#define PAP_Step 12
#define PAP_Direction 13

/* Moteur pas à pas sur broches */
static AccelStepper stepper(AccelStepper::DRIVER, PAP_Step, PAP_Direction);

//static void init_from_eeprom_int(int *val, int *defval, unsigned short int addr_EEPROM, char* varName){
static void init_from_eeprom_int(int *val, unsigned short int addr_EEPROM, char* varName){
	char buffer [50];
	if(isnan(*val) || *val == 0)
		{
			*val = (int)(EEPROM.readInt(addr_EEPROM));
			sprintf(buffer,"%s : %d", varName, *val);
			Serial.println(buffer);
		}

}

//static void init_from_eeprom_long(long *val, long *defval, unsigned short int addr_EEPROM, char* varName){
static void init_from_eeprom_long(long *val, unsigned short int addr_EEPROM, char* varName){
	char buffer [50];
	if(isnan(*val) || *val == 0)
		{
			*val = (long)(EEPROM.readLong(addr_EEPROM));
			sprintf(buffer,"%s : %ld", varName, *val);
			Serial.println(buffer);
		}

}

//static void init_from_eeprom_float(float *val, float *defval, unsigned short int addr_EEPROM, char* varName){
static void init_from_eeprom_float(float *val, unsigned short int addr_EEPROM, char* varName){
	char buffer [50];
	if(isnan(*val) || *val == 0)
		{
			*val = (float)(EEPROM.readFloat(addr_EEPROM));
			sprintf(buffer,"%s : %.2f", varName, (double)*val);
			Serial.println(buffer);
		}

}

// lecture des différents paramètres stockés dans l'EEPROM et mise à jour des variables liées
static void init_from_eeprom(){
	char buffer2 [50];
	if(EEPROM.updateFloat(EEPROM_screw_pitch,_default_screw_pitch))
		{
			Serial.println("EEPROM_screw_pitch modifié");
		} else {
			Serial.println("EEPROM_screw_pitch pas modifié");
		}
	GET_VAR_NAME(EEPROM_screw_pitch,buffer2);
	init_from_eeprom_float(&screw_pitch,EEPROM_screw_pitch,buffer2);

	if(EEPROM.updateInt(EEPROM_motor_no_steps,_default_motor_no_steps))
		{
			Serial.println("EEPROM_motor_no_steps modifié");
		} else {
			Serial.println("EEPROM_motor_no_steps pas modifié");
		}
	GET_VAR_NAME(EEPROM_motor_no_steps,buffer2);
	init_from_eeprom_int(&motor_no_steps,EEPROM_motor_no_steps,buffer2);

	GET_VAR_NAME(EEPROM_stepper_max_speed,buffer2);
	init_from_eeprom_int(&stepper_max_speed,EEPROM_stepper_max_speed,buffer2);

	GET_VAR_NAME(EEPROM_stepper_acceleration,buffer2);
	init_from_eeprom_int(&stepper_acceleration,EEPROM_stepper_acceleration,buffer2);

	GET_VAR_NAME(EEPROM_stepper_last_known_position,buffer2);
	init_from_eeprom_long(&stepper_last_known_position,EEPROM_stepper_last_known_position,buffer2);

	GET_VAR_NAME(EEPROM_stepper_high_bound,buffer2);
	init_from_eeprom_long(&stepper_high_bound,EEPROM_stepper_high_bound,buffer2);

	GET_VAR_NAME(EEPROM_stepper_low_bound,buffer2);
	init_from_eeprom_long(&stepper_low_bound,EEPROM_stepper_low_bound,buffer2);
}

static void update_stepper_bounds(){
	if(stepper.enabledBoundHigh()) {
		stepper_high_bound=stepper.getBoundHigh();
		EEPROM.updateLong(EEPROM_stepper_high_bound,stepper_high_bound);
	}
	if(stepper.enabledBoundLow()) {
		stepper_low_bound=stepper.getBoundLow();
		EEPROM.updateLong(EEPROM_stepper_low_bound,stepper_low_bound);
	}
}

static void init_pins(){
	// Définir les directions des PINs du LCD
	  pinMode(LCD_RS, OUTPUT);
	  pinMode(LCD_EN, OUTPUT);
	  pinMode(LCD_D4, OUTPUT);
	  pinMode(LCD_D5, OUTPUT);
	  pinMode(LCD_D6, OUTPUT);
	  pinMode(LCD_D7, OUTPUT);

	  // Définir les directions des PINS du controleur de moteur pas a pas
	  pinMode(11, OUTPUT);
	  pinMode(PAP_Step, OUTPUT);
	  pinMode(PAP_Direction, OUTPUT);
}


// configure les paramètres du stepper;
static void configure_stepper(){
	stepper.setMaxSpeed(stepper_max_speed);
	stepper.setAcceleration(stepper_acceleration);
	stepper.setCurrentPosition(stepper_last_known_position);
}

static void configure_lcd(){
	// Initialiser l'écran LCD :
	lcd.begin(LCD_number_of_columns, LCD_number_of_rows);
	lcd.display();
	lcd.clear(); // Effacer l'écran et se positionner en haut à gauche
}


// return the position in mm of the stepper
static void compute_position_in_mm(long &position_step, float &position_mm){
	position_mm = (float)(position_step * screw_pitch / motor_no_steps);
	return;
}

// return the position in step of the stepper
static void compute_position_in_step(float &position_mm, long &position_step){
	position_step = (long)(position_mm * motor_no_steps / screw_pitch);
	return;
}

//
// Clear all eeprom stored datas
//
static void format_eeprom() {
	// Mise à 0 complete
	for (int i = EEPROM_MIN_ADDR; i <= EEPROM_MAX_ADDR; i++){
		EEPROM.write(i, 0);
	}
}

// affiche la mémoire dispo sur le lcd
static void displayMemory(){
	lcd.clear();
	center_text("Free Memory");
	lcd.setCursor(7,1);
	lcd.print(freeMemory());
	return;
}


// met à jour (variable et EEPROM) la derniere position
static void update_stepper_last_known_position(){
	stepper_last_known_position = stepper.currentPosition();
	if(EEPROM.updateLong(EEPROM_stepper_last_known_position,stepper_last_known_position))
		Serial.println(stepper_last_known_position);
}

// timer d'affichage pour ne pas ralentir le reste des opérations
static unsigned long timer_display_stepper=0;
static unsigned long timer_manual_stepper_update_position=0;
static void display_stepper_position(){
	if (millis()-timer_display_stepper>200){
		lcd.setCursor(0,0);
		char buff[17];
		float float_stepper_position,float_stepper_target;
		long step_current_position, step_target_position;
		step_current_position=stepper.currentPosition();
		step_target_position=stepper.targetPosition();
		compute_position_in_mm(step_current_position,float_stepper_position);
		compute_position_in_mm(step_target_position,float_stepper_target);

		sprintf(buff,"C%+6.2f  T%+6.2f",(double)float_stepper_position,(double)float_stepper_target);
		lcd.print(buff);

		lcd.setCursor(0,1);
		char buff2[7];
		if (memorybank[mem_index]==EMPTY_BANK) {
			sprintf(buff2,"EMPTY");
		} else {
			sprintf(buff2,"%+6.2f",(double)memorybank[mem_index]);
		}
		sprintf(buff,"%c : %s",memorybank_mapping[mem_index],buff2);
		center_text(buff);
		// on tient à jour la position avec l'affichage
		if(millis()-timer_manual_stepper_update_position>300)
				{
					update_stepper_last_known_position();
					timer_manual_stepper_update_position=millis();
				}
		timer_display_stepper=millis(); // on mémorise la date du dernier affichage
	}
}



// interface de configuration nb pas moteur et ecriture du param dans l'EEPROM
//static void param_motor_no_steps(){
//	phi_prompt_struct myIntegerInput; // This struct stores information for library functions
//	myIntegerInput.ptr.i_buffer=&motor_no_steps; // Pass the address of user_input to the library. After library function call, user input will be stored in this variable. Note the use of “&”.
//	myIntegerInput.low.i=0; // Lower limit. The number wraps to 20 when decreased from 0.
//	myIntegerInput.high.i=1200; // Upper limit. The number wraps to 0 when increased from 20.
//	myIntegerInput.step.i=1; // Step size. You will get 0, 2, 4, 6, 8, etc if you set it to 2.
//	myIntegerInput.col=7; // Display the number at column 7
//	myIntegerInput.row=1; // Display the number at row 1
//	myIntegerInput.width=4; // The number occupies 4 character space.
//	myIntegerInput.option=0; // Option 0, space pad right, 1, zero pad left, 2, space pad left.
//	lcd.clear(); // Clear the lcd.
//	lcd.print("Nb pas (1-1200)"); // Prompt user for input
//	input_integer(&myIntegerInput);
//	if(EEPROM.updateInt(EEPROM_motor_no_steps,motor_no_steps))
//	{
//		//Serial.println("EEPROM_motor_no_steps modifié");
//		lcd.clear();
//		center_text("update");
//		wait_on_escape(1000);
//	}
//}
//
//// interface de configuration pitch de la vis et ecriture du param dans l'EEPROM
//static void param_screw_pitch(){
//	phi_prompt_struct myFloatInput; // This struct stores information for library functions
//	myFloatInput.ptr.f_buffer=&screw_pitch; // Pass the address of user_input to the library. After library function call, user input will be stored in this variable. Note the use of “&”.
//	myFloatInput.step.c_arr[0]=2;// digits after decimal
//	myFloatInput.step.c_arr[1]=2;// digits before decima
//	myFloatInput.col=7; // Display the number at column 7
//	myFloatInput.row=1; // Display the number at row 1
//	myFloatInput.option=0; // Option 0: only positive numbers allowed, 1: only negative numbers allowed, 2: both positive and negative numbers are allowed.
//	lcd.clear(); // Clear the lcd.
//	lcd.print("Pas vis"); // Prompt user for input
//	input_float(&myFloatInput);
//	if(EEPROM.updateFloat(EEPROM_screw_pitch,screw_pitch))
//	{
////		Serial.println("EEPROM_screw_pitch modifié");
//		lcd.clear();
//		center_text("update");
//		wait_on_escape(1000);
//	}
//}

// interface de configuration vitesse maxi moteur et ecriture du param dans l'EEPROM
static void param_stepper_max_speed(){
	phi_prompt_struct myIntegerInput; // This struct stores information for library functions
	myIntegerInput.ptr.i_buffer=&stepper_max_speed; // Pass the address of user_input to the library. After library function call, user input will be stored in this variable. Note the use of “&”.
	myIntegerInput.low.i=0; // Lower limit. The number wraps to 20 when decreased from 0.
	myIntegerInput.high.i=4800; // Upper limit. The number wraps to 0 when increased from 20.
	myIntegerInput.step.i=100; // Step size. You will get 0, 2, 4, 6, 8, etc if you set it to 2.
	myIntegerInput.col=7; // Display the number at column 7
	myIntegerInput.row=1; // Display the number at row 1
	myIntegerInput.width=4; // The number occupies 4 character space.
	myIntegerInput.option=0; // Option 0, space pad right, 1, zero pad left, 2, space pad left.
	lcd.clear(); // Clear the lcd.
	lcd.print("Vitesse (1-4800)"); // Prompt user for input
	input_integer(&myIntegerInput);
	if(EEPROM.updateInt(EEPROM_stepper_max_speed,stepper_max_speed))
	{
		lcd.clear();
		center_text("update");
		configure_stepper();
		wait_on_escape(1000);
	}
}

// interface de configuration acceleration moteur et ecriture du param dans l'EEPROM
static void param_stepper_acceleration(){
	phi_prompt_struct myIntegerInput; // This struct stores information for library functions
	myIntegerInput.ptr.i_buffer=&stepper_acceleration; // Pass the address of user_input to the library. After library function call, user input will be stored in this variable. Note the use of “&”.
	myIntegerInput.low.i=0; // Lower limit. The number wraps to 20 when decreased from 0.
	myIntegerInput.high.i=stepper_max_speed; // Upper limit. The number wraps to 0 when increased from 20.
	myIntegerInput.step.i=10; // Step size. You will get 0, 2, 4, 6, 8, etc if you set it to 2.
	myIntegerInput.col=7; // Display the number at column 7
	myIntegerInput.row=1; // Display the number at row 1
	myIntegerInput.width=4; // The number occupies 4 character space.
	myIntegerInput.option=0; // Option 0, space pad right, 1, zero pad left, 2, space pad left.
	lcd.clear(); // Clear the lcd.
	char buffer [20];
	sprintf(buffer,"Accel. (1-%d)",stepper_max_speed);
	lcd.print(buffer); // Prompt user for input
	input_integer(&myIntegerInput);
	if(EEPROM.updateInt(EEPROM_stepper_acceleration,stepper_acceleration))
	{
		lcd.clear();
		center_text("update");
		configure_stepper();
		wait_on_escape(1000);
	}
}

// interface pour formater l'eeprom
static void param_formater_eeprom(){
	if(yn_dialog("Formater EEPROM?")==1)
	{
		format_eeprom();
	}
}

// Render list option bits
//#define phi_prompt_arrow_dot B00000001      ///< List display option for using arrow/dot before a list item.
//#define phi_prompt_index_list B00000010     ///< List display option for using an index list such as 12*4 for 4 total items and 3 is highlighted.
//#define phi_prompt_current_total B00000100  ///< List display option for using a current/total index such as 2/4.
//#define phi_prompt_auto_scroll B00001000    ///< List display option for using auto scrolling items longer than the width of the list.
//#define phi_prompt_flash_cursor B00010000   ///< List display option for using flash cursor as indicator of highlighted item.
//#define phi_prompt_center_choice B00100000  ///< List display option for using centering highlighted item on screen so highlighted item is always in the middle when possible.
//#define phi_prompt_scroll_bar B01000000     ///< List display option for using a scroll bar on the right.
//#define phi_prompt_invert_text B10000000    ///< List display option for using inverted text. Only some modified version of the library uses it.
static const int global_style=B00101101;

static void create_phi_menu_from_array(phi_prompt_struct &myMenu, char** m, int width_menu){
		// Initialize the top menu
		myMenu.ptr.list=m; // Assign the list to the pointer
		myMenu.low.i=0; // Default item highlighted on the list
		myMenu.high.i=width_menu-1; // Last item of the list is size of the list - 1.
		myMenu.width=LCD_number_of_columns-((global_style&phi_prompt_arrow_dot)!=0)-((global_style&phi_prompt_scroll_bar)!=0); // Auto fit the size of the list to the screen. Length in characters of the longest list item.
		myMenu.step.c_arr[0]=LCD_number_of_rows-1; // rows to auto fit entire screen
		myMenu.step.c_arr[1]=1; // one col list
		myMenu.step.c_arr[2]=0; // y for additional feature such as an index
		myMenu.step.c_arr[3]=LCD_number_of_columns-4; // x for additional feature such as an index
		myMenu.col=0; // Display prompt at column 0
		myMenu.row=1; // Display prompt at row 1
		myMenu.option=global_style;
		myMenu.option=global_style; // This makes sure the change of menu style is updated if there is a menu style option in this level of menu.
		myMenu.width=LCD_number_of_columns-((global_style&phi_prompt_arrow_dot)!=0)-((global_style&phi_prompt_scroll_bar)!=0); // Auto fit the size of the list to the screen. Length in characters of the longest list item.


}

const char parametrage_item00[] PROGMEM = "Vitesse moteur";
const char parametrage_item01[] PROGMEM ="Accel. moteur";
const char parametrage_item02[] PROGMEM ="Memoire dispo";
const char parametrage_item03[] PROGMEM ="Format EEPROM";
const char parametrage_item04[] PROGMEM ="Retour menu";
const char* const parametrage_items[] PROGMEM = {parametrage_item00, parametrage_item01, parametrage_item02, parametrage_item03, parametrage_item04};

//PROGMEM const prog_char parametrage_item00[]="Vitesse moteur";
//PROGMEM const prog_char parametrage_item01[]="Accel. moteur";
//PROGMEM const prog_char parametrage_item02[]="Memoire dispo";
//PROGMEM const prog_char parametrage_item03[]="Format EEPROM";
//PROGMEM const prog_char parametrage_item04[]="Retour menu";
//PROGMEM const char* parametrage_items[] = {parametrage_item00, parametrage_item01, parametrage_item02, parametrage_item03, parametrage_item04};

static void parametrage_menu(){
	int menu_pointer_1=0;
	phi_prompt_struct myMenu; // This structure stores the sub menu.

	create_phi_menu_from_array(myMenu, (char**)&parametrage_items, ELEM_CNT(parametrage_items));

	while(1)
	{
		lcd.clear();  // Refresh menu if a button has been pushed
		center_text("Param menu");

		select_list(&myMenu);
		menu_pointer_1=myMenu.low.i;
		switch (menu_pointer_1)
		{
		case 0:
			param_stepper_max_speed();
			break;
		case 1:
			param_stepper_acceleration();
			break;
		case 2:
			displayMemory();
			wait_on_escape(3000);
			break;
		case 3:
			param_formater_eeprom();
			break;
		case 4:
			return;
			break;
		default:
			break;
		}
	}
}

static void mystop(){
	int targetOrig = stepper.targetPosition();
	int distanceRestanteOrig = abs(targetOrig-stepper.currentPosition());
	stepper.setAcceleration(abs(stepper.speed()*2));
	stepper.stop();
	if(abs(stepper.targetPosition()-stepper.currentPosition()) > distanceRestanteOrig) {/// stop nous fait aller trop loin
		stepper.moveTo(targetOrig);
	}
	// on cherche à s'arrêter sur des pas pairs (ma config half step)
	if (stepper.targetPosition()%2==1){
		int pas_sup = stepper.targetPosition()/abs(stepper.targetPosition()); // +1 si positif -1 sinon
		stepper.moveTo(stepper.targetPosition()+pas_sup);
	}
	stepper.setAcceleration(stepper_acceleration);
}

//Defini une nouvelle position en mettant à jour les bornes et la position du stepper en EEPROM
static void setNewCurrentPosition(long newPos){
	stepper.setCurrentPosition(newPos);
	update_stepper_bounds();
	update_stepper_last_known_position();
}


// deplace le stepper tant que l'on tient un bouton enfonce
static void moveWhileButtonheld(int button){
	int old_button_status=0,button_status=0,direction=0;
	switch(button){
	case phi_prompt_up:
		direction=1;
		break;
	case phi_prompt_down:
		direction=-1;
		break;
	default:
		break;
	}
	button_status=analog_keypad2.get_status();
	old_button_status=button_status;
	while (button_status==buttons_held || button_status==buttons_down || button_status==buttons_pressed ){
		if( (old_button_status==buttons_down ||	old_button_status==buttons_pressed) && button_status==buttons_held ) // si on detecte un changement bouton vers l'état pressé
		{
			direction=direction*1200; // on accélère parce qu'on est pressé :)
		}
		old_button_status = button_status;
		analog_keypad2.getKey(); // force le refresh du status
		button_status=analog_keypad2.get_status();
		stepper.move(direction);
		stepper.run();
		display_stepper_position();
	}
	mystop(); // stop un peu plus violent que celui par défaut dans la librairie AccelStepper
	while (stepper.currentPosition()!=stepper.targetPosition()) {
		stepper.run();
		display_stepper_position();
	}
	delay(201); // on attend pour être sûr d'avoir un affichage rafraichi (voir delai fonction display)
	display_stepper_position();
	update_stepper_last_known_position();
	configure_stepper(); // necessaire pour un redémarrage propre
}

// permet de générer des positions en mémoire pour faire des passes incrémentales
// ne fonctionne que si la position courante est positive
static void auto_split() {
	float finition=0;
	float float_stepper_position;
	long step_current_position;
	step_current_position=stepper.currentPosition();
	compute_position_in_mm(step_current_position,float_stepper_position);

	if (float_stepper_position>0.2) {
			finition=0.2;
		} // sinon ca ne vaut pas le coup

	if (mem_index>0&&finition>0){
		for(short int i=mem_index; i>=0; i--) {
			if (i==mem_index) {
				memorybank[i]=float_stepper_position;
			}else {
				if (i==mem_index-1) {
					memorybank[i]=float_stepper_position-finition; //passe de finition
				} else {
					if (i==0) {
						memorybank[i]=0;
					} else {
						memorybank[i]=i*(float_stepper_position/(mem_index-1));
					}
				}
			}
		}
	}
}

static unsigned long timer_read_key=0;

// mode de pilotage complètement manuel du moteur avec affichage de la position.
static void manual_stepper(){
	int key;
	boolean action=0;
	float float_stepper_position;
	long step_current_position;

	stepper.setSpeed(0); // coupe toute tentative de repartir tout seul :)
	stepper.setAcceleration(0); // et de repartir trop vite
	stepper.moveTo(stepper.currentPosition()); // gestion d'une sortie précipitée du menu
	update_stepper_last_known_position();

	int button_status,old_button_status;
	lcd.clear();
	display_stepper_position();

	while(true){
		stepper.run();
		display_stepper_position();
		if (action==true) {
			if (stepper.distanceToGo()==0) {
				update_stepper_last_known_position();
				display_stepper_position();
				action=false;
			}
			if (millis()-timer_read_key>200){ // si on a une action en cours, on y va mollo sur la lecture des boutons
				key = wait_on_escape(1);
				timer_read_key=millis();
			}
		} else {
			key = wait_on_escape(50);
		}


		switch (key){
		case NO_KEY:
			break;
		case phi_prompt_left:
			if (analog_keypad2.get_status()==buttons_held){
				if(stepper.enabledBoundLow()) {
					if(yn_dialog("Supprimer borne basse?")==1)
					{
						stepper.disableBoundLow();
					}
				} else {
					if(yn_dialog("Nouvelle borne  basse?")==1)
					{
						stepper.setBoundLow(stepper.currentPosition());
						update_stepper_bounds();
					}
				}

				lcd.clear();
				display_stepper_position();
			}
			break;
		case phi_prompt_right:
			if (analog_keypad2.get_status()==buttons_held){
				if(stepper.enabledBoundHigh()) {
					if(yn_dialog("Supprimer borne haute?")==1)
					{
						stepper.disableBoundHigh();
					}
				} else {
					if(yn_dialog("Nouvelle borne  haute?")==1)
					{
						stepper.setBoundHigh(stepper.currentPosition());
						update_stepper_bounds();
					}
				}
				lcd.clear();
				display_stepper_position();
			}
			break;
		case phi_prompt_up:
			//case 'U':
			moveWhileButtonheld(phi_prompt_up);
			break;
		case phi_prompt_down:
			//case 'D':
			moveWhileButtonheld(phi_prompt_down);
			break;
		case phi_prompt_escape:
			return;
			break;
		case phi_prompt_enter:
			break;
		case 'S':
			action=false;
			stepper.setSpeed(0); // coupe toute tentative de repartir tout seul :)
			stepper.setAcceleration(0); // et de repartir trop vite
			stepper.moveTo(stepper.currentPosition()); // on s'arrête sèchement
			update_stepper_last_known_position();
			break;
		case 'C':
			if (stepper.enabledBoundHigh()) {
				stepper.moveTo(stepper.getBoundHigh());
				action=true;
			} else {
				lcd.setCursor(0,1);
				center_text("No bound");
			}
			break;
		case 'Z':
			button_status=analog_keypad1.get_status();
			while (button_status==buttons_held || button_status==buttons_down || button_status==buttons_pressed ) {
				old_button_status=button_status;
				analog_keypad1.getKey();
				button_status=analog_keypad1.get_status();
			}
			switch (old_button_status) {
			case buttons_down:
				stepper.moveTo(0);
				action=true;
				break;
			case buttons_held:
				setNewCurrentPosition(0);
				display_stepper_position();
				break;
			default:
				break;
			}
			break;
		case 'N':
			if (mem_index!=25) {
				mem_index++;
			} else {
				mem_index=0;
			}
			button_status=analog_keypad1.get_status();
			while (button_status==buttons_held || button_status==buttons_down || button_status==buttons_pressed ) {
				old_button_status=button_status;
				analog_keypad1.getKey();
				button_status=analog_keypad1.get_status();
			}
			switch (old_button_status) {
			case buttons_down:
				//rien de particulier, l'incrément a déjà été fait
				break;
			case buttons_held:
				float_stepper_position=memorybank[mem_index]; // on lit la valeur en mm en mémoire
				if (float_stepper_position!=EMPTY_BANK){
					compute_position_in_step(float_stepper_position,step_current_position);
					stepper.moveTo(step_current_position);
					action=true;
				}
				break;
			default:
				break;
			}
		display_stepper_position();
		break;
		case 'M':
			if (mem_index!=0) {
				mem_index--;
			} else {
				mem_index=25;
			}
			button_status=analog_keypad1.get_status();
			while (button_status==buttons_held || button_status==buttons_down || button_status==buttons_pressed ) {
				old_button_status=button_status;
				analog_keypad1.getKey();
				button_status=analog_keypad1.get_status();
			}
			switch (old_button_status) {
			case buttons_down:
				//rien de particulier, l'incrément a déjà été fait
				break;
			case buttons_held:
				float_stepper_position=memorybank[mem_index]; // on lit la valeur en mm en mémoire
				if (float_stepper_position!=EMPTY_BANK){
					compute_position_in_step(float_stepper_position,step_current_position);
					stepper.moveTo(step_current_position);
					action=true;
				}
				break;
			default:
				break;
			}
			display_stepper_position();
			break;
		case 'F':
			if(yn_dialog("Format memory   bank?")==1)
			{
				format_memory_bank();
			}
			lcd.clear();
			display_stepper_position();
			break;
		case 'G':

			button_status=analog_keypad1.get_status();
			while (button_status==buttons_held || button_status==buttons_down || button_status==buttons_pressed ) {
				old_button_status=button_status;
				analog_keypad1.getKey();
				button_status=analog_keypad1.get_status();
			}
			switch (old_button_status) {
			case buttons_down:
				float_stepper_position=memorybank[mem_index]; // on lit la valeur en mm en mémoire
				if (float_stepper_position!=EMPTY_BANK){
					compute_position_in_step(float_stepper_position,step_current_position);
					stepper.moveTo(step_current_position);
					action=true;
				}
				break;
			case buttons_held:
				step_current_position=stepper.currentPosition();
				compute_position_in_mm(step_current_position,float_stepper_position);
				memorybank[mem_index]=float_stepper_position;
				update_memory_bank();
				display_stepper_position();
				break;
			default:
				break;
			}
			break;
		case 'T':
			auto_split();
			update_memory_bank();
			display_stepper_position();
			break;
		default:
			break;
		}
	}
}


// Menu texts
const char top_menu_item00[] PROGMEM ="Run";
const char top_menu_item01[] PROGMEM ="Parametrage";
const char * const top_menu_items[] PROGMEM = {top_menu_item00, top_menu_item01};

//PROGMEM const prog_char top_menu_item00[]="Run";
//PROGMEM const prog_char top_menu_item01[]="Parametrage";
//PROGMEM const char *top_menu_items[] = {top_menu_item00, top_menu_item01};

//This program is the main menu. It handles inputs from the keys, updates the menu or executes a certain menu function accordingly.
static void top_menu()
{
  int menu_pointer_1=0; // This stores the menu choice the user made.
  phi_prompt_struct myMenu; // This structure stores the main menu.
  create_phi_menu_from_array(myMenu, (char**)&top_menu_items, ELEM_CNT(top_menu_items));

  while(1) // This loops every time a menu item is selected.
  {
    lcd.clear();  // Refresh menu if a button has been pushed
    center_text("Main Menu");
    select_list(&myMenu); // Use the select_list to ask the user to select an item of the list, that is a menu item from your menu.
    menu_pointer_1=myMenu.low.i; // Get the selected item number and store it in the menu pointer.

    switch (menu_pointer_1) // See which menu item is selected and execute that correspond function
    {
    case 0:
    	manual_stepper();
    	break;
    case 1:
    	parametrage_menu();
    	break;
    default:
    	break;
    }

  }
}


void setup() {
	//pinMode(1,OUTPUT);
	Serial.begin(115200);
	EEPROM.setMaxAllowedWrites(32767);
	int i = 32767;
	Serial.println(i);
	init_pins();
	init_from_eeprom();
	init_from_eeprom_memorybank();
	configure_stepper();
	// TODO remove from here
	stepper.setBoundHigh(stepper_high_bound);
	stepper.setBoundLow(stepper_low_bound);
	configure_lcd();
	configure_analogkeyboard();

	// Supply the liquid crystal object, input keypads, and function key names. Also supply the column and row of the lcd, and indicator as '>'. You can also use '\x7e', which is a right arrow.
	init_phi_prompt(&lcd,keypads,function_keys, LCD_number_of_columns, LCD_number_of_rows, '~');



}

//long last_checktime = 0;

void loop() {
//	int i,j, key,key2;
//	char buffer[10];
//	while (1) {
//		if (millis()-timer_display_stepper>200){
//			i = analogRead(2);
//			j = analogRead(3);
//			//key=wait_on_escape(50);
//			//key=analog_keypad2.getKey();
//
//			sprintf(buffer,"%d - %d",i,j);
//			lcd.clear();
//			lcd.print(buffer);
//			timer_display_stepper = millis();
//		}
//	}

	top_menu();
	Serial.println("on ne devrait jamais arriver là!");
}




