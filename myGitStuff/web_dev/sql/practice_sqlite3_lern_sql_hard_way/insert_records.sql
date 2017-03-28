
BEGIN;

--create the people
INSERT INTO person(id, first_name, last_name, age)
	VALUES (0, "Zed", "Shaw", 37);
	
INSERT INTO person(id, first_name, last_name, age)
	VALUES (1, "Ashley", "Tharp", 27);
	
--create the pets
INSERT INTO pet(id, name, breed, age, dead)
	VALUES (0, "Fluffy", "Unicorn", 1000, 0);
	
INSERT INTO pet(id, name, breed, age, dead)
	VALUES (1, "Gigantor", "Robot", 1, 1);
	
INSERT INTO pet(id, name, breed, age, dead)
	VALUES (2, "Littles", "Kittay", 1, 0);

--create the ownership relations between the people and the pets
INSERT INTO person_pet (person_id, pet_id) VALUES (0, 0); --Zed owns Fluffy
INSERT INTO person_pet (person_id, pet_id) VALUES (0, 1); --Zed owns Gigantor
INSERT INTO person_pet (person_id, pet_id) VALUES (1, 2); --Ashley owns Littles

COMMIT;