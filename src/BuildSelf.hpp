#ifndef BUILD_SELF_HPP
#define BUILD_SELF_HPP

#define _CRT_SECURE_NO_WARNINGS
#include <vector>
#include <string>
#include <filesystem>
#include <map>
#include <optional>

namespace BuildSelf {

struct Flags {

	bool clean = false;
	bool release = false;
	bool scratch = false;
	bool show_help = false;
	bool run_after_compilation = false;
	std::optional<std::filesystem::path> state_file;
	std::optional<std::filesystem::path> output;

	static Flags parse(int argc, char** argv) noexcept;
	static const char* help_message() noexcept;
};

struct State {
	std::map<std::filesystem::path, std::uint64_t> files;

	static State load_from_file(const std::filesystem::path& p) noexcept;
	static State get_unchanged(const State& a, const State& b) noexcept;
	void save_to_file(const std::filesystem::path& p) noexcept;
};

struct Build {
	enum class Target {
		Header_Only,
		Exe
	};

	enum class Cli {
		Cl = 0,
		Gcc,
		Count
	};

	enum class Std_Ver {
		Cpp17 = 0,
		Count
	};

	std::string name;

	Flags flags;
	std::filesystem::path state_file;

	Cli cli;
	Target target;
	Std_Ver std_ver;

	bool invert_header_implementation_define = false;

	std::filesystem::path compiler;
	std::vector<std::filesystem::path> source_files;
	std::vector<std::filesystem::path> header_files;
	std::vector<std::filesystem::path> link_files;

	std::vector<std::string> defines;

	static Build get_default(Flags flags = {}) noexcept;

	void add_source(const std::filesystem::path& f) noexcept;
	void add_source_recursively(const std::filesystem::path& f) noexcept;
	void add_library(const std::filesystem::path& f) noexcept;
	void add_header(const std::filesystem::path& f) noexcept;
	void add_define(std::string str) noexcept;
};

struct Commands {
	std::vector<std::string> commands;
};

};

#endif