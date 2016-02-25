/* 
 * File:   states_setup.h
 * Author: Harry
 *
 * Created on 13 February 2016, 10:02
 */

#ifndef debuggersonpi_pic_states_setup_h
#define debuggersonpi_pic_states_setup_h

/////////////////////////////////////INCLUDES///////////////////////////////////

#include "xc.h"
#include "datatypes.h"

#include "compass.h"

/////////////////////////////////////DEFINES////////////////////////////////////

//////////////////////////////////GLOBAL VARIABLES//////////////////////////////

////////////////////////////////FUNCTION DECLARATIONS///////////////////////////

// Switch case function
void switch_statesetup(control_variables * local_state_vars_ptr,
                       spi_state_data * local_currentstate_data_ptr,
                       break_conditions_store * local_state_break_conditions_ptr);
// Default setup : stopped
void setup_state_stopped();

// Open loop
void setup_state_ol_forward(spi_state_data * local_currentstate_data_ptr,
                            control_variables * local_state_vars_ptr,
                            break_conditions_store * local_state_break_conditions_ptr);
void setup_state_ol_reverse(spi_state_data * local_currentstate_data_ptr,
                            control_variables * local_state_vars_ptr,
                            break_conditions_store * local_state_break_conditions_ptr);
// Compass feedback
void setup_state_comp_forward(spi_state_data * local_currentstate_data_ptr,
                              control_variables * local_state_vars_ptr,
                              break_conditions_store * local_state_break_conditions_ptr);
void setup_state_comp_turn(spi_state_data * local_currentstate_data_ptr,
                           control_variables * local_state_vars_ptr,
                           break_conditions_store * local_state_break_conditions_ptr);
void setup_state_comp_reverse(spi_state_data * local_currentstate_data_ptr,
                              control_variables * local_state_vars_ptr,
                              break_conditions_store * local_state_break_conditions_ptr);
void setup_state_comp_rev_left(spi_state_data * local_currentstate_data_ptr,
                               control_variables * local_state_vars_ptr,
                               break_conditions_store * local_state_break_conditions_ptr);
void setup_state_comp_rev_right(spi_state_data * local_currentstate_data_ptr,
                                control_variables * local_state_vars_ptr,
                                break_conditions_store * local_state_break_conditions_ptr);
// Encoder feedback
void setup_state_ecdr_forward(spi_state_data * local_currentstate_data_ptr,
                              control_variables * local_state_vars_ptr,
                              break_conditions_store * local_state_break_conditions_ptr);
void setup_state_ecdr_reverse(spi_state_data * local_currentstate_data_ptr,
                              control_variables * local_state_vars_ptr,
                              break_conditions_store * local_state_break_conditions_ptr);
void setup_state_ecdr_left(spi_state_data * local_currentstate_data_ptr,
                           control_variables * local_state_vars_ptr,
                           break_conditions_store * local_state_break_conditions_ptr);
void setup_state_ecdr_right(spi_state_data * local_currentstate_data_ptr,
                            control_variables * local_state_vars_ptr,
                            break_conditions_store * local_state_break_conditions_ptr);
void setup_state_ecdr_rev_left(spi_state_data * local_currentstate_data_ptr,
                               control_variables * local_state_vars_ptr,
                               break_conditions_store * local_state_break_conditions_ptr);
void setup_state_ecdr_rev_right(spi_state_data * local_currentstate_data_ptr,
                                control_variables * local_state_vars_ptr,
                                break_conditions_store * local_state_break_conditions_ptr);
// Photosensors/Compass Feedback
void setup_state_psns_forward(spi_state_data * local_currentstate_data_ptr,
                              control_variables * local_state_vars_ptr,
                              break_conditions_store * local_state_break_conditions_ptr);
void setup_state_psns_forward_junctiondetect(spi_state_data * local_currentstate_data_ptr,
                                             control_variables * local_state_vars_ptr,
                                             break_conditions_store * local_state_break_conditions_ptr);

#endif //debuggersonpi_pic_states_setup_h