#ifdef DD_UNLOCK_FORMATTER_INCLUDE
// Do not include this file, include "engine_bridge.h"

#include <fmt/core.h>

#define DD_TYPE_FORMATTER_BEGIN(dd_type_, dd_var_)                                                              \
template <> struct fmt::formatter<dd_type_> {                                                                   \
    constexpr auto parse(format_parse_context& ctx) {return ctx.begin();}                                       \
    template <typename FormatContext>                                                                           \
    auto format(const dd_type_ &, FormatContext& ctx) -> decltype(ctx.out());                                   \
};                                                                                                              \
template <typename FormatContext>                                                                               \
auto fmt::formatter<dd_type_>::format(const dd_type_ & dd_var_ , FormatContext& ctx) -> decltype(ctx.out())     \


//
// point
DD_TYPE_FORMATTER_BEGIN(dd::point, p)
{
    return format_to(ctx.out(), "[{},{}]", p.x, p.y);
}

DD_TYPE_FORMATTER_BEGIN(dd::rect, r)
{
    return format_to(ctx.out(), "[({},{}),({},{})]", r.x, r.y, r.width, r.height);
}

#endif // DD_UNLOCK_FORMATTER_INCLUDE