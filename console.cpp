#include "console.h"

void Console::reg_cmd(const std::string& command, const Callback& callback, const std::string& description)
{
	if (command.empty()) { return; }
	for (unsigned i = 0; i < m_total_commands; i++)
		if (command == m_commands.at(i)) { return; }

	m_commands.push_back(command);
	m_callbacks.push_back(callback);
	m_descriptions.push_back(description);

	m_total_commands++;
}

void Console::show_help_msg(const bool& b) { m_print_help_msg = b; }

void Console::set_prefix(const std::string& prefix)
{
	if (prefix.empty()) { return; }
	m_prefix = prefix;
}

void Console::open()
{
	std::cout << "Opening console...\n";
	if (!m_running) { m_running = true; }
	if (m_print_help_msg) { std::cout << "*** If you don't know what to do, type \"help\" ***\n"; }
	do
	{
		if (m_command_found) { m_command_found = false; }
		std::cout << m_prefix;
		std::getline(std::cin, m_input);
		if (m_input.empty()) { continue; }
		for (unsigned i = 0; i < m_total_commands; i++)
		{
			if (m_input == m_commands.at(i))
			{
				m_command_found = true;
				m_command_found_index = i;
				break;
			}
		}
		if (m_command_found) { m_callbacks.at(m_command_found_index)(); }
		else { std::cout << ">> Command: \"" << m_input << "\" not found\n"; }
	} while (m_running);
}

void Console::cmd_exit()
{
	if (m_running)
	{
		std::cout << ">> Exiting...\n";
		m_running = false;
	}
}
void Console::cmd_help() const
{
	std::cout << "-------------------- COMMAND LIST --------------------\n";
	for (unsigned i = 0; i < m_total_commands; i++) { std::cout << i + 1 << ")\t\t" << m_commands.at(i) << "\t\t\t" << m_descriptions.at(i) << '\n'; }
}