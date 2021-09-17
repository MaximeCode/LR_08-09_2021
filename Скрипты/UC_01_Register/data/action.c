Action()
{

	web_add_auto_header("Accept-Language", 
		"ru-RU,ru;q=0.9,en-US;q=0.8,en;q=0.7");

	web_url("welcome.pl", 
		"URL=http://127.0.0.1:1080/cgi-bin/welcome.pl?signOff=true", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://127.0.0.1:1080/WebTours/", 
		"Snapshot=t1.inf", 
		"Mode=HTML", 
		LAST);

	web_set_sockets_option("SSL_VERSION", "2&3");

	lr_think_time(68);

	lr_start_transaction("goToRegistration");

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

	lr_think_time(126);

	lr_start_transaction("completeForm");

	web_submit_data("login.pl_2", 
		"Action=http://127.0.0.1:1080/cgi-bin/login.pl", 
		"Method=POST", 
		"TargetFrame=info", 
		"RecContentType=text/html", 
		"Referer=http://127.0.0.1:1080/cgi-bin/login.pl?username=&password=&getInfo=true", 
		"Snapshot=t3.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=username", "Value=jojo55", ENDITEM, 
		"Name=password", "Value=bean55", ENDITEM, 
		"Name=passwordConfirm", "Value=bean55", ENDITEM, 
		"Name=firstName", "Value=&#1049;&#1086;&#1081;&#1086;&#1086;&#1086;", ENDITEM, 
		"Name=lastName", "Value=&#1041;&#1080;&#1085;&#1085;&#1085;", ENDITEM, 
		"Name=address1", "Value=&#1091;&#1083;&#1080;&#1094;&#1072;", ENDITEM, 
		"Name=address2", "Value=&#1075;&#1086;&#1088;&#1086;&#1076;", ENDITEM, 
		"Name=register.x", "Value=28", ENDITEM, 
		"Name=register.y", "Value=8", ENDITEM, 
		LAST);

	lr_end_transaction("completeForm",LR_AUTO);

	lr_start_transaction("finish");

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

	lr_think_time(19);

	lr_start_transaction("signOff");

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

	return 0;
}