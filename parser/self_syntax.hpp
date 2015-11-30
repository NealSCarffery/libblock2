// generated by MyParser C++ Code Generator

#pragma once

#include "./myparser.hpp"

namespace myparser {

template<>
class RuleDef<MP_STR("root")>:
public RuleList<MP_STR("root"),
    RuleLine<
        RuleItemSpace<>,
        RuleItemRef<MP_STR("blocks")>,
        RuleItemSpace<>
    >
> {};

template<>
class RuleDef<MP_STR("space")>:
public RuleList<MP_STR("space"),
    RuleLine<
        RuleItemRef<MP_STR("comment line"), TagAny0>
    >
> {};

template<>
class RuleDef<MP_STR("keyword")>:
public RuleList<MP_STR("keyword"),
    RuleLine<
        RuleItemRef<MP_STR("id")>
    >,
    RuleLine<
        RuleItemRef<MP_STR("sign")>
    >
> {};

template<>
class RuleDef<MP_STR("blocks")>:
public RuleList<MP_STR("blocks"),
    RuleLine<
        RuleItemRef<MP_STR("block"), TagAny1>
    >
> {};

template<>
class RuleDef<MP_STR("block")>:
public RuleList<MP_STR("block"),
    RuleLine<
        RuleItemRef<MP_STR("list head")>,
        RuleItemSpace<>,
        RuleItemRef<MP_STR("list body")>,
        RuleItemSpace<>
    >,
    RuleLine<
        RuleItemRef<MP_STR("builtin head")>,
        RuleItemSpace<>,
        RuleItemRef<MP_STR("list body")>,
        RuleItemSpace<>
    >,
    RuleLine<
        RuleItemRef<MP_STR("regex head")>,
        RuleItemSpace<>,
        RuleItemRef<MP_STR("regex line")>,
        RuleItemSpace<>
    >
> {};

template<>
class RuleDef<MP_STR("list head")>:
public RuleList<MP_STR("list head"),
    RuleLine<
        RuleItemRef<MP_STR("id")>,
        RuleItemKeyword<MP_STR(":")>,
        RuleItemRef<MP_STR("line break")>
    >
> {};

template<>
class RuleDef<MP_STR("builtin head")>:
public RuleList<MP_STR("builtin head"),
    RuleLine<
        RuleItemKeyword<MP_STR("**")>,
        RuleItemRef<MP_STR("id")>,
        RuleItemKeyword<MP_STR("**:")>,
        RuleItemRef<MP_STR("line break")>
    >
> {};

template<>
class RuleDef<MP_STR("regex head")>:
public RuleList<MP_STR("regex head"),
    RuleLine<
        RuleItemKeyword<MP_STR("*")>,
        RuleItemRef<MP_STR("id")>,
        RuleItemKeyword<MP_STR("*:")>,
        RuleItemRef<MP_STR("line break")>
    >
> {};

template<>
class RuleDef<MP_STR("list body")>:
public RuleList<MP_STR("list body"),
    RuleLine<
        RuleItemRef<MP_STR("list line")>,
        RuleItemSpace<>,
        RuleItemRef<MP_STR("list body")>
    >,
    RuleLine<
        RuleItemRef<MP_STR("list line")>
    >
> {};

template<>
class RuleDef<MP_STR("list line")>:
public RuleList<MP_STR("list line"),
    RuleLine<
        RuleItemRef<MP_STR("indent")>,
        RuleItemRef<MP_STR("list items")>,
        RuleItemRef<MP_STR("line break")>
    >
> {};

template<>
class RuleDef<MP_STR("regex line")>:
public RuleList<MP_STR("regex line"),
    RuleLine<
        RuleItemRef<MP_STR("indent")>,
        RuleItemRef<MP_STR("anything")>,
        RuleItemRef<MP_STR("line break")>
    >
> {};

template<>
class RuleDef<MP_STR("comment line")>:
public RuleList<MP_STR("comment line"),
    RuleLine<
        RuleItemRef<MP_STR("indent")>,
        RuleItemKeyword<MP_STR("//")>,
        RuleItemRef<MP_STR("anything")>,
        RuleItemRef<MP_STR("line break")>
    >,
    RuleLine<
        RuleItemRef<MP_STR("other markdown")>,
        RuleItemRef<MP_STR("line break")>
    >,
    RuleLine<
        RuleItemRef<MP_STR("line break")>
    >
> {};

template<>
class RuleDef<MP_STR("list items")>:
public RuleList<MP_STR("list items"),
    RuleLine<
        RuleItemRef<MP_STR("list item"), TagAny0>
    >
> {};

template<>
class RuleDef<MP_STR("list item")>:
public RuleList<MP_STR("list item"),
    RuleLine<
        RuleItemKeyword<MP_STR(" ")>
    >,
    RuleLine<
        RuleItemRef<MP_STR("empty item")>
    >,
    RuleLine<
        RuleItemRef<MP_STR("keyword item")>
    >,
    RuleLine<
        RuleItemRef<MP_STR("ref item")>
    >,
    RuleLine<
        RuleItemRef<MP_STR("error item")>
    >
> {};

template<>
class RuleDef<MP_STR("empty item")>:
public RuleList<MP_STR("empty item"),
    RuleLine<
        RuleItemKeyword<MP_STR("<")>,
        RuleItemKeyword<MP_STR(">")>
    >
> {};

template<>
class RuleDef<MP_STR("keyword item")>:
public RuleRegex<MP_STR("keyword item"),
    MP_STR("([^ \\r\\n\\\\<]|\\\\.)+")
> {};

template<>
class RuleDef<MP_STR("ref item")>:
public RuleList<MP_STR("ref item"),
    RuleLine<
        RuleItemKeyword<MP_STR("<")>,
        RuleItemRef<MP_STR("id")>,
        RuleItemKeyword<MP_STR(">")>
    >,
    RuleLine<
        RuleItemKeyword<MP_STR("<?")>,
        RuleItemRef<MP_STR("id")>,
        RuleItemKeyword<MP_STR(">")>
    >,
    RuleLine<
        RuleItemKeyword<MP_STR("<*")>,
        RuleItemRef<MP_STR("id")>,
        RuleItemKeyword<MP_STR(">")>
    >,
    RuleLine<
        RuleItemKeyword<MP_STR("<+")>,
        RuleItemRef<MP_STR("id")>,
        RuleItemKeyword<MP_STR(">")>
    >
> {};

template<>
class RuleDef<MP_STR("error item")>:
public RuleList<MP_STR("error item"),
    RuleLine<
        RuleItemKeyword<MP_STR("<!")>,
        RuleItemRef<MP_STR("id")>,
        RuleItemKeyword<MP_STR(">")>
    >
> {};

template<>
class RuleDef<MP_STR("id")>:
public RuleRegex<MP_STR("id"),
    MP_STR("\\w([\\w ]*\\w)?")
> {};

template<>
class RuleDef<MP_STR("sign")>:
public RuleRegex<MP_STR("sign"),
    MP_STR("\\**:|\\*+| +|\\/\\/|<[\\*\\+\\?\\!]?|>")
> {};

template<>
class RuleDef<MP_STR("other markdown")>:
public RuleRegex<MP_STR("other markdown"),
    MP_STR("( ? ? ?)[^ \\r\\n].*[^:\\r\\n]|.|")
> {};

template<>
class RuleDef<MP_STR("indent")>:
public RuleRegex<MP_STR("indent"),
    MP_STR("(    )")
> {};

template<>
class RuleDef<MP_STR("line break")>:
public RuleRegex<MP_STR("line break"),
    MP_STR("[\\r\\n]+")
> {};

template<>
class RuleDef<MP_STR("anything")>:
public RuleRegex<MP_STR("anything"),
    MP_STR(".*")
> {};


}
