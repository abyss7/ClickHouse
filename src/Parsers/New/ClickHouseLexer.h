
// Generated from ClickHouseLexer.g4 by ANTLR 4.8

#pragma once


#include "antlr4-runtime.h"


namespace DB {


class  ClickHouseLexer : public antlr4::Lexer {
public:
  enum {
    INTERVAL_TYPE = 1, ADD = 2, AFTER = 3, ALIAS = 4, ALL = 5, ALTER = 6, 
    AND = 7, ANTI = 8, ANY = 9, ARRAY = 10, AS = 11, ASCENDING = 12, ASOF = 13, 
    ATTACH = 14, BETWEEN = 15, BOTH = 16, BY = 17, CASE = 18, CAST = 19, 
    CHECK = 20, CLEAR = 21, CLUSTER = 22, COLLATE = 23, COLUMN = 24, COMMENT = 25, 
    CREATE = 26, CROSS = 27, DATABASE = 28, DAY = 29, DEDUPLICATE = 30, 
    DEFAULT = 31, DELAY = 32, DELETE = 33, DESC = 34, DESCENDING = 35, DESCRIBE = 36, 
    DETACH = 37, DISK = 38, DISTINCT = 39, DROP = 40, ELSE = 41, END = 42, 
    ENGINE = 43, EXISTS = 44, EXTRACT = 45, FINAL = 46, FIRST = 47, FORMAT = 48, 
    FROM = 49, FULL = 50, GLOBAL = 51, GROUP = 52, HAVING = 53, HOUR = 54, 
    ID = 55, IF = 56, IN = 57, INF = 58, INNER = 59, INSERT = 60, INTERVAL = 61, 
    INTO = 62, IS = 63, JOIN = 64, KEY = 65, LAST = 66, LEADING = 67, LEFT = 68, 
    LIKE = 69, LIMIT = 70, LOCAL = 71, MATERIALIZED = 72, MINUTE = 73, MODIFY = 74, 
    MONTH = 75, NAN_SQL = 76, NO = 77, NOT = 78, NULL_SQL = 79, NULLS = 80, 
    OFFSET = 81, ON = 82, OPTIMIZE = 83, OR = 84, ORDER = 85, OUTER = 86, 
    OUTFILE = 87, PARTITION = 88, POPULATE = 89, PREWHERE = 90, PRIMARY = 91, 
    QUARTER = 92, RENAME = 93, REPLICA = 94, RIGHT = 95, SAMPLE = 96, SECOND = 97, 
    SELECT = 98, SEMI = 99, SET = 100, SETTINGS = 101, SHOW = 102, SYNC = 103, 
    SYSTEM = 104, TABLE = 105, TABLES = 106, TEMPORARY = 107, THEN = 108, 
    TIES = 109, TO = 110, TOTALS = 111, TRAILING = 112, TRIM = 113, TTL = 114, 
    UNION = 115, USE = 116, USING = 117, VALUES = 118, VIEW = 119, VOLUME = 120, 
    WEEK = 121, WHEN = 122, WHERE = 123, WITH = 124, YEAR = 125, IDENTIFIER = 126, 
    FLOATING_LITERAL = 127, HEXADECIMAL_LITERAL = 128, INTEGER_LITERAL = 129, 
    STRING_LITERAL = 130, ARROW = 131, ASTERISK = 132, BACKQUOTE = 133, 
    BACKSLASH = 134, COLON = 135, COMMA = 136, CONCAT = 137, DASH = 138, 
    DOT = 139, EQ_DOUBLE = 140, EQ_SINGLE = 141, GE = 142, GT = 143, LBRACKET = 144, 
    LE = 145, LPAREN = 146, LT = 147, NOT_EQ = 148, PERCENT = 149, PLUS = 150, 
    QUERY = 151, QUOTE_DOUBLE = 152, QUOTE_SINGLE = 153, RBRACKET = 154, 
    RPAREN = 155, SEMICOLON = 156, SLASH = 157, UNDERSCORE = 158, SINGLE_LINE_COMMENT = 159, 
    MULTI_LINE_COMMENT = 160, WHITESPACE = 161
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
