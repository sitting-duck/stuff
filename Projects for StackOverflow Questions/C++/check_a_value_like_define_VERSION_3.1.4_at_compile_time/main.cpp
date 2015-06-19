//FUCKING GODAMN MACROS. SHIT.


//The version we are trying to check
#define VERSION 3.1.4

//If you want to stringify the result of expansion of a macro argument, you have to use two levels of macros
//source: https://gcc.gnu.org/onlinedocs/cpp/Stringification.html

#define H1(s,i,x)   (x*65599u+(uint8_t)s[(i)<strlen(s)?strlen(s)-1-(i):strlen(s)])
#define H4(s,i,x)   H1(s,i,H1(s,i+1,H1(s,i+2,H1(s,i+3,x))))
#define H16(s,i,x)  H4(s,i,H4(s,i+4,H4(s,i+8,H4(s,i+12,x))))
#define H64(s,i,x)  H16(s,i,H16(s,i+16,H16(s,i+32,H16(s,i+48,x))))
#define H256(s,i,x) H64(s,i,H64(s,i+64,H64(s,i+128,H64(s,i+192,x))))

#define HASH(s)    ((uint32_t)(H256(s,0,0)^(H256(s,0,0)>>16)))

#define xstr(s) str(s)
#define str(s) #s

#define SAME strcmp(xstr(VERSION), "3.1.4")==0

#define CORRECT_VERSION_HASH HASH("3.1.4")
#define ACTUAL_VERSION_HASH HASH(xstr(str(VERSION))
#define HAVE_CORRECT_VERSION ACTUAL_VERSION_HASH==CORRECT_VERSION_HASH
#if HAVE_CORRECT_VERSION
#define VERSION_CORRECT
#else
#define VERSION_INCORRECT
#endif

#ifdef VERSION_INCORRECT
	#error ERROR: The version is incorrect!!!!!!!!!!
#endif


#include <iostream>
#include <cstring>

//Question Source:
//http://stackoverflow.com/questions/30925756/how-to-check-a-value-like-define-version-3-1-4-at-compile-time

int main(){


	return 0;


}