/*
 * CSVWriter.cpp
 *
 *  Created on: Jan 23, 2014
 *      Author: friedrich
 */

#include "outputWriter/CSVWriter.h"

/**
 * Logger
 */
LoggerPtr loggerCSV(Logger::getLogger( "csvWriter"));

namespace outputWriter {
		CSVWriter::CSVWriter(){
			bins = 0;
			dimension =0;
			LOG4CXX_ERROR(loggerCSV, "In Wrong Dummy Constructor, exit");
			exit(1);
		}

		CSVWriter::CSVWriter(int dimension_, int bins_) {
				dimension = dimension_;
				bins = bins_;
				FILE* outFile1 = fopen("DensityFlow.csv", "w");
				FILE* outFile2 = fopen("VelocityFlow.csv", "w");
				for(int i = 1; i <= bins; i++){
					fprintf(outFile1, "%d", i);
					fprintf(outFile2, "%d", i);
					if(i!=bins){
						fprintf(outFile1, ",");
						fprintf(outFile2, ",");
					}else{
						fprintf(outFile1, "\n");
						fprintf(outFile2, "\n");
					}
				}
				if(fclose(outFile1)!=0){
					LOG4CXX_ERROR(loggerCSV, "Outfile1 unsuccessfully closed");
					exit(1);
				}
				if(fclose(outFile2)!=0){
					LOG4CXX_ERROR(loggerCSV, "Outfile2 unsuccessfully closed");
					exit(1);
				}
		}

		CSVWriter::~CSVWriter() {
		// TODO Auto-generated destructor stub
		}

		void CSVWriter::writeFile(std::vector<Particle*> particles) {
				double sizePerBin = ((double)dimension)/bins;
				double* density = new double[bins];
				double* velocity = new double[bins];
				double xPosition;

				Particle* p;
				FILE* outFile1;
				FILE* outFile2;
				int size = particles.size();
				for(int i = 0; i < bins; i++){
					density[i] = 0;
					velocity[i] = 0;
				}

				for(int i = 0; i < size; i++){
					p = particles[i];
					if(p->getNature()!=2&&p->getType()!=-1){
						xPosition = p->getX()[0];
						for(int j = 0; j < bins; j++){
							if(xPosition > j*sizePerBin && xPosition <= ((j+1)*sizePerBin)){
								density[j] = density[j]+1;
								velocity[j] = velocity[j] + abs((p->getV()[1]));
							}
						}
					}
				}

				if((outFile1 = fopen("DensityFlow.csv", "a"))==NULL){
					LOG4CXX_ERROR(loggerCSV, "Outfile1 could not be opened");
					exit(1);
				}
				if((outFile2 = fopen("VelocityFlow.csv", "a"))==NULL){
					LOG4CXX_ERROR(loggerCSV, "Outfile2 could not be opened");
					exit(1);
				}
				for(int i = 0; i < bins; i++){
					fprintf(outFile1, "%f", density[i]);
					fprintf(outFile2, "%f", velocity[i]);
					if(i<(bins-1)){
						fprintf(outFile1, ",");
						fprintf(outFile2, ",");
					}else{
						fprintf(outFile1, "\n");
						fprintf(outFile2, "\n");
					}
				}
				if(fclose(outFile1)!=0){
					LOG4CXX_ERROR(loggerCSV, "Outfile1 unsuccessfully closed");
					exit(1);
				}
				if(fclose(outFile2)!=0){
					LOG4CXX_ERROR(loggerCSV, "Outfile2 unsuccessfully closed");
					exit(1);
				}
		}

}

