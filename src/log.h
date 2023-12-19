#pragma once

#include <spdlog/logger.h>

extern std::shared_ptr<spdlog::logger> logger;

#define LDEBUG(message, ...) logger->debug("[{0}][{1}] {2}", __FUNCTION__, __LINE__, fmt::format(message, __VA_ARGS__)); logger->flush();
#define LINFO(message, ...) logger->info("[{0}][{1}] {2}", __FUNCTION__, __LINE__, fmt::format(message, __VA_ARGS__)); logger->flush();
#define LWARN(message, ...) logger->warn("[{0}][{1}] {2}", __FUNCTION__, __LINE__, fmt::format(message, __VA_ARGS__)); logger->flush();
#define LERR(message, ...) logger->error("[{0}][{1}] {2}", __FUNCTION__, __LINE__, fmt::format(message, __VA_ARGS__)); logger->flush();