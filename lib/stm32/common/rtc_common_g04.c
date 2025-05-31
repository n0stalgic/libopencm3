/** @addtogroup rtc_file RTC peripheral API
@ingroup peripheral_apis

@author @htmlonly &copy; @endhtmlonly 2012 Karl Palsson <karlp@tweak.net.au>

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

/**@{*/

#include <libopencm3/stm32/rtc.h>

/*---------------------------------------------------------------------------*/
/** @brief Wait for RTC registers to be synchronised with the APB1 bus

 Time and Date are accessed through shadow registers which must be synchronized
*/

void rtc_wait_for_synchro(void)
{
	/* Unlock RTC registers */
	RTC_WPR = 0xca;
	RTC_WPR = 0x53;

	RTC_ICSR &= ~(RTC_ICSR_RSF);

	while (!(RTC_ICSR & RTC_ICSR_RSF));

	/* disable write protection again */
	RTC_WPR = 0xff;
}

/*---------------------------------------------------------------------------*/
/** @brief Sets the wakeup time auto-reload value

*/
void rtc_set_wakeup_time(uint16_t wkup_time, uint8_t rtc_cr_wucksel)
{
	/* FTFM:
	 * The following sequence is required to configure or change the wakeup
	 * timer auto-reload value (WUT[15:0] in RTC_WUTR):
	 * 1. Clear WUTE in RTC_CR to disable the wakeup timer.
	 */
	RTC_CR &= ~RTC_CR_WUTE;
	/* 2. Poll WUTWF until it is set in RTC_ISR to make sure the access to
	 *    wakeup auto-reload counter and to WUCKSEL[2:0] bits is allowed.
	 *    It takes around 2 RTCCLK clock cycles (due to clock
	 *    synchronization).
	 */
	while (!((RTC_ICSR) & (RTC_ICSR_WUTWF)));
	/* 3. Program the wakeup auto-reload value WUT[15:0], and the wakeup
	 *    clock selection (WUCKSEL[2:0] bits in RTC_CR).Set WUTE in RTC_CR
	 *    to enable the timer again. The wakeup timer restarts
	 *    down-counting.
	 */
	RTC_WUTR = wkup_time;
	RTC_CR &= ~(RTC_CR_WUCLKSEL_MASK << RTC_CR_WUCLKSEL_SHIFT);
	RTC_CR |= (rtc_cr_wucksel << RTC_CR_WUCLKSEL_SHIFT);
	RTC_CR |= RTC_CR_WUTE;
}

/*---------------------------------------------------------------------------*/
/** @brief Sets the initialization flag

@details Requires unlocking backup domain write protection (PWR_CR_DBP)
*/
void rtc_set_init_flag(void)
{
	RTC_ICSR |= RTC_ICSR_INIT;
}

/*---------------------------------------------------------------------------*/
/** @brief Clears (resets) the initialization flag

@details Requires unlocking backup domain write protection (PWR_CR_DBP)
*/
void rtc_clear_init_flag(void)
{
	RTC_ICSR &= ~RTC_ICSR_INIT;
}

/*---------------------------------------------------------------------------*/
/** @brief Returns if the RTC_ISR init flag RTC_ISR_INITF is set

@details Requires unlocking backup domain write protection (PWR_CR_DBP)
*/
bool rtc_init_flag_is_ready(void)
{
	return (RTC_ICSR & RTC_ICSR_INITF);
}

/*---------------------------------------------------------------------------*/
/** @brief Clears wakeup timer interrupt

@details Requires unlocking backup domain write protection (PWR_CR_DBP)
*/
void rtc_clear_wakeup_interrupt(void)
{
	RTC_SCR |= RTC_SCR_CWUTF;
}

/*---------------------------------------------------------------------------*/
/** @brief Enable wakeup timer interrupt

@details Requires unlocking backup domain write protection (PWR_CR_DBP)
*/
void rtc_enable_wakeup_timer_interrupt(void)
{
	RTC_CR |= RTC_CR_WUTIE;
}

/*---------------------------------------------------------------------------*/
/** @brief Disable wakeup timer interrupt

@details Requires unlocking backup domain write protection (PWR_CR_DBP)
*/
void rtc_disable_wakeup_timer_interrupt(void)
{
	RTC_CR &= ~(RTC_CR_WUTIE);
}

/*---------------------------------------------------------------------------*/
/** @brief Enable auto-reloading wakeup timer

@details Requires unlocking backup domain write protection (PWR_CR_DBP)
*/
void rtc_enable_wakeup_timer(void)
{
	RTC_CR |= RTC_CR_WUTE;
}

/*---------------------------------------------------------------------------*/
/** @brief Disable auto-reloading wakeup timer

@details Requires unlocking backup domain write protection (PWR_CR_DBP)
*/
void rtc_disable_wakeup_timer(void)
{
	RTC_CR &= ~RTC_CR_WUTE;
}

/*---------------------------------------------------------------------------*/
/** @brief Wait for wakeup timer IRQ to clear in the RTC_SR register

@details Requires unlocking backup domain write protection (PWR_CR_DBP)
*/
void rtc_wait_for_wakeup_timer_irq_clear(void)
{
	while ((RTC_SR & RTC_SR_WUTF) != 0);
}