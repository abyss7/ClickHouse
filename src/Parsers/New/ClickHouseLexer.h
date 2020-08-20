
// Generated from ClickHouseLexer.g4 by ANTLR 4.8

#pragma once


#include "antlr4-runtime.h"


namespace DB {


class  ClickHouseLexer : public antlr4::Lexer {
public:
  enum {
    INTERVAL_TYPE = 1, ALIAS = 2, ALL = 3, AND = 4, ANTI = 5, ANY = 6, ARRAY = 7, 
    AS = 8, ASCENDING = 9, ASOF = 10, BETWEEN = 11, BOTH = 12, BY = 13, 
    CASE = 14, CAST = 15, CHECK = 16, CLUSTER = 17, COLLATE = 18, CREATE = 19, 
    CROSS = 20, DATABASE = 21, DAY = 22, DEDUPLICATE = 23, DEFAULT = 24, 
    DELETE = 25, DESC = 26, DESCENDING = 27, DESCRIBE = 28, DISK = 29, DISTINCT = 30, 
    DROP = 31, ELSE = 32, END = 33, ENGINE = 34, EXISTS = 35, EXTRACT = 36, 
    FINAL = 37, FIRST = 38, FORMAT = 39, FROM = 40, FULL = 41, GLOBAL = 42, 
    GROUP = 43, HAVING = 44, HOUR = 45, ID = 46, IF = 47, IN = 48, INF = 49, 
    INNER = 50, INSERT = 51, INTERVAL = 52, INTO = 53, IS = 54, JOIN = 55, 
    KEY = 56, LAST = 57, LEADING = 58, LEFT = 59, LIKE = 60, LIMIT = 61, 
    LOCAL = 62, MATERIALIZED = 63, MINUTE = 64, MONTH = 65, NAN_SQL = 66, 
    NOT = 67, NULL_SQL = 68, NULLS = 69, OFFSET = 70, ON = 71, OPTIMIZE = 72, 
    OR = 73, ORDER = 74, OUTER = 75, OUTFILE = 76, PARTITION = 77, PREWHERE = 78, 
    PRIMARY = 79, QUARTER = 80, RIGHT = 81, SAMPLE = 82, SECOND = 83, SELECT = 84, 
    SEMI = 85, SET = 86, SETTINGS = 87, SHOW = 88, TABLE = 89, TABLES = 90, 
    TEMPORARY = 91, THEN = 92, TO = 93, TOTALS = 94, TRAILING = 95, TRIM = 96, 
    TTL = 97, UNION = 98, USE = 99, USING = 100, VALUES = 101, VOLUME = 102, 
    WEEK = 103, WHEN = 104, WHERE = 105, WITH = 106, YEAR = 107, IDENTIFIER = 108, 
    FLOATING_LITERAL = 109, HEXADECIMAL_LITERAL = 110, INTEGER_LITERAL = 111, 
    STRING_LITERAL = 112, ARROW = 113, ASTERISK = 114, BACKQUOTE = 115, 
    BACKSLASH = 116, COLON = 117, COMMA = 118, CONCAT = 119, DASH = 120, 
    DOT = 121, EQ_DOUBLE = 122, EQ_SINGLE = 123, GE = 124, GT = 125, LBRACKET = 126, 
    LE = 127, LPAREN = 128, LT = 129, NOT_EQ = 130, PERCENT = 131, PLUS = 132, 
    QUERY = 133, QUOTE_SINGLE = 134, RBRACKET = 135, RPAREN = 136, SEMICOLON = 137, 
    SLASH = 138, UNDERSCORE = 139, SINGLE_LINE_COMMENT = 140, MULTI_LINE_COMMENT = 141, 
    WHITESPACE = 142
  };

  ClickHouseLexer(antlr4::CharStream *input);
  ~ClickHouseLexer();

  virtual std::string getGrammarFileName() const override;
  virtual const std::vector<std::string>& getRuleNames() const override;

  virtual const std::vector<std::string>& getChannelNames() const override;
  virtual const std::vector<std::string>& getModeNames() const override;
  virtual const std::vector<std::string>& getTokenNames() const override; // deprecated, use vocabulary instead
  virtual antlr4::dfa::Vocabulary& getVocabulary() const override;

  virtual const std::vector<uint16_t> getSerializedATN() const override;
  virtual const antlr4::atn::ATN& getATN() const override;

private:
  static std::vector<antlr4::dfa::DFA> _decisionToDFA;
  static antlr4::atn::PredictionContextCache _sharedContextCache;
  static std::vector<std::string> _ruleNames;
  static std::vector<std::string> _tokenNames;
  static std::vector<std::string> _channelNames;
  static std::vector<std::string> _modeNames;

  static std::vector<std::string> _literalNames;
  static std::vector<std::string> _symbolicNames;
  static antlr4::dfa::Vocabulary _vocabulary;
  static antlr4::atn::ATN _atn;
  static std::vector<uint16_t> _serializedATN;


  // Individual action functions triggered by action() above.

  // Individual semantic predicate functions triggered by sempred() above.

  struct Initializer {
    Initializer();
  };
  static Initializer _init;
};

}  // namespace DB
