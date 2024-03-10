#include "DnsController.h"

DnsController::DnsController()
{
}

json DnsController::GetDiffrence()
{

    Config = json::parse(QH->ReadFile("/etc/bind2cf/conf.json"));
    json BindMounts = json::parse(QH->ReadFile("/etc/bind2cf/mount.conf"));

    for (auto i : BindMounts)
    {
        string Zone = i["cloudflareID"];
        string BearerToken = Config["apikey"];
        RestClient::init();
        RestClient::Connection *RCConn = new RestClient::Connection("https://api.cloudflare.com");
        RestClient::HeaderFields Headers;
        Headers["Accept"] = "application/json";
        Headers["Authorization"] = "Bearer " + BearerToken;
        RCConn->SetHeaders(Headers);
        RestClient::Response r = RCConn->get("/client/v4/zones/" + Zone + "/dns_records");
        json JsonResponse = json::parse(r.body);
        RestClient::disable();
        for (auto &r : JsonResponse["result"])
        {
            {
                json Records = {
                    {"Host", r["name"]},
                    {"Type", r["type"]},
                    {"TTL", r["ttl"]},
                    {"Destination", r["content"]},
                    {"ZoneID", Zone}
                };
                CFDnsList.push_back(Records);
            }
        }
        for (auto &r : BM.ReadBindFile(i["bindfile"]))
        {
            if (r.Type != "SOA" && r.Type != "NS")
            {
                json Records = {
                    {"Host", r.Host},
                    {"Type", r.Type},
                    {"TTL", r.TTL},
                    {"Destination", r.Destination},
                    {"ZoneID", Zone} 
                };
                DnsList.push_back(Records);
            }
        }
    }
    return BM.CompareJsonFiles(DnsList, CFDnsList, "Local", "Cloudflare");
}

bool DnsController::Sync(json DiffList)
{

    for (auto Item : DiffList)
    {
        if(Item["Source"] == "Cloudflare")
        {
            //for now do nothing
        }
        else
        {
            //Lets send it to cloudflare
            this->SendToCloudflare(Item);
        }
    }
    return true;
}

bool DnsController::SendToCloudflare(json Item)
{
    QH->WriteLine(""); 
    QH->Write("Name: ", E_T_bright, E_F_green);
    QH->Write(Item["Host"], E_T_bright, E_F_blue);
    QH->Write("\nContent: ", E_T_bright, E_F_green);
    QH->Write(Item["Destination"], E_T_bright, E_F_blue);
    QH->Write("\nType: ", E_T_bright, E_F_green);
    QH->Write(Item["Type"], E_T_bright, E_F_blue);
    QH->Write("\nSource ", E_T_bright, E_F_green);
    QH->WriteLine(Item["Source"], E_T_bright, E_F_blue);
    QH->WriteLine(Item["ZoneID"], E_T_bright, E_F_red);

    json InsertRecords = {
         {"name", Item["Host"]},
         {"type", Item["Type"]},
         {"ttl", Item["TTL"]},
         {"content", Item["Destination"]},
         {"proxied", false},
         {"comment", "Send from bind"}
    };
    string PostData = InsertRecords.dump(0);
    string Zone = Item["ZoneID"];
    string BearerToken = Config["apikey"];
    string Name = Item["Host"];
    string Type = Item["Type"];
    RestClient::init();
    RestClient::Connection *RCConn = new RestClient::Connection("https://api.cloudflare.com");
    RestClient::HeaderFields Headers;
    Headers["Accept"] = "application/json";
    Headers["Authorization"] = "Bearer " + BearerToken;
    RCConn->SetHeaders(Headers);
    RestClient::Response r = RCConn->post("/client/v4/zones/" + Zone + "/dns_records", PostData );
    json JResp = json::parse(r.body);
    RestClient::disable();
    QH->WriteLine(r.body, E_T_bright, E_F_green);

    if(!JResp["success"])
    {

        RestClient::init();
        RestClient::Connection *RCConnGet = new RestClient::Connection("https://api.cloudflare.com");
        RestClient::HeaderFields GetHeaders;
        GetHeaders["Accept"] = "application/json";
        GetHeaders["Authorization"] = "Bearer " + BearerToken;
        RCConnGet->SetHeaders(GetHeaders);
        RestClient::Response RespGet = RCConnGet->get("/client/v4/zones/" + Zone + "/dns_records?name="+Name+"&type="+Type);
        //cout << RespGet.headers << endl;
        json JRespGet = json::parse(RespGet.body);
        QH->WriteLine(RespGet.body, E_T_bright, E_F_cyan);
        QH->WriteLine("/client/v4/zones/" + Zone + "/dns_records?name="+Name+"&type="+Type, E_T_bright_off, E_F_red );
        RestClient::disable();

        if(JRespGet["success"] && JRespGet["result_info"]["total_count"] > 0)
        {
            string RecordID = JRespGet["result"][0]["id"];
            RestClient::init();
            RestClient::Connection *RCConnUpdate = new RestClient::Connection("https://api.cloudflare.com");
            RestClient::HeaderFields UpdateHeaders;
            UpdateHeaders["Accept"] = "application/json";
            UpdateHeaders["Authorization"] = "Bearer " + BearerToken;
            RCConnUpdate->SetHeaders(UpdateHeaders);
            RestClient::Response RespUpdate = RCConnUpdate->put("/client/v4/zones/" + Zone + "/dns_records/" + RecordID, PostData);
            json JRespUpdate = json::parse(RespUpdate.body);
            RestClient::disable();
            QH->WriteLine(RespUpdate.body, E_T_bright, E_F_blue);
        }
        else
        {
            return false;
        }
    }
   // exit(1);
return true;
}