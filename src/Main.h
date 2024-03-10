
#pragma once

#include <iostream>
#include "lib/QuickHelpers.h"
#include "controllers/ServiceController/ServiceController.h"
#include "controllers/ManagementController/ManagementController.h"
#include "controllers/DnsController/DnsController.h"
#include "lib/json/json.hpp"
#include "lib/restclient/include/restclient-cpp/restclient.h"
#include "lib/restclient/include/restclient-cpp/connection.h"

using namespace std;

QuickHelpers *QH;
using json = nlohmann::json;
