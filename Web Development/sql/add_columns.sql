BEGIN;

--add a dead column to person that's like the one in pet
ALTER TABLE person
	ADD dead INTEGER;
	
--add a phone number column to person
ALTER TABLE person
	ADD phone_number TEXT;
	
-- add date of birth column to both person and pet
ALTER TABLE person
	ADD dob DATETIME;
	
ALTER TABLE pet
	ADD dob DATETIME;
	
--add date of purchase to person_pet
ALTER TABLE person_pet
	ADD purchased_on DATETIME;
	
--add parent to pet table that holds id of pet's parent
ALTER TABLE pet
	ADD parent INTEGER;
	
COMMIT;