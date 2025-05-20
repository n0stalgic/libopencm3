/** @addtogroup rtc_defines
 * @author @htmlonly &copy; @endhtmlonly 2012 Karl Palsson <karlp@tweak.net.au>
 *
 * @brief This covers the "version 2" RTC peripheral.
 * 
 * @todo update this description
 * 
 * This is completely different
 * to the v1 RTC periph on the F1 series devices.  It has BCD counters, with
 * automatic leapyear corrections and daylight savings support.
 * This peripheral is used on the majority of G, L, and F (minus F1) devices, though some
 * only support a subset.
 */
/*
 * This file is part of the libopencm3 project.
 *
 * Copyright (C) 2012 Karl Palsson <karlp@tweak.net.au>
 *
 * This library is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library.  If not, see <http://www.gnu.org/licenses/>.
 */

/* THIS FILE SHOULD NOT BE INCLUDED DIRECTLY, BUT ONLY VIA RTC.H
The order of header inclusion is important. rtc.h includes the device
specific memorymap.h header before including this header file.*/

/** @cond */
#ifdef LIBOPENCM3_RTC_H
/** @endcond */
#ifndef LIBOPENCM3_RTC_COMMON_ALL_H
#define LIBOPENCM3_RTC_COMMON_ALL_H

/**@{*/

/** @defgroup rtc_registers RTC Registers
 * @ingroup rtc_defines
 * @brief Real Time Clock registers
@{*/

/** RTC time register (RTC_TR) */
#define RTC_TR          MMIO32(RTC_BASE + 0x00)

/** RTC date register (RTC_DR) */
#define RTC_DR          MMIO32(RTC_BASE + 0x04)

/** RTC prescaler register (RTC_PRER) */
#define RTC_PRER        MMIO32(RTC_BASE + 0x10)

/** RTC wakeup timer register (RTC_WUTR) */
#define RTC_WUTR        MMIO32(RTC_BASE + 0x14)

/** RTC write protection register (RTC_WPR)*/
#define RTC_WPR         MMIO32(RTC_BASE + 0x24)

/** RTC time stamp time register (RTC_TSTR) */
#define RTC_TSTR        MMIO32(RTC_BASE + 0x30)

/** @defgroup rtc_tr_values RTC Time register (RTC_TR) values
 * @ingroup rtc_registers
 * Note: Bits [31:23], 15, and 7 are reserved, and must be kept at reset value.
@{*/
/** AM/PM notation */
#define RTC_TR_PM         (1 << 22)
/** Hour tens in BCD format shift */
#define RTC_TR_HT_SHIFT   (20)
/** Hour tens in BCD format mask */
#define RTC_TR_HT_MASK    (0x3)
/** Hour units in BCD format shift */
#define RTC_TR_HU_SHIFT   (16)
/** Hour units in BCD format mask */
#define RTC_TR_HU_MASK    (0xf)
/** Minute tens in BCD format shift */
#define RTC_TR_MNT_SHIFT  (12)
/** Minute tens in BCD format mask */
#define RTC_TR_MNT_MASK   (0x7)
/** Minute units in BCD format shift */
#define RTC_TR_MNU_SHIFT  (8)
/** Minute units in BCD format mask */
#define RTC_TR_MNU_MASK   (0xf)
/** Second tens in BCD format shift */
#define RTC_TR_ST_SHIFT   (4)
/** Second tens in BCD format mask */
#define RTC_TR_ST_MASK    (0x7)
/** Second units in BCD format shift */
#define RTC_TR_SU_SHIFT   (0)
/** Second units in BCD format mask */
#define RTC_TR_SU_MASK    (0xf)
/**@}*/

/** @defgroup rtc_dr_values RTC Date register (RTC_DR) values
 * @ingroup rtc_registers
 * Note: Bits [31:24] and [7:6] are reserved, and must be kept at reset value.
@{*/
/** Year tens in BCD format shift */
#define RTC_DR_YT_SHIFT   (20)
/** Year tens in BCD format mask */
#define RTC_DR_YT_MASK    (0xf)
/** Year units in BCD format shift */
#define RTC_DR_YU_SHIFT   (16)
/** Year units in BCD format mask */
#define RTC_DR_YU_MASK    (0xf)
/** Weekday units shift */
#define RTC_DR_WDU_SHIFT  (13)
/** Weekday units mask */
#define RTC_DR_WDU_MASK   (0x7)
/** Month tens in BCD format shift */
#define RTC_DR_MT_SHIFT   (12)
/** Month tens in BCD format mask */
#define RTC_DR_MT_MASK    (1)
/** Month units in BCD format shift */
#define RTC_DR_MU_SHIFT   (8)
/** Month units in BCD format mask */
#define RTC_DR_MU_MASK    (0xf)
/** Date tens in BCD format shift */
#define RTC_DR_DT_SHIFT   (4)
/** Date tens in BCD format mask */
#define RTC_DR_DT_MASK    (0x3)
/** Date units in BCD format shift */
#define RTC_DR_DU_SHIFT   (0)
/** Date units in BCD format mask */
#define RTC_DR_DU_MASK    (0xf)
/**@}*/

/** @defgroup rtc_prer_values RTC prescaler register (RTC_PRER) values
 * @ingroup rtc_registers
@{*/
/** Async prescaler factor shift */
#define RTC_PRER_PREDIV_A_SHIFT   (16)
/** Async prescaler factor mask */
#define RTC_PRER_PREDIV_A_MASK    (0x7f)
/** Sync prescaler factor shift */
#define RTC_PRER_PREDIV_S_SHIFT   (0)
/** Sync prescaler factor mask */
#define RTC_PRER_PREDIV_S_MASK    (0x7fff)
/**@}*/

/** @defgroup rtc_tstr_values RTC time stamp time register (RTC_TSTR) values
 * @ingroup rtc_registers
@{*/
#define RTC_TSTR_PM               (1<<22)
#define RTC_TSTR_HT_SHIFT         (20)
#define RTC_TSTR_HT_MASK          (0x3)
#define RTC_TSTR_HU_SHIFT         (16)
#define RTC_TSTR_HU_MASK          (0xf)
#define RTC_TSTR_MNT_SHIFT        (12)
#define RTC_TSTR_MNT_MASK         (0x7)
#define RTC_TSTR_MNU_SHIFT        (8)
#define RTC_TSTR_MNU_MASK         (0xf)
#define RTC_TSTR_ST_SHIFT         (4)
#define RTC_TSTR_ST_MASK          (0x7)
#define RTC_TSTR_SU_SHIFT         (0)
#define RTC_TSTR_SU_MASK          (0xf)
/**@}*/

enum rtc_weekday {
	RTC_DR_WDU_MON = 0x01,
	RTC_DR_WDU_TUE,
	RTC_DR_WDU_WED,
	RTC_DR_WDU_THU,
	RTC_DR_WDU_FRI,
	RTC_DR_WDU_SAT,
	RTC_DR_WDU_SUN,
};

BEGIN_DECLS

void rtc_set_prescaler(uint32_t sync, uint32_t async);
void rtc_wait_for_synchro(void);
void rtc_lock(void);
void rtc_unlock(void);
void rtc_set_wakeup_time(uint16_t wkup_time, uint8_t rtc_cr_wucksel);
void rtc_set_init_flag(void);
void rtc_clear_init_flag(void);
bool rtc_init_flag_is_ready(void);
void rtc_wait_for_init_ready(void);
void rtc_set_bypass_shadow_register(void);
void rtc_enable_bypass_shadow_register(void);
void rtc_disable_bypass_shadow_register(void);
void rtc_set_am_format(void);
void rtc_set_pm_format(void);
void rtc_calendar_set_year(uint8_t year);
void rtc_calendar_set_weekday(enum rtc_weekday rtc_dr_wdu);
void rtc_calendar_set_month(uint8_t month);
void rtc_calendar_set_day(uint8_t day);
void rtc_calendar_set_date(uint8_t year, uint8_t month, uint8_t day, enum rtc_weekday rtc_dr_wdu);
void rtc_time_set_hour(uint8_t hour, bool use_am_notation);
void rtc_time_set_minute(uint8_t minute);
void rtc_time_set_second(uint8_t second);
void rtc_time_set_time(uint8_t hour, uint8_t minute, uint8_t second, bool use_am_notation);

END_DECLS
/**@}*/

#endif  /* RTC2_H */
/** @cond */
#else
#warning "rtc_common_all.h should not be included explicitly, only via rtc.h"
#endif
/** @endcond */
