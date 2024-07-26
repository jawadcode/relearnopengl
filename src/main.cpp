#include <spdlog/spdlog.h>
#include <spdlog/cfg/env.h>

auto main() -> int {
	spdlog::cfg::load_env_levels();
	spdlog::info("Welcome to RelearnOpenGL!");
	return 0;
}
