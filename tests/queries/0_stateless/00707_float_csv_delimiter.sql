DROP TEMPORARY TABLE IF EXISTS test_00707;
CREATE TEMPORARY TABLE test_00707 (x Float32, y Float64, z UInt64, s String);

INSERT INTO test_00707 FORMAT CSV 123.456,789.012,345678,Hello;

SET format_csv_delimiter = ';';
INSERT INTO test_00707 FORMAT CSV 123.456;789.012;345678;Hello;

SET format_csv_delimiter = ':';
INSERT INTO test_00707 FORMAT CSV 123.456:789.012:345678:Hello;

SET format_csv_delimiter = '|';
INSERT INTO test_00707 FORMAT CSV 123.456|789.012|345678|Hello;

SELECT * FROM test_00707;
