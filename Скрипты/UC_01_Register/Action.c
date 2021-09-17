Action()
{
	lr_start_transaction("UC_01_Register");

	lr_start_transaction("openWebTours");

		web_add_auto_header("Accept-Language", "ru-RU,ru;q=0.9,en-US;q=0.8,en;q=0.7");
		web_reg_find("Text=<title>Web Tours</title>", LAST);
		web_reg_find("Text=Welcome to the Web Tours site.", LAST);

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

	lr_start_transaction("goToRegistration");

	web_reg_find("Text=<title>User Information</title>",	LAST);
	web_reg_find("Text=Customer Profile", LAST);

		web_url("login.pl", 
			"URL=http://127.0.0.1:1080/cgi-bin/login.pl?username=&password=&getInfo=true", 
			"TargetFrame=body", 
			"Resource=0", 
			"RecContentType=text/html", 
			"Referer=http://127.0.0.1:1080/WebTours/home.html", 
			"Snapshot=t2.inf", 
			"Mode=HTML", 
			LAST);

	lr_end_transaction("goToRegistration",LR_AUTO);

	lr_think_time(5);

	lr_start_transaction("completeForm");

		web_reg_find("Text=<title>Welcome to Web Tours</title>", LAST);
		web_reg_find("Text=Thank you, <b>{username}</b>, for registering and welcome to the Web Tours family.", LAST);

		web_submit_data("login.pl_2", 
			"Action=http://127.0.0.1:1080/cgi-bin/login.pl", 
			"Method=POST", 
			"TargetFrame=info", 
			"RecContentType=text/html", 
			"Referer=http://127.0.0.1:1080/cgi-bin/login.pl?username=&password=&getInfo=true", 
			"Snapshot=t3.inf", 
			"Mode=HTML", 
			ITEMDATA, 
			"Name=username", "Value={username}", ENDITEM, 
			"Name=password", "Value={password}", ENDITEM, 
			"Name=passwordConfirm", "Value={password}", ENDITEM, 
			"Name=firstName", "Value={firstName}", ENDITEM, 
			"Name=lastName", "Value={lastName}", ENDITEM, 
			"Name=address1", "Value={address1}", ENDITEM, 
			"Name=address2", "Value={address2}", ENDITEM, 
			"Name=register.x", "Value={register_x}", ENDITEM, 
			"Name=register.y", "Value={register_y}", ENDITEM, 
			LAST);

	lr_end_transaction("completeForm",LR_AUTO);

	lr_think_time(5);

	lr_start_transaction("finish");

		web_reg_find("Text=<title>Web Tours</title>", LAST);
		web_reg_find("Text=Welcome, <b>{username}</b>, to the Web Tours reservation pages.",	LAST);

		web_url("button_next.gif", 
			"URL=http://127.0.0.1:1080/cgi-bin/welcome.pl?page=menus", 
			"TargetFrame=body", 
			"Resource=0", 
			"RecContentType=text/html", 
			"Referer=http://127.0.0.1:1080/cgi-bin/login.pl", 
			"Snapshot=t4.inf", 
			"Mode=HTML", 
			LAST);

	lr_end_transaction("finish",LR_AUTO);

	lr_think_time(5);

	lr_start_transaction("signOff");

		web_reg_find("Text=<title>Web Tours</title>", LAST);
		web_reg_find("Text=Welcome to the Web Tours site.", LAST);

		web_url("SignOff Button", 
			"URL=http://127.0.0.1:1080/cgi-bin/welcome.pl?signOff=1", 
			"TargetFrame=body", 
			"Resource=0", 
			"RecContentType=text/html", 
			"Referer=http://127.0.0.1:1080/cgi-bin/nav.pl?page=menu&in=home", 
			"Snapshot=t5.inf", 
			"Mode=HTML", 
			LAST);

	lr_end_transaction("signOff",LR_AUTO);	

	lr_end_transaction("UC_01_Register", LR_AUTO);

	return 0;
}