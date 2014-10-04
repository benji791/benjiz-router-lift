/** \file
 *  \brief     This is the first official release of the phi_interfaces library.
 *  \details   This library unites buttons, rotary encoders and several types of keypads libraries under one library, the phi_interfaces library, for easy of use.
 *  This is the first official release. All currently supported input devices are buttons, matrix keypads, rotary encoders, analog buttons, 2-axis joysticks, serial keypads, and liudr keypads.
 *  User is encouraged to obtain compatible hardware from liudr or is solely responsible for converting it to work on other shields or configurations.
 *  \author    Dr. John Liu
 *  \version   1.01
 *  \date      02/05/2012
 *  \pre       Compatible with Arduino IDE 1.0 and 0022.
 *  \bug       Not tested on, Arduino IDE 0023 or arduino MEGA hardware! If you have done such test, please contact me with results.
 *  \warning   PLEASE DO NOT REMOVE THIS COMMENT WHEN REDISTRIBUTING! No warranty!
 *  \copyright Dr. John Liu. Free software for educational and personal uses. Commercial use without authorization is prohibited.
 *  \par Contact
 * Obtain the documentation or find details of the phi_interfaces, phi_prompt TUI library, Phi-2 shield, and Phi-panel hardware or contact Dr. Liu at:
 *
 * <a href="http://liudr.wordpress.com/phi_interfaces/">http://liudr.wordpress.com/phi_interfaces/</a>
 *
 * <a href="http://liudr.wordpress.com/phi-panel/">http://liudr.wordpress.com/phi-panel/</a>
 *
 * <a href="http://liudr.wordpress.com/phi_prompt/">http://liudr.wordpress.com/phi_prompt/</a>
 *
 * <a href="http://liudr.wordpress.com/phi-2-shield/">http://liudr.wordpress.com/phi-2-shield/</a>
 *
 *  \par Updates
 * 02/05/2012: Added support for 2-axis joystick as a directional keypad and example code.
 * 01/16/2012: Original code released.
*/

#ifndef phi_interfaces_h
#define phi_interfaces_h
#if ARDUINO < 100
#include <WProgram.h>
#else
#include <Arduino.h>
#endif

//Device types:
#define Liudr_shift_register_pad 0      ///< Liudr shift register pad used on phi-panels.
#define Single_button 1                 ///< (Not used in this library) Single buttons need to connect an arduino pin to GND.
#define Keypad 2                        ///< Generic keypad
#define Matrix3X4 3                     ///< 3X4 matrix keypad
#define Matrix4X4 4                     ///< 4X4 matrix keypad
#define Button_group 5                  ///< A group of arduino pins, each connected to a single button. Single buttons need to connect an arduino pin to GND.
#define Rotary_encoder 6                ///< Digital rotary encoder with two channels and a common connected to GND
#define PS2_keyboard 7                  ///< A PS/2 keyboard. This is not yet supported.
#define Analog_keypad 8                 ///< A number of buttons connected together with some resistors and one analog input.
#define Serial_keypad 9                 ///< Phi-panel serial LCD keypad as input.
#define Joy_stick 10                    ///< Phi_joy_stick as digital input with 8 directional keys.

//Button status
#define buttons_up 0        ///< Non-transitional button status
#define buttons_pressed 1   ///< Transitional button status
#define buttons_down 2      ///< Non-transitional button status
#define buttons_held 3      ///< Non-transitional button status
#define buttons_released 4  ///< Transitional button status
#define buttons_debounce 5  ///< One needs to wait till debounce status is over to become pressed status to confirm a press.

//Operating parameters
#define buttons_hold_time_def 1000      ///< Default key down time needed to be considered the key is held down
#define buttons_debounce_time_def 50    ///< Default key down time needed to be considered the key is not bouncing anymore
#define buttons_dash_threshold_def 10   ///< Default key down time needed to be considered the key is held down long enough to repeat in a dash speed
#define buttons_repeat_time_def 200     ///< Default delay between repeating of a held key
#define buttons_dash_time_def 50        ///< Default delay between dash repeating of a held key

//Internal and external "NO KEY" return values
#define NO_KEYs 255         ///< This is no key in scan code, internal to the library.
#define NO_KEY 0            ///< This is no key that the library outputs to a caller, to be compatible with keypad.h

//Pure virtual base classes (interfaces) start here
/*
.___  ___.  __    __   __      .___________. __  .______    __       _______
|   \/   | |  |  |  | |  |     |           ||  | |   _  \  |  |     |   ____|
|  \  /  | |  |  |  | |  |     `---|  |----`|  | |  |_)  | |  |     |  |__
|  |\/|  | |  |  |  | |  |         |  |     |  | |   ___/  |  |     |   __|
|  |  |  | |  `--'  | |  `----.    |  |     |  | |  |      |  `----.|  |____
|__|  |__|  \______/  |_______|    |__|     |__| | _|      |_______||_______|
*/
/** \brief Virtual base class for inputs that contain multiple keys.
 * \details This is a virtual base class meant to be inherited by child classes. You cannot instantiate any objects from this class.
 * This class is inherited by classes to handle matrix keypads, PS/2 keyboards (planned), rotary encoders, analog buttons, button groups, 2-axis joysticks.
 * This class handles anything that requires the program to not only sense the status of a digital or analog pin status, but also interpret the input and output keys pressed.
*/
class multiple_button_input{
  public:
/// This stores the type of the device such as rotary encoder or keypad etc.
  byte device_type;
/** \brief This function is responsible for sensing the input for key press and update status.
 * \details This function is responsible for sensing the input for key press and update status. Each child class implements this method to translate physical status changes into named buttons.
*/
  virtual byte getKey()=0;
/// This returns device type. See device type defs.
  virtual byte get_device_type() {return device_type;};
 /// This should be run after getKey to get the up-to-date result.
  virtual byte get_status()=0;
/// This should be run after getKey to get the up-to-date result.
  virtual byte get_sensed()=0;
/// This sets how long the button needs to be held before it repeats.
  virtual void set_hold(unsigned int ht) {buttons_hold_time=ht;};
/// This sets how long the button needs to be held before it is considered pressed.
  virtual void set_debounce(unsigned int dt) {buttons_debounce_time=dt;};
/// This sets how long the button needs to be held before it repeats rapidly.
  virtual void set_dash_threshold(unsigned int dt) {buttons_dash_threshold=dt;};
/// This sets how often the button press repeats after being held.
  virtual void set_repeat(unsigned int rt) {buttons_repeat_time=rt;};
/// This sets how often the button press rapidly repeats after being held.
  virtual void set_dash(unsigned int dt) {buttons_dash_time=dt;};

  protected:
  static unsigned long t_last_action;           ///< This stores the last time any real keypad was active. You may use this to implement sleeping mode.
  static unsigned int buttons_hold_time;        ///< Key down time needed to be considered the key is held down
  static unsigned int buttons_debounce_time;    ///< Key down time needed to be considered the key is not bouncing anymore
  static unsigned int buttons_dash_threshold;   ///< Key down time needed to be considered the key is held down long enough to repeat in a dash speed
  static unsigned int buttons_repeat_time;      ///< Delay between repeating of a held key
  static unsigned int buttons_dash_time;        ///< Delay between dash repeating of a held key
};

// Derived classes start here. Note: phi_keypads is pure.
/*
.______        ______   .___________.    ___      .______     ____    ____
|   _  \      /  __  \  |           |   /   \     |   _  \    \   \  /   /
|  |_)  |    |  |  |  | `---|  |----`  /  ^  \    |  |_)  |    \   \/   /
|      /     |  |  |  |     |  |      /  /_\  \   |      /      \_    _/
|  |\  \----.|  `--'  |     |  |     /  _____  \  |  |\  \----.   |  |
| _| `._____| \______/      |__|    /__/     \__\ | _| `._____|   |__|
*/
/** \brief a class for rotary encoders
 * \details This class senses a rotary encoder and reports when the rotary knob is turned one detent up or down.
 * You may use this similarly to a keypad. A call to getKey will yield say 'U' or 'D' for dial up or down. You can also call get_angle to get the orientation of the dial.
 * To use a rotary encoder with a clickable shaft, define a button with phi_buttons class or phi_button_arrays class, with the latter as preferred method.
 * By default both channels are off when the knob is in a groove. I strongly suggest you purchase an encoder that does that instead of both channels on when the knob is in a groove.
 * This class supports important functions such as getKey(), which you need to call periodically inside a loop to update the status of the encoder and sense a dial up or down when they happen.
 * Then if the return is up or down, you can trigger actions.
 * This library is not interrupt driven and thus has no call-back functions.
*/
class phi_rotary_encoders: public multiple_button_input{
  public:
  phi_rotary_encoders(char *na, byte ChnA, byte ChnB, byte det); ///< Constructor for rotary encoder
  byte getKey();            ///< Returns the key corresponding to dial up or down or NO_KEY.
  byte get_status();        ///< Always returns buttons_up since the encoder works differently than other keypads.
  byte get_sensed();        ///< Always returns NO_KEY since the encoder works differently than other keypads.
  byte get_angle();         ///< Get the angle or orientation of the rotary encoder between 0 and detent-1.

  protected:
  byte EncoderChnA;         ///< Arduino pin connected to channel A of the encoder
  byte EncoderChnB;         ///< Arduino pin connected to channel B of the encoder
  byte detent;              ///< Number of detents per rotation of the encoder
  byte stat_seq_ptr;        ///< Current status of the encoder in gray code
  byte counter;             ///< Counts for get_angle() to calculate knob orientation
  char * key_names;         ///< Pointer to array of characters two elements long. Each click up or down is translated into a name from this array such as 'U'.
};

/*
     _______. _______ .______       __       ___       __
    /       ||   ____||   _  \     |  |     /   \     |  |
   |   (----`|  |__   |  |_)  |    |  |    /  ^  \    |  |
    \   \    |   __|  |      /     |  |   /  /_\  \   |  |
.----)   |   |  |____ |  |\  \----.|  |  /  _____  \  |  `----.
|_______/    |_______|| _| `._____||__| /__/     \__\ |_______|
*/
/** \brief a class for <a href="http://liudr.wordpress.com/phi-panel/">phi-panel serial LCD keypads</a> and for serial port to simulate key presses
 * \details This class provides a way to seamlessly integrate a <a href="http://liudr.wordpress.com/phi-panel/">phi-panel serial LCD keypad</a> or to simulate key presses with serial port under the multiple_button_input virtual base class.
 * The purpose of this class is to integrate a <a href="http://liudr.wordpress.com/phi-panel/">phi-panel serial LCD keypad</a> or simulate key presses with serial port
 * This way a project can carry on without considering how to lay out user interfaces such as do you want single buttons or a keypad or with some rotary encoders?
 * Any actual multiple_button_input devices can do can be done over serial.
 * With this class, you can start working on your project's function either with a <a href="http://liudr.wordpress.com/phi-panel/">phi-panel serial LCD keypad</a> or serial port instead of worrying about its interface with a user.
 * Later you can decide what type of user interface and layout you want once you have developed all the project functions, an appropriate time to discuss user interface layout after all.
 * In Arduino IDE 1.0, both software and hardware serials are supported. In Arduino IDE 0022, only hardware serial is supported since the software serial library in this and previous versions don't inherit from Stream.
 * The getKey simply reads from serial port and returns either a character or NO_KEY.
 * The serial port has to be initialized with begin method before it can be passed to this object.
*/
class phi_serial_keypads:public multiple_button_input {
  public:
  phi_serial_keypads(Stream *ser, unsigned long bau); ///< Constructor for <a href="http://liudr.wordpress.com/phi-panel/">phi-panel serial LCD keypads</a> or serial port input
  byte getKey();                    ///< Returns the key coming from serial port or NO_KEY.
/// Get sensed button name. No serial port read will be done and it always return NO_KEY.
  virtual byte get_sensed(){return NO_KEY;};
/// Get status of the button being sensed. No serial port read will be done and it always return buttons_up.
  virtual byte get_status(){return buttons_up;};

  protected:
  Stream *ser_port; ///< Pointer to a Stream object such as hardware serial port.
  unsigned long ser_baud; ///< Baud rate of the Stream object.
};

/*
 __  ___  ___________    ____ .______      ___       _______
|  |/  / |   ____\   \  /   / |   _  \    /   \     |       \
|  '  /  |  |__   \   \/   /  |  |_)  |  /  ^  \    |  .--.  |
|    <   |   __|   \_    _/   |   ___/  /  /_\  \   |  |  |  |
|  .  \  |  |____    |  |     |  |     /  _____  \  |  '--'  |
|__|\__\ |_______|   |__|     | _|    /__/     \__\ |_______/
*/
/** \brief virtual class for all keypad subclasses
 * \details This class provides the hierarchy for actual keypad classes to inherit from. It provides common high-level function codes.
 * These function codes, coupled with the lower level function code of each inheriting child class, completes the translation from sensing physical pins to outputting named buttons with mapping array.
 * The function hierarchy is getKey()<---scanKeypad()<---sense_all().
 * The sense_all reads digital pins for input.
 * The scanKeypad turns these inputs into status changes for keys and provide scan code of the pressed key. It handles status change including debouncing and repeat.
 * The getKey translates the key press from scan code (0 to max_key-1) into named keys with the mapping array.
*/
class phi_keypads:public multiple_button_input {
  public:
  byte keyboard_type;               ///< This stores the type of the keypad so a caller can use special functions for specific keypads.
  byte getKey();                    ///< Returns the key corresponding to the pressed button or NO_KEY.
  unsigned long button_status_t;    ///< This is the time stamp of the sensed button first in the status stored in button_status.

  virtual byte get_sensed();        ///< Get sensed button name. Replace this in children class if needed.
  virtual byte get_status();        ///< Get status of the button being sensed. Replace this in children class if needed.

  protected:
  byte rows;                ///< Number of rows on a keypad. Rows are input pins. In analog keypads, each row pin is an analog pin.
  byte columns;             ///< Number of columns on a keypad. Columns are output pins when the column is addressed and tri-stated when the column is not addressed. In analog keypads, column represents number of buttons connected to each analog pin.
  byte buttonBits;          ///< This is the button bits. It's a temporary variable.
  byte button_sensed;       ///< This indicates which button is sensed or 255 if no button is sensed.
  byte button_status;       ///< This indicates the status of the button if button_sensed is not 255.
  byte * mySensorPins;      ///< Pointer to array of pins. Each subclass has a different convention of what pins are used, usually rows are followed by columns.
  char * key_names;         ///< Pointer to array of characters. Each key press is translated into a name from this array such as '0'.

  byte scanKeypad();        ///< Updates status of the keypad with button_sensed and button_status to provide information to getKey
/// This senses all input pins.
  virtual byte sense_all()=0;
};

/*
       __    ______   ____    ____  _______.___________. __    ______  __  ___
      |  |  /  __  \  \   \  /   / /       |           ||  |  /      ||  |/  /
      |  | |  |  |  |  \   \/   / |   (----`---|  |----`|  | |  ,----'|  '  /
.--.  |  | |  |  |  |   \_    _/   \   \       |  |     |  | |  |     |    <
|  `--'  | |  `--'  |     |  | .----)   |      |  |     |  | |  `----.|  .  \
 \______/   \______/      |__| |_______/       |__|     |__|  \______||__|\__\
*/
/** \brief class for 2-axis joy sticks
 * \details This class provides support to sense a 2-axis joy stick, with either analog output on each axis, or digital output of 8 directional keys.
 * These function codes, coupled with the lower level function code of each inheriting child class, completes the translation from sensing physical pins to outputting named buttons with mapping array.
 * The function hierarchy is getKey()<---scanKeypad()<---sense_all().
 * The sense_all reads digital pins for input.
 * The scanKeypad turns these inputs into status changes for keys and provide scan code of the pressed key. It handles status change including debouncing and repeat.
 * The getKey translates the key press from scan code (0 to max_key-1) into named keys with the mapping array.
*/
class phi_joysticks:public phi_keypads {
  public:
  phi_joysticks(char *na, byte *sp, int * dp, int th); ///< Constructor for joystick
  byte keyboard_type;               ///< This stores the type of the keypad so a caller can use special functions for specific keypads.
  int get_x(){return axis_vals[0];} ///< Returns x axis value of the joystick
  int get_y(){return axis_vals[1];} ///< Returns y axis value of the joystick
  unsigned long button_status_t;    ///< This is the time stamp of the sensed button first in the status stored in button_status.

  protected:
  int axis_vals[2];         ///< This stores the x and y axis values read from analog pin
  int threshold;            ///< This stores the threshold of matching the joystick with a directional key.
  int * values;             ///< This pointer points to an integer array with values of analog inputs. The number of values is equal to the number of axis times 3. The array starts with the value of the first axis, when it is pushed up, then the center value of this axis, then the value of this axis when it is pushed down.
  byte sense_all(); ///< This senses all input pins.
};

/*
     ___      .__   __.      ___       __        ______     _______
    /   \     |  \ |  |     /   \     |  |      /  __  \   /  _____|
   /  ^  \    |   \|  |    /  ^  \    |  |     |  |  |  | |  |  __
  /  /_\  \   |  . `  |   /  /_\  \   |  |     |  |  |  | |  | |_ |
 /  _____  \  |  |\   |  /  _____  \  |  `----.|  `--'  | |  |__| |
/__/     \__\ |__| \__| /__/     \__\ |_______| \______/   \______|
*/
/** \brief a class for buttons connected to analog pin with resistors
 * \details This class turns analogButton into a keypad. You may connect several buttons to one analog pin with resistors.
 * You may also use multiple analog pins, with each pin connected to several buttons and resistors, to form a keypad.
 * You have to use the same resistor values for all analog pins and thus the same amount of buttons per analog pin.
 * If you need less buttons, just don't connect that many and leave the rest of the circuit with all resistors untouched.
 * Only one function needs to be implemented, the sense_all(). Everything higher level is the same across all keypad subclasses, defined in phi_keypads.
 * Find the sample circuit on my blog under http://liudr.wordpress.com/phi_interfaces/
*/
class phi_analog_keypads: public phi_keypads{
  public:
  phi_analog_keypads(char *na, byte *sp, int * dp, byte r, byte c); ///< Constructor for analog keypad

  protected:
  int * values;             ///< This pointer points to an integer array with values of analog inputs. The number of dividers is equal to the number of buttons on each row. The values should increase monotonically, such as 0,146,342,513,744. A range of 10 between the stored and read values is taken as match to guarantee the match is good. These values apply to all columns so if you want to make a keypad with say three analog pins and 5 buttons on each pin, use the same button/resistor setup on all three pins.
  byte sense_all();         ///< This senses all analog input pins for change of key status.
};

/*
.___  ___.      ___   .___________..______       __  ___   ___
|   \/   |     /   \  |           ||   _  \     |  | \  \ /  /
|  \  /  |    /  ^  \ `---|  |----`|  |_)  |    |  |  \  V  /
|  |\/|  |   /  /_\  \    |  |     |      /     |  |   >   <
|  |  |  |  /  _____  \   |  |     |  |\  \----.|  |  /  .  \
|__|  |__| /__/     \__\  |__|     | _| `._____||__| /__/ \__\
*/
/** \brief a class for matrix keypads of any size.
 * \details This is the actual class for matrix keypads, not the phi_keypads, which is a virtual class to support all keypad type of inputs.
 * Only one function needs to be implemented, the sense_all(). Everything higher level is the same across all keypad subclasses, defined in phi_keypads.
*/
class phi_matrix_keypads: public phi_keypads{
  public:
  phi_matrix_keypads(char *na, byte * sp, byte r, byte c); ///< Constructor for matrix keypad.

  protected:
  byte sense_all();         ///< This senses all input pins.
};

/*
.______    __    __  .___________.___________.  ______   .__   __.
|   _  \  |  |  |  | |           |           | /  __  \  |  \ |  |
|  |_)  | |  |  |  | `---|  |----`---|  |----`|  |  |  | |   \|  |
|   _  <  |  |  |  |     |  |        |  |     |  |  |  | |  . `  |
|  |_)  | |  `--'  |     |  |        |  |     |  `--'  | |  |\   |
|______/   \______/      |__|        |__|      \______/  |__| \__|

  _______ .______        ______    __    __  .______        _______.
 /  _____||   _  \      /  __  \  |  |  |  | |   _  \      /       |
|  |  __  |  |_)  |    |  |  |  | |  |  |  | |  |_)  |    |   (----`
|  | |_ | |      /     |  |  |  | |  |  |  | |   ___/      \   \
|  |__| | |  |\  \----.|  `--'  | |  `--'  | |  |      .----)   |
 \______| | _| `._____| \______/   \______/  | _|      |_______/
*/
/** \brief a class for a group of buttons
 * \details Collection of all single buttons into a group and handled as a keypad so each button push is translated into a named key value such as '1'.
 * The pointer to pins has no column or row lines. Each pin is connected to one button.
 * This is the way to go if you want to start small with few buttons and intend to expand your interface into more buttons and add rotary encoders and keypads.
 * Using this class instead of phi_buttons class also gives you a virtual layer, where you can develop your project without any buttons or keypads and simulate such input with serial
 * You should only use the phi_buttons class if you are happy with just a few buttons and don't intend to expand your interface into mixtures of keypads, rotary encoders etc.
*/
class phi_button_groups: public phi_keypads{
  public:
  phi_button_groups(char *na, byte * sp, byte r); ///< Constructor for phi_button_groups

  protected:
  byte sense_all();         ///< This senses all input pins.
};

/*
 __       __   __    __   _______  .______
|  |     |  | |  |  |  | |       \ |   _  \
|  |     |  | |  |  |  | |  .--.  ||  |_)  |
|  |     |  | |  |  |  | |  |  |  ||      /
|  `----.|  | |  `--'  | |  '--'  ||  |\  \----.
|_______||__|  \______/  |_______/ | _| `._____|
*/
/** \brief a class for Liudr's shift register LED keypad
 * \details This keypad class uses an undisclosed hardware design that incorporates a keypad and LED indicators. The details may be published in a future date and is not the focus of this library.
*/
class phi_liudr_keypads: public phi_keypads{
  public:
  phi_liudr_keypads(char *na, byte * sp, byte cp, byte dp, byte lp, byte r, byte c);    ///< Constructor for liudr keypad led panel
  void setLed(byte led, byte on_off);   ///< Updates LED status using shift registers. Two bytes are shifted out.
  void setLedByte(byte led);            ///< Updates LED status using shift registers. Two bytes are shifted out.

  protected:
  byte clockPin;            ///< Clock pin for liudr shift register pad
  byte dataPin;             ///< Data pin for liudr shift register pad
  byte latchPin;            ///< Latch or storage pin for liudr shift register pad
  byte ledStatusBits;       ///< Contains the LED status bits of liudr shift register pad

  byte sense_all();         ///< This senses all input pins.
  void updateShiftRegister(byte first8, byte next8);    ///< This updates shift register with 2 bytes.
};

#endif
