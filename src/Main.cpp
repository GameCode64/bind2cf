#include "Main.h"
using namespace std;

QuickHelpers *QH;
using json = nlohmann::json;

int main(int argc, char *argv[])
{
    using namespace BindModelNS;
    json j = json::parse(QH->ReadFile("/etc/bind2cf/mount.conf"));
    // for (auto i : j)
    for (int i = 0; i < end(j) - begin(j); i++)
    {
        BindModel BM;
        QH->WriteLine(QH->ReadFile(j[i]["bindfile"]), E_T_bright, E_F_green);
        for (auto &r : BM.ReadBindFile(j[i]["bindfile"]))
        {
            if(r.Type != "SOA" && r.Type != "NS")
            {
                QH->WriteLine(r.Host + " [" + r.Type + "] => " + r.Destination + "  ["+r.TTL+"]", E_T_bright, E_F_yellow, E_B_black);
            }
        }
    }
    return 0;
}
