// #include "stepper_motor.h"
#include "usart.h"
#include "json.h"
#include "stdbool.h"
#include "stdio.h"
#include "stepper_motor.h"

void lwjson_my_init() {
    lwjson_init(&lwjson, tokens, LWJSON_ARRAYSIZE(tokens));
}

void json_process(char *json_str) {
    if (lwjson_parse(&lwjson, (char*)json_str) == lwjsonOK) {
        const lwjson_token_t *token1 = lwjson_find(&lwjson, "angle");
        const lwjson_token_t *token2 = lwjson_find(&lwjson, "setZero");
        // const lwjson_token_t *token3 = lwjson_find(&lwjson_find, "returnAngle");

        if (token1 != NULL) {
            int data = lwjson_get_val_int(token1);

        // TODO: sprawdzenie zakresu
            if (data > MAX_LEFT || data < MAX_RIGHT) {
                MOTOR_target_angle = data;
                MOTOR_current_status = MOTOR_ANGLE_RECEIVED; // zmiana statusu
            }
        }
        else if (token2 != NULL) {
            int data = lwjson_get_val_int(token2);
            if (data) {
                ENCODER_init = false;
            }
            MOTOR_target_angle = 0;
        }

        /*
        else if (token3 != NULL) {
            int data = lwjson_get_value_int(token3);
            if (data) {
                data_to_send = true;
            }
        }
        */
    }
}

