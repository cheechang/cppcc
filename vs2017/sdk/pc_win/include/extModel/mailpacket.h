#pragma once

#include "../extModel/packet.h"

namespace model
{
    struct mailSetting{
        mailSetting() :storedays(0), fetchTimeVal(0), SMTPSSL(0), fetchProt(0), FetchSSL(0){

        }
        std::string account;
        Optional<std::string> passwd;
        Optional<std::string> name;
        Optional<int> storedays;
        Optional<int> fetchTimeVal;
        Optional<std::string> SMTPAddr;
        Optional<std::string> SMTPPort;
        Optional<int8> SMTPSSL;
        Optional<int8> fetchProt;
        Optional<std::string> FetchAddr;
        Optional<std::string> FetchPort;
        Optional<int8> FetchSSL;
        Optional<std::string> attachPath;
        Optional<std::vector<std::string> > floderName;
    };
    
    struct stsendMail{
        std::string account;
        std::string myName;
        std::string myMailAddr;
        std::vector<std::string> recvList;
        std::string subject;
        std::string content;
        std::vector<std::string> attches;
    };
}