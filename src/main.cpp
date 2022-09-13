
#include <unicode/unistr.h>
#include <unicode/ustdio.h>
#include <unicode/brkiter.h>
#include <cstdlib>
#include <iostream>

using namespace icu;

void printUnicodeString(UFILE *out, const UnicodeString &s) {
    UnicodeString other = s;
    u_fprintf(out, "\"%S\"", other.getTerminatedBuffer());
}

int main( void )
{
    UFILE *out;
    UErrorCode status  = U_ZERO_ERROR;
    out = u_finit(stdout, NULL, NULL);
    if(!out) {
        fprintf(stderr, "Could not initialize (finit()) over stdout! \n");
        return 1;
    }
    ucnv_setFromUCallBack(u_fgetConverter(out), UCNV_FROM_U_CALLBACK_ESCAPE,
        NULL, NULL, NULL, &status);
    if(U_FAILURE(status)) {
        u_fprintf(out, "Warning- couldn't set the substitute callback - err %s\n", u_errorName(status));
    }

    /* End Demo boilerplate */

    u_fprintf(out,"ICU Case Mapping Sample Program\n\n");
    u_fprintf(out, "C++ Case Mapping\n\n");

    UnicodeString string("This is a test");

    u_fprintf(out, "\nstring: ");
    printUnicodeString(out, string);
    string.toUpper(); /* string = "THIS IS A TEST" */
    u_fprintf(out, "\ntoUpper(): ");
    printUnicodeString(out, string);

    std::cin.get();
    return 0;
}