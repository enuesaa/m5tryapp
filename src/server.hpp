#pragma once

#include <WebServer.h>

#include "monitor.hpp"

WebServer &setupServer(MonitorInflux &influx);
