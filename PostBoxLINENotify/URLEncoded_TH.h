// URL_Encode/TH.h

#ifndef URL_ENCODE_H
#define URL_ENCODE_H

#include <Arduino.h>

namespace URLEncoded {
    String Day(int day_n);
    String Month(int month_n);
    String BuddhistEra(int christian_year_n);
    String ChristianEra(int christian_year_n);
};

String GET_Message_URLEncoded(struct tm* DT_);

#endif /* URL_ENCODE_H */