/* Copyright 2023 Brian Low
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
 #pragma once

 #define XXX KC_NO

#define LAYOUT_miryoku(\
    K00, K01, K02, K03, K04,                K05, K06, K07, K08, K09,\
    K10, K11, K12, K13, K14,                K15, K16, K17, K18, K19,\
    K20, K21, K22, K23, K24,                K25, K26, K27, K28, K29,\
    N30, N31, K32, K33, K34,                K35, K36, K37, N38, N39\
)\
LAYOUT(\
XXX, XXX, XXX, XXX, XXX, XXX,                XXX, XXX, XXX, XXX, XXX, XXX,\
XXX, K00, K01, K02, K03, K04,                K05, K06, K07, K08, K09, XXX,\
XXX, K10, K11, K12, K13, K14,                K15, K16, K17, K18, K19, XXX,\
XXX, K20, K21, K22, K23, K24, XXX,      XXX, K25, K26, K27, K28, K29, XXX,\
         XXX, XXX, K32, K33, K34,      K35, K36, K37, XXX, XXX\
)

 // Enabling this option changes the startup behavior to listen for an
 // active USB communication to delegate which part is master and which
 // is slave. With this option enabled and theres’s USB communication,
 // then that half assumes it is the master, otherwise it assumes it
 // is the slave.
 //
 // I've found this helps with some ProMicros where the slave does not boot
 #define SPLIT_USB_DETECT

 #define RGB_MATRIX_SLEEP     // turn off effects when suspended
 #define SPLIT_TRANSPORT_MIRROR             // If LED_MATRIX_KEYPRESSES or LED_MATRIX_KEYRELEASES is enabled, you also will want to enable SPLIT_TRANSPORT_MIRROR
 #define RGB_MATRIX_MAXIMUM_BRIGHTNESS 100  // limits maximum brightness of LEDs (max 255). Higher may cause the controller to crash.
