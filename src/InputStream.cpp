#include "InputStream.h"

#include "string"

namespace WordConverter {

	std::pair<std::string, std::string> InputStream::ReadNext() const {
		std::string word, spaces;
		char c{};
		while (m_input_stream.get(c) && !std::isspace(c) && c != '.') {
			word.push_back(c);
		}
		if (m_input_stream) {
			spaces.push_back(c);
			while (m_input_stream.get(c) && (std::isspace(c) || c == '.')) {
				spaces.push_back(c);
			}
			if (m_input_stream) {
				m_input_stream.putback(c);
			}
		}
		return { word, spaces };
	}

}