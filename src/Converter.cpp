#include "Converter.h"

#include <algorithm>
#include <math.h>
#include <unordered_map>

namespace WordConverter {

	namespace {

		typedef std::unordered_map<std::string, int> NameNumbers;

		const static NameNumbers s_digits{
			{"one", 1}, {"two", 2}, {"three", 3}, {"four", 4},
			{"five", 5}, {"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9}
		};

		const static NameNumbers s_teens{
			{"ten", 10}, {"eleven", 11}, {"twelve", 12}, {"thirteen", 13}, {"fourteen", 14},
			{"fifteen", 15}, {"sixteen", 16}, {"seventeen", 17}, {"eighteen", 18}, {"nineteen", 19}
		};

		const static NameNumbers s_tens{
			{"twenty", 20}, {"thirty", 30}, {"forty", 40}, {"fifty", 50}, {"sixty", 60},
			{"seventy", 70}, {"eighty", 80}, {"ninety", 90}
		};

		const static NameNumbers s_multipliers{
			{"thousand", 1000}, {"million", 1000000}, {"billion", 1000000000}
		};

		int GetNumber(const std::string& name, const NameNumbers& map) {
			const auto it = map.find(name);
			return it == map.end() ? 0 : it->second;
		}
	}

	void Converter::Convert() {
		while (m_input_stream) {
			ReadNext();
			if (!ParseZero() && !ParseNonZero()) {
				m_output_streams.WriteNext(m_original_word, m_spaces);
			}
		}
	}

	bool Converter::ParseZero() {
		if (m_word != "zero") {
			return false;
		}
		m_output_streams.WriteNext(0, m_spaces);
		return true;
	}

	bool Converter::ParseNonZero() {
		int n = 0;
		int last_multiplier = 0;
		while (true) {
			const int triplet = ParseThreeDigits();
			if (triplet == 0) {
				if (n != 0) {
					m_read_again = true;
				}
				break;
			}
			ReadNext();
			const int multiplier = GetNumber(m_word, s_multipliers);
			if (multiplier == 0 || (last_multiplier != 0 && multiplier > last_multiplier) ||
				(multiplier == 1000000000 && triplet > 1)) {
				n += triplet;
				m_read_again = true;
				break;
			}
			n += triplet * multiplier;
			if (m_ended) {
				break;
			}
			last_multiplier = multiplier;
			ReadNext();
		}
		if (n != 0) {
			m_output_streams.WriteNext(n, GetSpaces());
		}
		return n != 0;
	}

	int Converter::ParseThreeDigits() {
		int n = GetNumber(m_word, s_digits);
		if (n != 0) {
			if (m_ended) {
				return n;
			}
			ReadNext();
			if (m_word != "hundred") {
				m_read_again = true;
				return n;
			}
			n *= 100;
			if (m_ended) {
				return n;
			}
			ReadNext();
			if (m_word != "and") {
				m_read_again = true;
				return n;
			}
			ReadNext();
			const int digit = GetNumber(m_word, s_digits);
			if (digit != 0) {
				return n + digit;
			}
		}
		return n + ParseTwoDigits();
	}

	int Converter::ParseTwoDigits() {
		const int teens = GetNumber(m_word, s_teens);
		if (teens != 0) {
			return teens;
		}
		int tens = GetNumber(m_word, s_tens);
		if (tens != 0) {
			return tens;
		}
		const auto pos = m_word.find('-');
		if (pos != std::string::npos) {
			const std::string part1 = m_word.substr(0, pos);
			const std::string part2 = m_word.substr(pos + 1);
			tens = GetNumber(part1, s_tens);
			if (tens != 0) {
				const int digit = GetNumber(part2, s_digits);
				if (digit != 0) {
					return tens + digit;
				}
			}
		}
		return 0;
	}

	void Converter::ReadNext() {
		if (m_read_again) {
			m_read_again = false;
			return;
		}
		const auto pair = m_input_stream.ReadNext();
		m_original_word = pair.first;
		m_word.resize(m_original_word.size());
		std::transform(m_original_word.begin(), m_original_word.end(), m_word.begin(),
			[](unsigned char c) { return std::tolower(c); });
		m_previous_spaces = m_spaces;
		m_spaces = pair.second;
		m_ended = !m_input_stream || m_spaces.find('.') != std::string::npos;
	}

	const std::string& Converter::GetSpaces() const {
		return m_read_again ? m_previous_spaces : m_spaces;
	}
}
