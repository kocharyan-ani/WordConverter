#pragma once

#include <string>

namespace WordConverter {

	class ArgumentParser {
	private:
		std::string m_input_file_name;
		std::string m_output_file_name;

	public:
		bool Parse(int, char**);

		std::string GetInputFileName() const {
			return m_input_file_name;
		}

		std::string GetOutputFileName() const {
			return m_output_file_name;
		}
	};

}
