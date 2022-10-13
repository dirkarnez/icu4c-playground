// #include "unicode/utypes.h"

// #include "unicode/umachine.h"
// #include "unicode/tblcoll.h"
// #include "unicode/coleitr.h"
// #include "unicode/ures.h"
// #include "unicode/ustring.h"
// #include "unicode/decimfmt.h"
// #include "unicode/udata.h"
// #include "unicode/rbnf.h"
// #include <iostream>

// // #include "cmemory.h"
// // #include "putilimp.h"
// // #include "testutil.h"

// #include <unicode/unistr.h>
// #include <unicode/ustdio.h>
// #include <unicode/brkiter.h>
// #include <cstdlib>
// #include "unicode/localebuilder.h"
// #include "unicode/localpointer.h"
// #include "unicode/decimfmt.h"
// #include "unicode/ucurr.h"
// #include "unicode/smpdtfmt.h"
// #include "unicode/strenum.h"
// #include "unicode/dtfmtsym.h"
// #include "unicode/brkiter.h"
// #include "unicode/coll.h"
// #include "unicode/ustring.h"
// #include "unicode/std_string.h"
// #include "unicode/numberformatter.h"

// using namespace icu;

// void printUnicodeString(UFILE *out, const UnicodeString &s)
// {
//     UnicodeString other = s;
//     u_fprintf(out, "\"%S\"", other.getTerminatedBuffer());
// }

// int main(void)
// {
//     UFILE *out;
//     out = u_finit(stdout, NULL, NULL);
//     if (!out)
//     {
//         fprintf(stderr, "Could not initialize (finit()) over stdout! \n");
//         return 1;
//     }

//     // createInstance(errorCode)
//     // Locale::getDefault(), UNUM_DECIMAL,

//     std::cin.get();
//     return 0;
// }


#define __STDC_FORMAT_MACROS 1
#define U_STATIC_IMPLEMENTATION 1
#include <inttypes.h>

#include "unicode/unistr.h"
#include "unicode/fmtable.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace icu;

enum {
    U_SPACE=0x20,
    U_DQUOTE=0x22,
    U_COMMA=0x2c,
    U_LEFT_SQUARE_BRACKET=0x5b,
    U_BACKSLASH=0x5c,
    U_RIGHT_SQUARE_BRACKET=0x5d,
    U_SMALL_U=0x75
};

// Verify that a UErrorCode is successful; exit(1) if not
void check(UErrorCode& status, const char* msg) {
    if (U_FAILURE(status)) {
        printf("ERROR: %s (%s)\n", u_errorName(status), msg);
        std::cin.get();
        exit(1);
    }
    // printf("Ok: %s\n", msg);
}
                                                      
// Append a hex string to the target
static UnicodeString& appendHex(uint32_t number, 
                         int8_t digits, 
                         UnicodeString& target) {
    uint32_t digit;
    while (digits > 0) {
        digit = (number >> ((--digits) * 4)) & 0xF;
        target += (UChar)(digit < 10 ? 0x30 + digit : 0x41 - 10 + digit);
    }
    return target;
}

// Replace nonprintable characters with unicode escapes
UnicodeString escape(const UnicodeString &source) {
    int32_t i;
    UnicodeString target;
    target += (UChar)U_DQUOTE;
    for (i=0; i<source.length(); ++i) {
        UChar ch = source[i];
        if (ch < 0x09 || (ch > 0x0D && ch < 0x20) || ch > 0x7E) {
            (target += (UChar)U_BACKSLASH) += (UChar)U_SMALL_U;
            appendHex(ch, 4, target);
        } else {
            target += ch;
        }
    }
    target += (UChar)U_DQUOTE;
    return target;
}

// Print the given string to stdout using the UTF-8 converter
void uprintf(const UnicodeString &str) {
    char stackBuffer[100];
    char *buf = 0;

    int32_t bufLen = str.extract(0, 0x7fffffff, stackBuffer, sizeof(stackBuffer), "UTF-8");
    if(bufLen < sizeof(stackBuffer)) {
        buf = stackBuffer;
    } else {
        buf = new char[bufLen + 1];
        bufLen = str.extract(0, 0x7fffffff, buf, bufLen + 1, "UTF-8");
    }
    printf("%s", buf);
    if(buf != stackBuffer) {
        delete[] buf;
    }
}

// Create a display string for a formattable
UnicodeString formattableToString(const Formattable& f) {
    switch (f.getType()) {
    case Formattable::kDate:
        // TODO: Finish implementing this
        return UNICODE_STRING_SIMPLE("Formattable_DATE_TBD");
    case Formattable::kDouble:
        {
            char buf[256];
            sprintf(buf, "%gD", f.getDouble());
            return UnicodeString(buf, "");
        }
    case Formattable::kLong:
        {
            char buf[256];
            sprintf(buf, "%" PRId32 "L", f.getLong());
            return UnicodeString(buf, "");
        }
    case Formattable::kInt64:
        {
            char buf[256];
            sprintf(buf, "%" PRId64 "L", f.getInt64());
            return UnicodeString(buf, "");
        }
    case Formattable::kString:
        return UnicodeString((UChar)U_DQUOTE).append(f.getString()).append((UChar)U_DQUOTE);
    case Formattable::kArray:
        {
            int32_t i, count;
            const Formattable* array = f.getArray(count);
            UnicodeString result((UChar)U_LEFT_SQUARE_BRACKET);
            for (i=0; i<count; ++i) {
                if (i > 0) {
                    (result += (UChar)U_COMMA) += (UChar)U_SPACE;
                }
                result += formattableToString(array[i]);
            }
            result += (UChar)U_RIGHT_SQUARE_BRACKET;
            return result;
        }
    default:
        return UNICODE_STRING_SIMPLE("INVALID_Formattable");
    }
}

#include "unicode/utypes.h"
#include "unicode/unistr.h"
#include "unicode/numfmt.h"
#include "unicode/dcfmtsym.h"
#include "unicode/decimfmt.h"
#include "unicode/locid.h"
#include "unicode/uclean.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <iostream>

#include "unicode/unistr.h"
#include "unicode/fmtable.h"
#include "unicode/numberformatter.h"
using namespace icu;


/**
 * Test using various numbering systems and numbering system keyword.
 */
typedef struct {
    const char *localeName;
    double      value;
    UBool        isRBNF;
    const char *expectedResult;
} TestNumberingSystemItem;

void TestNumberingSystems() {

    const TestNumberingSystemItem DATA[] = {
        // { "en_US@numbers=thai", 1234.567, false, "\\u0E51,\\u0E52\\u0E53\\u0E54.\\u0E55\\u0E56\\u0E57" },
        // { "en_US@numbers=hebr", 5678.0, true, "\\u05D4\\u05F3\\u05EA\\u05E8\\u05E2\\u05F4\\u05D7" },
        // { "en_US@numbers=arabext", 1234.567, false, "\\u06F1\\u066c\\u06F2\\u06F3\\u06F4\\u066b\\u06F5\\u06F6\\u06F7" },
        // { "ar_EG", 1234.567, false, "\\u0661\\u066C\\u0662\\u0663\\u0664\\u066b\\u0665\\u0666\\u0667" },
        // { "th_TH@numbers=traditional", 1234.567, false, "\\u0E51,\\u0E52\\u0E53\\u0E54.\\u0E55\\u0E56\\u0E57" }, // fall back to native per TR35
        // { "ar_MA", 1234.567, false, "1.234,567" },
        // { "en_US@numbers=hanidec", 1234.567, false, "\\u4e00,\\u4e8c\\u4e09\\u56db.\\u4e94\\u516d\\u4e03" },
        // { "ta_IN@numbers=native", 1234.567, false, "\\u0BE7,\\u0BE8\\u0BE9\\u0BEA.\\u0BEB\\u0BEC\\u0BED" },
        // { "ta_IN@numbers=traditional", 1235.0, true, "\\u0BF2\\u0BE8\\u0BF1\\u0BE9\\u0BF0\\u0BEB" },
        // { "ta_IN@numbers=finance", 1234.567, false, "1,234.567" }, // fall back to default per TR35
        // { "zh_TW@numbers=native", 1234.567, false, "\\u4e00,\\u4e8c\\u4e09\\u56db.\\u4e94\\u516d\\u4e03" },
        // { "zh_TW@numbers=traditional", 1234.567, true, "\\u4E00\\u5343\\u4E8C\\u767E\\u4E09\\u5341\\u56DB\\u9EDE\\u4E94\\u516D\\u4E03" },
        { "zh_TW@numbers=finance", 1234.567, true, "\\u58F9\\u4EDF\\u8CB3\\u4F70\\u53C3\\u62FE\\u8086\\u9EDE\\u4F0D\\u9678\\u67D2" },
        { NULL, 0, false, NULL }
    };

    UErrorCode ec;

    const TestNumberingSystemItem *item;
    for (item = DATA; item->localeName != NULL; item++) {
        ec = U_ZERO_ERROR;
        Locale loc = Locale::createFromName(item->localeName);

        NumberFormat *origFmt = NumberFormat::createInstance(loc,ec);
        // if (U_FAILURE(ec)) {
        //     dataerrln("FAIL: getInstance(%s) - %s", item->localeName, u_errorName(ec));
        //     continue;
        // }
        // Clone to test ticket #10682
        NumberFormat *fmt = origFmt->clone();
        delete origFmt;

        UErrorCode status = U_ZERO_ERROR;


        UnicodeString saw;
        FieldPosition pos;
        fmt->format(item->value, saw, pos, status);
        uprintf(saw);

        delete fmt;
    }
}

// static void
// showCurrencyFormatting(UBool useICU26API);


/**
 * Sample code for the C++ API to NumberFormat.
 */
void cppapi() {
    Locale us = Locale::getChina();
    UErrorCode status = U_ZERO_ERROR;
    
    // Create a number formatter for the US locale
    NumberFormat *fmt = NumberFormat::createInstance(us, status);
    check(status, "NumberFormat::createInstance");

    // Parse a string.  The string uses the digits '0' through '9'
    // and the decimal separator '.', standard in the US locale
    UnicodeString str("9876543210.123");
    Formattable result;
    fmt->parse(str, result, status);
    check(status, "NumberFormat::parse");

    printf("NumberFormat::parse(\""); // Display the result
    uprintf(str);
    printf("\") => ");
    uprintf(formattableToString(result));
    printf("\n");

    // Take the number parsed above, and use the formatter to
    // format it.
    str.remove(); // format() will APPEND to this string
    fmt->format(result, str, status);
    check(status, "NumberFormat::format");

    printf("NumberFormat::format("); // Display the result
    uprintf(formattableToString(result));
    printf(") => \"");
    uprintf(str);
    printf("\"\n");

    delete fmt; // Release the storage used by the formatter
    
}

int main(int argc, char **argv) {
    
    UErrorCode status = U_ZERO_ERROR;
    u_init(&status);
    check(status, "NumberFormat::format");


    printf("%s output is in UTF-8\n", argv[0]);

    printf("C++ API\n");
    cppapi();

    printf("C API\n");


    // showCurrencyFormatting(false);
    // showCurrencyFormatting(true);








     Locale ulocale("zh_Hant_HK");



    // UErrorCode success = U_ZERO_ERROR;
    number::LocalizedNumberFormatter withLocale = number::NumberFormatter::withLocale(ulocale);

    for (int32_t number : {1, 123456789, -1234567})
    {
        UnicodeString myString;
        UErrorCode success = U_ZERO_ERROR;
        number::FormattedNumber a = withLocale.formatInt(number, success);
        if (U_SUCCESS(success))
        {
             UnicodeString actualString = a.toString(success);
             uprintf(actualString);
             std::cout << std::endl;
        }
        else
        {
            std::cout << "ns" << std::endl;
        }
    }

    // UErrorCode status  = U_ZERO_ERROR;
    // UParseError parseError;

    // UnicodeString numberPattern("#,##0.###");
    // RuleBasedNumberFormat rbnf(numberPattern, UnicodeString(), , parseError, status);

    // UnicodeString us;
    // rbnf.format((const Formattable)1234.56, us, status);
    // if (U_SUCCESS(status)) {
    //
    // }




TestNumberingSystems();



















    u_cleanup();    // Release any additional storage held by ICU.  

    printf("Exiting successfully\n");






    std::cin.get();
    return 0;
}
