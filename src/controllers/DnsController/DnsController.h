#include "../../lib/QuickHelpers.h"
#include "../../lib/json/json.hpp"
#include "../../models/FileModels/BindModel/BindModel.h"
#include "../../lib/restclient/include/restclient-cpp/restclient.h"
#include "../../lib/restclient/include/restclient-cpp/connection.h"

using namespace std;
using namespace BindModelNS;

using json = nlohmann::json;


class DnsController {
    public:
        DnsController();
        json GetDiffrence();
        bool Sync(json DiffList);
    private:
        BindModel BM;
        QuickHelpers *QH;
        json DnsList;
        json CFDnsList;
        json Config;
        bool SendToCloudflare(json Item);
};