CREATE TEMPORARY TABLE tmp_json (values text);
COPY tmp_json FROM '/home/osboxes/Desktop/MSSQL_Backup/Class.json';

CREATE TABLE Class (CID SERIAL, CName varchar(45), URL varchar(256), Since TIME WITH TIME ZONE, CNamemd5 bit(32));
CREATE TEMPORARY TABLE tmp_class (CID INTEGER, CNAME varchar(45), URL varchar(256), Since varchar(64), CNamemd5 varchar(64));

INSERT INTO tmp_class 
SELECT CAST(values->>'CID' AS INTEGER) AS CID, 
       CAST(values->>'CName' AS varchar) AS CName,
       CAST(values->>'URL' AS VARCHAR) AS URL,
       CAST(values->>'Since' AS VARCHAR) AS Since,
       CAST(values->>'CNamemd5' AS varchar) AS CNamemd5 
FROM (
    SELECT json_array_elements(replace(values, '/', '/') :: json) as values
    FROM tmp_json
    ) a;

SELECT * FROM tmp_class;

INSERT INTO Class(CName, URL)
SELECT CName, URL FROM tmp_class;