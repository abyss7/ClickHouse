
// Generated from ClickHouseLexer.g4 by ANTLR 4.8

#pragma once


#include "antlr4-runtime.h"


namespace DB {


class  ClickHouseLexer : public antlr4::Lexer {
public:
  enum {
    ALL = 1, AND = 2, ANTI = 3, ANY = 4, ARRAY = 5, AS = 6, ASCENDING = 7, 
    ASOF = 8, BETWEEN = 9, BOTH = 10, BY = 11, CASE = 12, CAST = 13, COLLATE = 14, 
    CROSS = 15, DAY = 16, DESCENDING = 17, DISTINCT = 18, ELSE = 19, END = 20, 
    EXTRACT = 21, FINAL = 22, FIRST = 23, FORMAT = 24, FROM = 25, FULL = 26, 
    GLOBAL = 27, GROUP = 28, HAVING = 29, HOUR = 30, IN = 31, INNER = 32, 
    INSERT = 33, INTERVAL = 34, INTO = 35, IS = 36, JOIN = 37, LAST = 38, 
    LEADING = 39, LEFT = 40, LIKE = 41, LIMIT = 42, LOCAL = 43, MINUTE = 44, 
    MONTH = 45, NOT = 46, NULL_SQL = 47, NULLS = 48, OFFSET = 49, ON = 50, 
    OR = 51, ORDER = 52, OUTER = 53, OUTFILE = 54, PREWHERE = 55, QUARTER = 56, 
    RIGHT = 57, SAMPLE = 58, SECOND = 59, SELECT = 60, SEMI = 61, SETTINGS = 62, 
    THEN = 63, TOTALS = 64, TRAILING = 65, TRIM = 66, UNION = 67, USING = 68, 
    WEEK = 69, WHEN = 70, WHERE = 71, WITH = 72, YEAR = 73, INTERVAL_TYPE = 74, 
    IDENTIFIER = 75, NUMBER_LITERAL = 76, STRING_LITERAL = 77, ARROW = 78, 
    ASTERISK = 79, BACKQUOTE = 80, BACKSLASH = 81, COLON = 82, COMMA = 83, 
    CONCAT = 84, DASH = 85, DOT = 86, EQ = 87, EQ_DOUBLE = 88, EQ_SINGLE = 89, 
    GE = 90, GT = 91, LBRACKET = 92, LE = 93, LPAREN = 94, LT = 95, NOT_EQ = 96, 
    PERCENT = 97, PLUS = 98, QUERY = 99, QUOTE_SINGLE = 100, RBRACKET = 101, 
    RPAREN = 102, SEMICOLON = 103, SLASH = 104, UNDERSCORE = 105, LINE_COMMENT = 106, 
    WHITESPACE = 107
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
