Action()
{
	lr_start_transaction("UC_02_BuyTickets");

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

		web_reg_find("Text=<title>Web Tours</title>", LAST);
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

	lr_start_transaction("goToFlights");

		web_reg_find("Text=<title>Web Tours</title>", LAST);
		web_reg_find("Text=Find Flight", LAST);
		web_reg_save_param("advanceDiscount", "LB=input type=\"hidden\" name=\"advanceDiscount\" value=\"", "RB=\"", LAST);

		web_url("Search Flights Button", 
			"URL=http://127.0.0.1:1080/cgi-bin/welcome.pl?page=search", 
			"TargetFrame=body", 
			"Resource=0", 
			"RecContentType=text/html", 
			"Referer=http://127.0.0.1:1080/cgi-bin/nav.pl?page=menu&in=home", 
			"Snapshot=t3.inf", 
			"Mode=HTML", 
			LAST);

	lr_end_transaction("goToFlights",LR_AUTO);

	lr_think_time(5);

	lr_start_transaction("selectFlight");

		web_reg_find("Text=<title>Flight Selections</title>", LAST);
		web_reg_find("Text=Flight departing from <B>{depart}</B> to <B>{arrive}</B> on <B>{departDate}</B>", LAST);
		web_reg_save_param("outboundFlightArray", "LB=input type=\"radio\" name=\"outboundFlight\" value=\"", "RB=\"", "Ord=ALL", LAST);
		web_reg_save_param("returnFlightArray", "LB=input type=\"radio\" name=\"returnFlight\" value=\"", "RB=\"", "Ord=ALL", "NotFound=WARNING", LAST);

		web_submit_data("reservations.pl", 
			"Action=http://127.0.0.1:1080/cgi-bin/reservations.pl", 
			"Method=POST", 
			"TargetFrame=", 
			"RecContentType=text/html", 
			"Referer=http://127.0.0.1:1080/cgi-bin/reservations.pl?page=welcome", 
			"Snapshot=t4.inf", 
			"Mode=HTML", 
			ITEMDATA, 
			"Name=advanceDiscount", "Value={advanceDiscount}", ENDITEM, 
			"Name=depart", "Value={depart}", ENDITEM, 
			"Name=departDate", "Value={departDate}", ENDITEM, 
			"Name=arrive", "Value={arrive}", ENDITEM, 
			"Name=returnDate", "Value={returnDate}", ENDITEM, 
			"Name=numPassengers", "Value={numPassengers}", ENDITEM, 
			"Name=seatPref", "Value={seatPref}", ENDITEM, 
			"Name=seatType", "Value={seatType}", ENDITEM, 
			"Name=roundtrip", "Value={roundtrip}", ENDITEM, 
			"Name=findFlights.x", "Value={findFlights_x}", ENDITEM, 
			"Name=findFlights.y", "Value={findFlights_y}", ENDITEM, 
			"Name=.cgifields", "Value=roundtrip", ENDITEM, 
			"Name=.cgifields", "Value=seatType", ENDITEM, 
			"Name=.cgifields", "Value=seatPref", ENDITEM, 
			LAST);

		lr_save_string(lr_paramarr_random("outboundFlightArray"), "outboundFlight");
		if (lr_paramarr_len("returnFlightArray") > 0) {
			lr_save_string(lr_paramarr_random("returnFlightArray"), "returnFlight");
		} else {
			lr_save_string("", "returnFlight");
		}

	lr_end_transaction("selectFlight",LR_AUTO);

	lr_think_time(5);

	lr_start_transaction("reserveFlight");

		web_reg_find("Text=<title>Flight Reservation</title>", LAST);
		web_reg_find("Text=Payment Details", LAST);
		web_reg_find("Text={firstName} {lastName}", LAST);
		web_reg_find("Text={address1}", LAST);
		web_reg_find("Text={address2}", LAST);

		web_submit_data("reservations.pl_2", 
			"Action=http://127.0.0.1:1080/cgi-bin/reservations.pl", 
			"Method=POST", 
			"TargetFrame=", 
			"RecContentType=text/html", 
			"Referer=http://127.0.0.1:1080/cgi-bin/reservations.pl", 
			"Snapshot=t5.inf", 
			"Mode=HTML", 
			ITEMDATA, 
			"Name=outboundFlight", "Value={outboundFlight}", ENDITEM, 
			"Name=returnFlight", "Value={returnFlight}", ENDITEM, 
			"Name=numPassengers", "Value={numPassengers}", ENDITEM, 
			"Name=advanceDiscount", "Value={advanceDiscount}", ENDITEM, 
			"Name=seatType", "Value={seatType}", ENDITEM, 
			"Name=seatPref", "Value={seatPref}", ENDITEM, 
			"Name=reserveFlights.x", "Value={reserveFlights_x}", ENDITEM, 
			"Name=reserveFlights.y", "Value={reserveFlights_y}", ENDITEM, 
			LAST);

	lr_end_transaction("reserveFlight",LR_AUTO);

	lr_think_time(5);

	lr_start_transaction("pay");

		web_reg_find("Text=<title>Reservation Made!</title>", LAST);
		web_reg_find("Text=from {depart} to {arrive}.", LAST);
		web_reg_find("Text={firstName}{lastName}'s", LAST);
		web_reg_find("Text={seatType}", LAST);
		web_reg_find("Text={creditCard}", LAST);

		web_submit_data("reservations.pl_3", 
			"Action=http://127.0.0.1:1080/cgi-bin/reservations.pl", 
			"Method=POST", 
			"TargetFrame=", 
			"RecContentType=text/html", 
			"Referer=http://127.0.0.1:1080/cgi-bin/reservations.pl", 
			"Snapshot=t6.inf", 
			"Mode=HTML", 
			ITEMDATA, 
			"Name=firstName", "Value={firstName}", ENDITEM, 
			"Name=lastName", "Value={lastName}", ENDITEM, 
			"Name=address1", "Value={address1}", ENDITEM, 
			"Name=address2", "Value={address2}", ENDITEM, 
			"Name=pass1", "Value={firstName} {lastName}", ENDITEM, 
			"Name=pass2", "Value={pass2}", ENDITEM, 
			"Name=pass3", "Value={pass3}", ENDITEM, 
			"Name=pass4", "Value={pass4}", ENDITEM, 
			"Name=pass5", "Value={pass5}", ENDITEM, 
			"Name=creditCard", "Value={creditCard}", ENDITEM, 
			"Name=expDate", "Value={expDate}", ENDITEM, 
			"Name=oldCCOption", "Value=", ENDITEM, 
			"Name=numPassengers", "Value={numPassengers}", ENDITEM, 
			"Name=seatType", "Value={seatType}", ENDITEM, 
			"Name=seatPref", "Value={seatPref}", ENDITEM, 
			"Name=outboundFlight", "Value={outboundFlight}", ENDITEM, 
			"Name=advanceDiscount", "Value=0", ENDITEM, 
			"Name=returnFlight", "Value={returnFlight}", ENDITEM, 
			"Name=JSFormSubmit", "Value=off", ENDITEM, 
			"Name=buyFlights.x", "Value={buyFlights_x}", ENDITEM, 
			"Name=buyFlights.y", "Value={buyFlights_y}", ENDITEM, 
			"Name=.cgifields", "Value=saveCC", ENDITEM, 
			LAST);

	lr_end_transaction("pay",LR_AUTO);

	lr_think_time(5);

	lr_start_transaction("signOff");

		web_reg_find("Text=<title>Web Tours</title>", LAST);
		web_reg_find("Text=Welcome to the Web Tours site.", LAST);

		web_url("SignOff Button", 
			"URL=http://127.0.0.1:1080/cgi-bin/welcome.pl?signOff=1", 
			"TargetFrame=body", 
			"Resource=0", 
			"RecContentType=text/html", 
			"Referer=http://127.0.0.1:1080/cgi-bin/nav.pl?page=menu&in=flights", 
			"Snapshot=t7.inf", 
			"Mode=HTML", 
			LAST);

	lr_end_transaction("signOff",LR_AUTO);

	lr_end_transaction("UC_02_BuyTickets", LR_AUTO);

	return 0;
}