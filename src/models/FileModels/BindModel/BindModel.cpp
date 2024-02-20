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
        string TTL = "300";
        while (getline(File, Line))
        {
            if (Line.empty() || Line[0] == ';')
            {
                continue;
            }

            if (Skip > 0)
            {
                for (int i = 0; i < Skip - 1; ++i)
                {
                    continue;
                }
            }
            
            istringstream Iss(Line);
            vector<string> Tkn{
                istream_iterator<string>{Iss},
                istream_iterator<string>{}};
            if( Tkn.size() == 2 && Tkn[0] == "$ttl")
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
                Record.Host = Tkn[0];
                Record.Type = Tkn[2+TknSkip];
                Record.Destination = "";
                for (size_t i = 3+TknSkip; i < Tkn.size(); ++i)
                {
                    Record.Destination += Tkn[i] + " ";
                }
                //removing trailing spaces
                Record.Destination = Record.Destination.substr(0, Record.Destination.size() - 1);
                // Record.Destination = (Tkn.size() >= 4) ? Tkn[3] : "";

                DnsRecords.push_back(Record);
            }
        }

        return DnsRecords;
    }
}