Action()
{
	lr_start_transaction("UC_05_Login");

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

	lr_end_transaction("UC_05_Login", LR_AUTO);

	return 0;
}