/* Copyright 2021 Colin Lam (Ploopy Corporation)
 * Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
 * Copyright 2019 Sunjun Kim
 * Copyright 2019 Hiroyuki Okada
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

// Safe range starts at `PLOOPY_SAFE_RANGE` instead.

uint8_t caps_lock_state = 0;
uint8_t num_lock_state = 0;
uint8_t scroll_enabled = 0;
int8_t delta_x = 0;
int8_t delta_y = 0;

report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    if (num_lock_state == 1) {
        delta_x += mouse_report.x;
        delta_y += mouse_report.y;

        // Scroll is extremely sensitive: "120" seems to be a
        // comfortable value for me. Anything less feels too fast.

        if (delta_x > 120) {
            mouse_report.h = -1;
            delta_x = 0;
        } else if (delta_x < -120) {
            mouse_report.h = 1;
            delta_x = 0;
        }

        if (delta_y > 120) {
            mouse_report.v = 1;
            delta_y = 0;
        } else if (delta_y < -120) {
            mouse_report.v = -1;
            delta_y = 0;
        }

        // Scrolling, not moving the pointer
        mouse_report.x = mouse_report.y = 0;
    }

    return mouse_report;
}

void keyboard_post_init_user(void) {
    caps_lock_state = host_keyboard_led_state().caps_lock;
	num_lock_state = host_keyboard_led_state().num_lock;
}

bool led_update_user(led_t led_state) {

    // CapsLock led triggers reset to bootloader mode
    if (led_state.caps_lock != caps_lock_state) {
        reset_keyboard();
    }
    caps_lock_state = led_state.caps_lock;

    // NumLock led triggers scroll mode
    if (led_state.num_lock != num_lock_state) {
        delta_x = 0;
        delta_y = 0;
    }
	num_lock_state = led_state.num_lock;

    return true;
}

