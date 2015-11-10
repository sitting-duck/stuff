BEGIN;

--delete all the entries in the pet table
DELETE FROM pet WHERE id IN (

	SELECT pet.id
	FROM pet, person, person_pet
	WHERE
	--for the person named Zed
	person.first_name = "Zed"		 AND
	--such that there is a match for Zed in person_pet
	person.id = person_pet.person_id AND
	--and such that that matching record matches also the id of the pet in the pet table
	pet.id    = person_pet.pet_id    AND
	
);

--delete all the entries in the person_pet table
DELETE FROM person_pet
	WHERE pet_id NOT IN (
	
		--only delete entries from person_pet that we just deleted from pet.
		--note that we only deleted Zed's pets so the remaining pets in pets 
		--do not need to be deleted from person_pet
		SELECT id FROM pet
	
	);
	
COMMIT;