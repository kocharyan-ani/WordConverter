#pragma once

#include <istream>

namespace WordConverter {

	// Wrapper for input stream
	class InputStream {
	private:
		std::istream& m_input_stream;

	public:
		InputStream(std::istream& s) 
			: m_input_stream(s)
		{}

		explicit operator bool() const {
			return static_cast<bool>(m_input_stream);
		}

		std::pair<std::string, std::string> ReadNext() const;
	};

}
