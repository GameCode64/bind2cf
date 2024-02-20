#ifndef BINDMODEL_H
#define BINDMODEL_H
#endif

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <iterator>

namespace BindModelNS{
    using namespace std;
    struct DNSRecord {
        string Host;
        string TTL;
        string Type;
        string Destination;
    };

    class BindModel{
        public:
        vector<DNSRecord> ReadBindFile(string Filename, int Skip = 0);
    };
}