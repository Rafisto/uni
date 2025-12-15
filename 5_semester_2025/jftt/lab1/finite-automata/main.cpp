#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>

#include <unicode/uchar.h>
#include <unicode/unistr.h>
#include <unicode/ustream.h>

using icu::UnicodeString;
using tf_t = std::map<std::pair<std::size_t, UChar32>, std::size_t>;

namespace {

tf_t compute_transition_function(const UnicodeString &pattern) {
    const std::size_t m = static_cast<std::size_t>(pattern.countChar32());
    tf_t tf;

    std::set<UChar32> alphabet;
    for (int32_t i = 0; i < pattern.length();) {
        UChar32 ch = pattern.char32At(i);
        alphabet.insert(ch);
        i += U16_LENGTH(ch);
    }

    for (std::size_t q = 0; q <= m; ++q) {
        for (UChar32 c : alphabet) {
            std::size_t k = std::min(m, q + 1);
            while (k > 0) {
                int32_t q32 = static_cast<int32_t>(q);
                int32_t k32 = static_cast<int32_t>(k);

                UnicodeString prefix = pattern.tempSubStringBetween(0, q32);
                prefix.append(c);
                UnicodeString target = pattern.tempSubStringBetween(0, k32);

                if (prefix.endsWith(target))
                    break;
                --k;
            }
            tf[{q, c}] = k;
        }
    }
    return tf;
}

UnicodeString read_utf8_file(const std::filesystem::path &filename) {
    std::ifstream infile(filename, std::ios::binary);
    if (!infile) {
        std::cerr << "file " << filename << " does not exist.\n";
        return UnicodeString();
    }

    std::string content((std::istreambuf_iterator<char>(infile)),
                        std::istreambuf_iterator<char>());
    return UnicodeString::fromUTF8(content);
}

void finite_automation_matcher(const UnicodeString &pattern,
                               const std::filesystem::path &filename) {
    const std::size_t m = static_cast<std::size_t>(pattern.countChar32());
    UnicodeString text = read_utf8_file(filename);
    if (text.isEmpty())
        return;

    tf_t tf = compute_transition_function(pattern);

    std::size_t q = 0;
    std::size_t index = 0;

    for (int32_t i = 0; i < text.length();) {
        UChar32 c = text.char32At(i);
        auto it = tf.find({q, c});
        if (it != tf.end())
            q = it->second;
        else
            q = 0;

        if (q == m)
            std::cout << "pattern occurs with shift " << (index + 1 - m)
                      << '\n';

        ++index;
        i += U16_LENGTH(c);
    }
}

} // namespace

int main(int argc, const char *argv[]) {
    if (argc != 3) {
        std::cout << argv[0] << " <pattern> <filename>\n";
        return 1;
    }

    UnicodeString pattern = UnicodeString::fromUTF8(argv[1]);
    std::filesystem::path filename = argv[2];
    finite_automation_matcher(pattern, filename);
}
