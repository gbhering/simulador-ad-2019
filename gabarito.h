inline float EW(const float& lambda) {
	if ( abs(lambda-0.9) < 0.01 ) return 9.0;
	else if (lambda == 0.8 ) return 4.0;
	else if (lambda == 0.6 ) return 1.5;
	else if (lambda == 0.4 ) return 0.6667;
	else if (lambda == 0.2 ) return 0.25;
	else return 0.0;
}
inline float VW(const float& lambda, const bool& fcfs = true) {
	if ( abs(lambda-0.9) < 0.01 && fcfs ) return 99.0;
	else if ( abs(lambda-0.9) < 0.01 && !fcfs ) return 1719.0;
	else if (lambda == 0.8 && fcfs ) return 184.0;
	else if (lambda == 0.8 && !fcfs ) return 1719.0;
	else if (lambda == 0.6 && fcfs ) return 5.25;
	else if (lambda == 0.6 && !fcfs ) return 16.5;
	else if (lambda == 0.4 && fcfs ) return 1.7778;
	else if (lambda == 0.4 && !fcfs ) return 3.2592;
	else if (lambda == 0.2 && fcfs ) return 0.5625;
	else if (lambda == 0.2 && !fcfs ) return 0.7188;
	else return 0.0;
}
inline float ENq(const float& lambda) {
	if ( abs(lambda-0.9) < 0.01 ) return 8.1;
	else if ( abs(lambda-0.8) < 0.01 ) return 3.2;
	else if ( abs(lambda-0.6) < 0.01 ) return 0.9;
	else if (lambda == 0.4 ) return 0.2666;
	else if (lambda == 0.2 ) return 0.05;
	else return 0.0;
}
inline float VNq(const float& lambda) {
	if ( abs(lambda-0.9) < 0.01 ) return 88.29;
	else if ( abs(lambda-0.8) < 0.01 ) return 18.56;
	else if ( abs(lambda-0.6) < 0.01 ) return 2.79;
	else if ( abs(lambda-0.4) < 0.01 ) return 0.5511;
	else if ( abs(lambda-0.2) < 0.01 ) return 0.0725;	
	else return 0.0;
}