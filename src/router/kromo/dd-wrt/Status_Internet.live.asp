{wan_shortproto::<% nvg("wan_proto"); %>}
{wan_status::<% nvram_status_get("status2","1"); %>&nbsp;&nbsp;<input class="button" type="button" value="<% nvram_status_get("button1","1"); %>" onclick="connect(this.form, '<% nvram_status_get("button1","0"); %>_<% nvg("wan_proto"); %>')" />}
{wan_uptime::<% get_wan_uptime("0"); %>}
{pppoe_ac_name::<% nvg("pppoe_ac_name"); %>}
{wan_3g_signal::<% nvram_status_get("wan_3g_signal"); %>}
{wan_ipaddr::<% nvram_status_get("wan_ipaddr","0"); %>}
{wan_netmask::<% nvram_status_get("wan_netmask"); %>}
{wan_gateway::<% nvram_status_get("wan_gateway"); %>}
{wan_dns0::<% nvram_status_get("wan_dns0"); %>}
{wan_dns1::<% nvram_status_get("wan_dns1"); %>}
{wan_dns2::<% nvram_status_get("wan_dns2"); %>}
{dhcp_remaining::<% dhcp_remaining_time(); %>}
{ttraff_in::<% get_totaltraff("in"); %>}
{ttraff_out::<% get_totaltraff("out"); %>}
{uptime::<% get_uptime(); %>}
{ipinfo::<% show_wanipinfo(); %>}
<% show_status("adsl"); %>
