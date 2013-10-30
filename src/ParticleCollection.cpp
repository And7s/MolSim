
#include "ParticleCollection.h"
#include <list>

using namespace std;

ParticleCollection::ParticleCollection(std::list<Particle> particles_) {
	for(std::list<Particle>::iterator i = particles_.begin(); i != particles_.end(); i++) {
		particles.push_back(&(*i));
	}
	cout << "inti";
	nextP = particles.begin();
	nextPP1 = particles.begin();
	nextPP2 = particles.begin();
	nextPP2++;
}
void ParticleCollection::Show() {
	cout << "Show "<<particles.size() << "Particles";
	for(std::list<Particle *>::iterator i = particles.begin(); i != particles.end(); i++) {
		cout << (*i)->toString() << endl;
	}
}

bool ParticleCollection::getNextParticle(Particle &p) {
	//nextP++;
	if(nextP != particles.end()) {
		cout << "is" << (*nextP);
		cout << "Adress is" << &(*nextP);
		p = *(*nextP);
		nextP++;
	}else {
		nextP = particles.begin();
		return false;
	}
}
bool ParticleCollection::getNextParticlePair(Particle &p1, Particle &p2) {
	//nextP++;
	if(nextPP2 == particles.end()) {		//innerloop determin
		nextPP1++;
		nextPP2 = nextPP1;
		nextPP2++;
		//cout <<"inner"<<endl;
		if(nextPP2 == particles.end()) {
			//cout <<"end"<<endl;
			nextPP1 = particles.begin();
			nextPP2 = particles.begin();
			nextPP2++;
			return false;
		}
		
		
	}else {


		/*p1 = *(*nextPP2);
		cout << "PP2"<<(*nextPP2)<<endl;
		nextPP2++;*/
	}
	p1 = *(*nextPP1);
	p2 = *(*nextPP2);
	//cout << "PP1" << (*nextPP1) << " PP2" << (*nextPP2)<<endl;
	nextPP2++;
	return true;
}