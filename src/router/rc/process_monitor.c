
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <syslog.h>
#include <sys/stat.h>
#include <time.h>
#include <signal.h>
#include <sys/sysinfo.h>
#include <sys/time.h>
#include <shutils.h>
#include <code_pattern.h>
#include <typedefs.h>
#include <bcmnvram.h>
#include <rc.h>
#include <cy_conf.h>
#include <utils.h>

static void ntp_main(timer_t t, int arg);
extern void do_redial(timer_t t, int arg);
static int do_ntp(void);
static void check_udhcpd(timer_t t, int arg);
extern void init_event_queue(int n);
extern int timer_connect(timer_t timerid, void (*routine)(timer_t, int), int arg);

static unsigned int NTP_M_TIMER = 3600;
static unsigned int NTP_N_TIMER = 30;

static int process_monitor_main(int argc, char **argv)
{
	struct itimerspec t1, t4, t5;
	timer_t ntp1_id, ntp2_id, udhcpd_id;
	int time;
	long int leasetime = 0;

	init_event_queue(40);
	NTP_M_TIMER = nvram_default_geti("ntp_timer", 3600);
	openlog("process_monitor", LOG_PID | LOG_NDELAY, LOG_DAEMON);

	if (nvram_invmatchi("ntp_enable", 0)) {	// && check_wan_link(0) ) {

		/* 
		 * init ntp timer 
		 */

		if (nvram_geti("ntp_success") != 1 && do_ntp() != 0) {
			dd_syslog(LOG_ERR, "Last update failed, we need to re-update after %d seconds\n", NTP_N_TIMER);
			time = NTP_N_TIMER;

			memset(&t4, 0, sizeof(t4));
			t4.it_interval.tv_sec = time;
			t4.it_value.tv_sec = time;
			dd_timer_create(CLOCK_REALTIME, NULL, (timer_t *) & ntp1_id);
			dd_timer_connect(ntp1_id, ntp_main, FIRST);
			dd_timer_settime(ntp1_id, 0, &t4, NULL);
		}
		nvram_seti("ntp_success", 0);

		dd_syslog(LOG_DEBUG, "We need to re-update after %d seconds\n", NTP_M_TIMER);

		time = NTP_M_TIMER;

		memset(&t5, 0, sizeof(t5));
		t5.it_interval.tv_sec = time;
		t5.it_value.tv_sec = time;

		dd_loginfo("process_monitor", "set timer: %d seconds, callback: ntp_main()", time);

		dd_timer_create(CLOCK_REALTIME, NULL, (timer_t *) & ntp2_id);
		dd_timer_connect(ntp2_id, ntp_main, SECOND);
		dd_timer_settime(ntp2_id, 0, &t5, NULL);

	}
	printf("process_monitor..done\n");
	while (1) {
		sleep(3600);

	}

	closelog();

	return 1;
}
