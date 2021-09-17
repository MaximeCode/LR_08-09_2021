Action()
{
	lr_start_transaction("UC_04_CancelRandomTicket");

	lr_start_transaction("openWebTours");

		web_add_auto_header("Accept-Language", "ru-RU,ru;q=0.9,en-US;q=0.8,en;q=0.7");
		web_reg_find("Text=<title>Web Tours</title>", LAST);
		web_reg_find("Text=Welcome to the Web Tours site.", LAST);
		web_reg_save_param("userSession", "LB=<input type=\"hidden\" name=\"userSession\" value=\"", "RB=\"/>", LAST);

		web_url("WebTours", 
			"URL=http://127.0.0.1:1080/WebTours/", 
			"TargetFrame=", 
			"Resource=0", 
			"RecContentType=text/html", 
			"Referer=", 
			"Snapshot=t1.inf", 
			"Mode=HTML", 
			LAST);

		web_set_sockets_option("SSL_VERSION", "2&3");

	lr_end_transaction("openWebTours", LR_AUTO);

	lr_think_time(5);

	lr_start_transaction("login");

		web_reg_find("Text=<title>Welcome to Web Tours</title>", LAST);
		web_reg_find("Text=Welcome, <b>{username}</b>, to the Web Tours reservation pages.", LAST);

		web_submit_data("login.pl",
		"Action=http://127.0.0.1:1080/cgi-bin/login.pl",
		"Method=POST",
		"TargetFrame=body",
		"RecContentType=text/html",
		"Referer=http://127.0.0.1:1080/cgi-bin/nav.pl?in=home",
		"Snapshot=t2.inf",
		"Mode=HTML",
		ITEMDATA,
		"Name=userSession", "Value={userSession}", ENDITEM,
		"Name=username", "Value={username}", ENDITEM,
		"Name=password", "Value={password}", ENDITEM,
		"Name=login.x", "Value={login_x}", ENDITEM,
		"Name=login.y", "Value={login_y}", ENDITEM,
		"Name=JSFormSubmit", "Value=off", ENDITEM,
		LAST);

	lr_end_transaction("login",LR_AUTO);

	lr_think_time(5);

	lr_start_transaction("goToItinerary");

		web_reg_find("Text=<title>Flights List</title>", LAST);
		web_reg_find("Fail=Found", "Text=No flights have been reserved.", LAST);
		web_reg_save_param("nameArray", "LB=input type=\"checkbox\" name=\"", "RB=\"", "Ord=ALL", LAST);
		web_reg_save_param("flightIdArray", "LB=input type=\"hidden\" name=\"flightID\" value=\"", "RB=\"", "Ord=ALL", LAST);
	
		web_url("Itinerary Button",
			"URL=http://127.0.0.1:1080/cgi-bin/welcome.pl?page=itinerary", 
			"TargetFrame=body", 
			"Resource=0", 
			"RecContentType=text/html", 
			"Referer=http://127.0.0.1:1080/cgi-bin/nav.pl?page=menu&in=home", 
			"Snapshot=t3.inf", 
			"Mode=HTML", 
			LAST);

		lr_save_string(lr_paramarr_random("nameArray"), "name");
		lr_save_int(lr_paramarr_len("nameArray"), "len");

	lr_end_transaction("goToItinerary",LR_AUTO);

	lr_think_time(5);

	lr_start_transaction("cancel");

		web_reg_find("Text=<title>Flights List</title>", LAST);
		web_reg_find("Fail=Found", "Text=Unfortunately, we could not delete your entire itinerary", LAST);
		// ѕровер€ем, что номер последней брони изменилс€.
		web_reg_find("Fail=Found", "Text=input type\=\"checkbox\" name=\"{len}\"", LAST);
		// TODO —делать проверку отсутстви€ id брони после удалени€.

		// Ўаг работает, если в списке до 10 броней.
		web_submit_data("itinerary.pl",
		"Action=http://127.0.0.1:1080/cgi-bin/itinerary.pl",
		"Method=POST",
		"TargetFrame=",
		"RecContentType=text/html",
		"Referer=http://127.0.0.1:1080/cgi-bin/itinerary.pl",
		"Snapshot=t4.inf",
		"Mode=HTML",
		ITEMDATA,
		"Name={name}", "Value=on", ENDITEM,
		"Name=flightID", "Value={flightIdArray_1}", ENDITEM,
		"Name=flightID", "Value={flightIdArray_2}", ENDITEM,
		"Name=flightID", "Value={flightIdArray_3}", ENDITEM,
		"Name=flightID", "Value={flightIdArray_4}", ENDITEM,
		"Name=flightID", "Value={flightIdArray_5}", ENDITEM,
		"Name=flightID", "Value={flightIdArray_6}", ENDITEM,
		"Name=flightID", "Value={flightIdArray_7}", ENDITEM,
		"Name=flightID", "Value={flightIdArray_8}", ENDITEM,
		"Name=flightID", "Value={flightIdArray_9}", ENDITEM,
		"Name=flightID", "Value={flightIdArray_10}", ENDITEM,
		"Name=removeFlights.x", "Value={removeFlights_x}", ENDITEM,
		"Name=removeFlights.y", "Value={removeFlights_y}", ENDITEM,
		LAST);

	lr_end_transaction("cancel",LR_AUTO);

	lr_think_time(5);

	lr_start_transaction("signOff");

		web_reg_find("Text=<title>Web Tours</title>", LAST);
		web_reg_find("Text=Welcome to the Web Tours site.", LAST);

		web_url("SignOff Button", 
			"URL=http://127.0.0.1:1080/cgi-bin/welcome.pl?signOff=1", 
			"TargetFrame=body", 
			"Resource=0", 
			"RecContentType=text/html", 
			"Referer=http://127.0.0.1:1080/cgi-bin/nav.pl?page=menu&in=itinerary", 
			"Snapshot=t5.inf", 
			"Mode=HTML", 
			LAST);

	lr_end_transaction("signOff",LR_AUTO);

	lr_end_transaction("UC_04_CancelRandomTicket", LR_AUTO);

	return 0;
}