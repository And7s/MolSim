/*
 * LCDomain.cpp
 *
 *  Created on: Nov 26, 2013
 *      Author: paul
 */

#include "LCDomain.h"

/**
 * Logger
 */
LoggerPtr loggerDomain(Logger::getLogger("main.domain"));


LCDomain::LCDomain(std::vector<int>* initalBounds, double cutOffRad, double cellDimension) {
	
	this->cutOffRadius = cutOffRad;
	this->cellDimension = cellDimension;

	//calculate size of halo-border
	//check whether the cutoff radius is an integer

	this->haloSize = ceil(cutOffRad / cellDimension);

	this->dimension = initalBounds->size();
	LOG4CXX_INFO(loggerDomain, "CellD "<<this->cellDimension<<" dime "<<this->dimension);

	/*
	 * if the 3-dimensional space is only 1 cell deep, it is far more efficient to treat the domain like 2D.
	 * In this case, there wont be any halo regions along the x-y hyperplane, which decreses the number of cells by approximately 3 times.
	 * It should be guaranteed, that the particles can not evolve any forces, which are unequal to zero along the z axis.
	 * Furthermore, the neighbour and boundary calculation are way faster.
	 */
	if(this->dimension == 3){
		if((*initalBounds)[2] <= 1){
			this->dimension = 2;
		}
	}

	std::vector<int> b (dimension,0);
	int k;
	for(k = 0; k < dimension; k++){
		int z = (*initalBounds)[k];
		this->bounds.push_back(z + haloSize*2);
	}
	//offset
	offset = new int[dimension - 1];
	int i;
	int linearspace = 1;
	for (i = 0; i < dimension - 1; i++) {
		offset[i] = this->bounds[i];
	}
	for (i = 0; i < dimension; i++) {
		linearspace = linearspace * this->bounds[i];
	}
	cells = new ParticleContainer*[linearspace];
	for (i = 0; i < linearspace; i++) {
		ParticleContainer* lc = new ParticleContainer(i);
		cells[i] = lc;
	}
	numberOfCells = linearspace;

	//compute boundary zone
	linearspace = 0;

	for(i = 0; i < haloSize; i++){	//each loop, the domain's size is reduced by 2 in each dimension.
		int sum = 0;
		switch(dimension){
		case 2:
			linearspace = 2 * ((bounds[0] - i*2) + (bounds[1] - i*2));
			break;
		case 3:
			linearspace = 2 * ((bounds[0] - i*2) * (bounds[1] - i*2) +
					(bounds[1] - i*2) * ((bounds[2] - i*2) - 2) +
					((bounds[0] - i*2) - 2) * ((bounds[2] - i*2) -2));
			break;
		default:
			LOG4CXX_ERROR(loggerDomain, "unsupported dimension"); break;
		}
	}
	boundaryZone = new ParticleContainer*[linearspace];
	numberOfBZCells = linearspace;
	k = 0;
	for(i=0; i<numberOfCells;i++){
		if(this->isBoundaryCell((*cells[i]))){
			boundaryZone[k] = cells[i];
			k++;
		}
	}
	numberOfBZCells = k;	//reset, edges are xounted twice - dont think so

	LOG4CXX_INFO(loggerDomain,"Domain generation finished --- dimensions: " << this->dimension << " Number of cells: " << numberOfCells <<
					" Cells in boundary zone: "<< linearspace << " Halo size: " << haloSize);

	ASSERT_WITH_MESSAGE(loggerDomain, haloSize > 0, "erroneous halo size");
	ASSERT_WITH_MESSAGE(loggerDomain, numberOfCells > 0, "erroneous domain size");
}

ParticleContainer* LCDomain::getCellAt(std::vector<int>& pos) {
	
	int index;
	switch (dimension) {
		case 1:
			index = pos[0];
			break;	//x
		case 2:
			index = pos[1] * (offset[0]) + pos[0];	//y * offsetX + x
			break;
		case 3:
			index =  pos[2] * offset[0] * offset[1] + pos[1] * offset[0] + pos[0]; //z * offsetX * offsetY + y * offsetX + x
			break;
		default:
			//can't happen
			index = -1;	// will raise error on bounds check
			break;
	}

	//does not get triggered if eg x is negative and other components are positive, so as a sum it's greater 0
	//room for improvement
	if(index < 0 || index > numberOfCells) {	//more efficient check for out of bounds
		assert(checkBounds(pos));
		std::cerr << " posizion demanded "<<pos[0]<<" "<<pos[1]<<" "<< pos[2]<<"\n";
		std::cerr << "Failed getCellAt\n";
	}
	return cells[index];
}

ParticleContainer**& LCDomain::getHaloCells() {
	return boundaryZone;
}





void LCDomain::insertParticle(Particle* part){
	int index = -1;

	ASSERT_WITH_MESSAGE(loggerDomain, (cutOffRadius>0), "Invalid Cutoff radius. Please specify first");

	ASSERT_WITH_MESSAGE(loggerDomain, !(dimension == 1 && (part->getX()[1] != 0 || part->getX()[2] != 0)), "Non-matching dimensions. Domain currently set to 1D, Particle seems to have a higher dimensional Position vector");

	ASSERT_WITH_MESSAGE(loggerDomain, !(dimension == 2 && part->getX()[2] != 0), "Non-matching dimensions. Domain currently set to 2D, Particle seems to have a 3D Position vector");

	//transform to std::vector - not necessary,
	std::vector<int> partPos (3,0);

	partPos[0] = floorFix((double)(part->getX()[0] / cutOffRadius)) + haloSize;
	partPos[1] = floorFix((double)(part->getX()[1] / cutOffRadius)) + haloSize;
	partPos[2] = floorFix((double)(part->getX()[2] / cutOffRadius)) + haloSize;

	LOG4CXX_TRACE(loggerDomain, "position: " << partPos[0] << " | " << partPos[1] << " | " << partPos[2]);

	for(int i = 0; i< 3; i++) {
		if(partPos[i]< 0 || partPos[i] >= bounds[i]) {
			std::cerr << "insert to "<<partPos[0]<< " "<<partPos[1]<< " "<<partPos[2]<<"\n";
			std::cerr << "try insert: "<<*part<<"\n";

			std::cerr << ((double) part->getX()[0] / cutOffRadius)<<" | "<< floor((double) part->getX()[0] / cutOffRadius)<<"\n";

			exit(-1);
		}
	}
	index = this->getCellAt(partPos)->getPosition();
	this->cells[index]->setParticle(part);
	LOG4CXX_TRACE(loggerDomain,"added Particle to cell: " << index);
}

void LCDomain::insertParticles(std::vector<Particle*>& parts) {
	particles = parts;
	//unsave to parrelelize due the fact working on the same vektor
	//#pragma omp parallel for
	for(int i = 0; i < parts.size(); i++){
		this->insertParticle(parts[i]);
	}
}

void LCDomain::deleteParticle(Particle* particle) {
	//parallel can cause error if found and removed, which changes the vector length (for other threads as aswell)
	//#pragma omp parallel for
	for(int i = 0; i < particles.size(); i++) {

		if(particle->getUid() == particles[i]->getUid()){
			
			particles.erase(particles.begin()+i);
			LOG4CXX_TRACE(loggerDomain,"deleted particle in lcDomain at pos "<<i);
			break;
		}
	}
}

void LCDomain::reset(){
	int i;

	#pragma omp parallel for
	for(i = 0; i < this->numberOfCells; i++){
		cells[i]->clearParticles();
	}

  	int size = this->haloParts.size();
    for(i = 0; i < size; i++){
		delete this->haloParts[i];
    }
    this->haloParts.clear();

	insertParticles(particles);
}

void LCDomain::resetafter(){
	int i;


	#pragma omp parallel for
	for(i = 0; i < this->numberOfCells; i++){
		cells[i]->clearParticles();
	}

  	insertParticles(particles);
  	for(int i = 0; i < haloParts.size(); i++){
		this->insertParticle(haloParts[i]);
	}
}

void LCDomain::getNeighbourCells(ParticleContainer * cell,std::vector<ParticleContainer*>* neighbours) {
	std::vector<int> axis = this->decodeDimensinalOrigin(cell->getPosition());
	//check, if the input cell's position is valid.

	if(!checkBounds(axis)){
		LOG4CXX_ERROR(loggerDomain,"invalid input cell - unable to get neighbours");
		return;
	}

	//gather actual neighbours
	std::vector<int> reference (axis);
	int x,y,z;

	switch(dimension){
	case 1:
		if(axis[0] > 0){
			reference[0] = axis[0] -1;
			neighbours->push_back(getCellAt(reference));
			LOG4CXX_TRACE(loggerDomain,"added: " << getCellAt(reference)->getPosition());
		}
		if(axis[0] < (bounds)[0]-1){
			reference[0] = axis[0] +1;
			neighbours->push_back(getCellAt(reference));
			LOG4CXX_TRACE(loggerDomain,"added: " << getCellAt(reference)->getPosition());
		}
		break;
	case 2:
		for(x=(axis[0]-1); x < (axis[0]+2);x++){
			for(y=(axis[1]-1); y < (axis[1]+2);y++){
				if((x >= 0) && (x < (bounds)[0]) && (y >= 0) && (y < (bounds)[1])){
					if(!(x == axis[0] && y == axis[1])){
						reference[0] = x;
						reference[1] = y;
						neighbours->push_back(getCellAt(reference));
						LOG4CXX_TRACE(loggerDomain,"added: " << getCellAt(reference)->getPosition());
					}
				}
			}
		}
		break;
	case 3:
		for(x=(axis[0]-1); x < (axis[0]+2);x++){
			for(y=(axis[1]-1); y < (axis[1]+2);y++){
				for(z=(axis[2]-1); z < (axis[2]+2);z++){
					if((x >= 0) && (x < (bounds)[0])
							&& (y >= 0) && (y < (bounds)[1])
							&& (z >= 0) && (z < (bounds)[2])){
						if(!(x == axis[0] && y == axis[1] && z == axis[2])){
							reference[0] = x;
							reference[1] = y;
							reference[2] = z;
							neighbours->push_back(getCellAt(reference));
						}
					}
				}
			}
		}
		break;
	default:
		LOG4CXX_ERROR(loggerDomain,"unsupported dimension size!");	//cant happen
		return;
	}
}

ParticleContainer**& LCDomain::getCells(){
	return cells;
}

void LCDomain::setCells(ParticleContainer**& cells) {
	this->cells = cells;
}


bool LCDomain::checkBounds(std::vector<int>& pos) {
	if (pos.size() != dimension) {
		LOG4CXX_ERROR(loggerDomain,
				"Non-matching dimensions! Domain is currently set to " << this->dimension << " dimensions!");
		return false;
	}
	int i;
	for(i=0; i < dimension; i++){
		if(((pos)[i] < 0) || ((pos)[i] > (bounds)[i])){
			LOG4CXX_ERROR(loggerDomain,"The requested position is not located in the domain space.");
			LOG4CXX_ERROR(loggerDomain,"INFO ABOUT ERROR: checked pos: " << (pos)[i] << " bounds: " << (bounds)[i] << "Dim: "<<i <<
					" - This error may indicate a malfunction in the boundary condition");
			return false;
		}
	}
	return true;
}

bool LCDomain::isBoundaryCell(ParticleContainer& cell) {
	std::vector<int> axis(dimension,0);
	axis = this->decodeDimensinalOrigin(cell.getPosition());

	switch(dimension){
	case 2:
		return ((axis[0] - this->haloSize < 0) || (axis[0] + this->haloSize >= this->bounds[0])) ||
					((axis[1] - this->haloSize < 0) || (axis[1] + this->haloSize >= this->bounds[1]));
	case 3:
		return ((axis[0] - this->haloSize < 0) || (axis[0] + this->haloSize >= this->bounds[0])) ||
						((axis[1] - this->haloSize < 0) || (axis[1] + this->haloSize >= this->bounds[1])) ||
						((axis[2] - this->haloSize < 0) || (axis[2] + this->haloSize >= this->bounds[2]));
	default:
		LOG4CXX_ERROR(loggerDomain, "unsupported dimension"); break;
	}
	return false;
}

std::vector<int> LCDomain::decodeDimensinalOrigin(int pos){
	//decompose the 1D position into its higher dimensional origin.

	std::vector<int> axis (dimension,0);
	switch(dimension){
	case 3:
		axis[2] = pos / (offset[0] * offset[1]);
		pos = pos - (axis[2] * offset[1] * offset[0]);
	case 2:
		axis[1] = (pos / (offset[0]));
		pos = pos - (axis[1] * offset[0]);
	case 1:
		axis[0] = pos;
		break;
	default:
		LOG4CXX_ERROR(loggerDomain,"unsupported dimension size!");	//cant happen
		break;
	}
	return axis;
}

void LCDomain::addHaloParticle(Particle* part) {
	this->haloParts.push_back(part);
}

int LCDomain::getDimension() {
	return dimension;
}

double LCDomain::getCutOffRadius(){
	return this->cutOffRadius;
}

int LCDomain::getHaloSize() {
	return haloSize;
}

int LCDomain::getNumberOfCells() {
	return numberOfCells;
}

int LCDomain::getCellDimension(){
	return this->cellDimension;
}

int LCDomain::getNumberOfBZCells(){
	return this->numberOfBZCells;
}

std::vector<Particle*>* LCDomain::getAllParticles() {
	return &(this->particles);
}

std::vector<int> LCDomain::getBounds() {
	return bounds;
}

int* LCDomain::getOffset(){
	return offset;
}
