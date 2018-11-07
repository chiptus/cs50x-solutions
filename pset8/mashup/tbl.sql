CREATE TABLE places (
    country_code varchar(2),
    postal_code varchar(20),
    place_name varchar(180),
    admin_name1 varchar(100),
    admin_code1 varchar(20),
    admin_name2 varchar(100),
    admin_code2 varchar(20),
    admin_name3 varchar(100),
    admin_code3 varchar(20),
    latitude REAL,
    longitude REAL,
    accuracy INTEGER
)

CREATE VIRTUAL TABLE places_index USING fts4(state_code, state, city, postal_code, tokenize=porter);

INSERT INTO places_index (state_code, state, city, postal_code)
    SELECT admin_code1 as state_code, admin_name1 as state, place_name as city, postal_code FROM places;