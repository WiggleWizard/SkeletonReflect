#pragma once

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include <memory>

#define LOG_DECL(variableName) \
	std::shared_ptr<spdlog::logger> variableName
#define LOG_IMPL(c, variableName, category) \
	std::shared_ptr<spdlog::logger> c::variableName = spdlog::stdout_color_mt(#category)
#define LOGGER(variableName, category) \
	static std::shared_ptr<spdlog::logger> variableName = spdlog::stdout_color_mt(#category)


template<>
struct fmt::formatter<eastl::string>
{
	template<typename ParseContext>
	constexpr auto parse(ParseContext& ctx);

	template<typename FormatContext>
	auto format(const eastl::string& number, FormatContext& ctx);
};

template<typename ParseContext>
constexpr auto fmt::formatter<eastl::string>::parse(ParseContext& ctx)
{
	return ctx.begin();
}

template<typename FormatContext>
auto fmt::formatter<eastl::string>::format(const eastl::string& s, FormatContext& ctx)
{
	return fmt::format_to(ctx.out(), "{}", s.c_str());
}