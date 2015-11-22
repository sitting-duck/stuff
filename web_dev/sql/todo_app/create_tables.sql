BEGIN;

CREATE TABLE `user` (

	id INTEGER PRIMARY KEY,
	name TEXT,
	password TEXT

);

CREATE TABLE todo (

	id INTEGER PRIMARY KEY,
	user INTEGER,
	item TEXT

);

COMMIT;