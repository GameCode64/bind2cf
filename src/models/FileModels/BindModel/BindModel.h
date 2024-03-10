#ifndef BINDMODEL_H
#define BINDMODEL_H
#endif

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <set>
#include "../../../lib/json/json.hpp"




namespace BindModelNS{
    using namespace std;
    using json = nlohmann::json;
    
    struct DNSRecord {
        string Host;
        string TTL;
        string Type;
        string Destination;
        string ZoneID;
    };
    struct DNSDiffRecord {
        string Host;
        string TTL;
        string Type;
        string Destination;
        string Source;
        string ZoneID;
    };

    class BindModel{
        public:
        vector<DNSRecord> ReadBindFile(string Filename, int Skip = 0);
        vector<json> CompareJsonFiles(const vector<json>& first, const vector<json>& second, const string& source1, const string& source2);
        //private:
        //bool jsonEqual(const json& j1, const json& j2);
        //bool jsonLess(const json& j1, const json& j2);

    //   vector<DNSDiffRecord> CompareBindFiles(const vector<DNSDiffRecord>& first, const vector<DNSDiffRecord>& second, const string& source1, const string& source2);

    };
}