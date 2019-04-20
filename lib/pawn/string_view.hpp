#ifndef PAWN_STRING_VIEW_HPP
#define PAWN_STRING_VIEW_HPP

#if __cplusplus >= 201703L
#include <string_view>

namespace pawn {
    using string_view = std::basic_string_view<cell>;
};

#endif /* __cplusplus == 201703L */

#endif /* PAWN_STRING_VIEW_HPP */