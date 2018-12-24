SET send_logs_level = 'none';

DROP TABLE IF EXISTS test.join1;
DROP TABLE IF EXISTS test.join2;
DROP TABLE IF EXISTS test.join3;

CREATE TABLE test.join1 ( a Int8,  b Int8) ENGINE = MergeTree ORDER BY a;
CREATE TABLE test.join2 ( c Int8,  d Int8) ENGINE = MergeTree ORDER BY c;
CREATE TABLE test.join3 ( a Int8,  e Int8) ENGINE = MergeTree ORDER BY e;

INSERT INTO test.join1 VALUES (1,1) (2,2);
INSERT INTO test.join2 VALUES (1,1) (2,2) (3,3);
INSERT INTO test.join3 VALUES (1,1) (2,2) (4,4);

SELECT 'ALL LEFT JOIN USING';

/* test USING on missing column */
SELECT a FROM test.join1 LEFT JOIN test.join2 USING a; -- { serverError 10 }
SELECT a FROM test.join1 LEFT JOIN test.join2 USING c; -- { serverError 47 }

/* test SELECT with USING */
SELECT a FROM test.join1 LEFT JOIN test.join3 USING a FORMAT Vertical;
SELECT join3.a FROM test.join1 LEFT JOIN test.join3 USING a FORMAT Vertical;
SELECT test.join3.a FROM test.join1 LEFT JOIN test.join3 USING a FORMAT Vertical;

SELECT b FROM test.join1 LEFT JOIN test.join3 USING a FORMAT Vertical;

SELECT e FROM test.join1 LEFT JOIN test.join3 USING a FORMAT Vertical;
SELECT join3.e FROM test.join1 LEFT JOIN test.join3 USING a FORMAT Vertical;
SELECT test.join3.e FROM test.join1 LEFT JOIN test.join3 USING a FORMAT Vertical;

SELECT a, b FROM test.join1 LEFT JOIN test.join3 USING a FORMAT Vertical;
SELECT a, e FROM test.join1 LEFT JOIN test.join3 USING a FORMAT Vertical;
SELECT a, join3.e FROM test.join1 LEFT JOIN test.join3 USING a FORMAT Vertical;
SELECT a, test.join3.e FROM test.join1 LEFT JOIN test.join3 USING a FORMAT Vertical;

SELECT a, b FROM test.join3 LEFT JOIN test.join1 USING a FORMAT Vertical;
SELECT a, e FROM test.join3 LEFT JOIN test.join1 USING a FORMAT Vertical;

SELECT * FROM test.join1 LEFT JOIN test.join3 USING a FORMAT Vertical;
SELECT * FROM test.join3 LEFT JOIN test.join1 USING a FORMAT Vertical;

SELECT 'ALL LEFT JOIN ON';

/* test JOIN ON on missing column */
SELECT a FROM test.join1 LEFT JOIN test.join2 ON test.join1.a = test.join1.a; -- { serverError 403 }
SELECT a FROM test.join1 LEFT JOIN test.join2 ON test.join1.a = test.join1.b; -- { serverError 403 }
SELECT a FROM test.join1 LEFT JOIN test.join2 ON test.join1.a = test.join2.a; -- { serverError 47 }

/* test SELECT with JOIN ON */
SELECT a FROM test.join1 LEFT JOIN test.join2 ON test.join1.a = test.join2.c FORMAT Vertical;
SELECT b FROM test.join1 LEFT JOIN test.join2 ON test.join1.a = test.join2.c FORMAT Vertical;
SELECT c FROM test.join1 LEFT JOIN test.join2 ON test.join1.a = test.join2.c FORMAT Vertical;
SELECT join2.c FROM test.join1 LEFT JOIN test.join2 ON test.join1.a = test.join2.c FORMAT Vertical;
SELECT test.join2.c FROM test.join1 LEFT JOIN test.join2 ON test.join1.a = test.join2.c FORMAT Vertical;

SELECT a FROM test.join1 LEFT JOIN test.join3 ON test.join1.a = test.join3.a FORMAT Vertical;
SELECT join3.a FROM test.join1 LEFT JOIN test.join3 ON test.join1.a = test.join3.a FORMAT Vertical;
SELECT test.join3.a FROM test.join1 LEFT JOIN test.join3 ON test.join1.a = test.join3.a FORMAT Vertical;

SELECT a, b FROM test.join1 LEFT JOIN test.join2 ON test.join1.a = test.join2.c FORMAT Vertical;
SELECT a, c FROM test.join1 LEFT JOIN test.join2 ON test.join1.a = test.join2.c FORMAT Vertical;
SELECT a, join2.c FROM test.join1 LEFT JOIN test.join2 ON test.join1.a = test.join2.c FORMAT Vertical;
SELECT a, test.join2.c FROM test.join1 LEFT JOIN test.join2 ON test.join1.a = test.join2.c FORMAT Vertical;

SELECT a, b FROM test.join2 LEFT JOIN test.join1 ON test.join1.a = test.join2.c FORMAT Vertical;
SELECT a, c FROM test.join2 LEFT JOIN test.join1 ON test.join1.a = test.join2.c FORMAT Vertical;

SELECT * FROM test.join1 LEFT JOIN test.join2 ON test.join1.a = test.join2.c FORMAT Vertical;
SELECT * FROM test.join1 LEFT JOIN test.join3 ON test.join1.a = test.join3.e FORMAT Vertical;
SELECT * FROM test.join2 LEFT JOIN test.join1 ON test.join1.a = test.join2.c FORMAT Vertical;
SELECT * FROM test.join3 LEFT JOIN test.join1 ON test.join1.a = test.join3.e FORMAT Vertical;

SELECT 'ALL RIGHT JOIN USING';

/* test USING on missing column */
-- TODO: SELECT c FROM test.join2 RIGHT JOIN test.join1 USING c; -- { serverError 10 }
-- TODO: SELECT c FROM test.join2 RIGHT JOIN test.join1 USING a; -- { serverError 47 }

/* test SELECT with USING */
SELECT a FROM test.join3 RIGHT JOIN test.join1 USING a FORMAT Vertical;
-- TODO: SELECT join1.a FROM test.join3 RIGHT JOIN test.join1 USING a FORMAT Vertical;
-- TODO: SELECT test.join1.a FROM test.join3 RIGHT JOIN test.join1 USING a FORMAT Vertical;

SELECT e FROM test.join3 RIGHT JOIN test.join1 USING a FORMAT Vertical;

SELECT b FROM test.join3 RIGHT JOIN test.join1 USING a FORMAT Vertical;
SELECT join1.b FROM test.join3 RIGHT JOIN test.join1 USING a FORMAT Vertical;
SELECT test.join1.b FROM test.join3 RIGHT JOIN test.join1 USING a FORMAT Vertical;

SELECT a, e FROM test.join3 RIGHT JOIN test.join1 USING a FORMAT Vertical;
SELECT a, b FROM test.join3 RIGHT JOIN test.join1 USING a FORMAT Vertical;
SELECT a, join1.b FROM test.join3 RIGHT JOIN test.join1 USING a FORMAT Vertical;
SELECT a, test.join1.b FROM test.join3 RIGHT JOIN test.join1 USING a FORMAT Vertical;

SELECT a, e FROM test.join1 RIGHT JOIN test.join3 USING a FORMAT Vertical;
SELECT a, b FROM test.join1 RIGHT JOIN test.join3 USING a FORMAT Vertical;

-- TODO: SELECT * FROM test.join3 RIGHT JOIN test.join1 USING a FORMAT Vertical;
-- TODO: SELECT * FROM test.join1 RIGHT JOIN test.join3 USING a FORMAT Vertical;

SELECT 'ALL RIGHT JOIN ON';

/* test JOIN ON on missing column */
SELECT c FROM test.join2 RIGHT JOIN test.join1 ON test.join2.c = test.join2.c; -- { serverError 403 }
SELECT c FROM test.join2 RIGHT JOIN test.join1 ON test.join2.c = test.join2.d; -- { serverError 403 }
SELECT c FROM test.join2 RIGHT JOIN test.join1 ON test.join2.c = test.join1.c; -- { serverError 47 }

/* test SELECT with JOIN ON */
SELECT c FROM test.join2 RIGHT JOIN test.join1 ON test.join1.a = test.join2.c FORMAT Vertical;
SELECT d FROM test.join2 RIGHT JOIN test.join1 ON test.join1.a = test.join2.c FORMAT Vertical;
-- TODO: SELECT a FROM test.join2 RIGHT JOIN test.join1 ON test.join1.a = test.join2.c FORMAT Vertical;
-- TODO: SELECT join1.a FROM test.join2 RIGHT JOIN test.join1 ON test.join1.a = test.join2.c FORMAT Vertical;
-- TODO: SELECT test.join1.a FROM test.join2 RIGHT JOIN test.join1 ON test.join1.a = test.join2.c FORMAT Vertical;

SELECT a FROM test.join3 RIGHT JOIN test.join1 ON test.join1.a = test.join3.a FORMAT Vertical;
-- TODO: SELECT join1.a FROM test.join3 RIGHT JOIN test.join1 ON test.join1.a = test.join3.a FORMAT Vertical;
-- TODO: SELECT test.join1.a FROM test.join3 RIGHT JOIN test.join1 ON test.join1.a = test.join3.a FORMAT Vertical;

SELECT c, d FROM test.join2 RIGHT JOIN test.join1 ON test.join1.a = test.join2.c FORMAT Vertical;
-- TODO: SELECT c, a FROM test.join2 RIGHT JOIN test.join1 ON test.join1.a = test.join2.c FORMAT Vertical;
-- TODO: SELECT c, join1.a FROM test.join2 RIGHT JOIN test.join1 ON test.join1.a = test.join2.c FORMAT Vertical;
-- TODO: SELECT c, test.join1.a FROM test.join2 RIGHT JOIN test.join1 ON test.join1.a = test.join2.c FORMAT Vertical;

-- TODO: SELECT c, d FROM test.join1 RIGHT JOIN test.join2 ON test.join1.a = test.join2.c FORMAT Vertical;
-- TODO: SELECT c, a FROM test.join1 RIGHT JOIN test.join2 ON test.join1.a = test.join2.c FORMAT Vertical;

-- TODO: SELECT * FROM test.join2 RIGHT JOIN test.join1 ON test.join1.a = test.join2.c FORMAT Vertical;
-- TODO: SELECT * FROM test.join3 RIGHT JOIN test.join1 ON test.join1.a = test.join3.e FORMAT Vertical;
-- TODO: SELECT * FROM test.join1 RIGHT JOIN test.join2 ON test.join1.a = test.join2.c FORMAT Vertical;
-- TODO: SELECT * FROM test.join1 RIGHT JOIN test.join3 ON test.join1.a = test.join3.e FORMAT Vertical;
