#include "People.h"


Person * People::addPerson(void)
{
	Person * p = new Person();
	people.push_back(p);
	return p;
}


void People::removePerson(Person * p)
{
	people.remove(p);
}