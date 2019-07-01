#! /usr/bin/env python3
# -*- coding: utf-8 -*-

# `pip install …`
from fuzzingbook import Grammars, GrammarFuzzer  # … fuzzingbook

import copy
import random
import re
import string
import time


BASIC_GRAMMAR = {
    "<sign>"        : ["+", "-"],
    "<digit>"       : [d for d in string.digits],
    "<letter>"      : [c for c in string.ascii_lowercase],
    "<symbol>"      : ["<letter>", "_", "<digit>"],
    "<integer>"     : ["<sign>?<digit>+"],
    "<string>"      : ["'<letter>*'"],
    "<literal>"     : ["<integer>", "<string>"],
    "<identifier>"  : ["<letter><symbol>*"],
}

IDENTIFIER_GRAMMAR = {
    "<DatabaseId>"  : ["<identifier>"],
    "<TableId>"     : ["(<DatabaseId>.)?<identifier>"],
    "<ColumnId>"    : ["(<TableId>.)?<identifier>"],
}

OPERATOR_GRAMMAR = {
    "<UnaryOp>" : ["NOT", "-"],
    "<BinaryOp>": ["*", "/", "%", "+", "-"],
}

COLUMN_GRAMMAR = {
    "<ColumnExprList>"      : ["<ColumnExpr>(, <ColumnExpr>)*"],
    "<ColumnExpr>"          : ["<ColumnUnaryExpr>", "<ColumnExpr> <BinaryOp> <ColumnExpr>"],
    "<ColumnUnaryExpr>"     : ["<ColumnPrimaryExpr>", "<UnaryOp> <ColumnUnaryExpr>"],
    "<ColumnPrimaryExpr>"   : ["<literal>", "<ColumnId>", "<ColumnFuncCall>", "( <ColumnExpr> )"],
    "<ColumnFuncCall>"      : ["<identifier>(<ColumnExprList>)"],
}

TABLE_GRAMMAR = {
    "<TableExprList>": ["<TableExpr>(, <TableExpr>)*"],
    "<TableExpr>": ["<TablePrimaryExpr>"],
    "<TablePrimaryExpr>": ["<TableId>", "( <TableExpr> )"],
}

SELECT_GRAMMAR = {
    "<SelectQuery>": ["SELECT <ColumnExprList>( FROM <TableExprList>)?( WHERE <ColumnExpr>)?"],
}

CLICKHOUSE_GRAMMAR = {
    "<start>"       : ["<QueryList>"],
    "<QueryList>"   : ["<Query>(; <Query>)*"],
    "<Query>"       : ["<SelectQuery>"],
}

RE_EXTENDED_NONTERMINAL = re.compile(r'(<[^<> ]*>[?+*])')
RE_PARENTHESIZED_EXPR = re.compile(r'\([^()]*\)[?+*]')


def extend_grammar(grammar, extension={}):
    new_grammar = copy.deepcopy(grammar)
    new_grammar.update(extension)
    return new_grammar


def new_symbol(grammar, symbol_name="<tmp_symbol>"):
    if symbol_name not in grammar:
        return symbol_name

    count = 1
    while True:
        tentative_symbol_name = symbol_name[:-1] + "-" + repr(count) + ">"
        if tentative_symbol_name not in grammar:
            return tentative_symbol_name
        count += 1


def extended_nonterminals(expansion):
    if isinstance(expansion, tuple):
        expansion = expansion[0]

    return re.findall(RE_EXTENDED_NONTERMINAL, expansion)


def parenthesized_expressions(expansion):
    if isinstance(expansion, tuple):
        expansion = expansion[0]

    return re.findall(RE_PARENTHESIZED_EXPR, expansion)


def convert_ebnf_parentheses(ebnf_grammar):
    grammar = extend_grammar(ebnf_grammar)
    for nonterminal in ebnf_grammar:
        expansions = ebnf_grammar[nonterminal]

        for i in range(len(expansions)):
            expansion = expansions[i]

            while True:
                parenthesized_exprs = parenthesized_expressions(expansion)
                if len(parenthesized_exprs) == 0:
                    break

                for expr in parenthesized_exprs:
                    operator = expr[-1:]
                    contents = expr[1:-2]

                    new_sym = new_symbol(grammar)
                    expansion = grammar[nonterminal][i].replace(
                        expr, new_sym + operator, 1)
                    grammar[nonterminal][i] = expansion
                    grammar[new_sym] = [contents]

    return grammar


def convert_ebnf_operators(ebnf_grammar):
    grammar = extend_grammar(ebnf_grammar)
    for nonterminal in ebnf_grammar:
        expansions = ebnf_grammar[nonterminal]

        for i in range(len(expansions)):
            expansion = expansions[i]
            extended_symbols = extended_nonterminals(expansion)

            for extended_symbol in extended_symbols:
                operator = extended_symbol[-1:]
                original_symbol = extended_symbol[:-1]

                new_sym = new_symbol(grammar, original_symbol)
                grammar[nonterminal][i] = grammar[nonterminal][i].replace(
                    extended_symbol, new_sym, 1)

                if operator == '?':
                    grammar[new_sym] = ["", original_symbol]
                elif operator == '*':
                    grammar[new_sym] = ["", original_symbol + new_sym]
                elif operator == '+':
                    grammar[new_sym] = [
                        original_symbol, original_symbol + new_sym]

    return grammar


def convert_ebnf_grammar(grammar):
    return convert_ebnf_operators(convert_ebnf_parentheses(grammar))


def main():
    CLICKHOUSE_GRAMMAR.update(SELECT_GRAMMAR)
    CLICKHOUSE_GRAMMAR.update(TABLE_GRAMMAR)
    CLICKHOUSE_GRAMMAR.update(COLUMN_GRAMMAR)
    CLICKHOUSE_GRAMMAR.update(OPERATOR_GRAMMAR)
    CLICKHOUSE_GRAMMAR.update(IDENTIFIER_GRAMMAR)
    CLICKHOUSE_GRAMMAR.update(BASIC_GRAMMAR)

    grammar = convert_ebnf_grammar(CLICKHOUSE_GRAMMAR)

    assert Grammars.is_valid_grammar(grammar)

    random.seed()
    fuzzer = GrammarFuzzer.GrammarFuzzer(grammar, min_nonterminals=5, max_nonterminals=50)
    print(fuzzer.fuzz())


if __name__ == "__main__":
    exit(main())
