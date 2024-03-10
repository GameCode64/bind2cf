#include "BindModel.h"

namespace BindModelNS
{
    vector<DNSRecord> BindModel::ReadBindFile(string Filename, int Skip)
    {
        ifstream File(Filename);
        vector<DNSRecord> DnsRecords;

        if (!File.is_open())
        {
            cerr << "Cannot read file: " << Filename << endl;
            return {};
        }

        string Line;
        string SOARecord;
        string TTL = "300";
        while (getline(File, Line))
        {
            istringstream Iss(Line);
            vector<string> Tkn{
                istream_iterator<string>{Iss},
                istream_iterator<string>{}};
            if (Line.empty() || Line[0] == ';')
            {
                continue;
            }

            if (Line.find("IN SOA") != string::npos)
            {
                SOARecord = Line;
                break;
            }

            if (Skip > 0)
            {
                for (int i = 0; i < Skip - 1; ++i)
                {
                    continue;
                }
            }

            if (Tkn.size() == 2 && Tkn[0] == "$ttl")
            {
                TTL = Tkn[1];
            }

            if (Tkn.size() >= 3)
            {
                DNSRecord Record;
                int TknSkip = 0;
                Record.TTL = TTL;
                if (Tkn[2] == "IN")
                {
                    TknSkip = 1;
                    Record.TTL = Tkn[1];
                }
                string TName = Tkn[0];
                Record.Host = TName.substr(0, TName.size()-1);
                Record.Type = Tkn[2 + TknSkip];
                Record.Destination = "";
                for (size_t i = 3 + TknSkip; i < Tkn.size(); ++i)
                {
                    Record.Destination += Tkn[i] + " ";
                }
                // removing trailing spaces
                Record.Destination = Record.Destination.substr(0, Record.Destination.size() - 1);

                DnsRecords.push_back(Record);
            }
        }

        return DnsRecords;
    }
    vector<json> BindModel::CompareJsonFiles(const vector<json> &first, const vector<json> &second, const string &source1, const string &source2)
    {
        // Convert vectors to sets for efficient comparison
        set<json> set1(first.begin(), first.end());
        set<json> set2(second.begin(), second.end());

        vector<json> differences;

        

        // Find the symmetric difference between the sets
        set_symmetric_difference(set1.begin(), set1.end(), set2.begin(), set2.end(), back_inserter(differences));

        // Add source information to the differences
        for (auto &record : differences)
        {
            if (set1.find(record) != set1.end())
            {
                record["Source"] = source1;
            }
            else if (set2.find(record) != set2.end())
            {
                record["Source"] = source2;
            }
        }

        return differences;
    }

}