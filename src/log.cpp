#define _SILENCE_STDEXT_ARR_ITERS_DEPRECATION_WARNING
#include "log.h"

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

std::shared_ptr<spdlog::logger> logger = spdlog::basic_logger_mt("file", "logs/log.txt");