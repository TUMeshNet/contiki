/*
 * Copyright (c) 2014, OpenMote Technologies, S.L.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the Institute nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE INSTITUTE AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE INSTITUTE OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * This file is part of the Contiki operating system.
 *
 */
<<<<<<< HEAD
<<<<<<< HEAD

/**
 * \addtogroup platform
 * @{
 *
 * \defgroup openmote
 *
 * \file
 * Header for the MAX44009 light sensor in OpenMote-CC2538.
=======
=======
>>>>>>> OpenMote/master
/*---------------------------------------------------------------------------*/
/**
 * \addtogroup openmote-sensors
 * @{
 *
 * \defgroup openmote-max44009-sensor MAX4009 light sensor
 * @{
 *
 * \file
 * Header file for the MAX44009 light sensor driver
<<<<<<< HEAD
>>>>>>> OpenMote/master
=======
>>>>>>> OpenMote/master
 *
 * \author
 * Pere Tuset <peretuset@openmote.com>
 */
<<<<<<< HEAD
<<<<<<< HEAD

#ifndef __MAX44009_H__
#define __MAX44009_H__
/*---------------------------------------------------------------------------*/
void max44009_init(void);
void max44009_reset(void);
uint8_t max44009_is_present(void);
uint16_t max44009_read_light(void);
float max44009_convert_light(uint16_t light);
/*---------------------------------------------------------------------------*/
#endif /* ifndef __MAX44009_H__ */
/** @} */
=======
=======
>>>>>>> OpenMote/master
/*---------------------------------------------------------------------------*/
#ifndef MAX44009_H_
#define MAX44009_H_
/*---------------------------------------------------------------------------*/
#define MAX44009_ERROR            (-1)
#define MAX44009_SUCCESS          (0)
#define MAX44009_ACTIVATE         (SENSORS_ACTIVE)
#define MAX44009_READ_RAW_LIGHT   (2)
#define MAX44009_READ_LIGHT       (3)
#define MAX44009_RESET            (4)
#define MAX44009_NONE             (5)
/*---------------------------------------------------------------------------*/
#define MAX44009_SENSOR "MAX44009 Sensor"
/*---------------------------------------------------------------------------*/
extern const struct sensors_sensor max44009;
/*---------------------------------------------------------------------------*/
#endif /* MAX44009_H_ */
/*---------------------------------------------------------------------------*/
/**
 * @}
 * @}
 */
<<<<<<< HEAD
>>>>>>> OpenMote/master
=======
>>>>>>> OpenMote/master
