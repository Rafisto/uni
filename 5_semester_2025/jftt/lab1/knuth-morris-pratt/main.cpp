#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include <unicode/uchar.h>
#include <unicode/unistr.h>
#include <unicode/ustream.h>

using icu::UnicodeString;
using pf_t = std::vector<std::size_t>;

namespace {

pf_t compute_prefix_function(const UnicodeString &pattern) {
    const std::size_t m = static_cast<std::size_t>(pattern.countChar32());
    pf_t pi(m, 0);

    std::size_t k = 0;
    for (std::size_t q = 2; q <= m; ++q) {
        while (k > 0) {
            UChar32 pk = pattern.char32At(static_cast<int32_t>(k));
            UChar32 pq = pattern.char32At(static_cast<int32_t>(q - 1));
            if (pk != pq)
                k = pi[k - 1];
            else
                break;
        }
        UChar32 pk = pattern.char32At(static_cast<int32_t>(k));
        UChar32 pq = pattern.char32At(static_cast<int32_t>(q - 1));
        if (pk == pq)
            ++k;
        pi[q - 1] = k;
    }
    return pi;
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

    pf_t pf = compute_prefix_function(pattern);

    std::size_t index = 1;
    std::size_t q = 0;

    for (int32_t i = 0; i < text.length();) {
        UChar32 c = text.char32At(i);

        while (q > 0 && pattern.char32At(static_cast<int32_t>(q)) != c) {
            q = pf[q - 1];
        }

        if (pattern.char32At(static_cast<int32_t>(q)) == c) {
            ++q;
        }

        if (q == m) {
            std::cout << "pattern occurs with shift " << index - m << '\n';
            q = pf[q - 1];
        }

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
