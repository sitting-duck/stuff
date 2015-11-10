BEGIN;

--list the columns that must be in the resultant table
SELECT person.first_name, pet.name
	--list the tables that will need to be acessed
	FROM person, pet, person_pet
	WHERE 
	--the pet was purchased after 2004
	person_pet.purchased_on > "2004-01-01" AND
	
	--the pet id matches the pet id in the ownership relation table
	pet.id = person_pet.pet_id AND
	
	--the person id matches the person id in the ownership relation table
	person.id = person_pet.person_id;
	
COMMIT;