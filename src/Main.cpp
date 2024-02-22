#include "Main.h"


QuickHelpers *QH;
using json = nlohmann::json;

int main(int argc, char *argv[])
{

    json Config = json::parse(QH->ReadFile("/etc/bind2cf/conf.json"));
    //QH->WriteLine(Config["apikey"], E_T_bright);





  


    json BindMounts = json::parse(QH->ReadFile("/etc/bind2cf/mount.conf"));
   // json dnslist;
   // for (int i = 0; i < end(BindMounts) - begin(BindMounts); i++)
     for (auto i : BindMounts)
    {
        //BindModel BM;

        //QH->WriteLine(i["cloudflareID"]);
        string Zone = i["cloudflareID"];
        string BearerToken = Config["apikey"];

        RestClient::init();
        RestClient::Connection* RCConn = new RestClient::Connection("https://api.cloudflare.com");
        RestClient::HeaderFields Headers;
        Headers["Accept"] = "application/json";
        Headers["Authorization"] = "Bearer " + BearerToken;
        RCConn->SetHeaders(Headers);
        //RCConn->AppendHeader("Authorization", "bearer " + BearerToken );


        RestClient::Response r = RCConn->get("/client/v4/zones/" + Zone + "/dns_records");
        json JsonResponse = json::parse(r.body);

        RestClient::disable();

        QH->WriteLine(JsonResponse.dump(3), E_T_bright, E_F_cyan);

       // QH->WriteLine(QH->ReadFile(j[i]["bindfile"]), E_T_bright, E_F_green);
       /* for (auto &r : BM.ReadBindFile(BindMounts[i]["bindfile"]))
        {

            if(r.Type != "SOA" && r.Type != "NS")
            {
                json dnsrecord = {
                    {
                        "Host", r.Host
                    },
                    {
                        "Type", r.Type
                    },
                    {
                        "TTL", r.TTL
                    },
                    {
                        "Destination", r.Destination
                    },
                };
                dnslist.push_back(dnsrecord);
                QH->WriteLine(r.Host + " [" + r.Type + "] => " + r.Destination + "  ["+r.TTL+"]", E_T_bright, E_F_yellow, E_B_black);
            }
        }*/
    }
   // cout << dnslist.dump(1) << endl;





    return 0;
}
;