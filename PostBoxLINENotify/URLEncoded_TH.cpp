// URL_Encode/TH.cpp

#include "URLEncoded_TH.h"

String DAY[] = {
    "%E0%B8%A7%E0%B8%B1%E0%B8%99%E0%B8%AD%E0%B8%B2%E0%B8%97%E0%B8%B4%E0%B8%95%E0%B8%A2%E0%B9%8C",// 1 วันอาทิตย์ - Sunday
    "%E0%B8%A7%E0%B8%B1%E0%B8%99%E0%B8%88%E0%B8%B1%E0%B8%99%E0%B8%97%E0%B8%A3%E0%B9%8C",// 2 วันจันทร์ - Monday
    "%E0%B8%A7%E0%B8%B1%E0%B8%99%E0%B8%AD%E0%B8%B1%E0%B8%87%E0%B8%84%E0%B8%B2%E0%B8%A3",// 3 วันอังคาร - Tuesday
    "%E0%B8%A7%E0%B8%B1%E0%B8%99%E0%B8%9E%E0%B8%B8%E0%B8%98",// 4 วันพุธ - Wednesday
    "%E0%B8%A7%E0%B8%B1%E0%B8%99%E0%B8%9E%E0%B8%A4%E0%B8%AB%E0%B8%B1%E0%B8%AA%E0%B8%9A%E0%B8%94%E0%B8%B5",// 5 วันพฤหัสบดี - Thursday
    "%E0%B8%A7%E0%B8%B1%E0%B8%99%E0%B8%A8%E0%B8%B8%E0%B8%81%E0%B8%A3%E0%B9%8C",// 6 วันศุกร์ - Friday
    "%E0%B8%A7%E0%B8%B1%E0%B8%99%E0%B9%80%E0%B8%AA%E0%B8%B2%E0%B8%A3%E0%B9%8C"// 7 วันเสาร์ - Saturday
};

String MONTH[] = {
    "%E0%B8%A1%E0%B8%81%E0%B8%A3%E0%B8%B2%E0%B8%84%E0%B8%A1",// 1 มกราคม - January 31
    "%E0%B8%81%E0%B8%B8%E0%B8%A1%E0%B8%A0%E0%B8%B2%E0%B8%9E%E0%B8%B1%E0%B8%99%E0%B8%98%E0%B9%8C",// 2 กุมภาพันธ์ - February 28/29
    "%E0%B8%A1%E0%B8%B5%E0%B8%99%E0%B8%B2%E0%B8%84%E0%B8%A1",// 3 มีนาคม - March 31
    "%E0%B9%80%E0%B8%A1%E0%B8%A9%E0%B8%B2%E0%B8%A2%E0%B8%99",// 4 เมษายน - April 30
    "%E0%B8%9E%E0%B8%A4%E0%B8%A9%E0%B8%A0%E0%B8%B2%E0%B8%84%E0%B8%A1",// 5 พฤษภาคม - May 31
    "%E0%B8%A1%E0%B8%B4%E0%B8%96%E0%B8%B8%E0%B8%99%E0%B8%B2%E0%B8%A2%E0%B8%99",// 6 มิถุนายน - June 30
    "%E0%B8%81%E0%B8%A3%E0%B8%81%E0%B8%8E%E0%B8%B2%E0%B8%84%E0%B8%A1",// 7 กรกฎาคม - July 31
    "%E0%B8%AA%E0%B8%B4%E0%B8%87%E0%B8%AB%E0%B8%B2%E0%B8%84%E0%B8%A1",// 8 สิงหาคม - August 31
    "%E0%B8%81%E0%B8%B1%E0%B8%99%E0%B8%A2%E0%B8%B2%E0%B8%A2%E0%B8%99",// 9 กันยายน - September 30
    "%E0%B8%95%E0%B8%B8%E0%B8%A5%E0%B8%B2%E0%B8%84%E0%B8%A1",// 10 ตุลาคม - October 31
    "%E0%B8%9E%E0%B8%A4%E0%B8%A8%E0%B8%88%E0%B8%B4%E0%B8%81%E0%B8%B2%E0%B8%A2%E0%B8%99",// 11 พฤศจิกายน - November 30
    "%E0%B8%98%E0%B8%B1%E0%B8%99%E0%B8%A7%E0%B8%B2%E0%B8%84%E0%B8%A1"// 12 ธันวาคม - December 31
};

String URLEncoded::Day(int day_n) {
    return String(DAY[day_n]);
};

String URLEncoded::Month(int month_n) {
    return String(MONTH[month_n]);
};

String URLEncoded::ChristianEra(int christian_year_n) {
    return String("%E0%B8%84.%E0%B8%A8.%20" + String(christian_year_n + 1900));// ค.ศ. - A.D. 0
};

String URLEncoded::BuddhistEra(int christian_year_n) {
    return String("%E0%B8%9E.%E0%B8%A8.%20" + String(christian_year_n + 543 + 1900));// พ.ศ. - A.C. -> B.E. +543
};

////////////////////

String ZEROFILL_2(uint8_t n) {
    if (n > 9) {
        return String(n);
    } else {
        return "0" + String(n);
    };
};

String GET_Message_URLEncoded(struct tm* DT_) {
    Serial.println("[URLEncode] Message Generating");
    String tmpstr = "";
    tmpstr += URLEncoded::Day(DT_->tm_wday);
    tmpstr += "%E0%B8%97%E0%B8%B5%E0%B9%88%20";
    tmpstr += String(DT_->tm_mday);
    tmpstr += "%20";
    tmpstr += URLEncoded::Month(DT_->tm_mon);
    tmpstr += "%20";
    tmpstr += URLEncoded::BuddhistEra(DT_->tm_year);
    tmpstr += "%20%E0%B9%80%E0%B8%A7%E0%B8%A5%E0%B8%B2%20";
    tmpstr += ZEROFILL_2(DT_->tm_hour);
    tmpstr += "%3A";
    tmpstr += ZEROFILL_2(DT_->tm_min);
    tmpstr += "%3A";
    tmpstr += ZEROFILL_2(DT_->tm_sec);
    tmpstr += "%E0%B8%99.%20";
    tmpstr += "%E0%B8%A1%E0%B8%B5%E0%B8%88%E0%B8%94%E0%B8%AB%E0%B8%A1%E0%B8%B2%E0%B8%A2%E0%B9%83%E0%B8%AB%E0%B8%A1%E0%B9%88%E0%B9%80%E0%B8%82%E0%B9%89%E0%B8%B2%E0%B8%A1%E0%B8%B2%E0%B8%A2%E0%B8%B1%E0%B8%87%E0%B8%81%E0%B8%A5%E0%B9%88%E0%B8%AD%E0%B8%87%E0%B8%88%E0%B8%94%E0%B8%AB%E0%B8%A1%E0%B8%B2%E0%B8%A2";
    return tmpstr;
};
