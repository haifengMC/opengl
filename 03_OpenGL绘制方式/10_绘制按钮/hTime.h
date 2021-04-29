#pragma once

typedef std::chrono::time_point<std::chrono::steady_clock> hTimePoint;

const hTimePoint& getNow();