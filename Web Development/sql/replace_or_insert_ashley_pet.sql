
BEGIN;

--this will replace the pet with the matching id or else insert a new pet if there isn't one with matching id
REPLACE INTO pet (id, name, breed, age, dead)
	VALUES (3, "Loki", "Big Cat", 34, 0);
	
REPLACE INTO pet (id, name, breed, age, dead)
	VALUES (2, "Miss Littles", "Kittay", 2, 0);
	
COMMIT;