BEGIN;

--for every person indicate that they are currently alive
UPDATE person
	SET dead = 0;
	
--give every person a phone number
UPDATE person
	SET phone_number = "9728675309"
	WHERE 
	first_name = "Zed" AND
	last_name = "Shaw";
	
UPDATE person
	SET phone_number = "9728242147"
	WHERE
	first_name = "Ashley" AND
	last_name = "Tharp";
	
--give every person a birthday
UPDATE person
	SET dob = "1968-02-15"
	WHERE
	first_name = "Zed" AND
	last_name = "Shaw";
	
UPDATE person
	SET dob = "1988-09-23"
	WHERE
	first_name = "Ashley" AND
	last_name = "Tharp";
	
--give every pet a birthday
UPDATE pet
	SET dob = "1000-03-17"
	WHERE
	id = 0;
	
UPDATE pet
	SET dob = "1000-03-17"
	WHERE
	id = 1;

UPDATE pet
	SET dob = "2014-08-21"
	WHERE
	id = 2;

UPDATE pet
	SET dob = "2013-11-02"
	WHERE
	id = 3;	
	
--give every pet a parent
UPDATE pet
	SET parent = 0
	WHERE id = 0 OR
	id = 1 OR
	id = 2;
	
UPDATE pet
	SET parent = 1
	WHERE id = 3;
	
--add date of purchase for every pet

--when Zed purchased Unicorn
UPDATE person_pet
		SET purchased_on = "1986-12-13"
		WHERE
		person_id = 0 AND
		pet_id = 0;
		
--when Zed purchased the robot
UPDATE person_pet
	SET purchased_on = "1974-03-03"
	WHERE
	person_id = 0 AND
	pet_id = 1;
	
--when Ashley purchased Miss Littles
UPDATE person_pet
	SET purchased_on = "2014-04-04"
	WHERE
	person_id = 1 AND
	pet_id = 2;
	
COMMIT;