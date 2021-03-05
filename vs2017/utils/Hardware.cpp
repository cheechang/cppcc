#include "Hardware.h"
#include <iostream>
#ifdef _WIN32
#   include <winsock2.h>
#   include <windows.h>
#   include <iphlpapi.h>
#   include <stdio.h>
#   pragma comment(lib, "iphlpapi.lib")
#elif defined(__linux__)
#   include <stdio.h>
#   include <ifaddrs.h>
#   include <sys/ioctl.h>
#   include <sys/socket.h>
#   include <netinet/in.h>
#   include <net/if.h>
#   include <netdb.h>
#   include <string.h>
#elif defined(__APPLE__)
#include <net/if.h>
#include <net/if_dl.h>
#include <ifaddrs.h>
#endif // _MSC_VER

namespace utils
{
	/// ref:http://lists.boost.org/boost-users/2008/08/39812.php   
    std::string Hardware::mac()
    {
#ifdef _WIN32 
            std::string macOUT;
            bool ret = false;

            ULONG outBufLen = sizeof(IP_ADAPTER_ADDRESSES);
            PIP_ADAPTER_ADDRESSES pAddresses = (IP_ADAPTER_ADDRESSES*)malloc(outBufLen);
            if (pAddresses == NULL)
                return false;
            // Make an initial call to GetAdaptersAddresses to get the necessary size into the ulOutBufLen variable
            if (GetAdaptersAddresses(AF_UNSPEC, 0, NULL, pAddresses, &outBufLen) == ERROR_BUFFER_OVERFLOW)
            {
                free(pAddresses);
                pAddresses = (IP_ADAPTER_ADDRESSES*)malloc(outBufLen);
                if (pAddresses == NULL)
                    return false;
            }

            if (GetAdaptersAddresses(AF_UNSPEC, 0, NULL, pAddresses, &outBufLen) == NO_ERROR)
            {
                // If successful, output some information from the data we received
                for (PIP_ADAPTER_ADDRESSES pCurrAddresses = pAddresses; pCurrAddresses != NULL; pCurrAddresses = pCurrAddresses->Next)
                {
                    // ȷ��MAC��ַ�ĳ���Ϊ 00-00-00-00-00-00
                    if (pCurrAddresses->PhysicalAddressLength != 6)
                        continue;
                    char acMAC[32];
                    sprintf_s(acMAC, 32, "%02X:%02X:%02X:%02X:%02X:%02X",
                        int(pCurrAddresses->PhysicalAddress[0]),
                        int(pCurrAddresses->PhysicalAddress[1]),
                        int(pCurrAddresses->PhysicalAddress[2]),
                        int(pCurrAddresses->PhysicalAddress[3]),
                        int(pCurrAddresses->PhysicalAddress[4]),
                        int(pCurrAddresses->PhysicalAddress[5]));
                    macOUT = acMAC;
                    ret = true;
                    //break;
                }
            }

            free(pAddresses);
            return macOUT;
#elif defined(__linux__)
	/// http://www.cnblogs.com/quicksnow/p/3299172.html
		struct ifreq ifr;
		struct ifconf ifc;
		char buf[1024];
		int success = 0;

		int sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP);
		if (sock == -1) { std::cout<<"mac error 1\n"; return ""; };

		ifc.ifc_len = sizeof(buf);
		ifc.ifc_buf = buf;
		if (ioctl(sock, SIOCGIFCONF, &ifc) == -1) { std::cout<<"mac error 2\n"; return ""; }

		struct ifreq* it = ifc.ifc_req;
		const struct ifreq* const end = it + (ifc.ifc_len / sizeof(struct ifreq));

		for (; it != end; ++it) 
		{
			strcpy(ifr.ifr_name, it->ifr_name);
			if (ioctl(sock, SIOCGIFFLAGS, &ifr) == 0) 
			{
				if (! (ifr.ifr_flags & IFF_LOOPBACK)) 
				{ // don't count loopback
					if (ioctl(sock, SIOCGIFHWADDR, &ifr) == 0) 
					{
						success = 1;
						break;
					}
				}
			}
			else 
			{ 
				// handle error 
				std::cout<<"mac error 3\n";
				return "";
			}
		}
		if (success) 
		{
			char mac[19]; // one extra for terminating '\0'; You may want to make it a little larger still, just to be sure. 
			memset(mac,0,sizeof(mac));
			sprintf(mac, " %02x:%02x:%02x:%02x:%02x:%02x", 
				(unsigned char)ifr.ifr_hwaddr.sa_data[0],
				(unsigned char)ifr.ifr_hwaddr.sa_data[1],
				(unsigned char)ifr.ifr_hwaddr.sa_data[2],
				(unsigned char)ifr.ifr_hwaddr.sa_data[3],
				(unsigned char)ifr.ifr_hwaddr.sa_data[4],
				(unsigned char)ifr.ifr_hwaddr.sa_data[5]);

			return std::string(mac);
		}
		else
		{
			std::cout << "mac error 4\n";
			return "";
		}
#elif defined(__APPLE__)
   ifaddrs* iflist = CNull;
   char mac_addr[1024] = {0};
   const char* if_name = "en0";
   if (getifaddrs(&iflist) == 0) {
	for (ifaddrs* cur = iflist; cur; cur = cur->ifa_next) {
		if ((cur->ifa_addr->sa_family == AF_LINK) &&
			(strcmp(cur->ifa_name, if_name) == 0) &&
			cur->ifa_addr) {
			sockaddr_dl* sdl = (sockaddr_dl*)cur->ifa_addr;
			memcpy(mac_addr, LLADDR(sdl), sdl->sdl_alen);
			break;
		}
	}
	freeifaddrs(iflist);
	return std::string(mac_addr);
}
#endif 
    }
	std::vector<std::string> Hardware::getlocalip(){
	 std::vector<std::string> iplist;
#ifdef _WIN32 
	
	 PIP_ADAPTER_INFO pIpAdapterInfo = new IP_ADAPTER_INFO(); //PIP_ADAPTER_INFO�ṹ��ָ��洢����������Ϣ
	 unsigned long stSize = sizeof(IP_ADAPTER_INFO); //�õ��ṹ���С,����GetAdaptersInfo����
	 //����GetAdaptersInfo����,���pIpAdapterInfoָ�����;����stSize��������һ��������Ҳ��һ�������
	 int nRel = GetAdaptersInfo(pIpAdapterInfo, &stSize);
	 //��¼��������
	 int netCardNum = 0;
	 //��¼ÿ�������ϵ�IP��ַ����
	 int IPnumPerNetCard = 0;
	 if (ERROR_BUFFER_OVERFLOW == nRel)
	 {
		 //����������ص���ERROR_BUFFER_OVERFLOW
		 //��˵��GetAdaptersInfo�������ݵ��ڴ�ռ䲻��,ͬʱ�䴫��stSize,��ʾ��Ҫ�Ŀռ��С
		 //��Ҳ��˵��ΪʲôstSize����һ��������Ҳ��һ�������
		 //�ͷ�ԭ�����ڴ�ռ�
		 delete pIpAdapterInfo;
		 //���������ڴ�ռ������洢����������Ϣ
		 pIpAdapterInfo = (PIP_ADAPTER_INFO)new BYTE[stSize];
		 //�ٴε���GetAdaptersInfo����,���pIpAdapterInfoָ�����
		 nRel = GetAdaptersInfo(pIpAdapterInfo, &stSize);
	 }
	 if (ERROR_SUCCESS == nRel)
	 {
		 //���������Ϣ
		 //�����ж�����,���ͨ��ѭ��ȥ�ж�
		 while (pIpAdapterInfo)
		 {
			 std::cout << "����������" << ++netCardNum << std::endl;
			 std::cout << "�������ƣ�" << pIpAdapterInfo->AdapterName << std::endl;
			 std::cout << "����������" << pIpAdapterInfo->Description << std::endl;
			 switch (pIpAdapterInfo->Type)
			 {
			 case MIB_IF_TYPE_OTHER:
				 std::cout << "�������ͣ�" << "OTHER" << std::endl;
				 break;
			 case MIB_IF_TYPE_ETHERNET:
				 std::cout << "�������ͣ�" << "ETHERNET" << std::endl;
				 break;
			 case MIB_IF_TYPE_TOKENRING:
				 std::cout << "�������ͣ�" << "TOKENRING" << std::endl;
				 break;
			 case MIB_IF_TYPE_FDDI:
				 std::cout << "�������ͣ�" << "FDDI" << std::endl;
				 break;
			 case MIB_IF_TYPE_PPP:
				 printf("PP\n");
				 std::cout << "�������ͣ�" << "PPP" << std::endl;
				 break;
			 case MIB_IF_TYPE_LOOPBACK:
				 std::cout << "�������ͣ�" << "LOOPBACK" << std::endl;
				 break;
			 case MIB_IF_TYPE_SLIP:
				 std::cout << "�������ͣ�" << "SLIP" << std::endl;
				 break;
			 default:

				 break;
			 }
			 std::cout << "����MAC��ַ��";
			 for (DWORD i = 0; i < pIpAdapterInfo->AddressLength; i++)
			 if (i < pIpAdapterInfo->AddressLength - 1)
			 {
				 printf("%02X-", pIpAdapterInfo->Address[i]);
			 }
			 else
			 {
				 printf("%02X\n", pIpAdapterInfo->Address[i]);
			 }
			 std::cout << "����IP��ַ���£�" << std::endl;
			 //���������ж�IP,���ͨ��ѭ��ȥ�ж�
			 IP_ADDR_STRING *pIpAddrString = &(pIpAdapterInfo->IpAddressList);
			 do
			 {
				 std::cout << "�������ϵ�IP������" << ++IPnumPerNetCard << std::endl;
				 std::cout << "IP ��ַ��" << pIpAddrString->IpAddress.String << std::endl;
				 std::cout << "������ַ��" << pIpAddrString->IpMask.String << std::endl;
				 std::cout << "���ص�ַ��" << pIpAdapterInfo->GatewayList.IpAddress.String << std::endl;
				 if (std::string("0.0.0.0") == pIpAdapterInfo->GatewayList.IpAddress.String || std::string("0.0.0.0") == pIpAddrString->IpAddress.String)
				 {
					 pIpAddrString = pIpAddrString->Next;
					 continue;
				 }
				 iplist.push_back(pIpAddrString->IpAddress.String);
				 pIpAddrString = pIpAddrString->Next;
			 } while (pIpAddrString);
			 pIpAdapterInfo = pIpAdapterInfo->Next;
			 std::cout << "--------------------------------------------------------------------" << std::endl;
		 }

	 }
	 //�ͷ��ڴ�ռ�
	 if (pIpAdapterInfo)
	 {
		 delete [] pIpAdapterInfo;
		 pIpAdapterInfo = NULL;
	 }

#endif
	 return iplist;
	}
}