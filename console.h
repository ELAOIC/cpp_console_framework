#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <functional>

class Console
{
private:
	bool m_running;

	bool m_print_help_msg;

	using Callback = std::function<void()>;

	std::vector<std::string> m_commands;
	std::vector<Callback> m_callbacks;
	std::vector<std::string> m_descriptions;

	unsigned m_total_commands;

	std::string m_prefix;

	std::string m_input;

	bool m_command_found;
	unsigned m_command_found_index;

public:
	Console()
		: m_running(false), m_print_help_msg(true), m_total_commands(0), m_prefix("console > "), m_command_found(false)
	{
		reg_cmd("exit", [&] {cmd_exit(); }, "Exits the console");
		reg_cmd("help", [&] {cmd_help(); }, "Displays this text");
	}
	~Console() {}

	void reg_cmd(const std::string& command, const Callback& callback, const std::string& description);

	void show_help_msg(const bool& b);
	void set_prefix(const std::string& str);

	virtual void open();

private:
	void cmd_exit();
	void cmd_help() const;
};